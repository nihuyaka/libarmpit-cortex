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


#ifndef _TIMER_H
#define _TIMER_H

#include "common.h"

#ifdef USE_TIMER  

#define TIM2_BASE  0x40000000  //APB1
#define TIM3_BASE  0x40000400  //APB1
#define TIM6_BASE  0x40001000  //APB1
#define TIM7_BASE  0x40001400  //APB1

#if defined(STM32F1) || defined(STM32F2) || defined(STM32F4)

#define TIM4_BASE  0x40000800  //APB1
#define TIM5_BASE  0x40000C00  //APB1
#define TIM12_BASE 0x40001800  //APB1
#define TIM13_BASE 0x40001C00  //APB1
#define TIM14_BASE 0x40002000  //APB1

#if defined(STM32F1) 
#define TIM1_BASE   0x40012C00  //APB2
#define TIM8_BASE   0x40013400  //APB2
#define TIM9_BASE   0x40014C00  //APB2
#define TIM10_BASE  0x40015000  //APB2
#define TIM11_BASE  0x40015400  //APB2
#else 
#define TIM1_BASE   0x40010000   //APB2
#define TIM8_BASE   0x40010000   //APB2
#define TIM9_BASE   0x40014000  //APB2
#define TIM10_BASE  0x40014400  //APB2
#define TIM11_BASE  0x40014800  //APB2
#endif


#if defined(STM32F1)
#define TIM15_BASE  0x40014000  //APB2
#define TIM16_BASE  0x40014400  //APB2
#define TIM17_BASE  0x40014800  //APB2
#endif

#elif defined(STM32L0)

#define TIM21_BASE  0x40010800 //APB2
#define TIM22_BASE  0x40011400 //APB2

#else

#error "device not defined"

#endif

#define TIM_CR1_OFFSET   0x00
#define TIM_CR2_OFFSET   0x04
#define TIM_SMCR_OFFSET  0x08
#define TIM_DIER_OFFSET  0x0c
#define TIM_SR_OFFSET    0x10
#define TIM_EGR_OFFSET   0x14
#define TIM_CCMR1_OFFSET 0x18
#define TIM_CCMR2_OFFSET 0x1c
#define TIM_CCER_OFFSET  0x20
#define TIM_CNT_OFFSET   0x24
#define TIM_PSC_OFFSET   0x28
#define TIM_ARR_OFFSET   0x2c
#define TIM_RCR_OFFSET   0x30
#define TIM_CCR1_OFFSET  0x34
#define TIM_CCR2_OFFSET  0x38
#define TIM_CCR3_OFFSET  0x3c
#define TIM_CCR4_OFFSET  0x40
#define TIM_DCR_OFFSET   0x48
#define TIM_BDTR_OFFSET  0x44
#define TIM_DMAR_OFFSET  0x4c


#define TIM1_CR1   (*(volatile uint32_t*)(TIM1_BASE))
#define TIM2_CR1   (*(volatile uint32_t*)(TIM2_BASE))
#define TIM3_CR1   (*(volatile uint32_t*)(TIM3_BASE))
#define TIM4_CR1   (*(volatile uint32_t*)(TIM4_BASE))
#define TIM5_CR1   (*(volatile uint32_t*)(TIM5_BASE))
#define TIM6_CR1   (*(volatile uint32_t*)(TIM6_BASE))
#define TIM7_CR1   (*(volatile uint32_t*)(TIM7_BASE))
#define TIM8_CR1   (*(volatile uint32_t*)(TIM8_BASE))
#define TIM9_CR1   (*(volatile uint32_t*)(TIM9_BASE))
#define TIM10_CR1  (*(volatile uint32_t*)(TIM10_BASE))
#define TIM11_CR1  (*(volatile uint32_t*)(TIM11_BASE))
#define TIM12_CR1  (*(volatile uint32_t*)(TIM12_BASE))
#define TIM13_CR1  (*(volatile uint32_t*)(TIM13_BASE))
#define TIM14_CR1  (*(volatile uint32_t*)(TIM14_BASE))
#if defined(STM32F1)
#define TIM15_CR1  (*(volatile uint32_t*)(TIM15_BASE))
#define TIM16_CR1  (*(volatile uint32_t*)(TIM16_BASE))
#define TIM17_CR1  (*(volatile uint32_t*)(TIM17_BASE))
#endif
#if defined(STM32L0)
#define TIM21_CR1  (*(volatile uint32_t*)(TIM22_BASE))
#define TIM22_CR1  (*(volatile uint32_t*)(TIM22_BASE))
#endif


#define TIM1_CR2   (*(volatile uint32_t*)(TIM1_BASE + TIM_CR2_OFFSET))
#define TIM2_CR2   (*(volatile uint32_t*)(TIM2_BASE + TIM_CR2_OFFSET))
#define TIM3_CR2   (*(volatile uint32_t*)(TIM3_BASE + TIM_CR2_OFFSET))
#define TIM4_CR2   (*(volatile uint32_t*)(TIM4_BASE + TIM_CR2_OFFSET))
#define TIM5_CR2   (*(volatile uint32_t*)(TIM5_BASE + TIM_CR2_OFFSET))
#define TIM6_CR2   (*(volatile uint32_t*)(TIM6_BASE + TIM_CR2_OFFSET))
#define TIM7_CR2   (*(volatile uint32_t*)(TIM7_BASE + TIM_CR2_OFFSET))
#define TIM8_CR2   (*(volatile uint32_t*)(TIM8_BASE + TIM_CR2_OFFSET))
#define TIM9_CR2   (*(volatile uint32_t*)(TIM9_BASE + TIM_CR2_OFFSET))
#define TIM10_CR2  (*(volatile uint32_t*)(TIM10_BASE + TIM_CR2_OFFSET))
#define TIM11_CR2  (*(volatile uint32_t*)(TIM11_BASE + TIM_CR2_OFFSET))
#define TIM12_CR2  (*(volatile uint32_t*)(TIM12_BASE + TIM_CR2_OFFSET))
#define TIM13_CR2  (*(volatile uint32_t*)(TIM13_BASE + TIM_CR2_OFFSET))
#define TIM14_CR2  (*(volatile uint32_t*)(TIM14_BASE + TIM_CR2_OFFSET))
#if defined(STM32F1)
#define TIM15_CR2  (*(volatile uint32_t*)(TIM15_BASE + TIM_CR2_OFFSET))
#define TIM16_CR2  (*(volatile uint32_t*)(TIM16_BASE + TIM_CR2_OFFSET))
#define TIM17_CR2  (*(volatile uint32_t*)(TIM17_BASE + TIM_CR2_OFFSET))
#endif
#if defined(STM32L0)
#define TIM21_CR2  (*(volatile uint32_t*)(TIM22_BASE + TIM_CR2_OFFSET))
#define TIM22_CR2  (*(volatile uint32_t*)(TIM22_BASE + TIM_CR2_OFFSET))
#endif


