#define MPU6050_ADDR 0x68<<1

#include "i2c_cpp.h"

#ifdef USE_USART
#include "usart_cpp.h"
#endif

#include "MPU6050.h"
#include <stdlib.h>
#include "flash.h"
#include "RCC_helper.h"
#include "GPIO_Helper.h"


/*
 The accelerometer and gyroscope measurements are explained in the MPU-6050 datasheet
 in the GYRO_CONFIG and ACCEL_CONFIG register descriptions (sections 4.4 and 4.5 on pages 14 and 15).

 The scale of each depends on the sensitivity settings chosen,
 which can be one of +/- 2, 4, 8, or 16g for the accelerometer
 and one of +/- 250, 500, 1000, or 2000 deg/sec for the gyroscope.

 The accelerometer produces data in units of acceleration (distance over time2),
 and the gyroscope produces data in units of rotational velocity (rotation distance over time).

 The output scale for any setting is [-32768, +32767] for each of the six axes.

 The default setting in the I2Cdevlib class is +/- 2g for the accel and +/- 250 deg/sec for the gyro.
 If the device is perfectly level and not moving, then:

 X/Y accel axes should read 0
 Z accel axis should read 1g, which is +16384 at a sensitivity of 2g
 X/Y/Z gyro axes should read 0

 In reality, the accel axes won't read exactly 0 since it is difficult to be perfectly level
 and there is some noise/error, and the gyros will also not read exactly 0 for the same reason (noise/error).

 */

#define     M_PI   3.14159265358979323846

class TestMPU6050: public I2C_ErrorHandler
{
public:

    TestMPU6050()
    {
    }

    virtual void HandleError()
    {
    }

    void Run(uint32_t i2cClockSpeed)
    {
        bool dmpReady = false; // set true if DMP init was successful
        uint8_t mpuIntStatus; // holds actual interrupt status byte from MPU
        uint8_t devStatus; // return status after each device operation (0 = success, !0 = error)
        uint16_t packetSize; // expected DMP packet size (default is 42 bytes)
        uint16_t fifoCount; // count of all bytes currently in FIFO
        uint8_t fifoBuffer[64]; // FIFO storage buffer

        Quaternion q; // [w, x, y, z] quaternion container
        VectorInt16 aa; // [x, y, z] accel sensor measurements
        VectorInt16 aaReal; // [x, y, z] gravity-free accel sensor measurements
        VectorInt16 aaWorld; // [x, y, z] world-frame accel sensor measurements
        VectorFloat gravity; // [x, y, z] gravity vector
        float eu[3]; // [psi, theta, phi] Euler angle container
        float ypr[3]; // [yaw, pitch, roll] yaw/pitch/roll container and gravity vector
        uint16_t y, p, r;
        float yaw_offset;

        I2C1* i2c = GPIO_Helper::SetupI2C1_PB_6_9(i2cClockSpeed);
        i2c->SetErrorHandler(this);
        MPU6050 mpu(i2c);

        //Initialized with highest sensitivities
        mpu.reset();
        RCC_Delay_ms(50);
        mpu.initialize();

#ifdef USE_USART
        uint32_t clockSpeed = 1200000;
        USART* usart = GPIO_Helper::SetupUSART2_PA_2_3(clockSpeed);
#endif        

        devStatus = mpu.dmpInitialize();

        if (devStatus != 0)
        {
            while (1)
                ;
        }

        mpu.setDMPEnabled(true);
        packetSize = mpu.dmpGetFIFOPacketSize();

        while (1)
        {
            // wait for MPU interrupt or extra packet(s) available
            //while (!mpuInterrupt && fifoCount < packetSize) {
            //}

            // reset interrupt flag and get INT_STATUS byte
            mpuIntStatus = mpu.getIntStatus();
            // get current FIFO count
            fifoCount = mpu.getFIFOCount();
            // check for overflow (this should never happen unless our code is too inefficient)
            if (mpuIntStatus & 0x02)
            {
                // wait for correct available data length, should be a VERY short wait
                while (fifoCount < packetSize)
                    fifoCount = mpu.getFIFOCount();
                // read a packet from FIFO
                mpu.getFIFOBytes(fifoBuffer, packetSize);
                // track FIFO count here in case there is > 1 packet available
                // (this lets us immediately read more without waiting for an interrupt)
                fifoCount -= packetSize;

                // display quaternion values in easy matrix form: w x y z
                mpu.dmpGetQuaternion(&q, fifoBuffer);

                mpu.dmpGetEuler(eu, &q);
                eu[0] *= 180. / M_PI;
                eu[1] *= 180. / M_PI;
                eu[2] *= 180. / M_PI;
                mpu.dmpGetGravity(&gravity, &q);

                mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

                //rad to degrees
                ypr[0] *= 180. / M_PI;
                ypr[1] *= 180. / M_PI;
                ypr[2] *= 180. / M_PI;

                // display real acceleration, adjusted to remove gravity
                mpu.dmpGetAccel(&aa, fifoBuffer);
                mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);

                // display initial world-frame acceleration, adjusted to remove gravity
                // and rotated based on known orientation from quaternion
                mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);

#ifdef USE_USART
                if (usart->IsRXNE())
                {
                    if (usart->Receive() == 23)
                    {
                        usart->SendWord((int16_t)(ypr[0]));
                        usart->SendWord((int16_t) ypr[1]);
                        usart->SendWord((int16_t) ypr[2]);
                    }
                }

#endif                
            }
            else if ((mpuIntStatus & 0x10) || fifoCount == 1024)
            {
                // reset so we can continue cleanly
                mpu.resetFIFO();
            }
        }
    }

};

int main()
{
//    F4_EnableHSE_168Mhz();
    FLASH_EnableDCache(TRUE);
    FLASH_EnableICache(TRUE);
    FLASH_EnablePrefetchBuffer(TRUE);

    FLASH_SetWaitState(3);

    RCC_EnableHSI(TRUE);
    uint8_t pllm = 8;
    uint16_t plln = 200;
    uint16_t pllp = 4;
    RCC_EnablePLL(pllm, plln, pllp);

    RCC_SetAHBPrescalerDiv2();


	TestMPU6050 test;
    uint32_t i2cClockSpeed = 100000;
    test.Run(i2cClockSpeed);
}
