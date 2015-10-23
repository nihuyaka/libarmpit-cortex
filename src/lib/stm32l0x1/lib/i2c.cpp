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

#include "i2c_cpp.h"

#ifdef USE_I2C

#include "gpio_cpp.h"

#ifdef __cplusplus
extern "C"
{
#endif

void I2C1_EV_IRQHandler()
{
    I2C1::GetInstance()->HandleEventInterrupt();
}

void I2C1_ER_IRQHandler()
{

    I2C1::GetInstance()->HandleErrorInterrupt();

}


#if !defined(STM32F10X_LD) && !defined(STM32F10X_LD_VL)

void I2C2_EV_IRQHandler()
{
    I2C2::GetInstance()->HandleEventInterrupt();
}

void I2C2_ER_IRQHandler()
{
    I2C2::GetInstance()->HandleErrorInterrupt();

}

#endif

#ifdef __cplusplus
}
#endif

void I2C::HandleErrorInterrupt()
{
    if (_irqErrorHandler)
    {
        I2C_IRQ_Error_Info info;

        if (IsBusError())
        {
            info.BusError = true;
            ClearBusError();
        }

        if (IsARLO())
        {
            info.ArbitrationLoss = true;
            ClearARLO();
        }

        if (IsAF())
        {
            info.AckFailure = true;
            ClearAF();
        }

        if (IsOVR())
        {
            info.OverrunUnderrun = true;
            ClearOVR();
        }

        if (IsPECError())
        {
            info.PECError = true;
            ClearPECERR();
        }

        if (IsTimeout())
        {
            info.Timeout = true;
            ClearTimeout();
        }

        if (IsSMBAlert())
        {
            info.SMBAlert = true;
            ClearSMBAlert();
        }

        _irqErrorHandler->HandleErrorInterrupt(this, info);
    }

}

void I2C::HandleEventInterrupt()
{
    if (_irqEventHandler)
    {
        I2C_IRQ_Event_Info info;

        info.StartBitSent = IsSB();
        info.Addr10HeaderSent = IsADD10();
        info.AddressSentMatched = IsADDR();
        info.ByteTransferFinished = IsBTF();
        info.RxNE = IsRxNE();
        info.TxE = IsTxE();
        info.StopBitReceived = IsStOPF();

        _irqEventHandler->HandleEventInterrupt(this, info);
    }

}

void I2C::Initialize (uint32_t clockSpeed, bool isDuty16_9, bool isFmMode, bool initializeGPIO)
{
    Enable(false);
    SetSoftwareReset(true);
    SetSoftwareReset(false);
    EnablePeripheralClock(true);
    SetClock(clockSpeed, isDuty16_9, isFmMode);
    if (initializeGPIO)
    {
        InitGPIO();
    }
    Enable(true);
    _stuckBUSY = false;

}

void I2C::Reset(void)
{
    Enable(false);
    EnablePeripheralClock(false);
}

void I2C::Enable (bool enable)
{
    //EnableClock(enable);

    if (enable)
    {
        *_pI2C_CR1 &= ~I2C_CR1_PE;
        *_pI2C_CR1 |= I2C_CR1_PE;
    }
    else
    {
        *_pI2C_CR1 &= ~I2C_CR1_PE;
    }

}


void I2C::SetClock(uint32_t clockSpeed, bool isDuty16_9, bool isFmMode)
{
    uint32_t apb1_clk = RCC_GetAPB1_CLK();
    uint16_t result;

    *_pI2C_CR2 |= (apb1_clk / 1000000);

    if (clockSpeed <= 100000)
    {
        result = (uint16_t)(apb1_clk / (clockSpeed*2));
        if (result < 0x04)
        {
            result = 0x04;
        }

        *_pI2C_CCR |= result;

        *_pI2C_TRISE = apb1_clk / 1000000 + 1;
    }
    else // clockSpeed >100000
    {
        if (!isDuty16_9)
        {
            result = (uint16_t)(apb1_clk / (clockSpeed * 3));
        }
        else
        {
            result = (uint16_t)(apb1_clk / (clockSpeed * 25));
            result |= I2C_CCR_DUTY;
        }

        if ((result & 0x0fff) == 0)
        {
            result |= (uint16_t)0x0001;        /* Set minimum allowed value */
        }

        *_pI2C_CCR |= result;

        if (isFmMode)
        {
            SetModeFm();
        }

        *_pI2C_TRISE = (uint16_t)((((apb1_clk / 1000000) * 300) / 1000) + 1);
    }


}

