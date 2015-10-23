#include "IRSend.h"
#include "rcc.h"


IRSend::IRSend(TIMER_Channel* pwmChannel)
{
	_pwmChannel = pwmChannel;
    _pwmChannel->SetupPWM1(26, 13); //38KHZ 50% duty
    _pwmChannel->EnableChannel(true);
    _pwmChannel->GetTimer()->EnableCounter(true);
}



#if false
void  IRsend::sendShuzu (unsigned long data,  int nbits)
{
    // Set IR carrier frequency
    enableIROut(38);

    // Header
    mark (HDR_MARK);
    space(HDR_SPACE);

    // Data
    for (unsigned long  mask = 1UL << (nbits - 1);  mask;  mask >>= 1) {
        if (data & mask) {
            mark (BIT_MARK);
            space(ONE_SPACE);
        } else {
            mark (BIT_MARK);
            space(ZERO_SPACE);
        }
    }

    // Footer
    SendMark(BIT_MARK);
    space(0);  // Always end with the LED off
}
#endif



void  IRSend::SendSAMSUNG (uint32_t data,  uint8_t nbits)
{

    SendMark(SAMSUNG_HDR_MARK);
    SendSpace(SAMSUNG_HDR_SPACE);

    for (unsigned long  mask = 1UL << (nbits - 1);  mask;  mask >>= 1)
    {
        if (data & mask)
        {
            SendMark(SAMSUNG_BIT_MARK);
            SendSpace(SAMSUNG_ONE_SPACE);
        } else
        {
            SendMark(SAMSUNG_BIT_MARK);
            SendSpace(SAMSUNG_ZERO_SPACE);
        }
    }

    // Footer
    SendMark(SAMSUNG_BIT_MARK);
    SendSpace(0);  // Always end with the LED off
}

void IRSend::SendMark  (uint32_t time_us)
{
	_pwmChannel->EnableChannel(true);
	RCC_Delay_us(time_us);
}

void IRSend::SendSpace (uint32_t time_us)
{
	_pwmChannel->EnableChannel(false);
	RCC_Delay_us(time_us);
}


