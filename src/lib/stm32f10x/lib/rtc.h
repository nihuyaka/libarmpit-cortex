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


#ifndef _RTC_H
#define _RTC_H

#include "common.h"

#ifdef USE_RTC

//18. ********************  RTC APB1  *****************************
#define RTC_OFFSET 0x2800
#define RTC_BASE (PERIPH_BASE + RTC_OFFSET)
#define RTC_CRH  (*(volatile uint32_t*)(RTC_BASE))


#define RTC_CRH_SECIE (1<<0)  //Second interrupt enable 
#define RTC_CRH_ALRIE (1<<1)  //Alarm interrupt enable 
#define RTC_CRH_OWIE  (1<<2)  //Overflow interrupt enable

#define RTC_CRL  (*(volatile uint32_t*)(RTC_BASE + 0x4))
  
#define RTC_CRL_SECF (1<<0)   //set by hardware when the 32-bit programmable prescaler overflows
                 //An interrupt is generated if SECIE=1 in the RTC_CRH register. 

#define RTC_CRL_ALRF (1<<1)   //set by hardware when the 32-bit programmable counter reaches the threshold set 
                 // in the RTC_ALR register. 
                 // An interrupt is generated if ALRIE=1 in the RTC_CRH register.

#define RTC_CRL_OWF  (1<<2)   //set by hardware when the 32-bit programmable counter overflows. 
                 //An interrupt is generated if OWIE=1 in the RTC_CRH register.

#define RTC_CRL_RSF   (1<<3) 
#define RTC_CRL_CNF   (1<<4) 
#define RTC_CRL_RTOFF (1<<5) 

#define RTC_PRLH  (*(volatile uint16_t*)(RTC_BASE + 0x8))
#define RTC_PRLL  (*(volatile uint16_t*)(RTC_BASE + 0xc))
#define RTC_PRL  (*(volatile uint32_t*)(RTC_BASE + 0xc))

#define RTC_DIV  (*(volatile uint32_t*)(RTC_BASE + 0x14))

#define RTC_CNTH  (*(volatile uint16_t*)(RTC_BASE + 0x18))
#define RTC_CNTL  (*(volatile uint16_t*)(RTC_BASE + 0x1c))
#define RTC_CNT   (*(volatile uint32_t*)(RTC_BASE + 0x1c))
#define RTC_ALRH  (*(volatile uint16_t*)(RTC_BASE + 0x20))
#define RTC_ALRL  (*(volatile uint16_t*)(RTC_BASE + 0x24))
#define RTC_ALR   (*(volatile uint32_t*)(RTC_BASE + 0x24))


#endif

#endif