void I2C::SetSoftwareReset (bool on)
{
    if (on)
    {
        *_pI2C_CR1 |= I2C_CR1_SWRST;
    }
    else
    {
        *_pI2C_CR1 &= ~I2C_CR1_SWRST;
    }
}

void I2C::SetSMBAlert (bool on)
{
    if (on)
    {
        *_pI2C_CR1 |= I2C_CR1_ALERT;
    }
    else
    {
        *_pI2C_CR1 &= ~I2C_CR1_ALERT;
    }

}


void I2C::SetPEC (bool on)
{
    if (on)
    {
        *_pI2C_CR1 |= I2C_CR1_PEC;
    }
    else
    {
        *_pI2C_CR1 &= ~I2C_CR1_PEC;
    }

}

void I2C::SetPOS (bool on)
{
    if (on)
    {
        *_pI2C_CR1 |= I2C_CR1_POS;
    }
    else
    {
        *_pI2C_CR1 &= ~I2C_CR1_POS;
    }

}

void I2C::EnableACK (bool on)
{
    if (on)
    {
        *_pI2C_CR1 |= I2C_CR1_ACK;
    }
    else
    {
        *_pI2C_CR1 &= ~I2C_CR1_ACK;
    }

}

void I2C::SendStop (bool on)
{
    if (on)
    {
        *_pI2C_CR1 |= I2C_CR1_STOP;
    }
    else
    {
        *_pI2C_CR1 &= ~I2C_CR1_STOP;
    }

}

void I2C::SendStart (bool on)
{
    if (on)
    {
        *_pI2C_CR1 |= I2C_CR1_START;
    }
    else
    {
        *_pI2C_CR1 &= ~I2C_CR1_START;
    }

}

void I2C::SetNoStretch (bool on)
{
    if (on)
    {
        *_pI2C_CR1 |= I2C_CR1_NOSTRETCH;
    }
    else
    {
        *_pI2C_CR1 &= ~I2C_CR1_NOSTRETCH;
    }

}

void I2C::EnableGeneralCall (bool enable)
{
    if (enable)
    {
        *_pI2C_CR1 |= I2C_CR1_ENGC;
    }
    else
    {
        *_pI2C_CR1 &= ~I2C_CR1_ENGC;
    }

}

void I2C::EnablePEC (bool enable)
{
    if (enable)
    {
        *_pI2C_CR1 |= I2C_CR1_PEC;
    }
    else
    {
        *_pI2C_CR1 &= ~I2C_CR1_PEC;
    }

}


void I2C::EnableARP (bool enable)
{
    if (enable)
    {
        *_pI2C_CR1 |= I2C_CR1_ENARP;
    }
    else
    {
        *_pI2C_CR1 &= ~I2C_CR1_ENARP;
    }

}


void I2C::SetModeI2C()
{
    *_pI2C_CR1 &= ~I2C_CR1_SMBUS;
}

void I2C::SetModeSMBHost()
{
    *_pI2C_CR1 |= I2C_CR1_SMBUS;
    *_pI2C_CR1 |= I2C_CR1_SMBTYPE;

}
void I2C::SetModeSMBDevice()
{
    *_pI2C_CR1 |= I2C_CR1_SMBUS;
    *_pI2C_CR1 &= ~I2C_CR1_SMBTYPE;

}



void I2C::EnableDMA (bool enable)
{
    if (enable)
    {
        *_pI2C_CR2 |= I2C_CR2_DMANEN;
    }
    else
    {
        *_pI2C_CR2 &= ~I2C_CR2_DMANEN;
    }

}


void I2C::EnableAutoNACK (bool enable)
{
    if (enable)
    {
        *_pI2C_CR2 |= I2C_CR2_LAST;
    }
    else
    {
        *_pI2C_CR2 &= ~I2C_CR2_LAST;
    }

}

