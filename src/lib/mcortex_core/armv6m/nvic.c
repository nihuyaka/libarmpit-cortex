#include "nvic.h"

void NVIC_SetEnable (IRQn_Type irqNo) 
{
    NVIC_ISER |= irqNo;
}

int NVIC_IsEnabled (IRQn_Type irqNo) 
{
    return (NVIC_ISER & irqNo);
}


void NVIC_ClearEnable (IRQn_Type irqNo) 
{
    NVIC_ICER |= irqNo;
}


void NVIC_SetPending (IRQn_Type irqNo) 
{
    NVIC_ISPR |= irqNo;
}

int NVIC_IsPending (IRQn_Type irqNo) 
{
    return (NVIC_ISPR & irqNo);
}


void NVIC_ClearPending (IRQn_Type irqNo) 
{
    NVIC_ICPR |= irqNo;
}


void NVIC_SetPriority (IRQn_Type irqNo, uint8_t priority) 
{
    (&NVIC_IPR)[irqNo / 8] |= (priority<<(irqNo % 8));
}

int NVIC_GetPriority (IRQn_Type irqNo)
{   
    return ( (((&NVIC_IPR)[irqNo / 8]) >> (irqNo % 8))  & 0xC0 );
}
