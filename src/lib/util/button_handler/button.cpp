#include "button.h"


Button::Button(GPIO_PIN* pin, uint8_t buttonId) : _pin(pin)
{
    _buttonId = buttonId;

    Init();

}

void Button::Init()
{
    _pin->SetupGPIO_InPullUp();
    //initial set high
    n_same_read = 0;
    SetHigh();
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


bool Button::IsPinSet()
{
	return _pin->IsSet();
}

bool Button::IsOn()
{
    return (_currentState == _activeHigh);
}

