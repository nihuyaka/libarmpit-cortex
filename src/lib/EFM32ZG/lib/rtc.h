#ifndef _RTC_H
#define _RTC_H

//RTC - Real Time Counter

#define RTC_BASE 0x40080000


#define RTC_CTRL      (*(volatile uint32_t*)(RTC_BASE + 0x000)) 
#define RTC_CNT       (*(volatile uint32_t*)(RTC_BASE + 0x004)) 
#define RTC_COMP0     (*(volatile uint32_t*)(RTC_BASE + 0x008)) 
#define RTC_COMP1     (*(volatile uint32_t*)(RTC_BASE + 0x00C)) 
#define RTC_IF        (*(volatile uint32_t*)(RTC_BASE + 0x010)) 
#define RTC_IFS       (*(volatile uint32_t*)(RTC_BASE + 0x014)) 
#define RTC_IFC       (*(volatile uint32_t*)(RTC_BASE + 0x018)) 
#define RTC_IEN       (*(volatile uint32_t*)(RTC_BASE + 0x01C)) 
#define RTC_FREEZE    (*(volatile uint32_t*)(RTC_BASE + 0x020)) 
#define RTC_SYNCBUSY  (*(volatile uint32_t*)(RTC_BASE + 0x024)) 



#define RTC_CTRL_EN        (1<<0)
#define RTC_CTRL_DEBUGRUN  (1<<1)
#define RTC_CTRL_COMP0TOP  (1<<2)

#define RTC_IF_OF     (1<<0)
#define RTC_IF_COMP0  (1<<1)
#define RTC_IF_COMP1  (1<<2)

#define RTC_IFS_OF     (1<<0)
#define RTC_IFS_COMP0  (1<<1)
#define RTC_IFS_COMP1  (1<<2)

#define RTC_IFC_OF     (1<<0)
#define RTC_IFC_COMP0  (1<<1)
#define RTC_IFC_COMP1  (1<<2)

#define RTC_IEN_OF     (1<<0)
#define RTC_IEN_COMP0  (1<<1)
#define RTC_IEN_COMP1  (1<<2)

#define RTC_FREEZE_REGFREEZE  (1<<0)

#define RTC_SYNCBUSY_CTRL  (1<<0)
#define RTC_SYNCBUSY_COMP0 (1<<1)
#define RTC_SYNCBUSY_COMP1 (1<<2)


#endif 
