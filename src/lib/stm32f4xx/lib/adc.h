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


#ifndef _ADC_H
#define _ADC_H

#include "common.h"


#ifdef USE_ADC

#define ADC1_BASE  0x40012000
#define ADC2_BASE  0x40012100
#define ADC3_BASE  0x40012200
#define ADC_COMMON 0x40012300


enum ADC_CHANNEL
{
    ADC_IN0 = 0,
    ADC_IN1 = 1,
    ADC_IN2 = 2,
    ADC_IN3 = 3,
    ADC_IN4 = 4,
    ADC_IN5 = 5,
    ADC_IN6 = 6,
    ADC_IN7 = 7,
    ADC_IN8 = 8,
    ADC_IN9 = 9,
    ADC_IN10 = 10,
    ADC_IN11 = 11,
    ADC_IN12 = 12,
    ADC_IN13 = 13,
    ADC_IN14 = 14,
    ADC_IN15 = 15,
#if defined(STM32F401xC)  || defined(STM32F401xE) || defined(STM32F401xx) ||\
	defined(STM32F405xx) || defined(STM32F407xx) || defined(STM32F411xE) ||\
	defined(STM32F415xx) || defined(STM32F417xx)
    ADC_TEMP = 16,
#else
    ADC_TEMP = 18,
    ADC_VBAT = 18,
#endif
    ADC_VREFINT = 17,
    ADC_ALL = 0xff
};

#define ADC1_SR    (*(volatile uint32_t*)(ADC1_BASE))
#define ADC2_SR    (*(volatile uint32_t*)(ADC2_BASE))
#define ADC3_SR    (*(volatile uint32_t*)(ADC3_BASE))

#define ADC_SR_AWD   (1<<0)  //Analog watchdog flag
#define ADC_SR_EOC   (1<<1)  //End of conversion
#define ADC_SR_JEOC  (1<<2)  //End of conversion (injected channel)
#define ADC_SR_JSTRT (1<<3)  //Injected channel Start flag
#define ADC_SR_STRT  (1<<4)  //Regular channel Start flag
#define ADC_SR_OVR   (1<<5)

#define ADC1_CR1   (*(volatile uint32_t*)(ADC1_BASE + 0x4))
#define ADC2_CR1   (*(volatile uint32_t*)(ADC2_BASE + 0x4))
#define ADC3_CR1   (*(volatile uint32_t*)(ADC3_BASE + 0x4))

#define ADC_CR1_AWDCH  (1<<0)
#define ADC_CR1_EOCIE  (1<<5)  
#define ADC_CR1_AWDIE  (1<<6)  
#define ADC_CR1_JEOCIE (1<<7)  
#define ADC_CR1_SCAN   (1<<8)  
#define ADC_CR1_AWDSGL (1<<9)  
#define ADC_CR1_JAUTO  (1<<10) 
#define ADC_CR1_DISCEN (1<<11) 
#define ADC_CR1_JDISCEN (1<<12) 
#define ADC_CR1_DISCNUM (1<<13)
#define ADC_CR1_JAWDEN (1<<22) 
#define ADC_CR1_AWDEN (1<<23)
  
#define ADC_CR1_RES_12BIT  (0<<24)
#define ADC_CR1_RES_10BIT  (1<<24)
#define ADC_CR1_RES_8BIT   (2<<24)
#define ADC_CR1_RES_6BIT   (3<<24)
#define ADC_CR1_RES_CLEARMASK   (3<<24)
#define ADC_CR1_OVRIE  (1<<26)

#define ADC1_CR2   (*(volatile uint32_t*)(ADC1_BASE + 0x8))
#define ADC2_CR2   (*(volatile uint32_t*)(ADC2_BASE + 0x8))
#define ADC3_CR2   (*(volatile uint32_t*)(ADC3_BASE + 0x8))

#define ADC_CR2_ADON   (1<<0)  // A/D converter ON / OFF
#define ADC_CR2_CONT   (1<<1)  // Continuous conversion
#define ADC_CR2_DMA    (1<<8)
#define ADC_CR2_DDS    (1<<9)
#define ADC_CR2_EOCS   (1<<10)

#define ADC_CR2_ALIGN    (1<<11)  //0: left 1:right

