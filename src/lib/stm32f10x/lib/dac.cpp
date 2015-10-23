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


#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_XD_VL)

#include "dac_cpp.h"

#ifdef USE_DAC


#include "nvic.h"

void TIM6_DAC_IRQHandler()
{
    DAC::GetInstance()->HandleIrq();
}

DAC::DAC()
{
    _dacChannels[0]._pDAC_DHR12L = &DAC_DHR12L1;
    _dacChannels[0]._pDAC_DHR12R = &DAC_DHR12R1;
    _dacChannels[0]._pDAC_DHR8R = &DAC_DHR8R1;
    _dacChannels[0]._pDAC_DOR = &DAC_DOR1;
    _dacChannels[0]._channelNo = DAC_CHANNEL_1;
    _dacChannels[1]._pDAC_DHR12L = &DAC_DHR12L2;
    _dacChannels[1]._pDAC_DHR12R = &DAC_DHR12R2;
    _dacChannels[1]._pDAC_DHR8R = &DAC_DHR8R2;
    _dacChannels[1]._pDAC_DOR = &DAC_DOR2;
    _dacChannels[1]._channelNo = DAC_CHANNEL_2;
    _irqHandler = 0;
}

void DAC::EnablePeripheralClock(bool enable)
{
    RCC::GetInstance()->EnableDAC(enable);

}

void DAC::HandleIrq()
{
    DAC_CHANNEL channelNo;
    DAC_IRQ_Handler* handler = 0;

    for (int i = 0; i < 2; ++i)
    {
        if (_dacChannels[i].IsUnderrun())
        {
            _dacChannels[i].ClearUnderrunInterruptFlag();
            channelNo = (DAC_CHANNEL) (i);
            handler = _irqHandler;
            break;
        }
    }

    if (handler)
    {
        handler->HandleInterrupt(channelNo);
    }
}

void DAC_Channel::EnableChannel()
{
    DAC_CR |= (DAC_CR_EN1 << (_channelNo * 16));
}

bool DAC_Channel::IsUnderrun()
{
    return DAC_SR & (DAC_SR_DMAUDR1 << (_channelNo * 16));
}

void DAC_Channel::EnableUnderrunInterrupt()
{
    DAC_CR |= (DAC_CR_DMAUDRIE1 << (_channelNo * 16));
    NVIC_SetEnable(IRQn_TIM6_DAC);
}

void DAC_Channel::ClearUnderrunInterruptFlag()
{
    DAC_CR &= ~(DAC_CR_DMAUDRIE1 << (_channelNo * 16));
}

void DAC_Channel::EnableDMA()
{
    DAC_CR |= (DAC_CR_DMAEN1 << (_channelNo * 16));
}

void DAC_Channel::EnableNoiseGeneration()
{
    DAC_CR &= ((3 << 6) << (_channelNo * 16));
    DAC_CR |= (DAC_CR_WAVE1_NOISE << (_channelNo * 16));
}

void DAC_Channel::EnableTriangleWaveGeneration()
{
    DAC_CR &= ((3 << 6) << (_channelNo * 16));
    DAC_CR |= (DAC_CR_WAVE1_TRI << (_channelNo * 16));
}

void DAC_Channel::_SelectTrigger(uint32_t trigger)
{
    DAC_CR &= ((3 << 3) << (_channelNo * 16));
    DAC_CR |= (trigger << (_channelNo * 16));
    DAC_CR |= (DAC_CR_TEN1 << (_channelNo * 16));
}

void DAC_Channel::SelectTriggerTimer6()
{
    _SelectTrigger(DAC_CR_TSEL1_TIM6);
}

void DAC_Channel::SelectTriggerTimer3()
{
    _SelectTrigger(DAC_CR_TSEL1_TIM3);
}

void DAC_Channel::SelectTriggerTimer7()
{
    _SelectTrigger(DAC_CR_TSEL1_TIM7);
}

void DAC_Channel::SelectTriggerTimer5_15()
{
    _SelectTrigger(DAC_CR_TSEL1_TIM5);
}

void DAC_Channel::SelectTriggerTimer2()
{
    _SelectTrigger(DAC_CR_TSEL1_TIM2);
}

void DAC_Channel::SelectTriggerTimer4()
{
    _SelectTrigger(DAC_CR_TSEL1_TIM4);
}

void DAC_Channel::EnableOutputBuffer(bool enable)
{
    if (enable)
    {
        DAC_CR &= ~(DAC_CR_BOFF1 << (_channelNo * 16));
    }
    else
    {
        DAC_CR |= (DAC_CR_BOFF1 << (_channelNo * 16));
    }
}

void DAC_Channel::EnableSoftwareTrigger(bool enable)
{
    if (enable)
    {
        DAC_SWTRIGR &= ~(DAC_SWTRIGR_1 << (_channelNo * 16));
    }
    else
    {
        DAC_SWTRIGR |= (DAC_SWTRIGR_1 << (_channelNo * 16));
    }
}

void DAC_Channel::SelectDataRegister12R()
{
    _dataRegister = _pDAC_DHR12R;
    _dataShift = 0;
    _dataBitmask = 0x4ff;
}

void DAC_Channel::SelectDataRegister12L()
{
    _dataRegister = _pDAC_DHR12L;
    _dataShift = 4;
    _dataBitmask = 0xffc;
}

void DAC_Channel::SelectDataRegister8R()
{
    _dataRegister = _pDAC_DHR8R;
    _dataShift = 0;
    _dataBitmask = 0xff;
}

void DAC_Channel::Write(uint16_t data)
{
    *_dataRegister = _dataBitmask & (data << _dataShift);
}

void DAC_Channel::SetAmplitude(DAC_AMPLITUDE amplitude)
{
    DAC_CR |= amplitude << (DAC_CR_AMPL1 + _channelNo * 16);
}

#endif

#endif
