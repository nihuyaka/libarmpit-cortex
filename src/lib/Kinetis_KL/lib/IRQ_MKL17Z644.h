typedef enum IRQn {
  /* Core interrupts */
  IRQn_NonMaskableInt          = -14,              /**< Non Maskable Interrupt */
  IRQn_HardFault               = -13,              /**< Cortex-M0 SV Hard Fault Interrupt */
  IRQn_SVCall                  = -5,               /**< Cortex-M0 SV Call Interrupt */
  IRQn_PendSV                  = -2,               /**< Cortex-M0 Pend SV Interrupt */
  IRQn_SysTick                 = -1,               /**< Cortex-M0 System Tick Interrupt */

  /* Device specific interrupts */
  IRQn_DMA0                    = 0,                /**< DMA channel 0 transfer complete */
  IRQn_DMA1                    = 1,                /**< DMA channel 1 transfer complete */
  IRQn_DMA2                    = 2,                /**< DMA channel 2 transfer complete */
  IRQn_DMA3                    = 3,                /**< DMA channel 3 transfer complete */
  IRQn_Reserved20              = 4,                /**< Reserved interrupt */
  IRQn_FTFA                    = 5,                /**< Command complete and read collision */
  IRQn_PMC                     = 6,                /**< Low-voltage detect, low-voltage warning */
  IRQn_LLWU                    = 7,                /**< Low leakage wakeup */
  IRQn_I2C0                    = 8,                /**< I2C0 interrupt */
  IRQn_I2C1                    = 9,                /**< I2C1 interrupt */
  IRQn_SPI0                    = 10,               /**< SPI0 single interrupt vector for all sources */
  IRQn_SPI1                    = 11,               /**< SPI1 single interrupt vector for all sources */
  IRQn_LPUART0                 = 12,               /**< LPUART0 status and error */
  IRQn_LPUART1                 = 13,               /**< LPUART1 status and error */
  IRQn_UART2_FLEXIO            = 14,               /**< UART2 or FLEXIO */
  IRQn_ADC0                    = 15,               /**< ADC0 interrupt */
  IRQn_CMP0                    = 16,               /**< CMP0 interrupt */
  IRQn_TPM0                    = 17,               /**< TPM0 single interrupt vector for all sources */
  IRQn_TPM1                    = 18,               /**< TPM1 single interrupt vector for all sources */
  IRQn_TPM2                    = 19,               /**< TPM2 single interrupt vector for all sources */
  IRQn_RTC                     = 20,               /**< RTC alarm */
  IRQn_RTC_Seconds             = 21,               /**< RTC seconds */
  IRQn_PIT                     = 22,               /**< PIT interrupt */
  IRQn_Reserved39              = 23,               /**< Reserved interrupt */
  IRQn_Reserved40              = 24,               /**< Reserved interrupt */
  IRQn_Reserved41              = 25,               /**< Reserved interrupt */
  IRQn_Reserved42              = 26,               /**< Reserved interrupt */
  IRQn_Reserved43              = 27,               /**< Reserved interrupt */
  IRQn_LPTMR0                  = 28,               /**< LPTMR0 interrupt */
  IRQn_Reserved45              = 29,               /**< Reserved interrupt */
  IRQn_PORTA                   = 30,               /**< PORTA Pin detect */
  IRQn_PORTBCDE                = 31                /**< Single interrupt vector for PORTB,PORTC,PORTD,PORTE */
} IRQn_Type;
