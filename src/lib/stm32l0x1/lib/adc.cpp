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

#ifdef USE_ADC

#include "rcc_cpp.h"

#ifdef __cplusplus
extern "C"
{
#endif

#if defined (VALUE_LINE)
void ADC1_IRQHandler()
{
	if (ADC1_SR & ADC_SR_EOC)
	{
		if (ADC1_SR & ADC_SR_AWD)
		{
			ADC1::GetInstance()->HandleWatchdogInterrupt();
		}
		else
		{
			ADC1::GetInstance()->HandleInterrupt();
		}
	}
	else if (ADC1_SR & ADC_SR_JEOC)
	{
		if (ADC1_SR & ADC_SR_AWD)
		{
			ADC1::GetInstance()->HandleJWatchdogInterrupt();
		}
		else
		{
			ADC1::GetInstance()->HandleJInterrupt();
		}
	}
}
#else
void ADC1_2_IRQHandler()
{
	if (ADC1_SR & ADC_SR_EOC)
	{
		if (ADC1_SR & ADC_SR_AWD)
		{
			ADC1::GetInstance()->HandleWatchdogInterrupt();
		}
		else
		{
			ADC1::GetInstance()->HandleInterrupt();
		}
	}
	else if (ADC2_SR & ADC_SR_EOC)
	{
		if (ADC2_SR & ADC_SR_AWD)
		{
			ADC2::GetInstance()->HandleWatchdogInterrupt();
		}
		else
		{
			ADC2::GetInstance()->HandleInterrupt();
		}
	}
	else if (ADC1_SR & ADC_SR_JEOC)
	{
		if (ADC1_SR & ADC_SR_AWD)
		{
			ADC1::GetInstance()->HandleJWatchdogInterrupt();
		}
		else
		{
			ADC1::GetInstance()->HandleJInterrupt();
		}
	}
	else if (ADC2_SR & ADC_SR_JEOC)
	{
		if (ADC2_SR & ADC_SR_AWD)
		{
			ADC2::GetInstance()->HandleJWatchdogInterrupt();
		}
		else
		{
			ADC2::GetInstance()->HandleJInterrupt();
		}
	}

}

#if defined (STM32F10X_HD) || defined (STM32F10X_XL)
void ADC3_IRQHandler()
{
	if (ADC3_SR & ADC_SR_EOC)
	{
		if (ADC3_SR & ADC_SR_AWD)
		{
			ADC3::GetInstance()->HandleWatchdogInterrupt();
		}
		else
		{
			ADC3::GetInstance()->HandleInterrupt();
		}
	}
	else if (ADC3_SR & ADC_SR_JEOC)
	{
		if (ADC3_SR & ADC_SR_AWD)
		{
			ADC3::GetInstance()->HandleJWatchdogInterrupt();
		}
		else
		{
			ADC3::GetInstance()->HandleJInterrupt();
		}
	}
}

#endif

#endif

#ifdef __cplusplus
}
#endif

void ADC::HandleInterrupt()
{
	*_pADC_SR &= ~ADC_SR_EOC;
	*_pADC_SR &= ~ADC_SR_STRT;

	if (_interruptHandler)
	{
		_interruptHandler->Handle(this);
	}
}

void ADC::HandleJInterrupt()
{
	*_pADC_SR &= ~ADC_SR_JEOC;
	*_pADC_SR &= ~ADC_SR_JSTRT;

	if (_jInterruptHandler)
	{
		_jInterruptHandler->Handle(this);
	}
}

void ADC::HandleWatchdogInterrupt()
{
	*_pADC_SR &= ~ADC_SR_EOC;
	*_pADC_SR &= ~ADC_SR_STRT;
	*_pADC_SR &= ~ADC_SR_AWD;

	if (_watchdogHandler)
	{
		_watchdogHandler->Handle(this);
	}
}

void ADC::HandleJWatchdogInterrupt()
{
	*_pADC_SR &= ~ADC_SR_JEOC;
	*_pADC_SR &= ~ADC_SR_JSTRT;
	*_pADC_SR &= ~ADC_SR_AWD;

	if (_jWatchdogHandler)
	{
		_jWatchdogHandler->Handle(this);
	}
}