#define ADC_CR2_JEXTSEL_T1CC1   (0<<16)
#define ADC_CR2_JEXTSEL_T1CC2   (1<<16)
#define ADC_CR2_JEXTSEL_T1CC3   (2<<16)
#define ADC_CR2_JEXTSEL_T2CC2   (3<<16)
#define ADC_CR2_JEXTSEL_T2CC3   (4<<16)
#define ADC_CR2_JEXTSEL_T2CC4   (5<<16)
#define ADC_CR2_JEXTSEL_T2TRGO  (6<<16)
#define ADC_CR2_JEXTSEL_T3CC1   (7<<16)
#define ADC_CR2_JEXTSEL_T3TRGO  (8<<16)
#define ADC_CR2_JEXTSEL_T4CC4   (9<<16)
#define ADC_CR2_JEXTSEL_T5CC1   (10<<16)
#define ADC_CR2_JEXTSEL_T5CC2   (11<<16)
#define ADC_CR2_JEXTSEL_T5CC3   (12<<16)
#define ADC_CR2_JEXTSEL_T8CC1   (13<<16)
#define ADC_CR2_JEXTSEL_T8TRGO  (14<<16)
#define ADC_CR2_JEXTSEL_EXTI11  (15<<16)
#define ADC_CR2_JEXTSEL_CLEARMASK  (15<<16)

#define ADC_CR2_JEXTEN_OFF       (0<<20)
#define ADC_CR2_JEXTEN_RISING    (1<<20)
#define ADC_CR2_JEXTEN_FALLING   (2<<20)
#define ADC_CR2_JEXTEN_BOTH      (3<<20)
#define ADC_CR2_JEXTEN_CLEARMASK (3<<20)

#define ADC_CR2_JSWSTART         (1<<22)

#define ADC_CR2_EXTSEL_T1CC1   (0<<24)
#define ADC_CR2_EXTSEL_T1CC2   (1<<24)
#define ADC_CR2_EXTSEL_T1CC3   (2<<24)
#define ADC_CR2_EXTSEL_T2CC2   (3<<24)
#define ADC_CR2_EXTSEL_T2CC3   (4<<24)
#define ADC_CR2_EXTSEL_T2CC4   (5<<24)
#define ADC_CR2_EXTSEL_T2TRGO  (6<<24)
#define ADC_CR2_EXTSEL_T3CC1   (7<<24)
#define ADC_CR2_EXTSEL_T3TRGO  (8<<24)
#define ADC_CR2_EXTSEL_T4CC4   (9<<24)
#define ADC_CR2_EXTSEL_T5CC1   (10<<24)
#define ADC_CR2_EXTSEL_T5CC2   (11<<24)
#define ADC_CR2_EXTSEL_T5CC3   (12<<24)
#define ADC_CR2_EXTSEL_T8CC1   (13<<24)
#define ADC_CR2_EXTSEL_T8TRGO  (14<<24)
#define ADC_CR2_EXTSEL_EXTI11  (15<<24)
#define ADC_CR2_EXTSEL_CLEARMASK  (15<<24)

#define ADC_CR2_EXTEN_OFF       (0<<28)
#define ADC_CR2_EXTEN_RISING    (1<<28)
#define ADC_CR2_EXTEN_FALLING   (2<<28)
#define ADC_CR2_EXTEN_BOTH      (3<<28)
#define ADC_CR2_EXTEN_CLEARMASK (3<<28)

#define ADC_CR2_SWSTART         (1<<30)

#define ADC1_SMPR1 (*(volatile uint32_t*)(ADC1_BASE + 0xc))
#define ADC2_SMPR1 (*(volatile uint32_t*)(ADC2_BASE + 0xc))
#define ADC3_SMPR1 (*(volatile uint32_t*)(ADC3_BASE + 0xc))
#define ADC1_SMPR2 (*(volatile uint32_t*)(ADC1_BASE + 0x10))
#define ADC2_SMPR2 (*(volatile uint32_t*)(ADC2_BASE + 0x10))
#define ADC3_SMPR2 (*(volatile uint32_t*)(ADC3_BASE + 0x10))

//enum ADC_SAMPLE_TIME
//{
//    ADC_SMP_FASTEST = 0,
//    ADC_SMP_FAST = 1,
//    ADC_SMP_28 = 2,
//    ADC_SMP_56 = 3,
//    ADC_SMP_84 = 4,
//    ADC_SMP_112 = 5,
//    ADC_SMP_144 = 6,
//    ADC_SMP_480 = 7
//};

