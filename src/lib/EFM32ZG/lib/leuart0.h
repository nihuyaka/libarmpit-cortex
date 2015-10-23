#ifndef _LEUART0_H
#define _LEUART0_H


#define LEUART0_BASE  0x40084000

#define LEUARTn_CTRL        (*(volatile uint32_t*)(LEUART0_BASE + 0x000)) 
#define LEUARTn_CMD         (*(volatile uint32_t*)(LEUART0_BASE + 0x004)) 
#define LEUARTn_STATUS      (*(volatile uint32_t*)(LEUART0_BASE + 0x008)) 
#define LEUARTn_CLKDIV      (*(volatile uint32_t*)(LEUART0_BASE + 0x00C)) 
#define LEUARTn_STARTFRAM   (*(volatile uint32_t*)(LEUART0_BASE + 0x010)) 
#define LEUARTn_SIGFRAME    (*(volatile uint32_t*)(LEUART0_BASE + 0x014)) 
#define LEUARTn_RXDATAX     (*(volatile uint32_t*)(LEUART0_BASE + 0x018)) 
#define LEUARTn_RXDATA      (*(volatile uint32_t*)(LEUART0_BASE + 0x01C)) 
#define LEUARTn_RXDATAXP    (*(volatile uint32_t*)(LEUART0_BASE + 0x020)) 
#define LEUARTn_TXDATAX     (*(volatile uint32_t*)(LEUART0_BASE + 0x024)) 
#define LEUARTn_TXDATA      (*(volatile uint32_t*)(LEUART0_BASE + 0x028)) 
#define LEUARTn_IF          (*(volatile uint32_t*)(LEUART0_BASE + 0x02C)) 
#define LEUARTn_IFS         (*(volatile uint32_t*)(LEUART0_BASE + 0x030)) 
#define LEUARTn_IFC         (*(volatile uint32_t*)(LEUART0_BASE + 0x034)) 
#define LEUARTn_IEN         (*(volatile uint32_t*)(LEUART0_BASE + 0x038)) 
#define LEUARTn_PULSECTRL   (*(volatile uint32_t*)(LEUART0_BASE + 0x03C)) 
#define LEUARTn_FREEZE      (*(volatile uint32_t*)(LEUART0_BASE + 0x040)) 
#define LEUARTn_SYNCBUSY    (*(volatile uint32_t*)(LEUART0_BASE + 0x044)) 
#define LEUARTn_ROUTE       (*(volatile uint32_t*)(LEUART0_BASE + 0x054)) 
#define LEUARTn_INPUT       (*(volatile uint32_t*)(LEUART0_BASE + 0x0AC)) 


#endif