#define TIM1_SMCR (*(volatile uint32_t*)(TIM1_BASE + TIM_SMCR_OFFSET))
#define TIM2_SMCR (*(volatile uint32_t*)(TIM2_BASE + TIM_SMCR_OFFSET))
#define TIM3_SMCR (*(volatile uint32_t*)(TIM3_BASE + TIM_SMCR_OFFSET))
#define TIM4_SMCR (*(volatile uint32_t*)(TIM4_BASE + TIM_SMCR_OFFSET))
#define TIM5_SMCR (*(volatile uint32_t*)(TIM5_BASE + TIM_SMCR_OFFSET))
#define TIM6_SMCR (*(volatile uint32_t*)(TIM6_BASE + TIM_SMCR_OFFSET))
#define TIM7_SMCR (*(volatile uint32_t*)(TIM7_BASE + TIM_SMCR_OFFSET))
#define TIM8_SMCR (*(volatile uint32_t*)(TIM8_BASE + TIM_SMCR_OFFSET))
#define TIM9_SMCR (*(volatile uint32_t*)(TIM9_BASE + TIM_SMCR_OFFSET))
#define TIM10_SMCR (*(volatile uint32_t*)(TIM10_BASE + TIM_SMCR_OFFSET))
#define TIM11_SMCR (*(volatile uint32_t*)(TIM11_BASE + TIM_SMCR_OFFSET))
#define TIM12_SMCR (*(volatile uint32_t*)(TIM12_BASE + TIM_SMCR_OFFSET))
#define TIM13_SMCR (*(volatile uint32_t*)(TIM13_BASE + TIM_SMCR_OFFSET))
#define TIM14_SMCR (*(volatile uint32_t*)(TIM14_BASE + TIM_SMCR_OFFSET))
#if defined(STM32F1)
#define TIM15_SMCR (*(volatile uint32_t*)(TIM15_BASE + TIM_SMCR_OFFSET))
#define TIM16_SMCR (*(volatile uint32_t*)(TIM16_BASE + TIM_SMCR_OFFSET))
#define TIM17_SMCR (*(volatile uint32_t*)(TIM17_BASE + TIM_SMCR_OFFSET))
#endif
#if defined(STM32L0)
#define TIM21_SMCR  (*(volatile uint32_t*)(TIM22_BASE + TIM_SMCR_OFFSET))
#define TIM22_SMCR  (*(volatile uint32_t*)(TIM22_BASE + TIM_SMCR_OFFSET))
#endif

#define TIM1_DIER (*(volatile uint32_t*)(TIM1_BASE + TIM_DIER_OFFSET))
#define TIM2_DIER (*(volatile uint32_t*)(TIM2_BASE + TIM_DIER_OFFSET))
#define TIM3_DIER (*(volatile uint32_t*)(TIM3_BASE + TIM_DIER_OFFSET))
#define TIM4_DIER (*(volatile uint32_t*)(TIM4_BASE + TIM_DIER_OFFSET))
#define TIM5_DIER (*(volatile uint32_t*)(TIM5_BASE + TIM_DIER_OFFSET))
#define TIM6_DIER (*(volatile uint32_t*)(TIM6_BASE + TIM_DIER_OFFSET))
#define TIM7_DIER (*(volatile uint32_t*)(TIM7_BASE + TIM_DIER_OFFSET))
#define TIM8_DIER (*(volatile uint32_t*)(TIM8_BASE + TIM_DIER_OFFSET))
#define TIM9_DIER (*(volatile uint32_t*)(TIM9_BASE + TIM_DIER_OFFSET))
#define TIM10_DIER (*(volatile uint32_t*)(TIM10_BASE + TIM_DIER_OFFSET))
#define TIM11_DIER (*(volatile uint32_t*)(TIM11_BASE + TIM_DIER_OFFSET))
#define TIM12_DIER (*(volatile uint32_t*)(TIM12_BASE + TIM_DIER_OFFSET))
#define TIM13_DIER (*(volatile uint32_t*)(TIM13_BASE + TIM_DIER_OFFSET))
#define TIM14_DIER (*(volatile uint32_t*)(TIM14_BASE + TIM_DIER_OFFSET))
#if defined(STM32F1)
#define TIM15_DIER (*(volatile uint32_t*)(TIM15_BASE + TIM_DIER_OFFSET))
#define TIM16_DIER (*(volatile uint32_t*)(TIM16_BASE + TIM_DIER_OFFSET))
#define TIM17_DIER (*(volatile uint32_t*)(TIM17_BASE + TIM_DIER_OFFSET))
#endif
#if defined(STM32L0)
#define TIM21_DIER  (*(volatile uint32_t*)(TIM22_BASE + TIM_DIER_OFFSET))
#define TIM22_DIER  (*(volatile uint32_t*)(TIM22_BASE + TIM_DIER_OFFSET))
#endif

#define TIM1_SR (*(volatile uint32_t*)(TIM1_BASE + TIM_SR_OFFSET))
#define TIM2_SR (*(volatile uint32_t*)(TIM2_BASE + TIM_SR_OFFSET))
#define TIM3_SR (*(volatile uint32_t*)(TIM3_BASE + TIM_SR_OFFSET))
#define TIM4_SR (*(volatile uint32_t*)(TIM4_BASE + TIM_SR_OFFSET))
#define TIM5_SR (*(volatile uint32_t*)(TIM5_BASE + TIM_SR_OFFSET))
#define TIM6_SR (*(volatile uint32_t*)(TIM6_BASE + TIM_SR_OFFSET))
#define TIM7_SR (*(volatile uint32_t*)(TIM7_BASE + TIM_SR_OFFSET))
#define TIM8_SR (*(volatile uint32_t*)(TIM8_BASE + TIM_SR_OFFSET))
#define TIM9_SR (*(volatile uint32_t*)(TIM9_BASE + TIM_SR_OFFSET))
#define TIM10_SR (*(volatile uint32_t*)(TIM10_BASE + TIM_SR_OFFSET))
#define TIM11_SR (*(volatile uint32_t*)(TIM11_BASE + TIM_SR_OFFSET))
#define TIM12_SR (*(volatile uint32_t*)(TIM12_BASE + TIM_SR_OFFSET))
#define TIM13_SR (*(volatile uint32_t*)(TIM13_BASE + TIM_SR_OFFSET))
#define TIM14_SR (*(volatile uint32_t*)(TIM14_BASE + TIM_SR_OFFSET))
#if defined(STM32F1)
#define TIM15_SR (*(volatile uint32_t*)(TIM15_BASE + TIM_SR_OFFSET))
#define TIM16_SR (*(volatile uint32_t*)(TIM16_BASE + TIM_SR_OFFSET))
#define TIM17_SR (*(volatile uint32_t*)(TIM17_BASE + TIM_SR_OFFSET))
#endif
#if defined(STM32L0)
#define TIM21_SR  (*(volatile uint32_t*)(TIM22_BASE + TIM_SR_OFFSET))
#define TIM22_SR  (*(volatile uint32_t*)(TIM22_BASE + TIM_SR_OFFSET))
#endif

#define TIM1_EGR (*(volatile uint32_t*)(TIM1_BASE + TIM_EGR_OFFSET))
#define TIM2_EGR (*(volatile uint32_t*)(TIM2_BASE + TIM_EGR_OFFSET))
#define TIM3_EGR (*(volatile uint32_t*)(TIM3_BASE + TIM_EGR_OFFSET))
#define TIM4_EGR (*(volatile uint32_t*)(TIM4_BASE + TIM_EGR_OFFSET))
#define TIM5_EGR (*(volatile uint32_t*)(TIM5_BASE + TIM_EGR_OFFSET))
#define TIM6_EGR (*(volatile uint32_t*)(TIM6_BASE + TIM_EGR_OFFSET))
#define TIM7_EGR (*(volatile uint32_t*)(TIM7_BASE + TIM_EGR_OFFSET))
#define TIM8_EGR (*(volatile uint32_t*)(TIM8_BASE + TIM_EGR_OFFSET))
#define TIM9_EGR (*(volatile uint32_t*)(TIM9_BASE + TIM_EGR_OFFSET))
#define TIM10_EGR (*(volatile uint32_t*)(TIM10_BASE + TIM_EGR_OFFSET))
#define TIM11_EGR (*(volatile uint32_t*)(TIM11_BASE + TIM_EGR_OFFSET))
#define TIM12_EGR (*(volatile uint32_t*)(TIM12_BASE + TIM_EGR_OFFSET))
#define TIM13_EGR (*(volatile uint32_t*)(TIM13_BASE + TIM_EGR_OFFSET))
#define TIM14_EGR (*(volatile uint32_t*)(TIM14_BASE + TIM_EGR_OFFSET))
#if defined(STM32F1)
#define TIM15_EGR (*(volatile uint32_t*)(TIM15_BASE + TIM_EGR_OFFSET))
#define TIM16_EGR (*(volatile uint32_t*)(TIM16_BASE + TIM_EGR_OFFSET))
#define TIM17_EGR (*(volatile uint32_t*)(TIM17_BASE + TIM_EGR_OFFSET))
#endif
#if defined(STM32L0)
#define TIM21_EGR  (*(volatile uint32_t*)(TIM22_BASE + TIM_EGR_OFFSET))
#define TIM22_EGR  (*(volatile uint32_t*)(TIM22_BASE + TIM_EGR_OFFSET))
#endif

