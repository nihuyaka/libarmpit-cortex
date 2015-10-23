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

class ADC1_IRQ_Handler: public ADC_IRQ_Handler
{
private:
	GPIO_PIN* _pin;

public:

	ADC1_IRQ_Handler()
	{
		GPIOB* gpioB = GPIOB::GetInstance();
		gpioB->EnablePeripheralClock(true);
		_pin = gpioB->GetPin(GPIO_PIN12);
		_pin->SetupGPIO_OutPP();
	}

	virtual void Handle(ADC* adc)
	{
		static volatile uint32_t d;
		d = adc->GetData();
		if (d < 2000)
		{
			GPIOB::GetInstance()->SetPin(GPIO_PIN12);
		}
		else
		{
			GPIOB::GetInstance()->ResetPin(GPIO_PIN12);
		}
	}
};

void Test_Continuous_Conversion()
{
#if defined(STM32F1)
	//RCC_EnableHSI_72Mhz_AHB_72Mhz_APB1_36MHz_APB2_72MHz();
	RCC_EnableHSI_24Mhz();
#elif defined(STM32F4)
	RCC_EnableHSI_168Mhz();
	RCC_SetAPB2PrescalerDiv16();
	//RCC_EnableHSI(true);
#else
#error "Chip not defined"
#endif

	GPIOA* gpioA = GPIOA::GetInstance();
	gpioA->EnablePeripheralClock(true);
	gpioA->SetupGPIO_InAnalog(GPIO_PIN1);

	ADC1* adc1 = ADC1::GetInstance();
	adc1->Enable(true);
	adc1->AddConversion(ADC_IN1, ADC_SMP_SLOWEST);
	adc1->EnableInterrupt(true);
	ADC1_IRQ_Handler adcHandler;
	adc1->SetInterruptHandler(&adcHandler);
	adc1->StartContinuousConversion();

	while (1)
		;
}

int main()
{
	Test_Continuous_Conversion();
}
