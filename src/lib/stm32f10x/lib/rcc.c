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



#include "rcc.h"


static uint16_t t_presc[] = { 2, 4, 8, 16, 64, 128, 256, 512 };
static uint32_t _system_clock_freq;

#ifdef __cplusplus
extern "C"
{
#endif

    
uint32_t GetSystemClock(void) { return _system_clock_freq; } 


uint32_t RCC_GetAHB_CLK(void)
{
  uint32_t sysclk = GetSystemClock();
  uint16_t ahb_div = ((RCC_CFGR >> 4) & 0xf);

  if ((ahb_div & 0x8) == 0)
  {
      ahb_div = 1;
  }
  else
  {
    ahb_div = t_presc[ahb_div - 8];
  }

  return sysclk / ahb_div;

}

uint16_t RCC_GetAPBx_div(uint8_t offset)
{

  uint16_t apbx_div = ((RCC_CFGR >> offset) & 0x7);

  if ((apbx_div & 0x4) == 0)
  {
      apbx_div = 1;
  }
  else
  {
    apbx_div = t_presc[apbx_div - 4];
  }

  return apbx_div;

}


uint32_t RCC_GetAPB1_CLK(void)
{
  uint32_t ahb_clk = RCC_GetAHB_CLK();
  uint16_t apb1_div = RCC_GetAPBx_div(8);
  return ahb_clk / apb1_div;
}

uint32_t RCC_GetAPB2_CLK(void)
{
  uint32_t ahb_clk = RCC_GetAHB_CLK();
  uint16_t apb2_div = RCC_GetAPBx_div(11);
  return ahb_clk / apb2_div;
}

uint32_t RCC_GetTIMx_CLK(BOOL isAPB1)
{
  uint32_t ahb_clk = RCC_GetAHB_CLK();
  uint16_t apbx_div;
  if (isAPB1)
  {
      apbx_div = RCC_GetAPBx_div(8);
  }
  else
  {
      apbx_div = RCC_GetAPBx_div(11);
  }

  uint32_t timx_clk = ahb_clk / apbx_div;
  if (apbx_div > 1)
  {
      timx_clk *= 2;
  }
    
  return timx_clk;
}

uint32_t RCC_GetRTC_CLK(void)
{
    if ((RCC_BDCR & RCC_BDCR_RTC_LSE) ||
        (RCC_BDCR & RCC_BDCR_RTC_LSI))
    {
        return 32768;
    }
    else if (RCC_BDCR & RCC_BDCR_RTC_HSE128)
    {
        return HSE_CLOCK_FREQ / 128;
    }
    else
    {
        return 0;
    }
}

void RCC_Delay_us(uint32_t us)
{
  //uint64_t cnt = (uint64_t)_system_clock_freq  * (uint64_t)us / 6000000ull;
  uint64_t ahb_clk = (uint64_t)RCC_GetAHB_CLK();  
//  uint64_t cnt = (uint64_t)RCC_GetAHB_CLK() * (uint64_t)us / 6000000ull;
  uint64_t cnt = ahb_clk * (uint64_t)us / 6000000ull;
  uint64_t i;
  for (i = 0; i < cnt; ++i)
  {
  }
}


void RCC_Delay_ms(uint32_t ms)
{
  RCC_Delay_us (ms * 1000);
}


void RCC_ResetBKP(BOOL enable)
{
    if (enable)
        RCC_BDCR |= RCC_BDCR_BDRST;
    else
        RCC_BDCR &= ~RCC_BDCR_BDRST;

}

void RCC_SetRTCClockSourceLSE(void)
{
    RCC_BDCR &= ~RCC_BDCR_RTC_CLEARMASK;
    RCC_BDCR |= RCC_BDCR_RTC_LSE;
}
void RCC_SetRTCClockSourceLSI(void)
{
    RCC_BDCR &= ~RCC_BDCR_RTC_CLEARMASK;
    RCC_BDCR |= RCC_BDCR_RTC_LSI;
}
void RCC_SetRTCClockSourceHSE_DIV128(void)
{
    RCC_BDCR &= ~RCC_BDCR_RTC_CLEARMASK;
    RCC_BDCR |= RCC_BDCR_RTC_HSE128;
}

void RCC_SetRTCClockSourceOFF(void)
{
    RCC_BDCR &= ~RCC_BDCR_RTC_CLEARMASK;
    RCC_BDCR &= ~RCC_BDCR_RTCEN;
}

void RCC_EnableRTC(BOOL enable)
{
    if (enable)
    {
        RCC_BDCR |= RCC_BDCR_RTCEN;
    }
    else
    {
        RCC_BDCR &= ~RCC_BDCR_RTCEN;
    }
}


////////////// HSI ///////////////////////
//static void RCC_ResetHSI(void)
//{
//    RCC_CR &= ~RCC_CR_HSION;
//    while ((RCC_CR & (RCC_CR_HSIRDY)))
//        ;
//
//}
static void RCC_StartHSI(void)
{
    RCC_CR |= RCC_CR_HSION;
    while (!(RCC_CR & (RCC_CR_HSIRDY)))
        ;

}

static BOOL RCC_IsHSIActive(void)
{
    return (RCC_CFGR & RCC_CFGR_SWS_HSI) || !(RCC_CFGR & RCC_CFGR_PLLSRC_HSE);
}


void RCC_EnableHSI(BOOL enable)
{
    if (RCC_IsHSIActive())
    {
        _system_clock_freq = 8000000;
        return;
    }

    RCC_CFGR &= ~RCC_CFGR_SW_CLEARMASK;
    if (enable)
    {
        RCC_StartHSI();
        RCC_CFGR |= RCC_CFGR_SW_HSI;
        _system_clock_freq = 8000000;
    }


}

//////////  HSE /////////////////

static void RCC_ResetHSE(void)
{
    RCC_CR &= ~RCC_CR_HSEON;
    while ((RCC_CR & (RCC_CR_HSERDY)))
        ;
}

static void RCC_StartHSE(void)
{
    RCC_CR |= RCC_CR_HSEON;
    while (!(RCC_CR & (RCC_CR_HSERDY)))
        ;

}

static BOOL RCC_IsHSEActive(void)
{
    return (RCC_CFGR & RCC_CFGR_SWS_HSE) || (RCC_CFGR & RCC_CFGR_PLLSRC_HSE);
}


void RCC_EnableHSE(BOOL enable)
{
    if (RCC_IsHSEActive())
    {
        return;
    }

    RCC_ResetHSE();
    RCC_CFGR &= ~RCC_CFGR_SW_CLEARMASK;
    if (enable)
    {
        RCC_StartHSE();
        RCC_CFGR |= RCC_CFGR_SW_HSE;
        _system_clock_freq = HSE_CLOCK_FREQ;
    }
}


void RCC_BypassHSE(BOOL bypassHSE)
{
    if (bypassHSE)
    {
        RCC_CR |= RCC_CR_HSEBYP;
    }
    else
    {
        RCC_CR &= ~RCC_CR_HSEBYP;
    }
}





void RCC_EnableLSI(void)
{
    RCC_BDCR &= ~(RCC_BDCR_LSEON | RCC_BDCR_RTC_LSE);
    RCC_BDCR |= RCC_BDCR_RTC_LSI; //LSI ~40Khz
    RCC_CSR |= RCC_CSR_LSION;

    while ((RCC_CSR & (RCC_CSR_LSIRDY)) == 0)
        ;
}

void RCC_EnableLSE(void)
{
    RCC_CSR &= ~RCC_CSR_LSION;
    RCC_BDCR &= ~RCC_BDCR_RTC_LSI;
    RCC_BDCR |= RCC_BDCR_RTC_LSE;
    RCC_BDCR |= RCC_BDCR_LSEON;

    while ((RCC_BDCR & (RCC_BDCR_LSERDY)) == 0)
       ;

}

BOOL RCC_IsEnabledHSE(void)
{
    return ((RCC_CR & RCC_CR_HSEON) &&  (RCC_CR & RCC_CR_HSERDY));
}

BOOL RCC_IsEnabledHSI(void)
{
    return ((RCC_CR & RCC_CR_HSION) &&  (RCC_CR & RCC_CR_HSIRDY));
}

BOOL RCC_IsEnabledLSE(void)
{
    return ((RCC_BDCR & RCC_BDCR_LSEON) && (RCC_BDCR & RCC_BDCR_LSERDY));
}
BOOL RCC_IsEnabledLSI(void)
{
    return ((RCC_CSR & RCC_CSR_LSION) && (RCC_CSR & RCC_CSR_LSIRDY));
}



////////////  PLL  //////////////////////

static BOOL RCC_IsPLLActive(void)
{
    return RCC_CFGR & RCC_CFGR_SWS_PLL;
}


static void RCC_ResetPLL(void)
{
    RCC_CR &= ~(RCC_CR_PLLON);

    while ((RCC_CR & (RCC_CR_PLLRDY)))
        ;
}


static void RCC_StartPLL(void)
{
    
    RCC_CR |= (RCC_CR_PLLON);

    while (!(RCC_CR & (RCC_CR_PLLRDY)))
        ;


}


void RCC_EnablePLL(uint8_t pll_mul)
{
    if (pll_mul < 2 && pll_mul>16)
    {
        return;
    }

    if (RCC_IsPLLActive())
    {
        return;
    }

    
    RCC_ResetPLL();
    RCC_CFGR &= ~RCC_CFGR_PLLSRC_CLEARMASK;

   
    if (RCC_IsHSIActive())
    {
        RCC_CFGR |= RCC_CFGR_PLLSRC_HSI_DIV2;
    }
    else if (RCC_IsHSEActive())
    {
        RCC_CFGR |= RCC_CFGR_PLLSRC_HSE;
    }

    RCC_CFGR &= ~RCC_CFGR_SW_CLEARMASK;
    RCC_CFGR |= RCC_CFGR_SW_PLL;
    RCC_CFGR |= (pll_mul - 2)<<18;
      
    RCC_StartPLL();

    if ((RCC_CR & RCC_CR_HSION) ||  
        ((RCC_CR & RCC_CR_HSEON) && (RCC_CFGR & RCC_CFGR_PLLXTPRE))) 
    {
      _system_clock_freq /= 2;
    }
  
    _system_clock_freq *= pll_mul;
    
}



void RCC_EnableDAC(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_DACRST;
        RCC_APB1ENR |= RCC_APB1ENR_DACEN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_DACRST;
        RCC_APB1ENR &= ~RCC_APB1ENR_DACEN;
    }
}

