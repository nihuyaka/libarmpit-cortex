#ifndef _USART1_H
#define _USART1_H

#define USART1_BASE 0x4000C400

#define USARTn_CTRL       (*(volatile uint32_t*)(USART1_BASE + 0x000)) 
#define USARTn_FRAME      (*(volatile uint32_t*)(USART1_BASE + 0x004)) 
#define USARTn_TRIGCTRL   (*(volatile uint32_t*)(USART1_BASE + 0x008)) 
#define USARTn_CMD        (*(volatile uint32_t*)(USART1_BASE + 0x00C)) 
#define USARTn_STATUS     (*(volatile uint32_t*)(USART1_BASE + 0x010)) 
#define USARTn_CLKDIV     (*(volatile uint32_t*)(USART1_BASE + 0x014)) 
#define USARTn_RXDATAX    (*(volatile uint32_t*)(USART1_BASE + 0x018)) 
#define USARTn_RXDATA     (*(volatile uint32_t*)(USART1_BASE + 0x01C)) 
#define USARTn_RXDOUBLEX  (*(volatile uint32_t*)(USART1_BASE + 0x020)) 
#define USARTn_RXDOUBLE   (*(volatile uint32_t*)(USART1_BASE + 0x024)) 
#define USARTn_RXDATAXP   (*(volatile uint32_t*)(USART1_BASE + 0x028)) 
#define USARTn_RXDOUBLEXP (*(volatile uint32_t*)(USART1_BASE + 0x02C)) 
#define USARTn_TXDATAX    (*(volatile uint32_t*)(USART1_BASE + 0x030)) 
#define USARTn_TXDATA     (*(volatile uint32_t*)(USART1_BASE + 0x034)) 
#define USARTn_TXDOUBLEX  (*(volatile uint32_t*)(USART1_BASE + 0x038)) 
#define USARTn_TXDOUBLE   (*(volatile uint32_t*)(USART1_BASE + 0x03C)) 
#define USARTn_IF         (*(volatile uint32_t*)(USART1_BASE + 0x040)) 
#define USARTn_IFS        (*(volatile uint32_t*)(USART1_BASE + 0x044)) 
#define USARTn_IFC        (*(volatile uint32_t*)(USART1_BASE + 0x048)) 
#define USARTn_IEN        (*(volatile uint32_t*)(USART1_BASE + 0x04C)) 
#define USARTn_IRCTRL     (*(volatile uint32_t*)(USART1_BASE + 0x050)) 
#define USARTn_ROUTE      (*(volatile uint32_t*)(USART1_BASE + 0x054)) 
#define USARTn_INPUT      (*(volatile uint32_t*)(USART1_BASE + 0x058)) 
#define USARTn_I2SCTRL    (*(volatile uint32_t*)(USART1_BASE + 0x05C)) 


#endif