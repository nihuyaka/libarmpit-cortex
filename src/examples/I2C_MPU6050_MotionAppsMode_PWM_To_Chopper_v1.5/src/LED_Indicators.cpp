#include "LED_Indicators.h"
#include "GPIO_Helper.h"
#include <stdlib.h>
#define PITCH_ROLL_PERIOD 1000
#define THROTTLE_LED_PERIOD 2000

LED_Indicators::LED_Indicators()
{
	GPIOC::GetInstance()->EnablePeripheralClock(true);
	GPIOA::GetInstance()->EnablePeripheralClock(true);
	_rgb[0] = GPIOC::GetInstance()->GetPin(GPIO_PIN10);
	_rgb[0]->SetupGPIO_OutPP();
	_rgb[1] = GPIOA::GetInstance()->GetPin(GPIO_PIN15);
	_rgb[1]->SetupGPIO_OutPP();
	_rgb[2] = GPIOA::GetInstance()->GetPin(GPIO_PIN12);
	_rgb[2]->SetupGPIO_OutPP();
	RGB_Off();



	GPIOE::GetInstance()->EnablePeripheralClock(true);
	_greenMotorLed = GPIOE::GetInstance()->GetPin(GPIO_PIN2);
	_greenMotorLed->SetupGPIO_OutPP();
	_greenMotorLed->Reset();

	TIMER_With_Channels* t = GPIO_Helper::SetupTIM3_PC_6_7_8_9();
	_pitchRollCh = t->GetChannels();

	t = GPIO_Helper::SetupTIM1_PA_8_9_10_11();
	_throttleLedCh = t->GetChannels();

}

void LED_Indicators::RGB_BlinkAll()
{
	if (!(_delay++ % 5))
	{
		uint8_t active = _cnt++ % 3;

		for (uint8_t i = 0; i < 3; ++i)
		{
			if (i == active)
			{
				_rgb[i]->Reset();
			}
			else
			{
				_rgb[i]->Set();
			}
		}
	}
}

void LED_Indicators::SteadyOn(uint32_t idx, uint32_t duration_ms)
{
	RGB_Off();
	_rgb[idx]->Reset();
	RCC_Delay_ms(duration_ms);

}
void LED_Indicators::BlinkingOn(uint32_t idx, uint32_t period_ms, uint32_t duty_ms, uint32_t duration_ms)
{
	RGB_Off();
	uint32_t count = duration_ms / period_ms;
	for (uint32_t i = 0; i < count; ++i)
	{
		_rgb[idx]->Reset();
		RCC_Delay_ms(duty_ms);
		RGB_Off();
		RCC_Delay_ms(period_ms - duty_ms);
	}
}


void LED_Indicators::RGB_SteadyRed(uint32_t duration_ms)
{
	SteadyOn(1, duration_ms);
}
void LED_Indicators::RGB_BlinkingRed(uint32_t period_ms, uint32_t duty_ms, uint32_t duration_ms)
{
	BlinkingOn(1, period_ms, duty_ms, duration_ms);
}

void LED_Indicators::RGB_SteadyGreen(uint32_t duration_ms)
{
	SteadyOn(2, duration_ms);
}
void LED_Indicators::RGB_BlinkingGreen(uint32_t period_ms, uint32_t duty_ms, uint32_t duration_ms)
{
	BlinkingOn(2, period_ms, duty_ms, duration_ms);
}

void LED_Indicators::RGB_SteadyBlue(uint32_t duration_ms)
{
	SteadyOn(0, duration_ms);
}
void LED_Indicators::RGB_BlinkingBlue(uint32_t period_ms, uint32_t duty_ms, uint32_t duration_ms)

{
	BlinkingOn(0, period_ms, duty_ms, duration_ms);
}

void LED_Indicators::RGB_Off()
{
	_rgb[0]->Set();
	_rgb[1]->Set();
	_rgb[2]->Set();
}


void LED_Indicators::MotorLedOn()
{
	_greenMotorLed->Set();
}
void LED_Indicators::MotorLedOff()
{
	_greenMotorLed->Reset();
}

void LED_Indicators::EnablePitchRollLeds(bool enable)
{
	for (int i = 0; i < 4; ++i)
	{
		_pitchRollCh[i].EnableChannel(enable);
		if (enable)
		{
			_pitchRollCh[i].SetupPWM1(PITCH_ROLL_PERIOD, 0);
		}
	}
	_pitchRollCh[0].GetTimer()->EnableCounter(enable);
}

void LED_Indicators::EnableThrottleLevelLeds(bool enable)
{
	for (int i = 0; i < 4; ++i)
	{
		_throttleLedCh[i].EnableChannel(enable);
		if (enable)
		{
			_throttleLedCh[i].SetupPWM1(THROTTLE_LED_PERIOD, 0);
		}
	}
	_throttleLedCh[0].GetTimer()->EnableCounter(enable);
}



void LED_Indicators::DisplayPitchRoll (int8_t p, int8_t r)
{
	static uint8_t k = 5;
	if (abs(p) > 45)
	{
		p = p > 0 ? 45 : -45;
	}

	if (abs(r) > 45)
	{
		r = r > 0 ? 45 : -45;
	}

	if (p >= 0)
	{
		_pitchRollCh[2].SetupPWM1(PITCH_ROLL_PERIOD, p*k);
		_pitchRollCh[0].SetupPWM1(PITCH_ROLL_PERIOD, 0);
	}
	else
	{
		_pitchRollCh[2].SetupPWM1(PITCH_ROLL_PERIOD, 0);
		_pitchRollCh[0].SetupPWM1(PITCH_ROLL_PERIOD, -p*k);
	}
	if (r >= 0)
	{
		_pitchRollCh[1].SetupPWM1(PITCH_ROLL_PERIOD, r*k);
		_pitchRollCh[3].SetupPWM1(PITCH_ROLL_PERIOD, 0);
	}
	else
	{
		_pitchRollCh[1].SetupPWM1(PITCH_ROLL_PERIOD, 0);
		_pitchRollCh[3].SetupPWM1(PITCH_ROLL_PERIOD, -r*k);
	}

}

void LED_Indicators::DisplayThrottleLevel (int8_t m1, int8_t m2, int8_t m3, int8_t m4)
{
	_throttleLedCh[0].SetupPWM1(THROTTLE_LED_PERIOD, m1);
	_throttleLedCh[1].SetupPWM1(THROTTLE_LED_PERIOD, m2);
	_throttleLedCh[2].SetupPWM1(THROTTLE_LED_PERIOD, m3);
	_throttleLedCh[3].SetupPWM1(THROTTLE_LED_PERIOD, m4);

}

