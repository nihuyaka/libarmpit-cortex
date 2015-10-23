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



#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_XD_VL)

#include "dac_cpp.h"
#include <math.h>
#include "gpio_cpp.h"
#include "dma_cpp.h"

static const uint32_t nsteps = 60;
static uint16_t data[nsteps];

class DAC_IRQ_Handler1: public DAC_IRQ_Handler
{
public:
    virtual void HandleInterrupt(DAC_CHANNEL channelNo)
    {
    }
};

static void GenerateData()
{
    for (uint32_t i = 0; i <= nsteps; i += 1)
    {
        data[i] = (int) ((sin(2 * 3.14159 * (float) i / (float) nsteps) + 1.)
                * (float) (0xfff + 1) / 2.);
    }
}

static void DAC_Test()
{

    GenerateData();

    GPIOA* portA = GPIOA::GetInstance();
    portA->EnablePeripheralClock(true);
    portA->SetupGPIO_InAnalog(GPIO_PIN4); //DAC pin

    DAC* dac = DAC::GetInstance();
    dac->EnablePeripheralClock(true);
    DAC_Channel* ch = dac->GetChannel(DAC_CHANNEL_1);
    ch->SelectDataRegister12R();
    ch->SetAmplitude(DAC_CR_AMPL_2047);
    ch->EnableTriangleWaveGeneration();
    ch->EnableChannel();
    //ch->Write

}

static void DAC_Test_DMA()
{

    GenerateData();

    GPIOA* portA = GPIOA::GetInstance();
    portA->EnablePeripheralClock(true);
    portA->SetupGPIO_InAnalog(GPIO_PIN4); //DAC pin

    DAC* dac = DAC::GetInstance();
    dac->EnablePeripheralClock(true);
    dac->SetIrqHandler(new DAC_IRQ_Handler1());

    DAC_Channel* dacCh = dac->GetChannel(DAC_CHANNEL_1);
    dacCh->SelectTriggerTimer6();
    dacCh->EnableUnderrunInterrupt();
    dacCh->SelectDataRegister12R();

    uint32_t dacDataAddr = (uint32_t) dacCh->GetDataRegisterAddress();

    DMA1* dma1 = DMA1::GetInstance();
    dma1->EnablePeripheralClock(true);
    DMA_Channel* dmaCh3 = dma1->GetChannel(DMA_CHANNEL_3);
    dmaCh3->SetPeripheralAddress(dacDataAddr);
    dmaCh3->SetMemoryAddress((uint32_t) data);
    dmaCh3->SetCircularMode();
    dmaCh3->SetDirection_MemoryToPeripheral();
    dmaCh3->SetMemorySize_16bits();
    dmaCh3->SetPeripheralSize_16bits();
    dmaCh3->SetNumberOfData(nsteps);
    dmaCh3->SetMemoryIncrementMode();
    dmaCh3->SetPriorityHigh();

    dacCh->EnableChannel();
    dacCh->EnableDMA();


}

int main()
{
    RCC* rcc = RCC::GetInstance();
    rcc->SetAHBPrescalerDiv4();
    rcc->SetAPB1PrescalerDiv1();
    rcc->SetAPB2PrescalerDiv1();
    rcc->SetADCPrescalerDiv2();
    rcc->EnableHSI(3);

    DAC_Test_DMA();
}


#endif