bool I2C::IsError()
{
    bool isError = false;
    if (IsARLO())
    {
        ClearARLO();
        isError = true;
        ++_errorCountARLO;
    }
    if (IsAF())
    {
        ClearAF();
        isError = true;
        ++_errorCountAF;
    }
    if (IsTimeout())
    {
        ClearTimeout();
        isError = true;
        ++_errorCountTO;
    }
    if (IsBusError())
    {
        ClearBusError();
        isError = true;
        ++_errorCountBE;
    }

    return isError;

}

bool I2C::ReceiveDMA (void* data_ptr, uint32_t data_size)
{
    if (data_size == 0) 
    {
        return true;
    }
    
    EnableDMA(true);
    EnableAutoNACK(true);

    DMA1* dma1 = DMA1::GetInstance();
    if (!dma1->IsClockEnabled())
    {
        dma1->EnablePeripheralClock(true);
    }

    DMA_Channel* dmaCh = dma1->GetChannel(_dmaRxChannel);
    dmaCh->SetPeripheralAddress ((uint32_t)_pI2C_DR);
    dmaCh->SetMemoryAddress((uint32_t)data_ptr);
    dmaCh->SetDirection_PeripheralToMemory();
    dmaCh->SetMemorySize_8bits();
    dmaCh->SetPeripheralSize_8bits();
    dmaCh->SetNumberOfData(data_size);
    dmaCh->SetMemoryIncrementMode();
    dmaCh->SetPriorityHigh();

    dmaCh->EnableChannel(true);
    bool rc = true;

    while (!dma1->IsTransferComplete(dmaCh))
    {
        if  (dma1->IsTransferError(dmaCh))
        {
            ++_errorCount;
            ++_errorDMARX;
            rc = false;
            dma1->ClearTransferError(dmaCh);
            break;
        }
        if (IsError())
        {
            ++_errorCount;
            rc = false;
            break;
        }
    }

    SendStop(true);

    dmaCh->EnableChannel(false);
    dma1->ClearTransferComplete(dmaCh);

    EnableDMA(false);
    EnableAutoNACK(false);

    return rc;

}

bool I2C::SendDMA (void* data_ptr, uint32_t data_size)
{
    if (data_size == 0) 
    {
        return true;
    }

    EnableDMA(true);

    DMA1* dma1 = DMA1::GetInstance();
    if (!dma1->IsClockEnabled())
    {
        dma1->EnablePeripheralClock(true);
    }

    DMA_Channel* dmaCh = dma1->GetChannel(_dmaTxChannel);
    dmaCh->SetPeripheralAddress ((uint32_t)_pI2C_DR);
    dmaCh->SetMemoryAddress((uint32_t)data_ptr);
    dmaCh->SetDirection_MemoryToPeripheral();
    dmaCh->SetMemorySize_8bits();
    dmaCh->SetPeripheralSize_8bits();
    dmaCh->SetNumberOfData(data_size);
    dmaCh->SetMemoryIncrementMode();
    dmaCh->SetPriorityHigh();

    dmaCh->EnableChannel(true);

    bool rc = true;
    while (!dma1->IsTransferComplete(dmaCh))
    {
        if  (dma1->IsTransferError(dmaCh))
        {
            rc = false;
            ++_errorDMATX;
            ++_errorCount;
            dma1->ClearTransferError(dmaCh);
            break;
        }

    }

    if (!WaitStatus(I2C::MASTER_EV8_2, true))  //TRA, BUSY, MSL, TXE and BTF
        rc = false;


    SendStop(true);

    dmaCh->EnableChannel(false);
    dma1->ClearTransferComplete(dmaCh);
    EnableDMA(false);

    return rc;
}


void I2C::EnableBufferInterrupt (bool enable)
{
    if (enable)
    {
        *_pI2C_CR2 |= I2C_CR2_ITBUFEN;
    }
    else
    {
        *_pI2C_CR2 &= ~I2C_CR2_ITBUFEN;
    }
}

void I2C::EnableEventInterrupt (bool enable)
{
    if (enable)
    {
        *_pI2C_CR2 |= I2C_CR2_ITEVTEN;
        NVIC_SetEnable(_eventIrqNo);
    }
    else
    {
        *_pI2C_CR2 &= ~I2C_CR2_ITEVTEN;
        NVIC_ClearEnable(_eventIrqNo);
    }
}

