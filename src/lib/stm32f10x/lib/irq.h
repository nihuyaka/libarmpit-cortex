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



#ifndef _IRQ_H
#define _IRQ_H



typedef enum IRQn
{
  IRQn_NONE                   = 9999,
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  IRQn_IRQnNonMaskableInt         = -14,    /*!< 2 Non Maskable Interrupt                             */
  IRQn_MemoryManagement       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
  IRQn_BusFault               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
  IRQn_UsageFault             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
  IRQn_SVCall                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
  IRQn_DebugMonitor           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
  IRQn_PendSV                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
  IRQn_SysTick                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */

/******  STM32 specific Interrupt Numbers *********************************************************/
  IRQn_WWDG                   = 0,      /*!< Window WatchDog Interrupt                            */
  IRQn_PVD                    = 1,      /*!< PVD through EXTI Line detection Interrupt            */
  IRQn_TAMPER                 = 2,      /*!< Tamper Interrupt                                     */
  IRQn_RTC                    = 3,      /*!< RTC global Interrupt                                 */
  IRQn_FLASH                  = 4,      /*!< FLASH global Interrupt                               */
  IRQn_RCC                    = 5,      /*!< RCC global Interrupt                                 */
  IRQn_EXTI0                  = 6,      /*!< EXTI Line0 Interrupt                                 */
  IRQn_EXTI1                  = 7,      /*!< EXTI Line1 Interrupt                                 */
  IRQn_EXTI2                  = 8,      /*!< EXTI Line2 Interrupt                                 */
  IRQn_EXTI3                  = 9,      /*!< EXTI Line3 Interrupt                                 */
  IRQn_EXTI4                  = 10,     /*!< EXTI Line4 Interrupt                                 */
  IRQn_DMA1_Channel1          = 11,     /*!< DMA1 Channel 1 global Interrupt                      */
  IRQn_DMA1_Channel2          = 12,     /*!< DMA1 Channel 2 global Interrupt                      */
  IRQn_DMA1_Channel3          = 13,     /*!< DMA1 Channel 3 global Interrupt                      */
  IRQn_DMA1_Channel4          = 14,     /*!< DMA1 Channel 4 global Interrupt                      */
  IRQn_DMA1_Channel5          = 15,     /*!< DMA1 Channel 5 global Interrupt                      */
  IRQn_DMA1_Channel6          = 16,     /*!< DMA1 Channel 6 global Interrupt                      */
  IRQn_DMA1_Channel7          = 17,     /*!< DMA1 Channel 7 global Interrupt                      */

#ifdef STM32F10X_LD
  IRQn_ADC1_2                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
  IRQn_USB_HP_CAN1_TX         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
  IRQn_USB_LP_CAN1_RX0        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
  IRQn_CAN1_RX1               = 21,     /*!< CAN1 RX1 Interrupt                                   */
  IRQn_CAN1_SCE               = 22,     /*!< CAN1 SCE Interrupt                                   */
  IRQn_EXTI9_5                = 23,     /*!< External Line[9:5] Interrupts                        */
  IRQn_TIM1_BRK               = 24,     /*!< TIM1 Break Interrupt                                 */
  IRQn_TIM1_UP                = 25,     /*!< TIM1 Update Interrupt                                */
  IRQn_TIM1_TRG_COM           = 26,     /*!< TIM1 Trigger and Commutation Interrupt               */
  IRQn_TIM1_CC                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
  IRQn_TIM2                   = 28,     /*!< TIM2 global Interrupt                                */
  IRQn_TIM3                   = 29,     /*!< TIM3 global Interrupt                                */
  IRQn_I2C1_EV                = 31,     /*!< I2C1 Event Interrupt                                 */
  IRQn_I2C1_ER                = 32,     /*!< I2C1 Error Interrupt                                 */
  IRQn_SPI1                   = 35,     /*!< SPI1 global Interrupt                                */
  IRQn_USART1                 = 37,     /*!< USART1 global Interrupt                              */
  IRQn_USART2                 = 38,     /*!< USART2 global Interrupt                              */
  IRQn_EXTI15_10              = 40,     /*!< External Line[15:10] Interrupts                      */
  IRQn_RTCAlarm               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
  IRQn_USBWakeUp              = 42      /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
#endif /* STM32F10X_LD */  

#ifdef STM32F10X_LD_VL
  IRQn_ADC1                   = 18,     /*!< ADC1 global Interrupt                                */
  IRQn_EXTI9_5                = 23,     /*!< External Line[9:5] Interrupts                        */
  IRQn_TIM1_BRK_TIM15         = 24,     /*!< TIM1 Break and TIM15 Interrupts                      */
  IRQn_TIM1_UP_TIM16          = 25,     /*!< TIM1 Update and TIM16 Interrupts                     */
  IRQn_TIM1_TRG_COM_TIM17     = 26,     /*!< TIM1 Trigger and Commutation and TIM17 Interrupt     */
  IRQn_TIM1_CC                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
  IRQn_TIM2                   = 28,     /*!< TIM2 global Interrupt                                */
  IRQn_TIM3                   = 29,     /*!< TIM3 global Interrupt                                */
  IRQn_I2C1_EV                = 31,     /*!< I2C1 Event Interrupt                                 */
  IRQn_I2C1_ER                = 32,     /*!< I2C1 Error Interrupt                                 */
  IRQn_SPI1                   = 35,     /*!< SPI1 global Interrupt                                */
  IRQn_USART1                 = 37,     /*!< USART1 global Interrupt                              */
  IRQn_USART2                 = 38,     /*!< USART2 global Interrupt                              */
  IRQn_EXTI15_10              = 40,     /*!< External Line[15:10] Interrupts                      */
  IRQn_RTCAlarm               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
  IRQn_CEC                    = 42,     /*!< HDMI-CEC Interrupt                                   */
  IRQn_TIM6_DAC               = 54,     /*!< TIM6 and DAC underrun Interrupt                      */
  IRQn_TIM7                   = 55      /*!< TIM7 Interrupt                                       */
#endif /* STM32F10X_LD_VL */

#ifdef STM32F10X_MD
  IRQn_ADC1_2                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
  IRQn_USB_HP_CAN1_TX         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
  IRQn_USB_LP_CAN1_RX0        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
  IRQn_CAN1_RX1               = 21,     /*!< CAN1 RX1 Interrupt                                   */
  IRQn_CAN1_SCE               = 22,     /*!< CAN1 SCE Interrupt                                   */
  IRQn_EXTI9_5                = 23,     /*!< External Line[9:5] Interrupts                        */
  IRQn_TIM1_BRK               = 24,     /*!< TIM1 Break Interrupt                                 */
  IRQn_TIM1_UP                = 25,     /*!< TIM1 Update Interrupt                                */
  IRQn_TIM1_TRG_COM           = 26,     /*!< TIM1 Trigger and Commutation Interrupt               */
  IRQn_TIM1_CC                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
  IRQn_TIM2                   = 28,     /*!< TIM2 global Interrupt                                */
  IRQn_TIM3                   = 29,     /*!< TIM3 global Interrupt                                */
  IRQn_TIM4                   = 30,     /*!< TIM4 global Interrupt                                */
  IRQn_I2C1_EV                = 31,     /*!< I2C1 Event Interrupt                                 */
  IRQn_I2C1_ER                = 32,     /*!< I2C1 Error Interrupt                                 */
  IRQn_I2C2_EV                = 33,     /*!< I2C2 Event Interrupt                                 */
  IRQn_I2C2_ER                = 34,     /*!< I2C2 Error Interrupt                                 */
  IRQn_SPI1                   = 35,     /*!< SPI1 global Interrupt                                */
  IRQn_SPI2                   = 36,     /*!< SPI2 global Interrupt                                */
  IRQn_USART1                 = 37,     /*!< USART1 global Interrupt                              */
  IRQn_USART2                 = 38,     /*!< USART2 global Interrupt                              */
  IRQn_USART3                 = 39,     /*!< USART3 global Interrupt                              */
  IRQn_EXTI15_10              = 40,     /*!< External Line[15:10] Interrupts                      */
  IRQn_RTCAlarm               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
  IRQn_USBWakeUp              = 42      /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
#endif /* STM32F10X_MD */  

#ifdef STM32F10X_MD_VL
  IRQn_ADC1                   = 18,     /*!< ADC1 global Interrupt                                */
  IRQn_EXTI9_5                = 23,     /*!< External Line[9:5] Interrupts                        */
  IRQn_TIM1_BRK_TIM15         = 24,     /*!< TIM1 Break and TIM15 Interrupts                      */
  IRQn_TIM1_UP_TIM16          = 25,     /*!< TIM1 Update and TIM16 Interrupts                     */
  IRQn_TIM1_TRG_COM_TIM17     = 26,     /*!< TIM1 Trigger and Commutation and TIM17 Interrupt     */
  IRQn_TIM1_CC                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
  IRQn_TIM2                   = 28,     /*!< TIM2 global Interrupt                                */
  IRQn_TIM3                   = 29,     /*!< TIM3 global Interrupt                                */
  IRQn_TIM4                   = 30,     /*!< TIM4 global Interrupt                                */
  IRQn_I2C1_EV                = 31,     /*!< I2C1 Event Interrupt                                 */
  IRQn_I2C1_ER                = 32,     /*!< I2C1 Error Interrupt                                 */
  IRQn_I2C2_EV                = 33,     /*!< I2C2 Event Interrupt                                 */
  IRQn_I2C2_ER                = 34,     /*!< I2C2 Error Interrupt                                 */
  IRQn_SPI1                   = 35,     /*!< SPI1 global Interrupt                                */
  IRQn_SPI2                   = 36,     /*!< SPI2 global Interrupt                                */
  IRQn_USART1                 = 37,     /*!< USART1 global Interrupt                              */
  IRQn_USART2                 = 38,     /*!< USART2 global Interrupt                              */
  IRQn_USART3                 = 39,     /*!< USART3 global Interrupt                              */
  IRQn_EXTI15_10              = 40,     /*!< External Line[15:10] Interrupts                      */
  IRQn_RTCAlarm               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
  IRQn_CEC                    = 42,     /*!< HDMI-CEC Interrupt                                   */
  IRQn_TIM6_DAC               = 54,     /*!< TIM6 and DAC underrun Interrupt                      */
  IRQn_TIM7                   = 55      /*!< TIM7 Interrupt                                       */
#endif /* STM32F10X_MD_VL */

#ifdef STM32F10X_HD
  IRQn_ADC1_2                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
  IRQn_USB_HP_CAN1_TX         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
  IRQn_USB_LP_CAN1_RX0        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
  IRQn_CAN1_RX1               = 21,     /*!< CAN1 RX1 Interrupt                                   */
  IRQn_CAN1_SCE               = 22,     /*!< CAN1 SCE Interrupt                                   */
  IRQn_EXTI9_5                = 23,     /*!< External Line[9:5] Interrupts                        */
  IRQn_TIM1_BRK               = 24,     /*!< TIM1 Break Interrupt                                 */
  IRQn_TIM1_UP                = 25,     /*!< TIM1 Update Interrupt                                */
  IRQn_TIM1_TRG_COM           = 26,     /*!< TIM1 Trigger and Commutation Interrupt               */
  IRQn_TIM1_CC                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
  IRQn_TIM2                   = 28,     /*!< TIM2 global Interrupt                                */
  IRQn_TIM3                   = 29,     /*!< TIM3 global Interrupt                                */
  IRQn_TIM4                   = 30,     /*!< TIM4 global Interrupt                                */
  IRQn_I2C1_EV                = 31,     /*!< I2C1 Event Interrupt                                 */
  IRQn_I2C1_ER                = 32,     /*!< I2C1 Error Interrupt                                 */
  IRQn_I2C2_EV                = 33,     /*!< I2C2 Event Interrupt                                 */
  IRQn_I2C2_ER                = 34,     /*!< I2C2 Error Interrupt                                 */
  IRQn_SPI1                   = 35,     /*!< SPI1 global Interrupt                                */
  IRQn_SPI2                   = 36,     /*!< SPI2 global Interrupt                                */
  IRQn_USART1                 = 37,     /*!< USART1 global Interrupt                              */
  IRQn_USART2                 = 38,     /*!< USART2 global Interrupt                              */
  IRQn_USART3                 = 39,     /*!< USART3 global Interrupt                              */
  IRQn_EXTI15_10              = 40,     /*!< External Line[15:10] Interrupts                      */
  IRQn_RTCAlarm               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
  IRQn_USBWakeUp              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
  IRQn_TIM8_BRK               = 43,     /*!< TIM8 Break Interrupt                                 */
  IRQn_TIM8_UP                = 44,     /*!< TIM8 Update Interrupt                                */
  IRQn_TIM8_TRG_COM           = 45,     /*!< TIM8 Trigger and Commutation Interrupt               */
  IRQn_TIM8_CC                = 46,     /*!< TIM8 Capture Compare Interrupt                       */
  IRQn_ADC3                   = 47,     /*!< ADC3 global Interrupt                                */
  IRQn_FSMC                   = 48,     /*!< FSMC global Interrupt                                */
  IRQn_SDIO                   = 49,     /*!< SDIO global Interrupt                                */
  IRQn_TIM5                   = 50,     /*!< TIM5 global Interrupt                                */
  IRQn_SPI3                   = 51,     /*!< SPI3 global Interrupt                                */
  IRQn_UART4                  = 52,     /*!< UART4 global Interrupt                               */
  IRQn_UART5                  = 53,     /*!< UART5 global Interrupt                               */
  IRQn_TIM6                   = 54,     /*!< TIM6 global Interrupt                                */
  IRQn_TIM7                   = 55,     /*!< TIM7 global Interrupt                                */
  IRQn_DMA2_Channel1          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
  IRQn_DMA2_Channel2          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
  IRQn_DMA2_Channel3          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
  IRQn_DMA2_Channel4_5        = 59      /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
#endif /* STM32F10X_HD */  

#ifdef STM32F10X_HD_VL
  IRQn_ADC1                   = 18,     /*!< ADC1 global Interrupt                                */
  IRQn_EXTI9_5                = 23,     /*!< External Line[9:5] Interrupts                        */
  IRQn_TIM1_BRK_TIM15         = 24,     /*!< TIM1 Break and TIM15 Interrupts                      */
  IRQn_TIM1_UP_TIM16          = 25,     /*!< TIM1 Update and TIM16 Interrupts                     */
  IRQn_TIM1_TRG_COM_TIM17     = 26,     /*!< TIM1 Trigger and Commutation and TIM17 Interrupt     */
  IRQn_TIM1_CC                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
  IRQn_TIM2                   = 28,     /*!< TIM2 global Interrupt                                */
  IRQn_TIM3                   = 29,     /*!< TIM3 global Interrupt                                */
  IRQn_TIM4                   = 30,     /*!< TIM4 global Interrupt                                */
  IRQn_I2C1_EV                = 31,     /*!< I2C1 Event Interrupt                                 */
  IRQn_I2C1_ER                = 32,     /*!< I2C1 Error Interrupt                                 */
  IRQn_I2C2_EV                = 33,     /*!< I2C2 Event Interrupt                                 */
  IRQn_I2C2_ER                = 34,     /*!< I2C2 Error Interrupt                                 */
  IRQn_SPI1                   = 35,     /*!< SPI1 global Interrupt                                */
  IRQn_SPI2                   = 36,     /*!< SPI2 global Interrupt                                */
  IRQn_USART1                 = 37,     /*!< USART1 global Interrupt                              */
  IRQn_USART2                 = 38,     /*!< USART2 global Interrupt                              */
  IRQn_USART3                 = 39,     /*!< USART3 global Interrupt                              */
  IRQn_EXTI15_10              = 40,     /*!< External Line[15:10] Interrupts                      */
  IRQn_RTCAlarm               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
  IRQn_CEC                    = 42,     /*!< HDMI-CEC Interrupt                                   */
  IRQn_TIM12                  = 43,     /*!< TIM12 global Interrupt                               */
  IRQn_TIM13                  = 44,     /*!< TIM13 global Interrupt                               */
  IRQn_TIM14                  = 45,     /*!< TIM14 global Interrupt                               */
  IRQn_TIM5                   = 50,     /*!< TIM5 global Interrupt                                */
  IRQn_SPI3                   = 51,     /*!< SPI3 global Interrupt                                */
  IRQn_UART4                  = 52,     /*!< UART4 global Interrupt                               */
  IRQn_UART5                  = 53,     /*!< UART5 global Interrupt                               */
  IRQn_TIM6_DAC               = 54,     /*!< TIM6 and DAC underrun Interrupt                      */
  IRQn_TIM7                   = 55,     /*!< TIM7 Interrupt                                       */
  IRQn_DMA2_Channel1          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
  IRQn_DMA2_Channel2          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
  IRQn_DMA2_Channel3          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
  IRQn_DMA2_Channel4_5        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
  IRQn_DMA2_Channel5          = 60      /*!< DMA2 Channel 5 global Interrupt (DMA2 Channel 5 is
                                             mapped at position 60 only if the MISC_REMAP bit in 
                                             the AFIO_MAPR2 register is set)                      */       
#endif /* STM32F10X_HD_VL */

#ifdef STM32F10X_XL
  IRQn_ADC1_2                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
  IRQn_USB_HP_CAN1_TX         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
  IRQn_USB_LP_CAN1_RX0        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
  IRQn_CAN1_RX1               = 21,     /*!< CAN1 RX1 Interrupt                                   */
  IRQn_CAN1_SCE               = 22,     /*!< CAN1 SCE Interrupt                                   */
  IRQn_EXTI9_5                = 23,     /*!< External Line[9:5] Interrupts                        */
  IRQn_TIM1_BRK_TIM9          = 24,     /*!< TIM1 Break Interrupt and TIM9 global Interrupt       */
  IRQn_TIM1_UP_TIM10          = 25,     /*!< TIM1 Update Interrupt and TIM10 global Interrupt     */
  IRQn_TIM1_TRG_COM_TIM11     = 26,     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
  IRQn_TIM1_CC                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
  IRQn_TIM2                   = 28,     /*!< TIM2 global Interrupt                                */
  IRQn_TIM3                   = 29,     /*!< TIM3 global Interrupt                                */
  IRQn_TIM4                   = 30,     /*!< TIM4 global Interrupt                                */
  IRQn_I2C1_EV                = 31,     /*!< I2C1 Event Interrupt                                 */
  IRQn_I2C1_ER                = 32,     /*!< I2C1 Error Interrupt                                 */
  IRQn_I2C2_EV                = 33,     /*!< I2C2 Event Interrupt                                 */
  IRQn_I2C2_ER                = 34,     /*!< I2C2 Error Interrupt                                 */
  IRQn_SPI1                   = 35,     /*!< SPI1 global Interrupt                                */
  IRQn_SPI2                   = 36,     /*!< SPI2 global Interrupt                                */
  IRQn_USART1                 = 37,     /*!< USART1 global Interrupt                              */
  IRQn_USART2                 = 38,     /*!< USART2 global Interrupt                              */
  IRQn_USART3                 = 39,     /*!< USART3 global Interrupt                              */
  IRQn_EXTI15_10              = 40,     /*!< External Line[15:10] Interrupts                      */
  IRQn_RTCAlarm               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
  IRQn_USBWakeUp              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
  IRQn_TIM8_BRK_TIM12         = 43,     /*!< TIM8 Break Interrupt and TIM12 global Interrupt      */
  IRQn_TIM8_UP_TIM13          = 44,     /*!< TIM8 Update Interrupt and TIM13 global Interrupt     */
  IRQn_TIM8_TRG_COM_TIM14     = 45,     /*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
  IRQn_TIM8_CC                = 46,     /*!< TIM8 Capture Compare Interrupt                       */
  IRQn_ADC3                   = 47,     /*!< ADC3 global Interrupt                                */
  IRQn_FSMC                   = 48,     /*!< FSMC global Interrupt                                */
  IRQn_SDIO                   = 49,     /*!< SDIO global Interrupt                                */
  IRQn_TIM5                   = 50,     /*!< TIM5 global Interrupt                                */
  IRQn_SPI3                   = 51,     /*!< SPI3 global Interrupt                                */
  IRQn_UART4                  = 52,     /*!< UART4 global Interrupt                               */
  IRQn_UART5                  = 53,     /*!< UART5 global Interrupt                               */
  IRQn_TIM6                   = 54,     /*!< TIM6 global Interrupt                                */
  IRQn_TIM7                   = 55,     /*!< TIM7 global Interrupt                                */
  IRQn_DMA2_Channel1          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
  IRQn_DMA2_Channel2          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
  IRQn_DMA2_Channel3          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
  IRQn_DMA2_Channel4_5        = 59      /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
#endif /* STM32F10X_XL */  

#ifdef STM32F10X_CL
  IRQn_ADC1_2                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
  IRQn_CAN1_TX                = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
  IRQn_CAN1_RX0               = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
  IRQn_CAN1_RX1               = 21,     /*!< CAN1 RX1 Interrupt                                   */
  IRQn_CAN1_SCE               = 22,     /*!< CAN1 SCE Interrupt                                   */
  IRQn_EXTI9_5                = 23,     /*!< External Line[9:5] Interrupts                        */
  IRQn_TIM1_BRK               = 24,     /*!< TIM1 Break Interrupt                                 */
  IRQn_TIM1_UP                = 25,     /*!< TIM1 Update Interrupt                                */
  IRQn_TIM1_TRG_COM           = 26,     /*!< TIM1 Trigger and Commutation Interrupt               */
  IRQn_TIM1_CC                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
  IRQn_TIM2                   = 28,     /*!< TIM2 global Interrupt                                */
  IRQn_TIM3                   = 29,     /*!< TIM3 global Interrupt                                */
  IRQn_TIM4                   = 30,     /*!< TIM4 global Interrupt                                */
  IRQn_I2C1_EV                = 31,     /*!< I2C1 Event Interrupt                                 */
  IRQn_I2C1_ER                = 32,     /*!< I2C1 Error Interrupt                                 */
  IRQn_I2C2_EV                = 33,     /*!< I2C2 Event Interrupt                                 */
  IRQn_I2C2_ER                = 34,     /*!< I2C2 Error Interrupt                                 */
  IRQn_SPI1                   = 35,     /*!< SPI1 global Interrupt                                */
  IRQn_SPI2                   = 36,     /*!< SPI2 global Interrupt                                */
  IRQn_USART1                 = 37,     /*!< USART1 global Interrupt                              */
  IRQn_USART2                 = 38,     /*!< USART2 global Interrupt                              */
  IRQn_USART3                 = 39,     /*!< USART3 global Interrupt                              */
  IRQn_EXTI15_10              = 40,     /*!< External Line[15:10] Interrupts                      */
  IRQn_RTCAlarm               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
  IRQn_OTG_FS_WKUP            = 42,     /*!< USB OTG FS WakeUp from suspend through EXTI Line Interrupt */
  IRQn_TIM5                   = 50,     /*!< TIM5 global Interrupt                                */
  IRQn_SPI3                   = 51,     /*!< SPI3 global Interrupt                                */
  IRQn_UART4                  = 52,     /*!< UART4 global Interrupt                               */
  IRQn_UART5                  = 53,     /*!< UART5 global Interrupt                               */
  IRQn_TIM6                   = 54,     /*!< TIM6 global Interrupt                                */
  IRQn_TIM7                   = 55,     /*!< TIM7 global Interrupt                                */
  IRQn_DMA2_Channel1          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
  IRQn_DMA2_Channel2          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
  IRQn_DMA2_Channel3          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
  IRQn_DMA2_Channel4          = 59,     /*!< DMA2 Channel 4 global Interrupt                      */
  IRQn_DMA2_Channel5          = 60,     /*!< DMA2 Channel 5 global Interrupt                      */
  IRQn_ETH                    = 61,     /*!< Ethernet global Interrupt                            */
  IRQn_ETH_WKUP               = 62,     /*!< Ethernet Wakeup through EXTI line Interrupt          */
  IRQn_CAN2_TX                = 63,     /*!< CAN2 TX Interrupt                                    */
  IRQn_CAN2_RX0               = 64,     /*!< CAN2 RX0 Interrupt                                   */
  IRQn_CAN2_RX1               = 65,     /*!< CAN2 RX1 Interrupt                                   */
  IRQn_CAN2_SCE               = 66,     /*!< CAN2 SCE Interrupt                                   */
  IRQn_OTG_FS                 = 67,      /*!< USB OTG FS global Interrupt                          */
#endif /* STM32F10X_CL */     
} IRQn_Type;



#endif
