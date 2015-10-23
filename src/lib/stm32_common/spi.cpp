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


#include "spi_cpp.h"

#ifdef USE_SPI

#ifdef __cplusplus
extern "C" {
#endif


void SPI1_IRQHandler() 
{
    SPI1::GetInstance()->HandleInterrupt();
}

#if defined(STM32F10X_MD) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD)\
        || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL)\
        ||defined(STM32F4)
void SPI2_IRQHandler() 
{
    SPI2::GetInstance()->HandleInterrupt();
}

#endif 

#if defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL)\
        ||defined(STM32F4)

void SPI3_IRQHandler() 
{
    SPI3::GetInstance()->HandleInterrupt();
}

#endif


#ifdef __cplusplus
}
#endif


void SPI::HandleInterrupt ()
{
    if (_irqHandler)
    {
        _irqHandler->Handle(this, this->IsCRCError(), this->IsOverrun(), this->IsModeFault(), this->IsTXE(), this->IsRXNE());
    }

    this->ClearCRCError();
    this->ClearOverrun();
    this->ClearModeFault();
    this->ClearTXE();
    this->ClearRXNE();
}



SPI::SPI(volatile uint32_t* pSPI_CR1, 
         volatile uint32_t* pSPI_CR2,
         volatile uint32_t* pSPI_SR, 
         volatile uint32_t* pSPI_DR,
         volatile uint32_t* pSPI_CRCPR, 
         volatile uint32_t* pSPI_RXCRCR,
         volatile uint32_t* pSPI_TXCRCR, 
         IRQn_Type irqNo, 
         volatile uint32_t* pRCCEnableReg,
         volatile uint32_t* pRCCResetReg, 
         uint32_t           rccBit) : Peripheral (pRCCEnableReg, pRCCResetReg, rccBit)

{
    _pSPI_CR1 = pSPI_CR1;
    _pSPI_CR2 = pSPI_CR2;
    _pSPI_SR = pSPI_SR;
    _pSPI_DR = pSPI_DR;
    _pSPI_CRCPR = pSPI_CRCPR;
    _pSPI_RXCRCR = pSPI_RXCRCR;
    _pSPI_TXCRCR = pSPI_TXCRCR;
    _irqHandler = 0;
    _irqNo = irqNo;
    _startedSending = false;
    _ssPin = 0;
}

void SPI::Enable(bool enable)
{
    if (enable)
    {
        EnablePeripheralClock(true);

        *_pSPI_CR1 |= SPI_CR1_SPE_ENABLED;
        _startedSending = false;
    }
    else
    {
        *_pSPI_CR1 &= ~SPI_CR1_SPE_ENABLED;
        EnablePeripheralClock(false);
    }

}


void SPI::SetClockPhaseFirst()
{
    *_pSPI_CR1 |= SPI_CR1_CPHA_FIRST;
}

void SPI::SetClockPhaseSecond()
{
    *_pSPI_CR1 |= SPI_CR1_CPHA_SECOND;
}
void SPI::SetClockPolarity0()
{
    *_pSPI_CR1 |= SPI_CR1_CPOL_0;
}
void SPI::SetClockPolarity1()
{
    *_pSPI_CR1 |= SPI_CR1_CPOL_1;
}
void SPI::SetMaster(bool isMaster)
{
    if (isMaster)
    {
        *_pSPI_CR1 |= SPI_CR1_MASTER;
    }
    else
    {
        *_pSPI_CR1 &= ~SPI_CR1_MASTER;
    }
}

void SPI::SetBaudRate(SPI_BAUD_RATE rate)
{
    *_pSPI_CR1  &= ~(3<<3);
    *_pSPI_CR1 |= rate;
}

void SPI::SetBaudRateDiv2()
{
    SetBaudRate (SPI_BAUD_RATE_2);
}
void SPI::SetBaudRateDiv4()
{
    SetBaudRate (SPI_BAUD_RATE_4);
}
void SPI::SetBaudRateDiv8()
{
    SetBaudRate (SPI_BAUD_RATE_8);
}
void SPI::SetBaudRateDiv16()
{
    SetBaudRate (SPI_BAUD_RATE_16);
}
void SPI::SetBaudRateDiv32()
{
    SetBaudRate (SPI_BAUD_RATE_32);
}
void SPI::SetBaudRateDiv64()
{
    SetBaudRate (SPI_BAUD_RATE_64);
}
void SPI::SetBaudRateDiv128()
{
    SetBaudRate (SPI_BAUD_RATE_128);
}
void SPI::SetBaudRateDiv256()
{
    SetBaudRate (SPI_BAUD_RATE_256);
}


