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

#include "adc.h"

#ifdef USE_ADC

#include "rcc_cpp.h"
#include "nvic.h"

class ADC_IRQ_Handler;

class ADC: public Peripheral
{

private:
    volatile uint32_t* _pADC_CR1;
    volatile uint32_t* _pADC_CR2;
    volatile uint32_t* _pADC_SR;
    volatile uint32_t* _pADC_DR;
    volatile uint32_t* _pADC_SMPR1;
    volatile uint32_t* _pADC_SMPR2;
    volatile uint32_t* _pADC_HTR;
    volatile uint32_t* _pADC_LTR;
    volatile uint32_t* _pADC_SQR1;
    volatile uint32_t* _pADC_SQR2;
    volatile uint32_t* _pADC_SQR3;
    volatile uint32_t* _pADC_JDR1;
    volatile uint32_t* _pADC_JDR2;
    volatile uint32_t* _pADC_JDR3;
    volatile uint32_t* _pADC_JDR4;
    volatile uint32_t* _pADC_JSQR;

    IRQn_Type _irqNo;
    ADC_IRQ_Handler* _interruptHandler;
    ADC_IRQ_Handler* _jInterruptHandler;
    ADC_IRQ_Handler* _watchdogHandler;
    ADC_IRQ_Handler* _jWatchdogHandler;
    bool _emptySequence;
    bool _emptyJSequence;

    bool _initialized;

protected:
    ADC(volatile uint32_t* pADC_CR1, volatile uint32_t* pADC_CR2,
            volatile uint32_t* pADC_SR, volatile uint32_t* pADC_DR,
            volatile uint32_t* pADC_SMPR1, volatile uint32_t* pADC_SMPR2,
            volatile uint32_t* pADC_HTR, volatile uint32_t* pADC_LTR,
            volatile uint32_t* pADC_SQR1, volatile uint32_t* pADC_SQR2,
            volatile uint32_t* pADC_SQR3, volatile uint32_t* pADC_JDR1,
            volatile uint32_t* pADC_JDR2, volatile uint32_t* pADC_JDR3,
            volatile uint32_t* pADC_JDR4, volatile uint32_t* pADC_JSQR,
            IRQn_Type irqNo)
    {
        _pADC_CR1 = pADC_CR1;
        _pADC_CR2 = pADC_CR2;
        _pADC_SR = pADC_SR;
        _pADC_DR = pADC_DR;
        _pADC_SMPR1 = pADC_SMPR1;
        _pADC_SMPR2 = pADC_SMPR2;
        _pADC_HTR = pADC_HTR;
        _pADC_LTR = pADC_LTR;
        _pADC_SQR1 = pADC_SQR1;
        _pADC_SQR2 = pADC_SQR2;
        _pADC_SQR3 = pADC_SQR3;
        _pADC_JDR1 = pADC_JDR1;
        _pADC_JDR2 = pADC_JDR2;
        _pADC_JDR3 = pADC_JDR3;
        _pADC_JDR4 = pADC_JDR4;
        _pADC_JSQR = pADC_JSQR;
        _irqNo = irqNo;
        _initialized = false;
        _interruptHandler = 0;
        _jInterruptHandler = 0;
        _watchdogHandler = 0;
        _jWatchdogHandler = 0;
        _emptySequence = true;
        _emptyJSequence = true;

    }

    void SetChannelSampleTime(ADC_CHANNEL channel, ADC_SAMPLE_TIME sampleTime);
    void Calibrate();
    void _EnableInterrupt(uint16_t intMask, bool enable);
    void _EnableWatchdog(float minV, float maxV,
            ADC_IRQ_Handler* watchdogHandler, ADC_CHANNEL channel,
            bool injected);
public:

    void Enable(bool enable);

    uint32_t SingleConversion();
    void StartConversion(bool continous);
    void AddConversion(ADC_CHANNEL channel, ADC_SAMPLE_TIME sampleTime);
    void AddJConversion(ADC_CHANNEL channel, ADC_SAMPLE_TIME sampleTime);
    void EnableInterrupt(bool enable);
    void EnableJInterrupt(bool enable);
    void SetAutoInjection(bool on);