enum ADC_SAMPLE_TIME
{
    ADC_SMP_FASTEST = 0,
    ADC_SMP_FAST = 1,
    ADC_SMP_MEDIUM = 3,
    ADC_SMP_SLOW = 6,
    ADC_SMP_SLOWEST = 7
};


#define ADC1_HTR  (*(volatile uint32_t*)(ADC1_BASE + 0x24))
#define ADC2_HTR  (*(volatile uint32_t*)(ADC2_BASE + 0x24))
#define ADC3_HTR  (*(volatile uint32_t*)(ADC3_BASE + 0x24))

#define ADC1_LTR  (*(volatile uint32_t*)(ADC1_BASE + 0x28))
#define ADC2_LTR  (*(volatile uint32_t*)(ADC2_BASE + 0x28))
#define ADC3_LTR  (*(volatile uint32_t*)(ADC3_BASE + 0x28))

#define ADC1_SQR1  (*(volatile uint32_t*)(ADC1_BASE + 0x2c))
#define ADC2_SQR1  (*(volatile uint32_t*)(ADC2_BASE + 0x2c))
#define ADC3_SQR1  (*(volatile uint32_t*)(ADC3_BASE + 0x2c))    
#define ADC1_SQR2  (*(volatile uint32_t*)(ADC1_BASE + 0x30))
#define ADC2_SQR2  (*(volatile uint32_t*)(ADC2_BASE + 0x30))
#define ADC3_SQR2  (*(volatile uint32_t*)(ADC3_BASE + 0x30))
#define ADC1_SQR3  (*(volatile uint32_t*)(ADC1_BASE + 0x34))
#define ADC2_SQR3  (*(volatile uint32_t*)(ADC2_BASE + 0x34))
#define ADC3_SQR3  (*(volatile uint32_t*)(ADC3_BASE + 0x34))
#define ADC1_JSQR  (*(volatile uint32_t*)(ADC1_BASE + 0x38))
#define ADC2_JSQR  (*(volatile uint32_t*)(ADC2_BASE + 0x38))
#define ADC3_JSQR  (*(volatile uint32_t*)(ADC3_BASE + 0x38))

#define ADC1_JDR1  (*(volatile uint32_t*)(ADC1_BASE + 0x3c))
#define ADC1_JDR2  (*(volatile uint32_t*)(ADC1_BASE + 0x40))
#define ADC1_JDR3  (*(volatile uint32_t*)(ADC1_BASE + 0x44))
#define ADC1_JDR4  (*(volatile uint32_t*)(ADC1_BASE + 0x48))

#define ADC2_JDR1  (*(volatile uint32_t*)(ADC2_BASE + 0x3c))
#define ADC2_JDR2  (*(volatile uint32_t*)(ADC2_BASE + 0x40))
#define ADC2_JDR3  (*(volatile uint32_t*)(ADC2_BASE + 0x44))
#define ADC2_JDR4  (*(volatile uint32_t*)(ADC2_BASE + 0x48))

#define ADC3_JDR1  (*(volatile uint32_t*)(ADC3_BASE + 0x3c))
#define ADC3_JDR2  (*(volatile uint32_t*)(ADC3_BASE + 0x40))
#define ADC3_JDR3  (*(volatile uint32_t*)(ADC3_BASE + 0x44))
#define ADC3_JDR4  (*(volatile uint32_t*)(ADC3_BASE + 0x48))

#define ADC1_DR  (*(volatile uint32_t*)(ADC1_BASE + 0x4c))
#define ADC2_DR  (*(volatile uint32_t*)(ADC2_BASE + 0x4c))
#define ADC3_DR  (*(volatile uint32_t*)(ADC3_BASE + 0x4c))


#define ADC_CCR  (*(volatile uint32_t*)(ADC_COMMON + 0x4))

#define ADC_CCR_ADCPRE_DIV2 (0<<16)
#define ADC_CCR_ADCPRE_DIV4 (1<<16)
#define ADC_CCR_ADCPRE_DIV6 (2<<16)
#define ADC_CCR_ADCPRE_DIV8 (3<<16)
#define ADC_CCR_ADCPRE_CLEARMASK (3<<16)

#define ADC_CCR_VBATE  (1<<22)
#define ADC_CCR_TSVREFE  (1<<23)





#endif


#endif
