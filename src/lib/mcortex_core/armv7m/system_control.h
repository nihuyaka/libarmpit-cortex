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



#ifndef _SYSTEM_CONTROL_H
#define _SYSTEM_CONTROL_H

#include "common.h"


#define  SCB_CPUID  (*(volatile uint32_t*)(0xE000ED00))   //CPU ID 
#define  SCB_CPUID_REVISION_SHIFT 0
#define  SCB_CPUID_PARTNO_SHIFT 4
#define  SCB_CPUID_ARCHITECTURE_SHIFT 16
#define  SCB_CPUID_VARIANT_SHIFT 20
#define  SCB_CPUID_IMPLEMENTER_SHIFT 24

#define  SCB_CPUID_REVISION_MASK     (0xf    << SCB_CPUID_REVISION_SHIFT) 
#define  SCB_CPUID_PARTNO_MASK       (0x1000 << SCB_CPUID_REVISION_MASK) 
#define  SCB_CPUID_ARCHITECTURE_MASK (0xf    << SCB_CPUID_ARCHITECTURE_SHIFT) 
#define  SCB_CPUID_VARIANT_MASK      (0xf    << SCB_CPUID_VARIANT_SHIFT) 
#define  SCB_CPUID_IMPLEMENTER_MASK  (0xfful   << SCB_CPUID_IMPLEMENTER_SHIFT) 

#define  SCB_ICSR   (*(volatile uint32_t*)(0xE000ED04)) 
#define  SCB_ICSR_VECTPENDING_SHIFT 12
#define  SCB_ICSR_VECTPENDING_MASK (0x400 << SCB_ICSR_VECTPENDING_SHIFT)  //Subtract 16 to get IRQ number (sys exceptions are negative numbers)
#define  SCB_ICSR_PENDSTCLR   (1<<25) // Write 1 to clear pending SysTick interrupt
#define  SCB_ICSR_PENDSTSET   (1<<26) 
#define  SCB_ICSR_PENDSVCLR   (1<<27)  //
#define  SCB_ICSR_PENDSVSET   (1<<28)
#define  SCB_ICSR_NMIPENDSET  (1<<31)


#define  SCB_VTOR   (*(volatile uint32_t*)(0xE000ED08)) 


#define  SCB_AIRCR  (*(volatile uint32_t*)(0xE000ED0C)) 
#define  SCB_AIRCR_VECTRESET     (1<<0) 
#define  SCB_AIRCR_VECTCLRACTIVE (1<<1) 
#define  SCB_AIRCR_SYSRESETREQ   (1<<2) 
#define  SCB_AIRCR_ENDIANNESS    (1<<15) 
#define  SCB_AIRCR_VECTKEY_SHIFT 16 

#define  SCB_SCR    (*(volatile uint32_t*)(0xE000ED10)) 
#define  SCB_SCR_SLEEPONEXIT   (1<<1)
#define  SCB_SCR_SLEEPDEEP     (1<<2)
#define  SCB_SCR_SEVONPEND     (1<<4)

#define  SCB_CCR    (*(volatile uint32_t*)(0xE000ED14)) 
#define  SCB_CCR_NONBASETHRDENA  (1<<0)
#define  SCB_CCR_USERSETMPEND    (1<<1)
#define  SCB_CCR_UNALIGN_TRP     (1<<3)
#define  SCB_CCR_DIV_0_TRP       (1<<4)
#define  SCB_CCR_BFHFNMIGN       (1<<8)
#define  SCB_CCR_STKALIGN        (1<<9)

#define  SCB_SHPR1  (*(volatile uint32_t*)(0xE000ED18)) 
#define  SCB_SHPR2  (*(volatile uint32_t*)(0xE000ED1C)) 
#define  SCB_SHPR3  (*(volatile uint32_t*)(0xE000ED20)) 

#define  SCB_SHCSR  (*(volatile uint32_t*)(0xE000ED24)) 
#define  SCB_SHCSR_MEMFAULTACT  (1<<0)
#define  SCB_SHCSR_BUSFAULTACT  (1<<1)
#define  SCB_SHCSR_USGFAULTACT  (1<<3)
#define  SCB_SHCSR_SVCALLACT    (1<<7)
#define  SCB_SHCSR_MONITORACT   (1<<8)
#define  SCB_SHCSR_PENDSVACT    (1<<9)
#define  SCB_SHCSR_SYSTICKACT   (1<<11)
#define  SCB_SHCSR_USGFAULTPENDED  (1<<12)
#define  SCB_SHCSR_MEMFAULTPENDED  (1<<13)
#define  SCB_SHCSR_BUSFAULTPENDED  (1<<14)
#define  SCB_SHCSR_SVCALLPENDED  (1<<15)
#define  SCB_SHCSR_MEMFAULTENA  (1<<16)
#define  SCB_SHCSR_BUSFAULTENA  (1<<17)
#define  SCB_SHCSR_USGFAULTENA  (1<<18)

