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



#include "rtc_cpp.h"
#include "exti.h"
#include "pwr.h"
#include "bkp.h"
#include "gpio_cpp.h"

class My_RTC_Interrupt_Handler: public RTC_Interrupt_Handler
{

private:

    uint32_t alarmCount;
    uint32_t secondCount;

public:

    My_RTC_Interrupt_Handler()
    {
        alarmCount = 0;
        secondCount = 0;
    }

    void HandleInterrupt(bool isOverrun, bool isAlarm, bool isSecond)
    {
        static RTC* rtc = RTC::GetInstance();
        if (isAlarm)
        {
            ++alarmCount;
            rtc->SetCounter(0);
            rtc->SetAlarm_ms(2000);
            GPIOB::GetInstance()->TogglePin(GPIO_PIN13);
        }
        if (isSecond)
        {
            ++secondCount;
            GPIOB::GetInstance()->TogglePin(GPIO_PIN12);
        }
        if (isOverrun)
        {
            static volatile uint32_t tmp = 0;
        }
    }

};

static void rtc_test()
{

    GPIOB::GetInstance()->EnablePeripheralClock(true);
    GPIOB::GetInstance()->SetupGPIO_OutPP(GPIO_PIN12);  
    GPIOB::GetInstance()->SetupGPIO_OutPP(GPIO_PIN13);  


    My_RTC_Interrupt_Handler handler;
    RTC* rtc = RTC::GetInstance();
    rtc->SetClockSourceLSI();

    PWR::GetInstance()->EnablePeripheralClock(true);
    BKP::GetInstance()->EnablePeripheralClock(true);
    PWR::GetInstance()->EnableBKPWriteAccess(true);

    RCC::GetInstance()->EnableLSI();
    rtc->EnableClock(true);
    rtc->WaitRSF();
    rtc->SetCounter(0);
    rtc->SetPrescaler_ms(1000);
    rtc->SetAlarm_ms(2000);

    rtc->EnableAlarmInterrupt(true, &handler);
    rtc->EnableSecondInterrupt(true, &handler);
    rtc->EnableOverrunInterrupt(true, &handler);

    //rtc->OutputSecondPulse(true);
    //rtc->OutputAlarmdPulse(true);

    //EXTI17::GetInstance()->EnableInterruptFallingEdge(true);
    //EXTI17::GetInstance()->EnableInterruptRisingEdge(true);
    while (1)
    {

    }
}

int main()
{
    RCC* rcc = RCC::GetInstance();
    rcc->SetAHBPrescalerDiv4();
    rcc->SetAPB1PrescalerDiv1();
    rcc->SetAPB2PrescalerDiv1();
    rcc->SetADCPrescalerDiv2();
    rcc->EnableHSI(3);

    rtc_test();
}

