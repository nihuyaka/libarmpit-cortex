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



#ifndef _RCC_H
#define _RCC_H

#include "common.h"

#define HSI_CLOCK_FREQ  16000000

#ifndef HSE_CLOCK_FREQ 
#define HSE_CLOCK_FREQ 8000000
#endif


/* RCC  ****************************************************/
#define RCC_BASE    0x40023800

#include "common.h"

#include "rcc_cr.h"
#include "rcc_pllcfgr.h"
#include "rcc_cfgr.h"
#include "rcc_ahb.h"
#include "rcc_apb1.h"
#include "rcc_apb2.h"
#include "rcc_bdcr.h"
#include "rcc_csr.h"
#include "rcc_ckgatenr.h"

#define AHB1_BASE 0x40020000
#define AHB2_BASE 0x50000000
#define AHB3_BASE 0xA0001000 
#define APB2_BASE 0x40010000
#define APB1_BASE 0x40000000

#ifdef __cplusplus
extern "C"
{
#endif


void RCC_EnableHSI(BOOL enable);
void RCC_EnableHSE(BOOL enable);
void RCC_EnablePLL(uint8_t pllm, uint16_t plln, uint8_t pllp);
void RCC_DisablePLL(void);

void RCC_BypassHSE(BOOL bypassHSE);

uint32_t RCC_GetSystemClock(void); 
uint32_t RCC_GetAHB_CLK(void);
uint32_t RCC_GetAPB1_CLK(void);
uint32_t RCC_GetAPB2_CLK(void);
uint32_t RCC_GetTIMx_CLK(BOOL isAPB1);

void RCC_Delay_ms(uint32_t ms);
void RCC_Delay_us(uint32_t us);

    
//prescalers

void RCC_SetAHBPrescalerDiv1(void);    
void RCC_SetAHBPrescalerDiv2(void);
void RCC_SetAHBPrescalerDiv4(void);
void RCC_SetAHBPrescalerDiv8(void);
void RCC_SetAHBPrescalerDiv16(void);
void RCC_SetAHBPrescalerDiv64(void);
void RCC_SetAHBPrescalerDiv128(void);
void RCC_SetAHBPrescalerDiv256(void);
void RCC_SetAHBPrescalerDiv512(void);

void RCC_SetAPB1PrescalerDiv1(void);
void RCC_SetAPB1PrescalerDiv2(void);
void RCC_SetAPB1PrescalerDiv4(void);
void RCC_SetAPB1PrescalerDiv8(void);
void RCC_SetAPB1PrescalerDiv16(void);

void RCC_SetAPB2PrescalerDiv1(void);
void RCC_SetAPB2PrescalerDiv2(void);
void RCC_SetAPB2PrescalerDiv4(void);
void RCC_SetAPB2PrescalerDiv8(void);
void RCC_SetAPB2PrescalerDiv16(void);
    

//low level functions, can do without
BOOL RCC_calculate_pll_parameters (const uint32_t inputClockFreq, const uint32_t targetFreq, uint8_t* pllm, uint16_t* plln, uint8_t* pllp) ;
void RCC_SetPLLN (uint16_t plln);
void RCC_SetPLLM (uint8_t pllm) ;
void RCC_SetPLLP(uint8_t pllm);


#ifdef __cplusplus
}
#endif




#endif
