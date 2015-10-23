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


#include "usart_cpp.h"

#ifdef USE_USART

#include "gpio_cpp.h"


#ifdef __cplusplus
extern "C"
{
#endif

void USART1_IRQHandler()
{
    USART1::GetInstance()->HandleInterrupt();
}

void USART2_IRQHandler()
{
    USART2::GetInstance()->HandleInterrupt();
}



void USART3_IRQHandler()
{
    USART3::GetInstance()->HandleInterrupt();
}


void USART6_IRQHandler()
{
    USART6::GetInstance()->HandleInterrupt();
}




#ifdef __cplusplus
}
#endif

USART::USART(volatile uint32_t* pUSART_SR, volatile uint32_t* pUSART_DR,
            volatile uint32_t* pUSART_BRR, volatile uint32_t* pUSART_CR1,
            volatile uint32_t* pUSART_CR2, volatile uint32_t* pUSART_CR3,
            IRQn_Type irqNo, bool isAPB2,
            volatile uint32_t* pRCCEnableReg,
            volatile uint32_t* pRCCResetReg, 
            uint32_t           rccBit) : Peripheral (pRCCEnableReg, pRCCResetReg, rccBit)
{
        _pUSART_SR = pUSART_SR;
        _pUSART_DR = pUSART_DR;
        _pUSART_BRR = pUSART_BRR;
        _pUSART_CR1 = pUSART_CR1;
        _pUSART_CR2 = pUSART_CR2;
        _pUSART_CR3 = pUSART_CR3;
        _irqNo = irqNo;
        _isAPB2 = isAPB2;
        //_dmaRxChannel = dmaRxChannel;
        //_dmaTxChannel = dmaTxChannel;
}

#define USART_DIV(_PCLK_, _BAUD_)                  (((_PCLK_)*25)/(2*(_BAUD_)))
#define USART_DIVMANT(_PCLK_, _BAUD_)              (USART_DIV((_PCLK_), (_BAUD_))/100)
#define USART_DIVFRAQ(_PCLK_, _BAUD_)              (((USART_DIV((_PCLK_), (_BAUD_)) - (USART_DIVMANT((_PCLK_), (_BAUD_)) * 100)) * 16 + 50) / 100)
#define USART_BRR(_PCLK_, _BAUD_)                  ((USART_DIVMANT((_PCLK_), (_BAUD_)) << 4)|(USART_DIVFRAQ((_PCLK_), (_BAUD_)) & 0x0F))

void USART::SetBaudRate(uint32_t baudRate)
{
    uint32_t integerdivider = 0;
    uint32_t apbclock = 0;
    uint32_t rate_val = 0;


    if (_isAPB2)
    {
        apbclock = RCC_GetAPB2_CLK();
    }
    else
    {
        apbclock = RCC_GetAPB1_CLK();
    }

#if defined(STM32F4) || defined(STM32F2)
    uint8_t k = 2;
    *_pUSART_CR1 |= USART_CR1_OVER8;
#elif defined(STM32F1)
    uint8_t k = 4;
#else
#error "chip type undefined"
#endif

    integerdivider = ((25 * apbclock) / (k * baudRate));

    rate_val = (integerdivider / 100) << 4;

    uint32_t fractionaldivider = integerdivider - (100 * (rate_val >> 4));

    rate_val |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);

    *_pUSART_BRR = USART_BRR(apbclock, baudRate); //(uint16_t)rate_val;
    
}

void USART::HandleInterrupt()
{
    if (_irqHandler)
    {
        USART_IRQ_Info  info;
        info.isCTS = IsCTS();
        info.isFrameError = IsFramingError();
        info.isIDLE = IsIDLE();
        info.isLBD = IsLBD();
        info.isNoiseError = IsNoiseError();
        info.isOverrun = IsOverrun();
        info.isPE = IsParityError();
        info.isRXNE = IsRXNE();
        info.isTC = IsTC();
        info.isTXE = IsTXE();
        _irqHandler->Handle(this, info);
    }

    this->ClearError();
}

void USART::ClearError()
{

}



