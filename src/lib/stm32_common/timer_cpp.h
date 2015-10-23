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

#ifndef _TIMER_CPP_H
#define _TIMER_CPP_H

#include "common.h"

#ifdef USE_TIMER

#include "timer.h"

#include "nvic.h"
#include "rcc.h"
#include "peripheral.h"

class TIMER;
class TIMER_Channel;

class TIMER_Interrupt_Handler
{
public:
    virtual void HandleInterrupt(bool isUpdate, bool isTrigger) = 0;

};

class TIMER_Channel_CCInterrupt_Handler
{
public:
    virtual void HandleInterrupt(TIMER_Channel* ch) = 0;

};

class TIMER_With_OnePulseMode
{
private:
    volatile uint32_t* _cr1;
public:
    TIMER_With_OnePulseMode(uint32_t timx_base_addr);
    //cr1
    void EnableOnePulseMode(bool enable);
};

class TIMER_With_UpDownCounter
{
private:
    volatile uint32_t* _cr1;
public:
    TIMER_With_UpDownCounter(uint32_t timx_base_addr);
    //cr1
    void SetCenterAlignedModeOFF();
    void SetCenterAlignedModeFlagOnUp();
    void SetCenterAlignedModeFlagOnDown();
    void SetCenterAlignedModeFlagOnUpDown();
    void SetDirectionUp();
    void SetDirectionDown();
};

class TIMER_With_DMAControl //2-5
{
private:
    volatile uint32_t* _dcr;
    volatile uint32_t* _dmar;
    volatile uint32_t* _cr2;
    volatile uint32_t* _dier;

public:
    TIMER_With_DMAControl(uint32_t timx_base_addr);
    //dcr
    void SetDMABaseAddress(uint16_t addr);
    void SetDMABurstLength(uint16_t length);
    void SetDMAAddressFullTransfer(uint16_t addr);
    void SendDMARequestOnCCEvent();
    void SendDMARequestOnUpdateEvent();
    void EnableUpdateDMARequest(bool enable);
    void EnableTriggerDMARequest(bool enable);

};

class TIMER_With_MMS
{
private:
    volatile uint32_t* _cr2;
public:
    TIMER_With_MMS(uint32_t timx_base_addr);
    //cr2
    void SetMMS_Reset();
    void SetMMS_Enable();
    void SetMMS_Update();
    void SetMMS_Compare_Pulse();
    void SetMMS_Compare_OC1REF();
    void SetMMS_Compare_OC2REF();
    void SetMMS_Compare_OC3REF();
    void SetMMS_Compare_OC4REF();

};

class TIMER_With_SlaveMode
{
private:
    volatile uint32_t* _smcr;
public:
    TIMER_With_SlaveMode(uint32_t timx_base_addr);
    //smcr
    void SetSlaveMode_Disabled();
    void SetSlaveMode_Encoder1();
    void SetSlaveMode_Encoder2();
    void SetSlaveMode_Encoder3();
    void SetSlaveMode_Reset();
    void SetSlaveMode_Gated();
    void SetSlaveMode_Trigger();
    void SetSlaveMode_ExternalClock();
    void SetSlaveModeTrigger_ITR0();
    void SetSlaveModeTrigger_ITR1();
    void SetSlaveModeTrigger_ITR2();
    void SetSlaveModeTrigger_ITR3();
    void SetSlaveModeTrigger_TI1F_ED();
    void SetSlaveModeTrigger_TI1FP1();
    void SetSlaveModeTrigger_TI1FP2();
    void SetSlaveModeTrigger_ETRF();
    void EnableMasterSlaveMode(bool enable);
};

class TIMER_With_BDTR_RCR
{
protected:
    TIMER_With_BDTR_RCR (uint32_t timx_base_addr)
    {
        _bdtr = (volatile uint32_t*)(timx_base_addr + TIM_BDTR_OFFSET);
        _rcr = (volatile uint32_t*)(timx_base_addr + TIM_RCR_OFFSET);
    }
    volatile uint32_t* _bdtr;
    volatile uint32_t* _rcr;
public:
    void SetBDTR(uint16_t val)
    {   *_bdtr = val;}
    void SetRCR(uint16_t val)
    {   *_rcr = val;}
    uint16_t GetBDTR()
    {   return *_bdtr;}
    uint16_t GetRCR()
    {   return *_rcr;}
};

