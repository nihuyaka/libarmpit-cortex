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


#ifndef _DMA_H
#define _DMA_H 

#include "common.h"

#ifdef USE_DMA


#define DMA1_BASE 0x40020000  //AHB
#define DMA2_BASE 0x40020400  //AHB, HD

//interrupt status register
#define DMA1_ISR    (*(volatile uint32_t*)(DMA1_BASE))
#define DMA1_IFCR   (*(volatile uint32_t*)(DMA1_BASE + 0x4))

//configuration register
#define DMA1_CCR1   (*(volatile uint32_t*)(DMA1_BASE + 0x08 + 20*(1-1)))
#define DMA1_CCR2   (*(volatile uint32_t*)(DMA1_BASE + 0x08 + 20*(2-1)))
#define DMA1_CCR3   (*(volatile uint32_t*)(DMA1_BASE + 0x08 + 20*(3-1)))
#define DMA1_CCR4   (*(volatile uint32_t*)(DMA1_BASE + 0x08 + 20*(4-1)))
#define DMA1_CCR5   (*(volatile uint32_t*)(DMA1_BASE + 0x08 + 20*(5-1)))
#define DMA1_CCR6   (*(volatile uint32_t*)(DMA1_BASE + 0x08 + 20*(6-1)))
#define DMA1_CCR7   (*(volatile uint32_t*)(DMA1_BASE + 0x08 + 20*(7-1)))

//data register
#define DMA1_CNDTR1   (*(volatile uint32_t*)(DMA1_BASE + 0x0c + 20*(1-1)))
#define DMA1_CNDTR2   (*(volatile uint32_t*)(DMA1_BASE + 0x0c + 20*(2-1)))
#define DMA1_CNDTR3   (*(volatile uint32_t*)(DMA1_BASE + 0x0c + 20*(3-1)))
#define DMA1_CNDTR4   (*(volatile uint32_t*)(DMA1_BASE + 0x0c + 20*(4-1)))
#define DMA1_CNDTR5   (*(volatile uint32_t*)(DMA1_BASE + 0x0c + 20*(5-1)))
#define DMA1_CNDTR6   (*(volatile uint32_t*)(DMA1_BASE + 0x0c + 20*(6-1)))
#define DMA1_CNDTR7   (*(volatile uint32_t*)(DMA1_BASE + 0x0c + 20*(7-1)))

//peripheral address register
#define DMA1_CPAR1   (*(volatile uint32_t*)(DMA1_BASE + 0x10 + 20*(1-1)))
#define DMA1_CPAR2   (*(volatile uint32_t*)(DMA1_BASE + 0x10 + 20*(2-1)))
#define DMA1_CPAR3   (*(volatile uint32_t*)(DMA1_BASE + 0x10 + 20*(3-1)))
#define DMA1_CPAR4   (*(volatile uint32_t*)(DMA1_BASE + 0x10 + 20*(4-1)))
#define DMA1_CPAR5   (*(volatile uint32_t*)(DMA1_BASE + 0x10 + 20*(5-1)))
#define DMA1_CPAR6   (*(volatile uint32_t*)(DMA1_BASE + 0x10 + 20*(6-1)))
#define DMA1_CPAR7   (*(volatile uint32_t*)(DMA1_BASE + 0x10 + 20*(7-1)))

#define DMA1_CMAR1   (*(volatile uint32_t*)(DMA1_BASE + 0x14 + 20*(1-1)))
#define DMA1_CMAR2   (*(volatile uint32_t*)(DMA1_BASE + 0x14 + 20*(2-1)))
#define DMA1_CMAR3   (*(volatile uint32_t*)(DMA1_BASE + 0x14 + 20*(3-1)))
#define DMA1_CMAR4   (*(volatile uint32_t*)(DMA1_BASE + 0x14 + 20*(4-1)))
#define DMA1_CMAR5   (*(volatile uint32_t*)(DMA1_BASE + 0x14 + 20*(5-1)))
#define DMA1_CMAR6   (*(volatile uint32_t*)(DMA1_BASE + 0x14 + 20*(6-1)))
#define DMA1_CMAR7   (*(volatile uint32_t*)(DMA1_BASE + 0x14 + 20*(7-1)))

#define DMA2_ISR    (*(volatile uint32_t*)(DMA2_BASE))
#define DMA2_IFCR   (*(volatile uint32_t*)(DMA2_BASE + 0x4))