void USART::SendByte (uint16_t data)
{
    while (!IsTXE())
        ;

    *_pUSART_DR = (data & 0x01ff);

}

//LSB
void USART::SendWord (uint16_t data)
{
    for (uint8_t i = 0; i < 2; i++)
    {
        while (!IsTXE())
            ;
        
        *_pUSART_DR = (data>>(i*8) & 0x1ff);
    }
   
}



uint16_t USART::Receive()
{
    while (!IsRXNE())
        ;

    return *_pUSART_DR & 0x01ff;
}

void USART::ClearCTS()
{
    *_pUSART_SR &= ~ USART_SR_CTS;
}
void USART::ClearLBD()
{
    *_pUSART_SR &= ~ USART_SR_LBD;
}
void USART::ClearTC()
{
    *_pUSART_SR &= ~ USART_SR_TC;
}
void USART::ClearRXNE()
{
    *_pUSART_SR &= ~ USART_SR_RXNE;
}

bool USART::IsCTS()
{
    return (*_pUSART_SR & USART_SR_CTS);
}
bool USART::IsLBD()
{
    return (*_pUSART_SR & USART_SR_LBD);

}
bool USART::IsTXE()
{
    return (*_pUSART_SR & USART_SR_TXE);

}

void USART::WaitTXE()
{
    while (!IsTXE())
        ;
}

bool USART::IsTC()
{
    return (*_pUSART_SR & USART_SR_TC);
}

bool USART::IsRXNE()
{
    return (*_pUSART_SR & USART_SR_RXNE);
}

void USART::WaitRXNE()
{
    while (!IsRXNE())
        ;
}



bool USART::IsIDLE()
{
    return (*_pUSART_SR & USART_SR_IDLE);
}
bool USART::IsOverrun()
{
    return (*_pUSART_SR & USART_SR_ORE);
}
bool USART::IsNoiseError()
{
    return (*_pUSART_SR & USART_SR_NE);
}
bool USART::IsFramingError()
{
    return (*_pUSART_SR & USART_SR_FE);
}
bool USART::IsParityError()
{
    return (*_pUSART_SR & USART_SR_PE);
}


void USART::Enable(bool enable)
{
    if (enable)
    {
        EnablePeripheralClock(true);

        *_pUSART_CR1 |= USART_CR1_UE;

    }
    else
    {
        *_pUSART_CR1 &= ~USART_CR1_UE;
        EnablePeripheralClock(false);
    }
}



void USART::SetWordLength_9bit()
{
    *_pUSART_CR1 |= USART_CR1_M_9bits;
}
void USART::SetWordLength_8bit()
{
    *_pUSART_CR1 &= ~USART_CR1_M_9bits;
}
void USART::SetWakeupIdleLine()
{
    *_pUSART_CR1 &= ~USART_CR1_WAKE_ADDRESS_MARK;
}
void USART::SetWakeupAddressMark()
{
    *_pUSART_CR1 |= USART_CR1_WAKE_ADDRESS_MARK;
}
void USART::SetParityOdd()
{
    *_pUSART_CR1 |= USART_CR1_PCE;
    *_pUSART_CR1 |= USART_CR1_PS;
}
void USART::SetParityEven()
{
    *_pUSART_CR1 |= USART_CR1_PCE;
    *_pUSART_CR1 &= ~USART_CR1_PS;
}
void USART::EnableTransmitter(bool enable)
{
    if (enable)
    {
        *_pUSART_CR1 |= USART_CR1_TE;
    }
    else
    {
        *_pUSART_CR1 &= ~USART_CR1_TE;
    }

}
void USART::EnableReceiver(bool enable)
{
    if (enable)
    {
        *_pUSART_CR1 |= USART_CR1_RE;
    }
    else
    {
        *_pUSART_CR1 &= ~USART_CR1_RE;
    }

}
void USART::SetRWU(bool set)
{
    if (set)
    {
        *_pUSART_CR1 |= USART_CR1_RWU;
    }
    else
    {
        *_pUSART_CR1 &= ~USART_CR1_RWU;
    }

}
void USART::SendBreak()
{
    *_pUSART_CR1 |= USART_CR1_SBK;
}