typedef struct 
{
    BOOL memFaultActive;
    BOOL busFaultActive;
    BOOL usageFaultActive;
    BOOL memFaultPending;
    BOOL busFaultPending;
    BOOL usageFaultPending;

} SCB_SHCSR_def;




#define  SCB_CFSR  (*(volatile uint32_t*)(0xE000ED28)) 
#define  SCB_MMFSR (*(volatile uint8_t*)(0xE000ED28)) 
#define  SCB_BFSR (*(volatile uint8_t*)(0xE000ED29)) 
#define  SCB_UFSR (*(volatile uint16_t*)(0xE000ED2A)) 

#define  SCB_CFSR_IACCVIOL (1<<0) 
#define  SCB_CFSR_DACCVIOL (1<<1) 
#define  SCB_CFSR_MUNSTKERR (1<<3) 
#define  SCB_CFSR_MSTKERR (1<<4) 
#define  SCB_CFSR_MLSPERR (1<<5) 
#define  SCB_CFSR_MMARVALID (1<<7) 
#define  SCB_CFSR_IBUSERR (1<<8) 
#define  SCB_CFSR_PRECISERR (1<<9) 
#define  SCB_CFSR_IMPRECISERR (1<<10) 
#define  SCB_CFSR_UNSTKERR (1<<11) 
#define  SCB_CFSR_STKERR (1<<12) 
#define  SCB_CFSR_LSPERR (1<<13) 
#define  SCB_CFSR_BFARVALID (1<<15) 
#define  SCB_CFSR_UNDEFINSTR (1<<16) 
#define  SCB_CFSR_INVSTATE (1<<17) 
#define  SCB_CFSR_INVPC (1<<18) 
#define  SCB_CFSR_NOCP (1<<19) 
#define  SCB_CFSR_UNALIGNED (1<<24) 
#define  SCB_CFSR_DIVBYZERO (1<<25) 

typedef struct 
{
    BOOL IACCVIOL;
    BOOL DACCVIOL;
    BOOL MUNSTKERR;
    BOOL MSTKERR;
    BOOL MLSPERR;
    BOOL MMARVALID;
    BOOL IBUSERR;
    BOOL PRECISERR;
    BOOL IMPRECISERR;
    BOOL UNSTKERR;
    BOOL STKERR;
    BOOL LSPERR;
    BOOL BFARVALID;
    BOOL UNDEFINSTR;
    BOOL INVSTATE;
    BOOL INVPC;
    BOOL NOCP;
    BOOL UNALIGNED;
    BOOL DIVBYZERO;

} SCB_CFSR_def;

#define  SCB_MMFAR (*(volatile uint8_t*)(0xE000ED34)) 
#define  SCB_BFAR (*(volatile uint8_t*)(0xE000ED38)) 

//coproc / floating point
#define  CPACR (*(volatile uint32_t*)(0xE000ED88)) 
#define  FPCCR (*(volatile uint32_t*)(0xE000EF34)) 
#define  FPCAR (*(volatile uint32_t*)(0xE000EF38)) 
#define  FPDSCR (*(volatile uint32_t*)(0xE000EF3C)) 


#define CPACR_CP10_ACCESS_DENIED    (0<<20)
#define CPACR_CP10_PRIVILEGED_ONLY  (1<<20)
#define CPACR_CP10_FULL_ACCESS      (3<<20)
#define CPACR_CP10_CLEARMASK        (3<<20)

#define CPACR_CP11_ACCESS_DENIED    (0<<22)
#define CPACR_CP11_PRIVILEGED_ONLY  (1<<22)
#define CPACR_CP11_FULL_ACCESS      (3<<22)
#define CPACR_CP11_CLEARMASK        (3<<22)


#ifdef __cplusplus
extern "C"
{
#endif


void SCB_ReadCPUID (uint16_t* implementer_id, uint16_t* variant_id, uint16_t* architecture_id, uint16_t* partno_id, uint16_t* revision_id, BOOL* is_bigendian);

int8_t SCB_GetPendingIRQNo(void);

void SCB_SystemReset(void);

void SCB_SetSleepOnExit(BOOL set);
void SCB_SetSleepDeep(BOOL set);
void SCB_SetSEVONPEND(BOOL set);

void SCB_EnableDivByZeroTrap();
void SCB_EnableUnalignedTrap();
void SCB_EnableMemoryFault();
void SCB_EnableUsageFault();
void SCB_EnableBusFault();

void SCB_GetFaulStatus (volatile SCB_SHCSR_def* shcsr, volatile SCB_CFSR_def* cfsr);

void FPU_Enable (BOOL enable);


#ifdef __cplusplus
}
#endif


#endif