#define TIM1_CCMR1 (*(volatile uint32_t*)(TIM1_BASE + TIM_CCMR1_OFFSET))
#define TIM2_CCMR1 (*(volatile uint32_t*)(TIM2_BASE + TIM_CCMR1_OFFSET))
#define TIM3_CCMR1 (*(volatile uint32_t*)(TIM3_BASE + TIM_CCMR1_OFFSET))
#define TIM4_CCMR1 (*(volatile uint32_t*)(TIM4_BASE + TIM_CCMR1_OFFSET))
#define TIM5_CCMR1 (*(volatile uint32_t*)(TIM5_BASE + TIM_CCMR1_OFFSET))
#define TIM6_CCMR1 (*(volatile uint32_t*)(TIM6_BASE + TIM_CCMR1_OFFSET))
#define TIM7_CCMR1 (*(volatile uint32_t*)(TIM7_BASE + TIM_CCMR1_OFFSET))
#define TIM8_CCMR1 (*(volatile uint32_t*)(TIM8_BASE + TIM_CCMR1_OFFSET))
#define TIM9_CCMR1 (*(volatile uint32_t*)(TIM9_BASE + TIM_CCMR1_OFFSET))
#define TIM10_CCMR1 (*(volatile uint32_t*)(TIM10_BASE + TIM_CCMR1_OFFSET))
#define TIM11_CCMR1 (*(volatile uint32_t*)(TIM11_BASE + TIM_CCMR1_OFFSET))
#define TIM12_CCMR1 (*(volatile uint32_t*)(TIM12_BASE + TIM_CCMR1_OFFSET))
#define TIM13_CCMR1 (*(volatile uint32_t*)(TIM13_BASE + TIM_CCMR1_OFFSET))
#define TIM14_CCMR1 (*(volatile uint32_t*)(TIM14_BASE + TIM_CCMR1_OFFSET))
#if defined(STM32F1)
#define TIM15_CCMR1 (*(volatile uint32_t*)(TIM15_BASE + TIM_CCMR1_OFFSET))
#define TIM16_CCMR1 (*(volatile uint32_t*)(TIM16_BASE + TIM_CCMR1_OFFSET))
#define TIM17_CCMR1 (*(volatile uint32_t*)(TIM17_BASE + TIM_CCMR1_OFFSET))
#endif
#if defined(STM32L0)
#define TIM21_CCMR1  (*(volatile uint32_t*)(TIM22_BASE + TIM_CCMR1_OFFSET))
#define TIM22_CCMR1  (*(volatile uint32_t*)(TIM22_BASE + TIM_CCMR1_OFFSET))
#endif

#define TIM1_CCMR2 (*(volatile uint32_t*)(TIM1_BASE + TIM_CCMR2_OFFSET))
#define TIM2_CCMR2 (*(volatile uint32_t*)(TIM2_BASE + TIM_CCMR2_OFFSET))
#define TIM3_CCMR2 (*(volatile uint32_t*)(TIM3_BASE + TIM_CCMR2_OFFSET))
#define TIM4_CCMR2 (*(volatile uint32_t*)(TIM4_BASE + TIM_CCMR2_OFFSET))
#define TIM5_CCMR2 (*(volatile uint32_t*)(TIM5_BASE + TIM_CCMR2_OFFSET))
#define TIM6_CCMR2 (*(volatile uint32_t*)(TIM6_BASE + TIM_CCMR2_OFFSET))
#define TIM7_CCMR2 (*(volatile uint32_t*)(TIM7_BASE + TIM_CCMR2_OFFSET))
#define TIM8_CCMR2 (*(volatile uint32_t*)(TIM8_BASE + TIM_CCMR2_OFFSET))
#define TIM9_CCMR2 (*(volatile uint32_t*)(TIM9_BASE + TIM_CCMR2_OFFSET))
#define TIM10_CCMR2 (*(volatile uint32_t*)(TIM10_BASE + TIM_CCMR2_OFFSET))
#define TIM11_CCMR2 (*(volatile uint32_t*)(TIM11_BASE + TIM_CCMR2_OFFSET))
#define TIM12_CCMR2 (*(volatile uint32_t*)(TIM12_BASE + TIM_CCMR2_OFFSET))
#define TIM13_CCMR2 (*(volatile uint32_t*)(TIM13_BASE + TIM_CCMR2_OFFSET))
#define TIM14_CCMR2 (*(volatile uint32_t*)(TIM14_BASE + TIM_CCMR2_OFFSET))
#if defined(STM32F1)
#define TIM15_CCMR2 (*(volatile uint32_t*)(TIM15_BASE + TIM_CCMR2_OFFSET))
#define TIM16_CCMR2 (*(volatile uint32_t*)(TIM16_BASE + TIM_CCMR2_OFFSET))
#define TIM17_CCMR2 (*(volatile uint32_t*)(TIM17_BASE + TIM_CCMR2_OFFSET))
#endif
#if defined(STM32L0)
#define TIM21_CCMR2  (*(volatile uint32_t*)(TIM22_BASE + TIM_CCMR2_OFFSET))
#define TIM22_CCMR2  (*(volatile uint32_t*)(TIM22_BASE + TIM_CCMR2_OFFSET))
#endif


#define TIM1_CCER (*(volatile uint32_t*)(TIM1_BASE + TIM_CCER_OFFSET))
#define TIM2_CCER (*(volatile uint32_t*)(TIM2_BASE + TIM_CCER_OFFSET))
#define TIM3_CCER (*(volatile uint32_t*)(TIM3_BASE + TIM_CCER_OFFSET))
#define TIM4_CCER (*(volatile uint32_t*)(TIM4_BASE + TIM_CCER_OFFSET))
#define TIM5_CCER (*(volatile uint32_t*)(TIM5_BASE + TIM_CCER_OFFSET))
#define TIM6_CCER (*(volatile uint32_t*)(TIM6_BASE + TIM_CCER_OFFSET))
#define TIM7_CCER (*(volatile uint32_t*)(TIM7_BASE + TIM_CCER_OFFSET))
#define TIM8_CCER (*(volatile uint32_t*)(TIM8_BASE + TIM_CCER_OFFSET))
#define TIM9_CCER (*(volatile uint32_t*)(TIM9_BASE + TIM_CCER_OFFSET))
#define TIM10_CCER (*(volatile uint32_t*)(TIM10_BASE + TIM_CCER_OFFSET))
#define TIM11_CCER (*(volatile uint32_t*)(TIM11_BASE + TIM_CCER_OFFSET))
#define TIM12_CCER (*(volatile uint32_t*)(TIM12_BASE + TIM_CCER_OFFSET))
#define TIM13_CCER (*(volatile uint32_t*)(TIM13_BASE + TIM_CCER_OFFSET))
#define TIM14_CCER (*(volatile uint32_t*)(TIM14_BASE + TIM_CCER_OFFSET))
#if defined(STM32F1)
#define TIM15_CCER (*(volatile uint32_t*)(TIM15_BASE + TIM_CCER_OFFSET))
#define TIM16_CCER (*(volatile uint32_t*)(TIM16_BASE + TIM_CCER_OFFSET))
#define TIM17_CCER (*(volatile uint32_t*)(TIM17_BASE + TIM_CCER_OFFSET))
#endif
#if defined(STM32L0)
#define TIM21_CCER  (*(volatile uint32_t*)(TIM22_BASE + TIM_CCER_OFFSET))
#define TIM22_CCER  (*(volatile uint32_t*)(TIM22_BASE + TIM_CCER_OFFSET))
#endif

