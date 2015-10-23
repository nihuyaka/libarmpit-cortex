#include "chopper_esc.h"

void Chopper_ESC::Init()
{

    _ch1 = _timer->GetChannel(1);
    _ch1->SetupPWM1(PWM_PERIOD_MS, 0);
    _ch1->EnableChannel(true);

    _ch2 = _timer->GetChannel(2);
    _ch2->SetupPWM1(PWM_PERIOD_MS, 0);
    _ch2->EnableChannel(true);

    _ch3 = _timer->GetChannel(3);
    _ch3->SetupPWM1(PWM_PERIOD_MS, 0);
    _ch3->EnableChannel(true);

    _ch4 = _timer->GetChannel(4);
    _ch4->SetupPWM1(PWM_PERIOD_MS, 0);
    _ch4->EnableChannel(true);

    _timer->EnableCounter(true);

    _isArmed = false;

    _currentDuty_m1 = 0;
    _currentDuty_m2 = 0;
    _currentDuty_m3 = 0;
    _currentDuty_m4 = 0;

}


void Chopper_ESC::InitESC()
{

//    //programming:
//    _ch4->SetupPWM1(PWM_PERIOD_MS, 2000);
//    //wait 5 sec for the tone
//
//    //now 8 tones in a loop
//
//    //when you hear the right one, goto 700 within 3 sec: start programming mode
//    _ch4->SetupPWM1(PWM_PERIOD_MS, 700);
//
//
//    //save the setting
//    _ch4->SetupPWM1(PWM_PERIOD_MS, 2000);
//
//
//    //withing 2 sec: leave programming mode
//    _ch4->SetupPWM1(PWM_PERIOD_MS, 700);

//    while(1)
//    	;


	//calibration: 2000 to min
   //_ch2->SetupPWM1(PWM_PERIOD_MS, 2000);
  //  _leds->RGB_BlinkingGreen(100, 50, 1500);
  //_ch2->SetupPWM1(PWM_PERIOD_MS, 700);

 //   _leds->RGB_BlinkingGreen(100, 50, 3000);
//    _ch1->SetupPWM1(PWM_PERIOD_MS, 1200);
//    _ch1->SetupPWM1(PWM_PERIOD_MS, 1000);


    _ch1->SetupPWM1(PWM_PERIOD_MS, 700);
    _ch2->SetupPWM1(PWM_PERIOD_MS, 700);
    _ch3->SetupPWM1(PWM_PERIOD_MS, 700);
    _ch4->SetupPWM1(PWM_PERIOD_MS, 700);

    _leds->RGB_BlinkingBlue(100, 50, 2000);

    _ch1->SetupPWM1(PWM_PERIOD_MS, 1000);
    _ch2->SetupPWM1(PWM_PERIOD_MS, 1000);
    _ch3->SetupPWM1(PWM_PERIOD_MS, 1000);
    _ch4->SetupPWM1(PWM_PERIOD_MS, 1000);

    _currentDuty_m1 = 1000;
    _currentDuty_m2 = 1000;
    _currentDuty_m3 = 1000;
    _currentDuty_m4 = 1000;




}

void Chopper_ESC::SetDuty(uint32_t duty_ms)
{
	SetDuty(duty_ms, duty_ms, duty_ms, duty_ms);
}

void Chopper_ESC::SetDuty(uint32_t m1_duty_ms, uint32_t m2_duty_ms, uint32_t m3_duty_ms, uint32_t m4_duty_ms)
{
    _ch1->SetupPWM1(PWM_PERIOD_MS, m1_duty_ms);
    _ch2->SetupPWM1(PWM_PERIOD_MS, m2_duty_ms);
    _ch3->SetupPWM1(PWM_PERIOD_MS, m3_duty_ms);
    _ch4->SetupPWM1(PWM_PERIOD_MS, m4_duty_ms);

    _currentDuty_m1 = m1_duty_ms;
    _currentDuty_m2 = m2_duty_ms;
    _currentDuty_m3 = m3_duty_ms;
    _currentDuty_m4 = m4_duty_ms;

}


void Chopper_ESC::AdjustCurrentDuty(float m1OffsetDuty, float m2OffsetDuty, float m3OffsetDuty, float m4OffsetDuty)
{
	if (IsArmed())
	{
		_ch1->SetupPWM1(PWM_PERIOD_MS, _currentDuty_m1 + m1OffsetDuty);
		_ch2->SetupPWM1(PWM_PERIOD_MS, _currentDuty_m2 + m2OffsetDuty);
		_ch3->SetupPWM1(PWM_PERIOD_MS, _currentDuty_m3 + m3OffsetDuty);
		_ch4->SetupPWM1(PWM_PERIOD_MS, _currentDuty_m4 + m4OffsetDuty);
	}
}


void Chopper_ESC::SpeedUp()
{
	if (_currentDuty_m1 < 2000 && _currentDuty_m2 < 2000 && _currentDuty_m3 < 2000 && _currentDuty_m4 < 2000)
	{
		SetDuty(_currentDuty_m1 + 100, _currentDuty_m2 + 100, _currentDuty_m3 + 100, _currentDuty_m4 + 100);
	}
}

void Chopper_ESC::SlowDown()
{
	if (_currentDuty_m1 > 700 && _currentDuty_m2 > 700 && _currentDuty_m3 > 700 && _currentDuty_m4 > 700)
	{
		SetDuty(_currentDuty_m1 - 100, _currentDuty_m2 - 100, _currentDuty_m3 - 100, _currentDuty_m4 - 100);
	}
}


void Chopper_ESC::TurnOn()
{
	InitESC();
	SetDuty(1200);
	//SetDuty(2000,2000,1000,1000);

    _isArmed = true;
    _leds->MotorLedOn();

}

void Chopper_ESC::TurnOff()
{
	SetDuty(700);
	_isArmed = false;
    _leds->MotorLedOff();
}

