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


#ifndef _I2C_CPP_H
#define _I2C_CPP_H

#include "common.h"

#ifdef USE_I2C

#include "I2C.h"

#include "nvic.h"
#include "dma_cpp.h"
#include "gpio_cpp.h"

class I2C_IRQ_Event_Handler;
class I2C_IRQ_Error_Handler;

struct I2C_IRQ_Error_Info
{
    bool BusError;
    bool ArbitrationLoss;
    bool AckFailure;
    bool OverrunUnderrun;
    bool PECError;
    bool Timeout;
    bool SMBAlert;
};

struct I2C_IRQ_Event_Info
{
    bool StartBitSent;
    bool AddressSentMatched;
    bool Addr10HeaderSent;
    bool StopBitReceived;
    bool ByteTransferFinished;
    bool TxE;
    bool RxNE;
};

class I2C_ErrorHandler
{
public:
    virtual void HandleError() = 0;
};

class I2C: public Peripheral
{

public:

    enum STATUS_MASK
    {
        SB = I2C_SR1_SB,
        ADDR = I2C_SR1_ADDR,
        BTF = I2C_SR1_BTF,
        ADD10 = I2C_SR1_ADD10,
        STOPF = I2C_SR1_STOPF,
        RXNE = I2C_SR1_RxNE,
        TXE = I2C_SR1_TxE,
        BERR = I2C_SR1_BERR,
        ARLO = I2C_SR1_ARLO,
        AF = I2C_SR1_AF,
        OVR = I2C_SR1_OVR,
        PECERR = I2C_SR1_PECERR,
        TIMEOUT = I2C_SR1_TIMEOUT,
        SMBALERT = I2C_SR1_SMBALERT,

        MSL = I2C_SR2_MSL << 16,
        BUSY = I2C_SR2_BUSY << 16,
        TRA = I2C_SR2_TRA << 16,
        GENCALL = I2C_SR2_GENCALL << 16,
        SMBDEFAULT = I2C_SR2_SMBDEFAULT << 16,
        SMBHOST = I2C_SR2_SMBHOST << 16,
        DUALF = I2C_SR2_DUALF << 16,
        PEC = I2C_SR2_PEC << 16,

        //compound states
        MASTER_EV5 = MSL | BUSY | SB,
        MASTER_EV6_RECV = MSL | BUSY | ADDR,
        MASTER_EV6_TRA = MSL | BUSY | ADDR | TXE | TRA,
        MASTER_EV8 = MSL | BUSY | TXE | TRA,
        MASTER_EV8_2 = MASTER_EV8 | BTF,

        MASTER_EV7 = MSL | BUSY | RXNE,

        SLAVE_RECV_EV1 = BUSY | ADDR,
        SLAVE_TRA_EV1 = BUSY | ADDR | TXE | TRA,
        SLAVE_EV1_GENCALL = BUSY | GENCALL,

        SLAVE_RECV_EV2 = BUSY | RXNE,
        SLAVE_RECV_EV4 = STOPF,
        SLAVE_TRA_EV3 = BUSY | TXE | TRA,
        SLAVE_TRA_EV3_2 = AF

    };
private:

    volatile uint32_t* _pI2C_CR1;
    volatile uint32_t* _pI2C_CR2;
    volatile uint32_t* _pI2C_OAR1;
    volatile uint32_t* _pI2C_OAR2;
    volatile uint32_t* _pI2C_DR;
    volatile uint32_t* _pI2C_SR1;
    volatile uint32_t* _pI2C_SR2;
    volatile uint32_t* _pI2C_CCR;
    volatile uint32_t* _pI2C_TRISE;

    IRQn_Type _eventIrqNo;
    IRQn_Type _errorIrqNo;
    I2C_IRQ_Event_Handler* _irqEventHandler;
    I2C_IRQ_Error_Handler* _irqErrorHandler;

    DMA_IRQ_Handler* _dmaRxHandler;
    DMA_IRQ_Handler* _dmaTxHandler;
    DMA_CHANNEL _dmaRxChannel;
    DMA_CHANNEL _dmaTxChannel;

    uint32_t _retryCount;

    GPIO_PORT* _gpioPort;
    GPIO_PIN_N _clockPin;
    GPIO_PIN_N _sdaPin;

    uint32_t _errorCount;
    uint32_t _errorCountAF;
    uint32_t _errorCountBE;
    uint32_t _errorCountTO;
    uint32_t _errorCountARLO;
    uint32_t _errorCountRetry;
    uint32_t _errorDMARX;
    uint32_t _errorDMATX;

