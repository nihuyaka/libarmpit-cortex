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



class DMA_Stream
{
    friend class DMA;

private:
    DMA_Stream(){}

    volatile uint32_t* _pDMA_ISR;
    volatile uint32_t* _pDMA_IFCR;

    volatile uint32_t* _pDMA_SCR;
    volatile uint32_t* _pDMA_SNDTR;
    volatile uint32_t* _pDMA_SPAR;
    volatile uint32_t* _pDMA_SM0AR;
    volatile uint32_t* _pDMA_SM1AR;
    volatile uint32_t* _pDMA_SFCR;
        
    uint32_t  _FEIF;    
    uint32_t  _DMEIF;    
    uint32_t  _TEIF;    
    uint32_t  _HTIF;    
    uint32_t  _TCIF;    

    IRQn_Type _nvicIrqNumber;

    uint8_t  _streamNumber;
    uint8_t  _channelNumber;

    DMA_Stream(DMA_Stream const&);
    void operator=(DMA_Stream const&);
        
        

public:
    void EnableStream(bool enable);

    void EnableDirectModeErrorInterrupt(bool enable);
    void EnableTransferErrorInterrupt(bool enable);
    void EnableHalfTransferInterrupt(bool enable);
    void EnableTransferCompleteInterrupt(bool enable);
    void EnableFIFOErrorInterrupt(bool enable);

    bool IsDirectModeError();
    bool IsTransferComplete();
    bool IsHalfTransferComplete();
    bool IsTransferError();
    bool IsFIFOError();

    void ClearDirectModeError();
    void ClearTransferComplete();
    void ClearHalfTransferComplete();
    void ClearTransferError();
    void ClearFIFOError();


    void SetChannel (DMA_CHANNEL channel);
    void SetPFCTR (bool set);

    void SetDirection_MemoryToPeripheral();
    void SetDirection_PeripheralToMemory();
    void SetDirection_MemoryToMemory();
    void SetCircularMode(bool set);
    void SetMemoryIncrementMode(bool set);
    void SetPeripheralIncrementMode(bool set);
    void SetPeripheralSize_8bits();
    void SetPeripheralSize_16bits();
    void SetPeripheralSize_32bits();
    void SetMemorySize_8bits();
    void SetMemorySize_16bits();
    void SetMemorySize_32bits();
    void SetPeripheralIncOffsetSize(bool set);
    void SetPriorityLow();
    void SetPriorityMedium();
    void SetPriorityHigh();
    void SetPriorityVeryHigh();
    void EnableDoubleBufferMode (bool enable);        
    void SetPBURST_INCR4();
    void SetPBURST_INCR8();
    void SetPBURST_INCR16();
    void SetMBURST_INCR4();
    void SetMBURST_INCR8();
    void SetMBURST_INCR16();
    

    void SetPeripheralAddress(uint32_t addr);
    void SetMemory0Address(uint32_t addr);
    void SetMemory1Address(uint32_t addr);
    void SetNumberOfData(uint16_t);

    


};

class DMA: public Peripheral
{
private:

    DMA_Stream _dmaStreams[7];
    DMA_IRQ_Handler* _irqHandler;

protected:
    
    DMA(uint8_t DMA_number, IRQn_Type* nvicIrqNumbers);


public:

    void IRQ_Handler(int stream);
    void SetIRQHandler(DMA_IRQ_Handler* handler)
    {
        _irqHandler = handler;
    }
    DMA_Stream* GetStream(DMA_STREAM_N streamNo);

};

class DMA1: public DMA
{
public:

    static DMA1* GetInstance()
    {
        static DMA1 instance;
        return &instance;
    }

private:

    DMA1() :
            DMA(1, nvicIrqNumbers)
    {
    }

    static IRQn_Type nvicIrqNumbers[8];

    DMA1(DMA1 const&);
    void operator=(DMA1 const&);

};

class DMA2: public DMA
{
public:

    static DMA2* GetInstance()
    {
        static DMA2 instance;
        return &instance;
    }

private:

    DMA2() :
            DMA(2, nvicIrqNumbers)
    {
    }

    static IRQn_Type nvicIrqNumbers[8];

    DMA2(DMA2 const&);
    void operator=(DMA2 const&);

};


class DMA_IRQ_Handler
{
public:
    virtual void HandleInterrupt(DMA_Stream* stream, bool isTransferComplete,
            bool isHalfTransfer, bool isTransferError) = 0;
};

#endif

#endif
