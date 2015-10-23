#include "i2c_cpp.h"
#define MPU6050_ADDR 0x68<<1

#include "MPU6050.h"
#include <stdlib.h>
#include "timer_cpp.h"
#include "flash.h"
#include "rcc.h"
#include "RCC_helper.h"
#include "GPIO_Helper.h"



class TestMPU6050: public I2C_ErrorHandler
{
private:

	static void intro_blink(void)
	{
		//Use the user LED pins in a standard output mode
		GPIOD::GetInstance()->EnablePeripheralClock(true);
		GPIO_PIN* pins[4] =
		{
				GPIOD::GetInstance()->GetPin(GPIO_PIN12), //green
				GPIOD::GetInstance()->GetPin(GPIO_PIN13), //orange
				GPIOD::GetInstance()->GetPin(GPIO_PIN14), //red
				GPIOD::GetInstance()->GetPin(GPIO_PIN15) //blue

		};

		for (int i = 0; i < 4; ++i)
		{
			pins[i]->SetupGPIO_OutPP();
		}

		for (uint16_t i = 0; i < 10 * 4; ++i)
		{
			pins[i % 4]->Set();
			RCC_Delay_ms(100);
			pins[i % 4]->Reset();
		}

		for (int i = 0; i < 4; ++i)
		{
			pins[i]->Reset();
		}

	}

	void Init_MPU()
	{
		//mpu.setXGyroOffset(220);
		//mpu.setYGyroOffset(76);
		//mpu.setZGyroOffset(-85);

		//change sensitivity
		//mpu.setFullScaleAccelRange(...)
		//mpu.setFullScaleGyroRange(...)

		//lowest sensitivity
		//mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);
		//mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);

		//medium sensitivity
		//mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
		//mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_1000);
	}

public:

	TestMPU6050()
	{
	}

	virtual void HandleError()
	{
	}

    void Run(uint32_t i2cClockSpeed)
	{
		intro_blink();

        I2C* i2c = GPIO_Helper::F4_SetupI2C1_PB_6_9(i2cClockSpeed);
        i2c->SetErrorHandler(this);
        MPU6050 mpu(i2c);
        mpu.reset();
        RCC_Delay_ms(50);
        mpu.initialize(); //highest sensitivity
        uint8_t id = mpu.getDeviceID();
        mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_500);
        //lowest sensitivity
        //mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);
        //mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);

        //medium sensitivity
        //mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
        //mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_1000);

        //low pass filtering
        mpu.setDLPFMode(MPU6050_DLPF_BW_5);

        //high pass filter
        //mpu.setDHPFMode (MPU6050_DHPF_0P63);


		uint16_t max_threshold = 500;
		uint16_t read_delay_ms = 20;
		uint16_t min_threshold = 20;

		//Now the same LED pins are re-configured as timer PWM outputs:
		TIM4* timer = GPIO_Helper::F4_SetupTIM4_PD_12_13_14_15();

		//green: negative X
		TIMER_Channel* ch1_green = timer->GetChannel(1);
		ch1_green->SetupPWM1(max_threshold, 0);
		ch1_green->EnableChannel(true);

		//orange: positive Y
		TIMER_Channel* ch2_orange = timer->GetChannel(2);
		ch2_orange->SetupPWM1(max_threshold, 0);
		ch2_orange->EnableChannel(true);

		//red: positive X
		TIMER_Channel* ch3_red = timer->GetChannel(3);
		ch3_red->SetupPWM1(max_threshold, 0);
		ch3_red->EnableChannel(true);

		//blue: negative Y
		TIMER_Channel* ch4_blue = timer->GetChannel(4);
		ch4_blue->SetupPWM1(max_threshold, 0);
		ch4_blue->EnableChannel(true);

		timer->EnableCounter(true);


		//high pass filter
		//mpu.setDHPFMode (MPU6050_DHPF_0P63);
		uint16_t warmup = 0;
		uint16_t max_a = 0;
		uint16_t max_warmup = 1000;
		int16_t ax, ay, az;
		int16_t gx, gy, gz;

		int16_t ax_offset = 0, ay_offset = 0, az_offset = 0;
		int16_t gx_offset = 0, gy_offset = 0, gz_offset = 0;

		for (uint16_t i = 0; i < max_warmup; ++i)
		{
			mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
		}
		ax_offset = ax;
		ay_offset = ay;
		az_offset = az;
		gx_offset = gx;
		gy_offset = gy;
		gz_offset = gz;

		while (1)
		{
			mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

			ax -= ax_offset;
			ay -= ay_offset;
			az -= az_offset;
			gx -= gx_offset;
			gy -= gy_offset;
			gz -= gz_offset;

			if (abs(ax) > max_a)
			{
				max_a = abs(ax);
			}
			if (abs(ay) > max_a)
			{
				max_a = abs(ay);
			}
			if (abs(az) > max_a)
			{
				max_a = abs(az);
			}

			TIMER_Channel* chx = 0;
			TIMER_Channel* chy = 0;
			if (abs(ax) > min_threshold)
			{
				if (ax > 0)
				{
					chx = ch3_red;
				}
				else
				{
					chx = ch1_green;
					ax = abs(ax);
				}

				chx->UpdatePWMDuty(ax);
			}

			if (abs(ay) > min_threshold)
			{
				if (ay > 0)
				{
					chy = ch2_orange;
				}
				else
				{
					chy = ch4_blue;
					ay = abs(ay);
				}

				chy->UpdatePWMDuty(ay);
			}

			RCC_Delay_ms(2);
			if (chx)
			{
				chx->UpdatePWMDuty(0);
			}
			if (chy)
			{
				chy->UpdatePWMDuty(0);
			}

			//same thing but separate a and g
			//mpu.getAcceleration(&ax, &ay, &az);
			//mpu.getRotation(&gx, &gy, &gz);
		}

	}
};

int main()
{
    F4_EnableHSI_100Mhz();
    TestMPU6050 test;
    uint32_t i2cClockSpeed = 100000;
    test.Run(i2cClockSpeed);
}
