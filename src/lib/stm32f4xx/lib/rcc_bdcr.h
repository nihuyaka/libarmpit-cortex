#define RCC_BDCR  (*(volatile uint32_t*)(RCC_BASE + 0x70))
#define RCC_BDCR_LSEON  (1<<0)         
#define RCC_BDCR_LSERDY (1<<1)         
#define RCC_BDCR_LSEBYP (1<<2)         //External low-speed oscillator bypass

#define RCC_BDCR_LSEMOD_LOW_POWER  (0<<3)
#define RCC_BDCR_LSEMOD_HIGH_POWER (1<<3)
#define RCC_BDCR_LSEMOD_CLEARMASK  (1<<3)


#define RCC_BDCR_RTC_NOCLK        (0<<8)
#define RCC_BDCR_RTC_LSE          (1<<8)
#define RCC_BDCR_RTC_LSI          (2<<8)
#define RCC_BDCR_RTC_HSE          (3<<8)  //HSE oscillator clock divided by a programmable prescaler (selection through the 
                                          //RTCPRE[4:0] bits in RCC_CFGR) used as the RTC clock (1MHz)
#define RCC_BDCR_RTC_CLEARMASK    (3<<8)

#define RCC_BDCR_RTCEN   (1<<15)    
#define RCC_BDCR_BDRST   (1<<16)   //1: resets the entire backup domain
