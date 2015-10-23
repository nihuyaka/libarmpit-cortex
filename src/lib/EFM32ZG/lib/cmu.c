#include "cmu.h"

/////////////  CTRL
static void  CMU_SetHFXOMODE (uint32_t mode)
{
	CMU_CTRL &= ~CMU_CTRL_HFXOMODE_CLEARMASK;
	CMU_CTRL |= mode;
}

void CMU_SetHFXOMODE_XTAL (void)
{
	CMU_SetHFXOMODE (CMU_CTRL_HFXOMODE_XTAL);
}
void CMU_SetHFXOMODE_BUFEXTCLK (void)
{
	CMU_SetHFXOMODE (CMU_CTRL_HFXOMODE_BUFEXTCLK);
}
void CMU_SetHFXOMODE_DIGEXTCLK (void)
{
	CMU_SetHFXOMODE (CMU_CTRL_HFXOMODE_DIGEXTCLK);
}



static void CMU_SetHFXOTIMEOUT (uint32_t value)
{
	CMU_CTRL &= ~CMU_CTRL_HFXOTIMEOUT_CLEARMASK;
	CMU_CTRL |= value;

}

void CMU_SetHFXOTIMEOUT_8(void) 
{
	CMU_SetHFXOTIMEOUT (CMU_CTRL_HFXOTIMEOUT_8CYCLES);
}
void CMU_SetHFXOTIMEOUT_256 (void)
{
	CMU_SetHFXOTIMEOUT (CMU_CTRL_HFXOTIMEOUT_256CYCLES);
}
void CMU_SetHFXOTIMEOUT_1K (void)
{
	CMU_SetHFXOTIMEOUT (CMU_CTRL_HFXOTIMEOUT_1KCYCLES);
}
void CMU_SetHFXOTIMEOUT_16K (void)
{
	CMU_SetHFXOTIMEOUT (CMU_CTRL_HFXOTIMEOUT_16KCYCLES);
}



static void CMU_SetLFXOTIMEOUT (uint32_t value)
{
	CMU_CTRL &= ~CMU_CTRL_LFXOTIMEOUT_CLEARMASK;
	CMU_CTRL |= value;

}

void CMU_SetLFXOTIMEOUT_8(void) 
{
	CMU_SetLFXOTIMEOUT (CMU_CTRL_LFXOTIMEOUT_8CYCLES);
}
void CMU_SetLFXOTIMEOUT_1K (void)
{
	CMU_SetLFXOTIMEOUT (CMU_CTRL_LFXOTIMEOUT_1KCYCLES);
}
void CMU_SetLFXOTIMEOUT_16K (void)
{
	CMU_SetLFXOTIMEOUT (CMU_CTRL_LFXOTIMEOUT_16KCYCLES);
}



static void  CMU_SetLFXOMODE (uint32_t mode)
{
	CMU_CTRL &= ~CMU_CTRL_LFXOMODE_CLEARMASK;
	CMU_CTRL |= mode;
}

void CMU_SetLFXOMODE_XTAL (void)
{
	CMU_SetLFXOMODE (CMU_CTRL_LFXOMODE_XTAL);
}
void CMU_SetLFXOMODE_BUFEXTCLK (void)
{
	CMU_SetLFXOMODE (CMU_CTRL_LFXOMODE_BUFEXTCLK);
}
void CMU_SetLFXOMODE_DIGEXTCLK (void)
{
	CMU_SetLFXOMODE (CMU_CTRL_LFXOMODE_DIGEXTCLK);
}


void CMU_EnableCLKOUTSEL0 (CLKOUTSEL0 value)
{
	CMU_CTRL &= ~CMU_CTRL_CLKOUTSEL0_CLEAR;
	CMU_CTRL |= value;
	CMU_ROUTE |= CMU_ROUTE_CLKOUT0PEN;
}

void CMU_EnableCLKOUTSEL1 (CLKOUTSEL1 value)
{
	CMU_CTRL &= ~CMU_CTRL_CLKOUTSEL0_CLEAR;
	CMU_CTRL |= value;

	CMU_ROUTE |= CMU_ROUTE_CLKOUT1PEN;

}

////////////////////////////////////////////////////////////////////
// prescalers

