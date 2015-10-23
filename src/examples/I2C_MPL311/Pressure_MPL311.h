/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 igorS
 *  
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */



#ifndef _MPL311_H
#define _MPL311_H
#include "i2c_cpp.h"

//output data
#define OUT_P_MSB        0x01  //19-12
#define OUT_P_CSB        0x02  //11-4
#define OUT_P_LSB        0x03  //3-0
#define OUT_T_MSB        0x04  //11-4
#define OUT_T_LSB        0x05  //3-0

#define STATUS           0x00  //alias of 0x6
#define DR_STATUS        0x06  //same as 0x00 and 0xd

#define DR_STATUS_TDR   (1<<1) //new temp data ready
#define DR_STATUS_PDR   (1<<2) //new pressure data ready
#define DR_STATUS_PTDR  (1<<3) //t or p ready
#define DR_STATUS_TOW   (1<<5) // t overwrite
#define DR_STATUS_POW   (1<<6) // p overwrite
#define DR_STATUS_PTOW  (1<<7) //t or p overwrite

#define F_STATUS         0x0D  // alias of 0x06
#define F_STATUS_F_WMRK_FLAG  (6<<1)
#define F_STATUS_F_OVF        (7<<1)

#define OUT_P_DELTA_MSB  0x07  //19-12
#define OUT_P_DELTA_CSB  0x08  //11-4
#define OUT_P_DELTA_LSB  0x09  //3-0

#define OUT_T_DELTA_MSB  0x0A  //11-4
#define OUT_T_DELTA_LSB  0x0B  //3-0

#define WHO_AM_I         0x0C

#define F_DATA           0x0E  //same as 0x01

#define F_SETUP          0x0F

#define F_SETUP_F_WMRK0          (1<<0)
#define F_SETUP_F_FIFO_OFF       (0<<6)
#define F_SETUP_F_FIFO_CIRCULAR  (1<<6)
#define F_SETUP_F_FIFO_ONCE      (2<<6)
#define F_SETUP_F_FIFO_CLEARMASK (3<<6)

#define TIME_DELAY       0x10

#define SYSMOD           0x11
#define SYSMOD_ACTIVE            (1<<0)

#define INT_SOURCE       0x12

#define INT_SRC_TCHG  (1<<0)
#define INT_SRC_PCHG  (1<<1)
#define INT_SRC_TTH   (1<<2)
#define INT_SRC_PTH   (1<<3)
#define INT_SRC_TW    (1<<4)
#define INT_SRC_PW    (1<<5)
#define INT_SRC_FIFO  (1<<6)
#define INT_SRC_DRDY  (1<<7)

#define PT_DATA_CFG      0x13
#define PT_DATA_CFG_TDEFE     (1<<0)
#define PT_DATA_CFG_PDEFE     (1<<1)
#define PT_DATA_CFG_DREM      (1<<2)

#define BAR_IN_MSB       0x14
#define BAR_IN_LSB       0x15

#define P_TGT_MSB        0x16
#define P_TGT_LSB        0x17

#define T_TGT            0x18

#define P_WND_MSB        0x19
#define P_WND_LSB        0x1A

#define T_WND            0x1B

#define P_MIN_MSB        0x1C  //19-12
#define P_MIN_CSB        0x1D  //11-4
#define P_MIN_LSB        0x1E  //3-0

#define T_MIN_MSB        0x1F  //11-4
#define T_MIN_LSB        0x20  //3-0

#define P_MAX_MSB        0x21  //19-12
#define P_MAX_CSB        0x22  //11-4
#define P_MAX_LSB        0x23  //3-0

#define T_MAX_MSB        0x24  //11-4
#define T_MAX_LSB        0x25  //3-0

#define OFF_P            0x2B
#define OFF_T            0x2C
#define OFF_H            0x2D

#define CTRL_REG1        0x26

