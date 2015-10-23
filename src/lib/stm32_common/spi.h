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


#ifndef _SPI_H
#define _SPI_H

#include "common.h"

#ifdef USE_SPI

#define SPI1_BASE 0x40013000  //APB2

#define SPI1_CR1    (*(volatile uint32_t*)(SPI1_BASE))
#define SPI1_CR2    (*(volatile uint32_t*)(SPI1_BASE + 0x4))
#define SPI1_SR     (*(volatile uint32_t*)(SPI1_BASE + 0x8))    
#define SPI1_DR     (*(volatile uint32_t*)(SPI1_BASE + 0xc))        
#define SPI1_CRCPR   (*(volatile uint32_t*)(SPI1_BASE + 0x10))      
#define SPI1_RXCRCR (*(volatile uint32_t*)(SPI1_BASE + 0x14))       
#define SPI1_TXCRCR (*(volatile uint32_t*)(SPI1_BASE + 0x18))           


#if defined(STM32F10X_MD) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD)\
        || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL)\
        || defined(STM32F4)  || defined(STM32L0)

#define SPI2_BASE 0x40003800  //APB1

#define SPI2_CR1    (*(volatile uint32_t*)(SPI2_BASE))
#define SPI2_CR2    (*(volatile uint32_t*)(SPI2_BASE + 0x4))
#define SPI2_SR     (*(volatile uint32_t*)(SPI2_BASE + 0x8))    
#define SPI2_DR     (*(volatile uint32_t*)(SPI2_BASE + 0xc))        
#define SPI2_CRCPR  (*(volatile uint32_t*)(SPI2_BASE + 0x10))       
#define SPI2_RXCRCR (*(volatile uint32_t*)(SPI2_BASE + 0x14))       
#define SPI2_TXCRCR (*(volatile uint32_t*)(SPI2_BASE + 0x18))           

#endif


#if defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL)\
        || defined(STM32F4)



#define SPI3_BASE 0x40003C00  //APB1 (High density 100x, all 10x)
#define SPI3_CR1    (*(volatile uint32_t*)(SPI3_BASE))
#define SPI3_CR2    (*(volatile uint32_t*)(SPI3_BASE + 0x4))
#define SPI3_SR     (*(volatile uint32_t*)(SPI3_BASE + 0x8))    
#define SPI3_DR     (*(volatile uint32_t*)(SPI3_BASE + 0xc))        
#define SPI3_CRCPR  (*(volatile uint32_t*)(SPI3_BASE + 0x10))       
#define SPI3_RXCRCR (*(volatile uint32_t*)(SPI3_BASE + 0x14))       
#define SPI3_TXCRCR (*(volatile uint32_t*)(SPI3_BASE + 0x18))           

#endif


#define SPI_CR1_CPHA_FIRST       (0<<0)
#define SPI_CR1_CPHA_SECOND      (1<<0)
#define SPI_CR1_CPOL_0           (0<<1)
#define SPI_CR1_CPOL_1           (1<<1)
#define SPI_CR1_SLAVE            (0<<2)
#define SPI_CR1_MASTER           (1<<2)
#define SPI_CR1_BR_FPCLK_DIV_2   (0<<3)
#define SPI_CR1_BR_FPCLK_DIV_4   (1<<3) 
#define SPI_CR1_BR_FPCLK_DIV_8   (2<<3) 
#define SPI_CR1_BR_FPCLK_DIV_16  (3<<3)
#define SPI_CR1_BR_FPCLK_DIV_32  (4<<3)
#define SPI_CR1_BR_FPCLK_DIV_64  (5<<3)
#define SPI_CR1_BR_FPCLK_DIV_128 (6<<3)
#define SPI_CR1_BR_FPCLK_DIV_256 (7<<3)
#define SPI_CR1_SPE_ENABLED      (1<<6)
#define SPI_CR1_LSBFIRST_OFF     (0<<7)
#define SPI_CR1_LSBFIRST_ON      (1<<7)
#define SPI_CR1_SSI              (1<<8)
#define SPI_CR1_SSM              (1<<9) 
#define SPI_CR1_RXONLY           (1<<10) 
#define SPI_CR1_DFF_8_BIT        (0<<11)
#define SPI_CR1_DFF_16_BIT       (1<<11)
#define SPI_CR1_CRCNEXT          (1<<12) 
#define SPI_CR1_CRCEN            (1<<13) 
#define SPI_CR1_BIDIOE           (1<<14) 
#define SPI_CR1_BIDIMODE         (1<<14) 


#define SPI_CR2_RXDMAEN         (1<<0)
#define SPI_CR2_TXDMAEN         (1<<1)
#define SPI_CR2_SSOE            (1<<2)
#define SPI_CR2_ERRIE           (1<<5)
#define SPI_CR2_RXNEIE          (1<<6) 
#define SPI_CR2_TXEIE           (1<<7) 

#define SPI_SR_RXNE             (1<<0) 
#define SPI_SR_TXE              (1<<1) 
#define SPI_SR_CRCERR           (1<<4)
#define SPI_SR_MODF             (1<<5) 
#define SPI_SR_OVR              (1<<6) 
#define SPI_SR_BSY              (1<<7) 


void  InitSPI (int spi_number);
void  DisableSPI(int spi_number);
int   SendByte (uint8_t byte, int spi_number); 
int   ReadByte (uint8_t* byte, int spi_number);

#endif

#endif
