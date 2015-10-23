typedef enum
{
/******  Cortex-M0 Processor Exceptions Numbers ******************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                */
  HardFault_IRQn              = -13,    /*!< 3 Cortex-M0+ Hard Fault Interrupt                        */
  SVC_IRQn                    = -5,     /*!< 11 Cortex-M0+ SV Call Interrupt                          */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M0+ Pend SV Interrupt                          */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M0+ System Tick Interrupt                      */

/******  STM32L-0 specific Interrupt Numbers *********************************************************/
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                     */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detect Interrupt                        */
  RTC_IRQn                    = 2,      /*!< RTC through EXTI Line Interrupt                               */
  FLASH_IRQn                  = 3,      /*!< FLASH Interrupt                                               */
  RCC_CRS_IRQn                = 4,      /*!< RCC and CRS Interrupts                                        */
  EXTI0_1_IRQn                = 5,      /*!< EXTI Line 0 and 1 Interrupts                                  */
  EXTI2_3_IRQn                = 6,      /*!< EXTI Line 2 and 3 Interrupts                                  */
  EXTI4_15_IRQn               = 7,      /*!< EXTI Line 4 to 15 Interrupts                                  */
  TSC_IRQn                    = 8,      /*!< TSC Interrupt                                                  */
  DMA1_Channel1_IRQn          = 9,      /*!< DMA1 Channel 1 Interrupt                                      */
  DMA1_Channel2_3_IRQn        = 10,     /*!< DMA1 Channel 2 and Channel 3 Interrupts                       */
  DMA1_Channel4_5_6_7_IRQn    = 11,     /*!< DMA1 Channel 4, Channel 5, Channel 6 and Channel 7 Interrupts */
  ADC1_COMP_IRQn              = 12,     /*!< ADC1, COMP1 and COMP2 Interrupts                              */
  LPTIM1_IRQn                 = 13,     /*!< LPTIM1 Interrupt                                              */
  TIM2_IRQn                   = 15,     /*!< TIM2 Interrupt                                                */
  TIM6_DAC_IRQn               = 17,     /*!< TIM6 and DAC Interrupts                                       */
  TIM21_IRQn                   = 20,     /*!< TIM21 Interrupt                                               */
  TIM22_IRQn                  = 22,     /*!< TIM22 Interrupt                                               */
  I2C1_IRQn                   = 23,     /*!< I2C1 Interrupt                                                */
  I2C2_IRQn                   = 24,     /*!< I2C2 Interrupt                                                */
  SPI1_IRQn                   = 25,     /*!< SPI1 Interrupt                                                */
  SPI2_IRQn                   = 26,     /*!< SPI2 Interrupt                                                */
  USART1_IRQn                 = 27,     /*!< USART1 Interrupt                                              */
  USART2_IRQn                 = 28,     /*!< USART2 Interrupt                                              */
  AES_RNG_LPUART1_IRQn        = 29,     /*!< AES and RNG and LPUART1 Interrupts                            */
  USB_IRQn                    = 31      /*!< USB global Interrupt                                          */
} IRQn_Type;