#define CTRL_REG1_SBYB          (1<<0)
#define CTRL_REG1_OST           (1<<1)
#define CTRL_REG1_RST           (1<<2)
#define CTRL_REG1_OS_6MS        (0<<3)
#define CTRL_REG1_OS_10MS       (1<<3)
#define CTRL_REG1_OS_18MS       (2<<3)
#define CTRL_REG1_OS_34MS       (3<<3)
#define CTRL_REG1_OS_66MS       (4<<3)
#define CTRL_REG1_OS_130MS      (5<<3)
#define CTRL_REG1_OS_258MS      (6<<3)
#define CTRL_REG1_OS_512MS      (7<<3)
#define CTRL_REG1_OS_CLEARMASK  (7<<3)
#define CTRL_REG1_RAW           (1<<6)
#define CTRL_REG1_ALT           (1<<7)

#define CTRL_REG2        0x27

#define CTRL_REG2_ST_1SEC   (0<<0)
#define CTRL_REG2_ST_2SEC   (1<<0)
#define CTRL_REG2_ST_4SEC   (2<<0)
#define CTRL_REG2_ST_8SEC   (3<<0)
#define CTRL_REG2_ST_16SEC  (4<<0)
#define CTRL_REG2_ST_32SEC  (5<<0)
#define CTRL_REG2_ST_1MIN   (6<<0)
#define CTRL_REG2_ST_2MIN   (7<<0)
#define CTRL_REG2_ST_4MIN   (8<<0)
#define CTRL_REG2_ST_8MIN   (9<<0)
#define CTRL_REG2_ST_16MIN  (10<<0)
#define CTRL_REG2_ST_32MIN  (11<<0)
#define CTRL_REG2_ST_1H     (12<<0)
#define CTRL_REG2_ST_2H     (13<<0)
#define CTRL_REG2_ST_4H     (14<<0)
#define CTRL_REG2_ST_8H     (15<<0)
#define CTRL_REG2_ST_CLEARMASK     (0xf)
#define CTRL_REG2_ALARM_SEL   (1<<4)
#define CTRL_REG2_LOAD_OUTPUT (1<<4)

#define CTRL_REG3        0x28

#define CTRL_REG3_IPOL1    (1<<0)
#define CTRL_REG3_PP_OD1   (1<<1)
#define CTRL_REG3_IPOL2    (1<<4)
#define CTRL_REG3_PP_OD2   (1<<5)

#define CTRL_REG4        0x29

#define CTRL_REG4_INT_EN_DRDY  (1<<0)
#define CTRL_REG4_INT_EN_FIFO  (1<<1)
#define CTRL_REG4_INT_EN_PW    (1<<2)
#define CTRL_REG4_INT_EN_TW    (1<<3)
#define CTRL_REG4_INT_EN_PTH   (1<<4)
#define CTRL_REG4_INT_EN_TTH   (1<<5)
#define CTRL_REG4_INT_EN_PCHG  (1<<6)
#define CTRL_REG4_INT_EN_TCHG  (1<<7)

#define CTRL_REG5        0x2A

#define CTRL_REG5_INT_CFG_DRDY  (1<<0)
#define CTRL_REG5_INT_CFG_FIFO  (1<<1)
#define CTRL_REG5_INT_CFG_PW    (1<<2)
#define CTRL_REG5_INT_CFG_TW    (1<<3)
#define CTRL_REG5_INT_CFG_PTH   (1<<4)
#define CTRL_REG5_INT_CFG_TTH   (1<<5)
#define CTRL_REG5_INT_CFG_PCHG  (1<<6)
#define CTRL_REG5_INT_CFG_TCHG  (1<<7)

enum OSR
{
    OSR_6MS = 0,
    OSR_10MS = 1,
    OSR_18MS = 2,
    OSR_34MS = 3,
    OSR_66MS = 4,
    OSR_130MS = 5,
    OSR_258MS = 6,
    OSR_512MS = 7
};

#define MPL311_SLAVE_ADDR  0x60<<1

class Pressure_MPL311
{
private:
    I2C* _i2c;
    bool _initialized;
    bool _isAltimeterMode;

public:

    Pressure_MPL311(I2C* i2c)
    {
        _i2c = i2c;
        _initialized = false;
        _isAltimeterMode = false;
    }

    void InitializeI2C();
    void InitializeSensor(bool isAltimeterMode, OSR osr);

    double GetPressure();
    float GetAltitude();
    uint16_t GetTemperature();

    void SetModePolling();
    void SetModeInterrupt();
    void SetModeFIFO();

    uint8_t GetDeviceID();
};

#endif