    uint32_t GetData()
    {
        return *_pADC_DR;
    }
    uint32_t GetJData1()
    {
        return *_pADC_JDR1;
    }
    uint32_t GetJData2()
    {
        return *_pADC_JDR2;
    }
    uint32_t GetJData3()
    {
        return *_pADC_JDR3;
    }
    uint32_t GetJData4()
    {
        return *_pADC_JDR4;
    }

    void HandleInterrupt();
    void HandleJInterrupt();
    void SetInterruptHandler(ADC_IRQ_Handler* interruptHandler);
    void SetJInterruptHandler(ADC_IRQ_Handler* interruptHandler);
    void SetLeftAlignment();
    void SetRightAlignment();
    void SetScanMode();
    void EnableWatchdog(float minV, float maxV,
            ADC_IRQ_Handler* watchdogHandler, ADC_CHANNEL channel = ADC_ALL);
    void EnableJWatchdog(float minV, float maxV,
            ADC_IRQ_Handler* jWatchdogHandler, ADC_CHANNEL channel = ADC_ALL);
    void SetWatchdogHandler(ADC_IRQ_Handler* watchdogHandler);
    void SetJWatchdogHandler(ADC_IRQ_Handler* jWatchdogHandler);
    void HandleWatchdogInterrupt();
    void HandleJWatchdogInterrupt();

};

class ADC1: public ADC
{
public:

    static ADC1* GetInstance()
    {
        static ADC1 instance;
        return &instance;
    }

    virtual void EnablePeripheralClock(bool enable);

private:

    ADC1() :
            ADC(&ADC1_CR1, &ADC1_CR2, &ADC1_SR, &ADC1_DR, &ADC1_SMPR1,
                    &ADC1_SMPR2, &ADC1_HTR, &ADC1_LTR, &ADC1_SQR1, &ADC1_SQR2,
                    &ADC1_SQR3, &ADC1_JDR1, &ADC1_JDR2, &ADC1_JDR3, &ADC1_JDR4,
                    &ADC1_JSQR,
#if defined (VALUE_LINE)
                    IRQn_ADC1)
#else
    IRQn_ADC1_2)
#endif

    {
    }

    ADC1(ADC1 const&);
    void operator=(ADC1 const&);

};

#if !defined (VALUE_LINE)
class ADC2 : public ADC
{
public:
    static ADC2* GetInstance()
    {
        static ADC2 instance;
        return &instance;
    }

    virtual void EnablePeripheralClock(bool enable);

private:

    ADC2() :
    ADC (&ADC2_CR1, &ADC2_CR2, &ADC2_SR, &ADC2_DR, &ADC2_SMPR1, &ADC2_SMPR2, &ADC2_HTR, &ADC2_LTR,
            &ADC2_SQR1, &ADC2_SQR2, &ADC2_SQR3, &ADC2_JDR1, &ADC2_JDR2, &ADC2_JDR3, &ADC2_JDR4, &ADC2_JSQR,
            IRQn_ADC1_2)
    {
    }
    ADC2(ADC2 const&);
    void operator=(ADC2 const&);

};

#if defined (STM32F10X_HD) || defined (STM32F10X_XL)

class ADC3 : public ADC
{
public:
    static ADC3* GetInstance()
    {
        static ADC3 instance;
        return &instance;
    }

    virtual void EnablePeripheralClock(bool enable);

private:
    ADC3() :
    ADC (&ADC3_CR1, &ADC3_CR2, &ADC3_SR, &ADC3_DR, &ADC3_SMPR1, &ADC3_SMPR2, &ADC3_HTR, &ADC3_LTR,
            &ADC3_SQR1, &ADC3_SQR2, &ADC3_SQR3, &ADC3_JDR1, &ADC3_JDR2, &ADC3_JDR3, &ADC3_JDR4, &ADC3_JSQR,
            IRQn_ADC3)
    {
    }
    ADC3(ADC3 const&);
    void operator=(ADC3 const&);

};

#endif

#endif

class ADC_IRQ_Handler
{
public:
    virtual void Handle(ADC* adc) = 0;
};


#endif
