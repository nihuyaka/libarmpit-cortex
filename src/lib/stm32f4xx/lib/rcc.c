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

#include <stdint.h>



#ifdef __cplusplus
extern "C"
{
#endif


//////////  HSI /////////////////

/*	
static void RCC_ResetHSI(void)
{
    RCC_CR &= ~RCC_CR_HSION;
    while ((RCC_CR & (RCC_CR_HSIRDY)))
        ;

}
*/
	
static void RCC_StartHSI(void)
{
    RCC_CR |= RCC_CR_HSION;
    while (!(RCC_CR & (RCC_CR_HSIRDY)))
        ;

}

static BOOL RCC_IsHSIActive(void)
{
    volatile uint32_t cfgr = RCC_CFGR;
    ((void)cfgr);
    return (RCC_CFGR & RCC_CFGR_SWS_HSI) || (RCC_PLLCFGR & RCC_PLLCFGR_PLLSRC_HSI);
}


void RCC_EnableHSI(BOOL enable)
{
    if (RCC_IsHSIActive())
    {
        return;
    }

    //RCC_CFGR &= ~RCC_CFGR_SW_CLEARMASK;
    if (enable)
    {
        RCC_StartHSI();
        RCC_CFGR |= RCC_CFGR_SW_HSI;
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
    return (RCC_CFGR & RCC_CFGR_SWS_HSE) || (RCC_PLLCFGR & RCC_PLLCFGR_PLLSRC_HSE);
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


////////////  PLL  //////////////////////

static BOOL RCC_IsPLLActive(void)
{
    return RCC_CFGR & RCC_CFGR_SWS_PLL_P;
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


void RCC_EnablePLL(uint8_t pllm, uint16_t plln, uint8_t pllp)
{
    if (RCC_IsPLLActive())
    {
        return;
    }

    RCC_ResetPLL();

    RCC_SetPLLM (pllm);
    RCC_SetPLLN (plln);
    RCC_SetPLLP (pllp);

   
    if (RCC_IsHSIActive())
    {
        RCC_PLLCFGR &= ~RCC_PLLCFGR_PLLSRC_CLEARMASK;
        RCC_PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;
    }
    else if (RCC_IsHSEActive())
    {
        RCC_PLLCFGR &= ~RCC_PLLCFGR_PLLSRC_CLEARMASK;
        RCC_PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;
    }

    RCC_CFGR &= ~RCC_CFGR_SW_CLEARMASK;
    RCC_CFGR |= RCC_CFGR_SW_PLL_P;
    
    RCC_StartPLL();




    
    
    //    if (!(RCC_CR & RCC_CR_PLLON))
    //    {
    //        RCC_CFGR &= RCC_CFGR_SW_PLL_CLEARMASK;
    //        RCC_CFGR |= RCC_CFGR_SW_HSI;
    //    }
    //
    //    RCC_PLLCFGR &= ~RCC_PLLCFGR_PLLSRC_CLEARMASK;
    //    RCC_PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;


}


void RCC_DisablePLL()
{
    if (!RCC_IsPLLActive())
    {
        RCC_ResetPLL();
    }
}



//Division: VCO = PLL input clock freq /  PLLM
// 2 <= PLLM <= 63
void RCC_SetPLLM (uint8_t pllm) 
{
    if (pllm >= 2 && pllm <= 63) 
    {
        RCC_PLLCFGR &= ~RCC_PLLCFGR_PLLM_CLEARMASK;
        RCC_PLLCFGR |= pllm<<RCC_PLLCFGR_PLLM_OFFSET;
    }
}

//Multiplication factor for VCO
void RCC_SetPLLN (uint16_t plln) 
{
	RCC_PLLCFGR &= ~RCC_PLLCFGR_PLLN_CLEARMASK;
	RCC_PLLCFGR |= plln<<RCC_PLLCFGR_PLLN_OFFSET;
}

void RCC_SetPLLP (uint8_t pllp)
{
    RCC_PLLCFGR &= ~RCC_PLLCFGR_PLLP_CLEARMASK;
    if (pllp == 2)
    {
        RCC_PLLCFGR |= RCC_PLLCFGR_PLLP_2;
    }
    else if (pllp == 4)
    {
        RCC_PLLCFGR |= RCC_PLLCFGR_PLLP_4;
    }
    else if (pllp == 6)
    {
        RCC_PLLCFGR |= RCC_PLLCFGR_PLLP_6;
    }
    else if (pllp == 8)
    {
        RCC_PLLCFGR |= RCC_PLLCFGR_PLLP_8;
    }
    else
    {
        return;
    }

}


//f(VCO clock) = f(PLL clock input) x (PLLN / PLLM) 
//f(PLL general clock output)= f(VCO clock)/ PLLP
//f(USB OTG FS, SDIO)= f(VCO clock)/ PLLQ




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

static uint8_t ptable[] = { 2, 4, 6, 8 };

uint32_t RCC_GetSystemClock() 
{ 
    uint32_t sysClockFreq = HSI_CLOCK_FREQ;

    if (RCC_CFGR & RCC_CFGR_SWS_HSE)
    {
        return HSE_CLOCK_FREQ;
    }
    else if (RCC_CFGR & RCC_CFGR_SWS_PLL_P)
    {
        uint32_t pllm =  (RCC_PLLCFGR & RCC_PLLCFGR_PLLM_CLEARMASK) >> RCC_PLLCFGR_PLLM_OFFSET;
        uint32_t plln =  (RCC_PLLCFGR & RCC_PLLCFGR_PLLN_CLEARMASK) >> RCC_PLLCFGR_PLLN_OFFSET;
        uint32_t pllp =  (RCC_PLLCFGR & RCC_PLLCFGR_PLLP_CLEARMASK) >> RCC_PLLCFGR_PLLP_OFFSET;
        uint32_t hsFreq;
        uint32_t vcoFreq;
    
        pllp = ptable[pllp];

        if (RCC_PLLCFGR & RCC_PLLCFGR_PLLSRC_HSE)
        {
            hsFreq = HSE_CLOCK_FREQ;
        }
        else
        {
            hsFreq = HSI_CLOCK_FREQ;
        }

        vcoFreq = hsFreq / pllm * plln;
        sysClockFreq = vcoFreq / pllp;
    }

    return sysClockFreq;

}




static uint16_t t_presc[] = { 2, 4, 8, 16, 64, 128, 256, 512 };

uint32_t RCC_GetAHB_CLK(void)
{
  uint32_t sysclk = RCC_GetSystemClock();
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
static uint16_t RCC_GetAPBx_div(uint8_t offset)
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
  uint16_t apb1_div = RCC_GetAPBx_div(RCC_CFGR_APB1_PCLK1_PRE_POS);
  return ahb_clk / apb1_div;
}

uint32_t RCC_GetAPB2_CLK(void)
{
  uint32_t ahb_clk = RCC_GetAHB_CLK();
  uint16_t apb2_div = RCC_GetAPBx_div(RCC_CFGR_APB1_PCLK2_PRE_POS);
  return ahb_clk / apb2_div;
}

uint32_t RCC_GetTIMx_CLK(BOOL isAPB1)
{
  uint32_t ahb_clk = RCC_GetAHB_CLK();
  uint16_t apbx_div;
  uint32_t timx_clk;
    
  if (isAPB1)
  {
    apbx_div = RCC_GetAPBx_div(RCC_CFGR_APB1_PCLK1_PRE_POS);
  }
  else
  {
    apbx_div = RCC_GetAPBx_div(RCC_CFGR_APB1_PCLK2_PRE_POS);
  }
  
  timx_clk = ahb_clk / apbx_div;
  
  if (apbx_div > 1)
  {
    timx_clk *= 2;
  }
    
  return timx_clk;
}


void RCC_Delay_us(uint32_t us)
{


#ifdef __GNUC__
  uint64_t cnt = (uint64_t)RCC_GetAHB_CLK() * (uint64_t)us / 12000000ull;
  volatile uint64_t i;
#else
  uint64_t cnt = (uint64_t)RCC_GetAHB_CLK() * (uint64_t)us / 6000000ull;
  uint64_t i;
#endif
  for (i = 0; i < cnt; ++i) 
  {
  }
}


void RCC_Delay_ms(uint32_t ms)
{
  RCC_Delay_us (ms * 1000);
}




/*

uint16_t RCC::t_presc[] = { 2, 4, 8, 16, 64, 128, 256, 512 };

uint32_t RCC::GetAHB_CLK(void)
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

uint16_t RCC::GetAPBx_div(uint8_t offset)
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


uint32_t RCC::GetAPB1_CLK(void)
{
  uint32_t ahb_clk = GetAHB_CLK();
  uint16_t apb1_div = GetAPBx_div(8);
  return ahb_clk / apb1_div;
}

uint32_t RCC::GetAPB2_CLK(void)
{
  uint32_t ahb_clk = GetAHB_CLK();
  uint16_t apb2_div = GetAPBx_div(11);
  return ahb_clk / apb2_div;
}

uint32_t RCC::GetTIMx_CLK(void)
{
  uint32_t ahb_clk = GetAHB_CLK();
  uint16_t apb1_div = GetAPBx_div(8);
    uint32_t timx_clk = ahb_clk / apb1_div;
  if (apb1_div > 1)
  {
      timx_clk *= 2;
  }
    
  return timx_clk;
}

uint32_t RCC::GetRTC_CLK(void)
{
    if ((RCC_BDCR & RCC_BDCR_RTC_LSE) ||
        (RCC_BDCR & RCC_BDCR_RTC_LSI))
    {
        return 32768;
    }
    else if (RCC_BDCR & RCC_BDCR_RTC_HSE128)
    {
        return _hse_clock / 128;
    }
    else
    {
        return 0;
    }
}

void RCC::Delay_us(uint32_t us)
{
  //uint64_t cnt = (uint64_t)_system_clock  * (uint64_t)us / 6000000ull;
  uint64_t cnt = (uint64_t)GetAHB_CLK() * (uint64_t)us / 6000000ull;
  for (uint64_t i = 0; i < cnt; ++i) 
  {
  }
}


void RCC::Delay_ms(uint32_t ms)
{
  Delay_us (ms * 1000);
}


void RCC::ResetBKP(BOOL enable)
{
    if (enable)
        RCC_BDCR |= RCC_BDCR_BDRST;
    else
        RCC_BDCR &= ~RCC_BDCR_BDRST;

}

void RCC::SetRTCClockSourceLSE()
{
    RCC_BDCR &= ~RCC_BDCR_RTC_CLEARMASK;
    RCC_BDCR |= RCC_BDCR_RTC_LSE;
}
void RCC::SetRTCClockSourceLSI()
{
    RCC_BDCR &= ~RCC_BDCR_RTC_CLEARMASK;
    RCC_BDCR |= RCC_BDCR_RTC_LSI;
}
void RCC::SetRTCClockSourceHSE_DIV128()
{
    RCC_BDCR &= ~RCC_BDCR_RTC_CLEARMASK;
    RCC_BDCR |= RCC_BDCR_RTC_HSE128;
}

void RCC::SetRTCClockSourceOFF()
{
    RCC_BDCR &= ~RCC_BDCR_RTC_CLEARMASK;
    RCC_BDCR &= ~RCC_BDCR_RTCEN;
}

void RCC::EnableRTC(BOOL enable)
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



void RCC::EnableLSI()
{
    RCC_BDCR &= ~(RCC_BDCR_LSEON | RCC_BDCR_RTC_LSE);
    RCC_BDCR |= RCC_BDCR_RTC_LSI; //LSI ~40Khz
    RCC_CSR |= RCC_CSR_LSION;

    while ((RCC_CSR & (RCC_CSR_LSIRDY)) == 0)
        ;
}

void RCC::EnableLSE()
{
    RCC_CSR &= ~RCC_CSR_LSION;
    RCC_BDCR &= ~RCC_BDCR_RTC_LSI;
    RCC_BDCR |= RCC_BDCR_RTC_LSE;
    RCC_BDCR |= RCC_BDCR_LSEON;

    while ((RCC_BDCR & (RCC_BDCR_LSERDY)) == 0)
       ;

}

BOOL RCC::IsEnabledHSE()
{
    return ((RCC_CR & RCC_CR_HSEON) &&  (RCC_CR & RCC_CR_HSERDY));
}

BOOL RCC::IsEnabledHSI()
{
    return ((RCC_CR & RCC_CR_HSION) &&  (RCC_CR & RCC_CR_HSIRDY));
}

BOOL RCC::IsEnabledLSE()
{
    return ((RCC_BDCR & RCC_BDCR_LSEON) && (RCC_BDCR & RCC_BDCR_LSERDY));
}
BOOL RCC::IsEnabledLSI()
{
    return ((RCC_CSR & RCC_CSR_LSION) && (RCC_CSR & RCC_CSR_LSIRDY));
}



void RCC::InitPLL(uint8_t pll_mul)
{
    if (pll_mul < 2 && pll_mul>16)
    {
        return;
    }
    
    RCC_CFGR |= RCC_CFGR_SW_PLL;
    RCC_CFGR |= (pll_mul - 2)<<18;
    RCC_CR |= (RCC_CR_PLLON);

    while ((RCC_CR & (RCC_CR_PLLRDY)) == 0) 
        ;
    
    if ((RCC_CR & RCC_CR_HSION) ||  
        ((RCC_CR & RCC_CR_HSEON) && (RCC_CFGR & RCC_CFGR_PLLXTPRE))) 
    {
      _system_clock /= 2;
    }
  
    _system_clock *= pll_mul;
}


void RCC::EnableDAC(BOOL enable)
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

BOOL RCC::IsEnabledDAC()
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
BOOL IsEnabledCEC()
{
    return RCC_APB1ENR & RCC_APB1ENR_CECEN;
}


void RCC::EnableADC1(BOOL enable)
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


void RCC::EnableADC2(BOOL enable)
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

void RCC::EnableADC3(BOOL enable)
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

BOOL RCC::IsEnabledADC1()
{
    return RCC_APB2ENR & RCC_APB2ENR_ADC1EN;
}
BOOL RCC::IsEnabledADC2()
{
    return RCC_APB2ENR & RCC_APB2ENR_ADC2EN;
}
BOOL RCC::IsEnabledADC3()
{
    return RCC_APB2ENR & RCC_APB2ENR_ADC3EN;
}



void RCC::EnableSPI1(BOOL enable)
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
void RCC::EnableSPI2(BOOL enable)
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
void RCC::EnableSPI3(BOOL enable)
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

BOOL RCC::IsEnabledSPI1()
{
    return RCC_APB2ENR & RCC_APB2ENR_SPI1EN;
}

BOOL RCC::IsEnabledSPI2()
{
    return RCC_APB1ENR & RCC_APB1ENR_SPI2EN;
}

BOOL RCC::IsEnabledSPI3()
{
    return RCC_APB1ENR & RCC_APB1ENR_SPI3EN;
}

void RCC::EnableUSART1(BOOL enable)
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
void RCC::EnableUSART2(BOOL enable)
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
void RCC::EnableUSART3(BOOL enable)
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

BOOL RCC::IsEnabledUSART1()
{
    return RCC_APB2ENR & RCC_APB2ENR_USART1EN;
}
BOOL RCC::IsEnabledUSART2()
{
    return RCC_APB1ENR & RCC_APB1ENR_USART2EN;
}
BOOL RCC::IsEnabledUSART3()
{
    return RCC_APB1ENR & RCC_APB1ENR_USART3EN;
}


void RCC::EnableGPIOA(BOOL enable)
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

void RCC::EnableGPIOB(BOOL enable)
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

void RCC::EnableGPIOC(BOOL enable)
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

void RCC::EnableGPIOD(BOOL enable)
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


void RCC::EnableGPIOE(BOOL enable)
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

void RCC::EnableGPIOF(BOOL enable)
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


void RCC::EnableGPIOG(BOOL enable)
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

BOOL RCC::IsEnabledGPIOA()
{
    return RCC_APB2ENR & RCC_APB2ENR_IOPAEN;
}
BOOL RCC::IsEnabledGPIOB()
{
    return RCC_APB2ENR & RCC_APB2ENR_IOPBEN;
}
BOOL RCC::IsEnabledGPIOC()
{
    return RCC_APB2ENR & RCC_APB2ENR_IOPCEN;
}
BOOL RCC::IsEnabledGPIOD()
{
    return RCC_APB2ENR & RCC_APB2ENR_IOPDEN;
}
BOOL RCC::IsEnabledGPIOE()
{
    return RCC_APB2ENR & RCC_APB2ENR_IOPEEN;
}
BOOL RCC::IsEnabledGPIOF()
{
    return RCC_APB2ENR & RCC_APB2ENR_IOPFEN;
}
BOOL RCC::IsEnabledGPIOG()
{
    return RCC_APB2ENR & RCC_APB2ENR_IOPGEN;
}

void RCC::EnableI2C1(BOOL enable)
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

void RCC::EnableI2C2(BOOL enable)
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

BOOL RCC::IsEnabledI2C1()
{
    return RCC_APB1ENR & RCC_APB1ENR_I2C1EN;
}
BOOL RCC::IsEnabledI2C2()
{
    return RCC_APB1ENR & RCC_APB1ENR_I2C2EN;
}

void RCC::EnableDMA1(BOOL enable)
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
void RCC::EnableDMA2(BOOL enable)
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

BOOL RCC::IsEnabledDMA1()
{
    return RCC_AHBENR & RCC_AHBENR_DMA1EN;
}
BOOL RCC::IsEnabledDMA2()
{
    return RCC_AHBENR & RCC_AHBENR_DMA2EN;
}

void RCC::EnableSRAM(BOOL enable)
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
BOOL RCC::IsEnabledSRAM()
{
    return (RCC_AHBENR & RCC_AHBENR_SRAMEN);
}

void RCC::EnableFLITF(BOOL enable)
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
BOOL RCC::IsEnabledFLITF()
{
    return (RCC_AHBENR & RCC_AHBENR_FLITFEN);
}
void RCC::EnableCRC(BOOL enable)
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
BOOL RCC::IsEnabledCRC()
{
    return (RCC_AHBENR & RCC_AHBENR_CRCEN);
}
void RCC::EnableFSMC(BOOL enable)
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
BOOL RCC::IsEnabledFSMC()
{
    return (RCC_AHBENR & RCC_AHBENR_FSMCEN);
}
void RCC::EnableSDIO(BOOL enable)
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
BOOL RCC::IsEnabledSDIO()
{
    return (RCC_AHBENR & RCC_AHBENR_SDIOEN);
}

//Connectivity
void RCC::EnableOTGFS(BOOL enable)
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
BOOL RCC::IsEnabledOTGFS()
{
    return (RCC_AHBENR & RCC_AHBENR_OTGFSEN);
}
void RCC::EnableETHMAC(BOOL enable)
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
BOOL RCC::IsEnabledETHMAC()
{
    return (RCC_AHBENR & RCC_AHBENR_ETHMACEN);
}

void RCC::EnableETHMACTX(BOOL enable)
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
BOOL RCC::IsEnabledETHMACTX()
{
    return (RCC_AHBENR & RCC_AHBENR_ETHMACTXEN);
}

void RCC::EnableETHMACRX(BOOL enable)
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
BOOL RCC::IsEnabledETHMACRX()
{
    return (RCC_AHBENR & RCC_AHBENR_ETHMACRXEN);
}


void RCC::EnableTIM2(BOOL enable)
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
BOOL RCC::IsEnabledTIM2()
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM2EN);
}
void RCC::EnableTIM3(BOOL enable)
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
BOOL RCC::IsEnabledTIM3()
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM3EN);
}
void RCC::EnableTIM4(BOOL enable)
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
BOOL RCC::IsEnabledTIM4()
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM4EN);
}
void RCC::EnableTIM5(BOOL enable)
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
BOOL RCC::IsEnabledTIM5()
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM5EN);
}
void RCC::EnableTIM6(BOOL enable)
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
BOOL RCC::IsEnabledTIM6()
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM6EN);
}
void RCC::EnableTIM7(BOOL enable)
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
BOOL RCC::IsEnabledTIM7()
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM7EN);
}
void RCC::EnableTIM12(BOOL enable)
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
BOOL RCC::IsEnabledTIM12()
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM12EN);
}
void RCC::EnableTIM13(BOOL enable)
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
BOOL RCC::IsEnabledTIM13()
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM13EN);
}
void RCC::EnableTIM14(BOOL enable)
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
BOOL RCC::IsEnabledTIM14()
{
    return (RCC_APB1ENR & RCC_APB1ENR_TIM14EN);
}
void RCC::EnableWWDG(BOOL enable)
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
BOOL RCC::IsEnabledWWDG()
{
    return (RCC_APB1ENR & RCC_APB1ENR_WWDGEN);
}

//APB2
void RCC::EnableAFIO(BOOL enable)
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
BOOL RCC::IsEnabledAFIO()
{
    return (RCC_APB2ENR & RCC_APB2ENR_AFIOEN);
}

void RCC::EnableTIM1(BOOL enable)
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
BOOL RCC::IsEnabledTIM1()
{
    return (RCC_APB2ENR & RCC_APB2ENR_TIM1EN);
}
void RCC::EnableTIM8(BOOL enable)
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
BOOL RCC::IsEnabledSTIM8()
{
    return (RCC_APB2ENR & RCC_APB2ENR_TIM8EN);
}

void RCC::EnableTIM9(BOOL enable)
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
BOOL RCC::IsEnabledTIM9()
{
    return (RCC_APB2ENR & RCC_APB2ENR_TIM9EN);
}
void RCC::EnableTIM10(BOOL enable)
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
BOOL RCC::IsEnabledTIM10()
{
    return (RCC_APB2ENR & RCC_APB2ENR_TIM10EN);
}
void RCC::EnableTIM11(BOOL enable)
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
BOOL RCC::IsEnabledTIM11()
{
    return (RCC_APB2ENR & RCC_APB2ENR_TIM11EN);
}

void RCC::EnableTIM15(BOOL enable)
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
BOOL RCC::IsEnabledTIM15()
{
    return (RCC_APB2ENR & RCC_APB2ENR_TIM15EN);
}

void RCC::EnableTIM16(BOOL enable)
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
BOOL RCC::IsEnabledTIM16()
{
    return (RCC_APB2ENR & RCC_APB2ENR_TIM16EN);
}

void RCC::EnableTIM17(BOOL enable)
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
BOOL RCC::IsEnabledTIM17()
{
    return (RCC_APB2ENR & RCC_APB2ENR_TIM17EN);
}

void RCC::EnableClockSecurity(BOOL enable)
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

void RCC::EnableBKP(BOOL enable)
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
BOOL RCC::IsEnabledBKP()
{
    return RCC_APB1ENR & RCC_APB1ENR_BKPEN;
}
void RCC::EnablePWR(BOOL enable)
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

BOOL RCC::IsEnabledPWR()
{
    return RCC_APB1ENR & RCC_APB1ENR_PWREN;
}

void RCC::EnableUSB(BOOL enable)
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

BOOL RCC::IsEnabledUSB()
{
    return RCC_APB1ENR & RCC_APB1ENR_USBEN;
}

void RCC::EnableCAN(BOOL enable)
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
BOOL RCC::IsEnabledCAN()
{
    return RCC_APB1ENR & RCC_APB1ENR_CANEN;
}

void RCC::EnableCEC(BOOL enable)
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
BOOL RCC::IsEnabledCEC()
{
    return RCC_APB1ENR & RCC_APB1ENR_CECEN;
}
*/


#ifdef __cplusplus
}
#endif