BOOL RCC_IsEnabledDAC(void)
{
    return RCC_APB1ENR & RCC_APB1ENR_DACEN;
}


void EnableCEC(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_CECRST;
        RCC_APB1ENR |= RCC_APB1ENR_CECEN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_CECRST;
        RCC_APB1ENR &= ~RCC_APB1ENR_CECEN;
    }

}
BOOL IsEnabledCEC(void)
{
    return RCC_APB1ENR & RCC_APB1ENR_CECEN;
}


void RCC_EnableADC1(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_ADC1RST;
        RCC_APB2ENR |= RCC_APB2ENR_ADC1EN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_ADC1RST;
        RCC_APB2ENR &= ~RCC_APB2ENR_ADC1EN;
    }
}


void RCC_EnableADC2(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_ADC2RST;
        RCC_APB2ENR |= RCC_APB2ENR_ADC2EN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_ADC2RST;
        RCC_APB2ENR &= ~RCC_APB2ENR_ADC2EN;
    }
}

void RCC_EnableADC3(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_ADC3RST;
        RCC_APB2ENR |= RCC_APB2ENR_ADC3EN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_ADC3RST;
        RCC_APB2ENR &= ~RCC_APB2ENR_ADC3EN;
    }
}

BOOL RCC_IsEnabledADC1(void)
{
    return RCC_APB2ENR & RCC_APB2ENR_ADC1EN;
}
BOOL RCC_IsEnabledADC2(void)
{
    return RCC_APB2ENR & RCC_APB2ENR_ADC2EN;
}
BOOL RCC_IsEnabledADC3(void)
{
    return RCC_APB2ENR & RCC_APB2ENR_ADC3EN;
}



