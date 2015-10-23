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

//7.3.1. CCR: clock control register: set clock type: HSI/HSE/PLL 
#define RCC_CR  (*(volatile uint32_t*)(RCC_BASE))

#define RCC_CR_HSION  (1<<0) 
#define RCC_CR_HSIRDY (1<<1)        
#define RCC_CR_HSEON  (1<<16)        //set by sw (enable)
#define RCC_CR_HSERDY (1<<17)        //set by hw
#define RCC_CR_HSEBYP (1<<18)
#define RCC_CR_CSSON  (1<<19)
#define RCC_CR_PLLON  (1<<24)        //set by sw (enable)
#define RCC_CR_PLLRDY (1<<25)        //set by hw

//7.3.2. CFGR: PLL src/mul, prescalers, clock output
#define RCC_CFGR  (*(volatile uint32_t*)(RCC_BASE + 0x4))

//clock source
#define RCC_CFGR_SW_HSI      (0<<0)
#define RCC_CFGR_SW_HSE      (1<<0)
#define RCC_CFGR_SW_PLL      (2<<0)
#define RCC_CFGR_SW_CLEARMASK    (3<<0)

#define RCC_CFGR_SWS_HSI      (0<<2)
#define RCC_CFGR_SWS_HSE      (1<<2)
#define RCC_CFGR_SWS_PLL      (2<<2)


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

#define RCC_CFGR_PLLSRC_HSI_DIV2    (0<<16)
#define RCC_CFGR_PLLSRC_PREDIV1     (1<<16)
#define RCC_CFGR_PLLSRC_HSE         (1<<16)
#define RCC_CFGR_PLLSRC_CLEARMASK   (1<<16)

#define RCC_CFGR_PLLXTPRE      (1<<17)

#define RCC_CFGR_PLL_MUL2  (0<<18)   
#define RCC_CFGR_PLL_MUL3  (1<<18)
#define RCC_CFGR_PLL_MUL4  (2<<18)  
#define RCC_CFGR_PLL_MUL5  (3<<18)  
#define RCC_CFGR_PLL_MUL6  (4<<18)  
#define RCC_CFGR_PLL_MUL7  (5<<18)  
#define RCC_CFGR_PLL_MUL8  (6<<18)
#define RCC_CFGR_PLL_MUL9  (7<<18)  
#define RCC_CFGR_PLL_MUL10 (8<<18)  
#define RCC_CFGR_PLL_MUL11 (9<<18)  
#define RCC_CFGR_PLL_MUL12 (10<<18)
#define RCC_CFGR_PLL_MUL13 (11<<18)
#define RCC_CFGR_PLL_MUL14 (12<<18)
#define RCC_CFGR_PLL_MUL15 (13<<18)
#define RCC_CFGR_PLL_MUL16 (14<<18)
#define RCC_CFGR_PLL_CLEARMASK (14<<18)

//0xx: no clock, 100: sysclk, 101: HSI, 110: HSE, 111: PLL/2
#define MCO_OFF       (0<<24)
#define MCO_SYSCLK    (4<<24)
#define MCO_HSI       (5<<24)
#define MCO_HSE       (6<<24)
#define MCO_PLL_DIV2  (7<<24)
#define MCO_CLEARMASK (7<<24)


#define RCC_APB2RSTR  (*(volatile uint32_t*)(RCC_BASE + 0xc))
#define RCC_APB2RSTR_AFIORST   (1<<0)
#define RCC_APB2RSTR_GIOPARST  (1<<2)
#define RCC_APB2RSTR_GIOPBRST  (1<<3)
#define RCC_APB2RSTR_GIOPCRST  (1<<4)
#define RCC_APB2RSTR_GIOPDRST  (1<<5)
#define RCC_APB2RSTR_GIOPERST  (1<<6)
#define RCC_APB2RSTR_GIOPFRST  (1<<7)
#define RCC_APB2RSTR_GIOPGRST  (1<<8)
#define RCC_APB2RSTR_ADC1RST   (1<<9)
#define RCC_APB2RSTR_ADC2RST   (1<<10)
#define RCC_APB2RSTR_TIM1RST   (1<<11)
#define RCC_APB2RSTR_SPI1RST   (1<<12)
#define RCC_APB2RSTR_TIM8RST   (1<<13)
#define RCC_APB2RSTR_USART1RST (1<<14)
#define RCC_APB2RSTR_ADC3RST   (1<<15)

