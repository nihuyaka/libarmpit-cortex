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



#include "hd44780.h"

void LCD::SetRS()
{
    _controlPort->SetPin(_pinRS);
}

void LCD::ClearRS()
{
    _controlPort->ResetPin(_pinRS);

}
void LCD::SetEN()
{
    _controlPort->SetPin(_pinEN);

}
void LCD::ClearEN()
{
    _controlPort->ResetPin(_pinEN);

}

void LCD::WriteNibble(uint8_t nibble)
{
    SetEN();
    for (int i = 0; i < 4; ++i)
    {
        if (nibble & (1 << i))
        {
            _dataPort->SetPin(_pinData[i]);
        }
        else
        {
            _dataPort->ResetPin(_pinData[i]);
        }
    }

    RCC::GetInstance()->Delay_ms(4);
    asm ("nop");
    ClearEN();
    asm ("nop");
    RCC::GetInstance()->Delay_ms(4);
}

void LCD::Write(uint8_t data)
{
    WriteNibble((data >> 4) & 0xf);
    WriteNibble(data & 0xf);
}

void LCD::LCD_CMD(uint8_t cmd_data)
{
    ClearRS();
    Write(cmd_data);
}

void LCD::LCD_PrintChar(uint8_t ascode)
{
    SetRS();
    Write(ascode);
}

void LCD::LCD_PrintString(uint8_t *text)
{
    do
    {
        LCD_PrintChar(*text++);
    } while (*text != '\n');
    //while(*text) {LCD_printchar(*text++);}
}

void LCD::LCD_2ndRow(void)
{
    LCD_CMD(LCD_L2);
}

void LCD::LCD_Home(void)
{
    LCD_CMD(LCD_HOME);
    RCC::GetInstance()->Delay_ms(2);
}

void LCD::LCD_LShift(void)
{
    LCD_CMD(0x18);
}

void LCD::LCD_RShift(void)
{
    LCD_CMD(0x1C);
}

void LCD::LCD_CursorOn(void)
{
    LCD_CMD(0x0C);
}

void LCD::LCD_CursorOff(void)
{
    LCD_CMD(0x08);
}

void LCD::LCD_Locate(uint8_t row, uint8_t column)
{
    column--;
    if (row == 1)
    { /* Set cursor to 1st row address and add index*/
        LCD_CMD(column |= LCD_L1);
    }
    else if (row == 2)
    { /* Set cursor to 2nd row address and add index*/
        LCD_CMD(column |= LCD_L2);
    }

}

void LCD::LCD_Clear(void)
{
    LCD_CMD(LCD_CLS);
    RCC::GetInstance()->RCC::GetInstance()->Delay_ms(2);
}

void LCD::LCD_INIT(void)
{
    GPIO_Init();

    SetEN();
    ClearRS();
    //Initialization of HD44780-based LCD (4-bit HW)
    LCD_CMD(0x33);
    LCD_CMD(0x32);
    //Function Set 4-bit mode
    //LCD_CMD(0x28);
    LCD_CMD(0x28);
    //Cursor On/Off Control
    //LCD_CMD(0x0C);
    //Entry mode set
    LCD_CMD(0x06);
    LCD_Clear();
    LCD_CMD(0x20);
    //Minimum delay to wait before driving LCD module
    RCC::GetInstance()->Delay_ms(200);
}

void LCD::GPIO_Init()
{
    _dataPort->EnablePeripheralClock(true);
    _controlPort->EnablePeripheralClock(true);
    for (int i = 0; i < 4; ++i)
    {
        _dataPort->SetupGPIO_OutPP(_pinData[i]);
    }

    _controlPort->SetupGPIO_OutPP(_pinEN);
    _controlPort->SetupGPIO_OutPP(_pinRS);

    //_controlPort->SetupGPIO_OutPP (_pinRW);
    //_controlPort->SetPin (_pinRW);

}