    void* (*_errorCallBack)(void*);
    I2C_ErrorHandler* _errorHandler;
    void* _errorCallBackArg;

    bool _stuckBUSY;

    void _EnableInterrupt(uint16_t intMask, bool enable);

    bool MasterWrite(uint8_t* data, uint32_t data_size, uint8_t slave_addr,
            uint8_t* preg_addr);
    bool _MasterWrite(uint8_t* data, uint32_t data_size, uint8_t slave_addr,
            uint8_t* preg_addr);
    bool MasterRead(uint8_t* data, uint32_t data_size, uint8_t slave_addr,
            uint8_t* preg_addr);
    bool _MasterRead(uint8_t* data, uint32_t data_size, uint8_t slave_addr,
            uint8_t* preg_addr);

    void InitGPIO();

public:

    I2C(volatile uint32_t* pI2C_CR1, volatile uint32_t* pI2C_CR2,
            volatile uint32_t* pI2C_OAR1, volatile uint32_t* pI2C_OAR2,
            volatile uint32_t* pI2C_DR, volatile uint32_t* pI2C_SR1,
            volatile uint32_t* pI2C_SR2, volatile uint32_t* pI2C_CCR,
            volatile uint32_t* pI2C_TRISE, IRQn_Type eventIrqNo,
            IRQn_Type errorIrqNo, DMA_CHANNEL dmaRxChannel,
            DMA_CHANNEL dmaTxChannel, GPIO_PORT* gpioPort, GPIO_PIN_N clockPin,
            GPIO_PIN_N sdaPin)
    {
        _pI2C_CR1 = pI2C_CR1;
        _pI2C_CR2 = pI2C_CR2;
        _pI2C_OAR1 = pI2C_OAR1;
        _pI2C_OAR2 = pI2C_OAR2;
        _pI2C_DR = pI2C_DR;
        _pI2C_SR1 = pI2C_SR1;
        _pI2C_SR2 = pI2C_SR2;
        _pI2C_CCR = pI2C_CCR;
        _pI2C_TRISE = pI2C_TRISE;
        _eventIrqNo = eventIrqNo;
        _errorIrqNo = errorIrqNo;
        _dmaRxChannel = dmaRxChannel;
        _dmaTxChannel = dmaTxChannel;
        _retryCount = 100;
        _dmaTxHandler = 0;
        _dmaRxHandler = 0;
        _irqErrorHandler = 0;
        _irqEventHandler = 0;
        _gpioPort = gpioPort;
        _clockPin = clockPin;
        _sdaPin = sdaPin;
        _errorCount = 0;
        _errorCountAF = 0;
        _errorCountBE = 0;
        _errorCountTO = 0;
        _errorCountARLO = 0;
        _errorCountRetry = 0;
        _errorDMARX = 0;
        _errorDMATX = 0;
        _stuckBUSY = false;
    }

    void Initialize(uint32_t clockSpeed, bool isDuty16_9, bool isFmMode,  bool initializeGPIO = false);
    void Reset();

    void Enable(bool enable);
    void SetClock(uint32_t clockSpeed, bool isDuty16_9, bool isFmMode);

    void SetIrqEventHandler(I2C_IRQ_Event_Handler* handler)
    {
        _irqEventHandler = handler;
    }
    void SetIrqErrorHandler(I2C_IRQ_Error_Handler* handler)
    {
        _irqErrorHandler = handler;
    }

    void HandleErrorInterrupt();
    void HandleEventInterrupt();

    void SetSoftwareReset(bool on);
    void SetSMBAlert(bool on);
    //bool IsSoftwareReset();
    void SetPEC(bool on);
    //bool IsPEC();
    void SetPOS(bool on);
    //bool IsPOS();
    void EnableACK(bool on);
    //bool IsACK  ();
    void SendStop(bool on);
    //bool IsStop();
    void SendStart(bool on);
    //bool IsStart();
    void SetNoStretch(bool on);
    void EnableGeneralCall(bool enable);
    void EnablePEC(bool enable);
    void EnableARP(bool enable);
    void SetModeI2C();
    void SetModeSMBHost();
    void SetModeSMBDevice();

    void EnableDMA(bool enable);
    void EnableAutoNACK(bool enable);
    void EnableBufferInterrupt(bool enable);
    void EnableEventInterrupt(bool enable);
    void EnableErrorInterrupt(bool enable);
    void SetOwnAddr7Bit(uint8_t addr);
    void SetOwnAddr10bit(uint16_t addr);
    void SetOwnAddr7bitDual(uint8_t addr1, uint8_t addr2);

