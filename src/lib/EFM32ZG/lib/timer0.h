#ifndef _TIMER0_H
#define _TIMER0_H

#define TIMER0_BASE 0x40006000


#define TIMERn_CTRL        (*(volatile uint32_t*)(TIMER0_BASE + 0x000)) 
#define TIMERn_CMD         (*(volatile uint32_t*)(TIMER0_BASE + 0x004)) 
#define TIMERn_STATUS      (*(volatile uint32_t*)(TIMER0_BASE + 0x008)) 
#define TIMERn_IEN         (*(volatile uint32_t*)(TIMER0_BASE + 0x00C)) 
#define TIMERn_IF          (*(volatile uint32_t*)(TIMER0_BASE + 0x010)) 
#define TIMERn_IFS         (*(volatile uint32_t*)(TIMER0_BASE + 0x014)) 
#define TIMERn_IFC         (*(volatile uint32_t*)(TIMER0_BASE + 0x018)) 
#define TIMERn_TOP         (*(volatile uint32_t*)(TIMER0_BASE + 0x01C)) 
#define TIMERn_TOPB        (*(volatile uint32_t*)(TIMER0_BASE + 0x020)) 
#define TIMERn_CNT         (*(volatile uint32_t*)(TIMER0_BASE + 0x024)) 
#define TIMERn_ROUTE       (*(volatile uint32_t*)(TIMER0_BASE + 0x028)) 
#define TIMERn_CC0_CTRL    (*(volatile uint32_t*)(TIMER0_BASE + 0x030)) 
#define TIMERn_CC0_CCV     (*(volatile uint32_t*)(TIMER0_BASE + 0x034)) 
#define TIMERn_CC0_CCVP    (*(volatile uint32_t*)(TIMER0_BASE + 0x038)) 
#define TIMERn_CC0_CCVB    (*(volatile uint32_t*)(TIMER0_BASE + 0x03C)) 
#define TIMERn_CC1_CTRL    (*(volatile uint32_t*)(TIMER0_BASE + 0x040)) 
#define TIMERn_CC1_CCV     (*(volatile uint32_t*)(TIMER0_BASE + 0x044)) 
#define TIMERn_CC1_CCVP    (*(volatile uint32_t*)(TIMER0_BASE + 0x048)) 
#define TIMERn_CC1_CCVB    (*(volatile uint32_t*)(TIMER0_BASE + 0x04C)) 
#define TIMERn_CC2_CTRL    (*(volatile uint32_t*)(TIMER0_BASE + 0x050)) 
#define TIMERn_CC2_CCV     (*(volatile uint32_t*)(TIMER0_BASE + 0x054)) 
#define TIMERn_CC2_CCVP    (*(volatile uint32_t*)(TIMER0_BASE + 0x058)) 
#define TIMERn_CC2_CCVB    (*(volatile uint32_t*)(TIMER0_BASE + 0x05C)) 


#define TIMERn_CTRL_MODE_UP      0
#define TIMERn_CTRL_MODE_DOWN    1
#define TIMERn_CTRL_MODE_UPDOWN  2
#define TIMERn_CTRL_MODE_QDEC    3
#define TIMERn_CTRL_MODE_CLEAR   3

#define TIMERn_CTRL_SYNC      (1<<3)
#define TIMERn_CTRL_OSMEN     (1<<4)
#define TIMERn_CTRL_QDM       (1<<5)
#define TIMERn_CTRL_DEBUGRUN  (1<<6)
#define TIMERn_CTRL_DMACLRACT (1<<7)

#define TIMERn_CTRL_RISEA_NONE        (0<<8)
#define TIMERn_CTRL_RISEA_START       (1<<8)
#define TIMERn_CTRL_RISEA_STOP        (2<<8)
#define TIMERn_CTRL_RISEA_RELOADSTART (3<<8)
#define TIMERn_CTRL_RISEA_CLEAR       (3<<8)

#define TIMERn_CTRL_FALLA_NONE        (0<<10)
#define TIMERn_CTRL_FALLA_START       (1<<10)
#define TIMERn_CTRL_FALLA_STOP        (2<<10)
#define TIMERn_CTRL_FALLA_RELOADSTART (3<<10)
#define TIMERn_CTRL_FALLA_CLEAR       (3<<10)

#define TIMERn_CTRL_X2CNT (1<<13)