#define TIM1_CNT (*(volatile uint32_t*)(TIM1_BASE + TIM_CNT_OFFSET))
#define TIM2_CNT (*(volatile uint32_t*)(TIM2_BASE + TIM_CNT_OFFSET))
#define TIM3_CNT (*(volatile uint32_t*)(TIM3_BASE + TIM_CNT_OFFSET))
#define TIM4_CNT (*(volatile uint32_t*)(TIM4_BASE + TIM_CNT_OFFSET))
#define TIM5_CNT (*(volatile uint32_t*)(TIM5_BASE + TIM_CNT_OFFSET))
#define TIM6_CNT (*(volatile uint32_t*)(TIM6_BASE + TIM_CNT_OFFSET))
#define TIM7_CNT (*(volatile uint32_t*)(TIM7_BASE + TIM_CNT_OFFSET))
#define TIM8_CNT (*(volatile uint32_t*)(TIM8_BASE + TIM_CNT_OFFSET))
#define TIM9_CNT (*(volatile uint32_t*)(TIM9_BASE + TIM_CNT_OFFSET))
#define TIM10_CNT (*(volatile uint32_t*)(TIM10_BASE + TIM_CNT_OFFSET))
#define TIM11_CNT (*(volatile uint32_t*)(TIM11_BASE + TIM_CNT_OFFSET))
#define TIM12_CNT (*(volatile uint32_t*)(TIM12_BASE + TIM_CNT_OFFSET))
#define TIM13_CNT (*(volatile uint32_t*)(TIM13_BASE + TIM_CNT_OFFSET))
#define TIM14_CNT (*(volatile uint32_t*)(TIM14_BASE + TIM_CNT_OFFSET))
#if defined(STM32F1)
#define TIM15_CNT (*(volatile uint32_t*)(TIM15_BASE + TIM_CNT_OFFSET))
#define TIM16_CNT (*(volatile uint32_t*)(TIM16_BASE + TIM_CNT_OFFSET))
#define TIM17_CNT (*(volatile uint32_t*)(TIM17_BASE + TIM_CNT_OFFSET))
#endif
#if defined(STM32L0)
#define TIM21_CNT  (*(volatile uint32_t*)(TIM22_BASE + TIM_CNT_OFFSET))
#define TIM22_CNT  (*(volatile uint32_t*)(TIM22_BASE + TIM_CNT_OFFSET))
#endif

#define TIM1_PSC (*(volatile uint32_t*)(TIM1_BASE + TIM_PSC_OFFSET))
#define TIM2_PSC (*(volatile uint32_t*)(TIM2_BASE + TIM_PSC_OFFSET))
#define TIM3_PSC (*(volatile uint32_t*)(TIM3_BASE + TIM_PSC_OFFSET))
#define TIM4_PSC (*(volatile uint32_t*)(TIM4_BASE + TIM_PSC_OFFSET))
#define TIM5_PSC (*(volatile uint32_t*)(TIM5_BASE + TIM_PSC_OFFSET))
#define TIM6_PSC (*(volatile uint32_t*)(TIM6_BASE + TIM_PSC_OFFSET))
#define TIM7_PSC (*(volatile uint32_t*)(TIM7_BASE + TIM_PSC_OFFSET))
#define TIM8_PSC (*(volatile uint32_t*)(TIM8_BASE + TIM_PSC_OFFSET))
#define TIM9_PSC (*(volatile uint32_t*)(TIM9_BASE + TIM_PSC_OFFSET))
#define TIM10_PSC (*(volatile uint32_t*)(TIM10_BASE + TIM_PSC_OFFSET))
#define TIM11_PSC (*(volatile uint32_t*)(TIM11_BASE + TIM_PSC_OFFSET))
#define TIM12_PSC (*(volatile uint32_t*)(TIM12_BASE + TIM_PSC_OFFSET))
#define TIM13_PSC (*(volatile uint32_t*)(TIM13_BASE + TIM_PSC_OFFSET))
#define TIM14_PSC (*(volatile uint32_t*)(TIM14_BASE + TIM_PSC_OFFSET))
#if defined(STM32F1)
#define TIM15_PSC (*(volatile uint32_t*)(TIM15_BASE + TIM_PSC_OFFSET))
#define TIM16_PSC (*(volatile uint32_t*)(TIM16_BASE + TIM_PSC_OFFSET))
#define TIM17_PSC (*(volatile uint32_t*)(TIM17_BASE + TIM_PSC_OFFSET))
#endif
#if defined(STM32L0)
#define TIM21_PSC  (*(volatile uint32_t*)(TIM22_BASE + TIM_PSC_OFFSET))
#define TIM22_PSC  (*(volatile uint32_t*)(TIM22_BASE + TIM_PSC_OFFSET))
#endif

#define TIM1_ARR (*(volatile uint32_t*)(TIM1_BASE + TIM_ARR_OFFSET))
#define TIM2_ARR (*(volatile uint32_t*)(TIM2_BASE + TIM_ARR_OFFSET))
#define TIM3_ARR (*(volatile uint32_t*)(TIM3_BASE + TIM_ARR_OFFSET))
#define TIM4_ARR (*(volatile uint32_t*)(TIM4_BASE + TIM_ARR_OFFSET))
#define TIM5_ARR (*(volatile uint32_t*)(TIM5_BASE + TIM_ARR_OFFSET))
#define TIM6_ARR (*(volatile uint32_t*)(TIM6_BASE + TIM_ARR_OFFSET))
#define TIM7_ARR (*(volatile uint32_t*)(TIM7_BASE + TIM_ARR_OFFSET))
#define TIM8_ARR (*(volatile uint32_t*)(TIM8_BASE + TIM_ARR_OFFSET))
#define TIM9_ARR (*(volatile uint32_t*)(TIM9_BASE + TIM_ARR_OFFSET))
#define TIM10_ARR (*(volatile uint32_t*)(TIM10_BASE + TIM_ARR_OFFSET))
#define TIM11_ARR (*(volatile uint32_t*)(TIM11_BASE + TIM_ARR_OFFSET))
#define TIM12_ARR (*(volatile uint32_t*)(TIM12_BASE + TIM_ARR_OFFSET))
#define TIM13_ARR (*(volatile uint32_t*)(TIM13_BASE + TIM_ARR_OFFSET))
#define TIM14_ARR (*(volatile uint32_t*)(TIM14_BASE + TIM_ARR_OFFSET))
#if defined(STM32F1)
#define TIM15_ARR (*(volatile uint32_t*)(TIM15_BASE + TIM_ARR_OFFSET))
#define TIM16_ARR (*(volatile uint32_t*)(TIM16_BASE + TIM_ARR_OFFSET))
#define TIM17_ARR (*(volatile uint32_t*)(TIM17_BASE + TIM_ARR_OFFSET))
#endif
#if defined(STM32L0)
#define TIM21_ARR  (*(volatile uint32_t*)(TIM22_BASE + TIM_ARR_OFFSET))
#define TIM22_ARR  (*(volatile uint32_t*)(TIM22_BASE + TIM_ARR_OFFSET))
#endif