void ADC::Enable(bool enable)
{
	EnablePeripheralClock(enable);

	if (enable)
	{
		*_pADC_CR2 |= ADC_CR2_ADON;
		Calibrate();
		_initialized = true;
	}
	else
	{
		*_pADC_CR2 &= ~ADC_CR2_ADON;
		_initialized = false;
		_emptySequence = true;
		_emptyJSequence = true;

	}
}

void ADC::Calibrate()
{
	int i = 100;
	while (i--)
		;

	*_pADC_CR2 |= ADC_CR2_RSTCAL;
	while ((*_pADC_CR2 & ADC_CR2_RSTCAL) != 0)
		;

	*_pADC_CR2 |= ADC_CR2_CAL;

	while ((*_pADC_CR2 & ADC_CR2_CAL) != 0)
		;

}

void ADC::SetInterruptHandler(ADC_IRQ_Handler* interruptHandler)
{
	_interruptHandler = interruptHandler;
}

void ADC::SetJInterruptHandler(ADC_IRQ_Handler* interruptHandler)
{
	_jInterruptHandler = interruptHandler;
}

void ADC::StartConversion(bool continuous)
{
	if (continuous)
	{
		*_pADC_CR2 |= ADC_CR2_CONT;
	}

	*_pADC_CR2 |= ADC_CR2_ADON;  //ADON the second time starts the conversion

}

uint32_t ADC::SingleConversion()
{

	if (_initialized && !(*_pADC_CR1 & ADC_CR1_EOCIE))
	{
		*_pADC_CR2 |= ADC_CR2_ADON;  //ADON the second time starts the conversion

		//no interrupt, check EOC
		while ((*_pADC_SR & ADC_SR_EOC) == 0)
			;

		*_pADC_SR &= ~ADC_SR_EOC;  //not needed if DR is read

		return 0xffff & *_pADC_DR;
	}
	else
	{
		return 0;
	}
}

void ADC::SetChannelSampleTime(ADC_CHANNEL channel, ADC_SAMPLE_TIME sampleTime)
{

	int smpr_shift = (channel % 10) * 3;
	volatile uint32_t* pADC_SMPR;

	if (channel < 10)
	{
		pADC_SMPR = _pADC_SMPR2;
	}
	else
	{
		pADC_SMPR = _pADC_SMPR1;
	}

	*pADC_SMPR |= ((0x7 & sampleTime) << smpr_shift);

}

void ADC::AddConversion(ADC_CHANNEL channel, ADC_SAMPLE_TIME sampleTime)
{
	SetChannelSampleTime(channel, sampleTime);
	int current = 0xf & (*_pADC_SQR1 >> 20);

	if (current == 0xf)
	{
		return;
	}

	int seqno = 0xf & (current + 1);

	if (_emptySequence)
	{
		seqno = 0;
		_emptySequence = false;
	}

	*_pADC_SQR1 &= ~(0xf << 20);
	*_pADC_SQR1 |= (seqno << 20);

	volatile uint32_t* pADC_SQR;
	int sqr = 3 - seqno / 6;
	int sqr_shift = (seqno % 6) * 5;

	if (sqr == 3)
	{
		pADC_SQR = _pADC_SQR3;
	}
	else if (sqr == 2)
	{
		pADC_SQR = _pADC_SQR2;
	}
	else if (sqr == 1)
	{
		pADC_SQR = _pADC_SQR1;
	}
	else
	{
		//throw STM32F1_Exception ("Error setting ADC conversion sequence");
		pADC_SQR = 0;
	}

	if (pADC_SQR != 0)
	{
		*pADC_SQR |= ((0xff & channel) << sqr_shift);
	}

}

