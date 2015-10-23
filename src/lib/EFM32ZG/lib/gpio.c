#include "gpio.h"

static GPIO_PORT _g_PORTS[10];

GPIO_PORT* GPIO_GetPort(GPIO_PORT_N portNumber)
{
	GPIO_PORT*  port  = &_g_PORTS[portNumber];

	if (port->Px_CTRL == NULL)
	{

		uint32_t baseAddr = GPIO_BASE + GPIO_PORT_RANGE*portNumber;

		port->Px_CTRL = (volatile uint32_t*) (baseAddr + GPIO_Px_OFFSET_CTRL);
		port->Px_MODEL = (volatile uint32_t*)  (baseAddr + GPIO_Px_OFFSET_MODEL );
		port->Px_MODEH = (volatile uint32_t*)  (baseAddr + GPIO_Px_OFFSET_MODEH );
		port->Px_DOUT = (volatile uint32_t*)  (baseAddr + GPIO_Px_OFFSET_DOUT );
		port->Px_DOUTSET = (volatile uint32_t*)  (baseAddr + GPIO_Px_OFFSET_DOUTSET );
		port->Px_DOUTCLR = (volatile uint32_t*)  (baseAddr + GPIO_Px_OFFSET_DOUTCLR );
		port->Px_DOUTTGL = (volatile uint32_t*)  (baseAddr + GPIO_Px_OFFSET_DOUTTGL );
		port->Px_DIN = (volatile uint32_t*)  (baseAddr + GPIO_Px_OFFSET_DIN );
		port->Px_PINLOCKN = (volatile uint32_t*)  (baseAddr + GPIO_Px_OFFSET_PINLOCKN );
		port->EXTIPSELL = (volatile uint32_t*)  (baseAddr + GPIO_OFFSET_EXTIPSELL );
		port->EXTIPSELH = (volatile uint32_t*)  (baseAddr + GPIO_OFFSET_EXTIPSELH );
		port->EXTIRISE = (volatile uint32_t*)  (baseAddr + GPIO_OFFSET_EXTIRISE );
		port->EXTIFALL = (volatile uint32_t*)  (baseAddr + GPIO_OFFSET_EXTIFALL );
		port->IEN = (volatile uint32_t*)  (baseAddr + GPIO_OFFSET_IEN );
		port->IF = (volatile uint32_t*)  (baseAddr + GPIO_OFFSET_IF );
		port->IFS = (volatile uint32_t*)  (baseAddr + GPIO_OFFSET_IFS );
		port->IFC = (volatile uint32_t*)  (baseAddr + GPIO_OFFSET_IFC );
		port->ROUTE = (volatile uint32_t*)  (baseAddr + GPIO_OFFSET_ROUTE );
		port->INSENSE = (volatile uint32_t*)  (baseAddr + GPIO_OFFSET_INSENSE );
		port->LOCK = (volatile uint32_t*)  (baseAddr + GPIO_OFFSET_LOCK);
		port->CTRL = (volatile uint32_t*)  (baseAddr + GPIO_OFFSET_CTRL);
		port->CMD = (volatile uint32_t*)  (baseAddr + GPIO_OFFSET_CMD );
		port->EM4WUEN = (volatile uint32_t*)  (baseAddr + GPIO_OFFSET_EM4WUEN );
		port->EM4WUPOL = (volatile uint32_t*)  (baseAddr + GPIO_OFFSET_EM4WUPOL );
		port->EM4WUCAUSE = (volatile uint32_t*)  (baseAddr + GPIO_OFFSET_EM4WUCAUSE );

		for (uint8_t i = 0; i < 16; ++i)
		{
			port->pins[i].pinNumber = (GPIO_PIN_N)i;
			port->pins[i].portNumber = portNumber;
		}
	}

	return port;
}

GPIO_PIN*  GPIO_GetPin(GPIO_PORT* port, GPIO_PORT_N pinNumber)
{
	return &port->pins[pinNumber];
}


void GPIO_SetDriveMode_STANDARD(GPIO_PORT* port)
{
	*port->Px_CTRL &= ~GPIO_Px_CTRL_DRIVERMODE_CLEARMASK;
	*port->Px_CTRL |= GPIO_Px_CTRL_DRIVERMODE_STANDARD;
}

void GPIO_SetDriveMode_LOWEST(GPIO_PORT* port)
{
	*port->Px_CTRL &= ~GPIO_Px_CTRL_DRIVERMODE_CLEARMASK;
	*port->Px_CTRL |= GPIO_Px_CTRL_DRIVERMODE_LOWEST;
}
void GPIO_SetDriveMode_HIGH(GPIO_PORT* port)
{
	*port->Px_CTRL &= ~GPIO_Px_CTRL_DRIVERMODE_CLEARMASK;
	*port->Px_CTRL |= GPIO_Px_CTRL_DRIVERMODE_HIGH;
}
void GPIO_SetDriveMode_LOW(GPIO_PORT* port)
{
	*port->Px_CTRL &= ~GPIO_Px_CTRL_DRIVERMODE_CLEARMASK;
	*port->Px_CTRL |= GPIO_Px_CTRL_DRIVERMODE_LOW;
}


