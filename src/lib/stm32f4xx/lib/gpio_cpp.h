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



#ifndef GPIO_CPP_H
#define GPIO_CPP_H

#include "gpio.h"
#include "rcc.h"
#include "peripheral.h"

class GPIO_PORT;

class GPIO_PIN
{
friend class GPIO_PORT;
private:
    GPIO_PORT* gpioPort;
    GPIO_PIN_N pin;

    GPIO_PIN()
    {
        gpioPort = 0;
        pin = GPIO_PIN0;
    }
    void _init (GPIO_PORT* gpioPort, GPIO_PIN_N pin)
    {
        this->gpioPort = gpioPort;
        this->pin = pin;
    }
public:

    GPIO_PORT* GetPort() { return gpioPort; }

    void SetupGPIO_InFloat ();
    void SetupGPIO_InAnalog ();
    void SetupGPIO_InPullUp ();
    void SetupGPIO_InPullDown ();
    void SetupGPIO_OutPP ();
    void SetupGPIO_OutOD ();
    void SetupGPIO_OutAltOD ();
    void SetupGPIO_OutAltPP ();

    void SetSpeedLow ();
    void SetSpeedMedium ();
    void SetSpeedHigh ();

    void Set ();
    void Toggle ();
    void Reset ();
    bool IsSet ();
    void PullUp();
    void PullDown();
    void SetAF(GPIO_AF afno);

};


class GPIO_PORT : public Peripheral
{
private:

  GPIO_PIN _pins[16];

  volatile uint32_t* _pGPIO_MODER;
  volatile uint32_t* _pGPIO_OTYPER;
  volatile uint32_t* _pGPIO_OSPEEDR;
  volatile uint32_t* _pGPIO_PUPDR;
  volatile uint32_t* _pGPIO_IDR;
  volatile uint32_t* _pGPIO_ODR;
  volatile uint32_t* _pGPIO_BSRR;
  volatile uint32_t* _pGPIO_LCKR;
  volatile uint32_t* _pGPIO_AFRL;
  volatile uint32_t* _pGPIO_AFRH;

protected:
      GPIO_PORT(
            volatile uint32_t* pGPIO_MODER,
            volatile uint32_t* pGPIO_OTYPER,
            volatile uint32_t* pGPIO_OSPEEDR,
            volatile uint32_t* pGPIO_PUPDR,
            volatile uint32_t* pGPIO_IDR,
            volatile uint32_t* pGPIO_ODR,
            volatile uint32_t* pGPIO_BSRR,
            volatile uint32_t* pGPIO_LCKR,
            volatile uint32_t* pGPIO_AFRL,
            volatile uint32_t* pGPIO_AFRH, 
            volatile uint32_t* pRCCEnableReg,
            volatile uint32_t* pRCCResetReg, 
            uint32_t           rccBit);

    //void SetupGPIO (GPIO_PIN pin, uint32_t cnf, GPIO_MODE mode);
          
public:
    
    

    void SetupGPIO_InFloat (GPIO_PIN_N pin);
    void SetupGPIO_InAnalog (GPIO_PIN_N pin);
    void SetupGPIO_InPullUp (GPIO_PIN_N pin);
    void SetupGPIO_InPullDown (GPIO_PIN_N pin);
    void SetupGPIO_OutPP (GPIO_PIN_N pin);
    void SetupGPIO_OutOD (GPIO_PIN_N pin);
    void SetupGPIO_OutAltOD (GPIO_PIN_N pin);
    void SetupGPIO_OutAltPP (GPIO_PIN_N pin);

    void SetSpeedLow (GPIO_PIN_N pin);
    void SetSpeedMedium (GPIO_PIN_N pin);
    void SetSpeedHigh (GPIO_PIN_N pin);

    void SetOutput (uint16_t value);
    void SetPin (GPIO_PIN_N pin);
    void TogglePin (GPIO_PIN_N pin);
    void ResetPin (GPIO_PIN_N pin);
    uint32_t GetInput();
    bool IsSet (GPIO_PIN_N pin);
    void Lock (uint16_t bitMask);

    void PullUp(GPIO_PIN_N pin);
    void PullDown(GPIO_PIN_N pin);

    GPIO_PIN* GetPin(GPIO_PIN_N pin);

