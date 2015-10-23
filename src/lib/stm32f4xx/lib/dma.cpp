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


#define ISR_POS(CHANNEL) ((CHANNEL%2) * 6  + (((CHANNEL%4) / 2)*16))



#ifdef __cplusplus
extern "C"
{
#endif

void DMA1_Stream0_IRQHandler()
{
   DMA1::GetInstance()->IRQ_Handler(0);
}
void DMA1_Stream1_IRQHandler()
{
    DMA1::GetInstance()->IRQ_Handler(1);
}
void DMA1_Stream2_IRQHandler()
{
    DMA1::GetInstance()->IRQ_Handler(2);
}
void DMA1_Stream3_IRQHandler()
{
    DMA1::GetInstance()->IRQ_Handler(3);
}
void DMA1_Stream4_IRQHandler()
{
    DMA1::GetInstance()->IRQ_Handler(4);
}
void DMA1_Stream5_IRQHandler()
{
    DMA1::GetInstance()->IRQ_Handler(5);
}
void DMA1_Stream6_IRQHandler()
{
    DMA1::GetInstance()->IRQ_Handler(6);
}
void DMA1_Stream7_IRQHandler()
{
    DMA1::GetInstance()->IRQ_Handler(7);
}

void DMA2_Stream0_IRQHandler()
{
    //DMA2::GetInstance()->IRQ_Handler(0);

}
void DMA2_Stream1_IRQHandler()
{
    DMA2::GetInstance()->IRQ_Handler(1);
}
void DMA2_Stream2_IRQHandler()
{
    DMA2::GetInstance()->IRQ_Handler(2);
}
void DMA2_Stream3_IRQHandler()
{
    DMA2::GetInstance()->IRQ_Handler(3);
}
void DMA2_Stream4_IRQHandler()
{
    DMA2::GetInstance()->IRQ_Handler(4);
}
void DMA2_Stream5_IRQHandler()
{
    DMA2::GetInstance()->IRQ_Handler(5);
}
void DMA2_Stream6_IRQHandler()
{
    DMA2::GetInstance()->IRQ_Handler(6);
}
void DMA2_Stream7_IRQHandler()
{
    DMA2::GetInstance()->IRQ_Handler(7);
}



#ifdef __cplusplus
}
#endif

DMA::DMA(uint8_t DMA_number, IRQn_Type* nvicIrqNumbers) 
: Peripheral (&RCC_AHB1ENR, &RCC_AHB1RSTR, DMA_number==1 ? RCC_AHB1ENR_DMA1EN : RCC_AHB1ENR_DMA2EN )