void I2C::EnableErrorInterrupt (bool enable)
{
    if (enable)
    {
        *_pI2C_CR2 |= I2C_CR2_ITERREN;
        NVIC_SetEnable(_errorIrqNo);
    }
    else
    {
        *_pI2C_CR2 &= ~I2C_CR2_ITERREN;
        NVIC_ClearEnable(_errorIrqNo);
    }

}

void I2C::SetOwnAddr7Bit (uint8_t addr)
{
    *_pI2C_OAR1 = (addr & 0x7f) << 1;
    *_pI2C_OAR2 &= ~I2C_OAR2_ENDUAL;
}

void I2C::SetOwnAddr10bit (uint16_t addr)
{
    *_pI2C_OAR1 = (addr & 0x3ff);
    *_pI2C_OAR2 &= ~I2C_OAR2_ENDUAL;
}

void I2C::SetOwnAddr7bitDual (uint8_t addr1, uint8_t addr2)
{
    SetOwnAddr7Bit(addr1);
    *_pI2C_OAR2 = (addr2 & 0x7f) << 1;
    *_pI2C_OAR2 |= I2C_OAR2_ENDUAL;
}

bool I2C::IsSMBAlert()
{
    return *_pI2C_SR1 & I2C_SR1_SMBALERT;
}


bool I2C::IsTimeout()
{
    return *_pI2C_SR1 & I2C_SR1_TIMEOUT;

}

bool I2C::IsPECError()
{
    return *_pI2C_SR1 & I2C_SR1_PECERR;
}

bool I2C::IsOVR()
{
    return *_pI2C_SR1 & I2C_SR1_OVR;
}

bool I2C::IsAF()
{
    return *_pI2C_SR1 & I2C_SR1_AF;
}

bool I2C::IsARLO()
{
    return *_pI2C_SR1 & I2C_SR1_ARLO;
}
bool I2C::IsBusError()
{
    return *_pI2C_SR1 & I2C_SR1_BERR;
}


void I2C::ClearSMBAlert()
{
    *_pI2C_SR1 &= ~I2C_SR1_SMBALERT;
}
void I2C::ClearTimeout()
{
    *_pI2C_SR1 &= ~I2C_SR1_TIMEOUT;
}
void I2C::ClearPECERR()
{
    *_pI2C_SR1 &= ~I2C_SR1_PECERR;
}
void I2C::ClearOVR()
{
    *_pI2C_SR1 &= ~I2C_SR1_OVR;
}
void I2C::ClearAF()
{
    *_pI2C_SR1 &= ~I2C_SR1_AF;
}
void I2C::ClearARLO()
{
    *_pI2C_SR1 &= ~I2C_SR1_ARLO;
}
void I2C::ClearBusError()
{
    *_pI2C_SR1 &= ~I2C_SR1_BERR;
}


void I2C::ClearSTOPF()
{
    *_pI2C_SR1;
    *_pI2C_SR2;

    *_pI2C_CR1 &= 0xffff;
}

bool I2C::IsStop() 
{
    return *_pI2C_CR1 & I2C_CR1_STOP;
}


bool I2C::IsTxE()
{
    return *_pI2C_SR1 & I2C_SR1_TxE;
}
bool I2C::IsRxNE()
{
    return *_pI2C_SR1 & I2C_SR1_RxNE;
}
bool I2C::IsStOPF()
{
    return *_pI2C_SR1 & I2C_SR1_STOPF;
}
bool I2C::IsADD10()
{
    return *_pI2C_SR1 & I2C_SR1_ADD10;
}
bool I2C::IsBTF()
{
    return *_pI2C_SR1 & I2C_SR1_BTF;
}
bool I2C::IsADDR()
{
    return *_pI2C_SR1 & I2C_SR1_ADDR;
}
bool I2C::IsSB()
{
    return *_pI2C_SR1 & I2C_SR1_SB;
}

void I2C::SetModeSm()
{
    *_pI2C_CCR &= ~I2C_CCR_FS;
}
void I2C::SetModeFm()
{
    *_pI2C_CCR |= I2C_CCR_FS;
}