class TIMER_With_Complementary_Outputs
{
public:
};

class TIMER_With_Channels;

class PWM_Capture_Handler
{
public:
    virtual void Handle (uint32_t period, uint32_t duty) = 0;
};
class TIMER_Channel
{
    friend class TIMER_With_Channels;
    friend class AdvancedTimer;

private:

    TIMER_With_Channels* _timer;
    int8_t _channelNo;
    volatile uint32_t* _dier;
    volatile uint32_t* _sr;
    volatile uint32_t* _egr;
    volatile uint32_t* _ccmr;
    volatile uint32_t* _ccer;
    volatile uint32_t* _ccr;
    volatile uint32_t* _bdtr;

    uint16_t _dier_CCxDE;
    uint16_t _dier_CCxIE;

    uint16_t _sr_CCxIF;
    uint16_t _sr_CCxOF;

    uint16_t _egr_CCxG;

    uint16_t _ccmr_CCxS; //input/output selection

    uint16_t _ccmr_OCxFE;//fast
    uint16_t _ccmr_OCxPE;//preload
    uint16_t _ccmr_OCxM;//mode
    uint16_t _ccmr_OCxCE;//clear enable

    uint16_t _ccmr_ICxPSC;//prescaler
    uint16_t _ccmr_ICxF;//filter sampling freq

    uint16_t _ccer_CCxE;//output/capture enable
    uint16_t _ccer_CCxP;//output/input  polarity

    TIMER_Channel_CCInterrupt_Handler* _ccHandler;
    PWM_Capture_Handler* _pwmCaptureHandler;

    void SetupPWM(uint32_t period_us, uint32_t duty_us, bool isPWM1);

public:

    TIMER_Channel()
    {
        _timer = 0;
        _channelNo = -1; //invalid
        _ccHandler = 0;
    }

    TIMER_With_Channels* GetTimer() { return _timer; }

    //dier
    void EnableCCInterrupt(bool enable, TIMER_Channel_CCInterrupt_Handler* handler = 0);
    void EnableCCDMARequest(bool enable);

    //sr
    bool IsCCFlag();
    void ClearCCFlag();
    bool IsOCFlag();
    void ClearOCFlag();

    //egr

    void GenerateCCEvent(bool enable);

    //ccmr
    void SetModeOutput();
    void SetModeInputDirect();
    void SetModeInputInverse();
    void EnableFastMode(bool enable);
    void EnableOCPreload(bool enable);
    void SetOCMode_Frozen();
    void SetOCMode_HighOnMatch();
    void SetOCMode_LowOnMatch();
    void SetOCMode_ToggleOnMatch();
    void SetOCMode_ForceLow();
    void SetOCMode_ForceHigh();
    void SetOCMode_PWM1();
    void SetOCMode_PWM2();
    void EnableClearOnETRF(bool enable);
    void SetICPrescaler_None();
    void SetICPrescaler_2();
    void SetICPrescaler_4();
    void SetICPrescaler_8();
    void SetICFilter_None();
    void SetICFilter_CK_N2();
    void SetICFilter_CK_N4();
    void SetICFilter_CK_N8();
    void SetICFilter_DTS_DIV2_N6();
    void SetICFilter_DTS_DIV2_N8();
    void SetICFilter_DTS_DIV4_N6();
    void SetICFilter_DTS_DIV4_N8();
    void SetICFilter_DTS_DIV8_N6();
    void SetICFilter_DTS_DIV8_N8();
    void SetICFilter_DTS_DIV16_N5();
    void SetICFilter_DTS_DIV16_N6();
    void SetICFilter_DTS_DIV16_N8();
    void SetICFilter_DTS_DIV32_N5();
    void SetICFilter_DTS_DIV32_N6();
    void SetICFilter_DTS_DIV32_N8();

