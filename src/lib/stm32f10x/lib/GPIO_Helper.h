#ifndef _GPIO_HELPER_H
#define _GPIO_HELPER_H

#ifdef USE_SPI
#include "spi_cpp.h"
#endif

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
                                GPIO_PORT* port,  GPIO_PIN_N clkPin, GPIO_PIN_N misoPin, GPIO_PIN_N mosiPin, SPI* spi);

    static SPI1* SetupSPI1_MasterMode_PA_5_6_7(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate);
    static SPI1* SetupSPI1_MasterMode_PB_3_4_5(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate);
#if defined(STM32F10X_MD) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD)\
        || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL)
    static SPI2* SetupSPI2_MasterMode_PB_13_14_15(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate);
#endif

#if defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL)
    static SPI3* SetupSPI3_MasterMode_PB_3_4_5(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate);
#endif

#endif


#ifdef USE_TIMER
    static void   SetupTIMx(GPIO_PIN* ch0, GPIO_PIN* ch1, GPIO_PIN* ch2, GPIO_PIN* ch3);
    static TIM1*  SetupTIM1_PA_8_9_10_11();
    static TIM1*  SetupTIM1_PE_9_11_13_14();
    static TIM2*  SetupTIM2_PA_0_1_2_3();
    static TIM2*  SetupTIM2_PA_15_PB_3_10_11();
    static TIM3*  SetupTIM3_PA6_PA7_PB0_PB1();
    static TIM3*  SetupTIM3_PC_6_7_8_9();
    static TIM3*  SetupTIM3_PB_4_5_0_1();
#if !defined(STM32F10X_LD) && !defined(STM32F10X_LD_VL)
    static TIM4*  SetupTIM4_PD_12_13_14_15();
    static TIM4*  SetupTIM4_PB_6_7_8_9();
#endif
#if defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL)
    static TIM5*  SetupTIM5_PA_0_1_2_3();
#endif
#if defined(STM32F10X_XL) || defined(STM32F10X_HD)
    static TIM8*  SetupTIM8_PC_6_7_8_9();
#endif
#endif

#ifdef USE_I2C
    static I2C*   SetupI2Cx (I2C* i2c, uint32_t clockSpeed,  GPIO_PORT* port,  GPIO_PIN_N sdaPin, GPIO_PIN_N sclPin);
    static I2C1*  SetupI2C1_PB_6_7(uint32_t clockSpeed);
    static I2C1*  SetupI2C1_PB_8_9(uint32_t clockSpeed);
#endif

#ifdef USE_USART
    static USART*  SetupUSARTx(GPIO_PORT* port, GPIO_PIN_N txPin, GPIO_PIN_N rxPin, USART* usart, uint32_t clockSpeed);
    static USART1* SetupUSART1_PA_9_10(uint32_t clockSpeed);
    static USART1* SetupUSART1_PB_6_7(uint32_t clockSpeed);
    static USART2* SetupUSART2_PA_2_3(uint32_t clockSpeed);
    static USART2* SetupUSART2_PD_5_6(uint32_t clockSpeed);
    static USART3* SetupUSART3_PB_10_11(uint32_t clockSpeed);
    static USART3* SetupUSART3_PC_10_11(uint32_t clockSpeed);
    static USART3* SetupUSART3_PD_8_9(uint32_t clockSpeed);

#endif



};

#endif