    void SetAF(GPIO_AF afno, GPIO_PIN_N pin); 

};

class GPIOA : public GPIO_PORT 
{
public:
    
    static GPIOA* GetInstance() 
    {
        static GPIOA instance;
        return &instance;
    }


private:
    
    GPIOA() :
    GPIO_PORT (&GPIOA_MODER, &GPIOA_OTYPER, &GPIOA_OSPEEDR, &GPIOA_PUPDR,
          &GPIOA_IDR, &GPIOA_ODR, &GPIOA_BSRR, &GPIOA_LCKR, &GPIOA_AFRL, &GPIOA_AFRH, 
          &RCC_AHB1ENR, &RCC_AHB1RSTR, RCC_AHB1ENR_GPIOAEN)
    {
    }

    GPIOA(GPIOA const&);              
    void operator=(GPIOA const&);
};

class GPIOB : public GPIO_PORT 
{
public:
    
    static GPIOB* GetInstance() 
    {
        static GPIOB instance;
        return &instance;
    }


private:
    
    GPIOB() :
    GPIO_PORT (&GPIOB_MODER, &GPIOB_OTYPER, &GPIOB_OSPEEDR, &GPIOB_PUPDR,
          &GPIOB_IDR, &GPIOB_ODR, &GPIOB_BSRR, &GPIOB_LCKR, &GPIOB_AFRL, &GPIOB_AFRH, 
          &RCC_AHB1ENR, &RCC_AHB1RSTR, RCC_AHB1ENR_GPIOBEN)
    {
    }

    GPIOB(GPIOB const&);              
    void operator=(GPIOB const&);
};

class GPIOC : public GPIO_PORT 
{
public:
    
    static GPIOC* GetInstance() 
    {
        static GPIOC instance;
        return &instance;
    }


private:
    
    GPIOC() :
    GPIO_PORT (&GPIOC_MODER, &GPIOC_OTYPER, &GPIOC_OSPEEDR, &GPIOC_PUPDR,
          &GPIOC_IDR, &GPIOC_ODR, &GPIOC_BSRR, &GPIOC_LCKR, &GPIOC_AFRL, &GPIOC_AFRH, 
          &RCC_AHB1ENR, &RCC_AHB1RSTR, RCC_AHB1ENR_GPIOCEN)
    {
    }

    GPIOC(GPIOC const&);              
    void operator=(GPIOC const&);
};


class GPIOD : public GPIO_PORT 
{
public:
    
    static GPIOD* GetInstance() 
    {
        static GPIOD instance;
        return &instance;
    }


private:
    
    GPIOD() :
    GPIO_PORT (&GPIOD_MODER, &GPIOD_OTYPER, &GPIOD_OSPEEDR, &GPIOD_PUPDR,
          &GPIOD_IDR, &GPIOD_ODR, &GPIOD_BSRR, &GPIOD_LCKR, &GPIOD_AFRL, &GPIOD_AFRH, 
          &RCC_AHB1ENR, &RCC_AHB1RSTR, RCC_AHB1ENR_GPIODEN)
    {
    }

    GPIOD(GPIOD const&);              
    void operator=(GPIOD const&);
};

class GPIOE : public GPIO_PORT 
{
public:
    
    static GPIOE* GetInstance() 
    {
        static GPIOE instance;
        return &instance;
    }


private:
    
    GPIOE() :
    GPIO_PORT (&GPIOE_MODER, &GPIOE_OTYPER, &GPIOE_OSPEEDR, &GPIOE_PUPDR,
          &GPIOE_IDR, &GPIOE_ODR, &GPIOE_BSRR, &GPIOE_LCKR, &GPIOE_AFRL, &GPIOE_AFRH, 
          &RCC_AHB1ENR, &RCC_AHB1RSTR, RCC_AHB1ENR_GPIOEEN)
    {
    }

    GPIOE(GPIOE const&);              
    void operator=(GPIOE const&);
};


class GPIOF : public GPIO_PORT 
{
public:
    
    static GPIOF* GetInstance() 
    {
        static GPIOF instance;
        return &instance;
    }


private:
    
