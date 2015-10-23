#ifndef _GPIO_HELPER_H
#define _GPIO_HELPER_H

#include "spi_cpp.h"

#ifdef USE_TIMER
#include "timer_cpp.h"
#endif

#ifdef USE_I2C
#include "i2c_cpp.h"
#endif

#ifdef USE_USART
#include "usart_cpp.h"
#endif

#include "gpio_cpp.h"

class GPIO_Helper
{
public:
#ifdef USE_SPI
    static SPI* SetupSPIx (bool isMasterMode, bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate,
                                GPIO_PORT* port,  GPIO_PIN_N clkPin, GPIO_PIN_N misoPin, GPIO_PIN_N mosiPin, SPI* spi, GPIO_AF af);

    static SPI1* SetupSPI1_MasterMode_PA_5_6_7(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate);
    static SPI1* SetupSPI1_MasterMode_PB_3_4_5(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate);
    static SPI2* SetupSPI2_MasterMode_PB_13_14_15(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate);
    static SPI3* SetupSPI3_MasterMode_PB_3_4_5(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate);
    static SPI3* SetupSPI3_MasterMode_PC_10_11_12(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate);

#endif


#ifdef USE_TIMER
    static void   SetupTIMx(GPIO_PORT* port, GPIO_PIN_N ch0, GPIO_PIN_N ch1, GPIO_PIN_N ch2, GPIO_PIN_N ch3, GPIO_AF af);
    static TIM1*  SetupTIM1_PA_8_9_10_11();
    static TIM2*  SetupTIM2_PA_0_1_2_3();
    static TIM3*  SetupTIM3_PC_6_7_8_9();
    static TIM3*  SetupTIM3_PB_4_5_0_1();
    static TIM4*  SetupTIM4_PD_12_13_14_15();
    static TIM4*  SetupTIM4_PB_6_7_8_9();
    static TIM5*  SetupTIM5_PA_0_1_2_3();
#if !defined(STM32F401xC)  && !defined(STM32F401xE) && !defined(STM32F401xx) && !defined(STM32F411xE)
    static TIM8*  SetupTIM8_PC_6_7_8_9();
#endif		
#endif

#ifdef USE_I2C
    static I2C* SetupI2Cx(I2C* i2c, GPIO_PORT* port, GPIO_PIN_N sckPinNo, GPIO_PIN_N sdaPinNo, GPIO_AF afno,
    		DMA_CHANNEL txChannel, DMA_CHANNEL rxChannel,
    		DMA_STREAM_N txStreamNo, DMA_STREAM_N rxStreamNo, uint32_t clockSpeed);
    static I2C1*  SetupI2C1_PB_6_9(uint32_t clockSpeed);
    static I2C1*  SetupI2C1_PB_6_7(uint32_t clockSpeed);
    static I2C1*  SetupI2C1_PB_8_9(uint32_t clockSpeed);
    static I2C2*  SetupI2C2_PB10_11(uint32_t clockSpeed);
#endif

#ifdef USE_USART
    static USART*  SetupUSARTx(GPIO_PORT* port, GPIO_PIN_N txPin, GPIO_PIN_N rxPin, GPIO_AF af, USART* usart, uint32_t clockSpeed);
    static USART1* SetupUSART1_PA_9_10(uint32_t clockSpeed);
    static USART1* SetupUSART1_PB_6_7(uint32_t clockSpeed);
    static USART2* SetupUSART2_PA_2_3(uint32_t clockSpeed);
    static USART2* SetupUSART2_PD_5_6(uint32_t clockSpeed);

#if defined(STM32F10X_MD) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL) \
|| defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || defined(STM32F427xx) || defined(STM32F437xx) \
|| defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F446xx)

    static USART3* SetupUSART3_PB_10_11(uint32_t clockSpeed);
    static USART3* SetupUSART3_PC_10_11(uint32_t clockSpeed);

#endif

#if defined(STM32F4)
    static USART6* SetupUSART3_PC_6_7(uint32_t clockSpeed);
    static USART6* SetupUSART3_PG_14_9(uint32_t clockSpeed);
#endif


#endif //USE_USART




};

#endif