void ADC::AddJConversion(ADC_CHANNEL channel, ADC_SAMPLE_TIME sampleTime)
{
	SetChannelSampleTime(channel, sampleTime);

	int current = 0x3 & (*_pADC_JSQR >> 20);

	if (current == 3)
	{
		return;
	}

	int seqno = 0x3 & (current + 1);

	if (_emptyJSequence)
	{
		seqno = 0;
		_emptyJSequence = false;
	}

	*_pADC_JSQR &= ~(0x3 << 20);
	*_pADC_JSQR |= (seqno << 20);

	int sqr_shift = (3 - seqno) * 5;

	*_pADC_JSQR |= ((0xff & channel) << sqr_shift);

}

void ADC::EnableInterrupt(bool enable)
{
	_EnableInterrupt(ADC_CR1_EOCIE, enable);
}

void ADC::EnableJInterrupt(bool enable)
{
	_EnableInterrupt(ADC_CR1_JEOCIE, enable);
}

void ADC::_EnableInterrupt(uint16_t intMask, bool enable)
{
	if (enable)
	{
		*_pADC_CR1 |= intMask; //enable interrupt on EOC
		NVIC_SetEnable(_irqNo);
	}
	else
	{
		*_pADC_CR1 &= ~intMask; //clear interrupt on EOC
	}
}

void ADC::SetLeftAlignment()
{
	*_pADC_CR2 |= ADC_CR2_ALIGN;
}

void ADC::SetRightAlignment()
{
	*_pADC_CR2 &= ~ADC_CR2_ALIGN;
}

void ADC::SetScanMode()
{
	*_pADC_CR1 |= ADC_CR1_SCAN;
}

void ADC::SetAutoInjection(bool on)
{
	if (on)
	{
		*_pADC_CR1 |= ADC_CR1_JAUTO;
	}
	else
	{
		*_pADC_CR1 &= ~ADC_CR1_JAUTO;
	}
}

void ADC::EnableWatchdog(float minV, float maxV,
		ADC_IRQ_Handler* watchdogHandler, ADC_CHANNEL channel)
{
	_EnableWatchdog(minV, maxV, watchdogHandler, channel, false);
}

void ADC::EnableJWatchdog(float minV, float maxV,
		ADC_IRQ_Handler* watchdogHandler, ADC_CHANNEL channel)
{
	_EnableWatchdog(minV, maxV, watchdogHandler, channel, true);
}

void ADC::_EnableWatchdog(float minV, float maxV,
		ADC_IRQ_Handler* watchdogHandler, ADC_CHANNEL channel, bool injected)
{
	int32_t min = 4096. / 3.3 * minV;
	int32_t max = 4096. / 3.3 * maxV;

	if (min >= 0 && min <= 4096 && max >= 0 && max <= 4096 && min < max)
	{
		*_pADC_LTR = min;
		*_pADC_HTR = max;
		*_pADC_CR1 |= injected ? ADC_CR1_JAWDEN : ADC_CR1_AWDEN;
		if (watchdogHandler != 0)
		{
			*_pADC_CR1 |= ADC_CR1_AWDIE;
			if (injected)
			{
				SetJWatchdogHandler(watchdogHandler);
				//EnableJInterrupt();
			}
			else
			{
				SetWatchdogHandler(watchdogHandler);
				//EnableInterrupt();
			}
		}

		if (channel != ADC_ALL)
		{
			*_pADC_CR1 |= ADC_CR1_AWDSGL;
			*_pADC_CR1 |= (0x1f & channel);
		}

	}

}

void ADC::SetWatchdogHandler(ADC_IRQ_Handler* watchdogHandler)
{
	_watchdogHandler = watchdogHandler;
}

void ADC::SetJWatchdogHandler(ADC_IRQ_Handler* jWatchdogHandler)
{
	_jWatchdogHandler = jWatchdogHandler;
}

void ADC1::EnablePeripheralClock(bool enable)
{
	RCC::GetInstance()->EnableADC1(enable);
}

#if !defined (VALUE_LINE)

void ADC2::EnablePeripheralClock(bool enable)
{
	RCC::GetInstance()->EnableADC2(enable);
}

#if defined (STM32F10X_HD) || defined (STM32F10X_XL)

void ADC3::EnablePeripheralClock(bool enable)
{
	RCC::GetInstance()->EnableADC3(enable);
}

#endif

#endif

#endif
