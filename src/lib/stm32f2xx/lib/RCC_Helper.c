#include "Rcc_Helper.h" 

#ifdef __cplusplus
extern "C"
{
#endif



void RCC_EnableHSE_168Mhz()
{
    FLASH_EnableDCache(TRUE);
    FLASH_EnableICache(TRUE);
    FLASH_EnablePrefetchBuffer(TRUE);

    FLASH_EnableDCache(TRUE);
    FLASH_EnableICache(TRUE);
    FLASH_EnablePrefetchBuffer(TRUE);
    FLASH_SetWaitState(5);

    RCC_EnableHSE(TRUE);
    RCC_EnableHSI(FALSE);
    uint8_t pllm = HSE_CLOCK_FREQ / 1000000;
    uint16_t plln = 336;
    uint16_t pllp = 2; //vco out / pllp = sysclock
    RCC_EnablePLL(pllm, plln, pllp);
    RCC_SetAHBPrescalerDiv2();
}

void RCC_EnableHSI_100Mhz()
{
    FLASH_EnableDCache(TRUE);
    FLASH_EnableICache(TRUE);
    FLASH_EnablePrefetchBuffer(TRUE);

    FLASH_EnableDCache(TRUE);
    FLASH_EnableICache(TRUE);
    FLASH_EnablePrefetchBuffer(TRUE);
    FLASH_SetWaitState(5);

    RCC_EnableHSI(TRUE);
    uint8_t pllm = 4;    //8/4=2MHz
    uint16_t plln = 200; //2*200=400Mhz
    uint16_t pllp = 4; //400/4=100Mhz
    RCC_EnablePLL(pllm, plln, pllp);
    RCC_SetAHBPrescalerDiv2();

}
