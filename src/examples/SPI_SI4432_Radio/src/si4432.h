/*
 * SI4432 library for Arduino - v0.1
 *
 * Please note that Library uses standart SS pin for NSEL pin on the chip. This is 53 for Mega, 10 for Uno.
 * NOTES:
 *
 * V0.1
 * * Library supports no `custom' changes and usages of GPIO pin. Modify/add/remove your changes if necessary
 * * Radio use variable packet field format with 4 uint8_t address header, first data field as length. Change if necessary
 *
 * made by Ahmet (theGanymedes) Ipkin
 *
 * 2014
 */

#ifndef si4432_H_
#define si4432_H_

/* Now, according to the this design, you must
 * 1- Create an instance
 * 2- Call init()
 *
 * According to the data sheet, you can change any register value and most will get to work after going into IDLE state and back (to RX/TX)
 * (some are hot - changes right away) I didn't test this - but why not? :)
 * */

#include "spi_cpp.h"
#include "GPIO_Helper.h"

#define REG_DEV_TYPE  0x00
#define REG_DEV_VERSION  0x01
#define REG_DEV_STATUS  0x02

#define REG_INT_STATUS1  0x03
#define REG_INT_STATUS2  0x04
#define REG_INT_ENABLE1  0x05
#define REG_INT_ENABLE2  0x06
#define REG_STATE  0x07
#define REG_OPERATION_CONTROL  0x08

#define REG_GPIO0_CONF  0x0B
#define REG_GPIO1_CONF  0x0C
#define REG_GPIO2_CONF  0x0D
#define REG_IOPORT_CONF  0x0E

#define REG_IF_FILTER_BW  0x1C
#define REG_AFC_LOOP_GEARSHIFT_OVERRIDE  0x1D
#define REG_AFC_TIMING_CONTROL  0x1E
#define REG_CLOCK_RECOVERY_GEARSHIFT  0x1F
#define REG_CLOCK_RECOVERY_OVERSAMPLING  0x20
#define REG_CLOCK_RECOVERY_OFFSET2  0x21
#define REG_CLOCK_RECOVERY_OFFSET1  0x22
#define REG_CLOCK_RECOVERY_OFFSET0  0x23
#define REG_CLOCK_RECOVERY_TIMING_GAIN1  0x24
#define REG_CLOCK_RECOVERY_TIMING_GAIN0  0x25
#define REG_RSSI  0x26
#define REG_RSSI_THRESHOLD  0x27

#define REG_AFC_LIMITER  0x2A
#define REG_AFC_CORRECTION_READ  0x2B

#define REG_DATAACCESS_CONTROL  0x30
#define REG_EZMAC_STATUS  0x31
#define REG_HEADER_CONTROL1  0x32
#define REG_HEADER_CONTROL2  0x33
#define REG_PREAMBLE_LENGTH  0x34
#define REG_PREAMBLE_DETECTION  0x35
#define REG_SYNC_WORD3  0x36
#define REG_SYNC_WORD2  0x37
#define REG_SYNC_WORD1  0x38
#define REG_SYNC_WORD0  0x39
#define REG_TRANSMIT_HEADER3  0x3A
#define REG_TRANSMIT_HEADER2  0x3B
#define REG_TRANSMIT_HEADER1  0x3C
#define REG_TRANSMIT_HEADER0  0x3D

#define REG_PKG_LEN  0x3E

#define REG_CHECK_HEADER3  0x3F
#define REG_CHECK_HEADER2  0x40
#define REG_CHECK_HEADER1  0x41
#define REG_CHECK_HEADER0  0x42

#define REG_RECEIVED_HEADER3  0x47
#define REG_RECEIVED_HEADER2  0x48
#define REG_RECEIVED_HEADER1  0x49
#define REG_RECEIVED_HEADER0  0x4A

#define REG_RECEIVED_LENGTH  0x4B

#define REG_CHARGEPUMP_OVERRIDE  0x58
#define REG_DIVIDER_CURRENT_TRIM  0x59
#define REG_VCO_CURRENT_TRIM  0x5A

#define REG_AGC_OVERRIDE  0x69

#define REG_TX_POWER  0x6D
#define REG_TX_DATARATE1  0x6E
#define REG_TX_DATARATE0  0x6F

#define REG_MODULATION_MODE1  0x70
#define REG_MODULATION_MODE2  0x71

#define REG_FREQ_DEVIATION  0x72
#define REG_FREQ_OFFSET1  0x73
#define REG_FREQ_OFFSET2  0x74
#define REG_FREQBAND  0x75
#define REG_FREQCARRIER_H  0x76
#define REG_FREQCARRIER_L  0x77

#define REG_FREQCHANNEL  0x79
#define REG_CHANNEL_STEPSIZE  0x7A

#define REG_FIFO  0x7F

class Si4432
{
private:
	enum AntennaMode
	{
		RXMode = 0x04, TXMode = 0x08, Ready = 0x01, TuneMode = 0x02
	};

	SPI* _spi;
	GPIO_PIN *_sdnPin, *_intPin;

	uint64_t _freqCarrier;
	uint8_t _freqChannel;
	uint16_t _kbps;
	uint16_t _packageSign;

	void boot(); // sets SPI and pins ready and boot the radio

	void switchMode(uint8_t mode);

	void ChangeRegister(uint8_t reg, uint8_t value);
	uint8_t ReadRegister(uint8_t reg);

	void BurstWrite(uint8_t startReg, const uint8_t value[], uint8_t length);
	void BurstRead(uint8_t startReg, uint8_t value[], uint8_t length);

public:

	Si4432(SPI* spi, GPIO_PIN* ssPin, GPIO_PIN* sdnPin, GPIO_PIN* InterruptPin); // when a InterruptPin is given, interrupts are checked with this pin - rather than SPI polling

	void setFrequency(unsigned long baseFrequency);// sets the freq. call before boot
	void setChannel(uint8_t channel);// sets the channel. call before switching to tx or rx mode
	void setBaudRate(uint16_t kbps);// sets the  bps. call before switching to tx or rx mode - min:1, max: 256
	void init();
	void setCommsSignature(uint16_t signature);// used to 'sign' packets with a predetermined signature - call before boot

	bool sendPacket(uint8_t length, const uint8_t* data, bool waitResponse = false, uint32_t ackTimeout = 100,
			uint8_t *responseLength = 0, uint8_t* responseBuffer = 0);// switches to Tx mode and sends the package, then optionally receives response package

	void startListening();// switch to Rx mode (don't block)

	bool isPacketReceived();// check for the packet received flags

	bool waitForPacket(uint32_t waitMs);// switch to Rx mode and wait until timeout or 'valid' package to arrive
	void getPacketReceived(uint8_t* length, uint8_t* readData);// read from FIFO

	void readAll();

	void clearTxFIFO();
	void clearRxFIFO();

	void clearFIFO();

	void softReset();

	void hardReset();

	void turnOn();
	void turnOff();



};

#endif /* si4432_H_ */
