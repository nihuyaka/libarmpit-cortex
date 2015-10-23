#ifndef _DMA_H
#define _DMA_H

#define DMA_BASE 0x400C2000

#define DMA_STATUS        (*(volatile uint32_t*)(DMA_BASE + 0x000))  
#define DMA_CONFIG        (*(volatile uint32_t*)(DMA_BASE + 0x004)) 
#define DMA_CTRLBASE      (*(volatile uint32_t*)(DMA_BASE + 0x008)) 
#define DMA_ALTCTRLBASE   (*(volatile uint32_t*)(DMA_BASE + 0x00C)) 
#define DMA_CHWAITSTATUS  (*(volatile uint32_t*)(DMA_BASE + 0x010)) 
#define DMA_CHSWREQ       (*(volatile uint32_t*)(DMA_BASE + 0x014)) 
#define DMA_CHUSEBURSTS   (*(volatile uint32_t*)(DMA_BASE + 0x018)) 
#define DMA_CHUSEBURSTC   (*(volatile uint32_t*)(DMA_BASE + 0x01C)) 
#define DMA_CHREQMASKS    (*(volatile uint32_t*)(DMA_BASE + 0x020)) 
#define DMA_CHREQMASKC    (*(volatile uint32_t*)(DMA_BASE + 0x024)) 
#define DMA_CHENS         (*(volatile uint32_t*)(DMA_BASE + 0x028)) 
#define DMA_CHENC         (*(volatile uint32_t*)(DMA_BASE + 0x02C)) 
#define DMA_CHALTS        (*(volatile uint32_t*)(DMA_BASE + 0x030)) 
#define DMA_CHALTC        (*(volatile uint32_t*)(DMA_BASE + 0x034)) 
#define DMA_CHPRIS        (*(volatile uint32_t*)(DMA_BASE + 0x038)) 
#define DMA_CHPRIC        (*(volatile uint32_t*)(DMA_BASE + 0x03C)) 
#define DMA_ERRORC        (*(volatile uint32_t*)(DMA_BASE + 0x04C)) 
#define DMA_CHREQSTATUS   (*(volatile uint32_t*)(DMA_BASE + 0xE10)) 
#define DMA_CHSREQSTATUS  (*(volatile uint32_t*)(DMA_BASE + 0xE18)) 
#define DMA_IF            (*(volatile uint32_t*)(DMA_BASE + 0x1000))
#define DMA_IFS           (*(volatile uint32_t*)(DMA_BASE + 0x1004))
#define DMA_IFC           (*(volatile uint32_t*)(DMA_BASE + 0x1008))
#define DMA_IEN           (*(volatile uint32_t*)(DMA_BASE + 0x100C))
#define DMA_CH0_CTRL      (*(volatile uint32_t*)(DMA_BASE + 0x1100))
#define DMA_CH1_CTRL      (*(volatile uint32_t*)(DMA_BASE + 0x1104))
#define DMA_CH2_CTRL      (*(volatile uint32_t*)(DMA_BASE + 0x1108))
#define DMA_CH3_CTRL      (*(volatile uint32_t*)(DMA_BASE + 0x110C))


#endif
