#ifndef _BUTTON_HANDLER_H
#define _BUTTON_HANDLER_H

#include "timer_cpp.h"
#include "gpio_cpp.h"
#include "button.h"

/* Default behavior is active low: button is configured as a weak pull-up
 * So to active it, the switch needs to be connected from the input port to ground
 * Then pushing the switch will set it low the IsOn method will return true
 *
 */
class ButtonHandler : protected TIMER_Interrupt_Handler
{
private:
    const static uint32_t DEFAULT_TIMER_UPDATE_INTERVAL_US = 1000;
    const static uint32_t  DEFAULT_SETTLE_TIME_US = DEFAULT_TIMER_UPDATE_INTERVAL_US * 2;

    uint32_t timer_update_interval_us;
    uint32_t settle_time_us;
    uint32_t n_retries;
    const static uint8_t MAX_BUTTONS = 32;

    TIMER* _timer;


    Button*  _buttons[MAX_BUTTONS];
    uint8_t  _totalButtons;

    void Init();

    bool get_state_once(Button* b);
    virtual void HandleInterrupt(bool isUpdate, bool isTrigger);

public:

    ButtonHandler(TIMER* timer);

    void AddButton(Button* button);


    void SetUpdateIntervalUs (uint32_t us);
    void SetSettleTimeUs (uint32_t us);

    virtual void OnStateChange(Button* button){}
    virtual void OnClick(Button* button) {}


};

#endif
