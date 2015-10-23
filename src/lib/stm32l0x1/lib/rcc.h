/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 igorS
 *  
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */



#ifndef _RCC_H
#define _RCC_H

#include "common.h"

#ifndef HSE_CLOCK_FREQ 
#define HSE_CLOCK_FREQ 4000000
#endif

/* RCC  ****************************************************/
#define RCC_OFFSET  0x21000 
#define RCC_BASE    (PERIPH_BASE + RCC_OFFSET)

#define RCC_CR  (*(volatile uint32_t*)(RCC_BASE))

#define RCC_CR_HSI16ON    (1<<0) 
#define RCC_CR_HSI16KERON (1<<1)        
#define RCC_CR_HSI16RDYF  (1<<2)  
#define RCC_CR_HSI16DIVEN (1<<3)      
#define RCC_CR_HSI16DIVF  (1<<4)      
#define RCC_CR_HSI16OUTEN (1<<5)      
#define RCC_CR_MSION      (1<<8)      
#define RCC_CR_MSIRDY     (1<<9)      
#define RCC_CR_HSEON      (1<<16)      
#define RCC_CR_HSERDY     (1<<17)      
#define RCC_CR_HSEBYP     (1<<18)      
#define RCC_CR_CSSHSEON   (1<<19)      

#define RCC_CR_RTCPRE_HSEDIV2  (0<<20)      
#define RCC_CR_RTCPRE_HSEDIV4  (1<<20)      
#define RCC_CR_RTCPRE_HSEDIV8  (2<<20)      
#define RCC_CR_RTCPRE_HSEDIV16 (3<<20)      
#define RCC_CR_RTCPRE_CLEARMASK (3<<20)      

#define RCC_CR_PLLON   (1<<24)      
#define RCC_CR_PLLRDY  (1<<25)      



#define RCC_CFGR  (*(volatile uint32_t*)(RCC_BASE + 0xc))

//clock source
#define RCC_CFGR_SW_MSI        (0<<0)
#define RCC_CFGR_SW_HSI16      (1<<0)
#define RCC_CFGR_SW_HSE        (2<<0)
#define RCC_CFGR_SW_PLL        (3<<0)
#define RCC_CFGR_SW_CLEARMASK  (3<<0)

#define RCC_CFGR_SWS_MSI        (0<<0)
#define RCC_CFGR_SWS_HSI16      (1<<0)
#define RCC_CFGR_SWS_HSE        (2<<0)
#define RCC_CFGR_SWS_PLL        (3<<0)
#define RCC_CFGR_SWS_CLEARMASK  (3<<0)


//AHB prescaler (up to 72Mhz)
#define RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV1   (0<<4) 
#define RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV2   (8<<4) 
#define RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV4   (9<<4)
#define RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV8   (10<<4) 
#define RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV16  (11<<4) 
#define RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV64  (12<<4) 
#define RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV128 (13<<4) 
#define RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV256 (14<<4) 
#define RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV512 (15<<4)
#define RCC_CFGR_AHB_HCLK_PRE_SYSCLK_CLEARMASK (15<<4)

//APB1 low speed prescaler (up to 32Mhz) AHB / div
#define RCC_CFGR_APB1_PCLK1_PRE_AHB_HCLK_DIV1  (0<<8) 
#define RCC_CFGR_APB1_PCLK1_PRE_AHB_HCLK_DIV2  (4<<8)
#define RCC_CFGR_APB1_PCLK1_PRE_AHB_HCLK_DIV4  (5<<8)
#define RCC_CFGR_APB1_PCLK1_PRE_AHB_HCLK_DIV8  (6<<8)
#define RCC_CFGR_APB1_PCLK1_PRE_AHB_HCLK_DIV16 (7<<8)
#define RCC_CFGR_APB1_PCLK1_PRE_AHB_HCLK_CLEARMASK (7<<8)


