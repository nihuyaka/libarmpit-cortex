#ifndef _IR_SEND
#define _IR_SEND

#include "timer_cpp.h"
#include "IRRemote.h"

class IRSend
{
private:

	TIMER_Channel* _pwmChannel;

public:

	IRSend (TIMER_Channel* pwmChannel);

	void SendSpace (uint32_t time_us);
	void SendMark  (uint32_t time_us);

	void SendSAMSUNG (uint32_t data,  uint8_t nbits);

};


#endif