void CMU_SetHFCORECLK_DIV1 (void)
{
	CMU_HFCORECLKDIV &= CMU_HFCORECLKDIV_CLEARMASK;
	CMU_HFCORECLKDIV |= CMU_HFCORECLKDIV_HFCLK1;
}

void CMU_SetHFCORECLK_DIV2 (void)
{
	CMU_HFCORECLKDIV &= CMU_HFCORECLKDIV_CLEARMASK;
	CMU_HFCORECLKDIV |= CMU_HFCORECLKDIV_HFCLK2;
}

void CMU_SetHFCORECLK_DIV4 (void)
{
	CMU_HFCORECLKDIV &= CMU_HFCORECLKDIV_CLEARMASK;
	CMU_HFCORECLKDIV |= CMU_HFCORECLKDIV_HFCLK4;
}

void CMU_SetHFCORECLK_DIV8 (void)
{
	CMU_HFCORECLKDIV &= CMU_HFCORECLKDIV_CLEARMASK;
	CMU_HFCORECLKDIV |= CMU_HFCORECLKDIV_HFCLK8;
}

void CMU_SetHFCORECLK_DIV16 (void)
{
	CMU_HFCORECLKDIV &= CMU_HFCORECLKDIV_CLEARMASK;
	CMU_HFCORECLKDIV |= CMU_HFCORECLKDIV_HFCLK16;
}

void CMU_SetHFCORECLK_DIV32 (void)
{
	CMU_HFCORECLKDIV &= CMU_HFCORECLKDIV_CLEARMASK;
	CMU_HFCORECLKDIV |= CMU_HFCORECLKDIV_HFCLK32;
}

void CMU_SetHFCORECLK_DIV64 (void)
{
	CMU_HFCORECLKDIV &= CMU_HFCORECLKDIV_CLEARMASK;
	CMU_HFCORECLKDIV |= CMU_HFCORECLKDIV_HFCLK64;
}

void CMU_SetHFCORECLK_DIV128 (void)
{
	CMU_HFCORECLKDIV &= CMU_HFCORECLKDIV_CLEARMASK;
	CMU_HFCORECLKDIV |= CMU_HFCORECLKDIV_HFCLK128;
}

void CMU_SetHFCORECLK_DIV256 (void)
{
	CMU_HFCORECLKDIV &= CMU_HFCORECLKDIV_CLEARMASK;
	CMU_HFCORECLKDIV |= CMU_HFCORECLKDIV_HFCLK256;
}

void CMU_SetHFCORECLK_DIV512 (void)
{
	CMU_HFCORECLKDIV &= CMU_HFCORECLKDIV_CLEARMASK;
	CMU_HFCORECLKDIV |= CMU_HFCORECLKDIV_HFCLK512;
}

void CMU_SetHFCORECLK_LE_DIV2(void)
{
	CMU_HFCORECLKDIV &= CMU_HFCORECLKDIVLE_CLEARMASK;
	CMU_HFCORECLKDIV |= CMU_HFCORECLKDIVLE_DIV2;
}
void CMU_SetHFCORECLK_LE_DIV4(void)
{
	CMU_HFCORECLKDIV &= CMU_HFCORECLKDIVLE_CLEARMASK;
	CMU_HFCORECLKDIV |= CMU_HFCORECLKDIVLE_DIV4;
}

