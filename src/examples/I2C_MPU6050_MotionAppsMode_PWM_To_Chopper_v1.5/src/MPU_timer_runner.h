#ifndef MPU_TIMER_RUNNER_H
#define MPU_TIMER_RUNNER_H

#include "timer_cpp.h"
#include "i2c_cpp.h"
#include "motionapp_reader.h"

#include "chopper_esc.h"
#include "PidController.h"
#include "usart_cpp.h"
#include "GPIO_Helper.h"

#define SAMPLE_INTERVAL 20
class MPU_Timer_Runner
{

private:

	MotionAppReader _motionApp;


#ifdef USE_USART
	USART* usart;
#endif

	Chopper_ESC* _esc;

	bool _running;
	PidController _pidRoll, _pidYaw, _pidPitch;



public:

	MPU_Timer_Runner(I2C* i2c, Chopper_ESC* esc);

	void Start();
	void Stop();
	void Run();

	virtual ~MPU_Timer_Runner() {}



};

#endif
