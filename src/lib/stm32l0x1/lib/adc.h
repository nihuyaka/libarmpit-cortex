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



#define ADC1_BASE 0x40012400  //APB2  100x, 10x
#define ADC2_BASE 0x40012800  //APB2, 10x
#define ADC3_BASE 0x40013C00  //APB2, 10x

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
    ADC_IN16 = 16,
    ADC_IN17 = 17,
    ADC_ALL = 0xff
};

#define ADC1_SR    (*(volatile uint32_t*)(ADC1_BASE))
#define ADC2_SR    (*(volatile uint32_t*)(ADC2_BASE))
#define ADC3_SR    (*(volatile uint32_t*)(ADC3_BASE))
#define ADC1_CR1   (*(volatile uint32_t*)(ADC1_BASE + 0x4))
#define ADC2_CR1   (*(volatile uint32_t*)(ADC2_BASE + 0x4))
#define ADC3_CR1   (*(volatile uint32_t*)(ADC3_BASE + 0x4))
#define ADC1_CR2   (*(volatile uint32_t*)(ADC1_BASE + 0x8))
#define ADC2_CR2   (*(volatile uint32_t*)(ADC2_BASE + 0x8))
#define ADC3_CR2   (*(volatile uint32_t*)(ADC3_BASE + 0x8))
#define ADC1_SMPR1 (*(volatile uint32_t*)(ADC1_BASE + 0xc))
#define ADC2_SMPR1 (*(volatile uint32_t*)(ADC2_BASE + 0xc))
#define ADC3_SMPR1 (*(volatile uint32_t*)(ADC3_BASE + 0xc))
#define ADC1_SMPR2 (*(volatile uint32_t*)(ADC1_BASE + 0x10))
#define ADC2_SMPR2 (*(volatile uint32_t*)(ADC2_BASE + 0x10))
#define ADC3_SMPR2 (*(volatile uint32_t*)(ADC3_BASE + 0x10))

//high threshold
#define ADC1_HTR  (*(volatile uint32_t*)(ADC1_BASE + 0x24))
#define ADC2_HTR  (*(volatile uint32_t*)(ADC2_BASE + 0x24))
#define ADC3_HTR  (*(volatile uint32_t*)(ADC3_BASE + 0x24))

//low threshold
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

//data register
#define ADC1_DR  (*(volatile uint32_t*)(ADC1_BASE + 0x4c))
#define ADC2_DR  (*(volatile uint32_t*)(ADC2_BASE + 0x4c))
#define ADC3_DR  (*(volatile uint32_t*)(ADC3_BASE + 0x4c))

//ADC_SR   Status register

#define ADC_SR_AWD   (1<<0)  //Analog watchdog flag
#define ADC_SR_EOC   (1<<1)  //End of conversion
#define ADC_SR_JEOC  (1<<2)  //End of conversion (injected channel)
#define ADC_SR_JSTRT (1<<3)  //Injected channel Start flag
#define ADC_SR_STRT  (1<<4)  //Regular channel Start flag

//ADC_CR1    Control register 1

//Bits 4:0AWDCH[4:0]:Analog watchdog channel select bits
//ADC1 analog Channel16 and Channel17 are internally connected to the temperature sensor and to VREFINT, respectively.

#define ADC_CR1_EOCIE  (1<<5)  //Interrupt enable for EOC (end of conversion) 
#define ADC_CR1_AWDIE  (1<<6)  //Analog watchdog interrupt enable
#define ADC_CR1_JEOCIE (1<<7)  //Interrupt enable for injected channels
#define ADC_CR1_SCAN   (1<<8)  //
#define ADC_CR1_AWDSGL (1<<9)  //Enable the watchdog on a single channel in scan mode
#define ADC_CR1_JAUTO  (1<<10) 
#define ADC_CR1_DISCEN (1<<11) //Discontinuous mode on regular channels
#define ADC_CR1_JDISCEN (1<<12) //Discontinuous mode on injected channels
//Bits 15:13 DISCNUM[2:0]: Discontinuous mode channel count
//Bits 19:16DUALMOD[3:0]: Dual mode selection
#define ADC_CR1_JAWDEN (1<<22) //Analog watchdog enable on injected channels
#define ADC_CR1_AWDEN (1<<23)  //Analog watchdog enable on regular channels