//100x vl
#define RCC_APB2RSTR_TIM15RST  (1<<16)
#define RCC_APB2RSTR_TIM16RST  (1<<17)
#define RCC_APB2RSTR_TIM17RST  (1<<18)

#define RCC_APB2RSTR_TIM9RST  (1<<19)
#define RCC_APB2RSTR_TIM10RST (1<<20)
#define RCC_APB2RSTR_TIM11RST (1<<21)

#define RCC_APB1RSTR  (*(volatile uint32_t*)(RCC_BASE + 0x10))

#define RCC_APB1RSTR_TIM2RST  (1<<0)
#define RCC_APB1RSTR_TIM3RST  (1<<1)
#define RCC_APB1RSTR_TIM4RST  (1<<2)
#define RCC_APB1RSTR_TIM5RST  (1<<3)
#define RCC_APB1RSTR_TIM6RST  (1<<4)
#define RCC_APB1RSTR_TIM7RST  (1<<5)
#define RCC_APB1RSTR_TIM12RST (1<<6)
#define RCC_APB1RSTR_TIM13RST (1<<7)
#define RCC_APB1RSTR_TIM14RST (1<<8)
#define RCC_APB1RSTR_WWDGRST (1<<11)
#define RCC_APB1RSTR_SPI2RST (1<<14)
#define RCC_APB1RSTR_SPI3RST (1<<15)
#define RCC_APB1RSTR_USART2RST (1<<17)
#define RCC_APB1RSTR_USART3RST (1<<18)
#define RCC_APB1RSTR_UART4RST (1<<19)
#define RCC_APB1RSTR_UART5RST (1<<20)
#define RCC_APB1RSTR_I2C1RST (1<<21)
#define RCC_APB1RSTR_I2C2RST (1<<22)
#define RCC_APB1RSTR_USBRST (1<<23)
#define RCC_APB1RSTR_CANRST (1<<25)
#define RCC_APB1RSTR_BKPRST   (1<<27) 
#define RCC_APB1RSTR_PWRRST   (1<<28)
#define RCC_APB1RSTR_DACRST   (1<<29) 
#define RCC_APB1RSTR_CECRST   (1<<30) 


#define RCC_AHBENR  (*(volatile uint32_t*)(RCC_BASE + 0x14))
#define RCC_AHBENR_DMA1EN   (1<<0)
#define RCC_AHBENR_DMA2EN   (1<<1)
#define RCC_AHBENR_SRAMEN   (1<<2)
#define RCC_AHBENR_FLITFEN  (1<<4)
#define RCC_AHBENR_CRCEN    (1<<6)
#define RCC_AHBENR_FSMCEN   (1<<8)
#define RCC_AHBENR_SDIOEN   (1<<10)
#define RCC_AHBENR_OTGFSEN   (1<<12)
#define RCC_AHBENR_ETHMACEN   (1<<14)
#define RCC_AHBENR_ETHMACTXEN   (1<<15)
#define RCC_AHBENR_ETHMACRXEN   (1<<16)

#define RCC_APB2ENR  (*(volatile uint32_t*)(RCC_BASE + 0x18))

#define RCC_APB2ENR_AFIOEN   (1<<0)
#define RCC_APB2ENR_IOPAEN  (1<<2)
#define RCC_APB2ENR_IOPBEN  (1<<3)
#define RCC_APB2ENR_IOPCEN  (1<<4)
#define RCC_APB2ENR_IOPDEN  (1<<5)
#define RCC_APB2ENR_IOPEEN  (1<<6)
#define RCC_APB2ENR_IOPFEN  (1<<7)
#define RCC_APB2ENR_IOPGEN  (1<<8)
#define RCC_APB2ENR_ADC1EN   (1<<9)
#define RCC_APB2ENR_ADC2EN   (1<<10)
#define RCC_APB2ENR_TIM1EN   (1<<11)
#define RCC_APB2ENR_SPI1EN   (1<<12)
#define RCC_APB2ENR_TIM8EN   (1<<13)
#define RCC_APB2ENR_USART1EN (1<<14)
#define RCC_APB2ENR_ADC3EN   (1<<15)

