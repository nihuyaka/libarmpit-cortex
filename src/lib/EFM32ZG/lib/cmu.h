#ifndef CMU_H
#define CMU_H

#include "common.h"


// 1-21 MHz High Frequency RC Oscillator (HFRCO)
// 4-24 MHz High Frequency Crystal Oscillator (HFXO)
// 32768 Hz Low Frequency RC Oscillator (LFRCO)
// 32768 Hz Low Frequency Crystal Oscillator (LFXO)
// 1000 Hz Ultra Low Frequency RC Oscillator (ULFRCO)


#define CMU_BASE 0x400c8000

#define CMU_CTRL           (*(volatile uint32_t*)(CMU_BASE + 0x000)) 
	

//External HF clock
#define CMU_CTRL_HFXOMODE_XTAL        (0<<0) //4-24 MHz crystal oscillator
#define CMU_CTRL_HFXOMODE_BUFEXTCLK   (1<<0) //External sine wave
#define CMU_CTRL_HFXOMODE_DIGEXTCLK   (2<<0) //Digital external clock on HFXTAL_N pin. Oscillator is effectively bypassed.
#define CMU_CTRL_HFXOMODE_CLEARMASK       (3<<0)

#define CMU_CTRL_HFXOBOOST_50PCENT    (0<<2)
#define CMU_CTRL_HFXOBOOST_70PCENT    (1<<2)
#define CMU_CTRL_HFXOBOOST_80PCENT    (2<<2)
#define CMU_CTRL_HFXOBOOST_100PCENT   (3<<2)
#define CMU_CTRL_HFXOBOOST_CLEAR      (3<<2)

#define CMU_CTRL_HFXOBUFCUR (3<<5) 
#define CMU_CTRL_HFXOGLITCHDETEN  (1<<7)

#define CMU_CTRL_HFXOTIMEOUT_8CYCLES (0<<9)   
#define CMU_CTRL_HFXOTIMEOUT_256CYCLES (1<<9)   
#define CMU_CTRL_HFXOTIMEOUT_1KCYCLES (2<<9)   
#define CMU_CTRL_HFXOTIMEOUT_16KCYCLES (3<<9)   
#define CMU_CTRL_HFXOTIMEOUT_CLEARMASK  (3<<9)

//External  source  for  the  LFXO
#define CMU_CTRL_LFXOMODE_XTAL      (0<<11)  //32.768 kHz crystal oscillator
#define CMU_CTRL_LFXOMODE_BUFEXTCLK (1<<11)  //sine wave
#define CMU_CTRL_LFXOMODE_DIGEXTCLK (2<<11)  //Digital external clock on LFXTAL_N pin. Oscillator is effectively bypassed
#define CMU_CTRL_LFXOMODE_CLEARMASK     (3<<11)

#define CMU_CTRL_LFXOBOOST (1<<13) 

#define CMU_CTRL_LFXOBUFCUR  (1<<17) 

#define CMU_CTRL_LFXOTIMEOUT_8CYCLES    (0<<18)
#define CMU_CTRL_LFXOTIMEOUT_1KCYCLES   (1<<18)
#define CMU_CTRL_LFXOTIMEOUT_16KCYCLES  (2<<18)
#define CMU_CTRL_LFXOTIMEOUT_32KCYCLES  (3<<18)
#define CMU_CTRL_LFXOTIMEOUT_CLEARMASK      (3<<18)

//Controls the clock output multiplexer.
//To actually output on the pin, set CLKOUT0PEN in CMU_ROUTE
#define CMU_CTRL_CLKOUTSEL0_HFRCO       (0<<20)  
#define CMU_CTRL_CLKOUTSEL0_HFXO        (1<<20)  
#define CMU_CTRL_CLKOUTSEL0_HFCLK2      (2<<20)  
#define CMU_CTRL_CLKOUTSEL0_HFCLK4      (3<<20)  
#define CMU_CTRL_CLKOUTSEL0_HFCLK8      (4<<20)  
#define CMU_CTRL_CLKOUTSEL0_HFCLK16     (5<<20)  
#define CMU_CTRL_CLKOUTSEL0_ULFRCO      (6<<20)  
#define CMU_CTRL_CLKOUTSEL0_AUXHFRCO    (7<<20)  
#define CMU_CTRL_CLKOUTSEL0_CLEAR       (7<<20)  

