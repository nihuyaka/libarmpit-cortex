/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 igorS
 *  
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */



#include "bkp.h"
#include "pwr.h"
#include "rtc_cpp.h"
#include "gpio_cpp.h"
#include "exti.h"
#include "systick.h"

class TamperHandler: public BKP_TamperInterrupt_Handler
{
public:
    virtual void HandleInterrupt(bool isEvent)
    {

    }
};

static void systick_handler(void)
{
    GPIOB::GetInstance()->TogglePin(GPIO_PIN12);
}

class PowerModeTester: public RTC_Interrupt_Handler
{

private:

    GPIO_PORT* gpioPort;
    PWR* pwr;
    BKP* bkp;
    RTC* rtc;
    EXTI17* exti17;
    RCC* rcc;

    void StartClock()
    {
        rcc->SetAHBPrescalerDiv2();
        rcc->SetAPB1PrescalerDiv1();
        rcc->SetAPB2PrescalerDiv1();
        rcc->SetADCPrescalerDiv2();
        rcc->EnableHSI(9);
    }

    void InitSystick(uint32_t ms)
    {
        uint32_t clock = rcc->GetSystemClock();
        uint32_t count = clock * ms / 1000 * 8;
        SystickEnable(count, true, true, systick_handler);
    }

    void InitGPIO()
    {
        gpioPort->EnablePeripheralClock(true);
        gpioPort->SetupGPIO_OutPP(GPIO_PIN12);
        gpioPort->SetupGPIO_OutPP(GPIO_PIN14);
        gpioPort->SetupGPIO_OutPP(GPIO_PIN13);
    }

    void InitRTC(uint32_t second, uint32_t alarm)
    {
        rcc->EnableLSI();
        rtc->SetClockSourceLSI();
        rtc->SetPrescaler_ms(second);
        rtc->SetAlarm_ms(alarm);
        rtc->EnableClock(true);
        if (alarm != 0)
        {
            rtc->EnableAlarmInterrupt(true, this);
        }
    }

public:

    PowerModeTester()
    {
        gpioPort = GPIOB::GetInstance();
        pwr = PWR::GetInstance();
        bkp = BKP::GetInstance();
        rtc = RTC::GetInstance();
        rcc = RCC::GetInstance();
        exti17 = EXTI17::GetInstance();
    }

    void TestStop()
    {
        StartClock();
        InitGPIO();

        pwr->EnablePeripheralClock(true);
        bkp->EnablePeripheralClock(true);
        pwr->EnableBKPWriteAccess(true);

        InitSystick(200);

        InitRTC(1000, 10000);

        EXTI17::GetInstance()->EnableInterruptRisingEdge(true);
        while (1)
        {
            rtc->SetCounter(0);
            rcc->Delay_ms(2000);
            pwr->Stop(true, true);
            //clock will be restarted in the alarm int handler
            rcc->Delay_ms(1000);
            gpioPort->ResetPin(GPIO_PIN14);
            gpioPort->ResetPin(GPIO_PIN13);
        }
    }

    void TestStandBy()
    {
        StartClock();
        InitGPIO();

        pwr->EnablePeripheralClock(true);
        bkp->EnablePeripheralClock(true);
        pwr->EnableBKPWriteAccess(true);

        InitSystick(200);

        InitRTC(1000, 10000);

        if (pwr->IsSBF())
        {
            gpioPort->SetPin(GPIO_PIN14);
            pwr->ClearSBF();
        }
        rcc->Delay_ms(2000);
        pwr->Standby(true, true);
    }

    void TestSleep()
    {
        StartClock();
        InitGPIO();

        pwr->EnablePeripheralClock(true);
        bkp->EnablePeripheralClock(true);
        pwr->EnableBKPWriteAccess(true);

        InitSystick(200);

        InitRTC(10000, 0);
        rtc->EnableSecondInterrupt(true);

        while (1)
        {
            rcc->Delay_ms(2000);
            gpioPort->ResetPin(GPIO_PIN14);
            pwr->Sleep(true);
            if (pwr->IsWUF())
            {
                pwr->ClearWUF();
                gpioPort->SetPin(GPIO_PIN14);
            }
        }
    }

    void HandleInterrupt(bool isOverrun, bool isAlarm, bool isSecond)
    {
        if (isAlarm && pwr->IsWUF())
        {
            pwr->ClearWUF();
            gpioPort->SetPin(GPIO_PIN14);
            StartClock();
        }
        if (exti17->IsPending())
        {
            gpioPort->SetPin(GPIO_PIN13);
            exti17->ClearPending();
        }
    }

};

void bkp_pwr_test()
{
    PWR* pwr = PWR::GetInstance();
    pwr->EnablePeripheralClock(true);

    BKP* bkp = BKP::GetInstance();
    bkp->EnablePeripheralClock(true);

    pwr->EnableBKPWriteAccess(true);

    bkp->EnableTamperPin(true);

    TamperHandler tamperHandler;
    bkp->EnableTamperInterrupt(true, &tamperHandler);

    bkp->WriteBackupData(0xbeef, 1);
    uint16_t d = bkp->ReadBackupData(1);

    bkp->WriteBackupData(0xbeef, 42);
    d = bkp->ReadBackupData(42);

    bkp->ResetBackupDomain();
    d = bkp->ReadBackupData(42);

    bkp->WriteBackupData(0xbeef, 2);
    d = bkp->ReadBackupData(2);
    //trigger tamper here
    d = bkp->ReadBackupData(2);

    bkp->EnableTamperPin(false);
    bkp->EnableTamperPin(true);
    bkp->WriteBackupData(0xbeef, 3);
    d = bkp->ReadBackupData(3);

}


int main()
{
    //Clocks initialized inside the test
    bkp_pwr_test();
}