void CMU_SetHFPERCLK_DIV1 (void)
{
	CMU_HFPERCLKDIV &= ~CMU_HFPERCLKDIV_CLEARMASK;
	CMU_HFPERCLKDIV |= CMU_HFPERCLKDIV_HFCLK1;
}
void CMU_SetHFPERCLK_DIV2 (void)
{
	CMU_HFPERCLKDIV &= ~CMU_HFPERCLKDIV_CLEARMASK;
	CMU_HFPERCLKDIV |= CMU_HFPERCLKDIV_HFCLK2;
}
void CMU_SetHFPERCLK_DIV4 (void)
{
	CMU_HFPERCLKDIV &= ~CMU_HFPERCLKDIV_CLEARMASK;
	CMU_HFPERCLKDIV |= CMU_HFPERCLKDIV_HFCLK4;
}
void CMU_SetHFPERCLK_DIV8 (void)
{
	CMU_HFPERCLKDIV &= ~CMU_HFPERCLKDIV_CLEARMASK;
	CMU_HFPERCLKDIV |= CMU_HFPERCLKDIV_HFCLK8;
}
void CMU_SetHFPERCLK_DIV16 (void)
{
	CMU_HFPERCLKDIV &= ~CMU_HFPERCLKDIV_CLEARMASK;
	CMU_HFPERCLKDIV |= CMU_HFPERCLKDIV_HFCLK16;
}
void CMU_SetHFPERCLK_DIV32 (void)
{
	CMU_HFPERCLKDIV &= ~CMU_HFPERCLKDIV_CLEARMASK;
	CMU_HFPERCLKDIV |= CMU_HFPERCLKDIV_HFCLK32;
}
void CMU_SetHFPERCLK_DIV64 (void)
{
	CMU_HFPERCLKDIV &= ~CMU_HFPERCLKDIV_CLEARMASK;
	CMU_HFPERCLKDIV |= CMU_HFPERCLKDIV_HFCLK64;
}
void CMU_SetHFPERCLK_DIV128 (void)
{
	CMU_HFPERCLKDIV &= ~CMU_HFPERCLKDIV_CLEARMASK;
	CMU_HFPERCLKDIV |= CMU_HFPERCLKDIV_HFCLK128;
}
void CMU_SetHFPERCLK_DIV256 (void)
{
	CMU_HFPERCLKDIV &= ~CMU_HFPERCLKDIV_CLEARMASK;
	CMU_HFPERCLKDIV |= CMU_HFPERCLKDIV_HFCLK256;
}
void CMU_SetHFPERCLK_DIV512 (void)
{
	CMU_HFPERCLKDIV &= ~CMU_HFPERCLKDIV_CLEARMASK;
	CMU_HFPERCLKDIV |= CMU_HFPERCLKDIV_HFCLK512;
}

void CMU_EnableHFPERCLK (BOOL enable)
{
	if (enable)
	{
		CMU_HFPERCLKDIV |= CMU_HFPERCLKDIV_HFPERCLKEN;
	}
	else
	{
		CMU_HFPERCLKDIV &= ~CMU_HFPERCLKDIV_HFPERCLKEN;
	}

}


/////////////////////////

void CMU_EnableHFRCO(BOOL enable)
{
	if (enable)
	{
		CMU_OSCENCMD &= ~CMU_OSCENCMD_HFRCODIS;
		CMU_OSCENCMD |= CMU_OSCENCMD_HFRCOEN;
		while (!(CMU_STATUS & CMU_STATUS_HFRCORDY))
			;
	}
	else
	{
		CMU_OSCENCMD &= ~CMU_OSCENCMD_HFRCOEN;
		CMU_OSCENCMD |= CMU_OSCENCMD_HFRCODIS;
	}
}
void CMU_EnableHFXO(BOOL enable)
{
	if (enable)
	{
		CMU_OSCENCMD &= ~CMU_OSCENCMD_HFXODIS;
		CMU_OSCENCMD |= CMU_OSCENCMD_HFXOEN;
		while (!(CMU_STATUS & CMU_STATUS_HFXORDY))
			;
	}
	else
	{
		CMU_OSCENCMD &= ~CMU_OSCENCMD_HFXOEN;
		CMU_OSCENCMD |= CMU_OSCENCMD_HFXODIS;
	}

}
void CMU_EnableLFRCO(BOOL enable)
{
	if (enable)
	{
		CMU_OSCENCMD &= ~CMU_OSCENCMD_LFRCODIS;
		CMU_OSCENCMD |= CMU_OSCENCMD_LFRCOEN;
		while (!(CMU_STATUS & CMU_STATUS_LFRCORDY))
			;
	}
	else
	{
		CMU_OSCENCMD &= ~CMU_OSCENCMD_LFRCOEN;
		CMU_OSCENCMD |= CMU_OSCENCMD_LFRCODIS;
	}

}

void CMU_EnableLFXO(BOOL enable)
{
	if (enable)
	{
		CMU_OSCENCMD &= ~CMU_OSCENCMD_LFXODIS;
		CMU_OSCENCMD |= CMU_OSCENCMD_LFXOEN;
		while (!(CMU_STATUS & CMU_STATUS_LFXORDY))
			;
	}
	else
	{
		CMU_OSCENCMD &= ~CMU_OSCENCMD_LFXOEN;
		CMU_OSCENCMD |= CMU_OSCENCMD_LFXODIS;
	}

}

