typedef enum IRQn {
  /* Core interrupts */
  IRQn_NonMaskableInt          = -14,              /**< Non Maskable Interrupt */
  IRQn_HardFault               = -13,              /**< Cortex-M0 SV Hard Fault Interrupt */
  IRQn_SVCall                  = -5,               /**< Cortex-M0 SV Call Interrupt */
  IRQn_PendSV                  = -2,               /**< Cortex-M0 Pend SV Interrupt */
  IRQn_SysTick                 = -1,               /**< Cortex-M0 System Tick Interrupt */

  /* Device specific interrupts */
  IRQn_DMA0_0                  = 0,                /**< DMA0 channel 0 transfer complete */
  IRQn_DMA0_1                  = 1,                /**< DMA0 channel 1 transfer complete */
  IRQn_DMA0_2                  = 2,                /**< DMA0 channel 2 transfer complete */
  IRQn_DMA0_3                  = 3,                /**< DMA0 channel 3 transfer complete */
  IRQn_CTI0_DMA0_Error         = 4,                /**< CTI0 or DMA0 error */
  IRQn_FLEXIO                  = 5,                /**< FLEXIO */
  IRQn_TPM0                    = 6,                /**< TPM0 single interrupt vector for all sources */
  IRQn_TPM1                    = 7,                /**< TPM1 single interrupt vector for all sources */
  IRQn_TPM2                    = 8,                /**< TPM2 single interrupt vector for all sources */
  IRQn_PIT0                    = 9,                /**< PIT0 interrupt */
  IRQn_LPSPI0                  = 10,               /**< LPSPI0 single interrupt vector for all sources */
  IRQn_LPSPI1                  = 11,               /**< LPSPI1 single interrupt vector for all sources */
  IRQn_LPUART0                 = 12,               /**< LPUART0 status and error */
  IRQn_LPUART1                 = 13,               /**< LPUART1 status and error */
  IRQn_LPI2C0                  = 14,               /**< LPI2C0 interrupt */
  IRQn_LPI2C1                  = 15,               /**< LPI2C1 interrupt */
  IRQn_Reserved32              = 16,               /**< Reserved interrupt */
  IRQn_PORTA                   = 17,               /**< PORTA Pin detect */
  IRQn_PORTB                   = 18,               /**< PORTB Pin detect */
  IRQn_PORTC                   = 19,               /**< PORTC Pin detect */
  IRQn_PORTD                   = 20,               /**< PORTD Pin detect */
  IRQn_PORTE                   = 21,               /**< PORTE Pin detect */
  IRQn_Reserved38              = 22,               /**< Reserved interrupt */
  IRQn_I2S0                    = 23,               /**< I2S0 interrupt */
  IRQn_USB0                    = 24,               /**< USB0 interrupt */
  IRQn_ADC0                    = 25,               /**< ADC0 interrupt */
  IRQn_LPTMR0                  = 26,               /**< LPTMR0 interrupt */
  IRQn_RTC_Seconds             = 27,               /**< RTC seconds */
  IRQn_INTMUX0_0               = 28,               /**< INTMUX0_0 interrupt */
  IRQn_INTMUX0_1               = 29,               /**< INTMUX0_1 interrupt */
  IRQn_INTMUX0_2               = 30,               /**< INTMUX0_2 interrupt */
  IRQn_INTMUX0_3               = 31                /**< INTMUX0_3 interrupt */
} IRQn_Type;
