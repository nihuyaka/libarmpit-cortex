#ifndef MOTIONAPP_READER_H
#define MOTIONAPP_READER_H

#include "MPU6050/MPU6050.h"
#include "usart_cpp.h"
#include "GPIO_Helper.h"

#ifndef M_PI
#define M_PI        3.14159265358979323846
#endif

class MotionAppReader
{
private:
	MPU6050    _mpu;
    float      _ypr[3]; // [yaw, pitch, roll] yaw/pitch/roll container and gravity vector
    Quaternion _q; // [w, x, y, z] quaternion container
    VectorFloat _gravity; // [x, y, z] gravity vector
    uint8_t    _fifoBuffer[64]; // FIFO storage buffer
    uint16_t   _packetSize; // expected DMP packet size (default is 42 bytes)


public:
	MotionAppReader(I2C* i2c);

	bool GetYPR(float* y, float* p, float* r);
	bool Init();
	void Reset();
};


#endif
