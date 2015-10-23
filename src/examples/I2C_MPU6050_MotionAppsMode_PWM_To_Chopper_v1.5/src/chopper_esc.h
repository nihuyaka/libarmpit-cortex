#ifndef CHOPPER_ESC_H
#define CHOPPER_ESC_H

#include "timer_cpp.h"
#include "LED_Indicators.h"

class Chopper_ESC
{
private:
    TIMER_With_Channels* _timer;
    TIMER_Channel* _ch1; //PA0
    TIMER_Channel* _ch2; //PA1
    TIMER_Channel* _ch3; //PA2
    TIMER_Channel* _ch4; //PA3

    static const uint16_t PWM_PERIOD_MS = 20000;

    bool _isArmed;

    uint32_t _currentDuty_m1;
    uint32_t _currentDuty_m2;
    uint32_t _currentDuty_m3;
    uint32_t _currentDuty_m4;

    LED_Indicators* _leds;


public:
    Chopper_ESC(TIMER_With_Channels*  timer)
	{
    	_timer = timer;
    	_leds = LED_Indicators::GetInstance();
	}

    void Init();
    void InitESC();
    void SetDuty(uint32_t duty_ms);
    void SetDuty(uint32_t m1_duty_ms, uint32_t m2_duty_ms, uint32_t m3_duty_ms, uint32_t m4_duty_ms);
    void AdjustCurrentDuty(float m1OffsetDuty, float m2OffsetDuty, float m3OffsetDuty, float m4OffsetDuty);
    void SpeedUp();
    void SlowDown();
    void TurnOn();
    void TurnOff();
    bool IsArmed() { return _isArmed; }

    //bool SetIsArmed (bool isArmed) { _isArmed = isArmed; }

};


#endif