void CMU_EnableAUXHFRCO(BOOL enable)
{
	if (enable)
	{
		CMU_OSCENCMD &= ~CMU_OSCENCMD_AUXHFRCODIS;
		CMU_OSCENCMD |= CMU_OSCENCMD_AUXHFRCOEN;
		while (!(CMU_STATUS & CMU_STATUS_AUXHFRCORDY))
			;
	}
	else
	{
		CMU_OSCENCMD &= ~CMU_OSCENCMD_AUXHFRCOEN;
		CMU_OSCENCMD |= CMU_OSCENCMD_AUXHFRCODIS;
	}

}




// CMD clock select 

void CMU_SelectHFCLK_HFRCO()
{
	CMU_CMD &=  ~CMU_CMD_HFCLKSEL_CLEARFLAG;
  CMU_CMD |=  CMU_CMD_HFCLKSEL_HFRCO;
}

void CMU_SelectHFCLK_HFXO()
{

	CMU_CMD &=  ~CMU_CMD_HFCLKSEL_CLEARFLAG;
  CMU_CMD |=  CMU_CMD_HFCLKSEL_HFXO;

}
void CMU_SelectHFCLK_LFRCO()
{
	CMU_CMD &=  ~CMU_CMD_HFCLKSEL_CLEARFLAG;
  CMU_CMD |=  CMU_CMD_HFCLKSEL_LFRCO;

}
void CMU_SelectHFCLK_LFXO()
{
	CMU_CMD &=  ~CMU_CMD_HFCLKSEL_CLEARFLAG;
  CMU_CMD |=  CMU_CMD_HFCLKSEL_LFXO;
}

////////////////// low freq clock select

void CMU_EnableLFACLK_LFRCO()
{
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFAE;
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFA_CLEARMASK;
	 CMU_LFCLKSEL |= CMU_LFCLKSEL_LFA_LFRCO;

}
void CMU_EnableLFACLK_LFXO()
{
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFAE;
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFA_CLEARMASK;
	 CMU_LFCLKSEL |= CMU_LFCLKSEL_LFA_LFXO;
}
void CMU_EnableLFACLK_HFCORECLKLEDIV2()
{
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFAE;
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFA_CLEARMASK;
	 CMU_LFCLKSEL |= CMU_LFCLKSEL_LFA_HFCORECLKLEDIV2;
}
void CMU_EnableLFACLK_ULFRCO()
{
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFA_CLEARMASK;
	 CMU_LFCLKSEL |=  CMU_LFCLKSEL_LFAE;
}

void CMU_DisableLFACLK()
{
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFAE;
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFA_CLEARMASK;
}

void CMU_EnableLFBCLK_LFRCO()
{
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFBE;
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFB_CLEARMASK;
	 CMU_LFCLKSEL |= CMU_LFCLKSEL_LFB_LFRCO;

}
void CMU_EnableLFBCLK_LFXO()
{
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFBE;
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFB_CLEARMASK;
	 CMU_LFCLKSEL |= CMU_LFCLKSEL_LFB_LFXO;
}
void CMU_EnableLFBCLK_HFCORECLKLEDIV2()
{
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFBE;
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFB_CLEARMASK;
	 CMU_LFCLKSEL |= CMU_LFCLKSEL_LFB_HFCORECLKLEDIV2;
}
void CMU_EnableLFBCLK_ULFRCO()
{
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFB_CLEARMASK;
	 CMU_LFCLKSEL |=  CMU_LFCLKSEL_LFBE;
}

void CMU_DisableLFBCLK()
{
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFBE;
	 CMU_LFCLKSEL &=  ~CMU_LFCLKSEL_LFB_CLEARMASK;
}

//////////////////////////////////////////
void CMU_EnableCoreClock_AES(BOOL enable)
{
	if (enable) 
	{
		CMU_HFCORECLKEN0 |= CMU_HFCORECLKEN0_AES;
	}
	else 
	{
		CMU_HFCORECLKEN0 &= ~CMU_HFCORECLKEN0_AES;
	}
}

