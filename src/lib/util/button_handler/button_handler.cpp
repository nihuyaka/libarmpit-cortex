#include "button_handler.h"


ButtonHandler::ButtonHandler(TIMER* timer)
{
    _timer = timer;

    Init();


}

void ButtonHandler::Init()
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
    _totalButtons = 0;

}



void ButtonHandler::SetUpdateIntervalUs (uint32_t us)
{
    timer_update_interval_us = us;
    n_retries = settle_time_us / timer_update_interval_us;
    _timer->SetUpdatePeriod_us(timer_update_interval_us);
}

void ButtonHandler::SetSettleTimeUs (uint32_t us)
{
    settle_time_us = us;
    n_retries = settle_time_us / timer_update_interval_us;
}



void ButtonHandler::AddButton(Button* button)
{
   if (_totalButtons < MAX_BUTTONS) 
   {
        _buttons[_totalButtons++] = button;
   }
}



void ButtonHandler::HandleInterrupt(bool isUpdate, bool isTrigger)
{
	for (int i = 0; i < _totalButtons; ++i)
	{

		if (get_state_once(_buttons[i]))
		{
			OnStateChange(_buttons[i]);
			if (!_buttons[i]->IsOn())
			{
				OnClick(_buttons[i]);
			}
		}
	}


}



//Debouncing logic
//Returns true on state change (button is stable low or high)
bool ButtonHandler::get_state_once(Button* b)
{
    bool currentValue = b->IsPinSet();
    bool stateChanged = false;
    
    if (currentValue != b->_currentState)
    {
        if (currentValue == b->_lastReadValue)
        {
            ++b->n_same_read;
            if (b->n_same_read  == n_retries)
            {
                b->_currentState = !b->_currentState; //flip the state
                b->n_same_read = 0;
                stateChanged = true;
 //               ++_nStateChanges;  //debugging only
            }
        }
        else
        {
            b->n_same_read = 0;
        }
        b->_lastReadValue = currentValue;
    }

    return stateChanged;
}
