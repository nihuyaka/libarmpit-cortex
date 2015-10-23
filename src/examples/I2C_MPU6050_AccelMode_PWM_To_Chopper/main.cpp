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

//Fred ESC PWM

class ChopperControl: public I2C_ErrorHandler, IRRemoteCallback
{

private:
    TIMER_With_Channels* _timer;
    int16_t _ax_offset;
    int16_t _ay_offset;
    int16_t _az_offset;

    int16_t _ax, _ay, _az;

    I2C* _i2c;
    MPU6050* _mpu;

    TIMER_Channel* _ch1; //PA0
    TIMER_Channel* _ch2; //PA1
    TIMER_Channel* _ch3; //PA2
    TIMER_Channel* _ch4; //PA3

    static const uint16_t period_ms = 20000;
    uint32_t _i2cClockSpeed;
    IRRemote* _irRemote;
    uint32_t _remoteCode;
    uint32_t _totalIREvents;

    bool _isArmed;
    uint32_t _currentDuty;

public:

    ChopperControl(uint32_t i2cClockSpeed)
    {
        _i2cClockSpeed = i2cClockSpeed;
        Init();
        _totalIREvents = 0;
        _isArmed = false;
        _currentDuty = 0;
    }

    void Init()
    {
        _timer = GPIO_Helper::SetupTIM2_PA_0_1_2_3();

        _ch1 = _timer->GetChannel(1);
        _ch1->SetupPWM1(20000, 0);
        _ch1->EnableChannel(true);

        _ch2 = _timer->GetChannel(2);
        _ch2->SetupPWM1(20000, 0);
        _ch2->EnableChannel(true);

        _ch3 = _timer->GetChannel(3);
        _ch3->SetupPWM1(20000, 0);
        _ch3->EnableChannel(true);

        _ch4 = _timer->GetChannel(4);
        _ch4->SetupPWM1(20000, 0);
        _ch4->EnableChannel(true);
        _timer->EnableCounter(true);

        _i2c = GPIO_Helper::SetupI2C1_PB_6_9(_i2cClockSpeed);
        //_i2c->SetErrorHandler(this);
        _mpu = new MPU6050(_i2c);
        uint8_t id = _mpu->getDeviceID();
        _mpu->reset();
        RCC_Delay_ms(50);
        _mpu->initialize(); //highest sensitivity
        //lowest sensitivity
        _mpu->setFullScaleAccelRange(MPU6050_ACCEL_FS_16);
        //medium sensitivity
        //_mpu->setFullScaleAccelRange(MPU6050_ACCEL_FS_8);

        //low pass filtering
        _mpu->setDLPFMode(MPU6050_DLPF_BW_5);
        //high pass filter
        //_mpu->setDHPFMode (MPU6050_DHPF_0P63);

        GPIOE::GetInstance()->EnablePeripheralClock(true);
        GPIO_PIN* irPin = GPIOE::GetInstance()->GetPin(GPIO_PIN2);
        //GPIOC::GetInstance()->EnablePeripheralClock(true);
        //GPIO_PIN* irPin = GPIOC::GetInstance()->GetPin(GPIO_PIN13);

        irPin->SetupGPIO_InFloat();
        //irPin->SetSpeedHigh();

        _irRemote = new IRRemote(irPin);
        _irRemote->setCallback(this);

        TIM3* tim2 = TIM3::GetInstance();
        tim2->EnablePeripheralClock(true);
        tim2->SetUpdatePeriod_us(50);
        tim2->EnableNVICInterrupt(true);
        tim2->EnableUpdateInterrupt(true);
        tim2->AddInterruptHandler(_irRemote);
        tim2->EnableCounter(true);

    }

    void initESC()
    {

        _ch1->SetupPWM1(20000, 2000);
        _ch2->SetupPWM1(20000, 2000);
        _ch3->SetupPWM1(20000, 2000);
        _ch4->SetupPWM1(20000, 2000);

        RCC_Delay_ms(2000);

        _ch1->SetupPWM1(20000, 700);
        _ch2->SetupPWM1(20000, 700);
        _ch3->SetupPWM1(20000, 700);
        _ch4->SetupPWM1(20000, 700);

        RCC_Delay_ms(2000);

        _ch1->SetupPWM1(20000, 1000);
        _ch2->SetupPWM1(20000, 1000);
        _ch3->SetupPWM1(20000, 1000);
        _ch4->SetupPWM1(20000, 1000);

        RCC_Delay_ms(2000);

    }

    virtual void HandleError()
    {
    }

    virtual void RemoteButtonPressed(uint32_t buttonValue)
    {
        _remoteCode = buttonValue;
        ++_totalIREvents;
        if (isPowerPushed(buttonValue))
        {
            if (!_isArmed)
            {
                _currentDuty = 1000;
                _isArmed = true;
                initESC();

            }
            else
            {
                _currentDuty = 700;
                _isArmed = false;

            }

            UpdateDuty();

        }
        if (_isArmed)
        {
            if (isVolumeUpPushed(buttonValue) && _currentDuty < 2000)
            {
                _currentDuty += 20;
                UpdateDuty();
                RCC_Delay_ms(1);
            }
            else if (isVolumeDownPushed(buttonValue) && _currentDuty >= 800)
            {
                _currentDuty -= 20;
                UpdateDuty();
                RCC_Delay_ms(1);

            }
        }
    }

