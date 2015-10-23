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



#ifdef __cplusplus
extern "C"
{
#endif

#include "rcc.h"
#include "system_control.h"
    
//In all the examples system init is done as the first step in main (starting clocks, setting flash latency etc) 
//Can also do it here. (Makes no difference?)  This location is pointed to by the assembly start-up files provided by ARM
void SystemInit(void)
{
    FPU_Enable(TRUE);
    SCB_EnableBusFault();
    SCB_EnableDivByZeroTrap();
    SCB_EnableMemoryFault();
    SCB_EnableUnalignedTrap();
    SCB_EnableUsageFault();
}


void HardFault_Handler(void) 
{
    static volatile SCB_SHCSR_def shcsr;
    static volatile SCB_CFSR_def cfsr;
    SCB_GetFaulStatus (&shcsr, &cfsr);
    while(1);
}

void UsageFault_Handler(void) 
{
    static volatile SCB_SHCSR_def shcsr;
    static volatile SCB_CFSR_def cfsr;
    SCB_GetFaulStatus (&shcsr, &cfsr);
    while(1);
}

void BusFault_Handler(void) 
{
    static volatile SCB_SHCSR_def shcsr;
    static volatile SCB_CFSR_def cfsr;
    SCB_GetFaulStatus (&shcsr, &cfsr);
    while(1);
}

void MemManage_Handler(void) 
{
    static volatile SCB_SHCSR_def shcsr;
    static volatile SCB_CFSR_def cfsr;
    SCB_GetFaulStatus (&shcsr, &cfsr);
    while(1);
}




#ifdef __cplusplus
}
#endif
