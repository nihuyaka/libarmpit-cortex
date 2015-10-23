#ifndef _EMU_H 
#define _EMU_H 


#define EMU_BASE 0x400c6000


#define EMU_CTRL    (*(volatile uint32_t*)(EMU_BASE + 0x00)) 
#define EMU_LOCK    (*(volatile uint32_t*)(EMU_BASE + 0x08)) 
#define EMU_AUXCTRL (*(volatile uint32_t*)(EMU_BASE + 0x24)) 


//EMU - Energy Management Unit 

#define EMU_CTRL_EMVREG  (1<<0)  //0: reduced 1: full
#define EMU_CTRL_EM2BLOCK  (1<<1) 
#define EMU_CTRL_EM4CTRL_OFFSET 2

#define EMU_LOCK_UNLOCKED     (1<<0)
#define EMU_LOCK_UNLOCK_CODE  0xADE8

#define EMU_AUXCTRL_HRCCLR  (1<<0)


void EMU_EnterEM1(void);
void EMU_EnterEM2(void);
void EMU_EnterEM3(void);
void EMU_EnterEM4(void);



#endif 