    //  bool isIRCode(uint32_t value)
    //  {
    //      bool rc = false;
    //      if (_irRemote->decode())
    //      {
    //          rc = _irRemote->getValue() == value;
    //      }
    //      return rc;
    //  }

    bool isPowerPushed(uint32_t val)
    {
        return val == 0xE0E040BF || val == 0x000A8B47 || val == 0x99805850;
    }

    bool isVolumeUpPushed(uint32_t val)
    {
        return val == 0xE0E0E01F || val == 0x490 || val == 0x296AD059;
    }

    bool isVolumeDownPushed(uint32_t val)
    {
        return val == 0xE0E0D02F || val == 0xc90 || val == 0x65AF9C8A;
    }

    void UpdateDuty()
    {
        /*
         _ch1->UpdatePWMDuty(_currentDuty);
         _ch2->UpdatePWMDuty(_currentDuty);
         _ch3->UpdatePWMDuty(_currentDuty);
         _ch4->UpdatePWMDuty(_currentDuty);
         */

        _ch1->SetupPWM1(20000, _currentDuty);
        _ch2->SetupPWM1(20000, _currentDuty);
        _ch3->SetupPWM1(20000, _currentDuty);
        _ch4->SetupPWM1(20000, _currentDuty);
    }

#if 0
    void updateDuty2()
    {
        /*
         _ch1->UpdatePWMDuty(_currentDuty);
         _ch2->UpdatePWMDuty(_currentDuty);
         _ch3->UpdatePWMDuty(_currentDuty);
         _ch4->UpdatePWMDuty(_currentDuty);
         */

        int16_t ax = _ax;
        int16_t ay = _ay;

        int16_t ACCEL_MAX = 400;
        int26_t PWM_CEILING = 400; // maybe consider setting to 2000 - currentDuty

        if (abs(ax) > ACCEL_MAX)
            ax = (ax > 0) ? ACCEL_MAX : ACCEL_MAX * (-1);
        if (abs(ay) > ACCEL_MAX)
            ay = (ay > 0) ? ACCEL_MAX : ACCEL_MAX * (-1);

        float coeffX = (float) ax / (float) ACCEL_MAX;
        float coeffY = (float) ay / (float) ACCEL_MAX;

        uint32_t ch1Duty = _currentDuty + PWM_CEILING * coeffX * coeffY;
        uint32_t ch1Duty = _currentDuty + PWM_CEILING * coeffX * coeffY;
        _ch1->SetupPWM1(20000, _currentDuty);
        _ch2->SetupPWM1(20000, _currentDuty);
        _ch3->SetupPWM1(20000, _currentDuty);
        _ch4->SetupPWM1(20000, _currentDuty);
    }
#endif

    void Run()
    {

        uint32_t clockSpeed = 1200000;
        USART* usart = GPIO_Helper::SetupUSART2_PA_2_3(clockSpeed);

        //initESC();

        uint16_t max_warmup = 1000;
        int16_t ax, ay, az;
        int16_t gx, gy, gz;

        for (uint16_t i = 0; i < max_warmup; ++i)
        {
            _mpu->getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        }

        _ax_offset = ax;
        _ay_offset = ay;
        _az_offset = az;

        while (true)
        {
            readAccelero2(usart);

            if (_currentDuty > 1600)
            {
                //              updateDuty2();
            }
        }

    }
    void readAccelero()
    {
        int16_t ax, ay, az;
        int16_t gx, gy, gz;

        _mpu->getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

        ax -= _ax_offset;
        ay -= _ay_offset;
        az -= _az_offset;

        RCC_Delay_ms(2);

    }

    void readAccelero2(USART* usart)
    {

        int16_t gx, gy, gz;

        _mpu->getMotion6(&_ax, &_ay, &_az, &gx, &gy, &gz);

        _ax -= _ax_offset;
        _ay -= _ay_offset;
        _az -= _az_offset;

        if (usart->IsRXNE())
        {
            if (usart->Receive() == 23)
            {
                usart->SendWord((int16_t)(_ax));
                usart->SendWord((int16_t) (_ay));
                usart->SendWord((int16_t) (_az));
            }
        }

        RCC_Delay_ms(2);

    }

};

int main()
{
#if defined (STM32F1)   
    RCC_EnableHSI_72Mhz_AHB_72Mhz_APB1_36MHz_APB2_72MHz();
#else

    //RCC_EnableHSI_100Mhz();
    //RCC_SetAHBPrescalerDiv2();

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

    //RCC_SetAPB1PrescalerDiv16();

    volatile uint32_t c1 = RCC_GetAPB1_CLK();
    volatile uint32_t c2 = RCC_GetAPB2_CLK();

#endif  
    uint32_t i2cClockSpeed = 100000;
    ChopperControl test(i2cClockSpeed);
    test.Run();
}
