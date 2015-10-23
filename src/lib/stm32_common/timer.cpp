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




#include "timer_cpp.h"

#ifdef USE_TIMER

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(VALUE_LINE)
void TIM1_BRK_TIM15_IRQHandler(void)
{
    TIM15::GetInstance()->HandleInterrupt();
}

void TIM1_UP_TIM16_IRQHandler(void)
{
    if (TIM1::GetInstance()->IsUIF())
    {
        TIM1::GetInstance()->HandleInterrupt();
    }
    else
    {
        TIM16::GetInstance()->HandleInterrupt();
    }
}

void TIM1_TRG_COM_TIM17_IRQHandler(void)
{
    TIM17::GetInstance()->HandleInterrupt();
}
#endif

#if defined(STM32F2) || defined(STM32F4) || defined(STM32F10X_XL)
void TIM1_BRK_TIM9_IRQHandler(void)
{
    TIM9::GetInstance()->HandleInterrupt();
}
void TIM1_UP_TIM10_IRQHandler(void)
{
    if (TIM1::GetInstance()->IsUIF())
    {
        TIM1::GetInstance()->HandleInterrupt();
    }
    else
    {
        TIM10::GetInstance()->HandleInterrupt();
    }
}
void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
    TIM11::GetInstance()->HandleInterrupt();
}
#endif

//void TIM1_BRK_IRQHandler(void)
//{
//}
void TIM1_UP_IRQHandler(void)
{
    TIM1::GetInstance()->HandleInterrupt();
}
//void TIM1_TRG_COM_IRQHandler(void)
//{
//}
void TIM1_CC_IRQHandler(void)
{
    TIM1::GetInstance()->HandleInterrupt();
}

void TIM2_IRQHandler(void)
{
    TIM2::GetInstance()->HandleInterrupt();
}

void TIM3_IRQHandler(void)
{
    TIM3::GetInstance()->HandleInterrupt();
}

#if !defined(STM32F10X_LD) && !defined(STM32F10X_LD_VL)
void TIM4_IRQHandler(void)
{
    TIM4::GetInstance()->HandleInterrupt();
}
#endif

#if defined(STM32F2) || defined(STM32F4) || defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL)
void TIM5_IRQHandler(void)
{
    TIM5::GetInstance()->HandleInterrupt();
}
#endif

#if defined(VALUE_LINE)
void TIM6_DAC_IRQHandler(void)
{
    if (TIM6::GetInstance()->IsUIF())
    {
        TIM6::GetInstance()->HandleInterrupt();
    }
}
#endif

#if (defined(STM32F2) || defined(STM32F4) || defined(STM32F10X_HD)  || defined(STM32F10X_XL) || defined(STM32F10X_CL)) \
&& !defined(STM32F401xC)  && !defined(STM32F401xE) && !defined(STM32F401xx) && !defined(STM32F411xE)

void TIM6_IRQHandler(void)
{
    TIM6::GetInstance()->HandleInterrupt();
}
void TIM7_IRQHandler(void)
{
    TIM7::GetInstance()->HandleInterrupt();
}
#endif

#if (defined(STM32F2) || defined(STM32F4) || defined(STM32F10X_HD_VL)) \
&& !defined(STM32F401xC)  && !defined(STM32F401xE) && !defined(STM32F401xx) && !defined(STM32F411xE)

void TIM12_IRQHandler(void)
{
    TIM12::GetInstance()->HandleInterrupt();
}
void TIM13_IRQHandler(void)
{
    TIM13::GetInstance()->HandleInterrupt();
}
void TIM14_IRQHandler(void)
{
    TIM14::GetInstance()->HandleInterrupt();
}
#endif

#if defined(STM32F10X_XL)
void TIM8_BRK_TIM12_IRQHandler(void)
{
    TIM12::GetInstance()->HandleInterrupt();
}
void TIM8_UP_TIM13_IRQHandler(void)
{
    if (TIM8::GetInstance()->IsUIF())
    {
        TIM8::GetInstance()->HandleInterrupt();
    }
    else
    {
        TIM13::GetInstance()->HandleInterrupt();
    }
}
//void TIM8_TRG_COM_TIM14_IRQHandler(void)
//{
//}
void TIM8_CC_IRQHandler(void)
{
    TIM8::GetInstance()->HandleInterrupt();
}
#endif


#if (defined(STM32F2) || defined(STM32F4) || defined(STM32F10X_HD)) \
&& !defined(STM32F401xC)  && !defined(STM32F401xE) && !defined(STM32F401xx) && !defined(STM32F411xE)
//void TIM8_BRK_IRQHandler(void)
//{
//}
void TIM8_UP_IRQHandler(void)
{
    TIM8::GetInstance()->HandleInterrupt();
}
//void TIM8_TRG_COM_IRQHandler(void)
//{
//}
void TIM8_CC_IRQHandler(void)
{
    TIM8::GetInstance()->HandleInterrupt();
}

#endif


#if defined(STM32L0)