#define TIM1_CCR1 (*(volatile uint32_t*)(TIM1_BASE + TIM_CCR1_OFFSET))
#define TIM2_CCR1 (*(volatile uint32_t*)(TIM2_BASE + TIM_CCR1_OFFSET))
#define TIM3_CCR1 (*(volatile uint32_t*)(TIM3_BASE + TIM_CCR1_OFFSET))
#define TIM4_CCR1 (*(volatile uint32_t*)(TIM4_BASE + TIM_CCR1_OFFSET))
#define TIM5_CCR1 (*(volatile uint32_t*)(TIM5_BASE + TIM_CCR1_OFFSET))
#define TIM6_CCR1 (*(volatile uint32_t*)(TIM6_BASE + TIM_CCR1_OFFSET))
#define TIM7_CCR1 (*(volatile uint32_t*)(TIM7_BASE + TIM_CCR1_OFFSET))
#define TIM8_CCR1 (*(volatile uint32_t*)(TIM8_BASE + TIM_CCR1_OFFSET))
#define TIM9_CCR1 (*(volatile uint32_t*)(TIM9_BASE + TIM_CCR1_OFFSET))
#define TIM10_CCR1 (*(volatile uint32_t*)(TIM10_BASE + TIM_CCR1_OFFSET))
#define TIM11_CCR1 (*(volatile uint32_t*)(TIM11_BASE + TIM_CCR1_OFFSET))
#define TIM12_CCR1 (*(volatile uint32_t*)(TIM12_BASE + TIM_CCR1_OFFSET))
#define TIM13_CCR1 (*(volatile uint32_t*)(TIM13_BASE + TIM_CCR1_OFFSET))
#define TIM14_CCR1 (*(volatile uint32_t*)(TIM14_BASE + TIM_CCR1_OFFSET))
#if defined(STM32F1)
#define TIM15_CCR1 (*(volatile uint32_t*)(TIM15_BASE + TIM_CCR1_OFFSET))
#define TIM16_CCR1 (*(volatile uint32_t*)(TIM16_BASE + TIM_CCR1_OFFSET))
#define TIM17_CCR1 (*(volatile uint32_t*)(TIM17_BASE + TIM_CCR1_OFFSET))
#endif
#if defined(STM32L0)
#define TIM21_CCR1  (*(volatile uint32_t*)(TIM22_BASE + TIM_CCR1_OFFSET))
#define TIM22_CCR1  (*(volatile uint32_t*)(TIM22_BASE + TIM_CCR1_OFFSET))
#endif

#define TIM1_CCR2 (*(volatile uint32_t*)(TIM1_BASE + TIM_CCR2_OFFSET))
#define TIM2_CCR2 (*(volatile uint32_t*)(TIM2_BASE + TIM_CCR2_OFFSET))
#define TIM3_CCR2 (*(volatile uint32_t*)(TIM3_BASE + TIM_CCR2_OFFSET))
#define TIM4_CCR2 (*(volatile uint32_t*)(TIM4_BASE + TIM_CCR2_OFFSET))
#define TIM5_CCR2 (*(volatile uint32_t*)(TIM5_BASE + TIM_CCR2_OFFSET))
#define TIM6_CCR2 (*(volatile uint32_t*)(TIM6_BASE + TIM_CCR2_OFFSET))
#define TIM7_CCR2 (*(volatile uint32_t*)(TIM7_BASE + TIM_CCR2_OFFSET))
#define TIM8_CCR2 (*(volatile uint32_t*)(TIM8_BASE + TIM_CCR2_OFFSET))
#define TIM9_CCR2 (*(volatile uint32_t*)(TIM9_BASE + TIM_CCR2_OFFSET))
#define TIM10_CCR2 (*(volatile uint32_t*)(TIM10_BASE + TIM_CCR2_OFFSET))
#define TIM11_CCR2 (*(volatile uint32_t*)(TIM11_BASE + TIM_CCR2_OFFSET))
#define TIM12_CCR2 (*(volatile uint32_t*)(TIM12_BASE + TIM_CCR2_OFFSET))
#define TIM13_CCR2 (*(volatile uint32_t*)(TIM13_BASE + TIM_CCR2_OFFSET))
#define TIM14_CCR2 (*(volatile uint32_t*)(TIM14_BASE + TIM_CCR2_OFFSET))
#if defined(STM32F1)
#define TIM15_CCR2 (*(volatile uint32_t*)(TIM15_BASE + TIM_CCR2_OFFSET))
#define TIM16_CCR2 (*(volatile uint32_t*)(TIM16_BASE + TIM_CCR2_OFFSET))
#define TIM17_CCR2 (*(volatile uint32_t*)(TIM17_BASE + TIM_CCR2_OFFSET))
#endif
#if defined(STM32L0)
#define TIM21_CCR2  (*(volatile uint32_t*)(TIM22_BASE + TIM_CCR2_OFFSET))
#define TIM22_CCR2  (*(volatile uint32_t*)(TIM22_BASE + TIM_CCR2_OFFSET))
#endif

#define TIM1_CCR3 (*(volatile uint32_t*)(TIM1_BASE + TIM_CCR3_OFFSET))
#define TIM2_CCR3 (*(volatile uint32_t*)(TIM2_BASE + TIM_CCR3_OFFSET))
#define TIM3_CCR3 (*(volatile uint32_t*)(TIM3_BASE + TIM_CCR3_OFFSET))
#define TIM4_CCR3 (*(volatile uint32_t*)(TIM4_BASE + TIM_CCR3_OFFSET))
#define TIM5_CCR3 (*(volatile uint32_t*)(TIM5_BASE + TIM_CCR3_OFFSET))
#define TIM6_CCR3 (*(volatile uint32_t*)(TIM6_BASE + TIM_CCR3_OFFSET))
#define TIM7_CCR3 (*(volatile uint32_t*)(TIM7_BASE + TIM_CCR3_OFFSET))
#define TIM8_CCR3 (*(volatile uint32_t*)(TIM8_BASE + TIM_CCR3_OFFSET))
#define TIM9_CCR3 (*(volatile uint32_t*)(TIM9_BASE + TIM_CCR3_OFFSET))
#define TIM10_CCR3 (*(volatile uint32_t*)(TIM10_BASE + TIM_CCR3_OFFSET))
#define TIM11_CCR3 (*(volatile uint32_t*)(TIM11_BASE + TIM_CCR3_OFFSET))
#define TIM12_CCR3 (*(volatile uint32_t*)(TIM12_BASE + TIM_CCR3_OFFSET))
#define TIM13_CCR3 (*(volatile uint32_t*)(TIM13_BASE + TIM_CCR3_OFFSET))
#define TIM14_CCR3 (*(volatile uint32_t*)(TIM14_BASE + TIM_CCR3_OFFSET))
#if defined(STM32F1)
#define TIM15_CCR3 (*(volatile uint32_t*)(TIM15_BASE + TIM_CCR3_OFFSET))
#define TIM16_CCR3 (*(volatile uint32_t*)(TIM16_BASE + TIM_CCR3_OFFSET))
#define TIM17_CCR3 (*(volatile uint32_t*)(TIM17_BASE + TIM_CCR3_OFFSET))
#endif
#if defined(STM32L0)
#define TIM21_CCR3  (*(volatile uint32_t*)(TIM22_BASE + TIM_CCR3_OFFSET))
#define TIM22_CCR3  (*(volatile uint32_t*)(TIM22_BASE + TIM_CCR3_OFFSET))
#endif