//APB2 high speed prescaler (up to 72 Mhz)  AHB / div
#define RCC_CFGR_APB2_PCLK2_PRE_AHB_HCLK_DIV1  (0<<11)
#define RCC_CFGR_APB2_PCLK2_PRE_AHB_HCLK_DIV2  (4<<11)
#define RCC_CFGR_APB2_PCLK2_PRE_AHB_HCLK_DIV4  (5<<11) 
#define RCC_CFGR_APB2_PCLK2_PRE_AHB_HCLK_DIV8  (6<<11) 
#define RCC_CFGR_APB2_PCLK2_PRE_AHB_HCLK_DIV16 (7<<11) 
#define RCC_CFGR_APB2_PCLK2_PRE_AHB_HCLK_CLEARMASK (7<<11)


//ADC presc:  APB2 / DIV
#define RCC_CFGR_ADCPRE_APB2_PCLK2_DIV2 (0<<14)
#define RCC_CFGR_ADCPRE_APB2_PCLK2_DIV4 (1<<14)
#define RCC_CFGR_ADCPRE_APB2_PCLK2_DIV6 (2<<14)
#define RCC_CFGR_ADCPRE_APB2_PCLK2_DIV8 (3<<14)
#define RCC_CFGR_ADCPRE_APB2_PCLK2_CLEARMASK (3<<14)

#define RCC_CFGR_STOPWUCK           (1<<15)

#define RCC_CFGR_PLLSRC_HSI         (0<<16)
#define RCC_CFGR_PLLSRC_HSE         (1<<16)
#define RCC_CFGR_PLLSRC_CLEARMASK   (1<<16)

//max: 96 (1)  48(2)  24(3)
#define RCC_CFGR_PLL_MUL3   (0<<18)   
#define RCC_CFGR_PLL_MUL4   (1<<18)
#define RCC_CFGR_PLL_MUL6   (2<<18)  
#define RCC_CFGR_PLL_MUL8   (3<<18)  
#define RCC_CFGR_PLL_MUL12  (4<<18)  
#define RCC_CFGR_PLL_MUL16  (5<<18)  
#define RCC_CFGR_PLL_MUL24  (6<<18)
#define RCC_CFGR_PLL_MUL32  (7<<18)  
#define RCC_CFGR_PLL_MUL48  (8<<18)  
#define RCC_CFGR_PLL_MUL_CLEARMASK (0xf<<18)

#define RCC_CFGR_PLL_VCODIV2          (1<<22)   
#define RCC_CFGR_PLL_VCODIV3          (2<<22)   
#define RCC_CFGR_PLL_VCODIV4          (3<<22)   
#define RCC_CFGR_PLL_VCODIV_CLEARMASK (3<<22)

#define MCOSEL_OFF       (0<<24)
#define MCOSEL_SYSCLK    (1<<24)
#define MCOSEL_HSI16     (2<<24)
#define MCOSEL_MSI       (3<<24)
#define MCOSEL_HSE       (4<<24)
#define MCOSEL_PLL       (5<<24)
#define MCOSEL_LSI       (6<<24)
#define MCOSEL_LSE       (7<<24)
#define MCOSEL_CLEARMASK (7<<24)

#define MSOPRE_MCODIV1   (0<<28)
#define MSOPRE_MCODIV2   (1<<28)
#define MSOPRE_MCODIV4   (2<<28)
#define MSOPRE_MCODIV8   (3<<28)
#define MSOPRE_MCODIV16  (4<<28)
#define MSOPRE_MCODIV_CLEARMASK  (4<<28)

//////////////////////////////////////////////////////

#define RCC_IOPRSTR  (*(volatile uint32_t*)(RCC_BASE + 0x1c))
#define RCC_APB2RSTR_GIOPARST  (1<<0)
#define RCC_APB2RSTR_GIOPBRST  (1<<1)
#define RCC_APB2RSTR_GIOPCRST  (1<<2)
#define RCC_APB2RSTR_GIOPDRST  (1<<3)
#define RCC_APB2RSTR_GIOPERST  (1<<4)
#define RCC_APB2RSTR_GIOPHRST  (1<<7)

#define RCC_AHBRSTR  (*(volatile uint32_t*)(RCC_BASE + 0x20))
#define RCC_AHBRSTR_DMARST   (1<<0) 
#define RCC_AHBRSTR_MIFRST   (1<<8) 
#define RCC_AHBRSTR_CRCRST   (1<<12) 
#define RCC_AHBRSTR_CRYPRST   (1<<24) 