void RCC_EnableSPI1(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;
        RCC_APB2ENR |= RCC_APB2ENR_SPI1EN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_SPI1RST;
        RCC_APB2ENR &= ~RCC_APB2ENR_SPI1EN;
    }

}
void RCC_EnableSPI2(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_SPI2RST;
        RCC_APB1ENR |= RCC_APB1ENR_SPI2EN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_SPI2RST;
        RCC_APB1ENR &= ~RCC_APB1ENR_SPI2EN;
    }

}
void RCC_EnableSPI3(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_SPI3RST;
        RCC_APB1ENR |= RCC_APB1ENR_SPI3EN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_SPI3RST;
        RCC_APB1ENR &= ~RCC_APB1ENR_SPI3EN;
    }

}

BOOL RCC_IsEnabledSPI1(void)
{
    return RCC_APB2ENR & RCC_APB2ENR_SPI1EN;
}

BOOL RCC_IsEnabledSPI2(void)
{
    return RCC_APB1ENR & RCC_APB1ENR_SPI2EN;
}

BOOL RCC_IsEnabledSPI3(void)
{
    return RCC_APB1ENR & RCC_APB1ENR_SPI3EN;
}

void RCC_EnableUSART1(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_USART1RST;
        RCC_APB2ENR |= RCC_APB2ENR_USART1EN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_USART1RST;
        RCC_APB2ENR &= ~RCC_APB2ENR_USART1EN;
    }

}
void RCC_EnableUSART2(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_USART2RST;
        RCC_APB1ENR |= RCC_APB1ENR_USART2EN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_USART2RST;
        RCC_APB1ENR &= ~RCC_APB1ENR_USART2EN;
    }

}
void RCC_EnableUSART3(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_USART3RST;
        RCC_APB1ENR |= RCC_APB1ENR_USART3EN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_USART3RST;
        RCC_APB1ENR &= ~RCC_APB1ENR_USART3EN;
    }

}