#define CMU_CTRL_CLKOUTSEL1_LFRCO      (0<<23)  
#define CMU_CTRL_CLKOUTSEL1_LFXO       (1<<23)  
#define CMU_CTRL_CLKOUTSEL1_HFCLK      (2<<23)  
#define CMU_CTRL_CLKOUTSEL1_LFXOQ      (3<<23)  
#define CMU_CTRL_CLKOUTSEL1_HFXOQ      (4<<23)  
#define CMU_CTRL_CLKOUTSEL1_LFRCOQ     (5<<23)  
#define CMU_CTRL_CLKOUTSEL1_HFRCOQ     (6<<23)  
#define CMU_CTRL_CLKOUTSEL1_AUXHFRCOQ  (7<<23)  
#define CMU_CTRL_CLKOUTSEL1_CLEAR      (7<<23)  

#define CMU_HFCORECLKDIV   (*(volatile uint32_t*)(CMU_BASE + 0x004)) 
// High Frequency Core Clock Division Register

#define CMU_HFCORECLKDIV_HFCLK1          (0<<0)
#define CMU_HFCORECLKDIV_HFCLK2         (1<<0)
#define CMU_HFCORECLKDIV_HFCLK4         (2<<0)
#define CMU_HFCORECLKDIV_HFCLK8         (3<<0)
#define CMU_HFCORECLKDIV_HFCLK16        (4<<0)
#define CMU_HFCORECLKDIV_HFCLK32        (5<<0)
#define CMU_HFCORECLKDIV_HFCLK64        (6<<0)
#define CMU_HFCORECLKDIV_HFCLK128       (7<<0)
#define CMU_HFCORECLKDIV_HFCLK256       (8<<0)
#define CMU_HFCORECLKDIV_HFCLK512       (9<<0)
#define CMU_HFCORECLKDIV_CLEARMASK      (9<<0)

#define CMU_HFCORECLKDIVLE_DIV2          (0<<8)
#define CMU_HFCORECLKDIVLE_DIV4          (1<<8)
#define CMU_HFCORECLKDIVLE_CLEARMASK (1<<8)
	

#define CMU_HFPERCLKDIV    (*(volatile uint32_t*)(CMU_BASE + 0x008)) 
	
//  High Frequency Peripheral Clock Division Register
#define CMU_HFPERCLKDIV_HFCLK1          (0<<0)
#define CMU_HFPERCLKDIV_HFCLK2         (1<<0)
#define CMU_HFPERCLKDIV_HFCLK4         (2<<0)
#define CMU_HFPERCLKDIV_HFCLK8         (3<<0)
#define CMU_HFPERCLKDIV_HFCLK16        (4<<0)
#define CMU_HFPERCLKDIV_HFCLK32        (5<<0)
#define CMU_HFPERCLKDIV_HFCLK64        (6<<0)
#define CMU_HFPERCLKDIV_HFCLK128       (7<<0)
#define CMU_HFPERCLKDIV_HFCLK256       (8<<0)
#define CMU_HFPERCLKDIV_HFCLK512       (9<<0)
#define CMU_HFPERCLKDIV_CLEARMASK      (9<<0)

#define CMU_HFPERCLKDIV_HFPERCLKEN     (1<<8)



