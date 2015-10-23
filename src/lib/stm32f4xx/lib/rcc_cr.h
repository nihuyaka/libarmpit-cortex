//////////////////////////////////////////////////////////
#define RCC_CR  (*(volatile uint32_t*)(RCC_BASE + 0x0))

//common with f10x
#define RCC_CR_HSION  (1<<0) 
#define RCC_CR_HSIRDY (1<<1)        
#define RCC_CR_HSEON  (1<<16)        
#define RCC_CR_HSERDY (1<<17)        
#define RCC_CR_HSEBYP (1<<18)
#define RCC_CR_CSSON  (1<<19)

//System PLL 
#define RCC_CR_PLLON  (1<<24)        
#define RCC_CR_PLLRDY (1<<25)        

//f4xx I2S and SAI PLLs

#define RCC_CR_PLLI2SON   (1<<26)
#define RCC_CR_PLLI2SRDY  (1<<27)
#define RCC_CR_PLLISAION  (1<<28)
#define RCC_CR_PLLSAIRDY  (1<<29)

//f(VCO clock) = f(PLL clock input) x (PLLN / PLLM) 
//f(PLL general clock output)= f(VCO clock)/ PLLP
//f(USB OTG FS, SDIO)= f(VCO clock)/ PLLQ

