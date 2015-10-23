#ifndef _RMU_H
#define _RMU_H


//RMU - Reset Management Unit 


#define RMU_BASE 0x400ca000


#define RMU_CTRL      (*(volatile uint32_t*)(RMU_BASE + 0x00)) 
#define RMU_RSTCAUSE  (*(volatile uint32_t*)(RMU_BASE + 0x04)) 
#define RMU_CMD       (*(volatile uint32_t*)(RMU_BASE + 0x08)) 


#define RMU_CTRL_LOCKUPRDIS (1<<0) 

#define RMU_RSTCAUSE_PORST       (1<<0)
#define RMU_RSTCAUSE_BODUNREGRST (1<<1)
#define RMU_RSTCAUSE_BODREGRST   (1<<2)
#define RMU_RSTCAUSE_EXTRST      (1<<3)
#define RMU_RSTCAUSE_WDOGRST     (1<<4)
#define RMU_RSTCAUSE_LOCKUPRST   (1<<5)
#define RMU_RSTCAUSE_SYSREQRST   (1<<6)
#define RMU_RSTCAUSE_EM4RST      (1<<7)
#define RMU_RSTCAUSE_EM4WURST    (1<<8)
#define RMU_RSTCAUSE_BODAVDD0    (1<<9)
#define RMU_RSTCAUSE_BODAVDD1    (1<<10)

#define RMU_CMD_RCCLR  (1<<0)

#endif