BOOL RCC_IsEnabledUSART1(void)
{
    return RCC_APB2ENR & RCC_APB2ENR_USART1EN;
}
BOOL RCC_IsEnabledUSART2(void)
{
    return RCC_APB1ENR & RCC_APB1ENR_USART2EN;
}
BOOL RCC_IsEnabledUSART3(void)
{
    return RCC_APB1ENR & RCC_APB1ENR_USART3EN;
}


void RCC_EnableGPIOA(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_GIOPARST;
        RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_GIOPARST;
        RCC_APB2ENR &= ~RCC_APB2ENR_IOPAEN;
    }

}

void RCC_EnableGPIOB(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_GIOPBRST;
        RCC_APB2ENR |= RCC_APB2ENR_IOPBEN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_GIOPBRST;
        RCC_APB2ENR &= ~RCC_APB2ENR_IOPBEN;
    }

}

void RCC_EnableGPIOC(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_GIOPCRST;
        RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_GIOPDRST;
        RCC_APB2ENR &= ~RCC_APB2ENR_IOPDEN;
    }

}

void RCC_EnableGPIOD(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_GIOPDRST;
        RCC_APB2ENR |= RCC_APB2ENR_IOPDEN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_GIOPDRST;
        RCC_APB2ENR &= ~RCC_APB2ENR_IOPDEN;
    }

}


void RCC_EnableGPIOE(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_GIOPERST;
        RCC_APB2ENR |= RCC_APB2ENR_IOPEEN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_GIOPERST;
        RCC_APB2ENR &= ~RCC_APB2ENR_IOPEEN;
    }

}

void RCC_EnableGPIOF(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_GIOPFRST;
        RCC_APB2ENR |= RCC_APB2ENR_IOPFEN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_GIOPFRST;
        RCC_APB2ENR &= ~RCC_APB2ENR_IOPFEN;
    }

}


void RCC_EnableGPIOG(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_GIOPGRST;
        RCC_APB2ENR |= RCC_APB2ENR_IOPGEN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_GIOPGRST;
        RCC_APB2ENR &= ~RCC_APB2ENR_IOPGEN;
    }

}

BOOL RCC_IsEnabledGPIOA(void)
{
    return RCC_APB2ENR & RCC_APB2ENR_IOPAEN;
}
BOOL RCC_IsEnabledGPIOB(void)
{
    return RCC_APB2ENR & RCC_APB2ENR_IOPBEN;
}
BOOL RCC_IsEnabledGPIOC(void)
{
    return RCC_APB2ENR & RCC_APB2ENR_IOPCEN;
}
BOOL RCC_IsEnabledGPIOD(void)
{
    return RCC_APB2ENR & RCC_APB2ENR_IOPDEN;
}
BOOL RCC_IsEnabledGPIOE(void)
{
    return RCC_APB2ENR & RCC_APB2ENR_IOPEEN;
}
BOOL RCC_IsEnabledGPIOF(void)
{
    return RCC_APB2ENR & RCC_APB2ENR_IOPFEN;
}
BOOL RCC_IsEnabledGPIOG(void)
{
    return RCC_APB2ENR & RCC_APB2ENR_IOPGEN;
}

void RCC_EnableI2C1(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_I2C1RST;
        RCC_APB1ENR |= RCC_APB1ENR_I2C1EN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_I2C1RST;
        RCC_APB1ENR &= ~RCC_APB1ENR_I2C1EN;
    }

}

void RCC_EnableI2C2(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_I2C2RST;
        RCC_APB1ENR |= RCC_APB1ENR_I2C2EN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_I2C2RST;
        RCC_APB1ENR &= ~RCC_APB1ENR_I2C2EN;
    }

}

BOOL RCC_IsEnabledI2C1(void)
{
    return RCC_APB1ENR & RCC_APB1ENR_I2C1EN;
}
BOOL RCC_IsEnabledI2C2(void)
{
    return RCC_APB1ENR & RCC_APB1ENR_I2C2EN;
}

void RCC_EnableDMA1(BOOL enable)
{
    if (enable)
    {
        RCC_AHBENR |= RCC_AHBENR_DMA1EN;
    }
    else
    {
        RCC_AHBENR &= ~RCC_AHBENR_DMA1EN;
    }

}
void RCC_EnableDMA2(BOOL enable)
{
    if (enable)
    {
        RCC_AHBENR |= RCC_AHBENR_DMA2EN;
    }
    else
    {
        RCC_AHBENR &= ~RCC_AHBENR_DMA2EN;
    }

}

BOOL RCC_IsEnabledDMA1(void)
{
    return RCC_AHBENR & RCC_AHBENR_DMA1EN;
}
BOOL RCC_IsEnabledDMA2(void)
{
    return RCC_AHBENR & RCC_AHBENR_DMA2EN;
}