void TIM21_IRQHandler(void)
{
    TIM21::GetInstance()->HandleInterrupt();
}

void TIM22_IRQHandler(void)
{
    TIM22::GetInstance()->HandleInterrupt();
}
#endif



#ifdef __cplusplus
}
#endif

void TIMER::HandleInterrupt()
{
    if (IsUIF())
    {
        for (uint8_t i = 0; i < _irqHandlerCount; ++i)
        {
            ClearUIF();
            _irqHandlers[i]->HandleInterrupt(true, false);
        }
    }
}

void TIMER_With_Channels::HandleInterrupt()
{
    TIMER::HandleInterrupt();
    if (IsTIF())
    {
        if (_irqHandlerCount > 0)
        {
            ClearTIF();
            _irqHandlers[0]->HandleInterrupt(false, true);
        }
    }
    
    if (_channels[0]._pwmCaptureHandler && _channels[0].IsCCFlag())
    {
        _channels[0].ClearCCFlag();
        uint16_t period = _channels[0].GetCCR();
        uint16_t duty   = _channels[1].GetCCR();

        uint32_t timClk = RCC_GetTIMx_CLK(_isAPB1);
        volatile uint32_t period_us = (uint64_t)period * 1000000llu * (uint64_t)(*_psc + 1) / timClk;
        volatile uint32_t duty_us = (uint64_t)duty * 1000000llu * (uint64_t)(*_psc + 1) / timClk;
        _channels[0]._pwmCaptureHandler->Handle(period_us, duty_us);
    }
    else 
    {
        for (uint8_t i = 0; i < _nchannels; ++i)
        {
            if (_channels[i].IsCCFlag())
            {
                _channels[i].ClearCCFlag();
                if (_channels[i]._ccHandler)
                    _channels[i]._ccHandler->HandleInterrupt(&_channels[i]);
            }
        }
    }

}


TIMER_With_OnePulseMode::TIMER_With_OnePulseMode (uint32_t timx_base_addr)
{
    _cr1 = (volatile uint32_t*)(timx_base_addr + TIM_CR1_OFFSET);
}

void TIMER_With_OnePulseMode::EnableOnePulseMode (bool enable)
{
    if (enable)
        *_cr1 |= TIM_CR1_OPM;
    else
        *_cr1 &= ~TIM_CR1_OPM;
}


TIMER_With_UpDownCounter::TIMER_With_UpDownCounter (uint32_t timx_base_addr)
{
    _cr1 = (volatile uint32_t*)(timx_base_addr + TIM_CR1_OFFSET);
}
void TIMER_With_UpDownCounter::SetCenterAlignedModeOFF()
{
    *_cr1 &= ~TIM_CR1_CMS_CLEARMASK;
    *_cr1 |= TIM_CR1_CMS_EDGE_ALIGNED;
}
void TIMER_With_UpDownCounter::SetCenterAlignedModeFlagOnUp()
{
    *_cr1 &= ~TIM_CR1_CMS_CLEARMASK;
    *_cr1 |= TIM_CR1_CMS_CENTER_ALIGNED_UP;
}
void TIMER_With_UpDownCounter::SetCenterAlignedModeFlagOnDown()
{
    *_cr1 &= ~TIM_CR1_CMS_CLEARMASK;
    *_cr1 |= TIM_CR1_CMS_CENTER_ALIGNED_DOWN;
}
void TIMER_With_UpDownCounter::SetCenterAlignedModeFlagOnUpDown()
{
    *_cr1 &= ~TIM_CR1_CMS_CLEARMASK;
    *_cr1 |= TIM_CR1_CMS_CENTER_ALIGNED_UP_DOWN;
}
void TIMER_With_UpDownCounter::SetDirectionUp()
{
    *_cr1 &= ~TIM_CR1_DIR;
}
void TIMER_With_UpDownCounter::SetDirectionDown()
{
    *_cr1 |= TIM_CR1_DIR;
}


TIMER_With_DMAControl::TIMER_With_DMAControl(uint32_t timx_base_addr)
{
    _dcr = (volatile uint32_t*)(timx_base_addr + TIM_DCR_OFFSET);
    _dmar = (volatile uint32_t*)(timx_base_addr + TIM_DMAR_OFFSET);
    _cr2 = (volatile uint32_t*)(timx_base_addr + TIM_CR2_OFFSET);
    _dier = (volatile uint32_t*)(timx_base_addr + TIM_DIER_OFFSET);
}

void TIMER_With_DMAControl::SetDMABaseAddress (uint16_t addr)
{
    *_dcr |=  (addr & 0x1f)<< TIM_DCR_DBA_OFFSET;
}
void TIMER_With_DMAControl::SetDMABurstLength (uint16_t length)
{
    *_dcr |=  (length & 0x1f)<< TIM_DCR_DBL_OFFSET;
}
void TIMER_With_DMAControl::SetDMAAddressFullTransfer (uint16_t addr)
{
    *_dmar = addr;
}