#define TIM1_CCR4 (*(volatile uint32_t*)(TIM1_BASE + TIM_CCR4_OFFSET))
#define TIM2_CCR4 (*(volatile uint32_t*)(TIM2_BASE + TIM_CCR4_OFFSET))
#define TIM3_CCR4 (*(volatile uint32_t*)(TIM3_BASE + TIM_CCR4_OFFSET))
#define TIM4_CCR4 (*(volatile uint32_t*)(TIM4_BASE + TIM_CCR4_OFFSET))
#define TIM5_CCR4 (*(volatile uint32_t*)(TIM5_BASE + TIM_CCR4_OFFSET))
#define TIM6_CCR4 (*(volatile uint32_t*)(TIM6_BASE + TIM_CCR4_OFFSET))
#define TIM7_CCR4 (*(volatile uint32_t*)(TIM7_BASE + TIM_CCR4_OFFSET))
#define TIM8_CCR4 (*(volatile uint32_t*)(TIM8_BASE + TIM_CCR4_OFFSET))
#define TIM9_CCR4 (*(volatile uint32_t*)(TIM9_BASE + TIM_CCR4_OFFSET))
#define TIM10_CCR4 (*(volatile uint32_t*)(TIM10_BASE + TIM_CCR4_OFFSET))
#define TIM11_CCR4 (*(volatile uint32_t*)(TIM11_BASE + TIM_CCR4_OFFSET))
#define TIM12_CCR4 (*(volatile uint32_t*)(TIM12_BASE + TIM_CCR4_OFFSET))
#define TIM13_CCR4 (*(volatile uint32_t*)(TIM13_BASE + TIM_CCR4_OFFSET))
#define TIM14_CCR4 (*(volatile uint32_t*)(TIM14_BASE + TIM_CCR4_OFFSET))
#if defined(STM32F1)
#define TIM15_CCR4 (*(volatile uint32_t*)(TIM15_BASE + TIM_CCR4_OFFSET))
#define TIM16_CCR4 (*(volatile uint32_t*)(TIM16_BASE + TIM_CCR4_OFFSET))
#define TIM17_CCR4 (*(volatile uint32_t*)(TIM17_BASE + TIM_CCR4_OFFSET))
#endif
#if defined(STM32L0)
#define TIM21_CCR4  (*(volatile uint32_t*)(TIM22_BASE + TIM_CCR4_OFFSET))
#define TIM22_CCR4  (*(volatile uint32_t*)(TIM22_BASE + TIM_CCR4_OFFSET))
#endif


#define TIM_CR1_CEN (1<<0) //counter enable
#define TIM_CR1_UDIS (1<<1) //update disable: set/cleared by software
                            //0:Update event enabled. 1: UEV disabled
#define TIM_CR1_URS  (1<<2) //set/cleared by sw to select the UEV sources
//0: any of these generated an update interrupt: counter overflow/underflow, setting the UG bit, 
//1: only counter overflow/underflow 

#define TIM_CR1_OPM  (1<<3) //one pulse mode
//0: counter is not stopped at update event 
//1: counter stops counting at the next update event and CEN is cleared
#define TIM_CR1_DIR  (1<<4)  //direction: 0: upcounter, 1: downcounter
#define TIM_CR1_CMS_EDGE_ALIGNED (0<<5)
#define TIM_CR1_CMS_CENTER_ALIGNED_DOWN (1<<5)
#define TIM_CR1_CMS_CENTER_ALIGNED_UP (2<<5)
#define TIM_CR1_CMS_CENTER_ALIGNED_UP_DOWN (3<<5)
#define TIM_CR1_CMS_CLEARMASK       (3<<5)
#define TIM_CR1_ARPE  (1<<7)  //auto preload enable, 0: TIMx_ARR is not buffered, 1: buffered
#define TIM_CR1_CKD_CKINT (0<<8)
#define TIM_CR1_CKD_CKINT2 (1<<8)
#define TIM_CR1_CKD_CKINT4 (2<<8)
#define TIM_CR1_CKD_CLEARMASK (3<<8)

#define TIM_CR2_CCDS                (1<<3)

#define TIM_CR2_MMS_RESET           (0<<4)
#define TIM_CR2_MMS_ENABLE          (1<<4)
#define TIM_CR2_MMS_UPDATE          (2<<4)
#define TIM_CR2_MMS_COMPARE_PULSE   (3<<4)
#define TIM_CR2_MMS_COMPARE_OC1REF  (4<<4)
#define TIM_CR2_MMS_COMPARE_OC2REF  (5<<4)
#define TIM_CR2_MMS_COMPARE_OC3REF  (6<<4)
#define TIM_CR2_MMS_COMPARE_OC4REF  (7<<4)
#define TIM_CR2_MMS_CLEARMASK       (7<<4)
#define TIM_CR2_TI1S                (1<<7)  //TIM1/8 2/3/4/5, 100x: TIM15/16/17


#define TIM_DIER_UIE    (1<<0) //update interrupt enable
#define TIM_DIER_CC1IE  (1<<1) //Capture/compare int enable
#define TIM_DIER_CC2IE  (1<<2)
#define TIM_DIER_CC3IE  (1<<3)
#define TIM_DIER_CC4IE  (1<<4)
#define TIM_DIER_TIE    (1<<6) //Trigger interrupt enable 
#define TIM_DIER_UDE    (1<<8) //Update DMA request enable 
#define TIM_DIER_CC1DE  (1<<9) //Capture/compare DMA enable
#define TIM_DIER_CC2DE  (1<<10)
#define TIM_DIER_CC3DE  (1<<11)
#define TIM_DIER_CC4DE  (1<<12)
#define TIM_DIER_TDE    (1<<14) //Trigger DMA request enable


#define TIM_SR_UIF    (1<<0) //update interrupt flag
#define TIM_SR_CC1IF  (1<<1) //Capture/compare int
#define TIM_SR_CC2IF  (1<<2) //
#define TIM_SR_CC3IF  (1<<3) //
#define TIM_SR_CC4IF  (1<<4) //
#define TIM_SR_TIF    (1<<6) //
#define TIM_SR_CC1OF  (1<<9) //overcapture flag
#define TIM_SR_CC2OF  (1<<10)
#define TIM_SR_CC3OF  (1<<11)
#define TIM_SR_CC4OF  (1<<12)


#define TIM_CCMR_CC1_BITPOS         0
#define TIM_CCMR_IC1PSC_BITPOS      2
#define TIM_CCMR_IC1F_BITPOS        4
#define TIM_CCMR_OC1M_BITPOS        4

//0-1
#define TIM_CCMR1_CC1S_OUT             0
#define TIM_CCMR1_CC1S_IN_TI1          1
#define TIM_CCMR1_CC1S_IN_TI2          2
#define TIM_CCMR1_CC1S_IN_TRC          3
#define TIM_CCMR1_CC1S_CLEARMASK       3

//2-3 out
#define TIM_CCMR1_OC1FE              (1<<2) //fast enable
#define TIM_CCMR1_OC1PE              (1<<3) //preload enable

//2-3 input capture prescaler
#define TIM_CCMR1_IC1PSC_DIV1             (0<<2)
#define TIM_CCMR1_IC1PSC_DIV2             (1<<2)
#define TIM_CCMR1_IC1PSC_DIV4             (2<<2)
#define TIM_CCMR1_IC1PSC_DIV8             (3<<2)
#define TIM_CCMR1_IC1PSC_CLEARMASK        (3<<2)

//4-6 output
#define TIM_CCMR1_OC1M_FROZEN             (0<<4)
#define TIM_CCMR1_OC1M_ACTIVE_ON_MATCH    (1<<4)
#define TIM_CCMR1_OC1M_INACTIVE_ON_MATCH  (2<<4)
#define TIM_CCMR1_OC1M_TOGGLE             (3<<4)
#define TIM_CCMR1_OC1M_FORCE_LOW          (4<<4)
#define TIM_CCMR1_OC1M_FORCE_HIGH         (5<<4)
#define TIM_CCMR1_OC1M_PWM1               (6<<4)
#define TIM_CCMR1_OC1M_PWM2               (7<<4)
#define TIM_CCMR1_OC1M_CLEARMASK          (7<<4)
//7  out
#define TIM_CCMR1_OC1CE                   (1<<7)