#define RCC_APB2RSTR  (*(volatile uint32_t*)(RCC_BASE + 0x24))
#define RCC_APB2RSTR_SYSCFGRST  (1<<0)
#define RCC_APB2RSTR_TIM21RST   (1<<2)
#define RCC_APB2RSTR_TIM22RST   (1<<5)
#define RCC_APB2RSTR_ADCRST     (1<<9)
#define RCC_APB2RSTR_USART1RST  (1<<14)
#define RCC_APB2RSTR_DBGRST     (1<<22)


#define RCC_APB1RSTR  (*(volatile uint32_t*)(RCC_BASE + 0x28))

#define RCC_APB1RSTR_TIM2RST     (1<<0)
#define RCC_APB1RSTR_TIM3RST     (1<<1)
#define RCC_APB1RSTR_TIM6RST     (1<<4)
#define RCC_APB1RSTR_TIM7RST     (1<<5)
#define RCC_APB1RSTR_WWDGRST     (1<<11)
#define RCC_APB1RSTR_SPI2RST     (1<<14)
#define RCC_APB1RSTR_USART2RST   (1<<17)
#define RCC_APB1RSTR_LPUART1RST  (1<<18)
#define RCC_APB1RSTR_USART4RST   (1<<19)
#define RCC_APB1RSTR_USART5RST   (1<<20)
#define RCC_APB1RSTR_I2C1RST     (1<<21)
#define RCC_APB1RSTR_I2C2RST     (1<<22)
#define RCC_APB1RSTR_CRSRST      (1<<27) 
#define RCC_APB1RSTR_PWRRST      (1<<28)
#define RCC_APB1RSTR_I2C3RST     (1<<30) 
#define RCC_APB1RSTR_LPTIM1RST   (1<<31) 


//////////////////////////////

#define RCC_IOPENR  (*(volatile uint32_t*)(RCC_BASE + 0x2c))
#define RCC_APB2ENR_GIOPAEN  (1<<0)
#define RCC_APB2ENR_GIOPBEN  (1<<1)
#define RCC_APB2ENR_GIOPCEN  (1<<2)
#define RCC_APB2ENR_GIOPDEN  (1<<3)
#define RCC_APB2ENR_GIOPEEN  (1<<4)
#define RCC_APB2ENR_GIOPHEN  (1<<7)

#define RCC_AHBENR  (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define RCC_AHBENR_DMAEN   (1<<0) 
#define RCC_AHBENR_MIFEN   (1<<8) 
#define RCC_AHBENR_CRCEN   (1<<12) 
#define RCC_AHBENR_CRYPEN   (1<<24) 


#define RCC_APB2ENR  (*(volatile uint32_t*)(RCC_BASE + 0x34))
#define RCC_APB2ENR_SYSCFGEN  (1<<0)
#define RCC_APB2ENR_TIM21EN   (1<<2)
#define RCC_APB2ENR_TIM22EN   (1<<5)
#define RCC_APB2ENR_FWEN      (1<<7)
#define RCC_APB2ENR_ADCEN     (1<<9)
#define RCC_APB2ENR_USART1EN  (1<<14)
#define RCC_APB2ENR_DBGEN     (1<<22)


#define RCC_APB1ENR  (*(volatile uint32_t*)(RCC_BASE + 0x38))

#define RCC_APB1ENR_TIM2EN     (1<<0)
#define RCC_APB1ENR_TIM3EN     (1<<1)
#define RCC_APB1ENR_TIM6EN     (1<<4)
#define RCC_APB1ENR_TIM7EN     (1<<5)
#define RCC_APB1ENR_WWDGEN     (1<<11)
#define RCC_APB1ENR_SPI2EN     (1<<14)
#define RCC_APB1ENR_USART2EN   (1<<17)
#define RCC_APB1ENR_LPUART1EN  (1<<18)
#define RCC_APB1ENR_USART4EN   (1<<19)
#define RCC_APB1ENR_USART5EN   (1<<20)
#define RCC_APB1ENR_I2C1EN     (1<<21)
#define RCC_APB1ENR_I2C2EN     (1<<22)
#define RCC_APB1ENR_CRSEN      (1<<27) 
#define RCC_APB1ENR_PWREN      (1<<28)
#define RCC_APB1ENR_I2C3EN     (1<<30) 
#define RCC_APB1ENR_LPTIM1EN   (1<<31) 