{
    volatile uint32_t* pDMAx_LISR;
    volatile uint32_t* pDMAx_HISR;
    volatile uint32_t* pDMAx_LIFCR;
    volatile uint32_t* pDMAx_HIFCR;

    volatile uint32_t* pDMAx_SCR;
    volatile uint32_t* pDMAx_SNDTR;
    volatile uint32_t* pDMAx_SPAR;
    volatile uint32_t* pDMAx_SM0AR;
    volatile uint32_t* pDMAx_SM1AR;
    volatile uint32_t* pDMAx_SFCR;

    if (DMA_number == 1)
    {
        pDMAx_LISR = &DMA1_LISR;
        pDMAx_HISR = &DMA1_HISR;
        pDMAx_LIFCR = &DMA1_LIFCR;
        pDMAx_HIFCR = &DMA1_HIFCR;
        pDMAx_SCR  = &DMA1_S0CR;
        pDMAx_SNDTR  = &DMA1_S0NDTR;
        pDMAx_SPAR  = &DMA1_S0PAR;
        pDMAx_SM0AR  = &DMA1_S0M0AR;
        pDMAx_SM1AR  = &DMA1_S0M1AR;
        pDMAx_SFCR  = &DMA1_S0FCR;
    }
    else 
    {
        pDMAx_LISR = &DMA2_LISR;
        pDMAx_HISR = &DMA2_HISR;
        pDMAx_LIFCR = &DMA2_LIFCR;
        pDMAx_HIFCR = &DMA2_HIFCR;
        pDMAx_SCR  = &DMA2_S0CR;
        pDMAx_SNDTR  = &DMA2_S0NDTR;
        pDMAx_SPAR  = &DMA2_S0PAR;
        pDMAx_SM0AR  = &DMA2_S0M0AR;
        pDMAx_SM1AR  = &DMA2_S0M1AR;
        pDMAx_SFCR  = &DMA2_S0FCR;
    }


    for (uint8_t i = 0; i < 8; ++i)
    {
        _dmaStreams[i]._streamNumber = i;
        if (i < 4  )
        {
            _dmaStreams[i]._pDMA_ISR = pDMAx_LISR;
            _dmaStreams[i]._pDMA_IFCR = pDMAx_LIFCR;
        }
        else
        {
            _dmaStreams[i]._pDMA_ISR = pDMAx_HISR;
            _dmaStreams[i]._pDMA_IFCR = pDMAx_HIFCR;
        }


        _dmaStreams[i]._pDMA_SCR   = (uint32_t*) ((uint32_t)pDMAx_SCR   + (i * 0x18));
        _dmaStreams[i]._pDMA_SNDTR = (uint32_t*) ((uint32_t)pDMAx_SNDTR + (i * 0x18));
        _dmaStreams[i]._pDMA_SPAR  = (uint32_t*) ((uint32_t)pDMAx_SPAR  + (i * 0x18));
        _dmaStreams[i]._pDMA_SM0AR = (uint32_t*) ((uint32_t)pDMAx_SM0AR + (i * 0x18));
        _dmaStreams[i]._pDMA_SM1AR = (uint32_t*) ((uint32_t)pDMAx_SM1AR + (i * 0x18));
        _dmaStreams[i]._pDMA_SFCR  = (uint32_t*) ((uint32_t)pDMAx_SFCR  + (i * 0x24));

        _dmaStreams[i]._nvicIrqNumber = nvicIrqNumbers[i];

        _dmaStreams[i]._FEIF =  1<<DMA_IFCR_FEIF0_OFFSET<<ISR_POS(i);
        _dmaStreams[i]._DMEIF =  1<<DMA_IFCR_DMEIF0_OFFSET<<ISR_POS(i);
        _dmaStreams[i]._TEIF =  1<<DMA_IFCR_TEIF0_OFFSET<<ISR_POS(i);
        _dmaStreams[i]._HTIF =  1<<DMA_IFCR_HTIF0_OFFSET<<ISR_POS(i);
        _dmaStreams[i]._TCIF =  1<<DMA_IFCR_TCIF0_OFFSET<<ISR_POS(i);
        
        
    }

    _irqHandler = 0;
}

DMA_Stream* DMA::GetStream(DMA_STREAM_N streamNo)
{
    return &_dmaStreams[streamNo];
}

void DMA::IRQ_Handler(int streamNo)
{
    if (_irqHandler)
    {
        DMA_Stream* stream = &_dmaStreams[streamNo];
        bool isTransferComplete = stream->IsTransferComplete();
        bool isTransferError = stream->IsTransferError();
        bool isHalfTransfer = stream->IsHalfTransferComplete();

        if (isTransferComplete)
        {
            stream->ClearTransferComplete();
        }
        if (isHalfTransfer)
        {
            stream->ClearHalfTransferComplete();
        }
        if (isTransferError)
        {
            stream->ClearTransferError();
        }

        _irqHandler->HandleInterrupt(stream, isTransferComplete, isHalfTransfer,
                isTransferError);
    }
}

void DMA_Stream::SetChannel (DMA_CHANNEL channel)
{
    *_pDMA_SCR |=  (channel<<DMA_SCR_CHSEL_OFFSET);  
}


void DMA_Stream::EnableStream(bool enable)
{
    if (enable)
    {
        *_pDMA_SCR |= DMA_SCR_EN;
    }
    else
    {
        *_pDMA_SCR &= ~DMA_SCR_EN;
    }
}

void DMA_Stream::EnableDirectModeErrorInterrupt(bool enable)
{
    if (enable) 
    {
        *_pDMA_SCR |= DMA_SCR_DMEIE;
    }
    else
    {
        *_pDMA_SCR &= ~DMA_SCR_DMEIE;
    }
    NVIC_SetEnable (_nvicIrqNumber);
}


bool DMA_Stream::IsDirectModeError()
{
    return *_pDMA_ISR & _DMEIF;
}

void DMA_Stream::ClearDirectModeError()
{
    *_pDMA_IFCR &= ~_DMEIF;
}
    