#define CMU_HFRCOCTRL      (*(volatile uint32_t*)(CMU_BASE + 0x00C)) 
#define CMU_LFRCOCTRL      (*(volatile uint32_t*)(CMU_BASE + 0x010)) 
#define CMU_AUXHFRCOCTRL   (*(volatile uint32_t*)(CMU_BASE + 0x014)) 
#define CMU_CALCTRL        (*(volatile uint32_t*)(CMU_BASE + 0x018))
#define CMU_CALCNT         (*(volatile uint32_t*)(CMU_BASE + 0x01C)) 
#define CMU_OSCENCMD       (*(volatile uint32_t*)(CMU_BASE + 0x020)) 
//Oscillator Enable/Disable Command Register

#define CMU_OSCENCMD_HFRCOEN       (1<<0) 
#define CMU_OSCENCMD_HFRCODIS      (1<<1) 
#define CMU_OSCENCMD_HFXOEN        (1<<2) 
#define CMU_OSCENCMD_HFXODIS       (1<<3) 
#define CMU_OSCENCMD_AUXHFRCOEN    (1<<4) 
#define CMU_OSCENCMD_AUXHFRCODIS   (1<<5) 
#define CMU_OSCENCMD_LFRCOEN       (1<<6) 
#define CMU_OSCENCMD_LFRCODIS      (1<<7) 
#define CMU_OSCENCMD_LFXOEN        (1<<8) 
#define CMU_OSCENCMD_LFXODIS       (1<<9) 
	

#define CMU_CMD            (*(volatile uint32_t*)(CMU_BASE + 0x024)) 
#define CMU_CMD_HFCLKSEL_HFRCO    (1<<0)
#define CMU_CMD_HFCLKSEL_HFXO     (2<<0)
#define CMU_CMD_HFCLKSEL_LFRCO    (3<<0)
#define CMU_CMD_HFCLKSEL_LFXO     (4<<0)
#define CMU_CMD_HFCLKSEL_CLEARFLAG (7<<0)

#define CMU_CMD_CALSTART   (1<<3)
#define CMU_CMD_CALSTOP    (1<<4)

#define CMU_LFCLKSEL       (*(volatile uint32_t*)(CMU_BASE + 0x028)) 
//Low Frequency Clock Select Register

#define  CMU_LFCLKSEL_LFA_DISABLED          (0<<0)
#define  CMU_LFCLKSEL_LFA_LFRCO             (1<<0)
#define  CMU_LFCLKSEL_LFA_LFXO              (2<<0)
#define  CMU_LFCLKSEL_LFA_HFCORECLKLEDIV2   (3<<0)
#define  CMU_LFCLKSEL_LFA_CLEARMASK         (3<<0)

#define  CMU_LFCLKSEL_LFB_DISABLED          (0<<2)
#define  CMU_LFCLKSEL_LFB_LFRCO             (1<<2)
#define  CMU_LFCLKSEL_LFB_LFXO              (2<<2)
#define  CMU_LFCLKSEL_LFB_HFCORECLKLEDIV2   (3<<2)
#define  CMU_LFCLKSEL_LFB_CLEARMASK         (3<<2)

#define  CMU_LFCLKSEL_LFAE      (1<<16)
#define  CMU_LFCLKSEL_LFBE      (1<<20)

#define CMU_STATUS         (*(volatile uint32_t*)(CMU_BASE + 0x02C)) 
#define CMU_STATUS_HFRCOENS     (1<<0)
#define CMU_STATUS_HFRCORDY     (1<<1)
#define CMU_STATUS_HFXOENS      (1<<2)
#define CMU_STATUS_HFXORDY      (1<<3)
#define CMU_STATUS_AUXHFRCOENS  (1<<4)
#define CMU_STATUS_AUXHFRCORDY  (1<<5)
#define CMU_STATUS_LFRCOENS     (1<<6)
#define CMU_STATUS_LFRCORDY     (1<<7)
#define CMU_STATUS_LFXOENS      (1<<8)
#define CMU_STATUS_LFXORDY      (1<<9)
#define CMU_STATUS_HFRCOSEL     (1<<10)
#define CMU_STATUS_HFXOSEL      (1<<11)
#define CMU_STATUS_LFRCOSEL     (1<<12)
#define CMU_STATUS_LFXOSEL      (1<<13)
#define CMU_STATUS_CALBSY       (1<<14)

