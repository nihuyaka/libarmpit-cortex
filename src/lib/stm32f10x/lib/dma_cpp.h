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


#ifndef _DMA_CPP_H
#define _DMA_CPP_H

#include "dma.h"

#ifdef USE_DMA


#include "nvic.h"
#include "rcc.h"
#include "peripheral.h"

class DMA_IRQ_Handler;

class DMA_Channel
{
    friend class DMA;

private:
    volatile uint32_t* _pDMA_CCR;
    volatile uint32_t* _pDMA_CNDTR;
    volatile uint32_t* _pDMA_CPAR;
    volatile uint32_t* _pDMA_CMAR;

    uint32_t DMA_ISR_GIF;
    uint32_t DMA_ISR_TCIF;
    uint32_t DMA_ISR_HTIF;
    uint32_t DMA_ISR_TEIF;
    uint32_t DMA_IFCR_CGIF;
    uint32_t DMA_IFCR_CTCIF;
    uint32_t DMA_IFCR_CHTIF;
    uint32_t DMA_IFCR_CTEIF;

    IRQn_Type _nvicIrqNumber;

    DMA_Channel(DMA_Channel const&);
    void operator=(DMA_Channel const&);

protected:
    DMA_Channel()
    {
    }

public:
    void EnableChannel(bool enable);
    void SetPeripheralAddress(uint32_t addr);
    void SetMemoryAddress(uint32_t addr);
    void SetPeripheralSize_8bits();
    void SetPeripheralSize_16bits();
    void SetPeripheralSize_32bits();
    void SetMemorySize_8bits();
    void SetMemorySize_16bits();
    void SetMemorySize_32bits();
    void SetNumberOfData(uint16_t);
    void SetDirection_MemoryToPeripheral();
    void SetDirection_PeripheralToMemory();
    void SetDirection_MemoryToMemory();
    void SetMemoryIncrementMode();
    void SetPeripheralIncrementMode();
    void SetCircularMode();
    void SetPriorityLow();
    void SetPriorityMedium();
    void SetPriorityHigh();
    void SetPriorityVeryHigh();
    void EnableTransferErrorInterrupt();
    void EnableHalfTransferInterrupt();
    void EnableTransferCompleteInterrupt();

};

class DMA: public Peripheral
{
private:

    DMA_Channel _dmaChannels[7];
    volatile uint32_t* _pDMA_ISR;
    volatile uint32_t* _pDMA_IFCR;
    int _nChannels;
    DMA_IRQ_Handler* _irqHandler;


protected:

    DMA(volatile uint32_t* DMA_CCR, volatile uint32_t* DMA_CNDTR,
            volatile uint32_t* DMA_CPAR, volatile uint32_t* DMA_CMAR,
            volatile uint32_t* _pDMA_ISR, volatile uint32_t* _pDMA_IFCR,
            int nChannels, IRQn_Type* nvicIrqNumbers, uint32_t rccBit);

public:

    void IRQ_Handler(int channel);
    void SetIRQHandler(DMA_IRQ_Handler* handler)
    {
        _irqHandler = handler;
    }
    DMA_Channel* GetChannel(DMA_CHANNEL channelNo);
    virtual bool IsClockEnabled() = 0;


    void ClearTransferComplete(DMA_Channel* channel);
    void ClearHalfTransferComplete(DMA_Channel* channel);
    void ClearTransferError(DMA_Channel* channel);

    bool IsTransferComplete(DMA_Channel* channel);
    bool IsHalfTransferComplete(DMA_Channel* channel);
    bool IsTransferError(DMA_Channel* channel);
    
};

class DMA1: public DMA
{
public:

    static DMA1* GetInstance()
    {
        static DMA1 instance;
        return &instance;
    }

    virtual void EnablePeripheralClock(bool enable);
    virtual bool IsClockEnabled();

private:

    DMA1() :
            DMA(&DMA1_CCR1, &DMA1_CNDTR1, &DMA1_CPAR1, &DMA1_CMAR1, &DMA1_ISR,
                    &DMA1_IFCR, 7, nvicIrqNumbers, RCC_AHBENR_DMA1EN)
    {
    }

    static IRQn_Type nvicIrqNumbers[7];

    DMA1(DMA1 const&);
    void operator=(DMA1 const&);

};

#if defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL)

class DMA2 : public DMA
{
public:

    static DMA2* GetInstance()
    {
        static DMA2 instance;
        return &instance;
    }

    virtual void EnablePeripheralClock(bool enable);
    virtual bool IsClockEnabled();

private:

    DMA2() :
    DMA (&DMA2_CCR1, &DMA2_CNDTR1, &DMA2_CPAR1, &DMA2_CMAR1,
            &DMA2_ISR, &DMA2_IFCR, 5, nvicIrqNumbers, RCC_AHBENR_DMA2EN)
    {
    }

    static IRQn_Type nvicIrqNumbers[5];

    DMA2(DMA2 const&);
    void operator=(DMA2 const&);

};
#endif

class DMA_IRQ_Handler
{
public:
    virtual void HandleInterrupt(DMA_Channel* channel, bool isTransferComplete,
            bool isHalfTransfer, bool isTransferError) = 0;
};

#endif

#endif
