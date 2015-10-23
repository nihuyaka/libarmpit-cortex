#ifndef PERIPHERAL_H 
#define PERIPHERAL_H

#include "common.h"

class Peripheral
{
    
private:
    volatile uint32_t*  _enableReg;
    volatile uint32_t*  _resetReg;
    uint32_t   _bit;
    
public:
    Peripheral (volatile uint32_t* enableReg, volatile uint32_t* resetReg, uint32_t bit)
    {
        _enableReg = enableReg;
        _resetReg = resetReg;
        _bit = bit;    
    }
    void EnablePeripheralClock(bool enable);
    bool IsClockEnabled();
    
};



#endif
