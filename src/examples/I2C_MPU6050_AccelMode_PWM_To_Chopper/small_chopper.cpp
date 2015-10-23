    #include "i2c_cpp.h"
#define MPU6050_ADDR 0x68<<1

#include "MPU6050.h"
#include <stdlib.h>
#include "timer_cpp.h"
#include "flash.h"
#include "rcc.h"
#include "RCC_helper.h"
#include "GPIO_Helper.h"
#include "IRRemote.h"

//Small chopper

class ChopperControl: public I2C_ErrorHandler
{

private:
    TIMER_With_Channels* _timer;
    int16_t _ax_offset;
    int16_t _ay_offset;
    int16_t _az_offset;
    I2C* _i2c;
    MPU6050* _mpu;

    TIMER_Channel* _ch1_xminus;    //PA0
    TIMER_Channel* _ch2_yplus;     //PA1
    TIMER_Channel* _ch3_xplus;     //PA2
    TIMER_Channel* _ch4_yminus;    //PA3

    const uint16_t _max_threshold = 500;
    const uint16_t _min_threshold = 20;
    uint32_t _i2cClockSpeed;
    uint16_t _initialDuty;
    IRRemote* _irRemote;
    const GPIO_PIN_N  IR_PIN = GPIO_PIN2; //PORTE

    uint32_t _currentDuty;

public:

    ChopperControl(uint32_t i2cClockSpeed)
    {
        _i2cClockSpeed = i2cClockSpeed;
        Init();
    }

    void Init()
    {
        _timer = GPIO_Helper::F4_SetupTIM4_PD_12_13_14_15();

        //green: negative X
        _ch1_xminus = _timer->GetChannel(1);
        _ch1_xminus->SetupPWM1(_max_threshold, 0);
        _ch1_xminus->EnableChannel(true);

        //orange: positive Y
        _ch2_yplus = _timer->GetChannel(2);
        _ch2_yplus->SetupPWM1(_max_threshold, 0);
        _ch2_yplus->EnableChannel(true);

        //red: positive X
        _ch3_xplus = _timer->GetChannel(3);
        _ch3_xplus->SetupPWM1(_max_threshold, 0);
        _ch3_xplus->EnableChannel(true);

        //blue: negative Y
        _ch4_yminus = _timer->GetChannel(4);
        _ch4_yminus->SetupPWM1(_max_threshold, 0);
        _ch4_yminus->EnableChannel(true);
        _timer->EnableCounter(true);


        _i2c = GPIO_Helper::F4_SetupI2C1_PB_6_9(_i2cClockSpeed);
        _i2c->SetErrorHandler(this);
        _mpu = new MPU6050(_i2c);
        uint8_t id = _mpu->getDeviceID();
        _mpu->reset();
        RCC_Delay_ms(50);
        //_mpu->initialize(); //highest sensitivity
        //lowest sensitivity
        //_mpu->setFullScaleAccelRange(MPU6050_ACCEL_FS_16);
        //medium sensitivity
        //_mpu->setFullScaleAccelRange(MPU6050_ACCEL_FS_8);

        //low pass filtering
        //_mpu->setDLPFMode(MPU6050_DLPF_BW_5);
        //high pass filter
        //_mpu->setDHPFMode (MPU6050_DHPF_0P63);

        _initialDuty = _max_threshold / 6;
        _currentDuty = 0;

        GPIO_PORT* irPort = GPIOE::GetInstance();
        irPort->EnablePeripheralClock(true);
        GPIO_PIN* irPin = irPort->GetPin(IR_PIN);
        irPin->SetupGPIO_InFloat();
        irPin->SpeedHigh();

        _irRemote = new IRRemote(irPin);

        TIM3* tim2 = TIM3::GetInstance();
        tim2->EnablePeripheralClock(true);
        tim2->SetUpdatePeriod_us(50);
        tim2->EnableNVICInterrupt(true);
        tim2->EnableUpdateInterrupt(true);
        tim2->AddInterruptHandler(_irRemote);
        tim2->EnableCounter(true);

    }

    virtual void HandleError()
    {
    }

