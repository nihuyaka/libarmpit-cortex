/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 igorS
 *  
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "timer_cpp.h"
#include "gpio_cpp.h"
#include "button_handler/button_handler.h"

#define HAND_OPEN 1 
#define HAND_CLOSE 2
#define ARM_UP 3 
#define ARM_DOWN 4
#define PIVOT_RIGHT 5 
#define PIVOT_LEFT 6

class MyButtonHandler: public ButtonHandler
{
private:
    
    int _handPos;
    TIM2* timer2;

    TIMER_Channel* hand;
    TIMER_Channel* arm;
    TIMER_Channel* pivot;

public:
    MyButtonHandler() :
            ButtonHandler(TIM3::GetInstance())
    {
        timer2 = TIM2::GetInstance();
        timer2->EnablePeripheralClock(true);
        GPIO_PORT* pwmPort = GPIOA::GetInstance();
        pwmPort->EnablePeripheralClock(true);
        pwmPort->SetupGPIO_OutAltPP(GPIO_PIN0);
        pwmPort->SetupGPIO_OutAltPP(GPIO_PIN1);
        pwmPort->SetupGPIO_OutAltPP(GPIO_PIN2);
        pwmPort->SetupGPIO_OutAltPP(GPIO_PIN3);
    
        hand = timer2->GetChannel(1);
        hand->EnableChannel(true);
        arm = timer2->GetChannel(2);
        arm->EnableChannel(true);
        pivot = timer2->GetChannel(3);
        pivot->EnableChannel(true);
        timer2->EnableCounter(true);
        MoveHome();
 
    }
    
    void MoveHome()
    {
        _handPos = 1500;
        hand->SetupPWM1(20000, _handPos);
        arm->SetupPWM1(20000, 1500);
        pivot->SetupPWM1(20000, 1500);
    }

    virtual void OnStateChange(Button* button)
    {
    }

    void openHand()
    {

        hand->SetupPWM1(20000, 1200);
        return;
        
        if(_handPos > 1200)
        {
             _handPos -= 50;
            hand->SetupPWM1(20000, _handPos);
        }
    }
    
    void closeHand()
    {
        hand->SetupPWM1(20000, 1800);
        return;
        
        if(_handPos < 1800)
        {
            _handPos += 50;
            hand->SetupPWM1(20000, _handPos);
        }
    }
    
    virtual void OnClick(Button* button)
    {
        if(button->GetId() == HAND_OPEN )
        {
            openHand();
        }
        if(button->GetId() == HAND_CLOSE)
        {
            closeHand();
        }
        
        
    }

    void Run()
    {
        while (1)
        {
        }
    }

};

static void main_loop()
{
    GPIO_PORT* pinPort = GPIOB::GetInstance();
    pinPort->EnablePeripheralClock(true);

    /////////////////////////////////////////////
    MyButtonHandler handler;
    
    GPIO_PIN* inputPin1 = pinPort->GetPin(GPIO_PIN14);
    GPIO_PIN* inputPin2 = pinPort->GetPin(GPIO_PIN12);
    Button b1(inputPin1, HAND_OPEN);
    Button b2(inputPin2, HAND_CLOSE);

    handler.AddButton(&b1);
    handler.AddButton(&b2);


//////////////////////////////////////////////////
    handler.Run();

}


static void init_clock()
{
    RCC* rcc = RCC::GetInstance();
    rcc->SetAHBPrescalerDiv4();
    rcc->SetAPB1PrescalerDiv1();
    rcc->SetAPB2PrescalerDiv1();
    rcc->SetADCPrescalerDiv2();
    rcc->EnableHSI(3);
}

int main()
{
    init_clock();

    main_loop();
    while (1)
        ;

}
