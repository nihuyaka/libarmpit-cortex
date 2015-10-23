#ifndef _SYSTEM_CONTROL_H
#define _SYSTEM_CONTROL_H

#include "common.h"


#define  SCB_CPUID  (*(volatile uint32_t*)(0xE000ED00))   //CPU ID 
#define  SCB_ICSR   (*(volatile uint32_t*)(0xE000ED04)) 
#define  SCB_VTOR   (*(volatile uint32_t*)(0xE000ED08)) 
#define  SCB_AIRCR  (*(volatile uint32_t*)(0xE000ED0C)) 
#define  SCB_SCR    (*(volatile uint32_t*)(0xE000ED10)) 
#define  SCB_CCR    (*(volatile uint32_t*)(0xE000ED14)) 
#define  SCB_SHPR2  (*(volatile uint32_t*)(0xE000ED1C)) 
#define  SCB_SHPR3  (*(volatile uint32_t*)(0xE000ED20)) 



#define  CPUID_REVISION_SHIFT 0
#define  CPUID_PARTNO_SHIFT 4
#define  CPUID_ARCHITECTURE_SHIFT 16
#define  CPUID_VARIANT_SHIFT 20
#define  CPUID_IMPLEMENTER_SHIFT 24

#define  CPUID_REVISION_MASK     (0xf    << CPUID_REVISION_SHIFT) 
#define  CPUID_PARTNO_MASK       (0x1000 << CPUID_REVISION_MASK) 
#define  CPUID_ARCHITECTURE_MASK (0xf    << CPUID_ARCHITECTURE_SHIFT) 
#define  CPUID_VARIANT_MASK      (0xf    << CPUID_VARIANT_SHIFT) 
#define  CPUID_IMPLEMENTER_MASK  (0xff   << CPUID_IMPLEMENTER_SHIFT) 


#define  ICSR_VECTPENDING_SHIFT 12
#define  ICSR_VECTPENDING_MASK (0x400 << ICSR_VECTPENDING_SHIFT)  //Subtract 16 to get IRQ number (sys exceptions are negative numbers)
#define  ICSR_PENDSTCLR   (1<<25) // Write 1 to clear pending SysTick interrupt
#define  ICSR_PENDSTSET   (1<<26) 
#define  ICSR_PENDSVCLR   (1<<27)  //
#define  ICSR_PENDSVSET   (1<<28)
#define  ICSR_NMIPENDSET  (1<<31)

#define  AIRCR_VECTCLRACTIVE (1<<1) 
#define  AIRCR_SYSRESETREQ   (1<<2) 
#define  AIRCR_ENDIANNESS    (1<<15) 
#define  AIRCR_VECTKEY_SHIFT 16 


#define  SCR_SLEEPONEXIT   (1<<1)
#define  SCR_SLEEPDEEP     (1<<2)
#define  SCR_SEVONPEND     (1<<4)


void SystemControl_ReadCPUID (uint16_t* implementer_id, uint16_t* variant_id, uint16_t* architecture_id, uint16_t* partno_id, uint16_t* revision_id, BOOL* is_bigendian);

int8_t SCB_GetPendingIRQNo(void);

void SCB_SystemReset(void);

void SystemControl_SetSleepOnExit(BOOL set);
void SystemControl_SetSleepDeep(BOOL set);
void SystemControl_SetSEVONPEND(BOOL set);


#endif
