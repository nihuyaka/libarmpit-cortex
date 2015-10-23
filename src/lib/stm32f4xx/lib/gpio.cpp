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


#include "gpio_cpp.h"

GPIO_PORT::GPIO_PORT(
        volatile uint32_t* pGPIO_MODER,
        volatile uint32_t* pGPIO_OTYPER,
        volatile uint32_t* pGPIO_OSPEEDR,
        volatile uint32_t* pGPIO_PUPDR,
        volatile uint32_t* pGPIO_IDR,
        volatile uint32_t* pGPIO_ODR,
        volatile uint32_t* pGPIO_BSRR,
        volatile uint32_t* pGPIO_LCKR,
        volatile uint32_t* pGPIO_AFRL,
        volatile uint32_t* pGPIO_AFRH,
        volatile uint32_t* pRCCEnableReg,
        volatile uint32_t* pRCCResetReg,
        uint32_t           rccBit) : Peripheral (pRCCEnableReg, pRCCResetReg, rccBit)
{
    _pGPIO_MODER = pGPIO_MODER;
    _pGPIO_OTYPER = pGPIO_OTYPER;
    _pGPIO_OSPEEDR = pGPIO_OSPEEDR;
    _pGPIO_PUPDR = pGPIO_PUPDR;
    _pGPIO_IDR = pGPIO_IDR;
    _pGPIO_ODR = pGPIO_ODR;
    _pGPIO_BSRR = pGPIO_BSRR;
    _pGPIO_LCKR = pGPIO_LCKR;
    _pGPIO_AFRL = pGPIO_AFRL;
    _pGPIO_AFRH = pGPIO_AFRH;

    for (int i = 0 ; i < 16; ++i)
    {
      _pins[i]._init (this, (GPIO_PIN_N) i);
    }
}



void GPIO_PORT::Lock (uint16_t bitMask)
{
    *_pGPIO_LCKR = (0xff & bitMask);
    *_pGPIO_LCKR |= GPIOG_LCKR_LCKK; 
    *_pGPIO_LCKR &= ~GPIOG_LCKR_LCKK; 
    *_pGPIO_LCKR |= GPIOG_LCKR_LCKK; 
    uint16_t tmp = *_pGPIO_LCKR;
    ++tmp;
}


void GPIO_PORT::SetupGPIO_InFloat (GPIO_PIN_N pin) 
{
    *_pGPIO_MODER &= ~(3<<pin*2);
    *_pGPIO_MODER |= GPIO_MODE_IN<<pin*2;
    *_pGPIO_PUPDR &= ~(3<<pin*2);
}


void GPIO_PORT::SetupGPIO_InPullUp (GPIO_PIN_N pin) 
{
    *_pGPIO_MODER &= ~(3<<pin*2);
    *_pGPIO_MODER |= GPIO_MODE_IN<<pin*2;
    PullUp(pin);
}

void GPIO_PORT::SetupGPIO_InPullDown (GPIO_PIN_N pin) 
{
    *_pGPIO_MODER &= ~(3<<pin*2);
    *_pGPIO_MODER |= GPIO_MODE_IN<<pin*2;
    PullDown(pin);
}


void GPIO_PORT::SetupGPIO_InAnalog (GPIO_PIN_N pin) 
{
    *_pGPIO_MODER &= ~(3<<pin*2);
    *_pGPIO_MODER |= GPIO_MODE_ANAL<<pin*2;
}



void GPIO_PORT::SetupGPIO_OutPP (GPIO_PIN_N pin) 
{
    *_pGPIO_MODER &= ~(3<<pin*2);
    *_pGPIO_MODER |= GPIO_MODE_OUT<<pin*2;

    *_pGPIO_OTYPER &= ~(3<<pin*2);
    *_pGPIO_OTYPER |= GPIO_CNF_OPP<<pin*2;
}

void GPIO_PORT::SetupGPIO_OutOD (GPIO_PIN_N pin) 
{
    *_pGPIO_MODER &= ~(3<<pin*2);
    *_pGPIO_MODER |= GPIO_MODE_OUT<<pin*2;

    *_pGPIO_OTYPER &= ~(3<<pin*2);
    *_pGPIO_OTYPER |= GPIO_CNF_OD<<pin*2;

}

void GPIO_PORT::SetupGPIO_OutAltOD (GPIO_PIN_N pin) 
{
    *_pGPIO_MODER &= ~(3<<pin*2);
    *_pGPIO_MODER |= GPIO_MODE_ALT<<pin*2;
    *_pGPIO_OTYPER &= ~(3<<pin*2);
    *_pGPIO_OTYPER |= GPIO_CNF_OD<<pin;
}

void GPIO_PORT::SetupGPIO_OutAltPP (GPIO_PIN_N pin) 
{
    *_pGPIO_MODER &= ~(3<<pin*2);
    *_pGPIO_MODER |= GPIO_MODE_ALT<<pin*2;
    *_pGPIO_OTYPER &= ~(3<<pin*2);
    *_pGPIO_OTYPER |= GPIO_CNF_OPP<<pin*2;
}