    //ccer
    void EnableChannel(bool enable);
    void SetCCPolarityLow(bool set);

    //ccr
    void SetCCR(uint16_t val);
    uint16_t GetCCR();

    void SetupPWM1(uint32_t period_us, uint32_t duty_us);
    void SetupPWM2(uint32_t period_us, uint32_t duty_us);
    void UpdatePWMDuty(uint32_t duty_us);

    void CaptureInputPWM (uint32_t max_period_us, PWM_Capture_Handler* handler = 0);

};

class TIMER : public Peripheral
{
protected:
    volatile uint32_t* _cr1;
    //volatile uint32_t* _cr2;
    volatile uint32_t* _dier;
    volatile uint32_t* _sr;
    volatile uint32_t* _egr;
    volatile uint32_t* _cnt;
    volatile uint32_t* _psc;
    volatile uint32_t* _arr;
    const static uint32_t MAX_UPDATE_HANDLERS = 32;
    TIMER_Interrupt_Handler* _irqHandlers[MAX_UPDATE_HANDLERS];
    IRQn_Type _globalInterrupt;
    uint8_t _irqHandlerCount;
    bool _isAPB1;

protected:

    bool _is32_bit;

    TIMER(uint32_t timx_base_addr, IRQn_Type irqNo,
            volatile uint32_t* rccEnableReg, volatile uint32_t* rccResetReg, uint32_t rccBit,
            bool isAPB1);
public:

    void EnableCounter(bool enable);
    void EnableUpdateEvent(bool enable);
    void SetUpdateRequestSource(bool isAny);
    void EnableAutoPreload(bool enable);
    void SetClockDivision_TCK();
    void SetClockDivision_TCKx2();
    void SetClockDivision_TCKx4();

    void SetCounterValue(uint32_t val);
    void SetPrescalerValue(uint16_t val);
    void SetAutoReloadValue(uint32_t val);
    void SetUpdatePeriod_us (uint32_t us);

    //sr
    bool IsUIF();
    void ClearUIF();

    //egr
    void GenerateRegisterUpdate(bool enable);

    void CalculateTimerValues (uint32_t us, uint32_t* count, uint16_t* presc);
    void CalculateTimerValues2 (uint32_t us, uint16_t* count, uint16_t* presc);

    void EnableTriggerInterrupt(bool enable);
    void EnableNVICInterrupt(bool enable);
    void EnableUpdateInterrupt(bool enable);
    void AddInterruptHandler (TIMER_Interrupt_Handler* handler);
    virtual void HandleInterrupt();

};

class TIMER_With_Channels : public TIMER
{
protected:
    TIMER_Channel _channels[4];
    uint8_t _nchannels;
protected:
    TIMER_With_Channels(uint32_t timx_base_addr, uint8_t nchannels, IRQn_Type irqNo,
            volatile uint32_t* rccEnableReg,  volatile uint32_t* rccResetReg, uint32_t rccBit, bool isAPB1);

public:
    TIMER_Channel* GetChannel(int channelNo);
    TIMER_Channel* GetChannels() { return _channels; }
    bool IsTIF();
    void ClearTIF();
    bool IsCenterAlignedModeEnabled();
    virtual void HandleInterrupt();

};

class AdvancedTimer: public TIMER_With_Channels,
public TIMER_With_DMAControl,
public TIMER_With_OnePulseMode,
public TIMER_With_UpDownCounter,
public TIMER_With_MMS,
public TIMER_With_SlaveMode,
public TIMER_With_BDTR_RCR,
public TIMER_With_Complementary_Outputs
{
protected:
    IRQn_Type _ccIrqNo;

    AdvancedTimer(uint32_t timx_base_addr, IRQn_Type updateIrqNo, IRQn_Type ccIrqNo,
        volatile uint32_t* rccEnableReg, volatile uint32_t* rccResetReg, uint32_t rccBit);

public:


};

