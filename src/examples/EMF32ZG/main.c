#include "cmu.h"
#include "gpio.h" 

void SystemInit(void) 
{
	volatile uint8_t i; 
	++i;
}
int main() 
{
	CMU_EnableHFRCO(TRUE);
	CMU_SelectHFCLK_HFRCO();
	
	CMU_EnableHFPERCLK (TRUE);	
	
	//CMU_Enable_Peripheral_GPIO(TRUE); 
	
	//GPIO_PORT* port = GPIO_GetPort(GPIOC);
	//GPIO_PIN* pin11 = GPIO_GetPin(port, GPIO_PIN11);
	while(1);
}
