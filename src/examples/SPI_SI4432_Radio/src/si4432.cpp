#include "si4432.h"
#include "rcc.h"
#include <math.h>

#define MAX_TRANSMIT_TIMEOUT 200
#define round(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

//values here are kept in khz x 10 format (for not to deal with decimals) - look at AN440 page 26 for whole table
const uint16_t IFFilterTable[][2] =
{
{ 322, 0x26 },
{ 3355, 0x88 },
{ 3618, 0x89 },
{ 4202, 0x8A },
{ 4684, 0x8B },
{ 5188, 0x8C },
{ 5770, 0x8D },
{ 6207, 0x8E } };

Si4432::Si4432(SPI* spi, GPIO_PIN* ssPin, GPIO_PIN* sdnPin, GPIO_PIN* interruptPin = 0)
{ // default is 450 mhz
	_spi = spi;
	ssPin->SetupGPIO_OutPP();
	_spi->SetSSPin(ssPin);
	_sdnPin = sdnPin;
	_intPin = interruptPin;

	if (_intPin != 0)
		_intPin->SetupGPIO_InPullUp();

	_sdnPin->SetupGPIO_OutPP();

	_freqCarrier = 433000000;
	_freqChannel = 0;
	_kbps = 100;
	_packageSign = 0xBEEF;
}

void Si4432::setFrequency(unsigned long baseFrequencyMhz)
{

	if ((baseFrequencyMhz < 240) || (baseFrequencyMhz > 930))
		return; // invalid frequency

	_freqCarrier = baseFrequencyMhz;
	uint8_t highBand = 0;
	if (baseFrequencyMhz >= 480)
	{
		highBand = 1;
	}

	double fPart = (baseFrequencyMhz / (10 * (highBand + 1))) - 24;

	uint8_t freqband = (uint8_t) fPart; // truncate the int

	uint16_t freqcarrier = (fPart - freqband) * 64000;

	// sideband is always on (0x40) :
	uint8_t vals[3] =
	{
			(uint8_t)0x40 | (uint8_t)((uint8_t)highBand << 5) | (uint8_t)((uint8_t)freqband & 0x3F),
			((uint8_t)((uint8_t)freqcarrier >> 8)),
			(uint8_t)(freqcarrier & 0xFF)
	};

	BurstWrite(REG_FREQBAND, vals, 3);

}

void Si4432::setCommsSignature(uint16_t signature)
{
	_packageSign = signature;

	ChangeRegister(REG_TRANSMIT_HEADER3, _packageSign >> 8); // header (signature) uint8_t 3 val
	ChangeRegister(REG_TRANSMIT_HEADER2, (_packageSign & 0xFF)); // header (signature) uint8_t 2 val

	ChangeRegister(REG_CHECK_HEADER3, _packageSign >> 8); // header (signature) uint8_t 3 val for receive checks
	ChangeRegister(REG_CHECK_HEADER2, (_packageSign & 0xFF)); // header (signature) uint8_t 2 val for receive checks

#ifdef DEBUG
	Serial.println("Package signature is set!");
#endif
}

void Si4432::init()
{
	turnOff();
	_spi->SetSlaveSelectHigh();
	hardReset();

}

