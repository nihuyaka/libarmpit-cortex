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



#ifndef _SYSTICK_H
#define _SYSTICK_H

#include "common.h"


#define  SYST_CSR  (*(volatile uint32_t*)(0xE000E010))    //control
#define  SYST_LOAD  (*(volatile uint32_t*)(0xE000E014))    //reload value
#define  SYST_VAL  (*(volatile uint32_t*)(0xE000E018))    //current value
#define  SYST_CALIB  (*(volatile uint32_t*)(0xE000E01C))

#define  SYST_CSR_ENABLE   (1<<0) 
#define  SYST_CSR_TICKINT  (1<<1) 
#if defined(STM32) 
#define  SYST_CSR_CLKSOURCE_AHB_DIV8   (0<<2) 
#define  SYST_CSR_CLKSOURCE_AHB        (1<<2) 
#else
#define  SYST_CSR_CLKSOURCE_CORE        (1<<2) 
#endif
#define  SYST_CSR_CLKSOURCE_CLEARMASK  (1<<2) 
#define  SYST_CSR_COUNTFLAG  (1<<16) 


#ifdef __cplusplus
 extern "C" {
#endif

#if defined(STM32) 
void SystickEnable (uint32_t count, BOOL enableInterrupt, BOOL isDIV8, void (*handler)(void));
#else 
void SystickEnable (uint32_t count, BOOL enableInterrupt, void (*handler)(void));
#endif

void SystickDisable(void);
void SystickSetReloadValue (uint32_t count);

#ifdef __cplusplus
 }
 #endif


#endif
