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

class ADC_WatchdogHandler: public ADC_IRQ_Handler
{
public:

    //if input voltage is is below 1V, turn on the LED briefly
    virtual void Handle(ADC* adc)
    {
        static volatile uint32_t d;
        d = adc->GetData();
        GPIOB::GetInstance()->SetPin(GPIO_PIN12);
        RCC::GetInstance()->Delay_ms(500);
        GPIOB::GetInstance()->ResetPin(GPIO_PIN12);
    }
};

static void Test_Watchdog()
{
    
    GPIOB* gpioB = GPIOB::GetInstance();
    gpioB->EnablePeripheralClock(true);
    //LED on pin25
    gpioB->SetupGPIO_OutPP(GPIO_PIN12);
    
    GPIOA* gpioA = GPIOA::GetInstance();
    gpioA->SetupGPIO_InAnalog(GPIO_PIN3);
    
    ADC1* adc = ADC1::GetInstance();
    adc->Enable(true);
    adc->AddConversion(ADC_IN3, ADC_SMP_239_5); //pin13
    ADC_WatchdogHandler wdh;

    float min_volt = 0.0;
    float max_volt = 1.0;
    adc->EnableWatchdog(min_volt, max_volt, &wdh, ADC_IN3);
    adc->EnableInterrupt(true);
    adc->StartConversion(true);
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


    Test_Watchdog();

}