#define CMU_IF             (*(volatile uint32_t*)(CMU_BASE + 0x030)) 
#define CMU_IF_HFRCORDY    (1<<0)
#define CMU_IF_HFXORDY     (1<<1)
#define CMU_IF_LFRCORDY    (1<<2)
#define CMU_IF_LFXORDY     (1<<3)
#define CMU_IF_AUXHFRCORDY (1<<4)
#define CMU_IF_CALRDY      (1<<5)
#define CMU_IF_CALOF       (1<<6)

#define CMU_IFS            (*(volatile uint32_t*)(CMU_BASE + 0x034)) 
#define CMU_IFS_HFRCORDY    (1<<0)
#define CMU_IFS_HFXORDY     (1<<1)
#define CMU_IFS_LFRCORDY    (1<<2)
#define CMU_IFS_LFXORDY     (1<<3)
#define CMU_IFS_AUXHFRCORDY (1<<4)
#define CMU_IFS_CALRDY      (1<<5)
#define CMU_IFS_CALOF       (1<<6)

#define CMU_IFC            (*(volatile uint32_t*)(CMU_BASE + 0x038)) 
#define CMU_IFC_HFRCORDY    (1<<0)
#define CMU_IFC_HFXORDY     (1<<1)
#define CMU_IFC_LFRCORDY    (1<<2)
#define CMU_IFC_LFXORDY     (1<<3)
#define CMU_IFC_AUXHFRCORDY (1<<4)
#define CMU_IFC_CALRDY      (1<<5)
#define CMU_IFC_CALOF       (1<<6)

#define CMU_IEN            (*(volatile uint32_t*)(CMU_BASE + 0x03C)) 
#define CMU_IEN_HFRCORDY    (1<<0)
#define CMU_IEN_HFXORDY     (1<<1)
#define CMU_IEN_LFRCORDY    (1<<2)
#define CMU_IEN_LFXORDY     (1<<3)
#define CMU_IEN_AUXHFRCORDY (1<<4)
#define CMU_IEN_CALRDY      (1<<5)
#define CMU_IEN_CALOF       (1<<6)

#define CMU_HFCORECLKEN0   (*(volatile uint32_t*)(CMU_BASE + 0x040)) 
//High Frequency Core Clock Enable Register 0
#define CMU_HFCORECLKEN0_AES  (1<<0)
#define CMU_HFCORECLKEN0_DMA  (1<<1)
#define CMU_HFCORECLKEN0_LE   (1<<2)

#define CMU_HFPERCLKEN0    (*(volatile uint32_t*)(CMU_BASE + 0x044)) 
//High Frequency Peripheral Clock Enable Register 0
#define CMU_HFPERCLKEN0_TIMER0  (1<<0)
#define CMU_HFPERCLKEN0_TIMER1  (1<<1)
#define CMU_HFPERCLKEN0_ACMP0   (1<<2)
#define CMU_HFPERCLKEN0_USART1  (1<<3)
#define CMU_HFPERCLKEN0_PRS     (1<<4)
#define CMU_HFPERCLKEN0_IDAC0   (1<<6)
#define CMU_HFPERCLKEN0_GPIO    (1<<7)
#define CMU_HFPERCLKEN0_VCMP    (1<<8)
#define CMU_HFPERCLKEN0_ADC0    (1<<10)
#define CMU_HFPERCLKEN0_I2C0    (1<<11)

#define CMU_SYNCBUSY       (*(volatile uint32_t*)(CMU_BASE + 0x050)) 
// Synchronization Busy Register

#define CMU_SYNCBUSY_LFACLKEN0  (1<<0)
#define CMU_SYNCBUSY_LFAPRESC0  (1<<2)
#define CMU_SYNCBUSY_LFBCLKEN0  (1<<4)
#define CMU_SYNCBUSY_LFBPRESC0  (1<<6)

