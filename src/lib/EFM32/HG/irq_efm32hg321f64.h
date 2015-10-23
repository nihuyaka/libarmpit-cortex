typedef enum IRQn
{
/******  Cortex-M0+ Processor Exceptions Numbers *****************************************/
  NonMaskableInt_IRQn = -14,                /*!< 2 Cortex-M0+ Non Maskable Interrupt     */
  HardFault_IRQn      = -13,                /*!< 3 Cortex-M0+ Hard Fault Interrupt       */
  SVCall_IRQn         = -5,                 /*!< 11 Cortex-M0+ SV Call Interrupt         */
  PendSV_IRQn         = -2,                 /*!< 14 Cortex-M0+ Pend SV Interrupt         */
  SysTick_IRQn        = -1,                 /*!< 15 Cortex-M0+ System Tick Interrupt     */

/******  EFM32HG Peripheral Interrupt Numbers *********************************************/
  DMA_IRQn            = 0,  /*!< 16+0 EFM32 DMA Interrupt */
  GPIO_EVEN_IRQn      = 1,  /*!< 16+1 EFM32 GPIO_EVEN Interrupt */
  TIMER0_IRQn         = 2,  /*!< 16+2 EFM32 TIMER0 Interrupt */
  ACMP0_IRQn          = 3,  /*!< 16+3 EFM32 ACMP0 Interrupt */
  ADC0_IRQn           = 4,  /*!< 16+4 EFM32 ADC0 Interrupt */
  I2C0_IRQn           = 5,  /*!< 16+5 EFM32 I2C0 Interrupt */
  GPIO_ODD_IRQn       = 6,  /*!< 16+6 EFM32 GPIO_ODD Interrupt */
  TIMER1_IRQn         = 7,  /*!< 16+7 EFM32 TIMER1 Interrupt */
  USART1_RX_IRQn      = 8,  /*!< 16+8 EFM32 USART1_RX Interrupt */
  USART1_TX_IRQn      = 9,  /*!< 16+9 EFM32 USART1_TX Interrupt */
  LEUART0_IRQn        = 10, /*!< 16+10 EFM32 LEUART0 Interrupt */
  PCNT0_IRQn          = 11, /*!< 16+11 EFM32 PCNT0 Interrupt */
  RTC_IRQn            = 12, /*!< 16+12 EFM32 RTC Interrupt */
  CMU_IRQn            = 13, /*!< 16+13 EFM32 CMU Interrupt */
  VCMP_IRQn           = 14, /*!< 16+14 EFM32 VCMP Interrupt */
  MSC_IRQn            = 15, /*!< 16+15 EFM32 MSC Interrupt */
  USART0_RX_IRQn      = 17, /*!< 16+17 EFM32 USART0_RX Interrupt */
  USART0_TX_IRQn      = 18, /*!< 16+18 EFM32 USART0_TX Interrupt */
  USB_IRQn            = 19, /*!< 16+19 EFM32 USB Interrupt */
  TIMER2_IRQn         = 20, /*!< 16+20 EFM32 TIMER2 Interrupt */
} IRQn_Type;
