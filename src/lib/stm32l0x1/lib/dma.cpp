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

#include "dma_cpp.h"
#ifdef USE_DMA

#ifdef __cplusplus
extern "C"
{
#endif

void DMA1_Channel1_IRQHandler()
{
    DMA1::GetInstance()->IRQ_Handler(1);
}
void DMA1_Channel2_IRQHandler()
{
    DMA1::GetInstance()->IRQ_Handler(2);
}
void DMA1_Channel3_IRQHandler()
{
    DMA1::GetInstance()->IRQ_Handler(3);
}
void DMA1_Channel4_IRQHandler()
{
    DMA1::GetInstance()->IRQ_Handler(4);
}
void DMA1_Channel5_IRQHandler()
{
    DMA1::GetInstance()->IRQ_Handler(5);
}
void DMA1_Channel6_IRQHandler()
{
    DMA1::GetInstance()->IRQ_Handler(6);
}
void DMA1_Channel7_IRQHandler()
{
    DMA1::GetInstance()->IRQ_Handler(7);
}


#ifdef __cplusplus
}
#endif

DMA::DMA(volatile uint32_t* DMA_CCR, volatile uint32_t* DMA_CNDTR,
        volatile uint32_t* DMA_CPAR, volatile uint32_t* DMA_CMAR,
        volatile uint32_t* DMA_ISR, volatile uint32_t* DMA_IFCR, int nChannels,
        IRQn_Type* nvicIrqNumbers, uint32_t rccBit) :
        Peripheral(&RCC_AHBENR, &RCC_AHBENR, rccBit)

{
    for (int i = 0; i < nChannels; ++i)
    {
        _dmaChannels[i]._pDMA_CCR = (uint32_t*) ((uint32_t) DMA_CCR + 20 * i);
        _dmaChannels[i]._pDMA_CNDTR =
                (uint32_t*) ((uint32_t) DMA_CNDTR + 20 * i);
        _dmaChannels[i]._pDMA_CPAR = (uint32_t*) ((uint32_t) DMA_CPAR + 20 * i);
        _dmaChannels[i]._pDMA_CMAR = (uint32_t*) ((uint32_t) DMA_CMAR + 20 * i);
        _dmaChannels[i].DMA_ISR_GIF = ((DMA_ISR_GIF1) << (i * 4));
        _dmaChannels[i].DMA_ISR_TCIF = ((DMA_ISR_TCIF1) << (i * 4));
        _dmaChannels[i].DMA_ISR_HTIF = ((DMA_ISR_HTIF1) << (i * 4));
        _dmaChannels[i].DMA_ISR_TEIF = ((DMA_ISR_TEIF1) << (i * 4));
        _dmaChannels[i].DMA_IFCR_CGIF = ((DMA_IFCR_CGIF1) << (i * 4));
        _dmaChannels[i].DMA_IFCR_CTCIF = ((DMA_IFCR_CTCIF1) << (i * 4));
        _dmaChannels[i].DMA_IFCR_CHTIF = ((DMA_IFCR_CHTIF1) << (i * 4));
        _dmaChannels[i].DMA_IFCR_CTEIF = ((DMA_IFCR_CTEIF1) << (i * 4));
        _dmaChannels[i]._nvicIrqNumber = nvicIrqNumbers[i];
    }

    _nChannels = nChannels;
    _pDMA_IFCR = DMA_IFCR;
    _pDMA_ISR = DMA_ISR;
    _irqHandler = 0;
}

void DMA1::EnablePeripheralClock(bool enable)
{
    RCC_EnableDMA1(enable);
}
bool DMA1::IsClockEnabled()
{
    return RCC_IsEnabledDMA1();
}

DMA_Channel* DMA::GetChannel(DMA_CHANNEL channelNo)
{
    return &_dmaChannels[channelNo];
}

void DMA::IRQ_Handler(int channelNo)
{
    if (_irqHandler)
    {
        DMA_Channel* channel = &_dmaChannels[channelNo - 1];
        bool isTransferComplete = IsTransferComplete(channel);
        bool isTransferError = IsTransferError(channel);
        bool isHalfTransfer = IsHalfTransferComplete(channel);

        if (isTransferComplete)
        {
            ClearTransferComplete(channel);
        }
        if (isHalfTransfer)
        {
            ClearHalfTransferComplete(channel);
        }
        if (isTransferError)
        {
            ClearTransferError(channel);
        }

        *_pDMA_IFCR |= channel->DMA_IFCR_CGIF;

        _irqHandler->HandleInterrupt(channel, isTransferComplete,
                isHalfTransfer, isTransferError);
    }
}

void DMA_Channel::EnableChannel(bool enable)
{
    if (enable)
    {
        *_pDMA_CCR |= DMA_CCR_EN;
    }
    else
    {
        *_pDMA_CCR &= ~DMA_CCR_EN;
    }
}

