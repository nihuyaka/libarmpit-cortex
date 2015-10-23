#include "motionapp_reader.h"
#include "rcc.h"

MotionAppReader::MotionAppReader(I2C* i2c) : _mpu(i2c)
{
	_packetSize = 0;

}

bool MotionAppReader::Init()
{
    //Initialized with highest sensitivities
    _mpu.reset();
    RCC_Delay_ms(50);
    _mpu.initialize();

    bool rc = false;

    if (_mpu.dmpInitialize() == 0)
    {
    	_mpu.setDMPEnabled(true);
    	_packetSize = _mpu.dmpGetFIFOPacketSize();
    	rc = true;
    }

    return rc;

}

void MotionAppReader::Reset()
{
    _mpu.reset();
}


bool MotionAppReader::GetYPR(float* y, float* p, float* r)
{
	bool rc = false;
	uint16_t fifoCount;
	uint8_t mpuIntStatus = _mpu.getIntStatus();

	fifoCount = _mpu.getFIFOCount();

	if (mpuIntStatus & 0x02)
	{
		while (fifoCount < _packetSize)
			fifoCount = _mpu.getFIFOCount();


		_mpu.getFIFOBytes(_fifoBuffer, _packetSize);

		fifoCount -= _packetSize;

		_mpu.dmpGetQuaternion(&_q, _fifoBuffer);
		_mpu.dmpGetGravity(&_gravity, &_q);
		_mpu.dmpGetYawPitchRoll(_ypr, &_q, &_gravity);

		_ypr[0] *= 180. / M_PI;
		_ypr[1] *= 180. / M_PI;
		_ypr[2] *= 180. / M_PI;

		*y = _ypr[0];
		*p = _ypr[1];
		*r = _ypr[2];

		rc = true;

	}
	else if ((mpuIntStatus & 0x10) || fifoCount >= 1024)
	{
		_mpu.resetFIFO();
	}

	return rc;

}