#define TIMERn_CTRL_CLKSEL_PRESCHFPERCLK  (0<<16)
#define TIMERn_CTRL_CLKSEL_CC1            (1<<16)
#define TIMERn_CTRL_CLKSEL_TIMEROUF       (2<<16)
#define TIMERn_CTRL_CLKSEL_CLEAR          (3<<16)

#define TIMERn_CTRL_PRESC_DIV1      (0<<24)
#define TIMERn_CTRL_PRESC_DIV2      (1<<24)
#define TIMERn_CTRL_PRESC_DIV4      (2<<24)
#define TIMERn_CTRL_PRESC_DIV8      (3<<24)
#define TIMERn_CTRL_PRESC_DIV16     (4<<24)
#define TIMERn_CTRL_PRESC_DIV32     (5<<24)
#define TIMERn_CTRL_PRESC_DIV64     (6<<24)
#define TIMERn_CTRL_PRESC_DIV128    (7<<24)
#define TIMERn_CTRL_PRESC_DIV256    (8<<24)
#define TIMERn_CTRL_PRESC_DIV512    (9<<24)
#define TIMERn_CTRL_PRESC_DIV1024   (10<<24)

#define TIMERn_CTRL_ATI             (1<<28) 
#define TIMERn_CTRL_RSSCOIST        (1<<29)

#define TIMERn_CMD_STOP   (1<<0)
#define TIMERn_CMD_START  (1<<1)


#define TIMERn_STATUS_RUNNING     (1<<0)
#define TIMERn_STATUS_DIR         (1<<1)
#define TIMERn_STATUS_TOPBV       (1<<2)
#define TIMERn_STATUS_CCVBV0      (1<<8)
#define TIMERn_STATUS_CCVBV1      (1<<9)
#define TIMERn_STATUS_CCVBV2      (1<<10)
#define TIMERn_STATUS_ICV0        (1<<16)
#define TIMERn_STATUS_ICV1        (1<<17)
#define TIMERn_STATUS_ICV2        (1<<18)
#define TIMERn_STATUS_CCPOL0      (1<<24)
#define TIMERn_STATUS_CCPOL1      (1<<25)
#define TIMERn_STATUS_CCPOL2      (1<<26)


#define TIMERn_IEN_OF  (1<<0)
#define TIMERn_IEN_UF  (1<<1)
#define TIMERn_IEN_CC0  (1<<4)
#define TIMERn_IEN_CC1  (1<<5)
#define TIMERn_IEN_CC2  (1<<6)
#define TIMERn_IEN_ICBOF0  (1<<8)
#define TIMERn_IEN_ICBOF1  (1<<9)
#define TIMERn_IEN_ICBOF2  (1<<10)

#define TIMERn_IF_OF  (1<<0)
#define TIMERn_IF_UF  (1<<1)
#define TIMERn_IF_CC0  (1<<4)
#define TIMERn_IF_CC1  (1<<5)
#define TIMERn_IF_CC2  (1<<6)
#define TIMERn_IF_ICBOF0  (1<<8)
#define TIMERn_IF_ICBOF1  (1<<9)
#define TIMERn_IF_ICBOF2  (1<<10)

#define TIMERn_IFS_OF  (1<<0)
#define TIMERn_IFS_UF  (1<<1)
#define TIMERn_IFS_CC0  (1<<4)
#define TIMERn_IFS_CC1  (1<<5)
#define TIMERn_IFS_CC2  (1<<6)
#define TIMERn_IFS_ICBOF0  (1<<8)
#define TIMERn_IFS_ICBOF1  (1<<9)
#define TIMERn_IFS_ICBOF2  (1<<10)

#define TIMERn_IFC_OF  (1<<0)
#define TIMERn_IFC_UF  (1<<1)
#define TIMERn_IFC_CC0  (1<<4)
#define TIMERn_IFC_CC1  (1<<5)
#define TIMERn_IFC_CC2  (1<<6)
#define TIMERn_IFC_ICBOF0  (1<<8)
#define TIMERn_IFC_ICBOF1  (1<<9)
#define TIMERn_IFC_ICBOF2  (1<<10)


#define TIMERn_ROUTE_CC0PEN (1<<0) 
#define TIMERn_ROUTE_CC1PEN (1<<1) 
#define TIMERn_ROUTE_CC2PEN (1<<2) 