#define CMU_FREEZE         (*(volatile uint32_t*)(CMU_BASE + 0x054)) 
#define CMU_FREEZE_REGFREEZE  (1<<0) 

//Low Frequency A Clock Enable Register 0  (Async Reg)
#define CMU_LFACLKEN0      (*(volatile uint32_t*)(CMU_BASE + 0x058)) 
#define CMU_LFACLKEN0_RTC  (1<<0) 

//Low Frequency B Clock Enable Register 0 (Async Reg)
#define CMU_LFBCLKEN0      (*(volatile uint32_t*)(CMU_BASE + 0x060)) 
#define CMU_LFBCLKEN0_LEUART0  (1<<0) 

// Low Frequency A Prescaler Register 0 (Async Reg)
#define CMU_LFAPRESC0      (*(volatile uint32_t*)(CMU_BASE + 0x068)) 
#define CMU_LFAPRESC0_DIV1       0
#define CMU_LFAPRESC0_DIV2       1
#define CMU_LFAPRESC0_DIV4       2
#define CMU_LFAPRESC0_DIV8       3
#define CMU_LFAPRESC0_DIV16      4
#define CMU_LFAPRESC0_DIV32      5
#define CMU_LFAPRESC0_DIV64      6
#define CMU_LFAPRESC0_DIV128     7
#define CMU_LFAPRESC0_DIV256     8
#define CMU_LFAPRESC0_DIV512     9
#define CMU_LFAPRESC0_DIV1024    10
#define CMU_LFAPRESC0_DIV2048    11
#define CMU_LFAPRESC0_DIV4096    12
#define CMU_LFAPRESC0_DIV8192    13
#define CMU_LFAPRESC0_DIV16634   14
#define CMU_LFAPRESC0_DIV32768   15
#define CMU_LFAPRESC0_CLEARMASK      0xf

//Low Frequency B Prescaler Register 0 (Async Reg)
#define CMU_LFBPRESC0      (*(volatile uint32_t*)(CMU_BASE + 0x070)) 
#define CMU_LFBPRESC0_DIV1       0   
#define CMU_LFBPRESC0_DIV2       1
#define CMU_LFBPRESC0_DIV4       2
#define CMU_LFBPRESC0_DIV8       3
#define CMU_LFBPRESC0_CLEARMASK      3

//PCNT Control Register
#define CMU_PCNTCTRL       (*(volatile uint32_t*)(CMU_BASE + 0x078)) 
#define CMU_PCNTCTRL_PCNT0CLKEN   (1<<0)
#define CMU_PCNTCTRL_PCNT0CLKSEL  (1<<1) 

//I/O Routing Register
#define CMU_ROUTE          (*(volatile uint32_t*)(CMU_BASE + 0x080)) 
#define CMU_ROUTE_CLKOUT0PEN  (1<<0) 
#define CMU_ROUTE_CLKOUT1PEN  (1<<1) 

//Configuration Lock Register
#define CMU_LOCK           (*(volatile uint32_t*)(CMU_BASE + 0x084)) 
#define CMU_LOCK_UNLOCKED     (1<<0)
#define CMU_LOCK_UNLOCK_CODE  0x580E


//TODO calibration registers




typedef enum _CLKOUTSEL0
{
	CLKOUTSEL0_HFRCO = CMU_CTRL_CLKOUTSEL0_HFRCO,
	CLKOUTSEL0_HFXO = CMU_CTRL_CLKOUTSEL0_HFXO,
	CLKOUTSEL0_HFCLK2 = CMU_CTRL_CLKOUTSEL0_HFCLK2,
	CLKOUTSEL0_HFCLK4 = CMU_CTRL_CLKOUTSEL0_HFCLK4,
	CLKOUTSEL0_HFCLK8 = CMU_CTRL_CLKOUTSEL0_HFCLK8,
	CLKOUTSEL0_HFCLK16 = CMU_CTRL_CLKOUTSEL0_HFCLK16,
	CLKOUTSEL0_ULFRCO = CMU_CTRL_CLKOUTSEL0_ULFRCO,
	CLKOUTSEL0_AUXHFRCO = CMU_CTRL_CLKOUTSEL0_AUXHFRCO,

} CLKOUTSEL0;