void TIMER_With_DMAControl::SendDMARequestOnCCEvent()
{
    *_cr2 &= ~TIM_CR2_CCDS;
}
void TIMER_With_DMAControl::SendDMARequestOnUpdateEvent()
{
    *_cr2 |= TIM_CR2_CCDS;
}

void TIMER_With_DMAControl::EnableUpdateDMARequest(bool enable)
{
    if (enable)
        *_dier |= TIM_DIER_UDE;
    else
        *_dier &= ~TIM_DIER_UDE;

}
void TIMER_With_DMAControl::EnableTriggerDMARequest(bool enable)
{
    if (enable)
        *_dier |= TIM_DIER_TDE;
    else
        *_dier &= ~TIM_DIER_TDE;
}



TIMER_With_MMS::TIMER_With_MMS(uint32_t timx_base_addr)
{
    _cr2 = (volatile uint32_t*)(timx_base_addr + TIM_CR2_OFFSET);
}
void TIMER_With_MMS::SetMMS_Reset()
{
    *_cr2 &= ~TIM_CR2_MMS_CLEARMASK;
    *_cr2 |= TIM_CR2_MMS_RESET;
}
void TIMER_With_MMS::SetMMS_Enable()
{
    *_cr2 &= ~TIM_CR2_MMS_CLEARMASK;
    *_cr2 |= TIM_CR2_MMS_ENABLE;
}
void TIMER_With_MMS::SetMMS_Update()
{
    *_cr2 &= ~TIM_CR2_MMS_CLEARMASK;
    *_cr2 |= TIM_CR2_MMS_UPDATE;
}
void TIMER_With_MMS::SetMMS_Compare_Pulse()
{
    *_cr2 &= ~TIM_CR2_MMS_CLEARMASK;
    *_cr2 |= TIM_CR2_MMS_COMPARE_PULSE;
}
void TIMER_With_MMS::SetMMS_Compare_OC1REF()
{
    *_cr2 &= ~TIM_CR2_MMS_CLEARMASK;
    *_cr2 |= TIM_CR2_MMS_COMPARE_OC1REF;
}
void TIMER_With_MMS::SetMMS_Compare_OC2REF()
{
    *_cr2 &= ~TIM_CR2_MMS_CLEARMASK;
    *_cr2 |= TIM_CR2_MMS_COMPARE_OC2REF;
}
void TIMER_With_MMS::SetMMS_Compare_OC3REF()
{
    *_cr2 &= ~TIM_CR2_MMS_CLEARMASK;
    *_cr2 |= TIM_CR2_MMS_COMPARE_OC3REF;
}
void TIMER_With_MMS::SetMMS_Compare_OC4REF()
{
    *_cr2 &= ~TIM_CR2_MMS_CLEARMASK;
    *_cr2 |= TIM_CR2_MMS_COMPARE_OC4REF;
}


TIMER_With_SlaveMode::TIMER_With_SlaveMode(uint32_t timx_base_addr)
{
    _smcr = (volatile uint32_t*)(timx_base_addr + TIM_SMCR_OFFSET);
}

void TIMER_With_SlaveMode::SetSlaveMode_Disabled()
{
    *_smcr &= ~TIM_SMCR_SMS_CLEARMASK;
    *_smcr |= TIM_SMCR_SMS_OFF;
}
void TIMER_With_SlaveMode::SetSlaveMode_Encoder1()
{
    *_smcr &= ~TIM_SMCR_SMS_CLEARMASK;
    *_smcr |= TIM_SMCR_SMS_ENC1;
}
void TIMER_With_SlaveMode::SetSlaveMode_Encoder2()
{
    *_smcr &= ~TIM_SMCR_SMS_CLEARMASK;
    *_smcr |= TIM_SMCR_SMS_ENC2;
}
void TIMER_With_SlaveMode::SetSlaveMode_Encoder3()
{
    *_smcr &= ~TIM_SMCR_SMS_CLEARMASK;
    *_smcr |= TIM_SMCR_SMS_ENC3;
}
void TIMER_With_SlaveMode::SetSlaveMode_Reset()
{
    *_smcr &= ~TIM_SMCR_SMS_CLEARMASK;
    *_smcr |= TIM_SMCR_SMS_RESET;
}
void TIMER_With_SlaveMode::SetSlaveMode_Gated()
{
    *_smcr &= ~TIM_SMCR_SMS_CLEARMASK;
    *_smcr |= TIM_SMCR_SMS_GATED;
}
void TIMER_With_SlaveMode::SetSlaveMode_Trigger()
{
    *_smcr &= ~TIM_SMCR_SMS_CLEARMASK;
    *_smcr |= TIM_SMCR_SMS_TRIGGER;
}
void TIMER_With_SlaveMode::SetSlaveMode_ExternalClock()
{
    *_smcr &= ~TIM_SMCR_SMS_CLEARMASK;
    *_smcr |= TIM_SMCR_SMS_EXT;
}

