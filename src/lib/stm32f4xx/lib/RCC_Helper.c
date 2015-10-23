#include "Rcc_Helper.h" 

#ifdef __cplusplus
extern "C"
{
#endif



void RCC_EnableHSE_168Mhz()
{
    FLASH_EnableDCache();
    FLASH_EnableICache();
    FLASH_EnablePrefetchBuffer();

    FLASH_SetWaitState(5);

    RCC_EnableHSE(TRUE);
    RCC_EnableHSI(FALSE);
    uint8_t pllm = 8;
    uint16_t plln = 336;  //vco= 8mHz(HSE) * n / m
    uint16_t pllp = 2; //vco out / pllp = sysclock
    RCC_EnablePLL(pllm, plln, pllp);
    RCC_SetAHBPrescalerDiv2();
}

void RCC_EnableHSI_168Mhz()
{
    FLASH_EnableDCache();
    FLASH_EnableICache();
    FLASH_EnablePrefetchBuffer();

    FLASH_SetWaitState(5);

    RCC_EnableHSI(TRUE);
    uint8_t pllm = 16;
    uint16_t plln = 336;
    uint16_t pllp = 2; //vco out / pllp = sysclock
    RCC_EnablePLL(pllm, plln, pllp);
    RCC_SetAHBPrescalerDiv2();
}


void RCC_EnableHSI_100Mhz()
{
    FLASH_EnableDCache();
    FLASH_EnableICache();
    FLASH_EnablePrefetchBuffer();

    FLASH_SetWaitState(3);

    RCC_EnableHSI(TRUE);
    uint8_t pllm = 8;
    uint16_t plln = 200;
    uint16_t pllp = 4;
    RCC_EnablePLL(pllm, plln, pllp);
    RCC_SetAHBPrescalerDiv2();

}
