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



#ifndef HD44780_H
#define HD44780_H

#include "gpio_cpp.h"

#define LCD_4BIT    0x28    // LCD mode as 4-bit 2-line 5*8-dot 1/16Duty

#define LCDPort P0
#define LCDControlPort P0

#define LCD_EN          4
#define LCD_RW          5
#define LCD_RS          6

/* Exported constants ------------------------------------------------*/

#define LCD_CLS     0x01        // Clear LCD screen
#define LCD_HOME    0x02        // LCD Return home
#define LCD_ENTRY   0x06        // Set LCD Entry Mode
#define LCD_C2L     0x10        // Move Cursor to the left
#define LCD_C2R     0x14        // Move Cursor to the right
#define LCD_D2L     0x18        // Move display to the left
#define LCD_D2R     0x1C        // Move display to the right

#define LCD_ON      0x0F //0x0C        // Turn on LCD and Cursor
#define LCD_OFF     0x08        // Turn off LCD

#define LCD_L1      0x80
#define LCD_L2      0xC0

//#define SET_RS      sbi(LCDControlPort, LCD_RS)
//#define SET_RW      sbi(LCDControlPort, LCD_RW)
//#define SET_EN      sbi(LCDControlPort, LCD_EN)
//#define CLR_RS      cbi(LCDControlPort, LCD_RS)
//#define CLR_RW      cbi(LCDControlPort, LCD_RW)
//#define CLR_EN      cbi(LCDControlPort, LCD_EN)

class LCD
{
private:
    GPIO_PORT* _dataPort;
    GPIO_PORT* _controlPort;
    GPIO_PIN_N _pinData[4];
    GPIO_PIN_N _pinRW; //read-write
    GPIO_PIN_N _pinEN;  //enable
    GPIO_PIN_N _pinRS;  //register select: High=Data, Low=Control

    void GPIO_Init();
    void SetRS();
    void ClearRS();
    void SetEN();
    void ClearEN();
    void Write(uint8_t data);
    void WriteNibble(uint8_t nibble);

public:
    LCD(GPIO_PORT* dataPort, GPIO_PORT* controlPort, GPIO_PIN_N pinD4, GPIO_PIN_N pinD5,
            GPIO_PIN_N pinD6, GPIO_PIN_N pinD7, GPIO_PIN_N pinEN, GPIO_PIN_N pinRS,
            GPIO_PIN_N pinRW)
    {
        _dataPort = dataPort;
        _controlPort = controlPort;
        _pinData[0] = pinD4;
        _pinData[1] = pinD5;
        _pinData[2] = pinD6;
        _pinData[3] = pinD7;
        _pinEN = pinEN;
        _pinRS = pinRS;
        _pinRW = pinRW;
    }

    void LCD_INIT();
    void LCD_PrintChar(uint8_t ascode);
    void LCD_PrintString(uint8_t *text);
    void LCD_CMD(uint8_t cmd_data);
    void LCD_Clear();
    void LCD_2ndRow();
    void LCD_Home();
    void LCD_LShift();
    void LCD_RShift();
    void LCD_CursorOn();
    void LCD_CursorOff();
    void LCD_Locate(uint8_t row, uint8_t column);

};

#endif

