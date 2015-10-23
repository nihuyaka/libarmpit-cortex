#define RCC_CSR  (*(volatile uint32_t*)(RCC_BASE + 0x74))

#define RCC_CSR_LSION  (1<<0)         //set by sw (enable)
#define RCC_CSR_LSIRDY (1<<1)         //set by hw

#define RCC_CSR_RMVF      (1<<24)
#define RCC_CSR_BORRSTF   (1<<25)
#define RCC_CSR_PINRSTF   (1<<26)
#define RCC_CSR_PORRSTF   (1<<27)
#define RCC_CSR_SFTRSTF   (1<<28)
#define RCC_CSR_IWDGRSTF  (1<<29)
#define RCC_CSR_WWDGRSTF  (1<<30)
#define RCC_CSR_LPWRRSTF  (1<<31)


