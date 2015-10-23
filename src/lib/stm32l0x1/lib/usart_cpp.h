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


#ifndef _USART_CPP_H
#define _USART_CPP_H

#include "common.h"

#ifdef USE_USART

#include "usart.h"
#include "nvic.h"
#include "dma_cpp.h"
#include "Peripheral.h"
#include "rcc.h"

class USART_IRQ_Handler;

struct USART_IRQ_Info
{
    bool isCTS;
    bool isLBD;
    bool isTXE;

    bool isTC;
    bool isRXNE;
    bool isIDLE;

    bool isPE;
    bool isOverrun;
    bool isNoiseError;
    bool isFrameError;

};

class USART : public Peripheral
{

private:


    volatile uint32_t* _pUSART_SR;
    volatile uint32_t* _pUSART_DR;
    volatile uint32_t* _pUSART_BRR;
    volatile uint32_t* _pUSART_CR1;
    volatile uint32_t* _pUSART_CR2;
    volatile uint32_t* _pUSART_CR3;

    IRQn_Type _irqNo;
    USART_IRQ_Handler* _irqHandler;

    DMA_IRQ_Handler* _dmaRxHandler;
    DMA_IRQ_Handler* _dmaTxHandler;
    DMA_CHANNEL      _dmaRxChannel;
    DMA_CHANNEL      _dmaTxChannel;

    bool _isUSART1;

    void _EnableInterrupt(uint16_t intMask, volatile uint32_t* reg, bool enable);



public:

    USART(volatile uint32_t* pUSART_SR, volatile uint32_t* pUSART_DR,
            volatile uint32_t* pUSART_BRR, volatile uint32_t* pUSART_CR1,
            volatile uint32_t* pUSART_CR2, volatile uint32_t* pUSART_CR3,
            IRQn_Type irqNo, bool isUSART1, DMA_CHANNEL  dmaRxChannel, DMA_CHANNEL  dmaTxChannel,
            volatile uint32_t* enableReg, volatile uint32_t* resetReg, uint32_t bit)
    : Peripheral (enableReg, resetReg, bit)
{
        _pUSART_SR = pUSART_SR;
        _pUSART_DR = pUSART_DR;
        _pUSART_BRR = pUSART_BRR;
        _pUSART_CR1 = pUSART_CR1;
        _pUSART_CR2 = pUSART_CR2;
        _pUSART_CR3 = pUSART_CR3;
        _irqNo = irqNo;
        _isUSART1 = isUSART1;
        _dmaRxChannel = dmaRxChannel;
        _dmaTxChannel = dmaTxChannel;
}

    enum STOP_BIT
    {
        STOP_1 = USART_CR2_STOP_1,
        STOP_0_5 = USART_CR2_STOP_0_5,
        STOP_2 = USART_CR2_STOP_2,
        STOP_1_5 = USART_CR2_STOP_1_5
    };


    void Enable(bool enable);

    void SendByte (uint16_t data);
    void SendWord (uint16_t data);
    uint16_t Receive();  //TODO byte & word

    void ClearCTS();
    void ClearLBD();
    void ClearTC();
    void ClearRXNE();
    bool IsCTS();
    bool IsLBD();
    bool IsTXE();
    bool IsTC();
    bool IsRXNE();
    bool IsIDLE();
    bool IsOverrun();
    bool IsNoiseError();
    bool IsFramingError();
    bool IsParityError();

    void WaitTXE();
    void WaitRXNE();

    void SetBaudRate(uint32_t baudRate);


    void SetWordLength_9bit();
    void SetWordLength_8bit();
    void SetWakeupIdleLine();
    void SetWakeupAddressMark();
    void SetParityOdd();
    void SetParityEven();
    void EnableTransmitter(bool enable);
    void EnableReceiver(bool enable);
    void SetRWU(bool set);
    void SendBreak();

    void SetStopBits(STOP_BIT stopBit);
    void SetLBDL10();
    void SetLBDL11();
    void SetNodeAddr(uint8_t addr);

    void EnableLineMode(bool enable);
    void EnableCTS(bool enable);
    void EnableRTS(bool enable);
    void EnableDMAT(bool enable);
    void EnableDMAR(bool enable);
    void EnableSmartCardMode(bool enable, bool enableNack);
    void EnableHalfDuplexMode(bool enable);
    void EnableIrDA(bool enable, bool lowPower);
    void EnableSynchronousMode(bool clockPinEnable, bool isPolarityHigh, bool isPhaseSecond, bool isLBCL);

    void EnableInterrupt_CTS(bool enable);
    void EnableInterrupt_LBDIE(bool enable);
    void EnableInterrupt_PE(bool enable);
    void EnableInterrupt_TXE(bool enable);
    void EnableInterrupt_TC(bool enable);
    void EnableInterrupt_RXNE(bool enable);
    void EnableInterrupt_IDLE(bool enable);
    void EnableInterrupt_ERROR(bool enable);

    void SetIrqHandler(USART_IRQ_Handler* handler)
    {
        _irqHandler = handler;
    }

    void HandleInterrupt();
    void ClearError();

    volatile uint32_t* GetDataRegisterAddress() { return _pUSART_DR; }

    void ConfigureDMATX (void* data_ptr, uint32_t data_size, DMA_IRQ_Handler* dmaTxHandler);
    void ConfigureDMARX (void* data_ptr, uint32_t data_size, DMA_IRQ_Handler* dmaRxHandler);
private:
    void _ConfigureDMA (void* data_ptr, uint32_t data_size, DMA_CHANNEL channel);


};

class USART_IRQ_Handler
{
public:
    virtual void Handle(USART* spi, USART_IRQ_Info info) = 0;
};

class USART1: public USART
{
public:

    static USART1* GetInstance()
    {
        static USART1 instance;
        return &instance;
    }


private:
    USART1() :
        USART(&USART1_SR, &USART1_DR, &USART1_BRR, &USART1_CR1, &USART1_CR2,
                &USART1_CR3, IRQn_USART1, true, DMA_CHANNEL_5, DMA_CHANNEL_4,
                &RCC_APB2ENR, &RCC_APB2RSTR, RCC_APB2ENR_USART1EN)
{
}



    USART1(USART1 const&);
    void operator=(USART1 const&);
};

class USART2: public USART
{
public:

    static USART2* GetInstance()
    {
        static USART2 instance;
        return &instance;
    }


private:
    USART2() :
        USART(&USART2_SR, &USART2_DR, &USART2_BRR, &USART2_CR1, &USART2_CR2,
                &USART2_CR3, IRQn_USART2, false, DMA_CHANNEL_6, DMA_CHANNEL_7,
                &RCC_APB1ENR, &RCC_APB1RSTR, RCC_APB1ENR_USART2EN)
{
}



    USART2(USART2 const&);
    void operator=(USART2 const&);
};

#if !defined(STM32F10X_LD) && !defined(STM32F10X_LD_VL)

class USART3 : public USART
{
public:

    static USART3* GetInstance()
    {
        static USART3 instance;
        return &instance;
    }

private:
    USART3() : USART (&USART3_SR, &USART3_DR, &USART3_BRR, &USART3_CR1, &USART3_CR2, &USART3_CR3, IRQn_USART3, false,
            DMA_CHANNEL_3, DMA_CHANNEL_2,
            &RCC_APB1ENR, &RCC_APB1RSTR, RCC_APB1ENR_USART3EN)
{
}


    USART3(USART3 const&);
    void operator=(USART3 const&);
};

#endif

#endif

#endif