#define TIMERn_ROUTE_LOC0  (0<<16)
#define TIMERn_ROUTE_LOC1  (1<<16)
#define TIMERn_ROUTE_LOC2  (2<<16)
#define TIMERn_ROUTE_LOC3  (3<<16)
#define TIMERn_ROUTE_LOC4  (4<<16)
#define TIMERn_ROUTE_LOC5  (5<<16)
#define TIMERn_ROUTE_CLEAR (7<<16)

#define TIMERn_CCx_CTRL_MODE_OFF            (0<<0)
#define TIMERn_CCx_CTRL_MODE_INPUTCAPTURE   (1<<0)
#define TIMERn_CCx_CTRL_MODE_OUTPUTCOMPARE  (2<<0)
#define TIMERn_CCx_CTRL_MODE_PWM            (3<<0)
#define TIMERn_CCx_CTRL_MODE_CLEAR          (3<<0)

#define TIMERn_CCx_CTRL_OUTINV (1<<2)
#define TIMERn_CCx_CTRL_COIST  (1<<4)


#define TIMERn_CCx_CTRL_CMOA_NONE       (0<<8)
#define TIMERn_CCx_CTRL_CMOA_TOGGLE     (1<<8)
#define TIMERn_CCx_CTRL_CMOA_CLEAR      (2<<8)
#define TIMERn_CCx_CTRL_CMOA_SET        (3<<8)
#define TIMERn_CCx_CTRL_CMOA_CLEARMASK  (3<<8)

#define TIMERn_CCx_CTRL_COFOA_NONE       (0<<10)
#define TIMERn_CCx_CTRL_COFOA_TOGGLE     (1<<10)
#define TIMERn_CCx_CTRL_COFOA_CLEAR      (2<<10)
#define TIMERn_CCx_CTRL_COFOA_SET        (3<<10)
#define TIMERn_CCx_CTRL_COFOA_CLEARMASK  (3<<10)


#define TIMERn_CCx_CTRL_CUFOA_NONE       (0<<12)
#define TIMERn_CCx_CTRL_CUFOA_TOGGLE     (1<<12)
#define TIMERn_CCx_CTRL_CUFOA_CLEAR      (2<<12)
#define TIMERn_CCx_CTRL_CUFOA_SET        (3<<12)
#define TIMERn_CCx_CTRL_CUFOA_CLEARMASK  (3<<12)


#define TIMERn_CCx_CTRL_PRSSEL_PRSCH0     (0<<16)
#define TIMERn_CCx_CTRL_PRSSEL_PRSCH1     (1<<16)
#define TIMERn_CCx_CTRL_PRSSEL_PRSCH2     (2<<16)
#define TIMERn_CCx_CTRL_PRSSEL_PRSCH3     (3<<16)
#define TIMERn_CCx_CTRL_PRSSEL_CLEARMASK  (3<<16)

#define TIMERn_CCx_CTRL_INSEL_PIN         (0<<20)
#define TIMERn_CCx_CTRL_INSEL_PRS         (1<<20)
#define TIMERn_CCx_CTRL_INSEL_CLEARMASK   (1<<20)


#define TIMERn_CCx_CTRL_FILT              (1<<21)

#define TIMERn_CCx_CTRL_ICEDGE_RISING          (0<<24)
#define TIMERn_CCx_CTRL_ICEDGE_FALLING         (1<<24)
#define TIMERn_CCx_CTRL_ICEDGE_BOTH            (2<<24)
#define TIMERn_CCx_CTRL_ICEDGE_NONE            (3<<24)
#define TIMERn_CCx_CTRL_ICEDGE_CLEARMASK       (3<<24)


#define TIMERn_CCx_CTRL_ICEVCTRL_EVERYEDGE          (0<<26)
#define TIMERn_CCx_CTRL_ICEVCTRL_EVERYSECONDEDGE    (1<<26)
#define TIMERn_CCx_CTRL_ICEVCTRL_RISING             (2<<26)
#define TIMERn_CCx_CTRL_ICEVCTRL_FALLING            (3<<26)
#define TIMERn_CCx_CTRL_ICEVCTRL_CLEARMASK          (3<<26)


#define TIMERn_CCx_CTRL_PRSCONF_PULSE       (0<<28)
#define TIMERn_CCx_CTRL_PRSCONF_LEVEL       (1<<28)
#define TIMERn_CCx_CTRL_PRSCONF_CLEARMASK   (1<<28)




#endif
