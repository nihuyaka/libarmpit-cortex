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



#include "pwr.h"

#ifdef USE_PWR

#include "system_control.h"
#include "rcc_cpp.h"

void PWR::EnablePeripheralClock(bool enable)
{
    RCC::GetInstance()->EnablePWR(enable);
}

void PWR::EnableBKPWriteAccess(bool enable)
{
    if (enable)
    {
        PWR_CR |= PWR_CR_DBP;
    }
    else
    {
        PWR_CR &= ~PWR_CR_DBP;
    }
}

void PWR::Sleep(bool isWFI, bool sleepOnExit)
{
    SCB_SetSleepDeep(false);
    SCB_SetSleepOnExit(sleepOnExit);
    if (isWFI)
        __asm ("WFI");
    else
        __asm ("WFE");

}

void PWR::Stop(bool isLowPower, bool isWFI, bool sleepOnExit)
{
    PWR_CR &= ~PWR_CR_PDDS;
    if (isLowPower)
    {
        PWR_CR |= PWR_CR_LPDS;
    }
    else
    {
        PWR_CR &= ~PWR_CR_LPDS;
    }
    SCB_SetSleepDeep(false);
    SCB_SetSleepOnExit(sleepOnExit);

    if (isWFI)
        __asm ("WFI");
    else
        __asm ("WFE");

}

void PWR::Standby(bool isWFI, bool enableWakeupPin, bool sleepOnExit)
{
    PWR_CR |= PWR_CR_PDDS;
    PWR_CSR &= ~PWR_CSR_WUF;

    EnableWakeupPin(enableWakeupPin);

    SCB_SetSleepDeep(true);
    SCB_SetSleepOnExit(sleepOnExit);
    if (isWFI)
        __asm ("WFI");
    else
        __asm ("WFE");

}

void PWR::EnableWakeupPin(bool enable)
{
    if (enable)
        PWR_CSR |= PWR_CSR_EWUP;
    else
        PWR_CSR &= ~PWR_CSR_EWUP;
}

bool PWR::IsSBF()
{
    return PWR_CSR & PWR_CSR_SBF;
}

void PWR::ClearSBF()
{
    PWR_CR |= PWR_CR_CSBF;
}

bool PWR::IsWUF()
{
    return PWR_CSR & PWR_CSR_WUF;
}

void PWR::ClearWUF()
{
    PWR_CR |= PWR_CR_CWUF;
}

#endif
