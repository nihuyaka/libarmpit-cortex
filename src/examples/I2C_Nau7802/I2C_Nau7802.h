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



#ifndef _I2C_NAU7802_H
#define _I2C_NAU7802_H

#include "i2c_cpp.h"

#define REG0  0x00
#define REG1  0x01
#define REG2  0x02
#define REG12 0x12   //ADC 23-16
#define REG13 0x13   //ADC 15-8
#define REG14 0x14   //ADC 7-0
#define REG1F 0x1F   //revision iD

#define REG0_RR    1<<0
#define REG0_PUD   1<<1
#define REG0_PUA   1<<2
#define REG0_PUR   1<<3
#define REG0_CS    1<<4
#define REG0_CR    1<<5
#define REG0_OSCS  1<<6
#define REG0_AVDDS 1<<7

#define REG2_CALS     1<<2
#define REG2_CAL_ERR  1<<3
#define REG2_CHS      1<<7  //channel select

#define NAU7802_ADDR  0x2a<<1
#define CAL_INTERNAL 0x0
#define CAL_OFFSET   0x2
#define CAL_GAIN     0x3

class I2C_Nau7802: public I2C_ErrorHandler
{
private:
    I2C* _i2c;
    bool _initialized;

    bool Calibrate(uint8_t mode);

protected:
    virtual void HandleError();

public:

    I2C_Nau7802(I2C* i2c);

    void InitializeSensor();
    void InitializeI2C();
    uint32_t Convert();

};

#endif
