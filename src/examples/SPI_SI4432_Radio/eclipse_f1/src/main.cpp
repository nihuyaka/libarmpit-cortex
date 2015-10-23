#include "gpio_cpp.h"
#include "RCC_Helper.h"
#include "si4432.h"
#include "GPIO_Helper.h"

static void test()
{
	SPI* spi = GPIO_Helper::SetupSPI2_MasterMode_PB_13_14_15(false, false, SPI_BAUD_RATE_32);
	GPIOB::GetInstance()->EnablePeripheralClock(true);
	GPIO_PIN* ssPin = GPIOB::GetInstance()->GetPin(GPIO_PIN12);
	GPIO_PIN* sdnPin = GPIOB::GetInstance()->GetPin(GPIO_PIN11);

	Si4432 radio(spi, ssPin, sdnPin, 0);
	radio.init();
	radio.setBaudRate(70);
	radio.setFrequency(433);
	radio.readAll();

}

int main()
{
    RCC_EnableHSI_24Mhz();
    test();

}
