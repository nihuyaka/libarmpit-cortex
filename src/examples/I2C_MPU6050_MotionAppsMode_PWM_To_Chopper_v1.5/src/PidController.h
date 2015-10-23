/*
 * PidController.h
 *
 *  Created on Sep 26, 2015
 *      Author U9X4259
 */

#ifndef PIDCONTROLLER_H_
#define PIDCONTROLLER_H_

#define MANUAL 0
#define AUTOMATIC 1

#define DIRECT 0
#define REVERSE 1

class PidController {

private:

	unsigned long lastTime;

	float ITerm, lastInput;

	int SampleTime = 20;
	float outMin, outMax;
	bool inAuto = false;
	int controllerDirection = DIRECT;

public:
	float Input, Output, Setpoint;
	float kp, ki, kd;

	PidController();

	virtual ~PidController();

	void Compute(unsigned long now);

	void SetTunings(float Kp, float Ki, float Kd);
	void SetSampleTime(int NewSampleTime);
	void SetOutputLimits(float Min, float Max);
	void SetMode(int Mode);
	void Initialize();
	void SetControllerDirection(int Direction);
};

#endif /* PIDCONTROLLER_H_ */
