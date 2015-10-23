#include "ssd1306.h"
#include "rcc.h"

//TODO try fonts : guyc/py-gaugette

SSD1306::SSD1306(SPI* spi, GPIO_PIN* resetPin, GPIO_PIN* dcPin)
{
	_spi = spi;
	_resetPin = resetPin;
	_dcPin = dcPin;
	Init();
}

void SSD1306::Reset()
{
	_resetPin->Reset();
	RCC_Delay_ms(10);
	_resetPin->Set();
	RCC_Delay_ms(10);

}

void SSD1306::Init()
{
	Reset();
	SendCommand(SSD1306_DISPLAYOFF); // 0xAE
	SendCommand(SSD1306_SETDISPLAYCLOCKDIV); // 0xD5
	SendCommand(0x80); // the suggested ratio 0x80

	//SendCommand(SSD1306_SETMULTIPLEX); // 0xA8
	//SendCommand(0x3F);

	SendCommand(SSD1306_SETDISPLAYOFFSET); // 0xD3
	SendCommand(0x0); // no offset
	SendCommand(SSD1306_SETSTARTLINE | 0x0); // line #0
	SendCommand(SSD1306_CHARGEPUMP); // 0x8D
	SendCommand(0x14);

	SendCommand(SSD1306_MEMORYMODE); // 0x20
	//SendCommand(0x00); 
	SendCommand(0x02);
	SendCommand(SSD1306_SEGREMAP | 0x1);
	SendCommand(SSD1306_COMSCANDEC);
	SendCommand(SSD1306_SETCOMPINS); // 0xDA
	SendCommand(0x12);
	SendCommand(SSD1306_SETCONTRAST); // 0x81
	SendCommand(0xCF);

	SendCommand(SSD1306_SETPRECHARGE); // 0xd9
	//SendCommand(0x22);  external
	SendCommand(0xF1);

	SendCommand(SSD1306_SETVCOMDETECT); // 0xDB
	SendCommand(0x40);
	SendCommand(SSD1306_DISPLAYALLON_RESUME); // 0xA4
	SendCommand(SSD1306_NORMALDISPLAY); // 0xA6

	ClearScreen();

	SendCommand(SSD1306_DISPLAYON);

}

void SSD1306::ClearScreen()
{
	for (uint8_t y = 0; y < 8; ++y)
	{
		SendCommand(0xb0 + y);
		SendCommand(0x00);
		SendCommand(0x10);

		for (uint8_t x = 0; x < 128; ++x)
		{
			SendData(0);
		}
	}
}

void SSD1306::GoTo(uint8_t x, uint8_t y)
{
	SendCommand(0xb0 + y);
	SendCommand(((x & 0xf0) >> 4) | 0x10);
	SendCommand((x & 0x0f) | 0x00);
}

void SSD1306::WriteLine(uint8_t x, uint8_t y, char* str)
{
	for (uint8_t j = 0; str[j] != '\0'; ++j)
	{
		if (x > 126)
		{
			x = 0;
			y++;
		}

		GoTo(x, y);

		for (uint8_t i = 0; i < 6; ++i)
		{
			SendData(F6x8[str[j] - 32][i]);
		}

		x += 6;
	}
}

void SSD1306::SendCommand(uint8_t cmd)
{
	_dcPin->Reset();
	_spi->Transmit(cmd);
}

void SSD1306::SendData(uint8_t cmd)
{
	_dcPin->Set();
	_spi->Transmit(cmd);
}

void SSD1306::DrawPixel(uint8_t x, uint8_t y)
{
	if ((x >= SSD1306_LCDWIDTH) || (y >= SSD1306_LCDHEIGHT))
		return;

	_buffer[x + (y / 8) * SSD1306_LCDWIDTH] |= (1 << y % 8);
}