void RCC_EnableSRAM(BOOL enable)
{
    if (enable)
    {
        RCC_AHBENR |= RCC_AHBENR_SRAMEN;
    }
    else
    {
        RCC_AHBENR &= ~RCC_AHBENR_SRAMEN;
    }

}
BOOL RCC_IsEnabledSRAM(void)
{
    return (RCC_AHBENR & RCC_AHBENR_SRAMEN);
}

void RCC_EnableFLITF(BOOL enable)
{
    if (enable)
    {
        RCC_AHBENR |= RCC_AHBENR_FLITFEN;
    }
    else
    {
        RCC_AHBENR &= ~RCC_AHBENR_FLITFEN;
    }
}
BOOL RCC_IsEnabledFLITF(void)
{
    return (RCC_AHBENR & RCC_AHBENR_FLITFEN);
}
void RCC_EnableCRC(BOOL enable)
{
    if (enable)
    {
        RCC_AHBENR |= RCC_AHBENR_CRCEN;
    }
    else
    {
        RCC_AHBENR &= ~RCC_AHBENR_CRCEN;
    }
}
BOOL RCC_IsEnabledCRC(void)
{
    return (RCC_AHBENR & RCC_AHBENR_CRCEN);
}
void RCC_EnableFSMC(BOOL enable)
{
    if (enable)
    {
        RCC_AHBENR |= RCC_AHBENR_FSMCEN;
    }
    else
    {
        RCC_AHBENR &= ~RCC_AHBENR_FSMCEN;
    }
}
BOOL RCC_IsEnabledFSMC(void)
{
    return (RCC_AHBENR & RCC_AHBENR_FSMCEN);
}
void RCC_EnableSDIO(BOOL enable)
{
    if (enable)
    {
        RCC_AHBENR |= RCC_AHBENR_SDIOEN;
    }
    else
    {
        RCC_AHBENR &= ~RCC_AHBENR_SDIOEN;
    }
}
BOOL RCC_IsEnabledSDIO(void)
{
    return (RCC_AHBENR & RCC_AHBENR_SDIOEN);
}

//Connectivity
void RCC_EnableOTGFS(BOOL enable)
{
    if (enable)
    {
        RCC_AHBENR |= RCC_AHBENR_OTGFSEN;
    }
    else
    {
        RCC_AHBENR &= ~RCC_AHBENR_OTGFSEN;
    }

}
BOOL RCC_IsEnabledOTGFS(void)
{
    return (RCC_AHBENR & RCC_AHBENR_OTGFSEN);
}
void RCC_EnableETHMAC(BOOL enable)
{
    if (enable)
    {
        RCC_AHBENR |= RCC_AHBENR_ETHMACEN;
    }
    else
    {
        RCC_AHBENR &= ~RCC_AHBENR_ETHMACEN;
    }
}
BOOL RCC_IsEnabledETHMAC(void)
{
    return (RCC_AHBENR & RCC_AHBENR_ETHMACEN);
}

void RCC_EnableETHMACTX(BOOL enable)
{
    if (enable)
    {
        RCC_AHBENR |= RCC_AHBENR_ETHMACTXEN;
    }
    else
    {
        RCC_AHBENR &= ~RCC_AHBENR_ETHMACTXEN;
    }

}
BOOL RCC_IsEnabledETHMACTX(void)
{
    return (RCC_AHBENR & RCC_AHBENR_ETHMACTXEN);
}

void RCC_EnableETHMACRX(BOOL enable)
{
    if (enable)
    {
        RCC_AHBENR |= RCC_AHBENR_ETHMACRXEN;
    }
    else
    {
        RCC_AHBENR &= ~RCC_AHBENR_ETHMACRXEN;
    }

}
BOOL RCC_IsEnabledETHMACRX(void)
{
    return (RCC_AHBENR & RCC_AHBENR_ETHMACRXEN);
}


