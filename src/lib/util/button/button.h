#ifndef _BUTTON_H
#define _BUTTON_H

#include "timer_cpp.h"
#include "gpio_cpp.h"

/* Default behavior is active low: button is configured as a weak pull-up
 * So to active it, the switch needs to be connected from the input port to ground
 * Then pushing the switch will set it low the IsOn method will return true
 *
 */
class Button : TIMER_Interrupt_Handler
{
private:
	const static uint32_t DEFAULT_TIMER_UPDATE_INTERVAL_US = 1000;
	const static uint32_t  DEFAULT_SETTLE_TIME_US = DEFAULT_TIMER_UPDATE_INTERVAL_US * 2;

	uint32_t timer_update_interval_us;
	uint32_t settle_time_us;
	uint32_t n_retries;

	TIMER* _timer;
    GPIO_PIN* _pin;

	uint8_t n_same_read;

	bool _activeHigh;
	bool _currentState;
	bool _lastReadValue;

    uint8_t _nStateChanges;


	void Init();

	bool get_state_once();

public:
	Button(TIMER* timer, GPIO_PIN* pin);

    virtual void HandleInterrupt(bool isUpdate, bool isTrigger);


    //Activate the internal pull down resistor, so if the switch is open, the state will be low
    //So the switch needs to be connected to VDD
    void SetLow();

    //Activate the internal pull up resistor, so if the switch is open, the state will be high
    //So the switch needs to be connected to ground
    //This is the default
    void SetHigh();

    void SetUpdateIntervalUs (uint32_t us);
    void SetSettleTimeUs (uint32_t us);

    bool IsOn();

    virtual void OnStateChange(){}
    virtual void OnClick() {}


};

#endif