//configuration register
#define DMA2_CCR1   (*(volatile uint32_t*)(DMA2_BASE + 0x08 + 20*(1-1)))
#define DMA2_CCR2   (*(volatile uint32_t*)(DMA2_BASE + 0x08 + 20*(2-1)))
#define DMA2_CCR3   (*(volatile uint32_t*)(DMA2_BASE + 0x08 + 20*(3-1)))
#define DMA2_CCR4   (*(volatile uint32_t*)(DMA2_BASE + 0x08 + 20*(4-1)))
#define DMA2_CCR5   (*(volatile uint32_t*)(DMA2_BASE + 0x08 + 20*(5-1)))
#define DMA2_CCR6   (*(volatile uint32_t*)(DMA2_BASE + 0x08 + 20*(6-1)))
#define DMA2_CCR7   (*(volatile uint32_t*)(DMA2_BASE + 0x08 + 20*(7-1)))

//data register
#define DMA2_CNDTR1   (*(volatile uint32_t*)(DMA2_BASE + 0x0c + 20*(1-1)))
#define DMA2_CNDTR2   (*(volatile uint32_t*)(DMA2_BASE + 0x0c + 20*(2-1)))
#define DMA2_CNDTR3   (*(volatile uint32_t*)(DMA2_BASE + 0x0c + 20*(3-1)))
#define DMA2_CNDTR4   (*(volatile uint32_t*)(DMA2_BASE + 0x0c + 20*(4-1)))
#define DMA2_CNDTR5   (*(volatile uint32_t*)(DMA2_BASE + 0x0c + 20*(5-1)))
#define DMA2_CNDTR6   (*(volatile uint32_t*)(DMA2_BASE + 0x0c + 20*(6-1)))
#define DMA2_CNDTR7   (*(volatile uint32_t*)(DMA2_BASE + 0x0c + 20*(7-1)))

//peripheral address register
#define DMA2_CPAR1   (*(volatile uint32_t*)(DMA2_BASE + 0x10 + 20*(1-1)))
#define DMA2_CPAR2   (*(volatile uint32_t*)(DMA2_BASE + 0x10 + 20*(2-1)))
#define DMA2_CPAR3   (*(volatile uint32_t*)(DMA2_BASE + 0x10 + 20*(3-1)))
#define DMA2_CPAR4   (*(volatile uint32_t*)(DMA2_BASE + 0x10 + 20*(4-1)))
#define DMA2_CPAR5   (*(volatile uint32_t*)(DMA2_BASE + 0x10 + 20*(5-1)))
#define DMA2_CPAR6   (*(volatile uint32_t*)(DMA2_BASE + 0x10 + 20*(6-1)))
#define DMA2_CPAR7   (*(volatile uint32_t*)(DMA2_BASE + 0x10 + 20*(7-1)))

#define DMA2_CMAR1   (*(volatile uint32_t*)(DMA2_BASE + 0x14 + 20*(1-1)))
#define DMA2_CMAR2   (*(volatile uint32_t*)(DMA2_BASE + 0x14 + 20*(2-1)))
#define DMA2_CMAR3   (*(volatile uint32_t*)(DMA2_BASE + 0x14 + 20*(3-1)))
#define DMA2_CMAR4   (*(volatile uint32_t*)(DMA2_BASE + 0x14 + 20*(4-1)))
#define DMA2_CMAR5   (*(volatile uint32_t*)(DMA2_BASE + 0x14 + 20*(5-1)))
#define DMA2_CMAR6   (*(volatile uint32_t*)(DMA2_BASE + 0x14 + 20*(6-1)))
#define DMA2_CMAR7   (*(volatile uint32_t*)(DMA2_BASE + 0x14 + 20*(7-1)))

