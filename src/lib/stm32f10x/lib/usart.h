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



#ifndef _USART_H
#define _USART_H

#include "common.h"

#ifdef USE_USART


#define USART1_BASE 0x40013800  //APB2
#define USART2_BASE 0x40004400  //APB1
#define USART3_BASE 0x40004800  //APB1


#define USART1_SR       (*(volatile uint32_t*)(USART1_BASE))
#define USART1_DR       (*(volatile uint32_t*)(USART1_BASE + 0x04))
#define USART1_BRR      (*(volatile uint32_t*)(USART1_BASE + 0x08))
#define USART1_CR1      (*(volatile uint32_t*)(USART1_BASE + 0x0c))
#define USART1_CR2      (*(volatile uint32_t*)(USART1_BASE + 0x10))
#define USART1_CR3      (*(volatile uint32_t*)(USART1_BASE + 0x14))


#define USART2_SR       (*(volatile uint32_t*)(USART2_BASE))
#define USART2_DR       (*(volatile uint32_t*)(USART2_BASE + 0x04))
#define USART2_BRR      (*(volatile uint32_t*)(USART2_BASE + 0x08))
#define USART2_CR1      (*(volatile uint32_t*)(USART2_BASE + 0x0c))
#define USART2_CR2      (*(volatile uint32_t*)(USART2_BASE + 0x10))
#define USART2_CR3      (*(volatile uint32_t*)(USART2_BASE + 0x14))

#define USART3_SR       (*(volatile uint32_t*)(USART3_BASE))
#define USART3_DR       (*(volatile uint32_t*)(USART3_BASE + 0x04))
#define USART3_BRR      (*(volatile uint32_t*)(USART3_BASE + 0x08))
#define USART3_CR1      (*(volatile uint32_t*)(USART3_BASE + 0x0c))
#define USART3_CR2      (*(volatile uint32_t*)(USART3_BASE + 0x10))
#define USART3_CR3      (*(volatile uint32_t*)(USART3_BASE + 0x14))


#define USART_SR_PE    (1<<0)   //Parity Error
#define USART_SR_FE    (1<<1)   //Framing Error
#define USART_SR_NE    (1<<2)   //Noise Error
#define USART_SR_ORE   (1<<3)   //Overrun Error
#define USART_SR_IDLE  (1<<4)   //Idle line detected
#define USART_SR_RXNE  (1<<5)   //Read data register not empty
#define USART_SR_TC    (1<<6)   //Transmission complete
#define USART_SR_TXE   (1<<7)   //Transmit data register empty
#define USART_SR_LBD   (1<<8)   //LIN break detection flag
#define USART_SR_CTS   (1<<9)   //CTS flag

#define USART_CR1_SBK                 (1<<0)  //Send break
#define USART_CR1_RWU                 (1<<1)  //Receiver wakeup
#define USART_CR1_RE                  (1<<2)   //Receiver enable
#define USART_CR1_TE                  (1<<3)   //Transmitter enable
#define USART_CR1_IDLEIE              (1<<4)  //IDLE interrupt enable
#define USART_CR1_RXNEIE              (1<<5)  //RXNE interrupt enable
#define USART_CR1_TCIE                (1<<6)   //Transmission complete interrupt enable
#define USART_CR1_TXEIE               (1<<7)   //TXE interrupt enable
#define USART_CR1_PEIE                (1<<8)    //PE interrupt enable
#define USART_CR1_PS                  (1<<9)      //Parity selection
#define USART_CR1_PCE                 (1<<10)    //Parity control enable
#define USART_CR1_WAKE_ADDRESS_MARK   (1<<11)   //Wakeup method
#define USART_CR1_M_9bits             (1<<12)    // Word length
#define USART_CR1_UE                  (1<<13)         //USART enable

//USART_CR2_ADDR [3:0] : addr

#define USART_CR2_LBDL_10_BIT    (0<<5)
#define USART_CR2_LBDL_11_BIT    (1<<5)
#define USART_CR2_LBDIE          (1<<6)   //LIN break detection interrupt enable
#define USART_CR2_LBCL           (1<<8)   //Last bit clock pulse
#define USART_CR2_CPHA_FIRST     (0<<9)   //Clock phase
#define USART_CR2_CPHA_SECOND    (1<<9)   //Clock phase
#define USART_CR2_CPOL_LOW       (0<<10) //Clock polarity
#define USART_CR2_CPOL_HIGH      (1<<10)
#define USART_CR2_CLKEN          (1<<11) //Clock enable
#define USART_CR2_STOP_1         (0<<12)
#define USART_CR2_STOP_0_5       (1<<12)
#define USART_CR2_STOP_2         (2<<12)
#define USART_CR2_STOP_1_5       (3<<12)
#define USART_CR2_LINEN          (1<<14) //LIN mode enable

#define USART_CR3_EIE  (1<<0)   //Error interrupt enable
#define USART_CR3_IREN (1<<1)   //IrDA mode enable
#define USART_CR3_IRLP (1<<2)   //IrDA low-power
#define USART_CR3_HDSEL (1<<3)  //Half-duplex selection
#define USART_CR3_NACK  (1<<4)  //Smartcard NACK enable
#define USART_CR3_SCEN  (1<<5)  //Smartcard mode enable
#define USART_CR3_DMAR  (1<<6)  //DMA enable receiver
#define USART_CR3_DMAT  (1<<7)  //DMA enable transmitter
#define USART_CR3_RTSE  (1<<8)  //RTS enable  (hardware flow control, request)
#define USART_CR3_CTSE  (1<<9)  //CTS enable  (hardware flow control, transmit)
#define USART_CR3_CTSIE (1<<10) //CTS interrupt enable


#endif

#endif