//100x vl
#define RCC_APB2ENR_TIM15EN  (1<<16)
#define RCC_APB2ENR_TIM16EN  (1<<17)
#define RCC_APB2ENR_TIM17EN  (1<<18)

#define RCC_APB2ENR_TIM9EN  (1<<19)
#define RCC_APB2ENR_TIM10EN (1<<20)
#define RCC_APB2ENR_TIM11EN (1<<21)


#define RCC_APB1ENR  (*(volatile uint32_t*)(RCC_BASE + 0x1c))

#define RCC_APB1ENR_TIM2EN  (1<<0)
#define RCC_APB1ENR_TIM3EN  (1<<1)
#define RCC_APB1ENR_TIM4EN  (1<<2)
#define RCC_APB1ENR_TIM5EN  (1<<3)
#define RCC_APB1ENR_TIM6EN  (1<<4)
#define RCC_APB1ENR_TIM7EN  (1<<5)
#define RCC_APB1ENR_TIM12EN (1<<6)
#define RCC_APB1ENR_TIM13EN (1<<7)
#define RCC_APB1ENR_TIM14EN (1<<8)
#define RCC_APB1ENR_WWDGEN (1<<11)
#define RCC_APB1ENR_SPI2EN (1<<14)
#define RCC_APB1ENR_SPI3EN (1<<15)
#define RCC_APB1ENR_USART2EN (1<<17)
#define RCC_APB1ENR_USART3EN (1<<18)
#define RCC_APB1ENR_UART4EN (1<<19)
#define RCC_APB1ENR_UART5EN (1<<20)
#define RCC_APB1ENR_I2C1EN (1<<21)
#define RCC_APB1ENR_I2C2EN (1<<22)
#define RCC_APB1ENR_USBEN (1<<23)
#define RCC_APB1ENR_CANEN (1<<25)
#define RCC_APB1ENR_BKPEN   (1<<27) 
#define RCC_APB1ENR_PWREN   (1<<28)
#define RCC_APB1ENR_DACEN   (1<<29) 
#define RCC_APB1ENR_CECEN   (1<<30)

#define RCC_BDCR  (*(volatile uint32_t*)(RCC_BASE + 0x20))
#define RCC_BDCR_LSEON  (1<<0)         //set by sw (enable)
#define RCC_BDCR_LSERDY (1<<1)         //set by hw


#define RCC_BDCR_RTC_NOCLK        (0<<8)
#define RCC_BDCR_RTC_LSE          (1<<8)
#define RCC_BDCR_RTC_LSI          (2<<8)
#define RCC_BDCR_RTC_HSE128       (3<<8)
#define RCC_BDCR_RTC_CLEARMASK    (3<<8)

#define RCC_BDCR_RTCEN   (1<<15)    
#define RCC_BDCR_BDRST   (1<<16)   //1: resets the entire backup domain

//7.3.10. Control/status register 
#define RCC_CSR  (*(volatile uint32_t*)(RCC_BASE + 0x24))

#define RCC_CSR_LSION  (1<<0)         //set by sw (enable)
#define RCC_CSR_LSIRDY (1<<1)         //set by hw

