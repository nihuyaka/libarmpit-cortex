#include "gpio_cpp.h"
#include "RCC_Helper.h"
#include "si4432.h"
#include "GPIO_Helper.h"
#include "LED_Indicators.h"

static void test()
{
	GPIOA::GetInstance()->EnablePeripheralClock(true);
	GPIOC::GetInstance()->EnablePeripheralClock(true);

	SPI* spi = GPIO_Helper::SetupSPI1_MasterMode_PA_5_6_7(false, false, SPI_BAUD_RATE_32);
	GPIO_PIN* ssPin = GPIOA::GetInstance()->GetPin(GPIO_PIN4);
	GPIO_PIN* sdnPin = GPIOC::GetInstance()->GetPin(GPIO_PIN4);

	Si4432 radio(spi, ssPin, sdnPin, 0);
	radio.init();
	radio.setBaudRate(70);
	radio.setFrequency(433);
	radio.readAll();

	//receiver

	radio.startListening();
	LED_Indicators::GetInstance()->RGB_SteadyGreen(1000);
	LED_Indicators::GetInstance()->RGB_Off();

	uint8_t data[64] = {0};
	uint8_t len = 0;

	while(1)
	{
		if (radio.isPacketReceived())
		{
			LED_Indicators::GetInstance()->RGB_SteadyRed(100);
			radio.getPacketReceived(&len, data);

			LED_Indicators::GetInstance()->RGB_Off();
			radio.startListening();
		}

		RCC_Delay_ms(10);
	}


}


int main()
{
    RCC_EnableHSI_100Mhz();
    test();

}

