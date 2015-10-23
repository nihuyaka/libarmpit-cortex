#include "gpio_cpp.h"
#include "RCC_Helper.h"
#include "si4432.h"
#include "GPIO_Helper.h"

static void test()
{
	SPI* spi = GPIO_Helper::SetupSPI1_MasterMode_PA_5_6_7(false, false, SPI_BAUD_RATE_32);
	GPIO_PIN* ssPin = GPIOA::GetInstance()->GetPin(GPIO_PIN4);
	GPIO_PIN* sdnPin = GPIOC::GetInstance()->GetPin(GPIO_PIN4);

	Si4432 radio(spi, ssPin, sdnPin, 0);
	radio.init();
	radio.setBaudRate(70);
	radio.setFrequency(433);
	radio.readAll();

}


int main()
{
    RCC_EnableHSI_100Mhz();
    test();

}
