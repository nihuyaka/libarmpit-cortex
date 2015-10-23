#include "peripheral.h"

void Peripheral::EnablePeripheralClock(bool enable) 
{
    if (enable) 
    {
        *_resetReg &= ~_bit;
        *_enableReg |= _bit;
    }
    else 
    {
        *_resetReg |= _bit;
        *_enableReg &= ~_bit;
    }
}

bool Peripheral::IsClockEnabled()
{
    return (*_enableReg & _bit);
}