void DMA_Stream::EnableTransferErrorInterrupt(bool enable)
{
    if (enable) 
    {
        *_pDMA_SCR |= DMA_SCR_TEIE;
    }
    else
    {
        *_pDMA_SCR &= ~DMA_SCR_TEIE;
    }
    NVIC_SetEnable (_nvicIrqNumber);
}


bool DMA_Stream::IsTransferError()
{
    return *_pDMA_ISR & _TEIF;
}

void DMA_Stream::ClearTransferError()
{
    *_pDMA_IFCR |= _TEIF;
}


void DMA_Stream::EnableHalfTransferInterrupt(bool enable)
{
    if (enable) 
    {
        *_pDMA_SCR |= DMA_SCR_HTIE;
    }
    else
    {
        *_pDMA_SCR &= ~DMA_SCR_HTIE;
    }
    NVIC_SetEnable (_nvicIrqNumber);
}

bool DMA_Stream::IsHalfTransferComplete()
{
    return *_pDMA_ISR & _HTIF;
}

void DMA_Stream::ClearHalfTransferComplete()
{
    *_pDMA_IFCR |= _HTIF;    
}


void DMA_Stream::EnableTransferCompleteInterrupt(bool enable)
{
    if (enable) 
    {
        *_pDMA_SCR |= DMA_SCR_TCIE;
    }
    else
    {
        *_pDMA_SCR &= ~DMA_SCR_TCIE;
    }
    NVIC_SetEnable (_nvicIrqNumber);
}

bool DMA_Stream::IsTransferComplete()
{
    return *_pDMA_ISR & _TCIF;
}

void DMA_Stream::ClearTransferComplete()
{
    *_pDMA_IFCR |= _TCIF;
}

void DMA_Stream::EnableFIFOErrorInterrupt(bool enable)
{
    if (enable) 
    {
        *_pDMA_SFCR |= DMA_SFCR_FEIE;
    }
    else
    {
        *_pDMA_SFCR &= ~DMA_SFCR_FEIE;
    }
}

bool DMA_Stream::IsFIFOError()
{
    return *_pDMA_ISR & _FEIF;
}
void DMA_Stream::ClearFIFOError()
{
    *_pDMA_IFCR |= _FEIF;
}

void DMA_Stream::SetPFCTR (bool set)
{
    if (set) 
    {
        *_pDMA_SCR |= DMA_SCR_PFCTRL;
    }
    else
    {
        *_pDMA_SCR &= ~DMA_SCR_PFCTRL;
    }
}

void DMA_Stream::SetDirection_MemoryToPeripheral()
{
       *_pDMA_SCR &= ~DMA_SCR_DIR_CLEARMASK;
       *_pDMA_SCR |= DMA_SCR_DIR_M2P;
}
void DMA_Stream::SetDirection_PeripheralToMemory()
{
       *_pDMA_SCR &= ~DMA_SCR_DIR_CLEARMASK;
       *_pDMA_SCR |= DMA_SCR_DIR_P2M;
}
void DMA_Stream::SetDirection_MemoryToMemory()
{
       *_pDMA_SCR &= ~DMA_SCR_DIR_CLEARMASK;
       *_pDMA_SCR |= DMA_SCR_DIR_M2M;
}

void DMA_Stream::SetCircularMode(bool set)
{
    if (set) 
    {
       *_pDMA_SCR |= DMA_SCR_CIRC;
    }
    else 
    {
       *_pDMA_SCR &= ~DMA_SCR_CIRC;
    }
}

void DMA_Stream::SetMemoryIncrementMode(bool set)
{
    if (set) 
    {
       *_pDMA_SCR |= DMA_SCR_MINC;
    }
    else 
    {
       *_pDMA_SCR &= ~DMA_SCR_MINC;
    }
}
void DMA_Stream::SetPeripheralIncrementMode(bool set)
{
    if (set) 
    {
       *_pDMA_SCR |= DMA_SCR_PINC;
    }
    else 
    {
       *_pDMA_SCR &= ~DMA_SCR_PINC;
    }
}


void DMA_Stream::SetPeripheralSize_8bits()
{
    *_pDMA_SCR |= DMA_SCR_PSIZE_8;
}
void DMA_Stream::SetPeripheralSize_16bits()
{
    *_pDMA_SCR |= DMA_SCR_PSIZE_16;
}
void DMA_Stream::SetPeripheralSize_32bits()
{
    *_pDMA_SCR |= DMA_SCR_PSIZE_32;
}