////////////////////////////

#define RCC_IOPSMENR  (*(volatile uint32_t*)(RCC_BASE + 0x3c))
#define RCC_APB2SMENR_GIOPASMEN  (1<<0)
#define RCC_APB2SMENR_GIOPBSMEN  (1<<1)
#define RCC_APB2SMENR_GIOPCSMEN  (1<<2)
#define RCC_APB2SMENR_GIOPDSMEN  (1<<3)
#define RCC_APB2SMENR_GIOPESMEN  (1<<4)
#define RCC_APB2SMENR_GIOPHSMEN  (1<<7)

#define RCC_AHBSMENR  (*(volatile uint32_t*)(RCC_BASE + 0x40))
#define RCC_AHBSMENR_DMASMEN   (1<<0) 
#define RCC_AHBSMENR_MIFSMEN   (1<<8) 
#define RCC_AHBSMENR_CRCSMEN   (1<<12) 
#define RCC_AHBSMENR_CRYPSMEN   (1<<24) 


#define RCC_APB2SMENR  (*(volatile uint32_t*)(RCC_BASE + 0x44))
#define RCC_APB2SMENR_SYSCFGSMEN  (1<<0)
#define RCC_APB2SMENR_TIM21SMEN   (1<<2)
#define RCC_APB2SMENR_TIM22SMEN   (1<<5)
#define RCC_APB2SMENR_FWSMEN      (1<<7)
#define RCC_APB2SMENR_ADCSMEN     (1<<9)
#define RCC_APB2SMENR_USART1SMEN  (1<<14)
#define RCC_APB2SMENR_DBGSMEN     (1<<22)


#define RCC_APB1SMENR  (*(volatile uint32_t*)(RCC_BASE + 0x48))

#define RCC_APB1SMENR_TIM2SMEN     (1<<0)
#define RCC_APB1SMENR_TIM3SMEN     (1<<1)
#define RCC_APB1SMENR_TIM6SMEN     (1<<4)
#define RCC_APB1SMENR_TIM7SMEN     (1<<5)
#define RCC_APB1SMENR_WWDGSMEN     (1<<11)
#define RCC_APB1SMENR_SPI2SMEN     (1<<14)
#define RCC_APB1SMENR_USART2SMEN   (1<<17)
#define RCC_APB1SMENR_LPUART1SMEN  (1<<18)
#define RCC_APB1SMENR_USART4SMEN   (1<<19)
#define RCC_APB1SMENR_USART5SMEN   (1<<20)
#define RCC_APB1SMENR_I2C1SMEN     (1<<21)
#define RCC_APB1SMENR_I2C2SMEN     (1<<22)
#define RCC_APB1SMENR_CRSSMEN      (1<<27) 
#define RCC_APB1SMENR_PWRSMEN      (1<<28)
#define RCC_APB1SMENR_I2C3SMEN     (1<<30) 
#define RCC_APB1SMENR_LPTIM1SMEN   (1<<31) 

///////////////////////////


#define RCC_CCIPR  (*(volatile uint32_t*)(RCC_BASE + 0x4c))
#define RCC_CCIPR_USART1SEL_APB         (0<<0)
#define RCC_CCIPR_USART1SEL_SYSCLOCK    (1<<0)
#define RCC_CCIPR_USART1SEL_HSI16       (2<<0)
#define RCC_CCIPR_USART1SEL_LSE         (3<<0)
#define RCC_CCIPR_USART1SEL_CLEARMASK   (3<<0)

#define RCC_CCIPR_USART2SEL_APB         (0<<2)
#define RCC_CCIPR_USART2SEL_SYSCLOCK    (1<<2)
#define RCC_CCIPR_USART2SEL_HSI16       (2<<2)
#define RCC_CCIPR_USART2SEL_LSE         (3<<2)
#define RCC_CCIPR_USART2SEL_CLEARMASK   (3<<2)

