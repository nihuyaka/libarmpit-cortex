#ifndef _PROGRESS_BLINKER_H
#define _PROGRESS_BLINKER_H

#include "gpio_cpp.h"
#include "timer_cpp.h"

class LED_Indicators
{
private:
	GPIO_PIN* _rgb[3];
	GPIO_PIN* _greenMotorLed;
	uint32_t  _cnt = 0;
	uint32_t  _delay = 0;

	TIMER_Channel* _pitchRollCh;
	TIMER_Channel* _throttleLedCh;

	void SteadyOn(uint32_t idx, uint32_t duration_ms);
	void BlinkingOn(uint32_t idx, uint32_t period_ms, uint32_t duty_ms, uint32_t duration_ms);

    LED_Indicators(LED_Indicators const&);
	LED_Indicators();
    void operator=(LED_Indicators const&);


public:

	static LED_Indicators* GetInstance()
	{
		static LED_Indicators  instance;
		return &instance;
	}

	void RGB_BlinkAll();

	void RGB_SteadyRed(uint32_t duration_ms);
	void RGB_BlinkingRed(uint32_t period_ms, uint32_t duty_ms, uint32_t duration_ms);
	void RGB_SteadyGreen(uint32_t duration_ms);
	void RGB_BlinkingGreen(uint32_t period_ms, uint32_t duty_ms, uint32_t duration_ms);
	void RGB_SteadyBlue(uint32_t duration_ms);
	void RGB_BlinkingBlue(uint32_t period_ms, uint32_t duty_ms, uint32_t duration_ms);

	void RGB_Off();

    void MotorLedOn();
    void MotorLedOff();

    void EnablePitchRollLeds(bool enable);
    void EnableThrottleLevelLeds(bool enable);

    void DisplayPitchRoll (int8_t p, int8_t r);
    void DisplayThrottleLevel (int8_t m1, int8_t m2, int8_t m3, int8_t m4);

};

#endif