//HSE prescaler  for f100xx and f10x connectivity
#define RCC_CFGR2  (*(volatile uint32_t*)(RCC_BASE + 0x2c))
#define RCC_CFGR2_PREDIV1_DIV1   0
#define RCC_CFGR2_PREDIV1_DIV2   1
#define RCC_CFGR2_PREDIV1_DIV3   2
#define RCC_CFGR2_PREDIV1_DIV4   3
#define RCC_CFGR2_PREDIV1_DIV5   4
#define RCC_CFGR2_PREDIV1_DIV6   5
#define RCC_CFGR2_PREDIV1_DIV7   6
#define RCC_CFGR2_PREDIV1_DIV8   7
#define RCC_CFGR2_PREDIV1_DIV9   8
#define RCC_CFGR2_PREDIV1_DIV10  9
#define RCC_CFGR2_PREDIV1_DIV11  10
#define RCC_CFGR2_PREDIV1_DIV12  11
#define RCC_CFGR2_PREDIV1_DIV13  12
#define RCC_CFGR2_PREDIV1_DIV14  13
#define RCC_CFGR2_PREDIV1_DIV15  14
#define RCC_CFGR2_PREDIV1_DIV16  15
#define RCC_CFGR2_PREDIV1_CLEARMASK 15

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
    
    
    void RCC_SetADCPrescalerDiv2 (void); 

    void RCC_SetADCPrescalerDiv4 (void); 
    void RCC_SetADCPrescalerDiv6 (void); 
   
    
    void RCC_SetADCPrescalerDiv8 (void); 
    
    
    void RCC_EnableHSI(BOOL enable);
    void RCC_EnableHSE(BOOL enable);
    void RCC_EnablePLL(uint8_t pllm_mul);
    void RCC_DisablePLL(void);

    void RCC_BypassHSE(BOOL bypassHSE);


    void RCC_EnableLSI(void);
    void RCC_EnableLSE(void);

    BOOL RCC_IsEnabledHSE(void);
    BOOL RCC_IsEnabledHSI(void);
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
    void RCC_SetRTCClockSourceHSE_DIV128(void);
    void RCC_SetRTCClockSourceOFF(void);

    void RCC_ResetBKP(BOOL enable);

    //AHB
    void RCC_EnableDMA1(BOOL enable);
    BOOL RCC_IsEnabledDMA1(void);
    void RCC_EnableDMA2(BOOL enable);
    BOOL RCC_IsEnabledDMA2(void);
    void RCC_EnableSRAM(BOOL enable);
    BOOL RCC_IsEnabledSRAM(void);
    void RCC_EnableFLITF(BOOL enable);
    BOOL RCC_IsEnabledFLITF(void);
    void RCC_EnableCRC(BOOL enable);
    BOOL RCC_IsEnabledCRC(void);
    void RCC_EnableFSMC(BOOL enable);
    BOOL RCC_IsEnabledFSMC(void);
    void RCC_EnableSDIO(BOOL enable);
    BOOL RCC_IsEnabledSDIO(void);
    //Connectivity
    void RCC_EnableOTGFS(BOOL enable);
    BOOL RCC_IsEnabledOTGFS(void);
    void RCC_EnableETHMAC(BOOL enable);
    BOOL RCC_IsEnabledETHMAC(void);
    void RCC_EnableETHMACTX(BOOL enable);
    BOOL RCC_IsEnabledETHMACTX(void);
    void RCC_EnableETHMACRX(BOOL enable);
    BOOL RCC_IsEnabledETHMACRX(void);

    //APB1
    void RCC_EnableTIM2(BOOL enable);
    BOOL RCC_IsEnabledTIM2(void);
    void RCC_EnableTIM3(BOOL enable);
    BOOL RCC_IsEnabledTIM3(void);
    void RCC_EnableTIM4(BOOL enable);
    BOOL RCC_IsEnabledTIM4(void);
    void RCC_EnableTIM5(BOOL enable);
    BOOL RCC_IsEnabledTIM5(void);
    void RCC_EnableTIM6(BOOL enable);
    BOOL RCC_IsEnabledTIM6(void);
    void RCC_EnableTIM7(BOOL enable);
    BOOL RCC_IsEnabledTIM7(void);
    void RCC_EnableTIM12(BOOL enable);
    BOOL RCC_IsEnabledTIM12(void);
    void RCC_EnableTIM13(BOOL enable);
    BOOL RCC_IsEnabledTIM13(void);
    void RCC_EnableTIM14(BOOL enable);
    BOOL RCC_IsEnabledTIM14(void);
    void RCC_EnableWWDG(BOOL enable);
    BOOL RCC_IsEnabledWWDG(void);
    void RCC_EnableSPI2(BOOL enable);
    void RCC_EnableSPI3(BOOL enable);
    BOOL RCC_IsEnabledSPI2(void);
    BOOL RCC_IsEnabledSPI3(void);
    void RCC_EnableUSART2(BOOL enable);
    void RCC_EnableUSART3(BOOL enable);
    void RCC_EnableUART4(BOOL enable);
    void RCC_EnableUART5(BOOL enable);
    BOOL RCC_IsEnabledUSART2(void);
    BOOL RCC_IsEnabledUSART3(void);
    BOOL RCC_IsEnabledUART4(void);
    BOOL RCC_IsEnabledUART5(void);
    void RCC_EnableI2C1(BOOL enable);
    void RCC_EnableI2C2(BOOL enable);
    BOOL RCC_IsEnabledI2C1(void);
    BOOL RCC_IsEnabledI2C2(void);
    void RCC_EnableUSB(BOOL enable);
    BOOL RCC_IsEnabledUSB(void);
    void RCC_EnableCAN(BOOL enable);
    BOOL RCC_IsEnabledCAN(void);
    void RCC_EnableBKP(BOOL enable);
    BOOL RCC_IsEnabledBKP(void);
    void RCC_EnablePWR(BOOL enable);
    BOOL RCC_IsEnabledPWR(void);
    void RCC_EnableDAC(BOOL enable);
    BOOL RCC_IsEnabledDAC(void);
    void RCC_EnableCEC(BOOL enable);
    BOOL RCC_IsEnabledCEC(void);

    //APB2
    void RCC_EnableAFIO(BOOL enable);
    BOOL RCC_IsEnabledAFIO(void);
    void RCC_EnableGPIOA(BOOL enable);
    void RCC_EnableGPIOB(BOOL enable);
    void RCC_EnableGPIOC(BOOL enable);
    void RCC_EnableGPIOD(BOOL enable);
    void RCC_EnableGPIOE(BOOL enable);
    void RCC_EnableGPIOF(BOOL enable);
    void RCC_EnableGPIOG(BOOL enable);
    BOOL RCC_IsEnabledGPIOA(void);
    BOOL RCC_IsEnabledGPIOB(void);
    BOOL RCC_IsEnabledGPIOC(void);
    BOOL RCC_IsEnabledGPIOD(void);
    BOOL RCC_IsEnabledGPIOE(void);
    BOOL RCC_IsEnabledGPIOF(void);
    BOOL RCC_IsEnabledGPIOG(void);
    void RCC_EnableADC1(BOOL enable);
    void RCC_EnableADC2(BOOL enable);
    BOOL RCC_IsEnabledADC1(void);
    BOOL RCC_IsEnabledADC2(void);
    void RCC_EnableTIM1(BOOL enable);
    BOOL RCC_IsEnabledTIM1(void);
    void RCC_EnableSPI1(BOOL enable);
    BOOL RCC_IsEnabledSPI1(void);
    void RCC_EnableTIM8(BOOL enable);
    BOOL RCC_IsEnabledSTIM8(void);
    void RCC_EnableUSART1(BOOL enable);
    BOOL RCC_IsEnabledUSART1(void);
    void RCC_EnableADC3(BOOL enable);
    BOOL RCC_IsEnabledADC3(void);
    void RCC_EnableTIM9(BOOL enable);
    BOOL RCC_IsEnabledTIM9(void);
    void RCC_EnableTIM10(BOOL enable);
    BOOL RCC_IsEnabledTIM10(void);
    void RCC_EnableTIM11(BOOL enable);
    BOOL RCC_IsEnabledTIM11(void);
    //value line:
    void RCC_EnableTIM15(BOOL enable);
    BOOL RCC_IsEnabledTIM15(void);
    void RCC_EnableTIM16(BOOL enable);
    BOOL RCC_IsEnabledTIM16(void);
    void RCC_EnableTIM17(BOOL enable);
    BOOL RCC_IsEnabledTIM17(void);

    void RCC_EnableClockSecurity(BOOL enable);

#ifdef __cplusplus
}
#endif

#endif
