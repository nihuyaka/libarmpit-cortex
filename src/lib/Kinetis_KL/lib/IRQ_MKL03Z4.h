typedef enum IRQn {
  /* Core interrupts */
  IRQn_NonMaskableInt          = -14,              /**< Non Maskable Interrupt */
  IRQn_HardFault               = -13,              /**< Cortex-M0 SV Hard Fault Interrupt */
  IRQn_SVCall                  = -5,               /**< Cortex-M0 SV Call Interrupt */
  IRQn_PendSV                  = -2,               /**< Cortex-M0 Pend SV Interrupt */
  IRQn_SysTick                 = -1,               /**< Cortex-M0 System Tick Interrupt */

  /* Device specific interrupts */
  IRQn_Reserved16              = 0,                /**< Reserved interrupt */
  IRQn_Reserved17              = 1,                /**< Reserved interrupt */
  IRQn_Reserved18              = 2,                /**< Reserved interrupt */
  IRQn_Reserved19              = 3,                /**< Reserved interrupt */
  IRQn_Reserved20              = 4,                /**< Reserved interrupt */
  IRQn_FTFA                    = 5,                /**< Command complete and read collision */
  IRQn_PMC                     = 6,                /**< Low-voltage detect, low-voltage warning */
  IRQn_LLWU                    = 7,                /**< Low leakage wakeup */
  IRQn_I2C0                    = 8,                /**< I2C0 interrupt */
  IRQn_Reserved25              = 9,                /**< Reserved interrupt */
  IRQn_SPI0                    = 10,               /**< SPI0 single interrupt vector for all sources */
  IRQn_Reserved27              = 11,               /**< Reserved interrupt */
  IRQn_LPUART0                 = 12,               /**< LPUART0 status and error */
  IRQn_Reserved29              = 13,               /**< Reserved interrupt */
  IRQn_Reserved30              = 14,               /**< Reserved interrupt */
  IRQn_ADC0                    = 15,               /**< ADC0 interrupt */
  IRQn_CMP0                    = 16,               /**< CMP0 interrupt */
  IRQn_TPM0                    = 17,               /**< TPM0 single interrupt vector for all sources */
  IRQn_TPM1                    = 18,               /**< TPM1 single interrupt vector for all sources */
  IRQn_Reserved35              = 19,               /**< Reserved interrupt */
  IRQn_RTC                     = 20,               /**< RTC alarm */
  IRQn_RTC_Seconds             = 21,               /**< RTC seconds */
  IRQn_Reserved38              = 22,               /**< Reserved interrupt */
  IRQn_Reserved39              = 23,               /**< Reserved interrupt */
  IRQn_Reserved40              = 24,               /**< Reserved interrupt */
  IRQn_Reserved41              = 25,               /**< Reserved interrupt */
  IRQn_Reserved42              = 26,               /**< Reserved interrupt */
  IRQn_Reserved43              = 27,               /**< Reserved interrupt */
  IRQn_LPTMR0                  = 28,               /**< LPTMR0 interrupt */
  IRQn_Reserved45              = 29,               /**< Reserved interrupt */
  IRQn_PORTA                   = 30,               /**< PORTA Pin detect */
  IRQn_PORTB                   = 31                /**< PORTB Pin detect */
} IRQn_Type;
