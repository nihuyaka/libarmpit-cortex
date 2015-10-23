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


#include "exti.h"
#ifdef USE_EXTI

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(STM32F1) || defined(STM32F2) || defined(STM32F4)
void EXTI0_IRQHandler()
{
    EXTI0::GetInstance()->HandleInterrupt();
}
void EXTI1_IRQHandler()
{
    EXTI1::GetInstance()->HandleInterrupt();
}

void EXTI2_IRQHandler()
{
    EXTI2::GetInstance()->HandleInterrupt();
}

void EXTI3_IRQHandler()
{
    EXTI3::GetInstance()->HandleInterrupt();
}

void EXTI4_IRQHandler()
{
    EXTI4::GetInstance()->HandleInterrupt();
}

void EXTI9_5_IRQHandler()
{
    if (EXTI_PR & (1 << EXTI_LINE5))
        EXTI5::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE6))
        EXTI6::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE7))
        EXTI7::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE8))
        EXTI8::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE9))
        EXTI9::GetInstance()->HandleInterrupt();
}

void EXTI15_10_IRQHandler()
{
    if (EXTI_PR & (1 << EXTI_LINE10))
        EXTI10::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE11))
        EXTI11::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE12))
        EXTI12::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE13))
        EXTI13::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE14))
        EXTI14::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE15))
        EXTI15::GetInstance()->HandleInterrupt();
}

#elif defined(STM32L0)

void EXTI0_1_IRQHandler() 
{
    if (EXTI_PR & (1 << EXTI_LINE0))
        EXTI0::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE1))
        EXTI1::GetInstance()->HandleInterrupt();
}

void EXTI2_3_IRQHandler() 
{
    if (EXTI_PR & (1 << EXTI_LINE2))
        EXTI2::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE3))
        EXTI3::GetInstance()->HandleInterrupt();
}

void EXTI4_15_IRQHandler() 
{
    if (EXTI_PR & (1 << EXTI_LINE4))
        EXTI4::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE5))
        EXTI5::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE6))
        EXTI6::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE7))
        EXTI7::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE8))
        EXTI8::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE9))
        EXTI9::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE10))
        EXTI10::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE11))
        EXTI11::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE12))
        EXTI12::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE13))
        EXTI13::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE14))
        EXTI14::GetInstance()->HandleInterrupt();
    if (EXTI_PR & (1 << EXTI_LINE15))
        EXTI15::GetInstance()->HandleInterrupt();

}


#else
#error "Target device not defined"
#endif

#ifdef __cplusplus
}
#endif

void EXTI::HandleInterrupt()
{
    ClearPending();
    if (_irqHandler)
    {
        _irqHandler->HandleInterrupt(this);
    }

}

bool EXTI::IsPending()
{
    return (EXTI_PR & (1 << _line));
}
void EXTI::ClearPending()
{
    EXTI_PR |= (1 << _line);
}

void EXTI::Enable(bool enable, volatile uint32_t* edgeReg,
        volatile uint32_t* eventOrIntReg)
{
    if (enable)
    {
        if (_irqnNo != IRQn_NONE)
        {
            NVIC_SetEnable(_irqnNo);
        }
        *edgeReg |= (1 << _line);
        *eventOrIntReg |= (1 << _line);
    }
    else
    {
        if (_irqnNo != IRQn_NONE)
        {
            NVIC_ClearEnable(_irqnNo);
        }
        *edgeReg &= ~(1 << _line);
        *eventOrIntReg &= ~(1 << _line);
    }
}

void EXTI::EnableInterruptRisingEdge(bool enable)
{
    Enable(enable, &EXTI_RTSR, &EXTI_IMR);
}
void EXTI::EnableInterruptFallingEdge(bool enable)
{
    Enable(enable, &EXTI_FTSR, &EXTI_IMR);
}
void EXTI::EnableEventRisingEdge(bool enable)
{
    Enable(enable, &EXTI_RTSR, &EXTI_EMR);
}
void EXTI::EnableEventFallingEdge(bool enable)
{
    Enable(enable, &EXTI_FTSR, &EXTI_EMR);
}
void EXTI::GenerateSWI(bool enable)
{
    if (enable)
        EXTI_SWIER |= (1 << _line);
    else
        EXTI_SWIER &= ~(1 << _line);

}

#endif
