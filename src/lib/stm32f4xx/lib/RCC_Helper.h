#ifndef RCC_HELPER_H
#define RCC_HELPER_H

#include "flash.h"
#include "rcc.h"

#ifdef __cplusplus
extern "C"
{
#endif

void RCC_EnableHSE_168Mhz(void);
void RCC_EnableHSI_168Mhz(void);
void RCC_EnableHSI_100Mhz(void);

#ifdef __cplusplus
}
#endif



#endif
