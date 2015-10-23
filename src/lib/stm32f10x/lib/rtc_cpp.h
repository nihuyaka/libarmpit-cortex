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


#ifndef _RTC_CPP_H
#define _RTC_CPP_H

#include "rtc.h"

#ifdef USE_RTC


class RTC_Interrupt_Handler
{
public:
    virtual void HandleInterrupt (bool isOverrun, bool isAlarm, bool isSecond) = 0;

};

class RTC
{
private:
    RTC()
{
        _overrunHandler = 0;
        _alarmHandler = 0;
        _secondHandler = 0;
}

    RTC(RTC const&);
    void operator=(RTC const&);


    RTC_Interrupt_Handler* _overrunHandler;
    RTC_Interrupt_Handler* _alarmHandler;
    RTC_Interrupt_Handler* _secondHandler;

    void EnterConfigurationMode();
    void ExitConfigurationMode();

public:

    static RTC* GetInstance()
    {
        static RTC instance;
        return &instance;
    }

    void SetClockSourceHSE_DIV128();
    void SetClockSourceLSE();
    void SetClockSourceLSI();
    void EnableClock(bool enable);
    void WaitRSF();

    void EnableOverrunInterrupt (bool enable, RTC_Interrupt_Handler* overrunHandler = 0);
    void EnableAlarmInterrupt (bool enable, RTC_Interrupt_Handler* alarmHandler = 0);
    void EnableSecondInterrupt (bool enable, RTC_Interrupt_Handler* secondHandler = 0);

    void HandleInterrupt ();

    bool IsOverrun();
    bool IsAlarm();
    bool IsSecond();

    void ClearOverrun();
    void ClearAlarm();
    void ClearSecond();

    void SetPrescaler (uint32_t val);
    void SetCounter (uint32_t val);
    uint32_t GetCounter();
    void SetAlarm (uint32_t val);
    void SetPrescaler_ms (uint32_t val);
    void SetAlarm_ms (uint32_t val);

    void OutputAlarmPulse (bool enable);
    void OutputSecondPulse (bool enable);


};




#endif

#endif