//ADC_CR2  Control register 2

#define ADC_CR2_ADON   (1<<0)  // A/D converter ON / OFF
#define ADC_CR2_CONT   (1<<1)  // Continuous conversion 
#define ADC_CR2_CAL    (1<<2)  // A/D calibration  1: enable cal  0: cal completed
#define ADC_CR2_RSTCAL (1<<3) // Reset calibration  1: initialize cal reg, 0: cal reg initialized
#define ADC_CR2_DMA    (1<<8)
#define ADC_CR2_ALIGN    (1<<11)  //0: left 1:right

//Bits 19:17EXTSEL[2:0]: External event select for regular group
#define ADC_CR2_EXTSEL_ADC12_T1CC1   (0<<17)
#define ADC_CR2_EXTSEL_ADC12_T1CC2   (1<<17)
#define ADC_CR2_EXTSEL_ADC12_T1CC3   (2<<17)
#define ADC_CR2_EXTSEL_ADC12_T2CC2   (3<<17)
#define ADC_CR2_EXTSEL_ADC12_T3TRGO  (4<<17)
#define ADC_CR2_EXTSEL_ADC12_T4CC4   (5<<17)
#define ADC_CR2_EXTSEL_ADC12_EXTI11  (6<<17)
#define ADC_CR2_EXTSEL_ADC12_SWSTART (7<<17)

#define ADC_CR2_EXTTRIG  (1<<20) 
#define ADC_CR2_JSWSTART (1<<21)
#define ADC_CR2_SWSTART  (1<<22)
#define ADC_CR2_TSVREFE  (1<<23) // Temperature sensor and  VREFINT enable 
// In devices with dual ADCs this bit is present only in ADC1
#define ADC_CR2_ADC1_TSVREFE  (1<<23)  

//ADC_SMP  Sample time register 1 & 2

/*
 #define ADC_SMP_1_5    0
 #define ADC_SMP_7_5    1
 #define ADC_SMP_13_5   2
 #define ADC_SMP_28_5   3
 #define ADC_SMP_41_5   4
 #define ADC_SMP_55_5   5
 #define ADC_SMP_71_5   6
 #define ADC_SMP_239_5  7
 */

enum ADC_SAMPLE_TIME
{
    ADC_SMP_1_5 = 0,
    ADC_SMP_7_5 = 1,
    ADC_SMP_13_5 = 2,
    ADC_SMP_28_5 = 3,
    ADC_SMP_41_5 = 4,
    ADC_SMP_55_5 = 5,
    ADC_SMP_71_5 = 6,
    ADC_SMP_239_5 = 7
};

//ex:   ADC_SMPR2 |= (ADC_SMP_71_5 << ADC_SMPR2_SMP4)

//ADC_HTR: watchdog high threshold register 
//Bits 11:0 HT[11:0]:Analog watchdog high threshold

//ADC_LTR: watchdog low threshold register 
//Bits 11:0 LT[11:0]: Analog watchdog low threshold

/*

 To use the temp sensor:
 1. Select the ADCx_IN16 input channel.
 2.  Select a sample time of 17.1 µs
 3.  Set the TSVREFE bit in the ADC control register 2 (ADC_CR2)to wake up the
 temperature sensor from power down mode.
 4.  Start the ADC conversion by setting the ADON bit (or by external trigger).
 5.  Read the resulting VSENSE data in the ADC data register
 6.  Obtain the temperature using the following formula:

 Temperature (in °C) = {(V25 - VSENSE) / Avg_Slope} + 25.

 V25 = 1.43V
 Avg_Slope = 4.3

 */

//ADC channel 0-7:  PA0 - PA7, pin 10-17
//ADC channel 8-9: PB0, PB1,   pin 18,19
extern volatile int16_t adc1_val;

void ADC_Reset(int adc);
void ADC_Init(int adc);
uint32_t ADC_SingleConversion(int adc);
void ADC_StartContinuousConversion(int adc);
void ADC_AddConversion(int ADC, int channel, int sample_time);
void ADC_AddJConversion(int ADC, int channel, int sample_time);
void ADC_EnableInterrupt(int adc);
void ADC_EnableJInterrupt(int adc);

#endif


#endif