#define DMA_ISR_GIF1  (1<<0)
#define DMA_ISR_TCIF1 (1<<1)
#define DMA_ISR_HTIF1 (1<<2)
#define DMA_ISR_TEIF1 (1<<3)
#define DMA_ISR_GIF2  (1<<4)
#define DMA_ISR_TCIF2 (1<<5)
#define DMA_ISR_HTIF2 (1<<6)
#define DMA_ISR_TEIF2 (1<<7)
#define DMA_ISR_GIF3  (1<<8)
#define DMA_ISR_TCIF3 (1<<9)
#define DMA_ISR_HTIF3 (1<<10)
#define DMA_ISR_TEIF3 (1<<11)
#define DMA_ISR_GIF4  (1<<12)
#define DMA_ISR_TCIF4 (1<<13)
#define DMA_ISR_HTIF4 (1<<14)
#define DMA_ISR_TEIF4 (1<<15)
#define DMA_ISR_GIF5  (1<<16)
#define DMA_ISR_TCIF5 (1<<17)
#define DMA_ISR_HTIF5 (1<<18)
#define DMA_ISR_TEIF5 (1<<19)
#define DMA_ISR_GIF6  (1<<20)
#define DMA_ISR_TCIF6 (1<<21)
#define DMA_ISR_HTIF6 (1<<22)
#define DMA_ISR_TEIF6 (1<<23)
#define DMA_ISR_GIF7  (1<<24)
#define DMA_ISR_TCIF7 (1<<25)
#define DMA_ISR_HTIF7 (1<<26)
#define DMA_ISR_TEIF7 (1<<27)

#define DMA_IFCR_CGIF1  (1<<0)
#define DMA_IFCR_CTCIF1 (1<<1)
#define DMA_IFCR_CHTIF1 (1<<2)
#define DMA_IFCR_CTEIF1 (1<<3)
#define DMA_IFCR_CGIF2  (1<<4)
#define DMA_IFCR_CTCIF2 (1<<5)
#define DMA_IFCR_CHTIF2 (1<<6)
#define DMA_IFCR_CTEIF2 (1<<7)
#define DMA_IFCR_CGIF3  (1<<8)
#define DMA_IFCR_CTCIF3 (1<<9)
#define DMA_IFCR_CHTIF3 (1<<10)
#define DMA_IFCR_CTEIF3 (1<<11)
#define DMA_IFCR_CGIF4  (1<<12)
#define DMA_IFCR_CTCIF4 (1<<13)
#define DMA_IFCR_CHTIF4 (1<<14)
#define DMA_IFCR_CTEIF4 (1<<15)
#define DMA_IFCR_CGIF5  (1<<16)
#define DMA_IFCR_CTCIF5 (1<<17)
#define DMA_IFCR_CHTIF5 (1<<18)
#define DMA_IFCR_CTEIF5 (1<<19)
#define DMA_IFCR_CGIF6  (1<<20)
#define DMA_IFCR_CTCIF6 (1<<21)
#define DMA_IFCR_CHTIF6 (1<<22)
#define DMA_IFCR_CTEIF6 (1<<23)
#define DMA_IFCR_CGIF7  (1<<24)
#define DMA_IFCR_CTCIF7 (1<<25)
#define DMA_IFCR_CHTIF7 (1<<26)
#define DMA_IFCR_CTEIF7 (1<<27)

#define DMA_CCR_EN   (1<<0)
#define DMA_CCR_TCIE (1<<1)
#define DMA_CCR_HTIE (1<<2)
#define DMA_CCR_TEIE (1<<3)
#define DMA_CCR_DIR  (1<<4)
#define DMA_CCR_CIRC (1<<5)
#define DMA_CCR_PINC (1<<6)
#define DMA_CCR_MINC (1<<7)
#define DMA_CCR_PSIZE_8  (0<<8)
#define DMA_CCR_PSIZE_16 (1<<8)
#define DMA_CCR_PSIZE_32 (2<<8)
#define DMA_CCR_MSIZE_8  (0<<10)
#define DMA_CCR_MSIZE_16 (1<<10)
#define DMA_CCR_MSIZE_32 (2<<10)
#define DMA_CCR_PL_LOW   (0<<12)
#define DMA_CCR_PL_MED   (1<<12)
#define DMA_CCR_PL_HI    (2<<12)
#define DMA_CCR_PL_VHI   (3<<12)
#define DMA_CCR_MEM2MEM  (1<<14)

enum DMA_CHANNEL
{
    DMA_CHANNEL_1 = 0,
    DMA_CHANNEL_2 = 1,
    DMA_CHANNEL_3 = 2,
    DMA_CHANNEL_4 = 3,
    DMA_CHANNEL_5 = 4,
    DMA_CHANNEL_6 = 5,
    DMA_CHANNEL_7 = 6

};

#endif

#endif