void Si4432::boot()
{
	/*
	 uint8_t currentFix[] = { 0x80, 0x40, 0x7F };
	 BurstWrite(REG_CHARGEPUMP_OVERRIDE, currentFix, 3); // refer to AN440 for reasons

	 ChangeRegister(REG_GPIO0_CONF, 0x0F); // tx/rx data clk pin
	 ChangeRegister(REG_GPIO1_CONF, 0x00); // POR inverted pin
	 ChangeRegister(REG_GPIO2_CONF, 0x1C); // clear channel pin
	 */
	ChangeRegister(REG_AFC_TIMING_CONTROL, 0x02); // refer to AN440 for reasons
	ChangeRegister(REG_AFC_LIMITER, 0xFF); // write max value - excel file did that.
	ChangeRegister(REG_AGC_OVERRIDE, 0x60); // max gain control
	ChangeRegister(REG_AFC_LOOP_GEARSHIFT_OVERRIDE, 0x3C); // turn off AFC
	ChangeRegister(REG_DATAACCESS_CONTROL, 0xAD); // enable rx packet handling, enable tx packet handling, enable CRC, use CRC-IBM
	ChangeRegister(REG_HEADER_CONTROL1, 0x0C); // no broadcast address control, enable check headers for uint8_ts 3 & 2
	ChangeRegister(REG_HEADER_CONTROL2, 0x22);  // enable headers uint8_t 3 & 2, no fixed package length, sync word 3 & 2
	ChangeRegister(REG_PREAMBLE_LENGTH, 0x08); // 8 * 4 bits = 32 bits (4 uint8_ts) preamble length
	ChangeRegister(REG_PREAMBLE_DETECTION, 0x3A); // validate 7 * 4 bits of preamble  in a package
	ChangeRegister(REG_SYNC_WORD3, 0x2D); // sync uint8_t 3 val
	ChangeRegister(REG_SYNC_WORD2, 0xD4); // sync uint8_t 2 val

	ChangeRegister(REG_TX_POWER, 0x1F); // max power

	ChangeRegister(REG_CHANNEL_STEPSIZE, 0x64); // each channel is of 1 Mhz interval

	setFrequency(_freqCarrier); // default freq
	setBaudRate(_kbps); // default baud rate is 100kpbs
	setChannel(_freqChannel); // default channel is 0
	setCommsSignature(_packageSign); // default signature

	switchMode(Ready);

}

