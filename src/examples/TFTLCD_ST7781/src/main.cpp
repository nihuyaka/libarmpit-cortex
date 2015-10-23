#include "RCC_Helper.h"
#include "GPIO_Helper.h"
#include "spi.h"
#include "gpio_cpp.h"
#include <stdio.h>


static void test()
{
    GPIOA* portA = GPIOA::GetInstance();
    GPIOB* portB = GPIOB::GetInstance();
    portA->EnablePeripheralClock(true);
    portB->EnablePeripheralClock(true);
    SPI* spi = GPIO_Helper::SetupSPI1_MasterMode_PA_5_6_7(false, false, SPI_BAUD_RATE_2);
    GPIO_PIN* dcPin = portB->GetPin(GPIO_PIN1);
    dcPin->SetupGPIO_OutPP();

    GPIO_PIN* rstPin = portB->GetPin(GPIO_PIN0);
    rstPin->SetupGPIO_OutPP();
    rstPin->Reset();
    RCC_Delay_ms(10);
    rstPin->Set();
    RCC_Delay_ms(10);


    while(1)
        ;

}

int main()
{
#if defined (STM32F1)   
    //RCC_EnableHSI_72Mhz_AHB_72Mhz_APB1_36MHz_APB2_72MHz();
    //RCC_EnableHSI(TRUE);
    RCC_EnableHSI_24Mhz();
#else

    //RCC_EnableHSI_100Mhz();
    //RCC_SetAHBPrescalerDiv2();

    FLASH_EnableDCache(TRUE);
    FLASH_EnableICache(TRUE);
    FLASH_EnablePrefetchBuffer(TRUE);

    FLASH_SetWaitState(3);

    RCC_EnableHSI(TRUE);
    uint8_t pllm = 8;
    uint16_t plln = 200;
    uint16_t pllp = 4;
    RCC_EnablePLL(pllm, plln, pllp);

    RCC_SetAHBPrescalerDiv2();

    //RCC_SetAPB1PrescalerDiv16();

    volatile uint32_t c1 = RCC_GetAPB1_CLK();
    volatile uint32_t c2 = RCC_GetAPB2_CLK();

#endif  

    test();

}
