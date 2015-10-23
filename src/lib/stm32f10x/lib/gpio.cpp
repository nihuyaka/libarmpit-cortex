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

GPIO_PORT::GPIO_PORT(volatile uint64_t* pGPIO_CR, volatile uint32_t* pGPIO_IDR,
        volatile uint32_t* pGPIO_ODR, volatile uint32_t* pGPIO_BSRR,
        volatile uint32_t* pGPIO_BRR, volatile uint32_t* pGPIO_LCKR,
        volatile uint32_t* pRCCEnableReg,
        volatile uint32_t* pRCCResetReg,
        uint32_t           rccBit) : Peripheral (pRCCEnableReg, pRCCResetReg, rccBit)

{
    _pGPIO_CR = pGPIO_CR;
    _pGPIO_IDR = pGPIO_IDR;
    _pGPIO_ODR = pGPIO_ODR;
    _pGPIO_BSRR = pGPIO_BSRR;
    _pGPIO_BRR = pGPIO_BRR;
    _pGPIO_LCKR = pGPIO_LCKR;
    for (int i = 0; i < 16; ++i)
    {
        _pins[i]._init(this, (GPIO_PIN_N) i);
    }
}

void GPIO_PORT::SetupGPIO(GPIO_PIN_N pin, uint32_t cnf, GPIO_MODE mode)
{
    *_pGPIO_CR &= ~(0xfLLU << ((uint64_t) pin << 2LLU));
    *_pGPIO_CR |= (((uint64_t) cnf << 2LLU) | (uint64_t) mode)
            << ((uint64_t) pin << 2LLU);
}

void GPIO_PORT::SetupGPIO_Cnf(GPIO_PIN_N pin, uint32_t cnf)
{
    *_pGPIO_CR &= ~(0xcLLU << ((uint64_t) pin << 2LLU));
    *_pGPIO_CR |= ((uint64_t) cnf << 2LLU)  << ((uint64_t) pin << 2LLU);
}

void GPIO_PORT::SetupGPIO_Mode(GPIO_PIN_N pin, uint32_t mode)
{
    *_pGPIO_CR &= ~(0x3LLU << ((uint64_t) pin << 2LLU));
    *_pGPIO_CR |= ((uint64_t) mode)  << ((uint64_t) pin << 2LLU);
}



void GPIO_PORT::Lock(uint16_t bitMask)
{
    *_pGPIO_LCKR = (0xff & bitMask);
    *_pGPIO_LCKR |= GPIOG_LCKR_LCKK;
    *_pGPIO_LCKR &= ~GPIOG_LCKR_LCKK;
    *_pGPIO_LCKR |= GPIOG_LCKR_LCKK;
    uint16_t tmp = *_pGPIO_LCKR;
    ++tmp;
}

void GPIO_PORT::SetupGPIO_InFloat(GPIO_PIN_N pin)
{
    SetupGPIO(pin, GPIO_CNF_IFLOAT, GPIO_MODE_INP);
}

void GPIO_PORT::SetupGPIO_InAnalog(GPIO_PIN_N pin)
{
    SetupGPIO(pin, GPIO_CNF_IANAL, GPIO_MODE_INP);
}

void GPIO_PORT::SetupGPIO_InPullUp (GPIO_PIN_N pin) 
{
    SetupGPIO (pin, GPIO_CNF_IPUPD, GPIO_MODE_INP);
    SetPin (pin);
}

void GPIO_PORT::SetupGPIO_InPullDown (GPIO_PIN_N pin) 
{
    SetupGPIO (pin, GPIO_CNF_IPUPD, GPIO_MODE_INP);
    ResetPin (pin);
}


void GPIO_PORT::SetupGPIO_OutPP(GPIO_PIN_N pin)
{
    SetupGPIO(pin, GPIO_CNF_OPP, GPIO_MODE_OUT_HIGH_SPEED);
}


void GPIO_PORT::SetupGPIO_OutOD(GPIO_PIN_N pin)
{
    SetupGPIO(pin, GPIO_CNF_OD, GPIO_MODE_OUT_HIGH_SPEED);
}

