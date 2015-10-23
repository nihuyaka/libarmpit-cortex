#ifndef _FLASH_H
#define _FLASH_H

#include "common.h"

#define FLASH_BASE 0x08000000

#define FLASH_REG_BASE 0x40023C00

#define FLASH_ACR   (*(volatile uint32_t*)(FLASH_REG_BASE + 0x00))   


#define FLASH_ACR_LATENCY_OFFSET 0
#define FLASH_ACR_LATENCY_MASK (0xf < FLASH_ACR_LATENCY_OFFSET)
#define FLASH_ACR_PRFTEN (1<<8)
#define FLASH_ACR_ICEN   (1<<9)
#define FLASH_ACR_DCEN   (1<<10)
#define FLASH_ACR_ICRST  (1<<11)
#define FLASH_ACR_DCRST  (1<<12)



#define FLASH_KEYR   (*(volatile uint32_t*)(FLASH_REG_BASE + 0x04))   

#define FLASH_KEY1 0x45670123
#define FLASH_KEY2 0xCDEF89AB


#define FLASH_OPTKEYR   (*(volatile uint32_t*)(FLASH_REG_BASE + 0x08))   
#define FLASH_OPTKEY1 0x08192A3B
#define FLASH_OPTKEY2 0x4C5D6E7F


#define FLASH_SR   (*(volatile uint32_t*)(FLASH_REG_BASE + 0x0c))   
#define FLASH_SR_EOP    (1<<0)
#define FLASH_SR_OPERR  (1<<1)
#define FLASH_SR_WRPERR (1<<4)
#define FLASH_SR_PGAERR (1<<5)
#define FLASH_SR_PGPERR (1<<6)
#define FLASH_SR_PGSERR (1<<7)
#define FLASH_SR_RDERR  (1<<8)
#define FLASH_SR_BSY    (1<<16)


#define FLASH_CR   (*(volatile uint32_t*)(FLASH_REG_BASE + 0x10))   

#define FLASH_CR_PG   (1<<0)
#define FLASH_CR_SER  (1<<1)
#define FLASH_CR_MER  (1<<2)
#define FLASH_CR_SNB_OFFSET 3
#define FLASH_CR_SNB_MASK  (0xf<<FLASH_CR_SNB_OFFSET)
#define FLASH_CR_SNB_USER_SPECIFIC (12<<FLASH_CR_SNB_OFFSET)
#define FLASH_CR_SNB_USER_CONFIG (13<<FLASH_CR_SNB_OFFSET)

#define FLASH_CR_PSIZEx8   (0<<8)
#define FLASH_CR_PSIZEx16  (1<<8)
#define FLASH_CR_PSIZEx32  (2<<8)
#define FLASH_CR_PSIZEx64  (3<<8)
#define FLASH_CR_PSIZE_CLEARMASK (3<<8)

#define FLASH_CR_STRT   (1<<16)
#define FLASH_CR_EOPIE  (1<<24)
#define FLASH_CR_ERRIE  (1<<25)
#define FLASH_CR_LOCK   (1u<<31)



#define FLASH_OPTCR   (*(volatile uint32_t*)(FLASH_REG_BASE + 0x14))   

#define FLASH_OPTCR_OPTLOCK (1<<0)
#define FLASH_OPTCR_OPTSTRT (1<<1)
#define FLASH_OPTCR_BOR_LEV3 (0<<2)
#define FLASH_OPTCR_BOR_LEV2 (1<<2)
#define FLASH_OPTCR_BOR_LEV1 (2<<2)
#define FLASH_OPTCR_BOR_OFF (3<<2)
#define FLASH_OPTCR_BOR_CLEARMASK (3<<2)

#define FLASH_OPTCR_USER_WDG_SW     (1<<5)
#define FLASH_OPTCR_USER_nRST_STOP  (1<<6)
#define FLASH_OPTCR_USER_nRST_STDBY (1<<7)



#define FLASH_OPTCR_RDP_OFFSET 8
#define FLASH_OPTCR_RDP_OFF 0xAA 
#define FLASH_OPTCR_RDP_CHIP 0xCC 
#define FLASH_OPTCR_RDP_MEM 0x00
#define FLASH_OPTCR_RDP_MASK  (0xff<<FLASH_OPTCR_RDP_OFFSET)


#define FLASH_OPTCR_nWRP_SECTOR0 (1<<16)
#define FLASH_OPTCR_nWRP_MASK    (0xFFF<<16)
#define FLASH_OPTCR_SPRMOD       (1<<31)


#ifdef __cplusplus
extern "C"
{
#endif


void FLASH_SetWaitState(uint8_t wait_state);
void FLASH_EnableICache();
void FLASH_EnableDCache();
void FLASH_EnablePrefetchBuffer();

void FLASH_Unlock(void);
void FLASH_Lock(void);
BOOL FLASH_IsLocked(void);
void FLASH_OptUnlock(void);
void FLASH_OptLock(void);
void FLASH_OptSet (uint32_t val); 
    
void FLASH_SetPsize_x8(void);
void FLASH_SetPsize_x16(void);
void FLASH_SetPsize_x32(void);
void FLASH_SetPsize_x64(void);
BOOL FLASH_IsBusy(void);  

int FLASH_WriteByte (uint32_t addr, uint8_t byte);
int FLASH_WriteHalfWord (uint32_t addr, uint16_t byte);
int FLASH_WriteWord (uint32_t addr, uint32_t byte);
int FLASH_WriteDoubleWord (uint32_t addr, uint64_t byte);   

int FLASH_MassErase(void);
int FLASH_EraseSector(uint8_t sector);


#ifdef __cplusplus
}
#endif



#endif
