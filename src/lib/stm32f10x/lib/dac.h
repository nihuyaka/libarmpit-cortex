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

#ifndef _DAC_H
#define _DAC_H

#include "common.h"

#ifdef USE_DAC


#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_XD_VL)


#define DAC_BASE 0x40007400  //APB1

#define DAC_CR       (*(volatile uint32_t*)(DAC_BASE))
#define DAC_SWTRIGR  (*(volatile uint32_t*)(DAC_BASE + 0x04))
#define DAC_DHR12R1  (*(volatile uint32_t*)(DAC_BASE + 0x08))
#define DAC_DHR12L1  (*(volatile uint32_t*)(DAC_BASE + 0x0c))
#define DAC_DHR8R1   (*(volatile uint32_t*)(DAC_BASE + 0x10))
#define DAC_DHR12R2  (*(volatile uint32_t*)(DAC_BASE + 0x14))
#define DAC_DHR12L2  (*(volatile uint32_t*)(DAC_BASE + 0x18))
#define DAC_DHR8R2   (*(volatile uint32_t*)(DAC_BASE + 0x1c))
#define DAC_DHR12RD  (*(volatile uint32_t*)(DAC_BASE + 0x20))
#define DAC_DHR12LD  (*(volatile uint32_t*)(DAC_BASE + 0x24))
#define DAC_DHR8RD   (*(volatile uint32_t*)(DAC_BASE + 0x28))
#define DAC_DOR1     (*(volatile uint32_t*)(DAC_BASE + 0x2c))
#define DAC_DOR2     (*(volatile uint32_t*)(DAC_BASE + 0x30))
#define DAC_DHR8RD   (*(volatile uint32_t*)(DAC_BASE + 0x28))
#define DAC_SR       (*(volatile uint32_t*)(DAC_BASE + 0x34))

#define DAC_CR_EN1   (1<<0)  //channel 1 enable
#define DAC_CR_BOFF1 (1<<1)  //1: output buffer disabled
#define DAC_CR_TEN1  (1<<2)  //channel 1 trigger enable
#define DAC_CR_TSEL1_TIM6  (0<<3)
#define DAC_CR_TSEL1_TIM3  (1<<3)
#define DAC_CR_TSEL1_TIM7  (2<<3)
#define DAC_CR_TSEL1_TIM5  (3<<3)
#define DAC_CR_TSEL1_TIM2  (4<<3)
#define DAC_CR_TSEL1_TIM4  (5<<3)
#define DAC_CR_TSEL1_EXT9  (6<<3)
#define DAC_CR_TSEL1_SW    (7<<3)
#define DAC_CR_WAVE1_OFF   (0<<6)
#define DAC_CR_WAVE1_NOISE (1<<6)
#define DAC_CR_WAVE1_TRI   (2<<6)
#define DAC_CR_AMPL1        8
//Bits 11:8MAMP1[3:0]
#define DAC_CR_DMAEN1      (1<<12)
#define DAC_CR_DMAUDRIE1   (1<<13) //DMA underrun interrupt enable

#define DAC_CR_EN2   (1<<16)  //channel 2 enable
#define DAC_CR_BOFF2 (1<<17)  //1: output buffer disabled
#define DAC_CR_TEN2  (1<<18)  //channel 2 trigger enable
#define DAC_CR_TSEL2_TIM6  (0<<19)
#define DAC_CR_TSEL2_TIM3  (1<<19)
#define DAC_CR_TSEL2_TIM7  (2<<19)
#define DAC_CR_TSEL2_TIM5  (3<<19)
#define DAC_CR_TSEL2_TIM2  (4<<19)
#define DAC_CR_TSEL2_TIM4  (5<<19)
#define DAC_CR_TSEL2_EXT9  (6<<19)
#define DAC_CR_TSEL2_SW    (7<<19)
#define DAC_CR_WAVE2_OFF   (0<<22)
#define DAC_CR_WAVE2_NOISE (1<<22)
#define DAC_CR_WAVE2_TRI   (2<<22)
//Bits 27:24MAMP2[3:0]
#define DAC_CR_AMPL2        24
#define DAC_CR_DMAEN2      (1<<28)
#define DAC_CR_DMAUDRIE2   (1<<29) //DMA underrun interrupt enable

#define DAC_SWTRIGR_1  (1<<0)
#define DAC_SWTRIGR_2  (1<<1)

#define DAC_SR_DMAUDR1 (1<<13)
#define DAC_SR_DMAUDR2 (1<<29)

enum DAC_AMPLITUDE
{
    DAC_CR_AMPL_1 = 0,
    DAC_CR_AMPL_3 = 1,
    DAC_CR_AMPL_7 = 2,
    DAC_CR_AMPL_15 = 3,
    DAC_CR_AMPL_31 = 4,
    DAC_CR_AMPL_63 = 5,
    DAC_CR_AMPL_127 = 6,
    DAC_CR_AMPL_255 = 7,
    DAC_CR_AMPL_511 = 8,
    DAC_CR_AMPL_1023 = 9,
    DAC_CR_AMPL_2047 = 10,
    DAC_CR_AMPL_4095 = 11
};

#endif

#endif

#endif
