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


#ifndef _EXTI_H
#define _EXTI_H

#include "common.h"


typedef enum
{
    EXTI_LINE0 = 0,
    EXTI_LINE1 = 1,
    EXTI_LINE2 = 2,
    EXTI_LINE3 = 3,
    EXTI_LINE4 = 4,
    EXTI_LINE5 = 5,
    EXTI_LINE6 = 6,
    EXTI_LINE7 = 7,
    EXTI_LINE8 = 8,
    EXTI_LINE9 = 9,
    EXTI_LINE10 = 10,
    EXTI_LINE11 = 11,
    EXTI_LINE12 = 12,
    EXTI_LINE13 = 13,
    EXTI_LINE14 = 14,
    EXTI_LINE15 = 15,
    EXTI_LINE16 = 16,
    EXTI_LINE17 = 17,
    EXTI_LINE18 = 18,
    EXTI_LINE19 = 19,
#if defined (STM32F2) || defined (STM32F4) || defined (STM32L0)
    EXTI_LINE20 = 20,
    EXTI_LINE21 = 21,
    EXTI_LINE22 = 22,
#if defined (STM32L0)
    EXTI_LINE23 = 23,
    EXTI_LINE24 = 24,
    EXTI_LINE25 = 25,
    EXTI_LINE26 = 26,
    EXTI_LINE28 = 28,
    EXTI_LINE29 = 29,

#endif

#endif

} EXTI_LINE;



#ifdef USE_EXTI


#include "nvic.h"

#if defined (STM32F1) || defined (STM32L0)
#define EXTI_BASE 0x40010400  //APB2
#elif defined (STM32F2) || defined (STM32F4)
#define EXTI_BASE 0x40013C00  //APB2
#else 
#error "STM32 target device not defined"
#endif


#define EXTI_IMR   (*(volatile uint32_t*)(EXTI_BASE))         //interrupt mask
#define EXTI_EMR   (*(volatile uint32_t*)(EXTI_BASE + 0x4))   //event mask
#define EXTI_RTSR  (*(volatile uint32_t*)(EXTI_BASE + 0x8))   //rising  edge
#define EXTI_FTSR  (*(volatile uint32_t*)(EXTI_BASE + 0xc))   //falling edge
#define EXTI_SWIER (*(volatile uint32_t*)(EXTI_BASE + 0x10))  //software int event
#define EXTI_PR    (*(volatile uint32_t*)(EXTI_BASE + 0x14))  //pending

class EXTI;
class EXTI_IRQ_Handler
{
public:
    virtual void HandleInterrupt(EXTI* exti) = 0;
};

class EXTI
{
private:
    EXTI_LINE _line;
    IRQn_Type _irqnNo;
    EXTI_IRQ_Handler* _irqHandler;

    void Enable(bool enable, volatile uint32_t* edgeReg,
            volatile uint32_t* eventOrIntReg);

protected:
    EXTI(EXTI_LINE line, IRQn_Type irqnNo)
    {
        _line = line;
        _irqnNo = irqnNo;
        _irqHandler = 0;
    }

public:

    void EnableInterruptRisingEdge(bool enable);
    void EnableInterruptFallingEdge(bool enable);
    void EnableEventRisingEdge(bool enable);
    void EnableEventFallingEdge(bool enable);
    void GenerateSWI(bool enable);

    bool IsPending();
    void ClearPending();

    EXTI_LINE getEXTILine()
    {
        return _line;
    }

    void SetIrqHandler(EXTI_IRQ_Handler* handler)
    {
        _irqHandler = handler;
    }

    void HandleInterrupt();
};

class EXTI0: public EXTI
{
public:

    static EXTI0* GetInstance()
    {
        static EXTI0 instance;
        return &instance;
    }

private:
    EXTI0() :
            EXTI(EXTI_LINE0, IRQn_EXTI0)
    {
    }

    EXTI0(EXTI0 const&);
    void operator=(EXTI0 const&);
};

class EXTI1: public EXTI
{
public:

    static EXTI1* GetInstance()
    {
        static EXTI1 instance;
        return &instance;
    }

private:
    EXTI1() :
            EXTI(EXTI_LINE1, IRQn_EXTI1)
    {
    }

    EXTI1(EXTI1 const&);
    void operator=(EXTI1 const&);
};

class EXTI2: public EXTI
{
public:

    static EXTI2* GetInstance()
    {
        static EXTI2 instance;
        return &instance;
    }

private:
    EXTI2() :
            EXTI(EXTI_LINE2, IRQn_EXTI2)
    {
    }

    EXTI2(EXTI2 const&);
    void operator=(EXTI2 const&);
};

class EXTI3: public EXTI
{
public:

    static EXTI3* GetInstance()
    {
        static EXTI3 instance;
        return &instance;
    }

private:
    EXTI3() :
            EXTI(EXTI_LINE3, IRQn_EXTI3)
    {
    }

    EXTI3(EXTI3 const&);
    void operator=(EXTI3 const&);
};

class EXTI4: public EXTI
{
public:

    static EXTI4* GetInstance()
    {
        static EXTI4 instance;
        return &instance;
    }

private:
    EXTI4() :
            EXTI(EXTI_LINE4, IRQn_EXTI4)
    {
    }

    EXTI4(EXTI4 const&);
    void operator=(EXTI4 const&);
};