void SPI::SetFrameFormatMSBFirst()
{
    *_pSPI_CR1 &= ~SPI_CR1_LSBFIRST_ON;
}
void SPI::SetFrameFormatLSBFirst()
{
    *_pSPI_CR1 |= SPI_CR1_LSBFIRST_ON;
}

void SPI::SetSSM(bool isSSM_Enabled)
{
    if (isSSM_Enabled)
    {
        *_pSPI_CR1 |= SPI_CR1_SSM;
    }
    else
    {
        *_pSPI_CR1 &= ~SPI_CR1_SSM;
    }
}

void SPI::SetSSI (bool set)
{
    if (set)
    {
        *_pSPI_CR1 |= SPI_CR1_SSI;
    }
    else
    {
        *_pSPI_CR1 &= ~SPI_CR1_SSI;
    }

}

void SPI::SetFullDuplex(bool isFullDuplex)
{
    if (isFullDuplex)
    {
        *_pSPI_CR1  &= ~SPI_CR1_BIDIMODE;
    }
    else
    {
        *_pSPI_CR1  |= SPI_CR1_BIDIMODE;
    }

}

void SPI::SetFullDuplexRxOnly(bool set)
{
    if (set)
    {
        *_pSPI_CR1  &= ~SPI_CR1_RXONLY;
    }
    else
    {
        *_pSPI_CR1  |= SPI_CR1_RXONLY;
    }

}


void SPI::SetDFF_8bit()
{
    *_pSPI_CR1  &= ~SPI_CR1_DFF_16_BIT;
}
void SPI::SetDFF_16bit()
{
    *_pSPI_CR1  |= SPI_CR1_DFF_16_BIT;
}
void SPI::SetCRCNext (bool isCRCnext)
{
    if (isCRCnext)
    {
        *_pSPI_CR1  |=  SPI_CR1_CRCNEXT;
    }
    else
    {
        *_pSPI_CR1  &=  ~SPI_CR1_CRCNEXT;
    }
}
void SPI::EnableCRC()
{
    *_pSPI_CR1  |=  SPI_CR1_CRCEN;
}
void SPI::DisableCRC()
{
    *_pSPI_CR1  &=  ~SPI_CR1_CRCEN;
}

void SPI::SetBidirectionalReceiveOnly()
{
    *_pSPI_CR1  &=  ~SPI_CR1_BIDIOE;

}
void SPI::SetBidirectionalTransmitOnly()
{
    *_pSPI_CR1  |=  SPI_CR1_BIDIOE;
}


void SPI::Enable_RX_TX_DMA (bool rxDmaEnable, bool txDmaEnable)
{
    if (rxDmaEnable)
    {
        *_pSPI_CR2 |= SPI_CR2_RXDMAEN;
    }
    else
    {
        *_pSPI_CR2 &= ~SPI_CR2_RXDMAEN;
    }
    if (txDmaEnable)
    {
        *_pSPI_CR2 |= SPI_CR2_TXDMAEN;
    }
    else
    {
        *_pSPI_CR2 &= ~SPI_CR2_TXDMAEN;
    }
}

void SPI::EnableSSOE (bool enable)
{
    if (enable)
    {
        *_pSPI_CR2 |= SPI_CR2_SSOE;
    }
    else
    {
        *_pSPI_CR2 &= ~SPI_CR2_SSOE;
    }
}

void SPI::_EnableInterrupt(uint16_t intMask, bool enable) 
{
    if (enable)
    {
        *_pSPI_CR2 |= intMask;
        NVIC_SetEnable(_irqNo);
    }
    else
    {
        *_pSPI_CR2 &= ~intMask;
    }

}

