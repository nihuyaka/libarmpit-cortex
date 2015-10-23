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

#ifndef _AFIO_H
#define _AFIO_H

#include "common.h"


#include "gpio.h"
#include "exti.h"




#define AFIO_BASE 0x40010000
#define AFIO_EVCR      (*(volatile uint32_t*)(AFIO_BASE + 0x00))
#define AFIO_MAPR      (*(volatile uint32_t*)(AFIO_BASE + 0x04))
#define AFIO_EXTICR1   (*(volatile uint32_t*)(AFIO_BASE + 0x08))
#define AFIO_EXTICR2   (*(volatile uint32_t*)(AFIO_BASE + 0x0c))
#define AFIO_EXTICR3   (*(volatile uint32_t*)(AFIO_BASE + 0x10))
#define AFIO_EXTICR4   (*(volatile uint32_t*)(AFIO_BASE + 0x14))
#define AFIO_MAPR2     (*(volatile uint32_t*)(AFIO_BASE + 0x18))

#define AFIO_EVCR_EVOE  (1<<7)

#define AFIO_MAPR_SPI1_REMAP  (1<<0)
#define AFIO_MAPR_I2C1_REMAP  (1<<1)
#define AFIO_MAPR_USART1_REMAP  (1<<2)
#define AFIO_MAPR_USART2_REMAP  (1<<3)

#define AFIO_MAPR_USART3_REMAP_NONE       (0<<4)
#define AFIO_MAPR_USART3_REMAP_PARTIAL    (1<<4)
#define AFIO_MAPR_USART3_REMAP_FULL       (3<<4)
#define AFIO_MAPR_USART3_REMAP_CLEARMASK  (3<<4)

#define AFIO_MAPR_TIM1_REMAP_NONE      (0<<6)
#define AFIO_MAPR_TIM1_REMAP_PARTIAL   (1<<6)
#define AFIO_MAPR_TIM1_REMAP_FULL      (3<<6)
#define AFIO_MAPR_TIM1_REMAP_CLEARMASK (3<<6)

#define AFIO_MAPR_TIM2_REMAP_NONE       (0<<8)
#define AFIO_MAPR_TIM2_REMAP_1   (1<<8)
#define AFIO_MAPR_TIM2_REMAP_2   (2<<8)
#define AFIO_MAPR_TIM2_REMAP_FULL       (3<<8)
#define AFIO_MAPR_TIM2_REMAP_CLEARMASK  (3<<8)

#define AFIO_MAPR_TIM3_REMAP_NONE       (0<<10)
#define AFIO_MAPR_TIM3_REMAP_PARTIAL    (2<<10)
#define AFIO_MAPR_TIM3_REMAP_FULL       (3<<10)
#define AFIO_MAPR_TIM3_REMAP_CLEARMASK  (3<<10)

#define AFIO_MAPR_TIM4_REMAP  (1<<12)

#define AFIO_MAPR_CAN_REMAP_NONE       (0<<13)
#define AFIO_MAPR_CAN_REMAP_PARTIAL    (2<<13)
#define AFIO_MAPR_CAN_REMAP_FULL       (3<<13)
#define AFIO_MAPR_CAN_REMAP_CLEARMASK  (3<<13)

#define AFIO_MAPR_PD01_REMAP          (1<<15)
#define AFIO_MAPR_TIM5CH4_REMAP      (1<<16)
#define AFIO_MAPR_ADC1_ETRGINJ_REMAP  (1<<17)
#define AFIO_MAPR_ADC1_ETRGREG_REMAP  (1<<18)
#define AFIO_MAPR_ADC2_ETRGINJ_REMAP  (1<<19)
#define AFIO_MAPR_ADC2_ETRGREG_REMAP  (1<<20)

#define AFIO_MAPR_SWJ_CFG_FULL_SWJ           (0<<24)
#define AFIO_MAPR_SWJ_CFG_FULL_SWJ_NO_NJTRST (1<<24)
#define AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_ON     (2<<24)
#define AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_OFF    (4<<24)
#define AFIO_MAPR_SWJ_CFG_CLEARMASK          (7<<24)

#define AFIO_MAPR2_TIM9_REMAP   (1<<5)
#define AFIO_MAPR2_TIM10_REMAP  (1<<6)
#define AFIO_MAPR2_TIM11_REMAP  (1<<7)
#define AFIO_MAPR2_TIM13_REMAP  (1<<8)
#define AFIO_MAPR2_TIM14_REMAP  (1<<9)
#define AFIO_MAPR2_FSMC_NADV    (1<<10)

#ifdef __cplusplus
extern "C"
{
#endif

void AFIO_Remap_SPI1(BOOL remap);
void AFIO_Remap_I2C1(BOOL remap);
void AFIO_Remap_USART1(BOOL remap);
void AFIO_Remap_USART2(BOOL remap);
void AFIO_Remap_USART3(BOOL remap, BOOL full_remap);
void AFIO_Remap_TIM1(BOOL remap, BOOL full_remap);
void AFIO_Remap_TIM2(BOOL remap, BOOL full_remap);
void AFIO_Remap_TIM3(BOOL remap, BOOL full_remap);
void AFIO_Remap_TIM4(BOOL remap);
void AFIO_Remap_CAN(BOOL remap, BOOL full_remap);
void AFIO_Remap_PD01(BOOL remap);
void AFIO_Remap_TIM5CH4(BOOL remap);
void AFIO_Remap_ADC1_ETRGINJ(BOOL remap);
void AFIO_Remap_ADC1_ETRGREG(BOOL remap);
void AFIO_Remap_ADC2_ETRGINJ(BOOL remap);
void AFIO_Remap_ADC2_ETRGREG_(BOOL remap);

void AFIO_Remap_SWJ_CFG(BOOL enableJTAG, BOOL enableSW, BOOL enableNJRST);

void AFIO_Remap_TIM9(BOOL remap);
void AFIO_Remap_TIM10(BOOL remap);
void AFIO_Remap_TIM11(BOOL remap);
void AFIO_Remap_TIM13(BOOL remap);
void AFIO_Remap_TIM14(BOOL remap);

void AFIO_SetEventOutput(BOOL enable, GPIO_PORT_N port, GPIO_PIN_N pin);

void AFIO_RemapEXTI(EXTI_LINE line, GPIO_PORT_N port);



#ifdef __cplusplus
}
#endif

#endif