typedef enum _CLKOUTSEL1
{
	CLKOUTSEL1_LFRCO = CMU_CTRL_CLKOUTSEL1_LFRCO,
	CLKOUTSEL1_LFXO = CMU_CTRL_CLKOUTSEL1_LFXO,
	CLKOUTSEL1_HFCLK = CMU_CTRL_CLKOUTSEL1_HFCLK,
	CLKOUTSEL1_LFXOQ = CMU_CTRL_CLKOUTSEL1_LFXOQ,
	CLKOUTSEL1_HFXOQ = CMU_CTRL_CLKOUTSEL1_HFXOQ,
	CLKOUTSEL1_LFRCOQ = CMU_CTRL_CLKOUTSEL1_LFRCOQ,
	CLKOUTSEL1_HFRCOQ = CMU_CTRL_CLKOUTSEL1_HFRCOQ,
	CLKOUTSEL1_AUXHFRCOQ = CMU_CTRL_CLKOUTSEL1_AUXHFRCOQ

} CLKOUTSEL1;



//hfrco
void CMU_EnableHFRCO(BOOL enable);

//hfxo
void CMU_EnableHFXO(BOOL enable);
void CMU_SetHFXOMODE_XTAL (void);
void CMU_SetHFXOMODE_BUFEXTCLK (void);
void CMU_SetHFXOMODE_DIGEXTCLK (void);

void CMU_SetHFXOTIMEOUT_8 (void);
void CMU_SetHFXOTIMEOUT_256 (void);
void CMU_SetHFXOTIMEOUT_1K (void);
void CMU_SetHFXOTIMEOUT_16K (void);

//auxhfrco
void CMU_EnableAUXHFRCO(BOOL enable);

//lfrco
void CMU_EnableLFRCO(BOOL enable);

//lfxo
void CMU_EnableLFXO(BOOL enable);
void CMU_SetLFXOMODE_XTAL (void);
void CMU_SetLFXOMODE_BUFEXTCLK (void);
void CMU_SetLFXOMODE_DIGEXTCLK (void);
void CMU_SetLFXOTIMEOUT_8 (void);
void CMU_SetLFXOTIMEOUT_1K (void);
void CMU_SetLFXOTIMEOUT_16K (void);

//select clock
void CMU_SelectHFCLK_HFRCO(void);
void CMU_SelectHFCLK_HFXO(void);
void CMU_SelectHFCLK_LFRCO(void);
void CMU_SelectHFCLK_LFXO(void);

//prescalers

void CMU_SetHFCORECLK_DIV1 (void);
void CMU_SetHFCORECLK_DIV2 (void);
void CMU_SetHFCORECLK_DIV4 (void);
void CMU_SetHFCORECLK_DIV8 (void);
void CMU_SetHFCORECLK_DIV16 (void);
void CMU_SetHFCORECLK_DIV32 (void);
void CMU_SetHFCORECLK_DIV64 (void);
void CMU_SetHFCORECLK_DIV128 (void);
void CMU_SetHFCORECLK_DIV256 (void);
void CMU_SetHFCORECLK_DIV512 (void);

void CMU_SetHFCORECLK_LE_DIV2(void);
void CMU_SetHFCORECLK_LE_DIV4(void);

void CMU_SetHFPERCLK_DIV1 (void);
void CMU_SetHFPERCLK_DIV2 (void);
void CMU_SetHFPERCLK_DIV4 (void);
void CMU_SetHFPERCLK_DIV8 (void);
void CMU_SetHFPERCLK_DIV16 (void);
void CMU_SetHFPERCLK_DIV32 (void);
void CMU_SetHFPERCLK_DIV64 (void);
void CMU_SetHFPERCLK_DIV128 (void);
void CMU_SetHFPERCLK_DIV256 (void);
void CMU_SetHFPERCLK_DIV512 (void);

