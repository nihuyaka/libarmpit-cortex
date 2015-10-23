#ifndef _GPIO_H
#define _GPIO_H

#include "common.h"

//AHB1
#define GPIOA_BASE 0x40020000
#define GPIOB_BASE 0x40020400
#define GPIOC_BASE 0x40020800
#define GPIOD_BASE 0x40020C00 
#define GPIOE_BASE 0x40021000
#define GPIOF_BASE 0x40021400
#define GPIOG_BASE 0x40021800
#define GPIOH_BASE 0x40021C00 
#define GPIOI_BASE 0x40022000 
#define GPIOJ_BASE 0x40022400 
#define GPIOK_BASE 0x40022800

enum GPIO_OUT_SPEED 
{
    GPIO_OUT_SPEED_LOW     = 0,
    GPIO_OUT_SPEED_MEDIUM  = 1,
    GPIO_OUT_SPEED_FAST    = 2,
    GPIO_OUT_SPEED_HIGH    = 3
};

enum GPIO_MODE 
{
    GPIO_MODE_IN = 0,
    GPIO_MODE_OUT = 1,
    GPIO_MODE_ALT = 2,
    GPIO_MODE_ANAL = 3,
};

enum GPIO_CONF_IN 
{
    GPIO_CNF_IFLOAT = 1,
    GPIO_CNF_IPUP  = 2,
    GPIO_CNF_IPDN  = 3
};

enum GPIO_CONF_OUT 
{
    GPIO_CNF_OPP    = 0, 
    GPIO_CNF_OD     = 1
};

enum GPIO_PIN_N 
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
};

enum GPIO_PORT_N
{
    PORTA = 0,
    PORTB = 1,
    PORTC = 2,
    PORTD = 3,
    PORTE = 4,
    PORTF = 5,
    PORTG = 6,
    PORTH = 7
};

enum GPIO_AF
{
    AF0,
    AF1,
    AF2,
    AF3,
    AF4,
    AF5,
    AF6,
    AF7,
    AF8,
    AF9,
    AF10,
    AF11,
    AF12,
    AF13,
    AF14,
    AF15
};


#define GPIOA_MODER    (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOB_MODER    (*(volatile uint32_t*)(GPIOB_BASE + 0x00))
#define GPIOC_MODER    (*(volatile uint32_t*)(GPIOC_BASE + 0x00))
#define GPIOD_MODER    (*(volatile uint32_t*)(GPIOD_BASE + 0x00))
#define GPIOE_MODER    (*(volatile uint32_t*)(GPIOE_BASE + 0x00))
#define GPIOF_MODER    (*(volatile uint32_t*)(GPIOF_BASE + 0x00))
#define GPIOG_MODER    (*(volatile uint32_t*)(GPIOG_BASE + 0x00))
#define GPIOH_MODER    (*(volatile uint32_t*)(GPIOH_BASE + 0x00))
#define GPIOI_MODER    (*(volatile uint32_t*)(GPIOI_BASE + 0x00))
#define GPIOJ_MODER    (*(volatile uint32_t*)(GPIOJ_BASE + 0x00))
#define GPIOK_MODER    (*(volatile uint32_t*)(GPIOJ_BASE + 0x00))

#define GPIOA_OTYPER   (*(volatile uint32_t*)(GPIOA_BASE + 0x04))
#define GPIOB_OTYPER   (*(volatile uint32_t*)(GPIOB_BASE + 0x04))
#define GPIOC_OTYPER   (*(volatile uint32_t*)(GPIOC_BASE + 0x04))
#define GPIOD_OTYPER   (*(volatile uint32_t*)(GPIOD_BASE + 0x04))
#define GPIOE_OTYPER   (*(volatile uint32_t*)(GPIOE_BASE + 0x04))
#define GPIOF_OTYPER   (*(volatile uint32_t*)(GPIOF_BASE + 0x04))
#define GPIOG_OTYPER   (*(volatile uint32_t*)(GPIOG_BASE + 0x04))
#define GPIOH_OTYPER   (*(volatile uint32_t*)(GPIOH_BASE + 0x04))
#define GPIOI_OTYPER   (*(volatile uint32_t*)(GPIOI_BASE + 0x04))
#define GPIOJ_OTYPER   (*(volatile uint32_t*)(GPIOJ_BASE + 0x04))
#define GPIOK_OTYPER   (*(volatile uint32_t*)(GPIOK_BASE + 0x04))


