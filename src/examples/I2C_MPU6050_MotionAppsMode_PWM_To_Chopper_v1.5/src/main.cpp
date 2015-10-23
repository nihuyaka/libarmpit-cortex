
#include <stdlib.h>
#include "timer_cpp.h"
#include "flash.h"
#include "rcc.h"
#include "RCC_helper.h"
#include "GPIO_Helper.h"
#include "nvic.h"
#include "chopper_esc.h"
#include "MPU_timer_runner.h"

#include "usart_cpp.h"
#include "GPIO_Helper.h"
#include "LED_Indicators.h"

static void* I2C_Error (void* arg)
{
	((Chopper_ESC*)arg)->TurnOff();
	while(1)
	{
		LED_Indicators::GetInstance()->RGB_BlinkingRed(1000, 500, 1000);
	}
	return NULL;
}


static void run(uint32_t i2cClockSpeed)
{

#if defined (STM32F407xx)
	Chopper_ESC esc (GPIO_Helper::SetupTIM4_PD_12_13_14_15());
#else
	Chopper_ESC esc (GPIO_Helper::SetupTIM2_PA_0_1_2_3());
#endif
	esc.Init();

	I2C1* i2c = GPIO_Helper::SetupI2C1_PB_6_9(i2cClockSpeed);
	i2c->SetErrorCallback (I2C_Error, &esc);

	LED_Indicators::GetInstance()->RGB_BlinkingGreen(1000, 500, 5000);

	MPU_Timer_Runner runner (i2c, &esc);

	esc.TurnOn();



//	RCC_Delay_ms(1000);

	runner.Start();


	runner.Run();

	esc.TurnOff();


	LED_Indicators::GetInstance()->RGB_BlinkingBlue(1000, 500, 2000);

	while(1)
	{

	}

}


int main()
{
#if defined (STM32F1)

	RCC_EnableHSI_72Mhz_AHB_72Mhz_APB1_36MHz_APB2_72MHz();

#elif defined(STM32F4) || defined(STM32F2)

// 	RCC_Delay_ms(3000);
    	RCC_EnableHSI_100Mhz();
	//RCC_EnableHSI(true);
	RCC_SetAHBPrescalerDiv2();

#endif
	uint32_t i2cClockSpeed = 100000;
	//uint32_t i2cClockSpeed = 20000;



	run(i2cClockSpeed);

	return 0;
}
