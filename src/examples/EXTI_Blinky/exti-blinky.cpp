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



#include "exti.h"
#include "afio.h"
#include "gpio_cpp.h"
#include "timer_cpp.h"

static void generatePWM()
{
    GPIOA::GetInstance()->EnablePeripheralClock(true);
    GPIOA::GetInstance()->SetupGPIO_OutAltPP(GPIO_PIN0);
    TIM2* timer2 = TIM2::GetInstance();
    timer2->EnablePeripheralClock(true);
    TIMER_Channel* ch1 = timer2->GetChannel(1);
    ch1->SetupPWM1(1000000, 500000); //1 sec period, 50% duty
    ch1->EnableChannel(true);
    while (1)
        ;
}


class EXTI15_Handler2: public EXTI_IRQ_Handler
{
public:
    //toggles LED on pin25 every second
    void HandleInterrupt(EXTI* exti)
    {
        GPIOB::GetInstance()->TogglePin(GPIO_PIN12);
    }
};

static void exti_input_pwm_test()
{
    GPIOB::GetInstance()->EnablePeripheralClock(true);
    //LED on pin25
    GPIOB::GetInstance()->SetupGPIO_OutPP(GPIO_PIN12);

    //Output PWM signal with 1 sec period on pin10 
    //Connect pin10 to the EXTI input on pin28
    generatePWM();

    RCC::GetInstance()->EnableAFIO(true);
    
    //Remap LINE15 to PB15 : pin28
    AFIO_RemapEXTI(EXTI_LINE15, PORTB);

    
    EXTI15::GetInstance()->EnableInterruptRisingEdge(true);

    EXTI15_Handler2 handler;
    EXTI15::GetInstance()->SetIrqHandler(&handler);
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

    exti_input_pwm_test();
}