void I2C::SetFmDuty (bool set)
{
    if (set)
    {
        *_pI2C_CCR |= I2C_CCR_DUTY;
    }
    else
    {
        *_pI2C_CCR &= ~I2C_CCR_DUTY;
    }
}

void I2C::SetTRISE(uint8_t val)
{
    *_pI2C_TRISE = (val & 0x1f);
}


uint8_t I2C::GetPEC()
{
    return (*_pI2C_SR2 & (I2C_SR2_PEC<<8));
}

bool I2C::IsDualF()
{
    return (*_pI2C_SR2 & I2C_SR2_DUALF);
}

bool I2C::IsSMBHostAddr()
{   return (*_pI2C_SR2 & I2C_SR2_SMBHOST);

}
bool I2C::IsSMBDefaultAddr()
{
    return (*_pI2C_SR2 & I2C_SR2_SMBDEFAULT);
}
bool I2C::IsGenCallAddr()
{
    return (*_pI2C_SR2 & I2C_SR2_GENCALL);
}
bool I2C::IsTransmitter()
{
    return (*_pI2C_SR2 & I2C_SR2_TRA);
}
bool I2C::IsBusy()
{
    return (*_pI2C_SR2 & I2C_SR2_BUSY);
}
bool I2C::IsMasterMode()
{
    return (*_pI2C_SR2 & I2C_SR2_MSL);
}


void I2C::Send7bitAddress (uint8_t slaveAddr, bool isWrite)
{
    if (isWrite)
    {
        slaveAddr &= ~0x1;
    }
    else
    {
        slaveAddr |= 0x1;
    }
    *_pI2C_DR = slaveAddr;
}

void I2C::SendByte  (uint8_t data)
{
    *_pI2C_DR = data;
}

uint8_t I2C::ReceiveByte ()
{
    return *_pI2C_DR;
}

//#define FLAG_Mask               ((uint32_t)0x00FFFFFF)

bool I2C::WaitStatus (STATUS_MASK status_mask, bool set)
{

    //uint32_t lastevent = 0;
    //uint32_t flag1 = 0, flag2 = 0;
    bool rc = false;
    uint32_t retryCount = _retryCount;

    while(--retryCount)
    {
        //flag1 = *_pI2C_SR1;
        //flag2 = *_pI2C_SR2;
        //flag2 = (flag2 & 0xff) << 16;

        //lastevent = (flag1 | flag2);

        uint32_t status = *_pI2C_SR1 | (*_pI2C_SR2 & 0xff) << 16;

        bool is_set = (status & status_mask) == status_mask;
        if (set == is_set)
        {
            rc = true;
            break;
        }

        if (IsError())
        {
            break;
        }

    }

    if (!rc)
    {
        ++_errorCount;
        if (retryCount == 0)
        {
            ++_errorCountRetry;
        }
    }

    return rc;
}

bool I2C::MasterWriteRegister (uint8_t* data, uint32_t data_size, uint8_t slave_addr, uint8_t reg_addr)
{
    return MasterWrite (data, data_size, slave_addr, &reg_addr);
}

bool I2C::MasterWriteData (uint8_t* data, uint32_t data_size, uint8_t slave_addr)
{
    return MasterWrite (data, data_size, slave_addr, 0);
}



bool I2C::MasterWrite (uint8_t* data, uint32_t data_size, uint8_t slave_addr, uint8_t* preg_addr)
{
    if (!_errorCallBack  && !_errorHandler)
    {
        //return _MasterWrite (data, data_size, slave_addr, preg_addr);
        while (!_MasterWrite (data, data_size, slave_addr, preg_addr))
        {
            AutoRecover();
        }
        return true;
    }
    else
    {
        while (!_MasterWrite (data, data_size, slave_addr, preg_addr))
        {
            if (_errorCallBack)
            {
                _errorCallBack(_errorCallBackArg);
            }

            if (_errorHandler)
            {
                _errorHandler->HandleError();
            }
        }
        return true;
    }

}