#define GPIOA_OSPEEDR  (*(volatile uint32_t*)(GPIOA_BASE + 0x08))
#define GPIOB_OSPEEDR  (*(volatile uint32_t*)(GPIOB_BASE + 0x08))
#define GPIOC_OSPEEDR  (*(volatile uint32_t*)(GPIOC_BASE + 0x08))
#define GPIOD_OSPEEDR  (*(volatile uint32_t*)(GPIOD_BASE + 0x08))
#define GPIOE_OSPEEDR  (*(volatile uint32_t*)(GPIOE_BASE + 0x08))
#define GPIOF_OSPEEDR  (*(volatile uint32_t*)(GPIOF_BASE + 0x08))
#define GPIOG_OSPEEDR  (*(volatile uint32_t*)(GPIOG_BASE + 0x08))
#define GPIOH_OSPEEDR  (*(volatile uint32_t*)(GPIOH_BASE + 0x08))
#define GPIOI_OSPEEDR  (*(volatile uint32_t*)(GPIOI_BASE + 0x08))
#define GPIOJ_OSPEEDR  (*(volatile uint32_t*)(GPIOJ_BASE + 0x08))
#define GPIOK_OSPEEDR  (*(volatile uint32_t*)(GPIOK_BASE + 0x08))

#define GPIOA_PUPDR    (*(volatile uint32_t*)(GPIOA_BASE + 0x0C))
#define GPIOB_PUPDR    (*(volatile uint32_t*)(GPIOB_BASE + 0x0C))
#define GPIOC_PUPDR    (*(volatile uint32_t*)(GPIOC_BASE + 0x0C))
#define GPIOD_PUPDR    (*(volatile uint32_t*)(GPIOD_BASE + 0x0C))
#define GPIOE_PUPDR    (*(volatile uint32_t*)(GPIOE_BASE + 0x0C))
#define GPIOF_PUPDR    (*(volatile uint32_t*)(GPIOF_BASE + 0x0C))
#define GPIOG_PUPDR    (*(volatile uint32_t*)(GPIOG_BASE + 0x0C))
#define GPIOH_PUPDR    (*(volatile uint32_t*)(GPIOH_BASE + 0x0C))
#define GPIOI_PUPDR    (*(volatile uint32_t*)(GPIOI_BASE + 0x0C))
#define GPIOJ_PUPDR    (*(volatile uint32_t*)(GPIOJ_BASE + 0x0C))
#define GPIOK_PUPDR    (*(volatile uint32_t*)(GPIOK_BASE + 0x0C))


#define GPIOA_IDR      (*(volatile uint32_t*)(GPIOA_BASE + 0x10))
#define GPIOB_IDR      (*(volatile uint32_t*)(GPIOB_BASE + 0x10))
#define GPIOC_IDR      (*(volatile uint32_t*)(GPIOC_BASE + 0x10))
#define GPIOD_IDR      (*(volatile uint32_t*)(GPIOD_BASE + 0x10))
#define GPIOE_IDR      (*(volatile uint32_t*)(GPIOE_BASE + 0x10))
#define GPIOF_IDR      (*(volatile uint32_t*)(GPIOF_BASE + 0x10))
#define GPIOG_IDR      (*(volatile uint32_t*)(GPIOG_BASE + 0x10))
#define GPIOH_IDR      (*(volatile uint32_t*)(GPIOH_BASE + 0x10))
#define GPIOI_IDR      (*(volatile uint32_t*)(GPIOI_BASE + 0x10))
#define GPIOJ_IDR      (*(volatile uint32_t*)(GPIOJ_BASE + 0x10))
#define GPIOK_IDR      (*(volatile uint32_t*)(GPIOK_BASE + 0x10))


#define GPIOA_ODR      (*(volatile uint32_t*)(GPIOA_BASE + 0x14))
#define GPIOB_ODR      (*(volatile uint32_t*)(GPIOB_BASE + 0x14))
#define GPIOC_ODR      (*(volatile uint32_t*)(GPIOC_BASE + 0x14))
#define GPIOD_ODR      (*(volatile uint32_t*)(GPIOD_BASE + 0x14))
#define GPIOE_ODR      (*(volatile uint32_t*)(GPIOE_BASE + 0x14))
#define GPIOF_ODR      (*(volatile uint32_t*)(GPIOF_BASE + 0x14))
#define GPIOG_ODR      (*(volatile uint32_t*)(GPIOG_BASE + 0x14))
#define GPIOH_ODR      (*(volatile uint32_t*)(GPIOH_BASE + 0x14))
#define GPIOI_ODR      (*(volatile uint32_t*)(GPIOI_BASE + 0x14))
#define GPIOJ_ODR      (*(volatile uint32_t*)(GPIOJ_BASE + 0x14))
#define GPIOK_ODR      (*(volatile uint32_t*)(GPIOK_BASE + 0x14))