void GPIO_RemapEXTI(GPIO_PORT* port, EXTI_LINE line)
{
	volatile uint32_t*  EXTIPSEL = (line < 8) ?
			port->EXTIPSELL : port->EXTIPSELH;


	*EXTIPSEL &= ~ (GPIO_EXTIPSEL_CLEARMASK << (line % 2));

	*EXTIPSEL |=  (port->portNo << (line % 2));

}


static volatile uint32_t* GPIO_GetModeOffset(GPIO_PIN* pin)
{
	return ((uint8_t)pin->pinNumber < 8) ?
			GPIO_GetPort(pin->portNumber)->Px_MODEL: GPIO_GetPort(pin->portNumber)->Px_MODEH;


}

static uint8_t GPIO_GetMode(GPIO_PIN* pin)
{
	volatile uint32_t*  PxMode = GPIO_GetModeOffset(pin);
	return *PxMode >>  ((uint8_t)pin->pinNumber % 2);
}

void GPIO_DisablePin (GPIO_PIN* pin)
{
	volatile uint32_t*  PxMode = GPIO_GetModeOffset(pin);
	*PxMode &= ~ (GPIO_Px_MODE_CLEARMASK << ((uint8_t)pin->pinNumber % 2));
	*PxMode |= (GPIO_Px_MODE_DISABLED << ((uint8_t)pin->pinNumber % 2));
}

void GPIO_SetupInFloat (GPIO_PIN* pin)
{
	volatile uint32_t*  PxMode = GPIO_GetModeOffset(pin);
	*PxMode &= ~ (GPIO_Px_MODE_CLEARMASK << ((uint8_t)pin->pinNumber % 2));
	*PxMode |= (GPIO_Px_MODE_INPUT << ((uint8_t)pin->pinNumber % 2));
}

void GPIO_SetupInAnalog (GPIO_PIN* pin)
{
	GPIO_SetupInFloat(pin);
}

void GPIO_SetupInPullUp (GPIO_PIN* pin)
{
	volatile uint32_t*  PxMode = GPIO_GetModeOffset(pin);
	*PxMode &= ~ (GPIO_Px_MODE_CLEARMASK << ((uint8_t)pin->pinNumber % 2));
	*PxMode |= (GPIO_Px_MODE_INPUTPULL << ((uint8_t)pin->pinNumber % 2));
	GPIO_Set(pin);
}

void GPIO_SetupInPullDown (GPIO_PIN* pin)
{
	volatile uint32_t*  PxMode = GPIO_GetModeOffset(pin);
	*PxMode &= ~ (GPIO_Px_MODE_CLEARMASK << ((uint8_t)pin->pinNumber % 2));
	*PxMode |= (GPIO_Px_MODE_INPUTPULL << ((uint8_t)pin->pinNumber % 2));

}
void GPIO_SetupOutPP (GPIO_PIN* pin)
{
	volatile uint32_t*  PxMode = GPIO_GetModeOffset(pin);
	*PxMode &= ~ (GPIO_Px_MODE_CLEARMASK << ((uint8_t)pin->pinNumber % 2));
	*PxMode |= (GPIO_Px_MODE_PUSHPULL << ((uint8_t)pin->pinNumber % 2));

}
void GPIO_SetupOutOD (GPIO_PIN* pin)
{
	volatile uint32_t*  PxMode = GPIO_GetModeOffset(pin);
	*PxMode &= ~ (GPIO_Px_MODE_CLEARMASK << ((uint8_t)pin->pinNumber % 2));
}


void GPIO_EnableFilter (GPIO_PIN* pin)
{
	volatile uint32_t*  PxMode = GPIO_GetModeOffset(pin);

}


void GPIO_Set (GPIO_PIN* pin)
{
	*(GPIO_GetPort(pin->portNumber)->Px_DOUTSET) |= 1<<(uint8_t)pin->pinNumber;
}
void GPIO_Toggle (GPIO_PIN* pin)
{
	*(GPIO_GetPort(pin->portNumber)->Px_DOUTTGL) |= 1<<(uint8_t)pin->pinNumber;

}
void GPIO_Reset (GPIO_PIN* pin)
{
	*(GPIO_GetPort(pin->portNumber)->Px_DOUTCLR) |= 1<<(uint8_t)pin->pinNumber;
}

BOOL GPIO_IsSet (GPIO_PIN* pin)
{
	return 	*(GPIO_GetPort(pin->portNumber)->Px_DIN) & (1<<(uint8_t)pin->pinNumber);

}
void GPIO_PullUp(GPIO_PIN* pin)
{

}
void GPIO_PullDown(GPIO_PIN* pin)
{

}


