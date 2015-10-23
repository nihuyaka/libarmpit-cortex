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
#include "gpio_cpp.h"
#include "GPIO_Helper.h"


#define ERROR_BIT 1<<16

static BOOL read_temp(SPI* spi, float* temp)
{
	BOOL rc = false;
	uint32_t temp_reg = 0;
	float t_int;

	spi->SetSlaveSelectLow();

	temp_reg = 0;
	for (uint8_t i = 0; i < 4; ++i)
	{
		temp_reg |= (spi->Transmit(0x0) << ((3 - i) * 8)
				& (0xff << ((3 - i) * 8)));
	}

	spi->SetSlaveSelectHigh();

	if (!(temp_reg & ERROR_BIT))
	{
		*temp = (temp_reg >> 18 & 0x3fff) * 0.25;
		t_int = (temp_reg >> 4 & 0xfff) * 0.0625;
		rc = TRUE;
	}

	return rc;
}

static void run()
{
	SPI* spi1 = GPIO_Helper::F1_SetupSPI1_MasterMode(true, true, SPI_BAUD_RATE_128);
	float t;

	RCC_Delay_ms(150);

    read_temp (spi1, &t);
    read_temp (spi1, &t);
    read_temp (spi1, &t);
    read_temp (spi1, &t);

    
	USART1* usart = GPIO_Helper::F1_SetupUSART1(9600, true, true);

    volatile uint8_t in = 0;
    
	while (true)
	{
        usart->WaitRXNE();
        in = usart->Receive();
        if (in == 23) 
        {
            usart->WaitTXE();
            read_temp (spi1, &t);
            usart->SendByte((uint8_t) t);
        }
	}

}

int main(void)
{
	RCC_SetAHBPrescalerDiv4();
	RCC_SetAPB1PrescalerDiv1();
	RCC_SetAPB2PrescalerDiv1();
	RCC_SetADCPrescalerDiv2();
	RCC_EnableHSI(3);

	run();

}
