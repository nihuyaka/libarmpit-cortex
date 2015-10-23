#ifndef RCC_HELPER_H
#define RCC_HELPER_H

#include "flash.h"
#include "rcc.h"

#ifdef __cplusplus
extern "C"
{
#endif

void RCC_EnableHSI_8Mhz(void);
void RCC_EnableHSI_16Mhz(void);
void RCC_EnableHSI_24Mhz(void);
void RCC_EnableHSI_72Mhz_AHB_72Mhz_APB1_36MHz_APB2_72MHz(void);
void RCC_EnableHSI_72Mhz_AHB_36Mhz_APB1_18MHz_APB2_18MHz(void);

#ifdef __cplusplus
}
#endif



#endif
