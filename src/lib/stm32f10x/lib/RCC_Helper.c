#include "Rcc_Helper.h" 

#ifdef __cplusplus
extern "C"
{
#endif

void RCC_EnableHSI_8Mhz(void)
{
	RCC_EnableHSI(TRUE);
}


void RCC_EnableHSI_16Mhz(void)
{
	RCC_EnableHSI(TRUE);
	RCC_EnablePLL(4);
}

void RCC_EnableHSI_24Mhz(void)
{
	FLASH_SetWaitState(1);
	RCC_EnableHSI(TRUE);
	RCC_EnablePLL(6);
}

void RCC_EnableHSI_72Mhz_AHB_72Mhz_APB1_36MHz_APB2_72MHz(void)
{
	FLASH_SetWaitState(2);
	RCC_EnableHSI(TRUE);
	RCC_EnablePLL(18);
	RCC_SetAPB1PrescalerDiv2();
}

void RCC_EnableHSI_72Mhz_AHB_36Mhz_APB1_18MHz_APB2_18MHz(void)
{
	FLASH_SetWaitState(2);
	RCC_EnableHSI(TRUE);
	RCC_EnablePLL(18);
	RCC_SetAHBPrescalerDiv2();
	RCC_SetAPB1PrescalerDiv2();
	RCC_SetAPB2PrescalerDiv2();
}



#ifdef __cplusplus
}
#endif