    GPIOF() :
    GPIO_PORT (&GPIOF_MODER, &GPIOF_OTYPER, &GPIOF_OSPEEDR, &GPIOF_PUPDR,
          &GPIOF_IDR, &GPIOF_ODR, &GPIOF_BSRR, &GPIOF_LCKR, &GPIOF_AFRL, &GPIOF_AFRH, 
          &RCC_AHB1ENR, &RCC_AHB1RSTR, RCC_AHB1ENR_GPIOFEN)
    {
    }

    GPIOF(GPIOF const&);              
    void operator=(GPIOF const&);
};

class GPIOG : public GPIO_PORT 
{
public:
    
    static GPIOG* GetInstance() 
    {
        static GPIOG instance;
        return &instance;
    }


private:
    
    GPIOG() :
    GPIO_PORT (&GPIOG_MODER, &GPIOG_OTYPER, &GPIOG_OSPEEDR, &GPIOG_PUPDR,
          &GPIOG_IDR, &GPIOG_ODR, &GPIOG_BSRR, &GPIOG_LCKR, &GPIOG_AFRL, &GPIOG_AFRH, 
          &RCC_AHB1ENR, &RCC_AHB1RSTR, RCC_AHB1ENR_GPIOGEN)
    {
    }

    GPIOG(GPIOG const&);              
    void operator=(GPIOG const&);
};

class GPIOH : public GPIO_PORT 
{
public:
    
    static GPIOH* GetInstance() 
    {
        static GPIOH instance;
        return &instance;
    }


private:
    
    GPIOH() :
    GPIO_PORT (&GPIOH_MODER, &GPIOH_OTYPER, &GPIOH_OSPEEDR, &GPIOH_PUPDR,
          &GPIOH_IDR, &GPIOH_ODR, &GPIOH_BSRR, &GPIOH_LCKR, &GPIOH_AFRL, &GPIOH_AFRH, 
          &RCC_AHB1ENR, &RCC_AHB1RSTR, RCC_AHB1ENR_GPIOHEN)
    {
    }

    GPIOH(GPIOH const&);              
    void operator=(GPIOH const&);
};

class GPIOI : public GPIO_PORT 
{
public:
    
    static GPIOI* GetInstance() 
    {
        static GPIOI instance;
        return &instance;
    }


private:
    
    GPIOI() :
    GPIO_PORT (&GPIOI_MODER, &GPIOI_OTYPER, &GPIOI_OSPEEDR, &GPIOI_PUPDR,
          &GPIOI_IDR, &GPIOI_ODR, &GPIOI_BSRR, &GPIOI_LCKR, &GPIOI_AFRL, &GPIOI_AFRH, 
          &RCC_AHB1ENR, &RCC_AHB1RSTR, RCC_AHB1ENR_GPIOIEN)
    {
    }

    GPIOI(GPIOI const&);              
    void operator=(GPIOI const&);
};

class GPIOJ : public GPIO_PORT 
{
public:
    
    static GPIOJ* GetInstance() 
    {
        static GPIOJ instance;
        return &instance;
    }


private:
    
    GPIOJ() :
    GPIO_PORT (&GPIOJ_MODER, &GPIOJ_OTYPER, &GPIOJ_OSPEEDR, &GPIOJ_PUPDR,
          &GPIOJ_IDR, &GPIOJ_ODR, &GPIOJ_BSRR, &GPIOJ_LCKR, &GPIOJ_AFRL, &GPIOJ_AFRH, 
          &RCC_AHB1ENR, &RCC_AHB1RSTR, RCC_AHB1ENR_GPIOJEN)
    {
    }

    GPIOJ(GPIOJ const&);              
    void operator=(GPIOJ const&);
};


class GPIOK : public GPIO_PORT 
{
public:
    
    static GPIOK* GetInstance() 
    {
        static GPIOK instance;
        return &instance;
    }


private:
    
    GPIOK() :
    GPIO_PORT (&GPIOK_MODER, &GPIOK_OTYPER, &GPIOK_OSPEEDR, &GPIOK_PUPDR,
          &GPIOK_IDR, &GPIOK_ODR, &GPIOK_BSRR, &GPIOK_LCKR, &GPIOK_AFRL, &GPIOK_AFRH, 
          &RCC_AHB1ENR, &RCC_AHB1RSTR, RCC_AHB1ENR_GPIOKEN)
    {
    }

    GPIOK(GPIOK const&);              
    void operator=(GPIOK const&);
};



#endif