void RCC_EnableTIM2(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_TIM2RST;
        RCC_APB1ENR |= RCC_APB1ENR_TIM2EN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_TIM2RST;
        RCC_APB1ENR &= ~RCC_APB1ENR_TIM2EN;
    }

}
BOOL RCC_IsEnabledTIM2(void)
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM2EN);
}
void RCC_EnableTIM3(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_TIM3RST;
        RCC_APB1ENR |= RCC_APB1ENR_TIM3EN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_TIM3RST;
        RCC_APB1ENR &= ~RCC_APB1ENR_TIM3EN;
    }

}
BOOL RCC_IsEnabledTIM3(void)
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM3EN);
}
void RCC_EnableTIM4(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_TIM4RST;
        RCC_APB1ENR |= RCC_APB1ENR_TIM4EN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_TIM4RST;
        RCC_APB1ENR &= ~RCC_APB1ENR_TIM4EN;
    }

}
BOOL RCC_IsEnabledTIM4(void)
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM4EN);
}
void RCC_EnableTIM5(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_TIM5RST;
        RCC_APB1ENR |= RCC_APB1ENR_TIM5EN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_TIM5RST;
        RCC_APB1ENR &= ~RCC_APB1ENR_TIM5EN;
    }

}
BOOL RCC_IsEnabledTIM5(void)
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM5EN);
}
void RCC_EnableTIM6(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_TIM6RST;
        RCC_APB1ENR |= RCC_APB1ENR_TIM6EN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_TIM6RST;
        RCC_APB1ENR &= ~RCC_APB1ENR_TIM6EN;
    }

}
BOOL RCC_IsEnabledTIM6(void)
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM6EN);
}
void RCC_EnableTIM7(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_TIM7RST;
        RCC_APB1ENR |= RCC_APB1ENR_TIM7EN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_TIM7RST;
        RCC_APB1ENR &= ~RCC_APB1ENR_TIM7EN;
    }
}
BOOL RCC_IsEnabledTIM7(void)
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM7EN);
}
void RCC_EnableTIM12(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_TIM12RST;
        RCC_APB1ENR |= RCC_APB1ENR_TIM12EN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_TIM12RST;
        RCC_APB1ENR &= ~RCC_APB1ENR_TIM12EN;
    }

}
BOOL RCC_IsEnabledTIM12(void)
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM12EN);
}
void RCC_EnableTIM13(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_TIM13RST;
        RCC_APB1ENR |= RCC_APB1ENR_TIM13EN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_TIM13RST;
        RCC_APB1ENR &= ~RCC_APB1ENR_TIM13EN;
    }

}
BOOL RCC_IsEnabledTIM13(void)
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM13EN);
}
void RCC_EnableTIM14(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_TIM14RST;
        RCC_APB1ENR |= RCC_APB1ENR_TIM14EN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_TIM14RST;
        RCC_APB1ENR &= ~RCC_APB1ENR_TIM14EN;
    }

}
BOOL RCC_IsEnabledTIM14(void)
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM14EN);
}
void RCC_EnableWWDG(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_WWDGRST;
        RCC_APB1ENR |= RCC_APB1ENR_WWDGEN;
    }
    else
    {
        RCC_APB1RSTR |= RCC_APB1RSTR_WWDGRST;
        RCC_APB1ENR &= ~RCC_APB1ENR_WWDGEN;
    }

}
BOOL RCC_IsEnabledWWDG(void)
{
    return (RCC_APB1ENR & RCC_APB1ENR_WWDGEN);
}

//APB2
void RCC_EnableAFIO(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_AFIORST;
        RCC_APB2ENR |= RCC_APB2ENR_AFIOEN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_AFIORST;
        RCC_APB2ENR &= ~RCC_APB2ENR_AFIOEN;
    }
}
BOOL RCC_IsEnabledAFIO(void)
{
    return (RCC_APB2ENR & RCC_APB2ENR_AFIOEN);
}

void RCC_EnableTIM1(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_TIM1RST;
        RCC_APB2ENR |= RCC_APB2ENR_TIM1EN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_TIM1RST;
        RCC_APB2ENR &= ~RCC_APB2ENR_TIM1EN;
    }
}
BOOL RCC_IsEnabledTIM1(void)
{
    return (RCC_APB2ENR & RCC_APB2ENR_TIM1EN);
}
void RCC_EnableTIM8(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_TIM8RST;
        RCC_APB2ENR |= RCC_APB2ENR_TIM8EN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_TIM8RST;
        RCC_APB2ENR &= ~RCC_APB2ENR_TIM8EN;
    }
}
BOOL RCC_IsEnabledSTIM8(void)
{
    return (RCC_APB2ENR & RCC_APB2ENR_TIM8EN);
}

void RCC_EnableTIM9(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_TIM9RST;
        RCC_APB2ENR |= RCC_APB2ENR_TIM9EN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_TIM9RST;
        RCC_APB2ENR &= ~RCC_APB2ENR_TIM9EN;
    }
}
BOOL RCC_IsEnabledTIM9(void)
{
    return (RCC_APB2ENR & RCC_APB2ENR_TIM9EN);
}
void RCC_EnableTIM10(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_TIM10RST;
        RCC_APB2ENR |= RCC_APB2ENR_TIM10EN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_TIM10RST;
        RCC_APB2ENR &= ~RCC_APB2ENR_TIM10EN;
    }
}
BOOL RCC_IsEnabledTIM10(void)
{
    return (RCC_APB2ENR & RCC_APB2ENR_TIM10EN);
}
void RCC_EnableTIM11(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_TIM11RST;
        RCC_APB2ENR |= RCC_APB2ENR_TIM11EN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_TIM11RST;
        RCC_APB2ENR &= ~RCC_APB2ENR_TIM11EN;
    }
}
BOOL RCC_IsEnabledTIM11(void)
{
    return (RCC_APB2ENR & RCC_APB2ENR_TIM11EN);
}

