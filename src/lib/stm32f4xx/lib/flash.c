#include "flash.h"

#ifdef __cplusplus
extern "C"
{
#endif


void FLASH_SetWaitState(uint8_t wait_state)
{
    FLASH_ACR |= wait_state<<FLASH_ACR_LATENCY_OFFSET;
}

void FLASH_EnableICache()
{
    FLASH_ACR |= FLASH_ACR_ICEN;
}

void FLASH_EnableDCache()
{
    FLASH_ACR |= FLASH_ACR_DCEN;
}

void FLASH_EnablePrefetchBuffer()
{
    FLASH_ACR |= FLASH_ACR_PRFTEN;
}

void FLASH_Unlock(void) 
{
    FLASH_KEYR = FLASH_KEY1;   
    FLASH_KEYR = FLASH_KEY2;   
//    while (FLASH_IsLocked())
//        ; 
}

void FLASH_OptUnlock(void) 
{
    FLASH_OPTKEYR = FLASH_OPTKEY1;   
    FLASH_OPTKEYR = FLASH_OPTKEY2;   
}

void FLASH_OptSet (uint32_t val) 
{
    while (FLASH_IsBusy())
        ;

    FLASH_OPTCR = val;
    FLASH_OPTCR |= FLASH_OPTCR_OPTSTRT;
    
    while (FLASH_IsBusy())
        ;
    
}

void FLASH_OptLock(void)
{
    FLASH_OPTCR |= FLASH_OPTCR_OPTLOCK;
}

void FLASH_Lock(void) 
{
    FLASH_CR |= FLASH_CR_LOCK;    
}

BOOL FLASH_IsLocked(void) 
{
    return (FLASH_CR & FLASH_CR_LOCK);    
}

void FLASH_SetPsize_x8(void)
{
    FLASH_CR |= FLASH_CR_PSIZEx8;
}

void FLASH_SetPsize_x16(void)
{
    FLASH_CR |= FLASH_CR_PSIZEx16;
}

void FLASH_SetPsize_x32(void)
{
    FLASH_CR |= FLASH_CR_PSIZEx32;
}

void FLASH_SetPsize_x64(void)
{
    FLASH_CR |= FLASH_CR_PSIZEx64;
}

BOOL FLASH_IsBusy() 
{
    return (FLASH_SR & FLASH_SR_BSY);    
}

static uint32_t GetStatus(void) 
{
    if (FLASH_SR & FLASH_SR_OPERR) 
    {
        return 1;
    }
    else if (FLASH_SR & FLASH_SR_WRPERR) 
    {
        return 2;
    }
    else if (FLASH_SR & FLASH_SR_PGAERR)
    {
        return 3;
    }
    else if (FLASH_SR & FLASH_SR_PGPERR) 
    {
        return 3;
    }
    else if (FLASH_SR & FLASH_SR_PGSERR) 
    {
        return 4;
    }
    else if (FLASH_SR & FLASH_SR_RDERR) 
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

int FLASH_EraseSector(uint8_t sector) 
{
    while (FLASH_IsBusy())
        ;


    FLASH_CR |= FLASH_CR_SER;

    FLASH_CR &= FLASH_CR_SNB_MASK;
    FLASH_CR |= (sector<<FLASH_CR_SNB_OFFSET & FLASH_CR_SNB_MASK);

    FLASH_CR |= FLASH_CR_STRT;

    while (FLASH_IsBusy())
        ;

    return GetStatus();
         
}

int FLASH_MassErase(void) 
{
    while (FLASH_IsBusy())
        ;

    FLASH_CR |= FLASH_CR_MER;

    FLASH_CR |= FLASH_CR_STRT;

    while (FLASH_IsBusy())
        ;

    //shouldn't even get this far on success
    return GetStatus();

}

int FLASH_WriteByte (uint32_t addr, uint8_t byte) 
{
    while (FLASH_IsBusy())
        ;

    FLASH_CR |= FLASH_CR_PG;

    *(volatile uint8_t *)addr = byte;

    while (FLASH_IsBusy())
        ;

    
    FLASH_CR &= ~FLASH_CR_PG;
    
    return GetStatus();

}

int FLASH_WriteHalfWord (uint32_t addr, uint16_t byte) 
{
    while (FLASH_IsBusy())
        ;

    FLASH_CR |= FLASH_CR_PG;

    *(volatile uint16_t *)addr = byte;

    while (FLASH_IsBusy())
        ;

    
    FLASH_CR &= ~FLASH_CR_PG;
    
    return GetStatus();
}

int FLASH_WriteWord (uint32_t addr, uint32_t byte) 
{
    while (FLASH_IsBusy())
        ;

    FLASH_CR |= FLASH_CR_PG;

    *(volatile uint32_t *)addr = byte;

    while (FLASH_IsBusy())
        ;

    
    FLASH_CR &= ~FLASH_CR_PG;
    
    return GetStatus();
}

int FLASH_WriteDoubleWord (uint32_t addr, uint64_t byte) 
{
    while (FLASH_IsBusy())
        ;

    FLASH_CR |= FLASH_CR_PG;

    *(volatile uint64_t *)addr = byte;

    while (FLASH_IsBusy())
        ;

    
    FLASH_CR &= ~FLASH_CR_PG;
    
    return GetStatus();
}



#ifdef __cplusplus
}
#endif