void CMU_EnableCoreClock_DMA(BOOL enable)
{
	if (enable) 
	{
		CMU_HFCORECLKEN0 |= CMU_HFCORECLKEN0_DMA;
	}
	else 
	{
		CMU_HFCORECLKEN0 &= ~CMU_HFCORECLKEN0_DMA;
	}
}
void CMU_EnableCoreClock_LE(BOOL enable)
{
	if (enable) 
	{
		CMU_HFCORECLKEN0 |= CMU_HFCORECLKEN0_LE;
	}
	else 
	{
		CMU_HFCORECLKEN0 &= ~CMU_HFCORECLKEN0_LE;
	}
}

void CMU_Enable_Peripheral_TIMER0(BOOL enable)
{
	if (enable) 
	{
		CMU_HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER0;
	}
	else 
	{
		CMU_HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_TIMER0;
	}
}
void CMU_Enable_Peripheral_TIMER1(BOOL enable)
{
	if (enable) 
	{
		CMU_HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER1;
	}
	else 
	{
		CMU_HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_TIMER1;
	}
}
void CMU_Enable_Peripheral_ACMP0(BOOL enable)
{
	if (enable) 
	{
		CMU_HFPERCLKEN0 |= CMU_HFPERCLKEN0_ACMP0;
	}
	else 
	{
		CMU_HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_ACMP0;
	}
}
void CMU_Enable_Peripheral_USART1(BOOL enable)
{
	if (enable) 
	{
		CMU_HFPERCLKEN0 |= CMU_HFPERCLKEN0_USART1;
	}
	else 
	{
		CMU_HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_USART1;
	}
}
void CMU_Enable_Peripheral_PRS(BOOL enable)
{
	if (enable) 
	{
		CMU_HFPERCLKEN0 |= CMU_HFPERCLKEN0_PRS;
	}
	else 
	{
		CMU_HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_PRS;
	}
}
void CMU_Enable_Peripheral_IDAC0(BOOL enable)
{
	if (enable) 
	{
		CMU_HFPERCLKEN0 |= CMU_HFPERCLKEN0_IDAC0;
	}
	else 
	{
		CMU_HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_IDAC0;
	}
}
void CMU_Enable_Peripheral_GPIO(BOOL enable)
{
	if (enable) 
	{
		CMU_HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;
	}
	else 
	{
		CMU_HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_GPIO;
	}
}
void CMU_Enable_Peripheral_VCMP(BOOL enable)
{
	if (enable) 
	{
		CMU_HFPERCLKEN0 |= CMU_HFPERCLKEN0_VCMP;
	}
	else 
	{
		CMU_HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_VCMP;
	}
}
void CMU_Enable_Peripheral_ADC0(BOOL enable)
{
	if (enable) 
	{
		CMU_HFPERCLKEN0 |= CMU_HFPERCLKEN0_ADC0;
	}
	else 
	{
		CMU_HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_ADC0;
	}
}
void CMU_Enable_Peripheral_I2C0(BOOL enable)
{
	if (enable) 
	{
		CMU_HFPERCLKEN0 |= CMU_HFPERCLKEN0_I2C0;
	}
	else 
	{
		CMU_HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_I2C0;
	}
}
void CMU_Enable_LFA_RTC(BOOL enable)
{
	while (CMU_SYNCBUSY & CMU_SYNCBUSY_LFACLKEN0)
		;
	
	if (enable) 
	{
		CMU_LFACLKEN0 |= CMU_LFACLKEN0_RTC;
	}
	else 
	{
		CMU_LFACLKEN0 &= ~CMU_LFACLKEN0_RTC;
	}
}
void CMU_Enable_LFB_LEUART0(BOOL enable)
{
	while (CMU_SYNCBUSY & CMU_SYNCBUSY_LFBCLKEN0)
		;
	
	if (enable) 
	{
		CMU_LFBCLKEN0 |= CMU_LFBCLKEN0_LEUART0;
	}
	else 
	{
		CMU_LFBCLKEN0 &= ~CMU_LFBCLKEN0_LEUART0;
	}
}

////////////////////////////////////////////////////////////

