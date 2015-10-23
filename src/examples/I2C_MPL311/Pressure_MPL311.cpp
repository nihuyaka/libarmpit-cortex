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



#include "Pressure_MPL311.h"

void Pressure_MPL311::InitializeI2C()
{
    bool initializeGPIO = true;
    _i2c->Initialize(20000, false, false, initializeGPIO);
    _i2c->SetModeI2C();
    _i2c->EnableACK(true);
    _i2c->SetOwnAddr7Bit(0x00);

}

void Pressure_MPL311::InitializeSensor(bool isAltimeterMode, OSR osr)
{
    if (!_initialized)
    {
        InitializeI2C();
        _initialized = true;
    }

    uint8_t ctrl1 = CTRL_REG1_RST;
    //Reset
    _i2c->MasterWriteRegister(&ctrl1, 1, MPL311_SLAVE_ADDR, CTRL_REG1);
    while (1)
    {
        _i2c->MasterReadRegister(&ctrl1, 1, MPL311_SLAVE_ADDR, CTRL_REG1);
        if (!(ctrl1 & CTRL_REG1_RST))
        {
            break;
        }
    }

    if (isAltimeterMode)
    {
        ctrl1 = CTRL_REG1_ALT;
    }
    else
    {
        ctrl1 = 0;
    }

    ctrl1 |= (osr | CTRL_REG1_SBYB);
    _i2c->MasterWriteRegister(&ctrl1, 1, MPL311_SLAVE_ADDR, CTRL_REG1);

    uint8_t data_cfg = PT_DATA_CFG_DREM | PT_DATA_CFG_PDEFE | PT_DATA_CFG_TDEFE;

    _i2c->MasterWriteRegister(&data_cfg, 1, MPL311_SLAVE_ADDR, PT_DATA_CFG);

    ctrl1 |= CTRL_REG1_SBYB;
    _i2c->MasterWriteRegister(&ctrl1, 1, MPL311_SLAVE_ADDR, CTRL_REG1);

}

double Pressure_MPL311::GetPressure()
{
    uint8_t data[3];
    uint8_t byte;

    while (1)
    {
        _i2c->MasterReadRegister(&byte, 1, MPL311_SLAVE_ADDR, CTRL_REG1);
        _i2c->MasterReadRegister(&byte, 1, MPL311_SLAVE_ADDR, DR_STATUS);
        if (byte & DR_STATUS_PDR)
        {
            break;
        }

    }

    _i2c->MasterReadRegister(data, 3, MPL311_SLAVE_ADDR, OUT_P_MSB);

    float res = (float) (((data[0] << 16) | (data[1] << 8) | (data[2] & 0xC0))
            >> 6) + (float) ((data[2] & 0x30) >> 4) * (double) 0.25;

    //float res = (float) ((short) ((data[0] << 8) | data[1])) + (float) (data[2] >> 4) * 0.0625;
    return res;

}

uint16_t Pressure_MPL311::GetTemperature()
{
    //Temperature = (float) ((short)((RawData[3] << 8) | (RawData[4] & 0xF0)) >> 4) * 0.0625;}
    return 0;
}

uint8_t Pressure_MPL311::GetDeviceID()
{
    if (!_initialized)
    {
        InitializeI2C();
        _initialized = true;
    }

    static uint8_t byte = 0;
    _i2c->MasterReadRegister(&byte, 1, MPL311_SLAVE_ADDR, WHO_AM_I);
    return byte;

}