//4-7 input capture filter
#define TIM_CCMR1_IC1F_FDTS        (0<<4) 
#define TIM_CCMR1_IC1F_FCK_INT_2   (1<<4)
#define TIM_CCMR1_IC1F_FCK_INT_4   (2<<4)
#define TIM_CCMR1_IC1F_FCK_INT_8   (3<<4)
#define TIM_CCMR1_IC1F_FDTS_2_6    (4<<4)
#define TIM_CCMR1_IC1F_FDTS_2_8    (5<<4)
#define TIM_CCMR1_IC1F_FDTS_4_6    (6<<4)
#define TIM_CCMR1_IC1F_FDTS_4_8    (7<<4)
#define TIM_CCMR1_IC1F_FDTS_8_6    (8<<4)
#define TIM_CCMR1_IC1F_FDTS_8_8    (9<<4)
#define TIM_CCMR1_IC1F_FDTS_16_5   (10<<4)
#define TIM_CCMR1_IC1F_FDTS_16_6   (11<<4)
#define TIM_CCMR1_IC1F_FDTS_16_8   (12<<4)
#define TIM_CCMR1_IC1F_FDTS_32_5   (13<<4)
#define TIM_CCMR1_IC1F_FDTS_32_6   (14<<4)
#define TIM_CCMR1_IC1F_FDTS_32_8   (15<<4)
#define TIM_CCMR1_IC1F_CLEARMASK   (15<<4)
//8-9
#define TIM_CCMR1_CC2S_OUT             (0<<8)               
#define TIM_CCMR1_CC2S_IN_TI2          (1<<8)        
#define TIM_CCMR1_CC2S_IN_TI1          (2<<8)        
#define TIM_CCMR1_CC2S_IN_TRC          (3<<8)   
#define TIM_CCMR1_CC2S_CLEARMASK       (3<<8)
//10-11 out
#define TIM_CCMR1_OC2FE                   (1<<10)                 
#define TIM_CCMR1_OC2PE                   (1<<11)                 
//10-11 input capture prescaler
#define TIM_CCMR1_IC2PSC_DIV1             (0<<10)
#define TIM_CCMR1_IC2PSC_DIV2             (1<<10)
#define TIM_CCMR1_IC2PSC_DIV4             (2<<10)
#define TIM_CCMR1_IC2PSC_DIV8             (3<<10)

//12-14 output
#define TIM_CCMR1_OC2M_FROZEN             (0<<12)
#define TIM_CCMR1_OC2M_ACTIVE_ON_MATCH    (1<<12)
#define TIM_CCMR1_OC2M_INACTIVE_ON_MATCH  (2<<12)
#define TIM_CCMR1_OC2M_TOGGLE             (3<<12)
#define TIM_CCMR1_OC2M_FORCE_LOW          (4<<12)
#define TIM_CCMR1_OC2M_FORCE_HIGH         (5<<12)
#define TIM_CCMR1_OC2M_PWM1               (6<<12)
#define TIM_CCMR1_OC2M_PWM2               (7<<12)
//15 out
#define TIM_CCMR1_OC2CE                   (1<<15)


//12-15 input capture filter
#define TIM_CCMR1_IC2F_FDTS        (0<<12) 
#define TIM_CCMR1_IC2F_FCK_INT_2   (1<<12)
#define TIM_CCMR1_IC2F_FCK_INT_4   (2<<12)
#define TIM_CCMR1_IC2F_FCK_INT_8   (3<<12)
#define TIM_CCMR1_IC2F_FDTS_2_6    (4<<12)
#define TIM_CCMR1_IC2F_FDTS_2_8    (5<<12)
#define TIM_CCMR1_IC2F_FDTS_4_6    (6<<12)
#define TIM_CCMR1_IC2F_FDTS_4_8    (7<<12)
#define TIM_CCMR1_IC2F_FDTS_8_6    (8<<12)
#define TIM_CCMR1_IC2F_FDTS_8_8    (9<<12)
#define TIM_CCMR1_IC2F_FDTS_16_5   (10<<12)
#define TIM_CCMR1_IC2F_FDTS_16_6   (11<<12)
#define TIM_CCMR1_IC2F_FDTS_16_8   (12<<12)
#define TIM_CCMR1_IC2F_FDTS_32_5   (13<<12)
#define TIM_CCMR1_IC2F_FDTS_32_6   (14<<12)
#define TIM_CCMR1_IC2F_FDTS_32_8   (15<<12)


//0-1
#define TIM_CCMR2_CC3S_OUT             (0<<0)               
#define TIM_CCMR2_CC3S_IN_TI3          (1<<0)        
#define TIM_CCMR2_CC3S_IN_TI4          (2<<0)        
#define TIM_CCMR2_CC3S_IN_TRC          (3<<0)   



//2-3 out
#define TIM_CCMR2_OC3FE                   TIM_CCMR1_OC1FE                 
#define TIM_CCMR2_OC3PE                   TIM_CCMR1_OC1PE    

//2-3 input capture prescaler
#define TIM_CCMR2_IC3PSC_DIV1             TIM_CCMR1_IC1PSC_DIV1
#define TIM_CCMR2_IC3PSC_DIV2             TIM_CCMR1_IC1PSC_DIV2
#define TIM_CCMR2_IC3PSC_DIV4             TIM_CCMR1_IC1PSC_DIV4
#define TIM_CCMR2_IC3PSC_DIV8             TIM_CCMR1_IC1PSC_DIV8

//4-6 output
#define TIM_CCMR2_OC3M_FROZEN             TIM_CCMR1_OC1M_FROZEN           
#define TIM_CCMR2_OC3M_ACTIVE_ON_MATCH    TIM_CCMR1_OC1M_ACTIVE_ON_MATCH  
#define TIM_CCMR2_OC3M_INACTIVE_ON_MATCH  TIM_CCMR1_OC1M_INACTIVE_ON_MATCH
#define TIM_CCMR2_OC3M_TOGGLE             TIM_CCMR1_OC1M_TOGGLE           
#define TIM_CCMR2_OC3M_FORCE_LOW          TIM_CCMR1_OC1M_FORCE_LOW        
#define TIM_CCMR2_OC3M_FORCE_HIGH         TIM_CCMR1_OC1M_FORCE_HIGH       
#define TIM_CCMR2_OC3M_PWM1               TIM_CCMR1_OC1M_PWM1             
#define TIM_CCMR2_OC3M_PWM2               TIM_CCMR1_OC1M_PWM2             
//7  out
#define TIM_CCMR2_OC3CE                   TIM_CCMR1_OC1CE                 

//4-7 input capture filter
#define TIM_CCMR2_IC3F_FDTS        TIM_CCMR1_IC1F_FDTS     
#define TIM_CCMR2_IC3F_FCK_INT_2   TIM_CCMR1_IC1F_FCK_INT_2
#define TIM_CCMR2_IC3F_FCK_INT_4   TIM_CCMR1_IC1F_FCK_INT_4
#define TIM_CCMR2_IC3F_FCK_INT_8   TIM_CCMR1_IC1F_FCK_INT_8
#define TIM_CCMR2_IC3F_FDTS_2_6    TIM_CCMR1_IC1F_FDTS_2_6 
#define TIM_CCMR2_IC3F_FDTS_2_8    TIM_CCMR1_IC1F_FDTS_2_8 
#define TIM_CCMR2_IC3F_FDTS_4_6    TIM_CCMR1_IC1F_FDTS_4_6 
#define TIM_CCMR2_IC3F_FDTS_4_8    TIM_CCMR1_IC1F_FDTS_4_8 
#define TIM_CCMR2_IC3F_FDTS_8_6    TIM_CCMR1_IC1F_FDTS_8_6 
#define TIM_CCMR2_IC3F_FDTS_8_8    TIM_CCMR1_IC1F_FDTS_8_8 
#define TIM_CCMR2_IC3F_FDTS_16_5   TIM_CCMR1_IC1F_FDTS_16_5
#define TIM_CCMR2_IC3F_FDTS_16_6   TIM_CCMR1_IC1F_FDTS_16_6
#define TIM_CCMR2_IC3F_FDTS_16_8   TIM_CCMR1_IC1F_FDTS_16_8
#define TIM_CCMR2_IC3F_FDTS_32_5   TIM_CCMR1_IC1F_FDTS_32_5
#define TIM_CCMR2_IC3F_FDTS_32_6   TIM_CCMR1_IC1F_FDTS_32_6
#define TIM_CCMR2_IC3F_FDTS_32_8   TIM_CCMR1_IC1F_FDTS_32_8