bool Si4432::sendPacket(uint8_t length, const uint8_t* data, bool waitResponse, uint32_t ackTimeout, uint8_t* responseLength, uint8_t* responseBuffer)
{

	clearTxFIFO();
	ChangeRegister(REG_PKG_LEN, length);

	BurstWrite(REG_FIFO, data, length);

	ChangeRegister(REG_INT_ENABLE1, 0x04); // set interrupts on for package sent
	ChangeRegister(REG_INT_ENABLE2, 0x00); // set interrupts off for anything else
	//read interrupt registers to clean them
	ReadRegister(REG_INT_STATUS1);
	ReadRegister(REG_INT_STATUS2);

	switchMode(TXMode | Ready);

	for (int i = 0; i < MAX_TRANSMIT_TIMEOUT; ++i)
	{

		if ((_intPin == 0) || !_intPin->IsSet())
		{
			uint8_t intStatus = ReadRegister(REG_INT_STATUS1);
			ReadRegister(REG_INT_STATUS2);

			if (intStatus & 0x04)
			{
				switchMode(Ready | TuneMode);
				// package sent. now, return true if not to wait ack, or wait ack (wait for packet only for 'remaining' amount of time)
				if (waitResponse)
				{
					if (waitForPacket(ackTimeout))
					{
						getPacketReceived(responseLength, responseBuffer);
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return true;
				}
			}
		}

		RCC_Delay_ms(1);
	}

	switchMode(Ready);

	if (ReadRegister(REG_DEV_STATUS) & 0x80)
	{
		clearFIFO();
	}

	return false;

}

bool Si4432::waitForPacket(uint32_t waitMs)
{

	startListening();
	bool rc = false;

	for (uint32_t i = 0; i < waitMs; ++i)
	{

		if (isPacketReceived())
		{
			rc = true;
			break;
		}

		RCC_Delay_ms(1);

	}

	switchMode(Ready);
	clearRxFIFO();

	return rc;
}

void Si4432::getPacketReceived(uint8_t* length, uint8_t* readData)
{

	*length = ReadRegister(REG_RECEIVED_LENGTH);

	BurstRead(REG_FIFO, readData, *length);

	clearRxFIFO(); // which will also clear the interrupts
}

void Si4432::setChannel(uint8_t channel)
{

	ChangeRegister(REG_FREQCHANNEL, channel);

}

void Si4432::switchMode(uint8_t mode)
{
	ChangeRegister(REG_STATE, mode); // receive mode
	//delay(20);
}

void Si4432::ChangeRegister(uint8_t reg, uint8_t value)
{
	BurstWrite(reg, &value, 1);
}

void Si4432::setBaudRate(uint16_t kbps)
{

	// chip normally supports very low bps values, but they are cumbersome to implement - so I just didn't implement lower bps values
	if ((kbps > 256) || (kbps < 1))
		return;
	_kbps = kbps;

	uint8_t freqDev = kbps <= 10 ? 15 : 150;		// 15khz / 150 khz
	uint8_t modulationValue = _kbps < 30 ? 0x4c : 0x0c;		// use FIFO Mode, GFSK, low baud mode on / off

	uint8_t modulationVals[] =
	{ modulationValue, 0x23, (uint8_t)round((freqDev * 1000.0) / 625.0) }; // msb of the kpbs to 3rd bit of register
	BurstWrite(REG_MODULATION_MODE1, modulationVals, 3);

	// set data rate
	uint16_t bpsRegVal = round((kbps * (kbps < 30 ? 2097152 : 65536.0)) / 1000.0);
	uint8_t datarateVals[] =
	{ (uint8_t)(bpsRegVal >> 8), (uint8_t)(bpsRegVal & 0xFF) };

	BurstWrite(REG_TX_DATARATE1, datarateVals, 2);

	//now set the timings
	uint16_t minBandwidth = (2 * (uint32_t) freqDev) + kbps;
	uint8_t IFValue = 0xff;
	//since the table is ordered (from low to high), just find the 'minimum bandwith which is greater than required'
	for (uint8_t i = 0; i < 8; ++i)
	{
		if (IFFilterTable[i][0] >= (minBandwidth * 10))
		{
			IFValue = IFFilterTable[i][1];
			break;
		}
	}

	ChangeRegister(REG_IF_FILTER_BW, IFValue);

	uint8_t dwn3_bypass = (IFValue & 0x80) ? 1 : 0; // if msb is set
	uint8_t ndec_exp = (IFValue >> 4) & 0x07; // only 3 bits

	uint16_t rxOversampling = round((500.0 * (1 + 2 * dwn3_bypass)) / ((pow(2, ndec_exp - 3)) * (double) kbps));

	uint32_t ncOffset = ceil(((double) kbps * (pow(2, ndec_exp + 20))) / (500.0 * (1 + 2 * dwn3_bypass)));

	uint16_t crGain = 2 + ((65535 * (int64_t) kbps) / ((int64_t) rxOversampling * freqDev));
	uint8_t crMultiplier = 0x00;
	if (crGain > 0x7FF)
	{
		crGain = 0x7FF;
	}

	uint8_t timingVals[] =
	{
			(uint8_t)(rxOversampling & 0x00FF),
			(uint8_t)((rxOversampling & 0x0700) >> 3) | ((ncOffset >> 16) & 0x0F),
			(uint8_t)((ncOffset >> 8) & 0xFF),
			(uint8_t)(ncOffset & 0xFF),
			(uint8_t)((crGain & 0x0700) >> 8) | crMultiplier,
			(uint8_t)(crGain & 0xFF)
	};

	BurstWrite(REG_CLOCK_RECOVERY_OVERSAMPLING, timingVals, 6);

}

uint8_t Si4432::ReadRegister(uint8_t reg)
{
	uint8_t val = 0xFF;
	BurstRead(reg, &val, 1);
	return val;
}

void Si4432::BurstWrite(uint8_t startReg, const uint8_t value[], uint8_t length)
{

	uint8_t regVal = (uint8_t) startReg | 0x80; // set MSB

	_spi->SetSlaveSelectLow();
	_spi->TransmitByte(regVal);

	for (uint8_t i = 0; i < length; ++i)
	{
		_spi->TransmitByte(value[i]);
	}

	_spi->SetSlaveSelectHigh();
}

void Si4432::BurstRead(uint8_t startReg, uint8_t value[], uint8_t length)
{

	uint8_t regVal = (uint8_t) startReg & 0x7F; // set MSB

	_spi->SetSlaveSelectLow();
	_spi->TransmitByte(regVal);

	for (uint8_t i = 0; i < length; ++i)
	{
		value[i] = _spi->TransmitByte(0xFF);
	}

	_spi->SetSlaveSelectHigh();
}

void Si4432::clearTxFIFO()
{
	ChangeRegister(REG_OPERATION_CONTROL, 0x01);
	ChangeRegister(REG_OPERATION_CONTROL, 0x00);

}

void Si4432::clearRxFIFO()
{
	ChangeRegister(REG_OPERATION_CONTROL, 0x02);
	ChangeRegister(REG_OPERATION_CONTROL, 0x00);
}

void Si4432::clearFIFO()
{
	ChangeRegister(REG_OPERATION_CONTROL, 0x03);
	ChangeRegister(REG_OPERATION_CONTROL, 0x00);
}

void Si4432::softReset()
{
	ChangeRegister(REG_STATE, 0x80);

	uint8_t reg = ReadRegister(REG_INT_STATUS2);
	while ((reg & 0x02) != 0x02)
	{
		RCC_Delay_ms(1);
		reg = ReadRegister(REG_INT_STATUS2);
	}

	boot();

}

void Si4432::hardReset()
{

	turnOff();
	turnOn();

	uint8_t reg = ReadRegister(REG_INT_STATUS2);
	while ((reg & 0x02) != 0x02)
	{
		RCC_Delay_ms(1);
		reg = ReadRegister(REG_INT_STATUS2);
	}

	boot();
}

void Si4432::startListening()
{

	clearRxFIFO(); // clear first, so it doesn't overflow if packet is big

	ChangeRegister(REG_INT_ENABLE1, 0x03); // set interrupts on for package received and CRC error

#ifdef DEBUG
	ChangeRegister(REG_INT_ENABLE2, 0xC0);
#else
	ChangeRegister(REG_INT_ENABLE2, 0x00); // set other interrupts off
#endif
	//read interrupt registers to clean them
	ReadRegister(REG_INT_STATUS1);
	ReadRegister(REG_INT_STATUS2);

	switchMode(RXMode | Ready);
}

bool Si4432::isPacketReceived()
{

	if (_intPin != 0 && _intPin->IsSet())
	{
		return false; // if no interrupt occured, no packet received is assumed (since startListening will be called prior, this assumption is enough)
	}
	// check for package received status interrupt register
	uint8_t intStat = ReadRegister(REG_INT_STATUS1);

#ifdef DEBUG
	uint8_t intStat2 = ReadRegister(REG_INT_STATUS2);

	if (intStat2 & 0x40)
	{ //interrupt occured, check it && read the Interrupt Status1 register for 'preamble '

		Serial.print("HEY!! HEY!! Valid Preamble detected -- ");
		Serial.println(intStat2, HEX);

	}

	if (intStat2 & 0x80)
	{ //interrupt occured, check it && read the Interrupt Status1 register for 'preamble '

		Serial.print("HEY!! HEY!! SYNC WORD detected -- ");
		Serial.println(intStat2, HEX);

	}
#else
	ReadRegister(REG_INT_STATUS2);
#endif

	if (intStat & 0x02)
	{ //interrupt occured, check it && read the Interrupt Status1 register for 'valid packet'
		switchMode(Ready | TuneMode); // if packet came, get out of Rx mode till the packet is read out. Keep PLL on for fast reaction
		return true;
	}
	else if (intStat & 0x01)
	{ // packet crc error
		switchMode(Ready); // get out of Rx mode till buffers are cleared
		clearRxFIFO();
		switchMode(RXMode | Ready); // get back to work
		return false;
	}

	//no relevant interrupt? no packet!

	return false;
}

void Si4432::turnOn()
{
	// turn on the chip now
	_sdnPin->Reset();
	RCC_Delay_ms(20);
}

void Si4432::turnOff()
{
	// turn off the chip now
	_sdnPin->Set();
	RCC_Delay_ms(1);

}

void Si4432::readAll() {

	uint8_t allValues[0x7F];

    BurstRead(REG_DEV_TYPE, allValues, 0x7F);

    static volatile uint8_t tmp;

    for (uint8_t i = 0; i < 0x7f; ++i)
    {
        tmp =  allValues[i];
        UNUSED(tmp);
    }

}