class EXTI5: public EXTI
{
public:

    static EXTI5* GetInstance()
    {
        static EXTI5 instance;
        return &instance;
    }

private:
    EXTI5() :
            EXTI(EXTI_LINE5, IRQn_EXTI9_5)
    {
    }

    EXTI5(EXTI5 const&);
    void operator=(EXTI5 const&);
};

class EXTI6: public EXTI
{
public:

    static EXTI6* GetInstance()
    {
        static EXTI6 instance;
        return &instance;
    }

private:
    EXTI6() :
            EXTI(EXTI_LINE6, IRQn_EXTI9_5)
    {
    }

    EXTI6(EXTI6 const&);
    void operator=(EXTI6 const&);
};

class EXTI7: public EXTI
{
public:

    static EXTI7* GetInstance()
    {
        static EXTI7 instance;
        return &instance;
    }

private:
    EXTI7() :
            EXTI(EXTI_LINE7, IRQn_EXTI9_5)
    {
    }

    EXTI7(EXTI7 const&);
    void operator=(EXTI7 const&);
};

class EXTI8: public EXTI
{
public:

    static EXTI8* GetInstance()
    {
        static EXTI8 instance;
        return &instance;
    }

private:
    EXTI8() :
            EXTI(EXTI_LINE8, IRQn_EXTI9_5)
    {
    }

    EXTI8(EXTI8 const&);
    void operator=(EXTI8 const&);
};

class EXTI9: public EXTI
{
public:

    static EXTI9* GetInstance()
    {
        static EXTI9 instance;
        return &instance;
    }

private:
    EXTI9() :
            EXTI(EXTI_LINE9, IRQn_EXTI9_5)
    {
    }

    EXTI9(EXTI9 const&);
    void operator=(EXTI9 const&);
};

class EXTI10: public EXTI
{
public:

    static EXTI10* GetInstance()
    {
        static EXTI10 instance;
        return &instance;
    }

private:
    EXTI10() :
            EXTI(EXTI_LINE10, IRQn_EXTI15_10)
    {
    }

    EXTI10(EXTI10 const&);
    void operator=(EXTI10 const&);
};

class EXTI11: public EXTI
{
public:

    static EXTI11* GetInstance()
    {
        static EXTI11 instance;
        return &instance;
    }

private:
    EXTI11() :
            EXTI(EXTI_LINE11, IRQn_EXTI15_10)
    {
    }

    EXTI11(EXTI11 const&);
    void operator=(EXTI11 const&);
};

class EXTI12: public EXTI
{
public:

    static EXTI12* GetInstance()
    {
        static EXTI12 instance;
        return &instance;
    }

private:
    EXTI12() :
            EXTI(EXTI_LINE12, IRQn_EXTI15_10)
    {
    }

    EXTI12(EXTI12 const&);
    void operator=(EXTI12 const&);
};

class EXTI13: public EXTI
{
public:

    static EXTI13* GetInstance()
    {
        static EXTI13 instance;
        return &instance;
    }

private:
    EXTI13() :
            EXTI(EXTI_LINE13, IRQn_EXTI15_10)
    {
    }

    EXTI13(EXTI13 const&);
    void operator=(EXTI13 const&);
};

class EXTI14: public EXTI
{
public:

    static EXTI14* GetInstance()
    {
        static EXTI14 instance;
        return &instance;
    }

private:
    EXTI14() :
            EXTI(EXTI_LINE14, IRQn_EXTI15_10)
    {
    }

    EXTI14(EXTI14 const&);
    void operator=(EXTI14 const&);
};

class EXTI15: public EXTI
{
public:

    static EXTI15* GetInstance()
    {
        static EXTI15 instance;
        return &instance;
    }

private:
    EXTI15() :
            EXTI(EXTI_LINE15, IRQn_EXTI15_10)
    {
    }

    EXTI15(EXTI15 const&);
    void operator=(EXTI15 const&);
};

class EXTI16: public EXTI
{
public:

    static EXTI16* GetInstance()
    {
        static EXTI16 instance;
        return &instance;
    }

private:
    EXTI16() :
            EXTI(EXTI_LINE16, IRQn_NONE)
    {
    }

    EXTI16(EXTI16 const&);
    void operator=(EXTI16 const&);
};

class EXTI17: public EXTI
{
public:

    static EXTI17* GetInstance()
    {
        static EXTI17 instance;
        return &instance;
    }

private:
    EXTI17() :
            EXTI(EXTI_LINE17, IRQn_NONE)
    {
    }

    EXTI17(EXTI17 const&);
    void operator=(EXTI17 const&);
};

class EXTI18: public EXTI
{
public:

    static EXTI18* GetInstance()
    {
        static EXTI18 instance;
        return &instance;
    }

private:
    EXTI18() :
            EXTI(EXTI_LINE18, IRQn_NONE)
    {
    }

    EXTI18(EXTI18 const&);
    void operator=(EXTI18 const&);
};

class EXTI19: public EXTI
{
public:

    static EXTI19* GetInstance()
    {
        static EXTI19 instance;
        return &instance;
    }

private:
    EXTI19() :
            EXTI(EXTI_LINE19, IRQn_NONE)
    {
    }

    EXTI19(EXTI19 const&);
    void operator=(EXTI19 const&);
};

void EnableEXTI(bool enable, EXTI_LINE line);

#endif

#endif