bool DMA::IsTransferComplete(DMA_Channel* channel)
{
    return (*_pDMA_ISR & channel->DMA_ISR_TCIF);
}

bool DMA::IsHalfTransferComplete(DMA_Channel* channel)
{
    return (*_pDMA_ISR & channel->DMA_ISR_HTIF);
}

bool DMA::IsTransferError(DMA_Channel* channel)
{
    return (*_pDMA_ISR & channel->DMA_ISR_TEIF);
}

void DMA::ClearTransferComplete(DMA_Channel* channel)
{
    *_pDMA_IFCR |= channel->DMA_IFCR_CTCIF;
    *_pDMA_IFCR |= channel->DMA_IFCR_CGIF;
}

void DMA::ClearHalfTransferComplete(DMA_Channel* channel)
{
    *_pDMA_IFCR |= channel->DMA_IFCR_CHTIF;
    *_pDMA_IFCR |= channel->DMA_IFCR_CGIF;
}

void DMA::ClearTransferError(DMA_Channel* channel)
{
    *_pDMA_IFCR |= channel->DMA_IFCR_CTEIF;
    *_pDMA_IFCR |= channel->DMA_IFCR_CGIF;
}

void DMA_Channel::SetPeripheralAddress(uint32_t addr)
{
    *_pDMA_CPAR = addr;
}
void DMA_Channel::SetMemoryAddress(uint32_t addr)
{
    *_pDMA_CMAR = addr;
}

void DMA_Channel::SetPeripheralSize_8bits()
{
    *_pDMA_CCR |= DMA_CCR_PSIZE_8;
}
void DMA_Channel::SetPeripheralSize_16bits()
{
    *_pDMA_CCR |= DMA_CCR_PSIZE_16;
}
void DMA_Channel::SetPeripheralSize_32bits()
{
    *_pDMA_CCR |= DMA_CCR_PSIZE_32;
}
void DMA_Channel::SetMemorySize_8bits()
{
    *_pDMA_CCR |= DMA_CCR_MSIZE_8;
}
void DMA_Channel::SetMemorySize_16bits()
{
    *_pDMA_CCR |= DMA_CCR_MSIZE_16;
}
void DMA_Channel::SetMemorySize_32bits()
{
    *_pDMA_CCR |= DMA_CCR_MSIZE_32;
}
void DMA_Channel::SetNumberOfData(uint16_t length)
{
    *_pDMA_CNDTR = length;
}

void DMA_Channel::SetDirection_MemoryToPeripheral()
{
    *_pDMA_CCR |= DMA_CCR_DIR;
    *_pDMA_CCR &= ~DMA_CCR_MEM2MEM;
}
void DMA_Channel::SetDirection_PeripheralToMemory()
{
    *_pDMA_CCR &= ~DMA_CCR_DIR;
    *_pDMA_CCR &= ~DMA_CCR_MEM2MEM;
}
void DMA_Channel::SetDirection_MemoryToMemory()
{
    *_pDMA_CCR &= ~DMA_CCR_DIR;
    *_pDMA_CCR |= DMA_CCR_MEM2MEM;
}
void DMA_Channel::SetMemoryIncrementMode()
{
    *_pDMA_CCR |= DMA_CCR_MINC;
}
void DMA_Channel::SetPeripheralIncrementMode()
{
    *_pDMA_CCR |= DMA_CCR_PINC;

}
void DMA_Channel::SetCircularMode()
{
    *_pDMA_CCR |= DMA_CCR_CIRC;

}
void DMA_Channel::SetPriorityLow()
{
    *_pDMA_CCR |= DMA_CCR_PL_LOW;
}
void DMA_Channel::SetPriorityMedium()
{
    *_pDMA_CCR |= DMA_CCR_PL_MED;
}
void DMA_Channel::SetPriorityHigh()
{
    *_pDMA_CCR |= DMA_CCR_PL_HI;

}
void DMA_Channel::SetPriorityVeryHigh()
{
    *_pDMA_CCR |= DMA_CCR_PL_VHI;
}

void DMA_Channel::EnableTransferErrorInterrupt()
{
    *_pDMA_CCR |= DMA_CCR_TEIE;
    NVIC_SetEnable(_nvicIrqNumber);
}
void DMA_Channel::EnableHalfTransferInterrupt()
{
    *_pDMA_CCR |= DMA_CCR_HTIE;
    NVIC_SetEnable(_nvicIrqNumber);
}
void DMA_Channel::EnableTransferCompleteInterrupt()
{
    *_pDMA_CCR |= DMA_CCR_TCIE;
    NVIC_SetEnable(_nvicIrqNumber);
}

IRQn_Type DMA1::nvicIrqNumbers[7] =
{ IRQn_DMA1_Channel1, IRQn_DMA1_Channel2, IRQn_DMA1_Channel3,
        IRQn_DMA1_Channel4, IRQn_DMA1_Channel5, IRQn_DMA1_Channel6,
        IRQn_DMA1_Channel7 
};

#endif
