#include "button/button.h"

class MyButton : public Button 
{
private:
    GPIO_PIN* _ledPin;

public:
    MyButton(TIMER* timer, GPIO_PIN* inputPin, GPIO_PIN* ledPin) : Button (timer, inputPin), _ledPin (ledPin)
    {
        _ledPin->SetupGPIO_OutPP();
        _ledPin->Set();
    }
  
    //Uncomment TogglePin either in OnClick or OnStateChange
    virtual void OnClick() 
    {
        _ledPin->Toggle();
    }
    
    virtual void OnStateChange() 
    {
//        _ledPin.Toggle();
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
    

    GPIO_PORT* portB = GPIOB::GetInstance(); 

    GPIO_PIN*  inputPin1 = portB->GetPin(GPIO_PIN14);
    GPIO_PIN*  ledPin =  portB->GetPin(GPIO_PIN12);
    
    
    MyButton button (TIM2::GetInstance(), inputPin1, ledPin);
    //button.SetLow();
    
    //button.SetSettleTimeUs (20000);
    //MyButton button2 (TIM2::GetInstance(), GPIOB::GetInstance(), inputPin2, ledPin);

    
    while(1) 
    {
    }
    
}