#if defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL)
#define IRQn_TIM1_UP IRQn_TIM1_UP_TIM16
#elif defined(STM32F10X_XL) || defined (STM32F4) || defined (STM32F2)
#define IRQn_TIM1_UP IRQn_TIM1_UP_TIM10
#endif

class TIM1: public AdvancedTimer
{
private:
    TIM1() : AdvancedTimer(TIM1_BASE, IRQn_TIM1_UP, IRQn_TIM1_CC,  &RCC_APB2ENR, &RCC_APB2RSTR, RCC_APB2ENR_TIM1EN)
    {
    }

public:

    static TIM1* GetInstance()
    {
        static TIM1 instance;
        return &instance;
    }


};


#if (defined(STM32F10X_XL) || defined(STM32F10X_HD) || defined(STM32F4) || defined(STM32F2)) \
&& !defined(STM32F401xC)  && !defined(STM32F401xE) && !defined(STM32F401xx) && !defined(STM32F411xE)


#if defined(STM32F10X_XL) || defined(STM32F2) || defined(STM32F4) 
#define IRQn_TIM8_UP IRQn_TIM8_UP_TIM13
#endif

class TIM8: public AdvancedTimer
{
private:
    TIM8() : AdvancedTimer(TIM8_BASE, IRQn_TIM8_UP, IRQn_TIM8_CC,
        &RCC_APB2ENR, &RCC_APB2RSTR, RCC_APB2ENR_TIM1EN)
    {
    }

public:

    static TIM8* GetInstance()
    {
        static TIM8 instance;
        return &instance;
    }


};

#endif

class TIM2: public TIMER_With_Channels,
public TIMER_With_DMAControl,
public TIMER_With_OnePulseMode,
public TIMER_With_UpDownCounter,
public TIMER_With_MMS,
public TIMER_With_SlaveMode
{
private:
    TIM2() :
    TIMER_With_Channels(TIM2_BASE, 4, IRQn_TIM2, &RCC_APB1ENR, &RCC_APB1RSTR, RCC_APB1ENR_TIM2EN, true),
    TIMER_With_DMAControl(TIM2_BASE),
    TIMER_With_OnePulseMode(TIM2_BASE),
    TIMER_With_UpDownCounter(TIM2_BASE),
    TIMER_With_MMS(TIM2_BASE),
    TIMER_With_SlaveMode(TIM2_BASE)
    {
#if (defined(STM32F4) || defined(STM32F2))
    	//_is32_bit = true;
#endif
    }

public:

    static TIM2* GetInstance()
    {
        static TIM2 instance;
        return &instance;
    }


};

class TIM3: public TIMER_With_Channels,
public TIMER_With_DMAControl,
public TIMER_With_OnePulseMode,
public TIMER_With_UpDownCounter,
public TIMER_With_MMS,
public TIMER_With_SlaveMode
{
private:
    TIM3() :
    TIMER_With_Channels(TIM3_BASE, 4, IRQn_TIM3, &RCC_APB1ENR, &RCC_APB1RSTR, RCC_APB1ENR_TIM3EN, true),
    TIMER_With_DMAControl(TIM3_BASE),
    TIMER_With_OnePulseMode(TIM3_BASE),
    TIMER_With_UpDownCounter(TIM3_BASE),
    TIMER_With_MMS(TIM3_BASE),
    TIMER_With_SlaveMode(TIM3_BASE)
    {
    }

public:

    static TIM3* GetInstance()
    {
        static TIM3 instance;
        return &instance;
    }


};

#if !defined(STM32F10X_LD) && !defined(STM32F10X_LD_VL)

