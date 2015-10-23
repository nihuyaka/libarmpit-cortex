#ifndef _BUTTON_H
#define _BUTTON_H

#include "timer_cpp.h"
#include "gpio_cpp.h"

/* Default behavior is active low: button is configured as a weak pull-up
 * So to active it, the switch needs to be connected from the input port to ground
 * Then pushing the switch will set it low the IsOn method will return true
 *
 */
class Button
{

friend class ButtonHandler;

private:

    GPIO_PIN* _pin;


    bool _activeHigh;
    bool _currentState;
    bool _lastReadValue;

    uint8_t n_same_read;

    uint8_t _buttonId;


    void Init();


public:
    Button(GPIO_PIN* pin, uint8_t buttonId);

    //Activate the internal pull down resistor, so if the switch is open, the state will be low
    //So the switch needs to be connected to VDD
    void SetLow();

    //Activate the internal pull up resistor, so if the switch is open, the state will be high
    //So the switch needs to be connected to ground
    //This is the default
    void SetHigh();

    bool IsOn();

    GPIO_PIN* GetPin() const { return _pin; }

    bool IsPinSet();

    uint8_t GetId() { return _buttonId; }

};

#endif
