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


#include "timer_cpp.h"
#include "gpio_cpp.h"

class CCHandler : public TIMER_Channel_CCInterrupt_Handler
{
public:
    virtual void HandleInterrupt(TIMER_Channel* ch)
    {

    }
};

static void test_input_capture() 
{
    GPIOA::GetInstance()->EnablePeripheralClock(true);
    GPIOA::GetInstance()->SetupGPIO_OutAltPP(GPIO_PIN0); //pin10 PWM output
    
    GPIOA::GetInstance()->SetupGPIO_InFloat(GPIO_PIN6);  //pin16 input

    //TIM2 is used to generate the PWM signal  on pin10  (TIM2 channel 1)
    //pin10 has to be connected to pin16 (TIM3 channel 1) which is used to capture input

    TIM2* timer2 = TIM2::GetInstance();
    timer2->EnablePeripheralClock(true);
    TIMER_Channel* ch1 = timer2->GetChannel(1);
    uint32_t period_us = 10000;
    uint32_t duty_us =    4000;
    ch1->SetupPWM1(period_us, duty_us);
    ch1->EnableChannel(true);
    timer2->EnableCounter(true);

    TIM3* timer3 = TIM3::GetInstance();
    timer3->EnablePeripheralClock(true);
    TIMER_Channel* ch_in = timer3->GetChannel(1);  //TIM3 channe 1 : pin16 is used to capture input

    CCHandler handler;
    ch_in->EnableCCInterrupt(true, &handler);
    ch_in->SetModeInputDirect();
    ch_in->SetCCPolarityLow(true);
    ch_in->EnableChannel(true);
    
    timer3->EnableNVICInterrupt(true);
    timer3->EnableCounter(true);
    
    while(1);
}



int main()
{
    RCC* rcc = RCC::GetInstance();
    rcc->SetAHBPrescalerDiv4();
    rcc->SetAPB1PrescalerDiv1();
    rcc->SetAPB2PrescalerDiv1();
    rcc->SetADCPrescalerDiv2();
    rcc->EnableHSI(3);

    test_input_capture(); 
}