class TIM4: public TIMER_With_Channels,
public TIMER_With_DMAControl,
public TIMER_With_OnePulseMode,
public TIMER_With_UpDownCounter,
public TIMER_With_MMS,
public TIMER_With_SlaveMode
{
private:
    TIM4() :
    TIMER_With_Channels(TIM4_BASE, 4, IRQn_TIM4, &RCC_APB1ENR, &RCC_APB1RSTR, RCC_APB1ENR_TIM4EN, true),
    TIMER_With_DMAControl(TIM4_BASE),
    TIMER_With_OnePulseMode(TIM4_BASE),
    TIMER_With_UpDownCounter(TIM4_BASE),
    TIMER_With_MMS(TIM4_BASE),
    TIMER_With_SlaveMode(TIM4_BASE)
    {
    }

public:

    static TIM4* GetInstance()
    {
        static TIM4 instance;
        return &instance;
    }

};

#endif

#if defined(STM32F4) || defined(STM32F2) || defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL)

class TIM5: public TIMER_With_Channels,
public TIMER_With_DMAControl,
public TIMER_With_OnePulseMode,
public TIMER_With_UpDownCounter,
public TIMER_With_MMS,
public TIMER_With_SlaveMode
{
private:
    TIM5() :
    TIMER_With_Channels(TIM5_BASE, 4, IRQn_TIM5, &RCC_APB1ENR, &RCC_APB1RSTR, RCC_APB1ENR_TIM5EN, true),
    TIMER_With_DMAControl(TIM5_BASE),
    TIMER_With_OnePulseMode(TIM5_BASE),
    TIMER_With_UpDownCounter(TIM5_BASE),
    TIMER_With_MMS(TIM5_BASE),
    TIMER_With_SlaveMode(TIM5_BASE)
    {
#if (defined(STM32F4) || defined(STM32F2))
    	//_is32_bit = true;
#endif
    }

public:

    static TIM5* GetInstance()
    {
        static TIM5 instance;
        return &instance;
    }

};

#endif

#if (defined(STM32F4) || defined(STM32F2) || defined(VALUE_LINE)  \
|| defined(STM32F10X_HD)  || defined(STM32F10X_XL) || defined(STM32F10X_CL)) \
&& !defined(STM32F401xC)  && !defined(STM32F401xE) && !defined(STM32F401xx) && !defined(STM32F411xE)



#if defined(VALUE_LINE) || defined(STM32F2) || defined(STM32F4)
#define IRQn_TIM6 IRQn_TIM6_DAC
#endif

class TIM6: public TIMER, TIMER_With_MMS
{
private:
    TIM6() :
        TIMER(TIM6_BASE, IRQn_TIM6, &RCC_APB1ENR, &RCC_APB1RSTR, RCC_APB1ENR_TIM6EN, true),
        TIMER_With_MMS(TIM6_BASE)
    {
    }
public:

    static TIM6* GetInstance()
    {
        static TIM6 instance;
        return &instance;
    }

};

class TIM7: public TIMER, TIMER_With_MMS
{
private:
    TIM7() :
    TIMER(TIM7_BASE, IRQn_TIM7, &RCC_APB1ENR, &RCC_APB1RSTR, RCC_APB1ENR_TIM7EN, true),
    TIMER_With_MMS(TIM7_BASE)
    {
    }
public:

    static TIM7* GetInstance()
    {
        static TIM7 instance;
        return &instance;
    }


};
#endif

#if  defined(STM32F10X_HD_VL)


class TIM12 : public TIMER_With_Channels,
public TIMER_With_OnePulseMode,
public TIMER_With_MMS,
public TIMER_With_SlaveMode
{
private:
    TIM12() :
    TIMER_With_Channels(TIM12_BASE, 2, IRQn_TIM12, &RCC_APB1ENR, &RCC_APB1RSTR, RCC_APB1ENR_TIM12EN, true),
    TIMER_With_OnePulseMode(TIM12_BASE),
    TIMER_With_MMS(TIM12_BASE),
    TIMER_With_SlaveMode(TIM12_BASE)
    {
    }

public:

    static TIM12* GetInstance()
    {
        static TIM12 instance;
        return &instance;
    }


};

#elif (defined(STM32F10X_XL) || defined(STM32F2) || defined(STM32F4)) \
&& !defined(STM32F401xC)  && !defined(STM32F401xE) && !defined(STM32F401xx) && !defined(STM32F411xE)

