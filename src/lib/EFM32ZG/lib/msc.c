#include "msc.h" 

//1== >16Mhz, otherwise 0
void FLASH_SetWaitState(uint8_t wait_state)
{
    if (wait_state)
    {
        MSC_READCTRL |= MSC_READCTRL_MODE;
    }
    else 
    {
        MSC_READCTRL &= ~MSC_READCTRL_MODE;
    }

}

void FLASH_EnableIFlashCache (BOOL enable)
{
	if (enable)
	{
		MSC_READCTRL |= MSC_READCTRL_IFCDIS;
	}
	else
	{
		MSC_READCTRL &= ~MSC_READCTRL_IFCDIS;
	}

}
void FLASH_EnableAutomaticInvalidate (BOOL enable)
{
	if (enable)
	{
		MSC_READCTRL |= MSC_READCTRL_AIDIS;
	}
	else
	{
		MSC_READCTRL &= ~MSC_READCTRL_AIDIS;
	}

}
void FLASH_EnableRAMCache (BOOL enable)
{
	if (enable)
	{
		MSC_READCTRL |= MSC_READCTRL_RAMCEN;
	}
	else
	{
		MSC_READCTRL &= ~MSC_READCTRL_RAMCEN;
	}

}


void FLASH_EnableWriteEraseController (BOOL enable)
{
	if (enable)
	{
		MSC_WRITECTRL |= MSC_WRITECTRL_WREN;
	}
	else
	{
		MSC_WRITECTRL &= ~MSC_WRITECTRL_WREN;
	}

}

