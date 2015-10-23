#include "system_control.h" 

void SystemControl_ReadCPUID (uint16_t* implementer_id, uint16_t* variant_id, uint16_t* architecture_id, uint16_t* partno_id, uint16_t* revision_id, BOOL* is_bigendian)
{
    *revision_id =  (SCB_CPUID & CPUID_REVISION_MASK) >> CPUID_REVISION_SHIFT;
    *partno_id =  (SCB_CPUID & CPUID_PARTNO_MASK) >> CPUID_PARTNO_SHIFT;
    *architecture_id = (SCB_CPUID & CPUID_ARCHITECTURE_MASK) >> CPUID_ARCHITECTURE_SHIFT;
    *variant_id = (SCB_CPUID & CPUID_VARIANT_MASK) >> CPUID_VARIANT_SHIFT;
    *implementer_id = (SCB_CPUID & CPUID_IMPLEMENTER_MASK) >> CPUID_IMPLEMENTER_SHIFT;

    *is_bigendian = (SCB_AIRCR & AIRCR_ENDIANNESS);

}

int8_t SystemControl_GetPendingIRQNo()
{
    return ((SCB_ICSR & ICSR_VECTPENDING_MASK) >> ICSR_VECTPENDING_SHIFT) -  16;
}

void SystemControl_SystemReset() 
{
    SCB_AIRCR |= AIRCR_SYSRESETREQ;
}

void SystemControl_SetSleepOnExit(BOOL set)
{
    if (set)
        SCB_SCR |= SCR_SLEEPONEXIT;
    else
        SCB_SCR &= ~SCR_SLEEPONEXIT;

}

void SystemControl_SetSleepDeep(BOOL set)
{
    if (set)
        SCB_SCR |= SCR_SLEEPDEEP;
    else
        SCB_SCR &= ~SCR_SLEEPDEEP;
}

void SystemControl_SetSEVONPEND(BOOL set)
{
    if (set)
        SCB_SCR |= SCR_SEVONPEND;
    else
        SCB_SCR &= ~SCR_SEVONPEND;
}
