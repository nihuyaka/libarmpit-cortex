#ifndef _PRS_H
#define _PRS_H

#define PRS_BASE  0x400CC000

#define PRS_SWPULSE   (*(volatile uint32_t*)(PRS_BASE + 0x0000)) 
#define PRS_SWLEVEL   (*(volatile uint32_t*)(PRS_BASE + 0x0004)) 
#define PRS_ROUTE     (*(volatile uint32_t*)(PRS_BASE + 0x0008)) 
#define PRS_CH0_CTRL  (*(volatile uint32_t*)(PRS_BASE + 0x0010)) 
#define PRS_CH1_CTRL  (*(volatile uint32_t*)(PRS_BASE + 0x0014)) 
#define PRS_CH2_CTRL  (*(volatile uint32_t*)(PRS_BASE + 0x0018)) 
#define PRS_CH3_CTRL  (*(volatile uint32_t*)(PRS_BASE + 0x001C)) 



#endif