void RCC_EnableTIM15(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_TIM15RST;
        RCC_APB2ENR |= RCC_APB2ENR_TIM15EN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_TIM15RST;
        RCC_APB2ENR &= ~RCC_APB2ENR_TIM15EN;
    }
}
BOOL RCC_IsEnabledTIM15(void)
{
    return (RCC_APB2ENR & RCC_APB2ENR_TIM15EN);
}

void RCC_EnableTIM16(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_TIM16RST;
        RCC_APB2ENR |= RCC_APB2ENR_TIM16EN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_TIM16RST;
        RCC_APB2ENR &= ~RCC_APB2ENR_TIM16EN;
    }
}
BOOL RCC_IsEnabledTIM16(void)
{
    return (RCC_APB2ENR & RCC_APB2ENR_TIM16EN);
}

void RCC_EnableTIM17(BOOL enable)
{
    if (enable)
    {
        RCC_APB2RSTR &= ~RCC_APB2RSTR_TIM17RST;
        RCC_APB2ENR |= RCC_APB2ENR_TIM17EN;
    }
    else
    {
        RCC_APB2RSTR |= RCC_APB2RSTR_TIM17RST;
        RCC_APB2ENR &= ~RCC_APB2ENR_TIM17EN;
    }
}
BOOL RCC_IsEnabledTIM17(void)
{
    return (RCC_APB2ENR & RCC_APB2ENR_TIM17EN);
}

void RCC_EnableClockSecurity(BOOL enable)
{
    if (enable)
    {
        RCC_CR |= RCC_CR_CSSON;
    }
    else
    {
        RCC_CR &= ~RCC_CR_CSSON;
    }
}

void RCC_EnableBKP(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_BKPRST;
        RCC_APB1ENR |= RCC_APB1ENR_BKPEN;
    }
    else
    {
        RCC_APB1ENR &= ~RCC_APB1ENR_BKPEN;
        RCC_APB1RSTR |= RCC_APB1RSTR_BKPRST;
    }

}
BOOL RCC_IsEnabledBKP(void)
{
    return RCC_APB1ENR & RCC_APB1ENR_BKPEN;
}
void RCC_EnablePWR(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_PWRRST;
        RCC_APB1ENR |= RCC_APB1ENR_PWREN;
    }
    else
    {
        RCC_APB1ENR &= ~RCC_APB1ENR_PWREN;
        RCC_APB1RSTR |= RCC_APB1RSTR_PWRRST;
    }
}

BOOL RCC_IsEnabledPWR(void)
{
    return RCC_APB1ENR & RCC_APB1ENR_PWREN;
}

void RCC_EnableUSB(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_USBRST;
        RCC_APB1ENR |= RCC_APB1ENR_USBEN;
    }
    else
    {
        RCC_APB1ENR &= ~RCC_APB1ENR_USBEN;
        RCC_APB1RSTR |= RCC_APB1RSTR_USBRST;
    }
}

BOOL RCC_IsEnabledUSB(void)
{
    return RCC_APB1ENR & RCC_APB1ENR_USBEN;
}

void RCC_EnableCAN(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_CANRST;
        RCC_APB1ENR |= RCC_APB1ENR_CANEN;
    }
    else
    {
        RCC_APB1ENR &= ~RCC_APB1ENR_CANEN;
        RCC_APB1RSTR |= RCC_APB1RSTR_CANRST;
    }
}
BOOL RCC_IsEnabledCAN(void)
{
    return RCC_APB1ENR & RCC_APB1ENR_CANEN;
}

