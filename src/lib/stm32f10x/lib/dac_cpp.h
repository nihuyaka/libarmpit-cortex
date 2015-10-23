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



#ifndef _DAC_CPP_H
#define _DAC_CPP_H
#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_XD_VL)

#include "dac.h"

#ifdef USE_DAC



#include "rcc.h"
#include "peripheral.h"

enum DAC_CHANNEL
{
    DAC_CHANNEL_1 = 0, DAC_CHANNEL_2 = 1
};

class DAC_IRQ_Handler;

class DAC_Channel
{
    friend class DAC;
private:
    volatile uint32_t* _pDAC_DHR12R;
    volatile uint32_t* _pDAC_DHR12L;
    volatile uint32_t* _pDAC_DHR8R;
    volatile uint32_t* _pDAC_DOR;
    volatile uint32_t* _dataRegister;
    uint8_t _dataShift;
    uint32_t _dataBitmask;

    DAC_CHANNEL _channelNo;

    DAC_Channel(DAC_Channel const&);
    void operator=(DAC_Channel const&);

    void _SelectTrigger(uint32_t timer);

protected:

    DAC_Channel()
    {
        _dataRegister = _pDAC_DHR12R;
        _dataShift = 0;
        _dataBitmask = 0x4ff;
    }

public:

    void EnableChannel();
    bool IsUnderrun();
    void EnableUnderrunInterrupt();
    void ClearUnderrunInterruptFlag();
    void EnableDMA();
    void EnableNoiseGeneration();
    void EnableTriangleWaveGeneration();
    void SelectTriggerTimer6();
    void SelectTriggerTimer3();
    void SelectTriggerTimer7();
    void SelectTriggerTimer2();
    void SelectTriggerTimer4();
    void SelectTriggerTimer5_15();
    void EnableOutputBuffer(bool enable);
    void EnableSoftwareTrigger(bool enable);
    void SelectDataRegister12R();
    void SelectDataRegister12L();
    void SelectDataRegister8R();
    void Write(uint16_t data);
    void SetAmplitude(DAC_AMPLITUDE amplitude);

    volatile uint32_t* GetDataRegisterAddress()
    {
        return _dataRegister;
    }

};

class DAC: public Peripheral
{
public:

    DAC_Channel _dacChannels[2];

    static DAC* GetInstance()
    {
        static DAC instance;
        return &instance;
    }

private:

    DAC_IRQ_Handler* _irqHandler;

    DAC();

    DAC(DAC const&);
    void operator=(DAC const&);

public:

    void EnablePeripheralClock(bool enable);
    DAC_Channel* GetChannel(DAC_CHANNEL channelNo)
    {
        return &_dacChannels[channelNo];
    }
    void SetIrqHandler(DAC_IRQ_Handler* handler)
    {
        _irqHandler = handler;
    }
    void HandleIrq();
};

class DAC_IRQ_Handler
{
public:
    virtual void HandleInterrupt(DAC_CHANNEL channelNo) = 0;
};

#endif

#endif

#endif
