#define RCC_CKGATENR  (*(volatile uint32_t*)(RCC_BASE + 0x90))


#define RCC_CKGATENR_AHB2APB1_CKEN (1<<0) 
#define RCC_CKGATENR_AHB2APB2_CKEN (1<<1) 
#define RCC_CKGATENR_CM4DBG_CKEN   (1<<2) 
#define RCC_CKGATENR_SPARE_CKEN    (1<<3) 
#define RCC_CKGATENR_SRAM_CKEN     (1<<4) 
#define RCC_CKGATENR_FLITF_CKEN    (1<<5) 
#define RCC_CKGATENR_RCC_CKEN      (1<<6) 