void DMA_Stream::SetMemorySize_8bits()
{
    *_pDMA_SCR |= DMA_SCR_MSIZE_8;
}
void DMA_Stream::SetMemorySize_16bits()
{
    *_pDMA_SCR |= DMA_SCR_MSIZE_16;
}
void DMA_Stream::SetMemorySize_32bits()
{
    *_pDMA_SCR |= DMA_SCR_MSIZE_32;
}

void DMA_Stream::SetPeripheralIncOffsetSize(bool set)
{
    if (set) 
    {
       *_pDMA_SCR |= DMA_SCR_PINCOS;
    }
    else 
    {
       *_pDMA_SCR &= ~DMA_SCR_PINCOS;
    }
}


void DMA_Stream::SetPriorityLow()
{
    *_pDMA_SCR |= DMA_SCR_PL_LOW;
}
void DMA_Stream::SetPriorityMedium()
{
    *_pDMA_SCR |= DMA_SCR_PL_MED;
}
void DMA_Stream::SetPriorityHigh()
{
    *_pDMA_SCR |= DMA_SCR_PL_HI;

}
void DMA_Stream::SetPriorityVeryHigh()
{
    *_pDMA_SCR |= DMA_SCR_PL_VHI;
}


void DMA_Stream::EnableDoubleBufferMode (bool enable)
{
    if (enable) 
    {
       *_pDMA_SCR |= DMA_SCR_DBM;
    }
    else 
    {
       *_pDMA_SCR &= ~DMA_SCR_DBM;
    }
}


void DMA_Stream::SetPBURST_INCR4()
{
    *_pDMA_SCR &= ~DMA_SCR_PBURST_CLEARMASK;
    *_pDMA_SCR |= DMA_SCR_PBURST_INCR4;
}

void DMA_Stream::SetPBURST_INCR8()
{
    *_pDMA_SCR &= ~DMA_SCR_PBURST_CLEARMASK;
    *_pDMA_SCR |= DMA_SCR_PBURST_INCR8;
}

void DMA_Stream::SetPBURST_INCR16()
{
    *_pDMA_SCR &= ~DMA_SCR_PBURST_CLEARMASK;
    *_pDMA_SCR |= DMA_SCR_PBURST_INCR16;
}

void DMA_Stream::SetMBURST_INCR4()
{
    *_pDMA_SCR &= ~DMA_SCR_MBURST_CLEARMASK;
    *_pDMA_SCR |= DMA_SCR_MBURST_INCR4;
}

void DMA_Stream::SetMBURST_INCR8()
{
    *_pDMA_SCR &= ~DMA_SCR_MBURST_CLEARMASK;
    *_pDMA_SCR |= DMA_SCR_MBURST_INCR8;
}

void DMA_Stream::SetMBURST_INCR16()
{
    *_pDMA_SCR &= ~DMA_SCR_MBURST_CLEARMASK;
    *_pDMA_SCR |= DMA_SCR_MBURST_INCR16;
}



////////////////////////////////////////////////////////


void DMA_Stream::SetPeripheralAddress(uint32_t addr)
{
    *_pDMA_SPAR = addr;
}
void DMA_Stream::SetMemory0Address(uint32_t addr)
{
    *_pDMA_SM0AR = addr;
}
void DMA_Stream::SetMemory1Address(uint32_t addr)
{
    *_pDMA_SM0AR = addr;
}

void DMA_Stream::SetNumberOfData(uint16_t length)
{
    *_pDMA_SNDTR = length;
}



IRQn_Type DMA1::nvicIrqNumbers[8] =
{ IRQn_DMA1_Stream0, IRQn_DMA1_Stream1, IRQn_DMA1_Stream2, IRQn_DMA1_Stream3,
  IRQn_DMA1_Stream4, IRQn_DMA1_Stream5, IRQn_DMA1_Stream6, IRQn_DMA1_Stream7
};

IRQn_Type DMA2::nvicIrqNumbers[8] =
{ IRQn_DMA2_Stream0, IRQn_DMA2_Stream1, IRQn_DMA2_Stream2, IRQn_DMA2_Stream3,
  IRQn_DMA2_Stream4, IRQn_DMA2_Stream5, IRQn_DMA2_Stream6, IRQn_DMA2_Stream7
};



#endif

