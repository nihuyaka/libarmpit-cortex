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
#include "RCC_Helper.h"


static void TestSingleConversion() 
{
#if defined(STM32F1)
	RCC_EnableHSI_72Mhz_AHB_72Mhz_APB1_36MHz_APB2_72MHz();
#elif defined(STM32F4)
	RCC_EnableHSI_100Mhz();
    RCC_SetAPB2PrescalerDiv8();
#endif

    GPIOB* gpioB = GPIOB::GetInstance();
    gpioB->EnablePeripheralClock(true);
    //LED on pin25
    gpioB->SetupGPIO_OutPP(GPIO_PIN12);

    GPIOA* gpioA = GPIOA::GetInstance();
    gpioA->EnablePeripheralClock(true);
    gpioA->SetupGPIO_InAnalog(GPIO_PIN1);
    ADC1* adc1 = ADC1::GetInstance();
    adc1->Enable(true);
    adc1->SetPrescalerDIV8();
    adc1->AddConversion (ADC_IN1, ADC_SMP_FAST);
    volatile uint32_t res1;
    while (1) 
    {
        res1 = adc1->SingleConversion();
        if (res1 < 2000)
        {
            gpioB->SetPin(GPIO_PIN12);
        }
        else
        {
            gpioB->ResetPin(GPIO_PIN12);
        }
        RCC_Delay_us(100);
    }







}

int main()
{

    TestSingleConversion();

}
