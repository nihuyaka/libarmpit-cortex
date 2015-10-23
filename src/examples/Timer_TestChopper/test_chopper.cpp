#include "timer_cpp.h"
#include "gpio_cpp.h"
#include "button_handler/button_handler.h"

#define HAND_OPEN 1 
#define HAND_CLOSE 2
#define ARM_UP 3 
#define ARM_DOWN 4
#define PIVOT_CW 5 
#define PIVOT_CCW 6

class MotorControl : public ButtonHandler
{
private:

    TIM2* timer2;
    TIMER_Channel* m1;
    TIMER_Channel* m2;
    TIMER_Channel* m3;
    TIMER_Channel* m4;
    uint32_t _period_us;
    uint32_t _duty_us;

public:
    MotorControl() : ButtonHandler (TIM3::GetInstance())

    {
        timer2 = TIM2::GetInstance();
        timer2->EnablePeripheralClock(true);
        GPIO_PORT* pwmPort = GPIOA::GetInstance();
        pwmPort->EnablePeripheralClock(true);
        pwmPort->SetupGPIO_OutAltPP(GPIO_PIN0);
        pwmPort->SetupGPIO_OutAltPP(GPIO_PIN1);
        pwmPort->SetupGPIO_OutAltPP(GPIO_PIN2);
        pwmPort->SetupGPIO_OutAltPP(GPIO_PIN3);

        m1 = timer2->GetChannel(1);
        m1->EnableChannel(true);
        m2 = timer2->GetChannel(2);
        m2->EnableChannel(true);
        m3 = timer2->GetChannel(3);
        m3->EnableChannel(true);
        m4 = timer2->GetChannel(4);
        m4->EnableChannel(true);
        timer2->EnableCounter(true);

        _period_us = 20000;
        _duty_us = 0;
        m1->SetupPWM1(_period_us, 4000);
        m2->SetupPWM1(_period_us, 4000);
        m3->SetupPWM1(_period_us, 4000);
        m4->SetupPWM1(_period_us, 4000);
        
        
    }
    
     virtual void OnClick(Button* button) 
     {
            _duty_us += 200;
            m1->UpdatePWMDuty(_duty_us);
            m2->UpdatePWMDuty(_duty_us);
            m3->UpdatePWMDuty(_duty_us);
            m4->UpdatePWMDuty(_duty_us);
    }
   

    void StateLoop()
    {
        
        GPIO_PORT* pinPort = GPIOB::GetInstance();
        pinPort->EnablePeripheralClock(true);

        Button h1(pinPort->GetPin(GPIO_PIN14), 1);
        Button h2(pinPort->GetPin(GPIO_PIN12), 2);

        AddButton(&h1);
        while (1)
        {
        }
    }


};

static void init_clock()
{
    RCC_SetAHBPrescalerDiv4();
    RCC_SetAPB1PrescalerDiv1();
    RCC_SetAPB2PrescalerDiv1();
    RCC_SetADCPrescalerDiv2();
    RCC_EnableHSI(3);
}

int main()
{
    init_clock();

    MotorControl mc;

    mc.StateLoop();

    while (1)
        ;

}