void SPI::EnableErrorInterrupt (bool enable)
{
    _EnableInterrupt (SPI_CR2_ERRIE, enable);
}
void SPI::EnableRXNEInterrupt (bool enable)
{
    _EnableInterrupt (SPI_CR2_RXNEIE, enable);
}
void SPI::EnableTXEInterrupt (bool enable)
{
    _EnableInterrupt (SPI_CR2_TXEIE, enable);
}

bool SPI::IsBusy()
{
    return *_pSPI_SR & SPI_SR_BSY;
}
bool SPI::IsOverrun()
{
    return *_pSPI_SR & SPI_SR_OVR;
}
bool SPI::IsModeFault()
{
    return *_pSPI_SR & SPI_SR_MODF;
}
bool SPI::IsCRCError()
{
    return *_pSPI_SR & SPI_SR_CRCERR;
}
bool SPI::IsTXE()
{
    return *_pSPI_SR & SPI_SR_TXE;
}
bool SPI::IsRXNE()
{
    return *_pSPI_SR & SPI_SR_RXNE;
}

void SPI::ClearBusy()
{
    *_pSPI_SR &= ~SPI_SR_BSY;
}
void SPI::ClearOverrun()
{
    *_pSPI_SR &= ~SPI_SR_OVR;
}
void SPI::ClearModeFault()
{
    *_pSPI_SR &= ~SPI_SR_MODF;
}
void SPI::ClearCRCError()
{
    *_pSPI_SR &= ~SPI_SR_CRCERR;
}
void SPI::ClearTXE()
{
    *_pSPI_SR &= ~SPI_SR_TXE;
}
void SPI::ClearRXNE()
{
    *_pSPI_SR &= ~SPI_SR_RXNE;
}

bool SPI::IsError()
{
    return IsOverrun() || IsModeFault();
}


void SPI::Initialize(bool isMaster, bool isFullDuplex, SPI_BAUD_RATE baudRate, bool isClockPhase2,
        bool isClockPolarity1,  bool isLSBFirst, bool isSetSSM, bool is16Bit)
{
    if (is16Bit) SetDFF_16bit();

    Enable(true);

    isClockPhase2 ? SetClockPhaseSecond() : SetClockPhaseFirst();
    isClockPolarity1 ? SetClockPolarity1() : SetClockPolarity0();
    isLSBFirst ? SetFrameFormatLSBFirst() : SetFrameFormatMSBFirst();
    SetSSM (isSetSSM);
    if (isMaster)
    {
        SetBaudRate (baudRate);
        if (isSetSSM)
        {
            SetSSI(true);
        }
    }
    else
    {
        SetSSI(false);
    }


    SetFullDuplex(isFullDuplex);
    SetMaster(isMaster);
}



void SPI::WaitTXE()
{
    while (!IsTXE())
        ;
}

void SPI::WaitRXNE()
{
    while (!IsRXNE())
        ;
}

void SPI::WaitNotBSY()
{
    while (IsBusy())
        ;
}



uint8_t SPI::TransmitByte (uint8_t byte)
{
    WaitTXE();
    SendByte (byte);
    WaitRXNE();
    return ReceiveByte();
}

uint16_t SPI::TransmitWord (uint16_t word)
{
    WaitTXE();
    SendWord (word);
    WaitRXNE();
    return ReceiveWord();
}


uint8_t SPI::TransmitRegister (uint8_t reg, uint8_t data)
{
	TransmitByte(reg);
	return TransmitByte(data);
}

uint16_t SPI::TransmitRegister (uint16_t reg, uint16_t data)
{
	TransmitWord(reg);
	return TransmitWord(data);
}


void SPI::SendByte (uint8_t byte)
{
    *_pSPI_DR = byte;

}

void SPI::SendWord (uint16_t word)
{
    *_pSPI_DR = word;

}

uint8_t SPI::ReceiveByte()
{
    return *_pSPI_DR;
}

uint16_t SPI::ReceiveWord()
{
    return *_pSPI_DR;
}


void SPI::SetSlaveSelectLow()
{
    if (_ssPin)
    {
        _ssPin->Reset();
    }
}

void SPI::SetSlaveSelectHigh()
{
    if (_ssPin)
    {
        _ssPin->Set();
    }
}

#endif