bool I2C::_MasterWrite (uint8_t* data, uint32_t data_size, uint8_t slave_addr, uint8_t* preg_addr)
{
    if (data_size == 0) 
    {
        return true;
    }
    if (!WaitStatus(I2C::BUSY, false))
    {
        //ClearBUSY();
        _stuckBUSY= true;
        return false;
    }

    SendStart(true);

    if (!WaitStatus(I2C::MASTER_EV5, true))
        return false;

    Send7bitAddress(slave_addr, true);

    if (!WaitStatus(I2C::MASTER_EV6_TRA, true)) //MSL | BUSY | ADDR | TXE | TRA
        return false;

    ////////////////////////////////////////////////////////////////////////////
    if (preg_addr)
    {
        SendByte(*preg_addr);
        if (!WaitStatus(I2C::MASTER_EV8_2, true))  //TRA, BUSY, MSL, TXE and BTF
            return false;
    }
    ////////////////////////////////////////////////////////////////////////////

    if (data_size == 1)
    {
        SendByte(*data);

        if (!WaitStatus(I2C::MASTER_EV8, true))  //TRA, BUSY, MSL, TXE and BTF
            return false;

        SendStop(true);

        return true;

    }
    else
    {
        return SendDMA (data, data_size);
    }

}



bool I2C::MasterReadData (uint8_t* data, uint32_t data_size, uint8_t slave_addr)
{
    return MasterRead (data, data_size, slave_addr, 0);
}

bool I2C::MasterReadRegister (uint8_t* data, uint32_t data_size, uint8_t slave_addr, uint8_t reg_addr)
{
    return MasterRead (data, data_size, slave_addr, &reg_addr);
}

bool I2C::MasterRead (uint8_t* data, uint32_t data_size, uint8_t slave_addr, uint8_t* reg_addr)
{
    if (!_errorCallBack  && !_errorHandler)
    {
        //return _MasterRead (data, data_size, slave_addr, reg_addr);
        while (!_MasterRead (data, data_size, slave_addr, reg_addr))
        {
            AutoRecover();
        }
        return true;
    }
    else
    {
        while (!_MasterRead (data, data_size, slave_addr, reg_addr))
        {
            if (_errorCallBack)
            {
                _errorCallBack(_errorCallBackArg);
            }

            if (_errorHandler)
            {
                _errorHandler->HandleError();
            }
        }

        return true;
    }

}

bool I2C::_MasterRead (uint8_t* data, uint32_t data_size, uint8_t slave_addr, uint8_t* reg_addr)
{
    if (data_size == 0) 
    {
        return true;
    }

    if (!WaitStatus(I2C::BUSY, false))
    {
        //ClearBUSY();
        _stuckBUSY = true;
        return false;
    }
    

    if (reg_addr)
    {
        SendStart(true);

        if (!WaitStatus(I2C::MASTER_EV5, true)) //BSY MSL SB
            return false;

        Send7bitAddress(slave_addr, true);

        if (!WaitStatus(I2C::MASTER_EV6_TRA, true)) //MSL | BUSY | ADDR | TXE | TRA
            return false;

        SendByte(*reg_addr);

        if (!WaitStatus(I2C::MASTER_EV8_2, true))  //TRA, BUSY, MSL, TXE and BTF
            return false;

    }

    SendStart(true);

    if (!WaitStatus(I2C::MASTER_EV5, true)) //BSY MSL SB
        return false;

    Send7bitAddress(slave_addr, false);

    if (!WaitStatus(I2C::MASTER_EV6_RECV, true)) //MSL | BUSY | ADDR
        return false;

    if (data_size == 1)
    //if (false)
    {
        EnableACK(false);
        SendStop(true);

 //       if (!WaitStatus(I2C::MASTER_EV7, true))  //MSL | BUSY | ADDR
        if (!WaitStatus(I2C::RXNE, true))  //MSL | BUSY | ADDR
            return false;

        *data = ReceiveByte();

        EnableACK(true);
        return true;
    }
    else
    {
        return ReceiveDMA(data, data_size);
    }
}


bool I2C::SlaveReceiveData(uint8_t* data, uint8_t data_size)
{
    if (!WaitStatus(SLAVE_RECV_EV1, true))
    {
        return false;
    }

    for (uint8_t i = 0; i < data_size; ++i)
    {
        if (!WaitStatus(SLAVE_RECV_EV2, true))
        {
            return false;
        }
        data[i] = ReceiveByte();

    }

    if (!WaitStatus(SLAVE_RECV_EV4, true))
    {
        return false;
    }


    ClearSTOPF();


    return true;
}

