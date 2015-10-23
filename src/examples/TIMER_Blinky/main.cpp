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
#include "rcc_helper.h"


volatile static uint32_t t1 = 0;
volatile static uint32_t t2 = 0;


class Update_Handler: public TIMER_Interrupt_Handler
{
public:

    //blink LED on pin25 every second  and count seconds
    virtual void HandleInterrupt(bool isUpdate, bool isTrigger)
    {
        //update flag is cleared automatically before entering the handler, 
        //so no need to clear any flags here
        if (isUpdate)
        {
            t1++;
            RCC_Delay_ms(2000);
            GPIOB::GetInstance()->TogglePin(GPIO_PIN12);
        }
    }
};

class Update_Handler2: public TIMER_Interrupt_Handler
{
public:

    //blink LED on pin25 every second  and count seconds
    virtual void HandleInterrupt(bool isUpdate, bool isTrigger)
    {
        //update flag is cleared automatically before entering the handler, 
        //so no need to clear any flags here
        if (isUpdate)
        {
            t2++;
            RCC_Delay_us(100);
            GPIOB::GetInstance()->TogglePin(GPIO_PIN12);
        }
    }
};


static void test_counter() 
{
    GPIOB::GetInstance()->EnablePeripheralClock(true);
    GPIOB::GetInstance()->SetupGPIO_OutPP(GPIO_PIN12);  //pin25

    Update_Handler handler;
    TIM2* t = TIM2::GetInstance();
    t->EnablePeripheralClock(true);
    t->EnableNVICInterrupt(true);     //enable global system interrupts (core)
    //NVIC_SetPriority (IRQn_TIM2, 15<<4);  //set lowest priority
    t->AddInterruptHandler(&handler);
    t->EnableUpdateInterrupt(true);   //enable timer update interrupt
    t->SetCounterValue(0);            //optional
    //t->SetUpdatePeriod_us(1000000);   //1 second 
    t->SetUpdatePeriod_us(1000);   //1 second 

    Update_Handler2 handler2;
    TIM3* t3 = TIM3::GetInstance();
    t3->EnablePeripheralClock(true);
    t3->EnableNVICInterrupt(true);     //enable global system interrupts (core)
    //NVIC_SetPriority (IRQn_TIM2, 15<<4);  //set lowest priority
    NVIC_SetPriority (IRQn_TIM3, 15<<4);  //set lowest priority
    t3->AddInterruptHandler(&handler2);
    t3->EnableUpdateInterrupt(true);   //enable timer update interrupt
    t3->SetCounterValue(0);            //optional
    //t->SetUpdatePeriod_us(1000000);   //1 second 
    t3->SetUpdatePeriod_us(1000);   //1 second 
    t3->EnableCounter(true);           //start counting
    t->EnableCounter(true);           //start counting

    while(1)
        ;

}

int main()
{
 
    RCC_EnableHSI_100Mhz();

    test_counter();
}
