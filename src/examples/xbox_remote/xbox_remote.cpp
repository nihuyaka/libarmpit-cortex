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


#include "adc_cpp.h"
#include "gpio_cpp.h"
#include "timer_cpp.h"

class ADC1_IRQ_Handler: public ADC_IRQ_Handler
{
private:
    TIMER_Channel* ch1;

public:

    ADC1_IRQ_Handler()
    {
        GPIOA::GetInstance()->EnablePeripheralClock(true);
        GPIOA::GetInstance()->SetupGPIO_OutAltPP(GPIO_PIN6);
        TIM3* timer1 = TIM3::GetInstance();
        timer1->EnablePeripheralClock(true);
        ch1 = timer1->GetChannel(1);
        ch1->SetupPWM1(2000, 1000);
        ch1->EnableChannel(true);
        timer1->EnableCounter(true);
    }

    virtual void Handle(ADC* adc)
    {
        static volatile uint32_t d;
        static uint32_t div = 4096 / 128;
        static uint32_t last_d = 0;
        d = adc->GetData() / div;
        if (d != last_d)
        {
            ch1->SetupPWM1(3000, d * 90);
        }
        last_d = d;
   }
    
};


void main_loop()
{
    RCC::GetInstance()->Delay_ms(3000);
    GPIOA* gpioA = GPIOA::GetInstance();
    gpioA->EnablePeripheralClock(true);
    gpioA->SetupGPIO_InAnalog(GPIO_PIN0);
    
    ADC1* adc1 = ADC1::GetInstance();
    adc1->Enable(true);
    adc1->AddConversion(ADC_IN0, ADC_SMP_1_5); //PA0, pin 10
    adc1->EnableInterrupt(true);
    ADC1_IRQ_Handler adcHandler;
    adc1->SetInterruptHandler(&adcHandler);
    adc1->StartConversion(true);
    while (1)
        ;
}



int main()
{
    RCC* rcc = RCC::GetInstance();
    rcc->SetAHBPrescalerDiv4();
    rcc->SetAPB1PrescalerDiv1();
    rcc->SetAPB2PrescalerDiv1();
    rcc->SetADCPrescalerDiv2();
    rcc->EnableHSI(3);

    main_loop();

}