#define RCC_CCIPR_LPUART1SEL_APB         (0<<10)
#define RCC_CCIPR_LPUART1SEL_SYSCLOCK    (1<<10)
#define RCC_CCIPR_LPUART1SEL_HSI16       (2<<10)
#define RCC_CCIPR_LPUART1SEL_LSE         (3<<10)
#define RCC_CCIPR_LPUART1SEL_CLEARMASK   (3<<10)

#define RCC_CCIPR_I2C1SEL_APB         (0<<12)
#define RCC_CCIPR_I2C1SEL_SYSCLOCK    (1<<12)
#define RCC_CCIPR_I2C1SEL_HSI16       (2<<12)
#define RCC_CCIPR_I2C1SEL_CLEARMASK   (3<<12)

#define RCC_CCIPR_I2C1SEL_APB         (0<<12)
#define RCC_CCIPR_I2C1SEL_SYSCLOCK    (1<<12)
#define RCC_CCIPR_I2C1SEL_HSI16       (2<<12)
#define RCC_CCIPR_I2C1SEL_CLEARMASK   (3<<12)

#define RCC_CCIPR_I2C3SEL_APB         (0<<16)
#define RCC_CCIPR_I2C3SEL_SYSCLOCK    (1<<16)
#define RCC_CCIPR_I2C3SEL_HSI16       (2<<16)
#define RCC_CCIPR_I2C3SEL_CLEARMASK   (3<<16)

#define RCC_CCIPR_LPTIM1SEL_APB         (0<<18)
#define RCC_CCIPR_LPTIM1SEL_SYSCLOCK    (1<<18)
#define RCC_CCIPR_LPTIM1SEL_HSI16       (2<<18)
#define RCC_CCIPR_LPTIM1SEL_LSE         (3<<18)
#define RCC_CCIPR_LPTIM1SEL_CLEARMASK   (3<<18)



///////////////////////////////////////////////
#define RCC_CSR  (*(volatile uint32_t*)(RCC_BASE + 0x50))

#define RCC_CSR_LSION  (1<<0)        
#define RCC_CSR_LSIRDY (1<<1)        
#define RCC_CSR_LSEON  (1<<8)        
#define RCC_CSR_LSERDY (1<<9)        
#define RCC_CSR_LSEBYP (1<<10)        
#define RCC_CSR_LSEDRV_LOW        (0<<11)
#define RCC_CSR_LSEDRV_MED1       (1<<11)
#define RCC_CSR_LSEDRV_MED2       (2<<11)
#define RCC_CSR_LSEDRV_HIGH       (3<<11)
#define RCC_CSR_LSEDRV_CLEARMASK  (3<<11)
#define RCC_CSR_CSSLSEON   (1<<13) 
#define RCC_CSR_CSSLSED    (1<<14) 
#define RCC_CSR_RTCSEL_OFF     (0<<16) 
#define RCC_CSR_RTCSEL_LSE     (1<<16) 
#define RCC_CSR_RTCSEL_LSI     (2<<16) 
#define RCC_CSR_RTCSEL_HSE     (3<<16) 
#define RCC_CSR_RTCSEL_CLEARMASK     (3<<16) 


#define RCC_CSR_RTCEN      (1<<18) 
#define RCC_CSR_RTCRST     (1<<19) 
#define RCC_CSR_RMVF       (1<<23) 
#define RCC_CSR_FWRSTF     (1<<24) 
#define RCC_CSR_OBLRSTF    (1<<25) 
#define RCC_CSR_PINRSTF    (1<<26) 
#define RCC_CSR_PORRSTF    (1<<27) 
#define RCC_CSR_SFTRSTF    (1<<28) 
#define RCC_CSR_IWDGRSTF   (1<<29) 
#define RCC_CSR_WWDGRSTF   (1<<30) 
#define RCC_CSR_LPWRRSTF   (1<<31) 

