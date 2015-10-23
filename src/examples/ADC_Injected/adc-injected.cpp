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


class ADC_IRQ_JHandler_Test: public ADC_IRQ_Handler
{
public:

    virtual void Handle(ADC* adc)
    {
        static GPIOB* gpioB = GPIOB::GetInstance();
        static volatile uint32_t d1;
        static volatile uint32_t d2;
        static volatile uint32_t d3;
        static volatile uint32_t d4;

        d1 = adc->GetJData1();
        d2 = adc->GetJData2();
        d3 = adc->GetJData3();
        d4 = adc->GetJData4();
        if (d1 < 2000)
        {
            gpioB->SetPin(GPIO_PIN12);
        }
        else
        {
            gpioB->ResetPin(GPIO_PIN12);
        }
        if (d2 < 2000)
        {
            gpioB->SetPin(GPIO_PIN13);
        }
        else
        {
            gpioB->ResetPin(GPIO_PIN13);
        }

        if (d3 < 2000)
        {
            gpioB->SetPin(GPIO_PIN14);
        }
        else
        {
            gpioB->ResetPin(GPIO_PIN14);
        }

        if (d4 < 2000)
        {
            gpioB->SetPin(GPIO_PIN15);
        }
        else
        {
            gpioB->ResetPin(GPIO_PIN15);
        }


    }
};


static void Test_Injected()
{
    GPIOB* gpioB = GPIOB::GetInstance();
    gpioB->EnablePeripheralClock(true);
    //LEDs on pins 25 26 27 28
    gpioB->SetupGPIO_OutPP(GPIO_PIN12);
    gpioB->SetupGPIO_OutPP(GPIO_PIN13);
    gpioB->SetupGPIO_OutPP(GPIO_PIN14);
    gpioB->SetupGPIO_OutPP(GPIO_PIN15);

    GPIOA* gpioA = GPIOA::GetInstance();
    gpioA->EnablePeripheralClock(true);

    gpioA->SetupGPIO_InAnalog(GPIO_PIN0);
    gpioA->SetupGPIO_InAnalog(GPIO_PIN1);
    gpioA->SetupGPIO_InAnalog(GPIO_PIN2);
    gpioA->SetupGPIO_InAnalog(GPIO_PIN3);

    ADC1* adc1 = ADC1::GetInstance();
    adc1->Enable(true);
    adc1->AddConversion  (ADC_IN0, ADC_SMP_28_5);  //pin10
    adc1->AddJConversion (ADC_IN1,  ADC_SMP_13_5); //pin11
    adc1->AddJConversion(ADC_IN2, ADC_SMP_13_5);   //pin12
    adc1->AddJConversion (ADC_IN3,  ADC_SMP_13_5); //pin13
    
    ADC_IRQ_JHandler_Test  handler;
    adc1->SetJInterruptHandler(&handler);
    
    adc1->EnableJInterrupt(true);
    adc1->SetAutoInjection(true);
    adc1->SetScanMode();
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

    Test_Injected();

}
