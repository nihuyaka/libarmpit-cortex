/*
 * IRremote
 * Version 0.11 August, 2009
 * Copyright 2009 Ken Shirriff
 * For details, see http://arcfn.com/2009/08/multi-protocol-infrared-remote-library.html
 *
 * Modified by Paul Stoffregen <paul@pjrc.com> to support other boards and timers
 * Modified  by Mitra Ardron <mitra@mitra.biz> 
 * Added Sanyo and Mitsubishi controllers
 * Modified Sony to spot the repeat codes that some Sony's send
 *
 * Interrupt code based on NECIRrcv by Joe Knapp
 * http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1210243556
 * Also influenced by http://zovirl.com/2008/11/12/building-a-universal-remote-with-an-arduino/
 *
 * JVC and Panasonic protocol added by Kristian Lauszus (Thanks to zenwheel and other people at the original blog post)
 * LG added by Darryl Smith (based on the JVC protocol)
 */

#include "IRRemote.h"

IRRemote::IRRemote(GPIO_PIN* pin)
{
    _recvPin = pin;
    resume();
}

bool IRRemote::decode()
{
    bool rc = false;

    if (_rcvstate != STATE_STOP)
    {
        resume();
        rc = false;
    }

    else if (decodeNEC (_rawlen) || 
             decodeSony (_rawlen) ||
             decodeRC5 (_rawlen) ||
             decodeSAMSUNG (_rawlen) ||
             decodeHash (_rawlen))
             
    {
        rc = true;
    }


    return rc;
}

void IRRemote::resume()
{
    _rcvstate = STATE_IDLE;
    _rawlen = 0;
    _decode_type = UNKNOWN;
    _value = 0;
    _bits = 0;
}

uint32_t IRRemote::getValue()
{
    return _value;
}
DECODE_TYPE IRRemote::getType()
{
    return _decode_type;
}

int IRRemote::getRClevel(int *offset, int *used, int t1, int rawlen)
{
    if (*offset >= rawlen)
    {
        // After end of recorded buffer, assume SPACE.
        return SPACE;
    }
    int width = _rawbuf[*offset];
    int val = ((*offset) % 2) ? MARK : SPACE;
    int correction = (val == MARK) ? MARK_EXCESS : -MARK_EXCESS;

    int avail;
    if (MATCH(width, t1 + correction))
    {
        avail = 1;
    }
    else if (MATCH(width, 2 * t1 + correction))
    {
        avail = 2;
    }
    else if (MATCH(width, 3 * t1 + correction))
    {
        avail = 3;
    }
    else
    {
        return -1;
    }

    (*used)++;
    if (*used >= avail)
    {
        *used = 0;
        (*offset)++;
    }

    return val;
}

bool IRRemote::decodeNEC(int rawlen)
{
    long data = 0;
    int offset = 1; // Skip first space
    // Initial mark
    if (!MATCH_MARK(_rawbuf[offset], NEC_HDR_MARK))
    {
        return false;
    }
    offset++;
    // Check for repeat
    if (rawlen == 4 && MATCH_SPACE(_rawbuf[offset], NEC_RPT_SPACE)
            && MATCH_MARK(_rawbuf[offset + 1], NEC_BIT_MARK))
    {
        _bits = 0;
        _value = REPEAT;
        _decode_type = NEC;
        return true;
    }
    else if (rawlen < 2 * NEC_BITS + 4)
    {
        return false;
    }
    // Initial space
    if (!MATCH_SPACE(_rawbuf[offset], NEC_HDR_SPACE))
    {
        return false;
    }
    offset++;
    for (int i = 0; i < NEC_BITS; i++)
    {
        if (!MATCH_MARK(_rawbuf[offset], NEC_BIT_MARK))
        {
            return false;
        }
        offset++;
        if (MATCH_SPACE(_rawbuf[offset], NEC_ONE_SPACE))
        {
            data = (data << 1) | 1;
        }
        else if (MATCH_SPACE(_rawbuf[offset], NEC_ZERO_SPACE))
        {
            data <<= 1;
        }
        else
        {
            return false;
        }
        offset++;
    }
    // Success
    _bits = NEC_BITS;
    _value = data;
    _decode_type = NEC;
    return true;
}