void RCC_EnableCEC(BOOL enable)
{
    if (enable)
    {
        RCC_APB1RSTR &= ~RCC_APB1RSTR_CECRST;
        RCC_APB1ENR |= RCC_APB1ENR_CECEN;
    }
    else
    {
        RCC_APB1ENR &= ~RCC_APB1ENR_CECEN;
        RCC_APB1RSTR |= RCC_APB1RSTR_CECRST;
    }
}
BOOL RCC_IsEnabledCEC(void)
{
    return RCC_APB1ENR & RCC_APB1ENR_CECEN;
}


    void RCC_SetAHBPrescalerDiv1()
    {
        RCC_CFGR &= ~RCC_CFGR_AHB_HCLK_PRE_SYSCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV1;
    }

    void RCC_SetAHBPrescalerDiv2()
    {
        RCC_CFGR &= ~RCC_CFGR_AHB_HCLK_PRE_SYSCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV2;
    }

    
    void RCC_SetAHBPrescalerDiv4()
    {
        RCC_CFGR &= ~RCC_CFGR_AHB_HCLK_PRE_SYSCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV4;
    }
    
    void RCC_SetAHBPrescalerDiv8()
    {
        RCC_CFGR &= ~RCC_CFGR_AHB_HCLK_PRE_SYSCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV8;
    }
   
    void RCC_SetAHBPrescalerDiv16()
    {
        RCC_CFGR &= ~RCC_CFGR_AHB_HCLK_PRE_SYSCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV16;
    }
    
    void RCC_SetAHBPrescalerDiv64()
    {
        RCC_CFGR &= ~RCC_CFGR_AHB_HCLK_PRE_SYSCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV64;
    }
    
    void RCC_SetAHBPrescalerDiv128()
    {
        RCC_CFGR &= ~RCC_CFGR_AHB_HCLK_PRE_SYSCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV128;
    }
   
    void RCC_SetAHBPrescalerDiv256()
    {
        RCC_CFGR &= ~RCC_CFGR_AHB_HCLK_PRE_SYSCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV256;
    }
    
    void RCC_SetAHBPrescalerDiv512()
    {
        RCC_CFGR &= ~RCC_CFGR_AHB_HCLK_PRE_SYSCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_AHB_HCLK_PRE_SYSCLK_DIV512;
    }
   
   
    void RCC_SetAPB1PrescalerDiv1 ()
    {
        RCC_CFGR &= ~RCC_CFGR_APB1_PCLK1_PRE_AHB_HCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_APB1_PCLK1_PRE_AHB_HCLK_DIV1;
    }
    
    void RCC_SetAPB1PrescalerDiv2 ()
    {
        RCC_CFGR &= ~RCC_CFGR_APB1_PCLK1_PRE_AHB_HCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_APB1_PCLK1_PRE_AHB_HCLK_DIV2;
    }
    
    void RCC_SetAPB1PrescalerDiv4 ()
    {
        RCC_CFGR &= ~RCC_CFGR_APB1_PCLK1_PRE_AHB_HCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_APB1_PCLK1_PRE_AHB_HCLK_DIV4;
    }
    
    void RCC_SetAPB1PrescalerDiv8 ()
    {
        RCC_CFGR &= ~RCC_CFGR_APB1_PCLK1_PRE_AHB_HCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_APB1_PCLK1_PRE_AHB_HCLK_DIV8;
    }
    
    
    void RCC_SetAPB1PrescalerDiv16 ()
    {
        RCC_CFGR &= ~RCC_CFGR_APB1_PCLK1_PRE_AHB_HCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_APB1_PCLK1_PRE_AHB_HCLK_DIV16;
    }

    void RCC_SetAPB2PrescalerDiv1 ()
    {
        RCC_CFGR &= ~RCC_CFGR_APB2_PCLK2_PRE_AHB_HCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_APB2_PCLK2_PRE_AHB_HCLK_DIV1;
    }
    
    void RCC_SetAPB2PrescalerDiv2 ()
    {
        RCC_CFGR &= ~RCC_CFGR_APB2_PCLK2_PRE_AHB_HCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_APB2_PCLK2_PRE_AHB_HCLK_DIV2;
    }
    
    void RCC_SetAPB2PrescalerDiv4 ()
    {
        RCC_CFGR &= ~RCC_CFGR_APB2_PCLK2_PRE_AHB_HCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_APB2_PCLK2_PRE_AHB_HCLK_DIV4;
    }
    
    void RCC_SetAPB2PrescalerDiv8 ()
    {
        RCC_CFGR &= ~RCC_CFGR_APB2_PCLK2_PRE_AHB_HCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_APB2_PCLK2_PRE_AHB_HCLK_DIV8;
    }
    
    
    void RCC_SetAPB2PrescalerDiv16 ()
    {
        RCC_CFGR &= ~RCC_CFGR_APB2_PCLK2_PRE_AHB_HCLK_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_APB2_PCLK2_PRE_AHB_HCLK_DIV16;
    }
    
    
    void RCC_SetADCPrescalerDiv2 () 
    {
        RCC_CFGR &= ~RCC_CFGR_ADCPRE_APB2_PCLK2_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_ADCPRE_APB2_PCLK2_DIV2;
    }

    void RCC_SetADCPrescalerDiv4 () 
    {
        RCC_CFGR &= ~RCC_CFGR_ADCPRE_APB2_PCLK2_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_ADCPRE_APB2_PCLK2_DIV4;
    }
    
    void RCC_SetADCPrescalerDiv6 () 
    {
        RCC_CFGR &= ~RCC_CFGR_ADCPRE_APB2_PCLK2_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_ADCPRE_APB2_PCLK2_DIV6;
    }
   
    
    void RCC_SetADCPrescalerDiv8 () 
    {
        RCC_CFGR &= ~RCC_CFGR_ADCPRE_APB2_PCLK2_CLEARMASK;
        RCC_CFGR |= RCC_CFGR_ADCPRE_APB2_PCLK2_DIV8;
    }


#ifdef __cplusplus
}
#endif
