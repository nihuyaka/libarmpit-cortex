#include "MPU_timer_runner.h"
#include <stdlib.h>
#include "LED_Indicators.h"

MPU_Timer_Runner::MPU_Timer_Runner(I2C* i2c, Chopper_ESC* esc) :
		_motionApp(i2c)
{
	_running = false;

#ifdef USE_USART
	uint32_t clockSpeed = 1200000;
	usart = GPIO_Helper::SetupUSART2_PA_2_3(clockSpeed);
#endif

	_esc = esc;
	_pidRoll.SetSampleTime(SAMPLE_INTERVAL);
	_pidYaw.SetSampleTime(SAMPLE_INTERVAL);
	_pidPitch.SetSampleTime(SAMPLE_INTERVAL);

	_pidRoll.Setpoint = 0.0;  //balance to this angle
	_pidYaw.Setpoint = 0.0;
	_pidPitch.Setpoint = 0.0;

	// aggressive roll and pitch ks, conservative yaw
	_pidRoll.SetTunings(7, 0.5, 2.8);
	_pidPitch.SetTunings(7, 0.5, 2.8);
	_pidYaw.SetTunings(1, 0.01, 0.00);

	_pidRoll.SetMode(AUTOMATIC);
	_pidRoll.SetControllerDirection(DIRECT);
	_pidYaw.SetMode(AUTOMATIC);
	_pidYaw.SetControllerDirection(DIRECT);
	_pidPitch.SetMode(AUTOMATIC);
	_pidPitch.SetControllerDirection(DIRECT);

	_pidRoll.SetOutputLimits(-200, +200);
	_pidYaw.SetOutputLimits(-1, +1);
	_pidPitch.SetOutputLimits(-200, +200);

}

void MPU_Timer_Runner::Start()
{
	_motionApp.Init();
	_running = true;

}

void MPU_Timer_Runner::Stop()
{
	_running = false;
}

void MPU_Timer_Runner::Run()
{
	LED_Indicators* progress = LED_Indicators::GetInstance();
	float y, p, r;
	//float p0 = 0., r0 = 0.;
	volatile int count = 0;

	progress->EnablePitchRollLeds(true);
	progress->EnableThrottleLevelLeds(true);

	unsigned long sampleIntervall = 0;

	float throttle = 1500.0;

	for (int i = 0; i < 30000; i++)
	{
		if (_running)
		{
			if (_motionApp.GetYPR(&y, &p, &r))
			{
				// balance
				_pidRoll.Input = r;
				_pidRoll.Compute(sampleIntervall);

				_pidYaw.Input = y;
				_pidYaw.Compute(sampleIntervall);

				_pidPitch.Input = p;
				_pidPitch.Compute(sampleIntervall);

				sampleIntervall += 20;
				_pidYaw.Output = 0;

				float r_balance = _pidRoll.Output;
				float p_balance = _pidPitch.Output;

				if (r_balance>1999.0) r_balance = 1999.0;
				if (p_balance>1999.0) p_balance = 1999.0;

				float m1 = (throttle + r_balance + p_balance - _pidYaw.Output);
				float m2 = (throttle - r_balance + p_balance + _pidYaw.Output);
				float m3 = (throttle - r_balance - p_balance - _pidYaw.Output);
				float m4 = (throttle + r_balance - p_balance + _pidYaw.Output);

				_esc->SetDuty(m1, m2, m3, m4);

				if (i > 3000)
				{
					throttle = 1875;
					progress->MotorLedOff();

				}



#ifdef USE_USART
				if (usart->IsRXNE())
				{
					if (usart->Receive() == 23)
					{
						usart->SendWord((int16_t) y);
						usart->SendWord((int16_t) p_balance);
						usart->SendWord((int16_t) r_balance);
						usart->SendWord((int16_t) m1);
						usart->SendWord((int16_t) m2);
						usart->SendWord((int16_t) m3);
						usart->SendWord((int16_t) m4);
					}
				}

#endif

				++count;

//				if ((int) p0 != 0 && (int) r0 != 0 && (abs(p - p0) > 10 || abs(r - r0) > 10))
//				{
//					volatile int iii = 0; //bp plasceholder
//					++iii;
//					progress->RGB_BlinkingRed(100, 50, 100);
//					progress->RGB_Off();
//				}

		//		p0 = p_balance;
		//		r0 = r_balance;

				progress->RGB_BlinkAll();
				progress->DisplayPitchRoll((int8_t)p, (int8_t)r);
				progress->DisplayThrottleLevel(m1, m2, m3, m4);
			}
		}
	}

	progress->RGB_Off();
	progress->EnablePitchRollLeds(false);
	progress->EnableThrottleLevelLeds(false);

}