#ifdef __cplusplus
extern "C"
{
#endif

    void RCC_SetAHBPrescalerDiv1(void);
    void RCC_SetAHBPrescalerDiv2(void);
    void RCC_SetAHBPrescalerDiv4(void);
    void RCC_SetAHBPrescalerDiv8(void);
    void RCC_SetAHBPrescalerDiv16(void);
    void RCC_SetAHBPrescalerDiv64(void);
    void RCC_SetAHBPrescalerDiv128(void);
    void RCC_SetAHBPrescalerDiv256(void);
    void RCC_SetAHBPrescalerDiv512(void);
   
    void RCC_SetAPB1PrescalerDiv1 (void);
    void RCC_SetAPB1PrescalerDiv2 (void);
    void RCC_SetAPB1PrescalerDiv4 (void);
    void RCC_SetAPB1PrescalerDiv8 (void);
    void RCC_SetAPB1PrescalerDiv16 (void);

    void RCC_SetAPB2PrescalerDiv1 (void);
    void RCC_SetAPB2PrescalerDiv2 (void);
    void RCC_SetAPB2PrescalerDiv4 (void);
    void RCC_SetAPB2PrescalerDiv8 (void);
    void RCC_SetAPB2PrescalerDiv16 (void);
    
    
    void RCC_EnableHSI16(BOOL enable);
    void RCC_EnableMSI(BOOL enable);
    void RCC_EnableHSE(BOOL enable);
    void RCC_EnablePLL(uint8_t pllm_mul, uint8_t pll_div);
    void RCC_DisablePLL(void);
    void RCC_BypassHSE(BOOL bypassHSE);

    void RCC_EnableLSI(BOOL enable);
    void RCC_EnableLSE(BOOL enable);

    BOOL RCC_IsEnabledHSE(void);
    BOOL RCC_IsEnabledMSI(void);
    BOOL RCC_IsEnabledHSI16(void);
    BOOL RCC_IsEnabledLSE(void);
    BOOL RCC_IsEnabledLSI(void);
    
    uint32_t RCC_GetSystemClock(void);
    uint32_t RCC_GetAHB_CLK(void);
    uint32_t RCC_GetAPB1_CLK(void);
    uint32_t RCC_GetAPB2_CLK(void);
    uint32_t RCC_GetTIMx_CLK(BOOL isAPB1);
    uint32_t RCC_GetRTC_CLK(void);
        
    
    void RCC_Delay_us(uint32_t us);
    void RCC_Delay_ms(uint32_t ms);

    void RCC_EnableRTC(BOOL enable);
    void RCC_SetRTCClockSourceLSE(void);
    void RCC_SetRTCClockSourceLSI(void);
    void RCC_SetRTCClockSourceHSE(void);
    void RCC_SetRTCClockSourceOFF(void);

    //AHB
    void RCC_EnableDMA(BOOL enable);
    void RCC_EnableMIF(BOOL enable);
    void RCC_EnableCRC(BOOL enable);
    void RCC_EnableCRYP(BOOL enable);

    //APB1
    void RCC_EnableTIM2(BOOL enable);
    void RCC_EnableTIM3(BOOL enable);
    void RCC_EnableTIM6(BOOL enable);
    void RCC_EnableTIM7(BOOL enable);
    void RCC_EnableWWDG(BOOL enable);
    void RCC_EnableSPI2(BOOL enable);
    void RCC_EnableUSART2(BOOL enable);
    void RCC_EnableLPUART1(BOOL enable);
    void RCC_EnableUSART4(BOOL enable);
    void RCC_EnableUSART5(BOOL enable);
    void RCC_EnableI2C1(BOOL enable);
    void RCC_EnableI2C2(BOOL enable);
    void RCC_EnablePWR(BOOL enable);
    void RCC_EnableI2C3(BOOL enable);
    void RCC_EnableLPTIM1(BOOL enable);



    //APB2
    void RCC_EnableSYSCFG(BOOL enable);
    void RCC_EnableTIM21(BOOL enable);
    void RCC_EnableTIM22(BOOL enable);
    void RCC_EnableFW(BOOL enable);
    void RCC_EnableADC(BOOL enable);
    void RCC_EnableSPI1(BOOL enable);
    void RCC_EnableUSART1(BOOL enable);
    void RCC_EnableDBG(BOOL enable);


    
    void RCC_EnableClockSecurity(BOOL enable);

#ifdef __cplusplus
}
#endif

#endif