class TIM12 : public TIMER_With_Channels,
public TIMER_With_OnePulseMode,
public TIMER_With_SlaveMode
{
private:
    TIM12() :
    TIMER_With_Channels(TIM12_BASE, 2, IRQn_TIM8_BRK_TIM12, &RCC_APB1ENR, &RCC_APB1RSTR, RCC_APB1ENR_TIM12EN, true),
    TIMER_With_OnePulseMode(TIM12_BASE),
    TIMER_With_SlaveMode(TIM12_BASE)
    {
    }

public:

    static TIM12* GetInstance()
    {
        static TIM12 instance;
        return &instance;
    }


};

#endif

#if defined(STM32F2) || defined(STM32F4) || defined(STM32F10X_XL)

class TIM9 : public TIMER_With_Channels,
public TIMER_With_OnePulseMode,
public TIMER_With_SlaveMode
{
private:
    TIM9() :
    TIMER_With_Channels(TIM9_BASE, 2, IRQn_TIM1_BRK_TIM9, &RCC_APB2ENR, &RCC_APB2RSTR, RCC_APB2ENR_TIM9EN, false),
    TIMER_With_OnePulseMode(TIM9_BASE),
    TIMER_With_SlaveMode(TIM9_BASE)
    {
    }

public:

    static TIM9* GetInstance()
    {
        static TIM9 instance;
        return &instance;
    }


};

class TIM10 : public TIMER_With_Channels
{
private:
    TIM10() :
    TIMER_With_Channels(TIM10_BASE, 1, IRQn_TIM1_UP_TIM10, &RCC_APB2ENR, &RCC_APB2RSTR, RCC_APB2ENR_TIM10EN, false)
    {
    }

public:

    static TIM10* GetInstance()
    {
        static TIM10 instance;
        return &instance;
    }


};

class TIM11 : public TIMER_With_Channels
{
private:
    TIM11() :
    TIMER_With_Channels(TIM11_BASE, 1, IRQn_TIM1_TRG_COM_TIM11, &RCC_APB2ENR, &RCC_APB2RSTR, RCC_APB2ENR_TIM11EN, false)
    {
    }

public:

    static TIM11* GetInstance()
    {
        static TIM11 instance;
        return &instance;
    }


};
#endif

#if (defined(STM32F2) || defined(STM32F4) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL)) \
&& !defined(STM32F401xC)  && !defined(STM32F401xE) && !defined(STM32F401xx) && !defined(STM32F411xE)


#if defined(STM32F10X_XL) || defined(STM32F2) || defined (STM32F4)
#define IRQn_TIM13  IRQn_TIM8_UP_TIM13
#define IRQn_TIM14  IRQn_TIM8_TRG_COM_TIM14
#endif

class TIM13 : public TIMER_With_Channels
{
private:
    TIM13() :
    TIMER_With_Channels(TIM13_BASE, 2, IRQn_TIM13, &RCC_APB1ENR, &RCC_APB1RSTR, RCC_APB1ENR_TIM13EN, true)
    {
    }

public:

    static TIM13* GetInstance()
    {
        static TIM13 instance;
        return &instance;
    }


};

class TIM14 : public TIMER_With_Channels
{
private:
    TIM14() :
    TIMER_With_Channels(TIM14_BASE, 2, IRQn_TIM14, &RCC_APB1ENR, &RCC_APB1RSTR, RCC_APB1ENR_TIM14EN, true)
    {
    }

public:

    static TIM14* GetInstance()
    {
        static TIM14 instance;
        return &instance;
    }


};

#endif

