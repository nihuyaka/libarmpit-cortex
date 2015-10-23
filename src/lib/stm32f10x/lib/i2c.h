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


#ifndef _I2C_H
#define _I2C_H

#include "common.h"

#ifdef USE_I2C


#define I2C1_BASE 0x40005400  //APB1
#define I2C2_BASE 0x40005800  //APB1


#define I2C1_CR1      (*(volatile uint32_t*)(I2C1_BASE))
#define I2C1_CR2      (*(volatile uint32_t*)(I2C1_BASE + 0x04))
#define I2C1_OAR1     (*(volatile uint32_t*)(I2C1_BASE + 0x08))
#define I2C1_OAR2     (*(volatile uint32_t*)(I2C1_BASE + 0x0c))
#define I2C1_DR       (*(volatile uint32_t*)(I2C1_BASE + 0x10))
#define I2C1_SR1      (*(volatile uint32_t*)(I2C1_BASE + 0x14))
#define I2C1_SR2      (*(volatile uint32_t*)(I2C1_BASE + 0x18))
#define I2C1_CCR      (*(volatile uint32_t*)(I2C1_BASE + 0x1c))
#define I2C1_TRISE    (*(volatile uint32_t*)(I2C1_BASE + 0x20))

#define I2C2_CR1      (*(volatile uint32_t*)(I2C2_BASE))
#define I2C2_CR2      (*(volatile uint32_t*)(I2C2_BASE + 0x04))
#define I2C2_OAR1     (*(volatile uint32_t*)(I2C2_BASE + 0x08))
#define I2C2_OAR2     (*(volatile uint32_t*)(I2C2_BASE + 0x0c))
#define I2C2_DR       (*(volatile uint32_t*)(I2C2_BASE + 0x10))
#define I2C2_SR1      (*(volatile uint32_t*)(I2C2_BASE + 0x14))
#define I2C2_SR2      (*(volatile uint32_t*)(I2C2_BASE + 0x18))
#define I2C2_CCR      (*(volatile uint32_t*)(I2C2_BASE + 0x1c))
#define I2C2_TRISE    (*(volatile uint32_t*)(I2C2_BASE + 0x20))



#define I2C_CR1_PE        (1<<0)
#define I2C_CR1_SMBUS     (1<<1)
#define I2C_CR1_SMBTYPE   (1<<3)
#define I2C_CR1_ENARP     (1<<4)
#define I2C_CR1_ENPEC     (1<<5)
#define I2C_CR1_ENGC      (1<<6)
#define I2C_CR1_NOSTRETCH (1<<7)
#define I2C_CR1_START     (1<<8)
#define I2C_CR1_STOP      (1<<9)
#define I2C_CR1_ACK       (1<<10)
#define I2C_CR1_POS       (1<<11)
#define I2C_CR1_PEC       (1<<12)
#define I2C_CR1_ALERT     (1<<13)
#define I2C_CR1_SWRST     (1<<15)

#define I2C_CR2_FREQ      (1<<0)  //5:0
#define I2C_CR2_ITERREN   (1<<8)
#define I2C_CR2_ITEVTEN   (1<<9)
#define I2C_CR2_ITBUFEN   (1<<10)
#define I2C_CR2_DMANEN    (1<<11)
#define I2C_CR2_LAST      (1<<12)


#define I2C_OAR1_ADD0     (1<<0)
#define I2C_OAR1_ADD71    (1<<1)
#define I2C_OAR1_ADD98    (1<<8)
#define I2C_OAR1_ADDMODE  (1<<15)

#define I2C_OAR2_ENDUAL   (1<<0)
#define I2C_OAR2_ADD2     (1<<1)  //7:1


#define I2C_SR1_SB           (1<<0)
#define I2C_SR1_ADDR         (1<<1)
#define I2C_SR1_BTF          (1<<2)
#define I2C_SR1_ADD10        (1<<3)
#define I2C_SR1_STOPF        (1<<4)
#define I2C_SR1_RxNE         (1<<6)
#define I2C_SR1_TxE          (1<<7)
#define I2C_SR1_BERR         (1<<8)
#define I2C_SR1_ARLO         (1<<9)
#define I2C_SR1_AF           (1<<10)
#define I2C_SR1_OVR          (1<<11)
#define I2C_SR1_PECERR       (1<<12)
#define I2C_SR1_TIMEOUT      (1<<14)
#define I2C_SR1_SMBALERT     (1<<15)


#define I2C_SR2_MSL           (1<<0)
#define I2C_SR2_BUSY          (1<<1)
#define I2C_SR2_TRA           (1<<2)
#define I2C_SR2_GENCALL       (1<<4)
#define I2C_SR2_SMBDEFAULT    (1<<5)
#define I2C_SR2_SMBHOST       (1<<6)
#define I2C_SR2_DUALF         (1<<7)
#define I2C_SR2_PEC           (1<<8)

#define I2C_CCR_CCR           (1<<0) //11:0

#define I2C_CCR_DUTY          (1<<14)
#define I2C_CCR_FS            (1<<15)  //0:sm 1:fm



#endif

#endif
