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


#ifndef _NVI_H
#define _NVI_H

#include "common.h"
#include "irq.h"

#define NVIC_ISER   (*(volatile uint32_t*)(0xE000E100))
#define NVIC_ICER   (*(volatile uint32_t*)(0xE000E180))
#define NVIC_ISPR   (*(volatile uint32_t*)(0xE000E200))
#define NVIC_ICPR   (*(volatile uint32_t*)(0xE000E280))
#define NVIC_IABR   (*(volatile uint32_t*)(0xE000E300))
#define NVIC_IPR    (*(volatile uint32_t*)(0xE000E400))


#ifdef __cplusplus
extern "C"
{
#endif

void NVIC_SetEnable (IRQn_Type irqNo);
void NVIC_ClearEnable (IRQn_Type irqNo);
void NVIC_SetPending (IRQn_Type irqNo); 
void NVIC_ClearPending (IRQn_Type irqNo); 
int NVIC_IsActive (IRQn_Type irqNo);

void NVIC_SetPriority (IRQn_Type irqNo, uint8_t priority); 
int NVIC_GetPriority (IRQn_Type irqNo);


#ifdef __cplusplus
}
#endif


#endif