bool IRRemote::decodeSAMSUNG(int rawlen)

{
    long data = 0;
    int offset = 1; // Skip first space
    // Initial mark
    if (!MATCH_MARK(_rawbuf[offset], SAMSUNG_HDR_MARK))
    {
        return false;
    }
    offset++;
    // Check for repeat
    if (rawlen == 4 && MATCH_SPACE(_rawbuf[offset], SAMSUNG_RPT_SPACE)
            && MATCH_MARK(_rawbuf[offset + 1], SAMSUNG_BIT_MARK))
    {
        _bits = 0;
        _value = REPEAT;
        _decode_type = SAMSUNG;
        //TODO  see what happens if return false on repeat
        //return true;
        return false;
    }
    else if (rawlen < 2 * SAMSUNG_BITS + 4)
    {
        return false;
    }
    // Initial space
    if (!MATCH_SPACE(_rawbuf[offset], SAMSUNG_HDR_SPACE))
    {
        return false;
    }
    offset++;
    for (int i = 0; i < SAMSUNG_BITS; i++)
    {
        if (!MATCH_MARK(_rawbuf[offset], SAMSUNG_BIT_MARK))
        {
            return false;
        }
        offset++;
        if (MATCH_SPACE(_rawbuf[offset], SAMSUNG_ONE_SPACE))
        {
            data = (data << 1) | 1;
        }
        else if (MATCH_SPACE(_rawbuf[offset], SAMSUNG_ZERO_SPACE))
        {
            data <<= 1;
        }
        else
        {
            return false;
        }
        offset++;
    }
    // Success
    _bits = SAMSUNG_BITS;
    _value = data;
    _decode_type = SAMSUNG;
    return true;
}

bool IRRemote::decodeRC5(int rawlen)
{
    if (rawlen < MIN_RC5_SAMPLES + 2)
    {
        return false;
    }
    int offset = 1; // Skip gap space
    long data = 0;
    int used = 0;
    // Get start bits
    if (getRClevel(&offset, &used, RC5_T1, rawlen) != MARK)
        return false;
    else if (getRClevel(&offset, &used, RC5_T1, rawlen) != SPACE)
        return false;
    else if (getRClevel(&offset, &used, RC5_T1, rawlen) != MARK)
        return false;

    int nbits;
    for (nbits = 0; offset < rawlen; nbits++)
    {
        int levelA = getRClevel(&offset, &used, RC5_T1, rawlen);
        int levelB = getRClevel(&offset, &used, RC5_T1, rawlen);
        if (levelA == SPACE && levelB == MARK)
        {
            // 1 bit
            data = (data << 1) | 1;
        }
        else if (levelA == MARK && levelB == SPACE)
        {
            // zero bit
            data <<= 1;
        }
        else
        {
            return false;
        }
    }

    // Success
    _bits = nbits;
    _value = data;
    _decode_type = RC5;
    return true;
}

bool IRRemote::decodeSony(int rawlen)
{
    long data = 0;
    if (rawlen < 2 * SONY_BITS + 2)
    {
        return false;
    }
    int offset = 0; // Dont skip first space, check its size

    // Some Sony's deliver repeats fast after first
    // unfortunately can't spot difference from of repeat from two fast clicks
    if (_rawbuf[offset] < SONY_DOUBLE_SPACE_USECS)
    {
        // Serial.print("IR Gap found: ");
        _bits = 0;
        _value = REPEAT;
        _decode_type = SANYO;
        return true;
    }
    offset++;

    // Initial mark
    if (!MATCH_MARK(_rawbuf[offset], SONY_HDR_MARK))
    {
        return false;
    }
    offset++;

    while (offset + 1 < rawlen)
    {
        if (!MATCH_SPACE(_rawbuf[offset], SONY_HDR_SPACE))
        {
            break;
        }
        offset++;
        if (MATCH_MARK(_rawbuf[offset], SONY_ONE_MARK))
        {
            data = (data << 1) | 1;
        }
        else if (MATCH_MARK(_rawbuf[offset], SONY_ZERO_MARK))
        {
            data <<= 1;
        }
        else
        {
            return false;
        }
        offset++;
    }

    // Success
    _bits = (offset - 1) / 2;
    if (_bits < 12)
    {
        _bits = 0;
        return false;
    }
    _value = data;
    _decode_type = SONY;
    return true;
}