void CMU_EnableHFPERCLK (BOOL enable);

/////////////////////////////////////////
//low freq prescalers 
void CMU_SetLFAPrescaler_DIV1 (void);
void CMU_SetLFAPrescaler_DIV2 (void);
void CMU_SetLFAPrescaler_DIV4 (void);
void CMU_SetLFAPrescaler_DIV8 (void);
void CMU_SetLFAPrescaler_DIV16 (void);
void CMU_SetLFAPrescaler_DIV32 (void);
void CMU_SetLFAPrescaler_DIV64 (void);
void CMU_SetLFAPrescaler_DIV128 (void);
void CMU_SetLFAPrescaler_DIV256 (void);
void CMU_SetLFAPrescaler_DIV512 (void);
void CMU_SetLFAPrescaler_DIV1K (void);
void CMU_SetLFAPrescaler_DIV2K (void);
void CMU_SetLFAPrescaler_DIV4K (void);
void CMU_SetLFAPrescaler_DIV8K (void);
void CMU_SetLFAPrescaler_DIV16K (void);
void CMU_SetLFAPrescaler_DIV32K (void);

void CMU_SetLFBPrescaler_DIV1 (void);
void CMU_SetLFBPrescaler_DIV2 (void);
void CMU_SetLFBPrescaler_DIV4 (void);
void CMU_SetLFBPrescaler_DIV8 (void);


void CMU_EnableLFACLK_LFRCO(void);
void CMU_EnableLFACLK_LFXO(void);
void CMU_EnableLFACLK_HFCORECLKLEDIV2(void);
void CMU_EnableLFACLK_ULFRCO(void);
void CMU_DisableLFACLK(void);

void CMU_EnableLFBCLK_LFRCO(void);
void CMU_EnableLFBCLK_LFXO(void);
void CMU_EnableLFBCLK_HFCORECLKLEDIV2(void);
void CMU_EnableLFBCLK_ULFRCO(void);
void CMU_DisableLFBCLK(void);



////////////////////////////////
void CMU_EnableCoreClock_AES(BOOL enable); 
void CMU_EnableCoreClock_DMA(BOOL enable); 
void CMU_EnableCoreClock_LE(BOOL enable); 

void CMU_Enable_Peripheral_AES(BOOL enable);
void CMU_Enable_Peripheral_DMA(BOOL enable);
void CMU_Enable_Peripheral_TIMER0(BOOL enable);
void CMU_Enable_Peripheral_TIMER1(BOOL enable);
void CMU_Enable_Peripheral_ACMP0(BOOL enable);
void CMU_Enable_Peripheral_USART1(BOOL enable);
void CMU_Enable_Peripheral_PRS(BOOL enable);
void CMU_Enable_Peripheral_IDAC0(BOOL enable);
void CMU_Enable_Peripheral_GPIO(BOOL enable);
void CMU_Enable_Peripheral_VCMP(BOOL enable);
void CMU_Enable_Peripheral_ADC0(BOOL enable);
void CMU_Enable_Peripheral_I2C0(BOOL enable);
void CMU_Enable_Peripheral_RTC(BOOL enable);
void CMU_Enable_Peripheral_LEUART0(BOOL enable);

void CMU_Enable_LFA_RTC(BOOL enable);
void CMU_Enable_LFB_LEUART0(BOOL enable);


//////////////////////

void CMU_EnableCLKOUTSEL0 (CLKOUTSEL0 value);
void CMU_EnableCLKOUTSEL1 (CLKOUTSEL1 value);
void CMU_DisableCLKOUTSEL0(void);
void CMU_DisableCLKOUTSEL1(void);


#endif
