#include "RCC_Helper.h"
#include "GPIO_Helper.h"
#include "IRSend.h"
#include "timer_cpp.h"
#include "rcc.h"

static void test()
{
    TIMER_With_Channels* timer = TIM3::GetInstance();
    timer->EnablePeripheralClock(true);
    //GPIOA::GetInstance()->EnablePeripheralClock(true);
    GPIOB::GetInstance()->EnablePeripheralClock(true);
    //GPIO_PIN* irSendPin = GPIOA::GetInstance()->GetPin(GPIO_PIN6);
    //GPIO_PIN* ch1 = GPIOA::GetInstance()->GetPin(GPIO_PIN7);
    GPIO_PIN* irSendPin = GPIOB::GetInstance()->GetPin(GPIO_PIN0);
    //GPIO_PIN* ch3 = GPIOB::GetInstance()->GetPin(GPIO_PIN1);
    irSendPin->SetupGPIO_OutAltPP();
    //ch1->SetupGPIO_OutAltPP();
    //ch2->SetupGPIO_OutAltPP();
    //ch3->SetupGPIO_OutAltPP();

    TIMER_Channel* ch = timer->GetChannel(3);
    ch->SetupPWM1(26, 13); //38KHZ 50% duty
    timer->EnableCounter(true);
    
    /*
    
     while (1)
    {
        ch->EnableChannel(true);
        RCC_Delay_ms(1);
        ch->EnableChannel(false);
        RCC_Delay_ms(20);
        
    }
    */
    
    IRSend irSend (timer->GetChannel(3));

    while(1)
    {
        irSend.SendSAMSUNG(0xE0E0D02F, 32);
        irSend.SendSAMSUNG(0xE0E0D02F, 32);
        irSend.SendSAMSUNG(0xE0E0D02F, 32);
        RCC_Delay_ms(20);
    }

}

int main()
{
#if defined (STM32F1)   
    RCC_EnableHSI(TRUE);
    //RCC_EnableHSI_72Mhz_AHB_72Mhz_APB1_36MHz_APB2_72MHz();
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
