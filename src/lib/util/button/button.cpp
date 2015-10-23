#include "button.h"


Button::Button(TIMER* timer, GPIO_PIN* pin)
: _pin(pin)
{
	_timer = timer;

	Init();


}

void Button::Init()
{
	timer_update_interval_us = DEFAULT_TIMER_UPDATE_INTERVAL_US;
	settle_time_us = DEFAULT_SETTLE_TIME_US;
	n_retries = settle_time_us / timer_update_interval_us;

	_timer->EnablePeripheralClock(true);
	_timer->SetUpdatePeriod_us(timer_update_interval_us);
	_timer->EnableUpdateInterrupt(true);
    _timer->EnableNVICInterrupt(true);
	_timer->AddInterruptHandler(this);
	_timer->EnableCounter(true);

	_pin->GetPort()->EnablePeripheralClock(true);
	_pin->SetupGPIO_InPUPD();
	//initial set high
	SetHigh();
	n_same_read = 0;
    _nStateChanges = 0;
}

void Button::SetLow()
{
	_pin->Reset();
	_currentState = false;
	_activeHigh = true;
	_lastReadValue = _currentState;
}

void Button::SetHigh()
{
	_pin->Set();
	_currentState = true;
	_activeHigh = false;
	_lastReadValue = _currentState;
}


void Button::SetUpdateIntervalUs (uint32_t us)
{
	timer_update_interval_us = us;
	n_retries = settle_time_us / timer_update_interval_us;
	_timer->SetUpdatePeriod_us(timer_update_interval_us);
}

void Button::SetSettleTimeUs (uint32_t us)
{
	settle_time_us = us;
	n_retries = settle_time_us / timer_update_interval_us;
}



void Button::HandleInterrupt(bool isUpdate, bool isTrigger)
{
	if (get_state_once())
	{
		OnStateChange();
		if (!IsOn())
		{
			OnClick();
		}
	}


}

bool Button::IsOn()
{
	return (_currentState == _activeHigh);
}


//Debouncing logic
//Returns true on state change (button is stable low or high)
bool Button::get_state_once()
{
    bool currentValue = _pin->IsSet();
    bool stateChanged = false;
    
    if (currentValue != _currentState)
    {
        if (currentValue == _lastReadValue)
        {
            ++n_same_read;
            if (n_same_read  == n_retries)
            {
            	_currentState = !_currentState; //flip the state
                n_same_read = 0;
                stateChanged = true;
 //               ++_nStateChanges;  //debugging only
            }
        }
        else
        {
            n_same_read = 0;
        }
        _lastReadValue = currentValue;
    }

    return stateChanged;
}
