#ifndef _IRREMOTE_H
#define _IRREMOTE_H

#define FALSE 0
#define HIGH 1
#define LOW 0

// Values for decode_type
enum DECODE_TYPE
{
	NEC = 1,
	SONY = 2,
	RC5 = 3,
	RC6 = 4,
	DISH = 5,
	SHARP = 6,
	PANASONIC = 7,
	JVC = 8,
	SANYO = 9,
	MITSUBISHI = 10,
	SAMSUNG = 11,
	LG = 12,
	UNKNOWN = -1
};

// IR detector output is active low
#define MARK  0
#define SPACE 1

#define USECPERTICK 50  // microseconds per clock interrupt tick
#define RAWBUF 100 // Length of raw duration buffer
// Marks tend to be 100us too long, and spaces 100us too short
// when received due to sensor lag.
#define MARK_EXCESS 100

#define TOLERANCE 25  // percent tolerance in measurements
#define LTOL (1.0 - TOLERANCE/100.) 
#define UTOL (1.0 + TOLERANCE/100.) 

#define _GAP 5000 // Minimum gap between transmissions
#define GAP_TICKS (_GAP/USECPERTICK)

#define TICKS_LOW(us) (int) (((us)*LTOL/USECPERTICK))
#define TICKS_HIGH(us) (int) (((us)*UTOL/USECPERTICK + 1))

inline int MATCH(int measured, int desired)
{
	return measured >= TICKS_LOW(desired) && measured <= TICKS_HIGH(desired);
}
inline int MATCH_MARK(int measured_ticks, int desired_us)
{
	return MATCH(measured_ticks, (desired_us + MARK_EXCESS));
}
inline int MATCH_SPACE(int measured_ticks, int desired_us)
{
	return MATCH(measured_ticks, (desired_us - MARK_EXCESS));
}

// Pulse parms are *50-100 for the Mark and *50+100 for the space
// First MARK is the one after the long gap
// pulse parameters in usec
#define NEC_HDR_MARK    9000
#define NEC_HDR_SPACE   4500
#define NEC_BIT_MARK    560
#define NEC_ONE_SPACE   1600
#define NEC_ZERO_SPACE  560
#define NEC_RPT_SPACE   2250
#define NEC_BITS 32

#define SAMSUNG_HDR_MARK  5000
#define SAMSUNG_HDR_SPACE 5000
#define SAMSUNG_BIT_MARK  560
#define SAMSUNG_ONE_SPACE 1600
#define SAMSUNG_ZERO_SPACE  560
#define SAMSUNG_RPT_SPACE 2250
#define SAMSUNG_BITS 32

#define REPEAT 0xffffffff

#define RC5_T1      889
#define RC5_RPT_LENGTH  46000
#define MIN_RC5_SAMPLES 11
#define MIN_RC6_SAMPLES 1

#define SONY_HDR_MARK   2400
#define SONY_HDR_SPACE  600
#define SONY_ONE_MARK   1200
#define SONY_ZERO_MARK  600
#define SONY_RPT_LENGTH 45000
#define SONY_DOUBLE_SPACE_USECS  500  // usually ssee 713 - not using ticks as get number wrapround
#define SONY_BITS 12

// receiver states
#define STATE_IDLE     2
#define STATE_MARK     3
#define STATE_SPACE    4
#define STATE_STOP     5

#include "gpio_cpp.h"
#include "timer_cpp.h"

class IRRemoteCallback
{
public:
	virtual void RemoteButtonPressed (uint32_t codeValue) = 0;
};

class IRRemote : public TIMER_Interrupt_Handler
{
private:
	GPIO_PIN* _recvPin;
	uint8_t _rcvstate; // state machine
	unsigned int _timerCount;// state timer, counts 50uS ticks.
	unsigned int _rawbuf[RAWBUF];// raw data
	uint8_t _rawlen;// counter of entries in rawbuf

	DECODE_TYPE _decode_type;// NEC, SONY, RC5, UNKNOWN
	unsigned long _value;// Decoded value
	int _bits;// Number of bits in decoded value
	IRRemoteCallback* _callBack;

public:
	IRRemote(GPIO_PIN* pin);

	bool decode();

	void resume();

	uint32_t getValue();
	DECODE_TYPE getType();

	void setCallback (IRRemoteCallback* callback) {	_callBack = callback;}

private:

// Gets one undecoded level at a time from the raw buffer.
// The RC5/6 decoding is easier if the data is broken into time intervals.
// E.g. if the buffer has MARK for 2 time intervals and SPACE for 1,
// successive calls to getRClevel will return MARK, MARK, SPACE.
// offset and used are updated to keep track of the current position.
// t1 is the time interval for a single bit in microseconds.
// Returns -1 for error (measured time interval is not a multiple of t1).
	int getRClevel(int *offset, int *used, int t1, int rawlen);

	// NECs have a repeat only 4 items long
	bool decodeNEC(int rawlen);

	// SAMSUNGs have a repeat only 4 items long
	bool decodeSAMSUNG(int rawlen);
	bool decodeRC5(int rawlen);
	bool decodeSony(int rawlen);

#define FNV_PRIME_32 16777619UL
#define FNV_BASIS_32 2166136261UL

// Compare two tick values, returning 0 if newval is shorter,
// 1 if newval is equal, and 2 if newval is longer
// Use a tolerance of 20%
	static int compare(unsigned int oldval, unsigned int newval);

	bool decodeHash(int rawlen);

	uint8_t read_pin();

	virtual void HandleInterrupt(bool isUpdate, bool isTrigger);

};

#endif
