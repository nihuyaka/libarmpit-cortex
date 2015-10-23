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



#include "TempLM74.h"
#include "gpio_cpp.h"
#include "spi_cpp.h"
#include "usart_cpp.h"
#include "rcc_cpp.h"
#include "dma_cpp.h"


//Not used, just an example how an interrupt handler could be used
//for async communication, reacting to RXNE/TXE

class USART1_IRQ_Handler: public USART_IRQ_Handler
{
private:

    TempLM74* _lm74;

public:

    USART1_IRQ_Handler(TempLM74* lm74)
    {
        _lm74 = lm74;
    }

    virtual void Handle(USART* usart, USART_IRQ_Info info)
    {
        static int t = 0;

        if (info.isFrameError || info.isOverrun || info.isNoiseError
                || info.isPE)
        {
            volatile int i = 0;
        }

        if (info.isTXE)
        {
            t = (int) _lm74->GetTemp();
            if (t > -60)
                usart->Send((uint8_t) t);
        }

        if (info.isRXNE)
        {
            volatile int i = 0;
        }

        if (info.isTC)
        {

            volatile int i = 0;
        }

    }

};



//reads LM74 temperature via SPI and sends it to peer. 
//peer initiates read by sending byte with a value of 23 (decimal)
static void temp_read() 
{
    GPIOA::GetInstance()->EnablePeripheralClock(true);
    GPIOA::GetInstance()->SetupGPIO_OutPP(GPIO_PIN4); //NSS  slave select

    SPI1* spi1 = SPI1::GetInstance();
    spi1->Enable(true);

    bool isMaster = true;
    bool isFullDuplex = true;
    bool isClockPhase2 = true;
    bool isClockPolarity1 = true;
    bool isLSBFirst = false;
    bool isSetSSM = true;
    bool initializeGPIO = true;

    spi1->Initialize(isMaster, isFullDuplex, SPI::SPI_BAUD_RATE_256,
            isClockPhase2, isClockPolarity1, isLSBFirst, isSetSSM,
            initializeGPIO);

    spi1->PullDownInputPin();

    TempLM74 lm74(spi1);
    lm74.Init();

    USART1* usart = USART1::GetInstance();

    usart->Enable(true);
    usart->SetBaudRate(9600);
    usart->EnableTransmitter(true);
    usart->EnableReceiver(true);

    volatile uint8_t in = 0;
    while(1)
    {
        usart->WaitRXNE();
        in = usart->Receive();
        if (in == 23) 
        {
            usart->WaitTXE();
            uint32_t t = (int) lm74.GetTemp();
            usart->Send((uint8_t) t);
        }
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

    temp_read() ;
}
