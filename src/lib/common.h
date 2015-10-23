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



#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>
#include <stddef.h>
#include "_components.h"
#include "stm32.h"
#include "kinetis.h"
#include "efm32.h"

#if !defined(Kinetis) && !defined(STM32) && !defined(EFM32)
 #error "Target device not defined in the project settings"
#endif

#include "irq.h" 

#define UNUSED(arg)  ((void)arg)

#define PERIPH_BASE  0x40000000


// Automaic dependencies:


#if defined(USE_RTC) && !defined(USE_BKP)
#define USE_BKP
#ifndef USE_EXTI
#define USE_EXTI
#endif
#endif

#if defined(USE_BKP) && !defined(USE_PWR)
#define USE_PWR
#endif

#if defined(USE_SPI) && !defined(USE_DMA)
#define USE_DMA
#endif

#if defined(USE_USART) && !defined(USE_DMA)
#define USE_DMA
#endif

#if defined(USE_I2C) && !defined(USE_DMA)
#define USE_DMA
#endif

typedef int BOOL;

#define TRUE 1 
#define FALSE 0

#if defined(__GNUC__) && defined (__cplusplus)
#include <bits/c++config.h>
#include <malloc.h>
inline void* operator new (std::size_t size) {return ::malloc(size);}
#endif


#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#endif