void USART::EnableLineMode(bool enable)
{
    if (enable)
    {
        *_pUSART_CR2 |= USART_CR2_LINEN;
    }
    else
    {
        *_pUSART_CR2 &= ~USART_CR2_LINEN;
    }

}
void USART::SetStopBits(STOP_BIT stopBit)
{
    *_pUSART_CR2 &= ~(0x3 << 12);
    *_pUSART_CR2 |= (uint16_t) stopBit;
}

void USART::EnableSynchronousMode(bool clockPinEnable, bool isPolarityHigh, bool isPhaseSecond, bool isLBCL)
{
    if (clockPinEnable)
    {
        *_pUSART_CR2 |= USART_CR2_CLKEN;
    }
    else
    {
        *_pUSART_CR2 &= ~USART_CR2_CLKEN;
    }


    if (isPolarityHigh)
    {
        *_pUSART_CR2 |= USART_CR2_CPOL_HIGH;
    }
    else
    {
        *_pUSART_CR2 &= ~USART_CR2_CPOL_HIGH;
    }
    if (isPhaseSecond)
    {
        *_pUSART_CR2 |= USART_CR2_CPHA_SECOND;
    }
    else
    {
        *_pUSART_CR2 &= ~USART_CR2_CPHA_SECOND;
    }

    if (isLBCL)
    {
        *_pUSART_CR2 |= USART_CR2_LBCL;
    }
    else
    {
        *_pUSART_CR2 &= ~USART_CR2_LBCL;
    }

}
void USART::SetLBDL10()
{
    *_pUSART_CR2 &= ~USART_CR2_LBDL_11_BIT;
}
void USART::SetLBDL11()
{
    *_pUSART_CR2 |= USART_CR2_LBDL_11_BIT;
}
void USART::SetNodeAddr(uint8_t addr)
{
    *_pUSART_CR2 |= (addr & 0xf);
}


void USART::EnableCTS(bool enable)
{
    if (enable)
    {
        *_pUSART_CR3 |= USART_CR3_CTSE;
    }
    else
    {
        *_pUSART_CR3 &= ~USART_CR3_CTSE;
    }

}
void USART::EnableRTS(bool enable)
{
    if (enable)
    {
        *_pUSART_CR3 |= USART_CR3_RTSE;
    }
    else
    {
        *_pUSART_CR3 &= ~USART_CR3_RTSE;
    }

}
void USART::EnableDMAT(bool enable)
{
    if (enable)
    {
        *_pUSART_CR3 |= USART_CR3_DMAT;
    }
    else
    {
        *_pUSART_CR3 &= ~USART_CR3_DMAT;
    }

}
void USART::EnableDMAR(bool enable)
{
    if (enable)
    {
        *_pUSART_CR3 |= USART_CR3_DMAR;
    }
    else
    {
        *_pUSART_CR3 &= ~USART_CR3_DMAR;
    }

}
void USART::EnableSmartCardMode(bool enable, bool enableNack)
{
    if (enable)
    {
        *_pUSART_CR3 |= USART_CR3_SCEN;
    }
    else
    {
        *_pUSART_CR3 &= ~USART_CR3_SCEN;
    }
    if (enableNack)
    {
        *_pUSART_CR3 |= USART_CR3_NACK;
    }
    else
    {
        *_pUSART_CR3 &= ~USART_CR3_NACK;
    }


}

void USART::EnableHalfDuplexMode(bool enable)
{
    if (enable)
    {
        *_pUSART_CR3 |= USART_CR3_HDSEL;
    }
    else
    {
        *_pUSART_CR3 &= ~USART_CR3_HDSEL;
    }

}

void USART::EnableIrDA(bool enable, bool lowPower)
{
    if (enable)
    {
        *_pUSART_CR3 |= USART_CR3_IREN;
    }
    else
    {
        *_pUSART_CR3 &= ~USART_CR3_IREN;
    }

    if (lowPower)
    {
        *_pUSART_CR3 |= USART_CR3_IRLP;
    }
    else
    {
        *_pUSART_CR3 &= ~USART_CR3_IRLP;
    }

}