static void CMU_SetLFAPrescaler (uint32_t val) 
{
	while (CMU_SYNCBUSY & CMU_SYNCBUSY_LFAPRESC0) 
		;
	
	CMU_LFAPRESC0 &= ~CMU_LFAPRESC0_CLEARMASK;
	CMU_LFAPRESC0 |= val;
}

void CMU_SetLFAPrescaler_DIV1 (void)
{
	CMU_SetLFAPrescaler (CMU_LFAPRESC0_DIV1);
}
void CMU_SetLFAPrescaler_DIV2 (void)
{
	CMU_SetLFAPrescaler (CMU_LFAPRESC0_DIV2);
}
void CMU_SetLFAPrescaler_DIV4 (void)
{
	CMU_SetLFAPrescaler (CMU_LFAPRESC0_DIV4);
}
void CMU_SetLFAPrescaler_DIV8 (void)
{
	CMU_SetLFAPrescaler (CMU_LFAPRESC0_DIV8);
}
void CMU_SetLFAPrescaler_DIV16 (void)
{
	CMU_SetLFAPrescaler (CMU_LFAPRESC0_DIV16);
}
void CMU_SetLFAPrescaler_DIV32 (void)
{
	CMU_SetLFAPrescaler (CMU_LFAPRESC0_DIV32);
}
void CMU_SetLFAPrescaler_DIV64 (void)
{
	CMU_SetLFAPrescaler (CMU_LFAPRESC0_DIV64);
}
void CMU_SetLFAPrescaler_DIV128 (void)
{
	CMU_SetLFAPrescaler (CMU_LFAPRESC0_DIV128);
}
void CMU_SetLFAPrescaler_DIV256 (void)
{
	CMU_SetLFAPrescaler (CMU_LFAPRESC0_DIV256);
}
void CMU_SetLFAPrescaler_DIV512 (void)
{
	CMU_SetLFAPrescaler (CMU_LFAPRESC0_DIV512);
}
void CMU_SetLFAPrescaler_DIV1K (void)
{
	CMU_SetLFAPrescaler (CMU_LFAPRESC0_DIV1024);
}
void CMU_SetLFAPrescaler_DIV2K (void)
{
	CMU_SetLFAPrescaler (CMU_LFAPRESC0_DIV2048);
}
void CMU_SetLFAPrescaler_DIV4K (void)
{
	CMU_SetLFAPrescaler (CMU_LFAPRESC0_DIV4096);
}
void CMU_SetLFAPrescaler_DIV8K (void)
{
	CMU_SetLFAPrescaler (CMU_LFAPRESC0_DIV8192);
}
void CMU_SetLFAPrescaler_DIV16K (void)
{
		CMU_SetLFAPrescaler (CMU_LFAPRESC0_DIV16634);
}
void CMU_SetLFAPrescaler_DIV32K (void)
{
	CMU_SetLFAPrescaler (CMU_LFAPRESC0_DIV32768);
}

static void CMU_SetLFBPrescaler (uint32_t val) 
{
	while (CMU_SYNCBUSY & CMU_SYNCBUSY_LFBPRESC0) 
		;
	
	CMU_LFBPRESC0 &= ~CMU_LFBPRESC0_CLEARMASK;
	CMU_LFBPRESC0 |= val;
}

void CMU_SetLFBPrescaler_DIV1 (void)
{
	CMU_SetLFBPrescaler (CMU_LFBPRESC0_DIV1);
}
void CMU_SetLFBPrescaler_DIV2 (void)
{
	CMU_SetLFBPrescaler (CMU_LFBPRESC0_DIV2);
}
void CMU_SetLFBPrescaler_DIV4 (void)
{
	CMU_SetLFBPrescaler (CMU_LFBPRESC0_DIV4);
}
void CMU_SetLFBPrescaler_DIV8 (void)
{
	CMU_SetLFBPrescaler (CMU_LFBPRESC0_DIV8);
}


////////////////////////////////////////////////////////////

void CMU_DisableCLKOUTSEL0()
{
	CMU_ROUTE &= ~CMU_ROUTE_CLKOUT0PEN;
}

void CMU_DisableCLKOUTSEL1()
{
	CMU_ROUTE &= ~CMU_ROUTE_CLKOUT1PEN;
}

//////////////////////////////////////////