#if defined(VALUE_LINE)
class TIM15 : public TIMER_With_Channels,
public TIMER_With_DMAControl,
public TIMER_With_OnePulseMode,
public TIMER_With_MMS,
public TIMER_With_SlaveMode,
public TIMER_With_BDTR_RCR,
public TIMER_With_Complementary_Outputs
{
private:
    TIM15() :
    TIMER_With_Channels(TIM15_BASE, 2, IRQn_TIM1_BRK_TIM15, &RCC_APB2ENR, &RCC_APB2RSTR, RCC_APB2ENR_TIM15EN, false),
    TIMER_With_DMAControl(TIM15_BASE),
    TIMER_With_OnePulseMode(TIM15_BASE),
    TIMER_With_MMS(TIM15_BASE),
    TIMER_With_SlaveMode(TIM15_BASE),
    TIMER_With_BDTR_RCR(TIM15_BASE)
    {
    }

public:

    static TIM15* GetInstance()
    {
        static TIM15 instance;
        return &instance;
    }


};

class TIM16 : public TIMER_With_Channels,
public TIMER_With_DMAControl,
public TIMER_With_OnePulseMode,
public TIMER_With_BDTR_RCR,
public TIMER_With_Complementary_Outputs
{
private:
    TIM16() :
    TIMER_With_Channels(TIM16_BASE, 1, IRQn_TIM1_UP_TIM16, &RCC_APB2ENR, &RCC_APB2RSTR, RCC_APB2ENR_TIM16EN, false),
    TIMER_With_DMAControl(TIM16_BASE),
    TIMER_With_OnePulseMode(TIM16_BASE),
    TIMER_With_BDTR_RCR(TIM16_BASE)
    {
    }

public:

    static TIM16* GetInstance()
    {
        static TIM16 instance;
        return &instance;
    }


};

class TIM17 : public TIMER_With_Channels,
public TIMER_With_DMAControl,
public TIMER_With_OnePulseMode,
public TIMER_With_BDTR_RCR,
public TIMER_With_Complementary_Outputs

{
private:
    TIM17() :
    TIMER_With_Channels(TIM17_BASE, 1, IRQn_TIM1_TRG_COM_TIM17, &RCC_APB2ENR, &RCC_APB2RSTR, RCC_APB2ENR_TIM17EN, false),
    TIMER_With_DMAControl(TIM17_BASE), TIMER_With_OnePulseMode(TIM17_BASE),
    TIMER_With_BDTR_RCR(TIM16_BASE)
    {
    }

public:

    static TIM17* GetInstance()
    {
        static TIM17 instance;
        return &instance;
    }


};
#endif

#if defined(STM32L0)

class TIM21 : public TIMER_With_Channels,
public TIMER_With_OnePulseMode,
public TIMER_With_MMS,
public TIMER_With_SlaveMode,
public TIMER_With_BDTR_RCR,
public TIMER_With_Complementary_Outputs
{
private:
    TIM21() :
    TIMER_With_Channels(TIM21_BASE, 2, IRQn_TIM1_BRK_TIM15, &RCC_APB2ENR, &RCC_APB2RSTR, RCC_APB2ENR_TIM21EN, false),
    TIMER_With_OnePulseMode(TIM21_BASE),
    TIMER_With_MMS(TIM21_BASE),
    TIMER_With_SlaveMode(TIM21_BASE),
    TIMER_With_BDTR_RCR(TIM21_BASE)
    {
    }

public:

    static TIM21* GetInstance()
    {
        static TIM21 instance;
        return &instance;
    }

};

class TIM22 : public TIMER_With_Channels,
public TIMER_With_OnePulseMode,
public TIMER_With_MMS,
public TIMER_With_SlaveMode,
public TIMER_With_BDTR_RCR,
public TIMER_With_Complementary_Outputs
{
private:
    TIM22() :
    TIMER_With_Channels(TIM22_BASE, 2, IRQn_TIM1_BRK_TIM15, &RCC_APB2ENR, &RCC_APB2RSTR, RCC_APB2ENR_TIM22EN, false),
    TIMER_With_OnePulseMode(TIM22_BASE),
    TIMER_With_MMS(TIM22_BASE),
    TIMER_With_SlaveMode(TIM22_BASE),
    TIMER_With_BDTR_RCR(TIM22_BASE)
    {
    }

public:

    static TIM22* GetInstance()
    {
        static TIM22 instance;
        return &instance;
    }

};


#endif


#endif

#endif