    bool IsStop();
    bool IsSMBAlert();
    bool IsTimeout();
    bool IsPECError();
    bool IsOVR();
    bool IsAF();
    bool IsARLO();
    bool IsBusError();

    void ClearSMBAlert();
    void ClearTimeout();
    void ClearPECERR();
    void ClearOVR();
    void ClearAF();
    void ClearARLO();
    void ClearBusError();
    void ClearSTOPF();

    bool IsTxE();
    bool IsRxNE();
    bool IsStOPF();
    bool IsADD10();
    bool IsBTF();
    bool IsADDR();
    bool IsSB();

    uint8_t GetPEC();
    bool IsDualF();
    bool IsSMBHostAddr();
    bool IsSMBDefaultAddr();
    bool IsGenCallAddr();
    bool IsTransmitter();
    bool IsBusy();
    bool IsMasterMode();

    void SetModeSm();
    void SetModeFm();

    void SetFmDuty(bool set);

    void SetTRISE(uint8_t val);

    void Send7bitAddress(uint8_t slaveAddr, bool isWrite);

    void SendByte(uint8_t data);
    uint8_t ReceiveByte();

    bool MasterWriteRegister(uint8_t* data, uint32_t data_size,  uint8_t slave_addr, uint8_t reg_addr);
    bool MasterWriteData(uint8_t* data, uint32_t data_size, uint8_t slave_addr);
    bool MasterReadRegister(uint8_t* data, uint32_t data_size, uint8_t slave_addr, uint8_t reg_addr);
    bool MasterReadData(uint8_t* data, uint32_t data_size, uint8_t slave_addr);

    void SetRetryCount(uint32_t retryCount)
    {
        _retryCount = retryCount;
    }

    bool WaitStatus(STATUS_MASK status_mask, bool set);

    bool SendDMA(void* data_ptr, uint32_t data_size);
    bool ReceiveDMA(void* data_ptr, uint32_t data_size);

    bool SlaveReceiveData(uint8_t* data, uint8_t data_size);
    bool SlaveSendData(uint8_t* data, uint8_t data_size);

    void AutoRecover();
    void ClearBUSY();
    bool IsError();

    void SetErrorCallback(void*(*f)(void*), void* arg)
    {
        _errorCallBack = f;
        _errorCallBackArg = arg;
    }

    void SetErrorHandler(I2C_ErrorHandler* errorHandler)
    {
        _errorHandler = errorHandler;
    }

};

class I2C_IRQ_Event_Handler
{
public:
    virtual void HandleEventInterrupt(I2C* spi, I2C_IRQ_Event_Info info) = 0;
};

class I2C_IRQ_Error_Handler
{
public:
    virtual void HandleErrorInterrupt(I2C* spi, I2C_IRQ_Error_Info info) = 0;
};

class I2C1: public I2C
{
public:

    static I2C1* GetInstance()
    {
        static I2C1 instance;
        return &instance;
    }

    virtual void EnablePeripheralClock(bool enable);

private:
    I2C1() :
            I2C(&I2C1_CR1, &I2C1_CR2, &I2C1_OAR1, &I2C1_OAR2, &I2C1_DR,
                    &I2C1_SR1, &I2C1_SR2, &I2C1_CCR, &I2C1_TRISE, IRQn_I2C1_EV,
                    IRQn_I2C1_ER, DMA_CHANNEL_7, DMA_CHANNEL_6,
                    GPIOB::GetInstance(), GPIO_PIN6, GPIO_PIN7)
    {
    }

    I2C1(I2C1 const&);
    void operator=(I2C1 const&);
};

#if !defined(STM32F10X_LD) && !defined(STM32F10X_LD_VL)

class I2C2 : public I2C
{
public:

    static I2C2* GetInstance()
    {
        static I2C2 instance;
        return &instance;
    }

    virtual void EnablePeripheralClock(bool enable);

private:
    I2C2() : I2C (&I2C2_CR1, &I2C2_CR2, &I2C2_OAR1, &I2C2_OAR2, &I2C2_DR, &I2C2_SR1, &I2C2_SR2, &I2C2_CCR, &I2C2_TRISE,
            IRQn_I2C2_EV, IRQn_I2C2_ER, DMA_CHANNEL_5, DMA_CHANNEL_4, GPIOB::GetInstance(), GPIO_PIN10, GPIO_PIN11)
    {
    }

    I2C2(I2C2 const&);
    void operator=(I2C2 const&);

};

#endif

#endif

#endif