void GPIO_PORT::PullUp (GPIO_PIN_N pin) 
{
   *_pGPIO_PUPDR &= ~(3<<pin*2);
   *_pGPIO_PUPDR |= 1<<pin*2;
}

void GPIO_PORT::PullDown (GPIO_PIN_N pin) 
{
   *_pGPIO_PUPDR &= ~(3<<pin*2);
   *_pGPIO_PUPDR |= 2<<pin*2;
}


void GPIO_PORT::SetSpeedLow (GPIO_PIN_N pin)
{
  *_pGPIO_OSPEEDR &= ~(3<<pin*2);
  *_pGPIO_OSPEEDR |= (GPIO_OUT_SPEED_LOW<<pin*2);
}
    
void GPIO_PORT::SetSpeedMedium (GPIO_PIN_N pin)
{
  *_pGPIO_OSPEEDR &= ~(3<<pin*2);
  *_pGPIO_OSPEEDR |= (GPIO_OUT_SPEED_MEDIUM<<pin*2);
}


void GPIO_PORT::SetSpeedHigh (GPIO_PIN_N pin)
{
  *_pGPIO_OSPEEDR &= ~(3<<pin*2);
  *_pGPIO_OSPEEDR |= (GPIO_OUT_SPEED_HIGH<<pin*2);
}


void GPIO_PORT::SetOutput (uint16_t value)
{
    *_pGPIO_ODR = 0xffff & value;
}
    
void GPIO_PORT::SetPin (GPIO_PIN_N pin)
{
    *_pGPIO_BSRR = 0xffff & (1<<pin);
}

void GPIO_PORT::TogglePin (GPIO_PIN_N pin)
{
    *_pGPIO_ODR ^= (1<<pin);
}

    
void GPIO_PORT::ResetPin (GPIO_PIN_N pin)
{
    *_pGPIO_BSRR = 0xffff0000 & ((1<<pin)<<16);
}
    
uint32_t GPIO_PORT::GetInput()
{
    return *_pGPIO_IDR;
}

bool GPIO_PORT::IsSet (GPIO_PIN_N pin)
{
    return ((*_pGPIO_IDR & (1<<pin)) == (uint16_t)(1<<pin));
}


GPIO_PIN* GPIO_PORT::GetPin(GPIO_PIN_N pin_n)
{
    return &_pins[pin_n];
}

void GPIO_PORT::SetAF(GPIO_AF afno, GPIO_PIN_N pin)
{
    volatile uint32_t* afr = (pin<8)  ? _pGPIO_AFRL : _pGPIO_AFRH;
    *afr &= ~(GPIO_AFR_MASK<<(pin%8)*4);
    *afr |= afno<<((pin%8)*4);
}


////////////////////////////////////

void GPIO_PIN::SetupGPIO_InFloat ()
{
    gpioPort->SetupGPIO_InFloat(pin);
}


void GPIO_PIN::SetupGPIO_InPullUp ()
{
    gpioPort->SetupGPIO_InPullUp(pin);
}

void GPIO_PIN::SetupGPIO_InPullDown ()
{
    gpioPort->SetupGPIO_InPullDown(pin);
}


void GPIO_PIN::SetupGPIO_InAnalog ()
{
    gpioPort->SetupGPIO_InAnalog(pin);
}

void GPIO_PIN::SetupGPIO_OutPP ()
{
    gpioPort->SetupGPIO_OutPP(pin);
}

void GPIO_PIN::SetupGPIO_OutOD ()
{
    gpioPort->SetupGPIO_OutOD(pin);
}

void GPIO_PIN::SetupGPIO_OutAltOD ()
{
    gpioPort->SetupGPIO_OutAltOD(pin);
}

void GPIO_PIN::SetupGPIO_OutAltPP ()
{
    gpioPort->SetupGPIO_OutAltPP(pin);
}

void GPIO_PIN::PullUp ()
{
    gpioPort->PullUp(pin);
}

void GPIO_PIN::PullDown ()
{
    gpioPort->PullDown(pin);
}


void GPIO_PIN::SetSpeedLow ()
{
    gpioPort->SetSpeedLow(pin);
}

void GPIO_PIN::SetSpeedMedium ()
{
    gpioPort->SetSpeedMedium(pin);
}

void GPIO_PIN::SetSpeedHigh ()
{
    gpioPort->SetSpeedHigh(pin);
}

void GPIO_PIN::Set ()
{
    gpioPort->SetPin(pin);
}

void GPIO_PIN::Toggle ()
{
    gpioPort->TogglePin(pin);
}


void GPIO_PIN::Reset ()
{
    gpioPort->ResetPin(pin);
}

bool GPIO_PIN::IsSet ()
{
    return gpioPort->IsSet(pin);
}


void GPIO_PIN::SetAF(GPIO_AF afno)
{
    gpioPort->SetAF (afno, pin);
}

