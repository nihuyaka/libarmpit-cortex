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



#include "systick.h"

static void (*g_handler)(void);

#ifdef __cplusplus
extern "C"
{
#endif

void SysTick_Handler(void) 
{
    if (g_handler)
    {
        g_handler();
    }
}

#ifdef __cplusplus
}
#endif

#if defined(STM32) 
void SystickEnable (uint32_t count, BOOL enableInterrupt, BOOL isDIV8, void (*handler)(void))
#else 
void SystickEnable (uint32_t count, BOOL enableInterrupt, void (*handler)(void))
#endif
{
    SYST_LOAD = (count - 1) & 0xffffff;
    
    SYST_VAL = 0;
    if (enableInterrupt)
    {
        SYST_CSR |= SYST_CSR_TICKINT;
    }
    else
    {
        SYST_CSR &= ~SYST_CSR_TICKINT;
    }

    SYST_CSR &= ~SYST_CSR_CLKSOURCE_CLEARMASK;

#if defined(STM32) 
    if (isDIV8)
    {
        SYST_CSR |= SYST_CSR_CLKSOURCE_AHB_DIV8;
    }
    else
    {
        SYST_CSR |= SYST_CSR_CLKSOURCE_AHB;
    }
#else
        SYST_CSR |= SYST_CSR_CLKSOURCE_CORE;
#endif

    SYST_CSR |= SYST_CSR_ENABLE;

    g_handler = handler;

}

void SystickSetReloadValue (uint32_t count)
{
    SYST_LOAD = count;
    SYST_VAL = 0;
}

void SystickDisable(void)
{
    SYST_CSR &= ~SYST_CSR_ENABLE;
}

