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
#define PIVOT_CW 5 
#define PIVOT_CCW 6

class ServoControl
{
private:

    int _handPos;
    int _armPos;
    int _pivotPos;
    TIMER_With_Channels * pwmTimer;
    bool buttonOn;
    int step;
    int armAction;

    TIMER_Channel* hand;
    TIMER_Channel* arm;
    TIMER_Channel* pivot;

public:
    ServoControl()
    {

        buttonOn = false;
        pwmTimer = TIM3::GetInstance();
        pwmTimer->EnablePeripheralClock(true);

        GPIOA::GetInstance()->EnablePeripheralClock(true);
        GPIOB::GetInstance()->EnablePeripheralClock(true);

        GPIOA::GetInstance()->SetupGPIO_OutAltPP(GPIO_PIN6);
        GPIOA::GetInstance()->SetupGPIO_OutAltPP(GPIO_PIN7);
        GPIOB::GetInstance()->SetupGPIO_OutAltPP(GPIO_PIN0);
        GPIOB::GetInstance()->SetupGPIO_OutAltPP(GPIO_PIN1);

        hand = pwmTimer->GetChannel(1);
        hand->EnableChannel(true);
        arm = pwmTimer->GetChannel(2);
        arm->EnableChannel(true);
        pivot = pwmTimer->GetChannel(3);
        pivot->EnableChannel(true);
        pwmTimer->EnableCounter(true);
        MoveHome();
        step = 15;

    }

    void MoveHome()
    {
        _handPos = 1500;
        _armPos = 1500;
        _pivotPos = 1500;
        hand->SetupPWM1(20000, _handPos);
        arm->SetupPWM1(20000, 1500);
        pivot->SetupPWM1(20000, 1500);
    }

    void StateLoop()
    {
        ButtonHandler handler(TIM2::GetInstance());

        GPIO_PORT* pinPort = GPIOB::GetInstance();
        pinPort->EnablePeripheralClock(true);

        Button h1(pinPort->GetPin(GPIO_PIN14), HAND_OPEN);
        Button h2(pinPort->GetPin(GPIO_PIN15), HAND_CLOSE);
        
        Button a3(pinPort->GetPin(GPIO_PIN11), ARM_UP);
        Button a4(pinPort->GetPin(GPIO_PIN13), ARM_DOWN);
        
        Button p5(pinPort->GetPin(GPIO_PIN2), PIVOT_CW);
        Button p6(pinPort->GetPin(GPIO_PIN10), PIVOT_CCW);

        handler.AddButton(&h1);
        handler.AddButton(&h2);
        handler.AddButton(&a3);
        handler.AddButton(&a4);
        handler.AddButton(&p5);
        handler.AddButton(&p6);

        while (1)
        {

            if (h1.IsOn())
            {
                openHand();
            }
            else if (h2.IsOn())
            {
                closeHand();
            }
            
            if (a3.IsOn())
            {
                armUp();
            }
            else if (a4.IsOn())
            {
                armDown();
            }
            
            if (p5.IsOn())
            {
                pivotCw();
            }
            else if (p6.IsOn())
            {
                pivotCcw();
            }

            RCC_Delay_ms(10);
        }

    }

    void openHand()
    {

        if (_handPos > 1200)
        {
            _handPos -= step;
            hand->UpdatePWMDuty(_handPos);
        }
    }

    void closeHand()
    {
        if (_handPos < 1800)
        {
            _handPos += step;
            hand->UpdatePWMDuty(_handPos);
        }
    }
    
    void armUp()
    {

        if (_armPos > 1200)
        {
            _armPos -= step;
            arm->UpdatePWMDuty(_armPos);
        }
    }

    void armDown()
    {
        if (_armPos < 1800)
        {
            _armPos += step;
            arm->UpdatePWMDuty(_armPos);
        }
    }
    
    void pivotCw()
    {

        if (_pivotPos > 1000)
        {
            _pivotPos -= step;
            pivot->UpdatePWMDuty(_pivotPos);
        }
    }

    void pivotCcw()
    {
        if (_pivotPos < 2000)
        {
            _pivotPos += step;
            pivot->UpdatePWMDuty(_pivotPos);
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

    ServoControl sc;

    sc.StateLoop();

    while (1)
        ;

}
