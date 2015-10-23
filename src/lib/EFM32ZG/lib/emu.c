#include "emu.h"
#include "system_control.h"

void EMU_EnterEM1()
{
    SystemControl_SetSleepDeep(FALSE);
    __asm ("wfe");
}


void EMU_EnterEM2()
{
    SystemControl_SetSleepDeep(TRUE);
    __asm ("wfe");
}


void EMU_EnterEM3()
{
    //Disable LFA/LFB
    SystemControl_SetSleepDeep(TRUE);
    __asm ("wfe");
}

void EMU_EnterEM4()
{
    static uint8_t em4_sec[] = { 2, 3, 2, 3, 2, 3, 2, 3, 2 };
    for (uint8_t i = 0; i < sizeof(em4_sec); ++i)
    {
        EMU_CTRL |= (em4_sec[i] << EMU_CTRL_EM4CTRL_OFFSET);
    }
}