//8-9 in/out
#define TIM_CCMR2_CC4S_OUT             (0<<8)               
#define TIM_CCMR2_CC4S_IN_TI4          (1<<8)        
#define TIM_CCMR2_CC4S_IN_TI3          (2<<8)        
#define TIM_CCMR2_CC4S_IN_TRC          (3<<8)   

//10-11 out
#define TIM_CCMR2_OC4FE                   TIM_CCMR1_OC2FE                 
#define TIM_CCMR2_OC4PE                   TIM_CCMR1_OC2PE    

//10-11 input capture prescaler
#define TIM_CCMR2_IC4PSC_DIV1             TIM_CCMR1_IC2PSC_DIV1
#define TIM_CCMR2_IC4PSC_DIV2             TIM_CCMR1_IC2PSC_DIV2
#define TIM_CCMR2_IC4PSC_DIV4             TIM_CCMR1_IC2PSC_DIV4
#define TIM_CCMR2_IC4PSC_DIV8             TIM_CCMR1_IC2PSC_DIV8


//12-14 output
#define TIM_CCMR2_OC4M_FROZEN             TIM_CCMR1_OC2M_FROZEN           
#define TIM_CCMR2_OC4M_ACTIVE_ON_MATCH    TIM_CCMR1_OC2M_ACTIVE_ON_MATCH  
#define TIM_CCMR2_OC4M_INACTIVE_ON_MATCH  TIM_CCMR1_OC2M_INACTIVE_ON_MATCH
#define TIM_CCMR2_OC4M_TOGGLE             TIM_CCMR1_OC2M_TOGGLE           
#define TIM_CCMR2_OC4M_FORCE_LOW          TIM_CCMR1_OC2M_FORCE_LOW        
#define TIM_CCMR2_OC4M_FORCE_HIGH         TIM_CCMR1_OC2M_FORCE_HIGH       
#define TIM_CCMR2_OC4M_PWM1               TIM_CCMR1_OC2M_PWM1             
#define TIM_CCMR2_OC4M_PWM2               TIM_CCMR1_OC2M_PWM2             
//15 out
#define TIM_CCMR2_OC4CE                   TIM_CCMR1_OC2CE                 


//12-15 input capture filter
#define TIM_CCMR2_IC4F_FDTS              TIM_CCMR1_IC2F_FDTS         
#define TIM_CCMR2_IC4F_FCK_INT_2         TIM_CCMR1_IC2F_FCK_INT_2 
#define TIM_CCMR2_IC4F_FCK_INT_4         TIM_CCMR1_IC2F_FCK_INT_4 
#define TIM_CCMR2_IC4F_FCK_INT_8         TIM_CCMR1_IC2F_FCK_INT_8 
#define TIM_CCMR2_IC4F_FDTS_2_6          TIM_CCMR1_IC2F_FDTS_2_6  
#define TIM_CCMR2_IC4F_FDTS_2_8          TIM_CCMR1_IC2F_FDTS_2_8  
#define TIM_CCMR2_IC4F_FDTS_4_6          TIM_CCMR1_IC2F_FDTS_4_6  
#define TIM_CCMR2_IC4F_FDTS_4_8          TIM_CCMR1_IC2F_FDTS_4_8  
#define TIM_CCMR2_IC4F_FDTS_8_6          TIM_CCMR1_IC2F_FDTS_8_6  
#define TIM_CCMR2_IC4F_FDTS_8_8          TIM_CCMR1_IC2F_FDTS_8_8  
#define TIM_CCMR2_IC4F_FDTS_16_5         TIM_CCMR1_IC2F_FDTS_16_5 
#define TIM_CCMR2_IC4F_FDTS_16_6         TIM_CCMR1_IC2F_FDTS_16_6 
#define TIM_CCMR2_IC4F_FDTS_16_8         TIM_CCMR1_IC2F_FDTS_16_8 
#define TIM_CCMR2_IC4F_FDTS_32_5         TIM_CCMR1_IC2F_FDTS_32_5 
#define TIM_CCMR2_IC4F_FDTS_32_6         TIM_CCMR1_IC2F_FDTS_32_6 
#define TIM_CCMR2_IC4F_FDTS_32_8         TIM_CCMR1_IC2F_FDTS_32_8 


#define TIM_CCER_CC1E  (1<<0)
#define TIM_CCER_CC1P  (1<<1)
#define TIM_CCER_CC2E  (1<<4)
#define TIM_CCER_CC2P  (1<<5)
#define TIM_CCER_CC3E  (1<<8)
#define TIM_CCER_CC3P  (1<<9)
#define TIM_CCER_CC4E  (1<<12)
#define TIM_CCER_CC4P  (1<<13)


#define TIM_SMCR_SMS_OFF        0
#define TIM_SMCR_SMS_ENC1       1  
#define TIM_SMCR_SMS_ENC2       2  
#define TIM_SMCR_SMS_ENC3       3 
#define TIM_SMCR_SMS_RESET      4 
#define TIM_SMCR_SMS_GATED      5
#define TIM_SMCR_SMS_TRIGGER    6
#define TIM_SMCR_SMS_EXT        7
#define TIM_SMCR_SMS_CLEARMASK 7
//100x
#define TIM_SMCR_OCCS        (1<<3)

#define TIM_SMCR_TS_ITR0        (0<<4)
#define TIM_SMCR_TS_ITR1        (1<<4)
#define TIM_SMCR_TS_ITR2        (2<<4)
#define TIM_SMCR_TS_ITR3        (3<<4)
#define TIM_SMCR_TS_TI1F_ED     (4<<4)
#define TIM_SMCR_TS_TI1FP1      (5<<4)
#define TIM_SMCR_TS_TI1FP2      (6<<4)
#define TIM_SMCR_TS_ETRF        (7<<4)
#define TIM_SMCR_TS_CLEARMASK   (7<<4)
#define TIM_SMCR_MSM            (1<<7)
//external trigger stuff


#define TIM_EGR_UG    (1<<0)
#define TIM_EGR_CC1G  (1<<1)
#define TIM_EGR_CC2G  (1<<2)
#define TIM_EGR_CC3G  (1<<3)
#define TIM_EGR_CC4G  (1<<4)
#define TIM_EGR_TG    (1<<6)

#define TIM_DCR_DBA_OFFSET   0
#define TIM_DCR_DBL_OFFSET   8

#define TIM_BDTR_MOE  (1<<15)


typedef struct 
{
  uint32_t volatile TIM_BASE;
  uint32_t volatile RCC_APBxENR_TIMxEN;
  uint32_t volatile NVIC_TIMx_IRQ;
  
} _timer_init2;


typedef struct _TIMER_type
{
	volatile uint32_t* cr1;
	volatile uint32_t* dier;
	volatile uint32_t* sr;
	volatile uint32_t* egr;
	volatile uint32_t* cnt;
	volatile uint32_t* psc;
	volatile uint32_t* arr;

} TIMER_type;


typedef enum
{
	TIMER_1,
	TIMER_2,
	TIMER_3,
	TIMER_4,
	TIMER_5,
	TIMER_6,
	TIMER_7,
	TIMER_8,
	TIMER_9,
	TIMER_10,
	TIMER_11,
	TIMER_12,
	TIMER_13,
	TIMER_14,
	TIMER_15,
	TIMER_16,
	TIMER_17,
	TIMER_18,
	TIMER_19,
	TIMER_20

} TIMER_number;

typedef struct _TIMER_lookup
{


}TIMER_lookup;


#endif

#endif