void USART::EnableInterrupt_PE(bool enable)
{
    _EnableInterrupt(USART_CR1_PEIE, _pUSART_CR1, enable);

}
void USART::EnableInterrupt_TXE(bool enable)
{
    _EnableInterrupt(USART_CR1_TXEIE, _pUSART_CR1, enable);

}
void USART::EnableInterrupt_TC(bool enable)
{
    _EnableInterrupt(USART_CR1_TCIE, _pUSART_CR1, enable);
}
void USART::EnableInterrupt_RXNE(bool enable)
{
    _EnableInterrupt(USART_CR1_RXNEIE, _pUSART_CR1, enable);
}
void USART::EnableInterrupt_IDLE(bool enable)
{
    _EnableInterrupt(USART_CR1_IDLEIE, _pUSART_CR1, enable);

}

void USART::EnableInterrupt_ERROR(bool enable)
{
    _EnableInterrupt(USART_CR3_EIE, _pUSART_CR3, enable);
}

void USART::EnableInterrupt_LBDIE(bool enable)
{
    _EnableInterrupt(USART_CR2_LBDIE, _pUSART_CR2, enable);

}

void USART::EnableInterrupt_CTS(bool enable)
{
    _EnableInterrupt(USART_CR3_CTSIE, _pUSART_CR3, enable);
}


void USART::_EnableInterrupt(uint16_t intMask, volatile uint32_t* reg, bool enable)
{
    if (enable)
    {
        *reg |= intMask;
        NVIC_SetEnable(_irqNo);
    }
    else
    {
        *_pUSART_CR2 &= ~intMask;
    }

}


void USART::ConfigureDMATX (void* data_ptr, uint32_t data_size, DMA_IRQ_Handler* dmaTxHandler, DMA_Stream* stream, DMA_CHANNEL channel)
{
    DMA1* dma1 = DMA1::GetInstance();
    if (!dma1->IsClockEnabled())
    {
        dma1->EnablePeripheralClock(true);
    }


    dma1->SetIRQHandler(dmaTxHandler);


    stream->SetPeripheralAddress ((uint32_t)_pUSART_DR);
    stream->SetMemory0Address((uint32_t)data_ptr);
    stream->SetDirection_MemoryToPeripheral();
    stream->SetMemorySize_8bits();
    stream->SetPeripheralSize_8bits();
    stream->SetNumberOfData(data_size);
    stream->SetMemoryIncrementMode(true);
    stream->SetPriorityHigh();

    if (dmaTxHandler)
    {
        stream->EnableTransferCompleteInterrupt(true);
        stream->EnableHalfTransferInterrupt(true);
        stream->EnableTransferErrorInterrupt(true);
    }
    stream->EnableStream(true);
    EnableDMAT(true);

}
void USART::ConfigureDMARX (void* data_ptr, uint32_t data_size, DMA_IRQ_Handler* dmaRxHandler, DMA_Stream* stream, DMA_CHANNEL channel)
{
    _dmaTxHandler = dmaRxHandler;
    DMA1* dma1 = DMA1::GetInstance();
    if (!dma1->IsClockEnabled())
    {
        dma1->EnablePeripheralClock(true);
    }
    dma1->SetIRQHandler(dmaRxHandler);

    stream->SetPeripheralAddress ((uint32_t)_pUSART_DR);
    stream->SetMemory0Address((uint32_t)data_ptr);
    stream->SetDirection_PeripheralToMemory();
    stream->SetMemorySize_8bits();
    stream->SetPeripheralSize_8bits();
    stream->SetNumberOfData(data_size);
    stream->SetMemoryIncrementMode(true);
    stream->SetPriorityHigh();
    if (dmaRxHandler)
    {
        stream->EnableTransferCompleteInterrupt(true);
        stream->EnableHalfTransferInterrupt(true);
        stream->EnableTransferErrorInterrupt(true);
        stream->EnableStream(true);
    }
    EnableDMAR(true);

}



#endif


