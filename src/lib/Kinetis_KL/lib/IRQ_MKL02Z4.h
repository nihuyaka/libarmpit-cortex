typedef enum IRQn {
  /* Core interrupts */
  IRQn_NonMaskableInt          = -14,              /**< Non Maskable Interrupt */
  IRQn_HardFault               = -13,              /**< Cortex-M0 SV Hard Fault Interrupt */
  IRQn_SVCall                  = -5,               /**< Cortex-M0 SV Call Interrupt */
  IRQn_PendSV                  = -2,               /**< Cortex-M0 Pend SV Interrupt */
  IRQn_SysTick                 = -1,               /**< Cortex-M0 System Tick Interrupt */

  /* Device specific interrupts */
  IRQn_Reserved16              = 0,                /**< Reserved interrupt 16 */
  IRQn_Reserved17              = 1,                /**< Reserved interrupt 17 */
  IRQn_Reserved18              = 2,                /**< Reserved interrupt 18 */
  IRQn_Reserved19              = 3,                /**< Reserved interrupt 19 */
  IRQn_Reserved20              = 4,                /**< Reserved interrupt 20 */
  IRQn_FTFA                    = 5,                /**< FTFA command complete/read collision interrupt */
  IRQn_LVD_LVW                 = 6,                /**< Low Voltage Detect, Low Voltage Warning */
  IRQn_Reserved23              = 7,                /**< Reserved interrupt 23 */
  IRQn_I2C0                    = 8,                /**< I2C0 interrupt */
  IRQn_I2C1                    = 9,                /**< I2C1 interrupt */
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
  IRQn_Reserved36              = 20,               /**< Reserved interrupt 36 */
  IRQn_Reserved37              = 21,               /**< Reserved interrupt 37 */
  IRQn_Reserved38              = 22,               /**< Reserved interrupt 38 */
  IRQn_Reserved39              = 23,               /**< Reserved interrupt 39 */
  IRQn_Reserved40              = 24,               /**< Reserved interrupt 40 */
  IRQn_Reserved41              = 25,               /**< Reserved interrupt 41 */
  IRQn_Reserved42              = 26,               /**< Reserved interrupt 42 */
  IRQn_MCG                     = 27,               /**< MCG interrupt */
  IRQn_LPTimer                 = 28,               /**< LPTimer interrupt */
  IRQn_Reserved45              = 29,               /**< Reserved interrupt 45 */
  IRQn_PORTA                   = 30,               /**< Port A interrupt */
  IRQn_PORTB                   = 31                /**< Port B interrupt */
} IRQn_Type;