#define GPIOA_BSRR     (*(volatile uint32_t*)(GPIOA_BASE + 0x18))
#define GPIOB_BSRR     (*(volatile uint32_t*)(GPIOB_BASE + 0x18))
#define GPIOC_BSRR     (*(volatile uint32_t*)(GPIOC_BASE + 0x18))
#define GPIOD_BSRR     (*(volatile uint32_t*)(GPIOD_BASE + 0x18))
#define GPIOE_BSRR     (*(volatile uint32_t*)(GPIOE_BASE + 0x18))
#define GPIOF_BSRR     (*(volatile uint32_t*)(GPIOF_BASE + 0x18))
#define GPIOG_BSRR     (*(volatile uint32_t*)(GPIOG_BASE + 0x18))
#define GPIOH_BSRR     (*(volatile uint32_t*)(GPIOH_BASE + 0x18))
#define GPIOI_BSRR     (*(volatile uint32_t*)(GPIOI_BASE + 0x18))
#define GPIOJ_BSRR     (*(volatile uint32_t*)(GPIOJ_BASE + 0x18))
#define GPIOK_BSRR     (*(volatile uint32_t*)(GPIOK_BASE + 0x18))


#define GPIOA_LCKR     (*(volatile uint32_t*)(GPIOA_BASE + 0x1c))
#define GPIOB_LCKR     (*(volatile uint32_t*)(GPIOB_BASE + 0x1c))
#define GPIOC_LCKR     (*(volatile uint32_t*)(GPIOC_BASE + 0x1c))
#define GPIOD_LCKR     (*(volatile uint32_t*)(GPIOD_BASE + 0x1c))
#define GPIOE_LCKR     (*(volatile uint32_t*)(GPIOE_BASE + 0x1c))
#define GPIOF_LCKR     (*(volatile uint32_t*)(GPIOF_BASE + 0x1c))
#define GPIOG_LCKR     (*(volatile uint32_t*)(GPIOG_BASE + 0x1c))
#define GPIOH_LCKR     (*(volatile uint32_t*)(GPIOH_BASE + 0x1c))
#define GPIOI_LCKR     (*(volatile uint32_t*)(GPIOI_BASE + 0x1c))
#define GPIOJ_LCKR     (*(volatile uint32_t*)(GPIOJ_BASE + 0x1c))
#define GPIOK_LCKR     (*(volatile uint32_t*)(GPIOK_BASE + 0x1c))


#define GPIOA_AFRL     (*(volatile uint32_t*)(GPIOA_BASE + 0x20))
#define GPIOB_AFRL     (*(volatile uint32_t*)(GPIOB_BASE + 0x20))
#define GPIOC_AFRL     (*(volatile uint32_t*)(GPIOC_BASE + 0x20))
#define GPIOD_AFRL     (*(volatile uint32_t*)(GPIOD_BASE + 0x20))
#define GPIOE_AFRL     (*(volatile uint32_t*)(GPIOE_BASE + 0x20))
#define GPIOF_AFRL     (*(volatile uint32_t*)(GPIOF_BASE + 0x20))
#define GPIOG_AFRL     (*(volatile uint32_t*)(GPIOG_BASE + 0x20))
#define GPIOH_AFRL     (*(volatile uint32_t*)(GPIOH_BASE + 0x20))
#define GPIOI_AFRL     (*(volatile uint32_t*)(GPIOI_BASE + 0x20))
#define GPIOJ_AFRL     (*(volatile uint32_t*)(GPIOJ_BASE + 0x20))
#define GPIOK_AFRL     (*(volatile uint32_t*)(GPIOK_BASE + 0x20))


#define GPIOA_AFRH     (*(volatile uint32_t*)(GPIOA_BASE + 0x24))
#define GPIOB_AFRH     (*(volatile uint32_t*)(GPIOB_BASE + 0x24))
#define GPIOC_AFRH     (*(volatile uint32_t*)(GPIOC_BASE + 0x24))
#define GPIOD_AFRH     (*(volatile uint32_t*)(GPIOD_BASE + 0x24))
#define GPIOE_AFRH     (*(volatile uint32_t*)(GPIOE_BASE + 0x24))
#define GPIOF_AFRH     (*(volatile uint32_t*)(GPIOF_BASE + 0x24))
#define GPIOG_AFRH     (*(volatile uint32_t*)(GPIOG_BASE + 0x24))
#define GPIOH_AFRH     (*(volatile uint32_t*)(GPIOH_BASE + 0x24))
#define GPIOI_AFRH     (*(volatile uint32_t*)(GPIOI_BASE + 0x24))
#define GPIOJ_AFRH     (*(volatile uint32_t*)(GPIOJ_BASE + 0x24))
#define GPIOK_AFRH     (*(volatile uint32_t*)(GPIOK_BASE + 0x24))


#define GPIO_AFR_MASK 0x0f


#define GPIOG_LCKR_LCKK (1<<16)


#endif
