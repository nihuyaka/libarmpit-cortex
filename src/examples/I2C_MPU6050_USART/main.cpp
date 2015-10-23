#include "i2c_cpp.h"
#define MPU6050_ADDR 0x68<<1

#include "MPU6050.h"
#include <stdlib.h>
#include "usart_cpp.h"
#include "flash.h"

#define 	M_PI   3.14159265358979323846


static uint16_t g_y, g_p, g_r;



class TestMPU6050: public I2C_ErrorHandler
{
private:
    I2C* _i2c;
    MPU6050* _mpu;
    uint8_t _id;

    Quaternion  _q; // [w, x, y, z] quaternion container
    VectorInt16 _aa; // [x, y, z] accel sensor measurements
    VectorInt16 _aaReal; // [x, y, z] gravity-free accel sensor measurements
    VectorInt16 _aaWorld; // [x, y, z] world-frame accel sensor measurements
    VectorFloat _gravity; // [x, y, z] gravity vector
    float _euler[3]; // [psi, theta, phi] Euler angle container
    float _ypr[3]; // [yaw, pitch, roll] yaw/pitch/roll container and gravity vector
    USART1* usart;
    uint16_t y, p, r;

    void Init_i2c()
    {
        _i2c = I2C1::GetInstance();

        bool initializeGPIO = true;
        bool isDuty16_9 = false;
        bool isFmMode = false;
        _i2c->Initialize(300000, isDuty16_9, isFmMode, initializeGPIO);
        _i2c->SetModeI2C();
        _i2c->EnableACK(false);
        _i2c->SetOwnAddr7Bit(0x00);
        for (uint8_t i = 0; i < 3; ++i) 
        {
            _euler[i] = 0.;
            _ypr[i] = 0.;
        }
        y = p = r = 0;
    }


public:

    TestMPU6050()
    {
        GPIO_PORT* i2c1_port = GPIOB::GetInstance();
        i2c1_port->EnablePeripheralClock(false);
        i2c1_port->EnablePeripheralClock(true);
        usart = USART1::GetInstance();
    }

    virtual void HandleError()
    {
    }


    void Run()
    {
        bool dmpReady = false; // set true if DMP init was successful
        uint8_t mpuIntStatus; // holds actual interrupt status byte from MPU
        uint8_t devStatus; // return status after each device operation (0 = success, !0 = error)
        uint16_t packetSize; // expected DMP packet size (default is 42 bytes)
        uint16_t fifoCount; // count of all bytes currently in FIFO
        uint8_t fifoBuffer[64]; // FIFO storage buffer
// orientation/motion vars
// packet structure for InvenSense teapot demo
        uint8_t teapotPacket[14] =
        { '$', 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x00, '\r', '\n' };

        Init_i2c();
        _mpu = new MPU6050(_i2c);
        _mpu->initialize();


        usart->Enable(true);
        usart->SetBaudRate(200000);
        //USART_Handler h;
        //usart->SetIrqHandler (&h);
        //usart->EnableInterrupt_RXNE(true);
        usart->EnableTransmitter(true);
        usart->EnableReceiver(true);
        
   
        devStatus = _mpu->dmpInitialize();
        
        if (devStatus != 0) 
        {
            while(1)
                ;
        }
        
        _mpu->setDMPEnabled(true);
        packetSize = _mpu->dmpGetFIFOPacketSize();      

        while (1)
        {
            // wait for MPU interrupt or extra packet(s) available
            //while (!mpuInterrupt && fifoCount < packetSize) {
            //}

            // reset interrupt flag and get INT_STATUS byte
            mpuIntStatus = _mpu->getIntStatus();
            // get current FIFO count
            fifoCount = _mpu->getFIFOCount();
            // check for overflow (this should never happen unless our code is too inefficient)
            if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
                // reset so we can continue cleanly
                _mpu->resetFIFO();
                // otherwise, check for DMP data ready interrupt (this should happen frequently)
            } else if (mpuIntStatus & 0x02) {
                // wait for correct available data length, should be a VERY short wait
                while (fifoCount < packetSize) fifoCount = _mpu->getFIFOCount();
                // read a packet from FIFO
                _mpu->getFIFOBytes(fifoBuffer, packetSize);
                // track FIFO count here in case there is > 1 packet available
                // (this lets us immediately read more without waiting for an interrupt)
                fifoCount -= packetSize;

                // display quaternion values in easy matrix form: w x y z
                _mpu->dmpGetQuaternion(&_q, fifoBuffer);

                _mpu->dmpGetEuler(_euler, &_q);
                _euler[0] *= 180./M_PI;
                _euler[1] *= 180./M_PI;
                _euler[2] *= 180./M_PI;
                _mpu->dmpGetGravity(&_gravity, &_q);

                _mpu->dmpGetYawPitchRoll(_ypr, &_q, &_gravity);
                
                //rad to degrees
                _ypr[0] *= 180./M_PI;
                _ypr[1] *= 180./M_PI;
                _ypr[2] *= 180./M_PI;
                
                
                // display real acceleration, adjusted to remove gravity
                _mpu->dmpGetAccel(&_aa, fifoBuffer);
                _mpu->dmpGetLinearAccel(&_aaReal, &_aa, &_gravity);
                
                // display initial world-frame acceleration, adjusted to remove gravity
                // and rotated based on known orientation from quaternion
                _mpu->dmpGetLinearAccelInWorld(&_aaWorld, &_aaReal, &_q);
                
                // display quaternion values in InvenSense Teapot demo format:
                /*
                teapotPacket[2] = fifoBuffer[0];
                teapotPacket[3] = fifoBuffer[1];
                teapotPacket[4] = fifoBuffer[4];
                teapotPacket[5] = fifoBuffer[5];
                teapotPacket[6] = fifoBuffer[8];
                teapotPacket[7] = fifoBuffer[9];
                teapotPacket[8] = fifoBuffer[12];
                teapotPacket[9] = fifoBuffer[13];
                */
                //Serial.write(teapotPacket, 14);
                //teapotPacket[11]++; // packetCount, loops at 0xFF on purpose
                if (usart->IsRXNE())
                {
                    if (usart->Receive() == 23)
                    {
                        usart->SendWord((int16_t) _euler[0]);
                        usart->SendWord((int16_t)_euler[1]);
                        usart->SendWord((int16_t)_euler[2]);
                    }
                }
        
                
            }
        }
    }

};

int main()
{
    FLASH_EnablePrefetchBuffer(TRUE);
    FLASH_SetWaitState (2);

    RCC_SetAHBPrescalerDiv1();
    RCC_SetAPB1PrescalerDiv2();
    RCC_SetAPB2PrescalerDiv4();
    RCC_SetADCPrescalerDiv2();
    RCC_EnableHSI(true);

    //44xx HSI no pll 20-100kHz
    //12xx  pll 10 300KHz = 4xxKhz
    
    RCC_EnablePLL(15);

    
    //test_mpu6050();
    
    TestMPU6050 test;
    test.Run();
}