void GPIO_PORT::SetupGPIO_OutAltOD(GPIO_PIN_N pin)
{
    SetupGPIO(pin, GPIO_CNF_ALT_OD, GPIO_MODE_OUT_HIGH_SPEED);
}

void GPIO_PORT::SetupGPIO_OutAltPP(GPIO_PIN_N pin)
{
    SetupGPIO(pin, GPIO_CNF_ALT_PP, GPIO_MODE_OUT_HIGH_SPEED);
}

void GPIO_PORT::SetSpeedLow (GPIO_PIN_N pin)
{
    SetupGPIO_Mode(pin, GPIO_MODE_OUT_LOW_SPEED);
}

void GPIO_PORT::SetSpeedMedium (GPIO_PIN_N pin)
{
    SetupGPIO_Mode(pin, GPIO_MODE_OUT_MEDIUM_SPEED);
}


void GPIO_PORT::SetSpeedHigh (GPIO_PIN_N pin)
{
    SetupGPIO_Mode(pin, GPIO_MODE_OUT_HIGH_SPEED);
}


void GPIO_PORT::SetOutput(uint16_t value)
{
    *_pGPIO_ODR = 0xffff & value;
}

void GPIO_PORT::SetPin(GPIO_PIN_N pin)
{
    *_pGPIO_BSRR = 0xffff & (1 << pin);
}

void GPIO_PORT::TogglePin(GPIO_PIN_N pin)
{
    *_pGPIO_ODR ^= (1 << pin);
}

void GPIO_PORT::ResetPin(GPIO_PIN_N pin)
{
    *_pGPIO_BRR = 0xffff & (1 << pin);
}

uint32_t GPIO_PORT::GetInput()
{
    return *_pGPIO_IDR;
}

bool GPIO_PORT::IsSet(GPIO_PIN_N pin)
{
    return ((*_pGPIO_IDR & (1 << pin)) == (uint16_t)(1 << pin));
}

GPIO_PIN* GPIO_PORT::GetPin(GPIO_PIN_N pin_n)
{
    return &_pins[pin_n];
}

////////////////////////////////////
void GPIO_PIN::SetupGPIO_InFloat()
{
    gpioPort->SetupGPIO(pin, GPIO_CNF_IFLOAT, GPIO_MODE_INP);
}

void GPIO_PIN::SetupGPIO_InAnalog()
{
    gpioPort->SetupGPIO(pin, GPIO_CNF_IANAL, GPIO_MODE_INP);
}

void GPIO_PIN::SetupGPIO_InPullUp ()
{
    gpioPort->SetupGPIO_InPullUp (pin);
}

void GPIO_PIN::SetupGPIO_InPullDown ()
{
    gpioPort->SetupGPIO_InPullDown (pin);
}

void GPIO_PIN::SetupGPIO_OutPP()
{
    gpioPort->SetupGPIO(pin, GPIO_CNF_OPP, GPIO_MODE_OUT_HIGH_SPEED);
}

void GPIO_PIN::SetupGPIO_OutOD()
{
    gpioPort->SetupGPIO(pin, GPIO_CNF_OD, GPIO_MODE_OUT_HIGH_SPEED);
}

void GPIO_PIN::SetupGPIO_OutAltOD()
{
    gpioPort->SetupGPIO(pin, GPIO_CNF_ALT_OD, GPIO_MODE_OUT_HIGH_SPEED);
}

void GPIO_PIN::SetupGPIO_OutAltPP()
{
    gpioPort->SetupGPIO(pin, GPIO_CNF_ALT_PP, GPIO_MODE_OUT_HIGH_SPEED);
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

void GPIO_PIN::Set()
{
    gpioPort->SetPin(pin);
}
void GPIO_PIN::Toggle()
{
    gpioPort->TogglePin(pin);
}
void GPIO_PIN::Reset()
{
    gpioPort->ResetPin(pin);
}
bool GPIO_PIN::IsSet()
{
    return gpioPort->IsSet(pin);
}

