#include "button_handler/button_handler.h"

#define LEFT_BUTTON 1 
#define RIGHT_BUTTON 2

class MyButtonHandler : public ButtonHandler 
{
private:
    GPIO_PIN* _ledPin1;
    GPIO_PIN* _ledPin2;

public:
    MyButtonHandler (TIMER* timer, GPIO_PIN* ledPin1, GPIO_PIN* ledPin2) : ButtonHandler (timer),
    _ledPin1 (ledPin1), 
    _ledPin2 (ledPin2) 
    {
        _ledPin1->SetupGPIO_OutPP();
        _ledPin2->SetupGPIO_OutPP();
    }

    virtual void OnStateChange(Button* button)
    {
//        ledPort->TogglePin (ledPin);
    }
    
    virtual void OnClick(Button* button)
    {
        if (button->GetId() == LEFT_BUTTON)
        {
            _ledPin1->Toggle ();
        }
        else
        {
             _ledPin2->Toggle ();
        }
    }
};

int main()
{
    RCC* rcc = RCC::GetInstance();
    rcc->SetAHBPrescalerDiv4();
    rcc->SetAPB1PrescalerDiv1();
    rcc->SetAPB2PrescalerDiv1();
    rcc->SetADCPrescalerDiv2();
    rcc->EnableHSI(3);
    
    GPIO_PORT* ledPort = GPIOB::GetInstance();
    ledPort->EnablePeripheralClock(true);

    GPIO_PORT* pinPort = GPIOB::GetInstance();
    pinPort->EnablePeripheralClock(true);
    
    
    GPIO_PIN*  ledPin1 = ledPort->GetPin(GPIO_PIN12);
    GPIO_PIN*  ledPin2 = ledPort->GetPin(GPIO_PIN15);
    
    TIMER* tim2 = TIM2::GetInstance();
    MyButtonHandler buttonHandler (tim2, ledPin1, ledPin2);


    GPIO_PIN*  inputPin1 = pinPort->GetPin(GPIO_PIN14);
    GPIO_PIN*  inputPin2 = pinPort->GetPin(GPIO_PIN13);

    Button b1 (inputPin1, LEFT_BUTTON);
    Button b2 (inputPin2, RIGHT_BUTTON);
   
    buttonHandler.AddButton (&b1);
    buttonHandler.AddButton (&b2);
    
    while(1) 
    {
    }
    
}