void TIMER_With_SlaveMode::SetSlaveModeTrigger_ITR0()
{
    *_smcr &= ~TIM_SMCR_TS_CLEARMASK;
    *_smcr |= TIM_SMCR_TS_ITR0;
}
void TIMER_With_SlaveMode::SetSlaveModeTrigger_ITR1()
{
    *_smcr &= ~TIM_SMCR_TS_CLEARMASK;
    *_smcr |= TIM_SMCR_TS_ITR1;
}
void TIMER_With_SlaveMode::SetSlaveModeTrigger_ITR2()
{
    *_smcr &= ~TIM_SMCR_TS_CLEARMASK;
    *_smcr |= TIM_SMCR_TS_ITR2;
}
void TIMER_With_SlaveMode::SetSlaveModeTrigger_ITR3()
{
    *_smcr &= ~TIM_SMCR_TS_CLEARMASK;
    *_smcr |= TIM_SMCR_TS_ITR3;
}
void TIMER_With_SlaveMode::SetSlaveModeTrigger_TI1F_ED()
{
    *_smcr &= ~TIM_SMCR_TS_CLEARMASK;
    *_smcr |= TIM_SMCR_TS_TI1F_ED;
}
void TIMER_With_SlaveMode::SetSlaveModeTrigger_TI1FP1()
{
    *_smcr &= ~TIM_SMCR_TS_CLEARMASK;
    *_smcr |= TIM_SMCR_TS_TI1FP1;
}
void TIMER_With_SlaveMode::SetSlaveModeTrigger_TI1FP2()
{
    *_smcr &= ~TIM_SMCR_TS_CLEARMASK;
    *_smcr |= TIM_SMCR_TS_TI1FP2;
}
void TIMER_With_SlaveMode::SetSlaveModeTrigger_ETRF()
{
    *_smcr &= ~TIM_SMCR_TS_CLEARMASK;
    *_smcr |= TIM_SMCR_TS_ETRF;
}


void TIMER_With_SlaveMode::EnableMasterSlaveMode(bool enable)
{
    if (enable)
        *_smcr |= TIM_SMCR_MSM;
    else
        *_smcr &= ~TIM_SMCR_MSM;
}


void TIMER_Channel::EnableCCInterrupt (bool enable, TIMER_Channel_CCInterrupt_Handler* handler)
{
    if (enable)
    {
        *_dier |= _dier_CCxIE;
        _ccHandler = handler;
    }
    else
        *_dier &= ~_dier_CCxIE;
}

void TIMER_Channel::EnableCCDMARequest (bool enable)
{
    if (enable)
        *_dier |= _dier_CCxDE;
    else
        *_dier &= ~_dier_CCxDE;
}

bool TIMER_Channel::IsCCFlag()
{
    return *_sr & _sr_CCxIF;
}
void TIMER_Channel::ClearCCFlag()
{
    *_sr &= ~_sr_CCxIF;
}

bool TIMER_Channel::IsOCFlag()
{
    return *_sr & _sr_CCxOF;
}
void TIMER_Channel::ClearOCFlag()
{
    *_sr &= ~_sr_CCxOF;
}

void TIMER_Channel::GenerateCCEvent(bool enable)
{
    if (enable)
        *_egr |= _egr_CCxG;
    else
        *_egr &= ~_egr_CCxG;
}


