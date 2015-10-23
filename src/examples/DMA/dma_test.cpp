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

class DMA1_IRQ_Handler: public DMA_IRQ_Handler
{
public:
    virtual void HandleInterrupt(DMA_Channel* channel, bool isTransferComplete,
            bool isHalfTransfer, bool isTransferError)
    {
        //volatile bool complete = isTransferComplete;
        //volatile bool half = isHalfTransfer;
        //volatile bool err = isTransferError;
    }

    virtual ~DMA1_IRQ_Handler()
    {
    }

};

uint32_t from[3] = { 1, 2, 3 };
uint32_t to[3] =   { 0, 0, 0 };

static void DMA_Test()
{

    DMA1* dma1 = DMA1::GetInstance();
    dma1->EnablePeripheralClock(true);
    //dma1->SetIRQHandler (new DMA1_IRQ_Handler());
    DMA_Channel* ch3 = dma1->GetChannel(DMA_CHANNEL_2);
    ch3->EnableTransferCompleteInterrupt();
    ch3->EnableTransferErrorInterrupt();
    ch3->SetDirection_MemoryToMemory();
    ch3->SetCircularMode();
    ch3->SetMemorySize_32bits();
    ch3->SetPeripheralSize_32bits();
    ch3->SetMemoryIncrementMode();
    ch3->SetPeripheralIncrementMode();
    ch3->SetPriorityHigh();
    ch3->SetNumberOfData(3);
    ch3->SetMemoryAddress((uint32_t) to);
    ch3->SetPeripheralAddress((uint32_t) from);

    ch3->EnableChannel(true);
    ;
    while (1)
    {
    }

}

int main()
{
    RCC* rcc = RCC::GetInstance();
    rcc->SetAHBPrescalerDiv4();
    rcc->SetAPB1PrescalerDiv1();
    rcc->SetAPB2PrescalerDiv1();
    rcc->SetADCPrescalerDiv2();
    rcc->EnableHSI(3);

    DMA_Test();
}
