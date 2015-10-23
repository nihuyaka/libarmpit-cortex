typedef enum IRQn {
  /* Core interrupts */
  IRQn_NonMaskableInt          = -14,              /**< Non Maskable Interrupt */
  IRQn_HardFault               = -13,              /**< Cortex-M0 SV Hard Fault Interrupt */
  IRQn_SVCall                  = -5,               /**< Cortex-M0 SV Call Interrupt */
  IRQn_PendSV                  = -2,               /**< Cortex-M0 Pend SV Interrupt */
  IRQn_SysTick                 = -1,               /**< Cortex-M0 System Tick Interrupt */

  /* Device specific interrupts */
  IRQn_DMA0                    = 0,                /**< DMA channel 0 transfer complete/error interrupt */
  IRQn_DMA1                    = 1,                /**< DMA channel 1 transfer complete/error interrupt */
  IRQn_DMA2                    = 2,                /**< DMA channel 2 transfer complete/error interrupt */
  IRQn_DMA3                    = 3,                /**< DMA channel 3 transfer complete/error interrupt */
  IRQn_Reserved20              = 4,                /**< Reserved interrupt 20 */
  IRQn_FTFA                    = 5,                /**< FTFA command complete/read collision interrupt */
  IRQn_LVD_LVW                 = 6,                /**< Low Voltage Detect, Low Voltage Warning */
  IRQn_LLW                     = 7,                /**< Low Leakage Wakeup */
  IRQn_I2C0                    = 8,                /**< I2C0 interrupt */
  IRQn_Reserved25              = 9,                /**< Reserved interrupt 25 */
  IRQn_SPI0                    = 10,               /**< SPI0 interrupt */
  IRQn_Reserved27              = 11,               /**< Reserved interrupt 27 */
  IRQn_UART0                   = 12,               /**< UART0 status/error interrupt */
  IRQn_Reserved29              = 13,               /**< Reserved interrupt 29 */
  IRQn_Reserved30              = 14,               /**< Reserved interrupt 30 */
  IRQn_ADC0                    = 15,               /**< ADC0 interrupt */
  IRQn_CMP0                    = 16,               /**< CMP0 interrupt */
  IRQn_TPM0                    = 17,               /**< TPM0 fault, overflow and channels interrupt */
  IRQn_TPM1                    = 18,               /**< TPM1 fault, overflow and channels interrupt */
  IRQn_Reserved35              = 19,               /**< Reserved interrupt 35 */
  IRQn_RTC                     = 20,               /**< RTC interrupt */
  IRQn_RTC_Seconds             = 21,               /**< RTC seconds interrupt */
  IRQn_PIT                     = 22,               /**< PIT timer interrupt */
  IRQn_Reserved39              = 23,               /**< Reserved interrupt 39 */
  IRQn_Reserved40              = 24,               /**< Reserved interrupt 40 */
  IRQn_DAC0                    = 25,               /**< DAC0 interrupt */
  IRQn_TSI0                    = 26,               /**< TSI0 interrupt */
  IRQn_MCG                     = 27,               /**< MCG interrupt */
  IRQn_LPTimer                 = 28,               /**< LPTimer interrupt */
  IRQn_Reserved45              = 29,               /**< Reserved interrupt 45 */
  IRQn_PORTA                   = 30,               /**< Port A interrupt */
  IRQn_PORTB                   = 31                /**< Port B interrupt */
} IRQn_Type;