bool I2C::SlaveSendData(uint8_t* data, uint8_t data_size)
{
    if (!WaitStatus(SLAVE_TRA_EV1, true))
    {
        return false;
    }

    for (uint8_t i = 0; i < data_size; ++i)
    {
        if (!WaitStatus(SLAVE_TRA_EV3, true))
        {
            return false;
        }

        SendByte (data[i]);
    }

    if (!WaitStatus(BTF, true))
    {
        return false;
    }


    if (!WaitStatus(SLAVE_TRA_EV3_2, true))
    {
        return false;
    }


    ClearAF();

    return true;
}


void I2C::AutoRecover()
{
    //save registers

    //cr1
    bool isAck = (*_pI2C_CR1  & I2C_CR1_ACK);
    //isAck = true;
    bool isENARP = (*_pI2C_CR1  & I2C_CR1_ENARP);
    bool isENPEC = (*_pI2C_CR1  & I2C_CR1_ENPEC);
    bool isENGC = (*_pI2C_CR1  & I2C_CR1_ENGC);

    uint16_t cr2 = *_pI2C_CR2;
    uint16_t oar1 = *_pI2C_OAR1;
    uint16_t oar2 = *_pI2C_OAR2;
    uint16_t ccr = *_pI2C_CCR;
    uint16_t trise = *_pI2C_TRISE;

    if (_stuckBUSY)
    {
        ClearBUSY();
    }

    /*
    Initialize(100000, false, false);



    SetModeI2C();
    EnableACK(true);
    SetOwnAddr7Bit(0x00);
    return;
     */


    Enable(false);
    SetSoftwareReset(true);
    SetSoftwareReset(false);
    EnablePeripheralClock(true);

    InitGPIO();


    //restore registers;

    EnableACK(isAck);
    EnableARP(isENARP);
    EnablePEC(isENPEC);
    EnableGeneralCall(isENGC);

    *_pI2C_CR2 = cr2;
    *_pI2C_OAR1 = oar1;
    *_pI2C_OAR2 = oar2;
    *_pI2C_CCR = ccr;
    *_pI2C_TRISE = trise;

    _stuckBUSY = false;

    Enable(true);


}


void I2C::ClearBUSY()
{
    Enable(false);


    _gpioPort->SetupGPIO_OutOD (_clockPin,  GPIO_MODE_OUT_50MHZ);  //I2C_SCL
    _gpioPort->SetupGPIO_OutOD (_sdaPin);  //I2C_SDA
    _gpioPort->SetPin(_clockPin);
    _gpioPort->ResetPin(_sdaPin);
    _gpioPort->ResetPin(_clockPin);
    _gpioPort->SetPin(_clockPin);
    _gpioPort->SetPin(_sdaPin);

    *_pI2C_CR1 |= I2C_CR1_SWRST;
    *_pI2C_CR1 &= ~I2C_CR1_SWRST;

    //Enable(true);
}



void I2C::InitGPIO()
{
    if (_gpioPort->IsClockEnabled())
    {
        _gpioPort->EnablePeripheralClock(true);
    }

    if (!_gpioPort->IsClockEnabled())
    {
        _gpioPort->EnablePeripheralClock(true);
    }

    _gpioPort->SetupGPIO_OutAltOD (_clockPin);  //I2C_SCL
    _gpioPort->SetupGPIO_OutAltOD (_sdaPin);  //I2C_SDA

}


//uint32_t  I2C::GetStatus()
//{
//  return (*_pI2C_SR1 & 0x0000ffff) | ((*_pI2C_SR2<<16) & 0xffff0000);
//}


void I2C1::EnablePeripheralClock(bool enable)
{
    RCC_EnableI2C1(enable);
}






#if !defined(STM32F10X_LD) && !defined(STM32F10X_LD_VL)

void I2C2::EnablePeripheralClock(bool enable)
{
    RCC_EnableI2C2(enable);
}


#endif

#endif