    bool isIRCode(uint32_t value)
    {   
        bool rc = false;
        if (_irRemote->decode())
        {            
            rc = _irRemote->getValue() == value;
        }
        return rc;
    }

    bool isPowerPushed(uint32_t val)
    {
        return val==0xE0E040BF || val==0x000A8B47 || val==0x99805850;
    }


    bool isVolumeUpPushed(uint32_t val)
    {
        return val==0xE0E0E01F || val==0x490 || val==0x296AD059;
    }

    bool isVolumeDownPushed(uint32_t val)
    {
        return val==0xE0E0D02F || val==0xc90 || val==0x65AF9C8A;
    }


    void UpdateDuty()
    {
        _ch1_xminus->UpdatePWMDuty(_currentDuty);
        _ch2_yplus->UpdatePWMDuty(_currentDuty);
        _ch3_xplus->UpdatePWMDuty(_currentDuty);
        _ch4_yminus->UpdatePWMDuty(_currentDuty);
    }

    void Run()
    {
        //_currentDuty = _max_threshold;
        //UpdateDuty();
    
        //while(1);

        uint16_t warmup = 0;
        uint16_t max_warmup = 1000;
        int16_t ax, ay, az;
        int16_t gx, gy, gz;

        for (uint16_t i = 0; i < max_warmup; ++i)
        {
            //_mpu->getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        }

        _ax_offset = ax;
        _ay_offset = ay;
        _az_offset = az;

        bool isEngaged = false;
        uint32_t irVal = 0;

        while (true)
        {
            if (_irRemote->decode())
            {
                irVal = _irRemote->getValue();
                _irRemote->resume();
            }
            if (isPowerPushed(irVal))
            {
                irVal = 0;
                if (!isEngaged)
                {
                    isEngaged = true;
                    _currentDuty = _initialDuty;
                    UpdateDuty();
                //  _timer->EnableCounter(true);
                }
                else
                {
                    isEngaged = false;
                //  _timer->EnableCounter(false);
                    _currentDuty = 0;
                    UpdateDuty();
                }
                //RCC_Delay_ms(1);

            }

            if (isEngaged)
            {
                if (isVolumeUpPushed(irVal) && _currentDuty < _max_threshold)
                {
                    irVal = 0;
                    _currentDuty += 20;
                    UpdateDuty();
                    RCC_Delay_ms(1);
                }               else if (isVolumeDownPushed(irVal) && _currentDuty > _max_threshold/10)
                {
                    irVal = 0;
                    _currentDuty -= 20;
                    UpdateDuty();
                    RCC_Delay_ms(1);

                }
//              MotionIteration();
            }
        }

    }

    void MotionIteration()
    {
        uint16_t read_delay_ms = 20;
        int16_t ax, ay, az;
        int16_t gx, gy, gz;
        uint16_t max_a = 0;

        _mpu->getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

        ax -= _ax_offset;
        ay -= _ay_offset;
        az -= _az_offset;

        if (abs(ax) > max_a)
        {
            max_a = abs(ax);
        }
        if (abs(ay) > max_a)
        {
            max_a = abs(ay);
        }
        if (abs(az) > max_a)
        {
            max_a = abs(az);
        }

        TIMER_Channel* chx = 0;
        TIMER_Channel* chy = 0;
        if (abs(ax) > _min_threshold)
        {
            if (ax > 0)
            {
                chx = _ch3_xplus;
            }
            else
            {
                chx = _ch1_xminus;
                ax = abs(ax);
            }

            chx->UpdatePWMDuty(ax);
        }

        if (abs(ay) > _min_threshold)
        {
            if (ay > 0)
            {
                chy = _ch2_yplus;
            }
            else
            {
                chy = _ch4_yminus;
                ay = abs(ay);
            }

            chy->UpdatePWMDuty(ay);
        }

        RCC_Delay_ms(2);
        if (chx)
        {
            chx->UpdatePWMDuty(0);
        }
        if (chy)
        {
            chy->UpdatePWMDuty(0);
        }

    }

};

int main()
{
    F4_EnableHSI_100Mhz();
    uint32_t i2cClockSpeed = 100000;
    ChopperControl test(i2cClockSpeed);
    test.Run();
}