#define FNV_PRIME_32 16777619UL
#define FNV_BASIS_32 2166136261UL

int IRRemote::compare(unsigned int oldval, unsigned int newval)
{
    if (newval < oldval * .8)
    {
        return 0;
    }
    else if (oldval < newval * .8)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

bool IRRemote::decodeHash(int rawlen)
{
    // Require at least 6 samples to prevent triggering on noise
    if (rawlen < 6)
    {
        return false;
    }
    unsigned long hash = FNV_BASIS_32;
    for (int i = 1; i + 2 < rawlen; i++)
    {
        int value = compare(_rawbuf[i], _rawbuf[i + 2]);
        // Add value into the hash
        hash = (hash * FNV_PRIME_32) ^ value;
    }
    _value = hash;
    _bits = 32;
    _decode_type = UNKNOWN;
    return true;
}

uint8_t IRRemote::read_pin()
{
    return _recvPin->IsSet();
}

void IRRemote::HandleInterrupt(bool isUpdate, bool isTrigger)
{
	UNUSED(isTrigger);
	if (!isUpdate)
		return;

    uint8_t irdata = (uint8_t) read_pin();

    if (irdata == 0)
    {
        irdata = 0;
        //printf ("data low\n");
    }

    _timerCount++; // One more 50us tick
    if (_rawlen >= RAWBUF)
    {
        // Buffer overflow
        _rcvstate = STATE_STOP;
    }
    switch (_rcvstate)
    {
    case STATE_IDLE: // In the middle of a gap
        if (irdata == MARK)
        {
            if (_timerCount < GAP_TICKS)
            {
                // Not big enough to be a gap.
                _timerCount = 0;
            }
            else
            {
                // gap just ended, record duration and start recording transmission
                _rawlen = 0;
                _rawbuf[_rawlen++] = _timerCount;
                _timerCount = 0;
                _rcvstate = STATE_MARK;
            }
        }
        break;
    case STATE_MARK: // timing MARK
        if (irdata == SPACE)
        { // MARK ended, record time
            _rawbuf[_rawlen++] = _timerCount;
            _timerCount = 0;
            _rcvstate = STATE_SPACE;
        }
        break;
    case STATE_SPACE: // timing SPACE
        if (irdata == MARK)
        { // SPACE just ended, record it
            _rawbuf[_rawlen++] = _timerCount;
            _timerCount = 0;
            _rcvstate = STATE_MARK;
        }
        else
        { // SPACE
            if (_timerCount > GAP_TICKS)
            {
                // big SPACE, indicates gap between codes
                // Mark current code as ready for processing
                // Switch to STOP
                // Don't reset timer; keep counting space width
                _rcvstate = STATE_STOP;
            }
        }
        break;
    case STATE_STOP: // waiting, measuring gap
        if (irdata == MARK)
        { // reset gap timer
            _timerCount = 0;
        }

        if (_callBack && decode())
        {
            _callBack->RemoteButtonPressed(_value);
            uint32_t maxIdle = 200;
            uint32_t totalIdle = 0;
            while (1)
            {
            	if (read_pin())
            	{
            		if (totalIdle++ >= maxIdle)
            		{
            			break;
            		}
            	}
            	else
            	{
            		totalIdle= 0;
            	}
            	RCC_Delay_us(100);

            }
        }
        resume();
        break;
    }

}