void TIMER_Channel::SetModeOutput()
{
    *_ccmr &= ~(TIM_CCMR1_CC1S_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_CC1S_OUT << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetModeInputDirect()
{
    *_ccmr &= ~(TIM_CCMR1_CC1S_CLEARMASK << (_channelNo-1)%2*8);
        *_ccmr |= (TIM_CCMR1_CC1S_IN_TI1 << (_channelNo-1)%2*8);
}

void TIMER_Channel::SetModeInputInverse()
{
    *_ccmr &= ~(TIM_CCMR1_CC1S_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_CC1S_IN_TI2 << (_channelNo-1)%2*8);
}
void TIMER_Channel::EnableFastMode (bool enable)
{
    if (enable)
        *_ccmr |= (TIM_CCMR1_OC1FE << (_channelNo-1)%2*8);
    else
        *_ccmr &= (~TIM_CCMR1_OC1FE << (_channelNo-1)%2*8);

}
void TIMER_Channel::EnableOCPreload (bool enable)
{
    if (enable)
        *_ccmr |= (TIM_CCMR1_OC1PE << (_channelNo-1)%2*8);
    else
        *_ccmr &= ~(TIM_CCMR1_OC1PE << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetOCMode_Frozen()
{
    *_ccmr &= ~(TIM_CCMR1_OC1M_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_OC1M_FROZEN << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetOCMode_HighOnMatch()
{
    *_ccmr &= ~(TIM_CCMR1_OC1M_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_OC1M_ACTIVE_ON_MATCH << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetOCMode_LowOnMatch()
{
    *_ccmr &= ~(TIM_CCMR1_OC1M_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_OC1M_INACTIVE_ON_MATCH << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetOCMode_ToggleOnMatch()
{
    *_ccmr &= ~(TIM_CCMR1_OC1M_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_OC1M_TOGGLE << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetOCMode_ForceLow()
{
    *_ccmr &= ~(TIM_CCMR1_OC1M_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_OC1M_FORCE_LOW << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetOCMode_ForceHigh()
{
    *_ccmr &= ~(TIM_CCMR1_OC1M_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_OC1M_FORCE_HIGH << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetOCMode_PWM1()
{
    *_ccmr &= ~(TIM_CCMR1_OC1M_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_OC1M_PWM1 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetOCMode_PWM2()
{
    *_ccmr &= ~(TIM_CCMR1_OC1M_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_OC1M_PWM2 << (_channelNo-1)%2*8);
}

void TIMER_Channel::EnableClearOnETRF (bool enable)
{
    if (enable)
        *_ccmr |= (TIM_CCMR1_OC1CE << (_channelNo-1)%2*8);
    else
        *_ccmr &= (~TIM_CCMR1_OC1CE << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICPrescaler_None()
{
    *_ccmr &= ~(TIM_CCMR1_IC1PSC_CLEARMASK << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICPrescaler_2()
{
    *_ccmr &= ~(TIM_CCMR1_IC1PSC_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1PSC_DIV2 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICPrescaler_4()
{
    *_ccmr &= ~(TIM_CCMR1_IC1PSC_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1PSC_DIV4 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICPrescaler_8()
{
    *_ccmr &= ~(TIM_CCMR1_IC1PSC_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1PSC_DIV8 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICFilter_None()
{
    *_ccmr &= ~(TIM_CCMR1_IC1F_CLEARMASK << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICFilter_CK_N2()
{
    *_ccmr &= ~(TIM_CCMR1_IC1F_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1F_FCK_INT_2 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICFilter_CK_N4()
{
    *_ccmr &= ~(TIM_CCMR1_IC1F_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1F_FCK_INT_4 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICFilter_CK_N8()
{
    *_ccmr &= ~(TIM_CCMR1_IC1F_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1F_FCK_INT_8 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICFilter_DTS_DIV2_N6()
{
    *_ccmr &= ~(TIM_CCMR1_IC1F_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1F_FDTS_2_6 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICFilter_DTS_DIV2_N8()
{
    *_ccmr &= ~(TIM_CCMR1_IC1F_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1F_FDTS_2_8 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICFilter_DTS_DIV4_N6()
{
    *_ccmr &= ~(TIM_CCMR1_IC1F_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1F_FDTS_4_6 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICFilter_DTS_DIV4_N8()
{
    *_ccmr &= ~(TIM_CCMR1_IC1F_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1F_FDTS_4_8 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICFilter_DTS_DIV8_N6()
{
    *_ccmr &= ~(TIM_CCMR1_IC1F_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1F_FDTS_8_6 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICFilter_DTS_DIV8_N8()
{
    *_ccmr &= ~(TIM_CCMR1_IC1F_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1F_FDTS_8_8 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICFilter_DTS_DIV16_N5()
{
    *_ccmr &= ~(TIM_CCMR1_IC1F_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1F_FDTS_16_5 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICFilter_DTS_DIV16_N6()
{
    *_ccmr &= ~(TIM_CCMR1_IC1F_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1F_FDTS_16_6 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICFilter_DTS_DIV16_N8()
{
    *_ccmr &= ~(TIM_CCMR1_IC1F_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1F_FDTS_16_8 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICFilter_DTS_DIV32_N5()
{
    *_ccmr &= ~(TIM_CCMR1_IC1F_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1F_FDTS_32_5 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICFilter_DTS_DIV32_N6()
{
    *_ccmr &= ~(TIM_CCMR1_IC1F_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1F_FDTS_32_6 << (_channelNo-1)%2*8);
}
void TIMER_Channel::SetICFilter_DTS_DIV32_N8()
{
    *_ccmr &= ~(TIM_CCMR1_IC1F_CLEARMASK << (_channelNo-1)%2*8);
    *_ccmr |= (TIM_CCMR1_IC1F_FDTS_32_8 << (_channelNo-1)%2*8);
}

void TIMER_Channel::EnableChannel (bool enable)
{
    if (enable)
        *_ccer |= (TIM_CCER_CC1E<<(_channelNo-1)*4);
    else
        *_ccer &= ~(TIM_CCER_CC1E<<(_channelNo-1)*4);

}
void TIMER_Channel::SetCCPolarityLow (bool set)
{
    if (set)
        *_ccer |= (TIM_CCER_CC1P<<(_channelNo-1)*4);
    else
        *_ccer &= ~(TIM_CCER_CC1P<<(_channelNo-1)*4);

}

void TIMER_Channel::SetCCR (uint16_t val)
{
    *_ccr = val;
}

uint16_t TIMER_Channel::GetCCR()
{
    return *_ccr;
}

TIMER::TIMER (uint32_t timx_base_addr, IRQn_Type irqNo, volatile uint32_t* rccEnableReg,
              volatile uint32_t* rccResetReg, uint32_t rccBit, bool isAPB1)
: Peripheral (rccEnableReg, rccResetReg, rccBit)
{
    _globalInterrupt = irqNo;
    _isAPB1 = isAPB1;

    _cr1 = (volatile uint32_t*)(timx_base_addr + TIM_CR1_OFFSET);
    //_cr2 = (volatile uint32_t*)(timx_base_addr + TIM_CR2_OFFSET);
    _dier = (volatile uint32_t*)(timx_base_addr + TIM_DIER_OFFSET);
    _sr = (volatile uint32_t*)(timx_base_addr + TIM_SR_OFFSET);
    _egr = (volatile uint32_t*)(timx_base_addr + TIM_EGR_OFFSET);
    _cnt = (volatile uint32_t*)(timx_base_addr + TIM_CNT_OFFSET);
    _psc = (volatile uint32_t*)(timx_base_addr + TIM_PSC_OFFSET);
    _arr = (volatile uint32_t*)(timx_base_addr + TIM_ARR_OFFSET);
    _irqHandlerCount = 0;
    _is32_bit = false;
}

TIMER_With_Channels::TIMER_With_Channels(uint32_t timx_base_addr, uint8_t nchannels, IRQn_Type irqNo,
        volatile uint32_t* rccEnableReg,  volatile uint32_t* rccResetReg, uint32_t rccBit, bool isAPB1) :
TIMER (timx_base_addr, irqNo, rccEnableReg, rccResetReg, rccBit, isAPB1)
{
    _nchannels = nchannels;


    for (uint8_t ch = 0; ch < nchannels; ++ch)
    {
        _channels[ch]._channelNo = ch + 1;
        _channels[ch]._timer = this;
        _channels[ch]._dier = (volatile uint32_t*)(timx_base_addr + TIM_DIER_OFFSET);
        _channels[ch]._sr = (volatile uint32_t*)(timx_base_addr + TIM_SR_OFFSET);
        _channels[ch]._egr = (volatile uint32_t*)(timx_base_addr + TIM_EGR_OFFSET);
        _channels[ch]._bdtr = 0;

        if (ch < 2)
        {
            _channels[ch]._ccmr = (volatile uint32_t*)(timx_base_addr + TIM_CCMR1_OFFSET);
        }
        else
        {
            _channels[ch]._ccmr = (volatile uint32_t*)(timx_base_addr + TIM_CCMR2_OFFSET);
        }

        _channels[ch]._ccer = (volatile uint32_t*)(timx_base_addr + TIM_CCER_OFFSET);

        switch (ch)
        {
        case 0:
            _channels[ch]._dier_CCxIE = TIM_DIER_CC1IE;
            _channels[ch]._dier_CCxDE = TIM_DIER_CC1DE;
            _channels[ch]._sr_CCxIF = TIM_SR_CC1IF;
            _channels[ch]._sr_CCxOF = TIM_SR_CC1OF;
            _channels[ch]._egr_CCxG = TIM_EGR_CC1G;
            _channels[ch]._ccer_CCxE = TIM_CCER_CC1E;
            _channels[ch]._ccer_CCxP = TIM_CCER_CC1P;
            _channels[ch]._ccr = (volatile uint32_t*)(timx_base_addr + TIM_CCR1_OFFSET);
            break;
        case 1:
            _channels[ch]._dier_CCxIE = TIM_DIER_CC2IE;
            _channels[ch]._dier_CCxDE = TIM_DIER_CC2DE;
            _channels[ch]._sr_CCxIF = TIM_SR_CC2IF;
            _channels[ch]._sr_CCxOF = TIM_SR_CC2OF;
            _channels[ch]._egr_CCxG = TIM_EGR_CC2G;
            _channels[ch]._ccer_CCxE = TIM_CCER_CC2E;
            _channels[ch]._ccer_CCxP = TIM_CCER_CC2P;
            _channels[ch]._ccr = (volatile uint32_t*)(timx_base_addr + TIM_CCR2_OFFSET);
            break;
        case 2:
            _channels[ch]._dier_CCxIE = TIM_DIER_CC3IE;
            _channels[ch]._dier_CCxDE = TIM_DIER_CC3DE;
            _channels[ch]._sr_CCxIF = TIM_SR_CC3IF;
            _channels[ch]._sr_CCxOF = TIM_SR_CC3OF;
            _channels[ch]._egr_CCxG = TIM_EGR_CC3G;
            _channels[ch]._ccer_CCxE = TIM_CCER_CC3E;
            _channels[ch]._ccer_CCxP = TIM_CCER_CC3P;
            _channels[ch]._ccr = (volatile uint32_t*)(timx_base_addr + TIM_CCR3_OFFSET);
            break;
        case 3:
            _channels[ch]._dier_CCxIE = TIM_DIER_CC3IE;
            _channels[ch]._dier_CCxDE = TIM_DIER_CC3DE;
            _channels[ch]._sr_CCxIF = TIM_SR_CC4IF;
            _channels[ch]._sr_CCxOF = TIM_SR_CC4OF;
            _channels[ch]._egr_CCxG = TIM_EGR_CC4G;
            _channels[ch]._ccer_CCxE = TIM_CCER_CC4E;
            _channels[ch]._ccer_CCxP = TIM_CCER_CC4P;
            _channels[ch]._ccr = (volatile uint32_t*)(timx_base_addr + TIM_CCR4_OFFSET);
            break;

        };

    }
}

TIMER_Channel*  TIMER_With_Channels::GetChannel(int channelNo)
{
    if (channelNo>0 && channelNo <= _nchannels)
    {
        return &_channels[channelNo-1];
    }
    else
        return 0;
}

AdvancedTimer::AdvancedTimer(uint32_t timx_base_addr, IRQn_Type updateIrqNo, IRQn_Type ccIrqNo,
    volatile uint32_t* rccEnableReg, volatile uint32_t* rccResetReg, uint32_t rccBit):
TIMER_With_Channels(timx_base_addr, 4, updateIrqNo, rccEnableReg, rccResetReg, rccBit,  false),
TIMER_With_DMAControl(timx_base_addr),
TIMER_With_OnePulseMode(timx_base_addr),
TIMER_With_UpDownCounter(timx_base_addr),
TIMER_With_MMS(timx_base_addr),
TIMER_With_SlaveMode(timx_base_addr),
TIMER_With_BDTR_RCR(timx_base_addr)
{
    _ccIrqNo = ccIrqNo;
    for (uint8_t ch = 0; ch < 4; ++ch)
    {
        _channels[ch]._bdtr = (volatile uint32_t*)(timx_base_addr + TIM_BDTR_OFFSET);
    }
}



void TIMER::EnableCounter (bool enable)
{
    if (enable)
        *_cr1 |= TIM_CR1_CEN;
    else
        *_cr1 &= ~TIM_CR1_CEN;

}


void TIMER::EnableUpdateEvent (bool enable)
{
    if (enable)
        *_cr1 |= TIM_CR1_UDIS;
    else
        *_cr1 &= ~TIM_CR1_UDIS;
}

void TIMER::SetUpdateRequestSource (bool isAny)
{
    if (isAny)
        *_cr1 &= ~TIM_CR1_URS;
    else
        *_cr1 |= TIM_CR1_URS;
}

void TIMER::EnableAutoPreload (bool enable)
{
    if (enable)
        *_cr1 |= TIM_CR1_ARPE;
    else
        *_cr1 &= ~TIM_CR1_ARPE;

}

void TIMER::SetClockDivision_TCK()
{
    *_cr1 &= ~TIM_CR1_CKD_CLEARMASK;
    *_cr1 |= TIM_CR1_CKD_CKINT;
}
void TIMER::SetClockDivision_TCKx2()
{
    *_cr1 &= ~TIM_CR1_CKD_CLEARMASK;
    *_cr1 |= TIM_CR1_CKD_CKINT2;
}
void TIMER::SetClockDivision_TCKx4()
{
    *_cr1 &= ~TIM_CR1_CKD_CLEARMASK;
    *_cr1 |= TIM_CR1_CKD_CKINT4;
}

void TIMER::EnableUpdateInterrupt (bool enable)
{
    if (enable)
    {
        *_dier |= TIM_DIER_UIE;
    }
    else
        *_dier &= ~TIM_DIER_UIE;

}
void TIMER::EnableNVICInterrupt(bool enable)
{
    if (enable)
        NVIC_SetEnable(_globalInterrupt);
    else
        NVIC_ClearEnable(_globalInterrupt);
}

void TIMER::EnableTriggerInterrupt (bool enable)
{
    if (enable)
        *_dier |= TIM_DIER_TIE;
    else
        *_dier &= ~TIM_DIER_TIE;

}

void TIMER::AddInterruptHandler (TIMER_Interrupt_Handler* handler)
{
    if (_irqHandlerCount < MAX_UPDATE_HANDLERS)
        _irqHandlers[_irqHandlerCount++] = handler;
}


void TIMER::SetCounterValue (uint32_t val)
{
    *_cnt = (_is32_bit) ? val : (val & 0xffff);
}

void TIMER::SetPrescalerValue (uint16_t val)
{
    *_psc = val;
}

void TIMER::SetAutoReloadValue (uint32_t val)
{
    *_arr = (_is32_bit) ? val : (val & 0xffff);
}



bool TIMER::IsUIF()
{
    return *_sr & TIM_SR_UIF;
}

void TIMER::ClearUIF()
{
    *_sr &= ~TIM_SR_UIF;
}

bool TIMER_With_Channels::IsTIF()
{
    return *_sr & TIM_SR_TIF;
}

void TIMER_With_Channels::ClearTIF()
{
    *_sr &= ~TIM_SR_TIF;
}

void TIMER::GenerateRegisterUpdate(bool enable)
{
    if (enable)
        *_egr |= TIM_EGR_UG;
    else
        *_egr &= ~TIM_EGR_UG;

}



void TIMER::CalculateTimerValues (uint32_t us, uint32_t* count, uint16_t* presc)
{
    uint32_t timClk = RCC_GetTIMx_CLK(_isAPB1);
    uint64_t count64 = (uint64_t)timClk  * (uint64_t)us / 1000000llu;

    uint32_t max = (_is32_bit) ? 0xffffffff : 0xffff;

    if (count64 == 0)
    {
        count64 = 1;
    }

    *presc = 1;

    while (count64 >= max)
    {
        count64 /= 2;
        (*presc) *= 2;
    }

    *count = (uint32_t)count64;

}

void TIMER::CalculateTimerValues2 (uint32_t us, uint16_t* count, uint16_t* presc)
{
    uint32_t timClk = RCC_GetTIMx_CLK(_isAPB1);
//    uint32_t count32 = (uint32_t)((float) timClk / 1000000.f * (float)us);
    uint64_t count32 = (uint64_t)timClk  * (uint64_t)us / 1000000llu;

    uint32_t max = (_is32_bit) ? 0xffffffff : 0xffff;

    if (count32 == 0)
    {
        count32 = 1;
    }

    *presc = 1;

    while (count32 >= max)
    {
        count32 /= 2;
        (*presc) *= 2;
    }

    *count = (uint16_t)count32;

}



void TIMER::SetUpdatePeriod_us (uint32_t us)
{
    uint32_t count;
    uint16_t presc;

    CalculateTimerValues (us, &count, &presc);

    SetAutoReloadValue(count);
    SetPrescalerValue(presc-1);
}


bool TIMER_With_Channels::IsCenterAlignedModeEnabled()
{
    return (*_cr1 & TIM_CR1_CMS_CLEARMASK);
}

void TIMER_Channel::SetupPWM1(uint32_t period_us, uint32_t duty_us)
{
    SetupPWM (period_us, duty_us, true);
}
void TIMER_Channel::SetupPWM2(uint32_t period_us, uint32_t duty_us)
{
    SetupPWM (period_us, duty_us, false);
}



void TIMER_Channel::UpdatePWMDuty(uint32_t duty_us) 
{
    uint32_t duty_count;
    uint16_t presc = 1;

    if (_timer->IsCenterAlignedModeEnabled())
    {
        duty_us /= 2;
    }

    _timer->CalculateTimerValues (duty_us, &duty_count, &presc);
    SetCCR((uint16_t)duty_count);
}

void TIMER_Channel::SetupPWM(uint32_t period_us, uint32_t duty_us, bool isPWM1)
{
    uint16_t period_count;
    uint16_t presc = 1;

    if (_timer->IsCenterAlignedModeEnabled())
    {
        period_us /= 2;
    }

    _timer->CalculateTimerValues2 (period_us, &period_count, &presc);

    uint16_t duty_count = (uint16_t)((float)period_count * ((float)duty_us / (float)period_us));
    _timer->SetAutoReloadValue(period_count);
    _timer->SetPrescalerValue(presc-1);

    if (isPWM1)
    {
        SetOCMode_PWM1();
    }
    else
    {
        SetOCMode_PWM2();
    }

    if (_bdtr != 0)
    {
    	*_bdtr |= TIM_BDTR_MOE;
    }


    SetCCR(duty_count);
    EnableOCPreload(true);
    _timer->EnableAutoPreload(true);
    _timer->GenerateRegisterUpdate(true);
}

void TIMER_Channel::CaptureInputPWM (uint32_t max_period_us, PWM_Capture_Handler* handler)
{
    uint32_t period_count;
    uint16_t presc = 1;

#ifdef __GNUC__
    TIMER_With_SlaveMode* twsm =  (TIMER_With_SlaveMode*)(_timer);
#else
    TIMER_With_SlaveMode* twsm =  dynamic_cast<TIMER_With_SlaveMode*>(_timer);
#endif
    if (twsm == 0)
    {
        return;
    }
    if (_channelNo != 1)
    {
        return;
    }
    
    _pwmCaptureHandler = handler;

    _timer->CalculateTimerValues (max_period_us, &period_count, &presc);
    _timer->SetPrescalerValue(presc-1);
    _timer->SetCounterValue(0);

    _pwmCaptureHandler = handler;
    SetModeInputDirect();
    SetCCPolarityLow(false);
    EnableCCInterrupt(true);

    TIMER_Channel* ch2 = _timer->GetChannel(2);
    ch2->SetModeInputInverse();
    ch2->SetCCPolarityLow(true);

    twsm->SetSlaveModeTrigger_TI1FP1();
    twsm->SetSlaveMode_Reset();

    *_ccer |= (TIM_CCER_CC1E | TIM_CCER_CC2E);

    _timer->EnableNVICInterrupt(true);
    _timer->EnableCounter(true);

}



#endif
