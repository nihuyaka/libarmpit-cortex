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



#ifndef _GPIO_H
#define _GPIO_H

#include <stdint.h>
#include "common.h"

//9. ********************  GPIO APB2  *****************************
#define GPIOA_BASE 0x40010800
#define GPIOB_BASE 0x40010C00
#define GPIOC_BASE 0x40011000
#define GPIOD_BASE 0x40011400
#define GPIOE_BASE 0x40011800
#define GPIOF_BASE 0x40011C00
#define GPIOG_BASE 0x40012000

#define GPIOA_CR  (*(volatile uint64_t*)(GPIOA_BASE))
#define GPIOB_CR  (*(volatile uint64_t*)(GPIOB_BASE))
#define GPIOC_CR  (*(volatile uint64_t*)(GPIOC_BASE))
#define GPIOD_CR  (*(volatile uint64_t*)(GPIOD_BASE))
#define GPIOE_CR  (*(volatile uint64_t*)(GPIOE_BASE))
#define GPIOF_CR  (*(volatile uint64_t*)(GPIOF_BASE))
#define GPIOG_CR  (*(volatile uint64_t*)(GPIOG_BASE))

enum GPIO_MODE 
{
    GPIO_MODE_INP       = 0,
    GPIO_MODE_OUT_MEDIUM_SPEED = 1,  //10MHZ
    GPIO_MODE_OUT_LOW_SPEED  = 2,    //2MHZ
    GPIO_MODE_OUT_HIGH_SPEED = 3          //50MHZ
};


enum GPIO_CONF_IN 
{
    GPIO_CNF_IANAL  = 0,
    GPIO_CNF_IFLOAT = 1,
    GPIO_CNF_IPUPD  = 2
};

//#define GPIO_CNF_OPP     0LLU
//#define GPIO_CNF_OD      (1LLU<<2LLU)
//#define GPIO_CNF_ALT_PP  (2LLU<<2LLU)
//#define GPIO_CNF_ALT_OD  (3LLU<<2LLU)

enum GPIO_CONF_OUT 
{
    GPIO_CNF_OPP    = 0, 
    GPIO_CNF_OD     = 1,
    GPIO_CNF_ALT_PP = 2,
    GPIO_CNF_ALT_OD = 3
};

typedef enum
{
 GPIO_PIN0  = 0,
 GPIO_PIN1  = 1,
 GPIO_PIN2  = 2,
 GPIO_PIN3  = 3,
 GPIO_PIN4  = 4,
 GPIO_PIN5  = 5,
 GPIO_PIN6  = 6,
 GPIO_PIN7  = 7,
 GPIO_PIN8  = 8,
 GPIO_PIN9  = 9,
 GPIO_PIN10 = 10,
 GPIO_PIN11 = 11,
 GPIO_PIN12 = 12,
 GPIO_PIN13 = 13,
 GPIO_PIN14 = 14,
 GPIO_PIN15 = 15
} GPIO_PIN_N;

typedef enum
{
	PORTA = 0,
	PORTB = 1,
	PORTC = 2,
	PORTD = 3,
	PORTE = 4,
	PORTF = 5,
	PORTG = 6
} GPIO_PORT_N ;


#define GPIOA_IDR  (*(volatile uint32_t*)(GPIOA_BASE + 0x08))
#define GPIOB_IDR  (*(volatile uint32_t*)(GPIOB_BASE + 0x08))
#define GPIOC_IDR  (*(volatile uint32_t*)(GPIOC_BASE + 0x08))
#define GPIOD_IDR  (*(volatile uint32_t*)(GPIOD_BASE + 0x08))
#define GPIOE_IDR  (*(volatile uint32_t*)(GPIOE_BASE + 0x08))
#define GPIOF_IDR  (*(volatile uint32_t*)(GPIOF_BASE + 0x08))
#define GPIOG_IDR  (*(volatile uint32_t*)(GPIOG_BASE + 0x08))

#define GPIOA_ODR  (*(volatile uint32_t*)(GPIOA_BASE + 0x0c))
#define GPIOB_ODR  (*(volatile uint32_t*)(GPIOB_BASE + 0x0c))
#define GPIOC_ODR  (*(volatile uint32_t*)(GPIOC_BASE + 0x0c))
#define GPIOD_ODR  (*(volatile uint32_t*)(GPIOD_BASE + 0x0c))
#define GPIOE_ODR  (*(volatile uint32_t*)(GPIOE_BASE + 0x0c))
#define GPIOF_ODR  (*(volatile uint32_t*)(GPIOF_BASE + 0x0c))
#define GPIOG_ODR  (*(volatile uint32_t*)(GPIOG_BASE + 0x0c))

#define GPIOA_BSRR  (*(volatile uint32_t*)(GPIOA_BASE + 0x10))
#define GPIOB_BSRR  (*(volatile uint32_t*)(GPIOB_BASE + 0x10))
#define GPIOC_BSRR  (*(volatile uint32_t*)(GPIOC_BASE + 0x10))
#define GPIOD_BSRR  (*(volatile uint32_t*)(GPIOD_BASE + 0x10))
#define GPIOE_BSRR  (*(volatile uint32_t*)(GPIOE_BASE + 0x10))
#define GPIOF_BSRR  (*(volatile uint32_t*)(GPIOF_BASE + 0x10))
#define GPIOG_BSRR  (*(volatile uint32_t*)(GPIOG_BASE + 0x10))

#define GPIOA_BRR  (*(volatile uint32_t*)(GPIOA_BASE + 0x14))
#define GPIOB_BRR  (*(volatile uint32_t*)(GPIOB_BASE + 0x14))
#define GPIOC_BRR  (*(volatile uint32_t*)(GPIOC_BASE + 0x14))
#define GPIOD_BRR  (*(volatile uint32_t*)(GPIOD_BASE + 0x14))
#define GPIOE_BRR  (*(volatile uint32_t*)(GPIOE_BASE + 0x14))
#define GPIOF_BRR  (*(volatile uint32_t*)(GPIOF_BASE + 0x14))
#define GPIOG_BRR  (*(volatile uint32_t*)(GPIOG_BASE + 0x14))

#define GPIOA_LCKR  (*(volatile uint32_t*)(GPIOA_BASE + 0x18))
#define GPIOB_LCKR  (*(volatile uint32_t*)(GPIOB_BASE + 0x18))
#define GPIOC_LCKR  (*(volatile uint32_t*)(GPIOC_BASE + 0x18))
#define GPIOD_LCKR  (*(volatile uint32_t*)(GPIOD_BASE + 0x18))
#define GPIOE_LCKR  (*(volatile uint32_t*)(GPIOE_BASE + 0x18))
#define GPIOF_LCKR  (*(volatile uint32_t*)(GPIOF_BASE + 0x18))
#define GPIOG_LCKR  (*(volatile uint32_t*)(GPIOG_BASE + 0x18))

#define GPIOG_LCKR_LCKK (1<<16)

#endif
