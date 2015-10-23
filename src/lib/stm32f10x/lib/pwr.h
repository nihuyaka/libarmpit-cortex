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


#ifndef _PWR_H
#define _PWR_H

#include "common.h"

#ifdef USE_PWR

#include "rcc.h"
#include "peripheral.h"

/* PWR   APB1 ****************************************************/
#define PWR_OFFSET 0x7000
#define PWR_BASE  (PERIPH_BASE + PWR_OFFSET)

#define PWR_CR  (*(volatile uint32_t*)(PWR_BASE))
#define PWR_CR_DBP  (1<<8)   //backup domain write protection
#define PWR_CR_PVDE (1<<4)  //power voltage detector enable
#define PWR_CR_CSBF (1<<3)  //clear standby flag (write 1 to clear)
#define PWR_CR_CWUF (1<<2)  //clear the WUF wake-up flag

#define PWR_CR_PDDS (1<<1)  //set and cleared by software. It works together with the LPDS bit
                            //0: STOP on deepsleep   1: STANDBY on deepsleep

#define PWR_CR_LPDS (1<<0)  //set and cleared by software. It works together with the PDDS bit.
                            //0: Voltage regulator on during Stop mode
                            //1: Voltage regulator in low-power mode during Stop mode

#define PWR_CSR  (*(volatile uint32_t*)(PWR_BASE + 0x4))
  
#define PWR_CSR_EWUP (1<<8)     //1: WKUP pin is used for wakeup from Standby mode and forced in input pull down 
                                //   configuration (rising edge on WKUP pin wakes-up the system from Standby mode).

#define PWR_CSR_PVDO (1<<2)  //This bit is set and cleared by hardware. It is valid only if PVD is enabled by the PVDE bit. 
                             //0: VDD/VDDAis higher than the PVD threshold selected with the PLS[2:0] bits. 
                             //1: VDD/VDDAis lower than the PVD threshold selected with the PLS[2:0] bits.

#define PWR_CSR_SBF (1<<1)   //Standby flag  (read only)
                             //0: Device has not been in Standby mode
                             //1: Device has been in Standby mode

#define PWR_CSR_WUF (1<<0)   //Wakeup flag  (read only) 
                             //0: No wakeup event occurred
                             //1: A wakeup event was received from the WKUP pin or from the RTC alarm


class PWR : public Peripheral
{
private:
    PWR() {}

    PWR(PWR const&);
    void operator=(PWR const&);

public:

    static PWR* GetInstance()
    {
        static PWR instance;
        return &instance;
    }

    void EnablePeripheralClock(bool enable);
    void EnableBKPWriteAccess(bool enable);

    void Sleep(bool isWFI, bool sleepOnExit = false);
    void Stop(bool isLowPower, bool isWFI, bool sleepOnExit = false);
    void Standby(bool isWFI, bool enableWakeupPin, bool sleepOnExit = false);
    void EnableWakeupPin(bool enable);
    bool IsSBF();
    void ClearSBF();
    bool IsWUF();
    void ClearWUF();
};



#endif


#endif
