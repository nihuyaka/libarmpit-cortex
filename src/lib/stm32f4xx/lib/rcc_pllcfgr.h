//////////////////////////////////////////////////////////
#define RCC_PLLCFGR  (*(volatile uint32_t*)(RCC_BASE + 0x4))

//division factor for the main PLL input clock 
#define RCC_PLLCFGR_PLLM_OFFSET 0
#define RCC_PLLCFGR_PLLM_CLEARMASK (0x3f<<RCC_PLLCFGR_PLLM_OFFSET)

//PLLN[8:0]:Main PLL (PLL) multiplication factor for VCO   100 to  432
#define RCC_PLLCFGR_PLLN_OFFSET 6
#define RCC_PLLCFGR_PLLN_CLEARMASK (0x1ff<<RCC_PLLCFGR_PLLN_OFFSET)


//PLLP[1:0]:Main PLL (PLL) division factor for main system clock
#define RCC_PLLCFGR_PLLP_OFFSET 16
#define RCC_PLLCFGR_PLLP_2 (0<<RCC_PLLCFGR_PLLP_OFFSET)
#define RCC_PLLCFGR_PLLP_4 (1<<RCC_PLLCFGR_PLLP_OFFSET)
#define RCC_PLLCFGR_PLLP_6 (2<<RCC_PLLCFGR_PLLP_OFFSET)
#define RCC_PLLCFGR_PLLP_8 (3<<RCC_PLLCFGR_PLLP_OFFSET)
#define RCC_PLLCFGR_PLLP_CLEARMASK (3<<RCC_PLLCFGR_PLLP_OFFSET)

#define RCC_PLLCFGR_PLLSRC_HSI        (0<<22)
#define RCC_PLLCFGR_PLLSRC_HSE        (1<<22)
#define RCC_PLLCFGR_PLLSRC_CLEARMASK  (1<<22)

//PLLQ[3:0]:Main PLL (PLL) division factor for USB OTG FS, SDIOclocks
//2 to 15 
#define RCC_PLLCFGR_PLLQ 24
#define RCC_PLLCFGR_PLLQ_CLEARMASK (4<<24)


//Main PLL division factor for I2Ss, SAIs, SYSTEM and SPDIF-Rx clocks
//2 to 7 
#define RCC_PLLCFGR_PLLR 28
#define RCC_PLLCFGR_PLLR_CLEARMASK (3<<28)


