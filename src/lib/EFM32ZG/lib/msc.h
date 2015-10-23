#ifndef _MSC_H
#define _MSC_H

#include "common.h"

#define MSC_BASE 0x400C0000

#define MSC_CTRL          (*(volatile uint32_t*)(MSC_BASE + 0x000))

#define MSC_CTRL_IGNORE  (1<<0) 



#define MSC_READCTRL      (*(volatile uint32_t*)(MSC_BASE + 0x004))
#define MSC_READCTRL_MODE     (1<<0)
#define MSC_READCTRL_IFCDIS   (1<<3)
#define MSC_READCTRL_AIDIS    (1<<4)
#define MSC_READCTRL_RAMCEN   (1<<7)


#define MSC_WRITECTRL     (*(volatile uint32_t*)(MSC_BASE + 0x008))

#define MSC_WRITECTRL_WREN           (1<<0)
#define MSC_WRITECTRL_IRQERASEABORT  (1<<1)


#define MSC_WRITECMD      (*(volatile uint32_t*)(MSC_BASE + 0x00C))

#define MSC_WRITECMD_LADDRIM     (1<<0)
#define MSC_WRITECMD_ERASEPAGE   (1<<1)
#define MSC_WRITECMD_WRITEEND    (1<<2)
#define MSC_WRITECMD_WRITEONCE   (1<<3)
#define MSC_WRITECMD_WRITETRIG   (1<<4)
#define MSC_WRITECMD_ERASEABORT  (1<<5)
#define MSC_WRITECMD_ERASEMAIN0  (1<<8)
#define MSC_WRITECMD_CLEARWDATA  (1<<12)



#define MSC_ADDRB         (*(volatile uint32_t*)(MSC_BASE + 0x010))
#define MSC_WDATA         (*(volatile uint32_t*)(MSC_BASE + 0x018))
#define MSC_STATUS        (*(volatile uint32_t*)(MSC_BASE + 0x01C))

#define MSC_STATUS_BUSY         (1<<0)
#define MSC_STATUS_LOCKED       (1<<1)
#define MSC_STATUS_INVADDR      (1<<2)
#define MSC_STATUS_WDATAREADY   (1<<3)
#define MSC_STATUS_WORDTIMEOUT  (1<<4)
#define MSC_STATUS_ERASEABORTED (1<<5)
#define MSC_STATUS_PCRUNNING    (1<<6)


#define MSC_IF            (*(volatile uint32_t*)(MSC_BASE + 0x02C))

#define MSC_IF_ERASE  (1<<0)
#define MSC_IF_WRITE  (1<<1)
#define MSC_IF_CHOF  (1<<2)
#define MSC_IF_CMOF  (1<<3)

#define MSC_IFS           (*(volatile uint32_t*)(MSC_BASE + 0x030))

#define MSC_IFS_ERASE  (1<<0)
#define MSC_IFS_WRITE  (1<<1)
#define MSC_IFS_CHOF  (1<<2)
#define MSC_IFS_CMOF  (1<<3)


#define MSC_IFC           (*(volatile uint32_t*)(MSC_BASE + 0x034))

#define MSC_IFC_ERASE  (1<<0)
#define MSC_IFC_WRITE  (1<<1)
#define MSC_IFC_CHOF  (1<<2)
#define MSC_IFC_CMOF  (1<<3)

#define MSC_IEN           (*(volatile uint32_t*)(MSC_BASE + 0x038))


#define MSC_IEN_ERASE  (1<<0)
#define MSC_IEN_WRITE  (1<<1)
#define MSC_IEN_CHOF  (1<<2)
#define MSC_IEN_CMOF  (1<<3)


#define MSC_LOCK          (*(volatile uint32_t*)(MSC_BASE + 0x03C))

#define MSC_LOCKKEY 0x1B71

#define MSC_CMD           (*(volatile uint32_t*)(MSC_BASE + 0x040))


#define MSC_CACHEHITS     (*(volatile uint32_t*)(MSC_BASE + 0x044))
#define MSC_CACHEMISSES   (*(volatile uint32_t*)(MSC_BASE + 0x048))
#define MSC_TIMEBASE      (*(volatile uint32_t*)(MSC_BASE + 0x050))


#define MSC_TIMEBASE_1US  (1<<0)
#define MSC_TIMEBASE_5US  (1<<1) //5 us should only be used with 1 MHz AUXHFRCO band
#define MSC_TIMEBASE_CLEARMASK  (1<<1)


#define MSC_MASSLOCK      (*(volatile uint32_t*)(MSC_BASE + 0x054))

#define MSC_MASSLOCK_LOCKKEY  0x631A

#define MSC_IRQLATENCY    (*(volatile uint32_t*)(MSC_BASE + 0x058))


void FLASH_SetWaitState(uint8_t wait_state);
void FLASH_EnableIFlashCache (BOOL enable);
void FLASH_EnableAutomaticInvalidate (BOOL enable);
void FLASH_EnableRAMCache (BOOL enable);

void FLASH_EnableWriteEraseController (BOOL enable);

#endif
