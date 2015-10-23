#include "GPIO_Helper.h" 
#include "spi_cpp.h"

#define USE_AFIO
#include "afio.h"


/*
SPI1* GPIO_Helper::F1_SetupSPI1_SlaveMode(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate)
{
    GPIOA::GetInstance()->EnablePeripheralClock(true);
    GPIOA::GetInstance()->SetupGPIO_InFloat(GPIO_PIN5); //CLK
    GPIOA::GetInstance()->SetupGPIO_InPullUp(GPIO_PIN7);//MOSI
    GPIOA::GetInstance()->SetupGPIO_OutAltPP(GPIO_PIN6);

    SPI1* spi1 = SPI1::GetInstance();
    spi1->Enable(true);

    bool isMaster = false;
    bool isFullDuplex = true;
    bool isLSBFirst = false;
    bool isSetSSM = true;

    spi1->Initialize(isMaster, isFullDuplex, baudRate,
            isClockPhase2, isClockPolarity1, isLSBFirst, isSetSSM);

    return spi1;

}
*/




#ifdef USE_SPI

SPI* GPIO_Helper::SetupSPIx (bool isMasterMode, bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate,
        GPIO_PORT* port,  GPIO_PIN_N clkPin, GPIO_PIN_N misoPin, GPIO_PIN_N mosiPin, SPI* spi)
{
    port->EnablePeripheralClock(true);
    GPIO_PIN* CLK_pin = port->GetPin (clkPin);
    GPIO_PIN* MISO_pin = port->GetPin (misoPin);
    GPIO_PIN* MOSI_pin = port->GetPin (mosiPin);

    MOSI_pin->SetupGPIO_OutAltPP();

    CLK_pin->SetupGPIO_OutAltPP();
    MISO_pin->SetupGPIO_InPullUp();

    bool isFullDuplex = true;
    bool isLSBFirst = false;
    bool isSetSSM = true;
    bool is16Bit = false;

    spi->Initialize(isMasterMode, isFullDuplex, baudRate,  isClockPhase2, isClockPolarity1, isLSBFirst, isSetSSM, is16Bit);
    return spi;

}



SPI1* GPIO_Helper::SetupSPI1_MasterMode_PA_5_6_7(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate)
{
    AFIO_Remap_SPI1(false);
    return (SPI1*)SetupSPIx(true, isClockPhase2, isClockPolarity1, baudRate, GPIOA::GetInstance(), GPIO_PIN5, GPIO_PIN6, GPIO_PIN7, SPI1::GetInstance());
}

SPI1* GPIO_Helper::SetupSPI1_MasterMode_PB_3_4_5(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate)
{
    AFIO_Remap_SPI1(true);
    return (SPI1*)SetupSPIx(true, isClockPhase2, isClockPolarity1, baudRate, GPIOB::GetInstance(), GPIO_PIN3, GPIO_PIN4, GPIO_PIN5, SPI1::GetInstance());
}


#if defined(STM32F10X_MD) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD)\
        || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL)

SPI2* GPIO_Helper::SetupSPI2_MasterMode_PB_13_14_15(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate)
{
    return (SPI2*)SetupSPIx(true, isClockPhase2, isClockPolarity1, baudRate, GPIOB::GetInstance(), GPIO_PIN13, GPIO_PIN14, GPIO_PIN15, SPI2::GetInstance());

}
#endif


#if defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL)
SPI3* GPIO_Helper::SetupSPI3_MasterMode_PB_3_4_5(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate)
{
    return (SPI3*)SetupSPIx(true, isClockPhase2, isClockPolarity1, baudRate, GPIOB::GetInstance(), GPIO_PIN3, GPIO_PIN4, GPIO_PIN5, SPI3::GetInstance());

}
#endif



#endif

#ifdef USE_TIMER


TIM1*  GPIO_Helper::SetupTIM1_PA_8_9_10_11()
{
    TIM1* timer = TIM1::GetInstance();
    timer->EnablePeripheralClock(true);
    AFIO_Remap_TIM1(false, false);
    GPIOA::GetInstance()->EnablePeripheralClock(true);
    GPIO_PIN* ch0 = GPIOA::GetInstance()->GetPin(GPIO_PIN8);
    GPIO_PIN* ch1 = GPIOA::GetInstance()->GetPin(GPIO_PIN9);
    GPIO_PIN* ch2 = GPIOA::GetInstance()->GetPin(GPIO_PIN10);
    GPIO_PIN* ch3 = GPIOA::GetInstance()->GetPin(GPIO_PIN11);
    ch0->SetupGPIO_OutAltPP();
    ch1->SetupGPIO_OutAltPP();
    ch2->SetupGPIO_OutAltPP();
    ch3->SetupGPIO_OutAltPP();
    return timer;

}

TIM1*  GPIO_Helper::SetupTIM1_PE_9_11_13_14()
{
    TIM1* timer = TIM1::GetInstance();
    timer->EnablePeripheralClock(true);
    AFIO_Remap_TIM1(true, true);
    GPIOE::GetInstance()->EnablePeripheralClock(true);
    GPIO_PIN* ch0 = GPIOE::GetInstance()->GetPin(GPIO_PIN9);
    GPIO_PIN* ch1 = GPIOE::GetInstance()->GetPin(GPIO_PIN11);
    GPIO_PIN* ch2 = GPIOE::GetInstance()->GetPin(GPIO_PIN13);
    GPIO_PIN* ch3 = GPIOE::GetInstance()->GetPin(GPIO_PIN14);
    ch0->SetupGPIO_OutAltPP();
    ch1->SetupGPIO_OutAltPP();
    ch2->SetupGPIO_OutAltPP();
    ch3->SetupGPIO_OutAltPP();
    return timer;

}


TIM2*  GPIO_Helper::SetupTIM2_PA_0_1_2_3()
{
    TIM2* timer = TIM2::GetInstance();
    timer->EnablePeripheralClock(true);
    AFIO_Remap_TIM2(false, false);
    GPIOA::GetInstance()->EnablePeripheralClock(true);
    GPIO_PIN* ch0 = GPIOA::GetInstance()->GetPin(GPIO_PIN0);
    GPIO_PIN* ch1 = GPIOA::GetInstance()->GetPin(GPIO_PIN1);
    GPIO_PIN* ch2 = GPIOA::GetInstance()->GetPin(GPIO_PIN2);
    GPIO_PIN* ch3 = GPIOA::GetInstance()->GetPin(GPIO_PIN3);
    ch0->SetupGPIO_OutAltPP();
    ch1->SetupGPIO_OutAltPP();
    ch2->SetupGPIO_OutAltPP();
    ch3->SetupGPIO_OutAltPP();
    return timer;

}

TIM2*  GPIO_Helper::SetupTIM2_PA_15_PB_3_10_11()
{
    TIM2* timer = TIM2::GetInstance();
    timer->EnablePeripheralClock(true);
    AFIO_Remap_TIM2(true, true);
    GPIOA::GetInstance()->EnablePeripheralClock(true);
    GPIOB::GetInstance()->EnablePeripheralClock(true);
    GPIO_PIN* ch0 = GPIOA::GetInstance()->GetPin(GPIO_PIN15);
    GPIO_PIN* ch1 = GPIOB::GetInstance()->GetPin(GPIO_PIN3);
    GPIO_PIN* ch2 = GPIOB::GetInstance()->GetPin(GPIO_PIN10);
    GPIO_PIN* ch3 = GPIOB::GetInstance()->GetPin(GPIO_PIN11);
    ch0->SetupGPIO_OutAltPP();
    ch1->SetupGPIO_OutAltPP();
    ch2->SetupGPIO_OutAltPP();
    ch3->SetupGPIO_OutAltPP();
    return timer;

}

TIM3*  GPIO_Helper::SetupTIM3_PA6_PA7_PB0_PB1()
{
    TIM3* timer = TIM3::GetInstance();
    timer->EnablePeripheralClock(true);
    AFIO_Remap_TIM3(false, false);
    GPIOA::GetInstance()->EnablePeripheralClock(true);
    GPIOB::GetInstance()->EnablePeripheralClock(true);
    GPIO_PIN* ch0 = GPIOA::GetInstance()->GetPin(GPIO_PIN6);
    GPIO_PIN* ch1 = GPIOA::GetInstance()->GetPin(GPIO_PIN7);
    GPIO_PIN* ch2 = GPIOB::GetInstance()->GetPin(GPIO_PIN0);
    GPIO_PIN* ch3 = GPIOB::GetInstance()->GetPin(GPIO_PIN1);
    ch0->SetupGPIO_OutAltPP();
    ch1->SetupGPIO_OutAltPP();
    ch2->SetupGPIO_OutAltPP();
    ch3->SetupGPIO_OutAltPP();
    return timer;

}


TIM3*  GPIO_Helper::SetupTIM3_PC_6_7_8_9()
{
    TIM3* timer = TIM3::GetInstance();
    timer->EnablePeripheralClock(true);
    AFIO_Remap_TIM3(true, true);
    GPIOC::GetInstance()->EnablePeripheralClock(true);
    GPIO_PIN* ch0 = GPIOC::GetInstance()->GetPin(GPIO_PIN6);
    GPIO_PIN* ch1 = GPIOC::GetInstance()->GetPin(GPIO_PIN7);
    GPIO_PIN* ch2 = GPIOC::GetInstance()->GetPin(GPIO_PIN8);
    GPIO_PIN* ch3 = GPIOC::GetInstance()->GetPin(GPIO_PIN9);
    ch0->SetupGPIO_OutAltPP();
    ch1->SetupGPIO_OutAltPP();
    ch2->SetupGPIO_OutAltPP();
    ch3->SetupGPIO_OutAltPP();
    return timer;

}

TIM3*  GPIO_Helper::SetupTIM3_PB_4_5_0_1()
{
    TIM3* timer = TIM3::GetInstance();
    timer->EnablePeripheralClock(true);
    AFIO_Remap_TIM3(true, true);
    GPIOB::GetInstance()->EnablePeripheralClock(true);
    GPIO_PIN* ch0 = GPIOB::GetInstance()->GetPin(GPIO_PIN4);
    GPIO_PIN* ch1 = GPIOB::GetInstance()->GetPin(GPIO_PIN5);
    GPIO_PIN* ch2 = GPIOB::GetInstance()->GetPin(GPIO_PIN0);
    GPIO_PIN* ch3 = GPIOB::GetInstance()->GetPin(GPIO_PIN1);
    ch0->SetupGPIO_OutAltPP();
    ch1->SetupGPIO_OutAltPP();
    ch2->SetupGPIO_OutAltPP();
    ch3->SetupGPIO_OutAltPP();
    return timer;
}

#if !defined(STM32F10X_LD) && !defined(STM32F10X_LD_VL)
TIM4*   GPIO_Helper::SetupTIM4_PD_12_13_14_15()
{
    TIM4* timer = TIM4::GetInstance();
    timer->EnablePeripheralClock(true);
    AFIO_Remap_TIM4(true);
    GPIOD::GetInstance()->EnablePeripheralClock(true);
    GPIO_PIN* ch0 = GPIOD::GetInstance()->GetPin(GPIO_PIN12);
    GPIO_PIN* ch1 = GPIOD::GetInstance()->GetPin(GPIO_PIN13);
    GPIO_PIN* ch2 = GPIOD::GetInstance()->GetPin(GPIO_PIN14);
    GPIO_PIN* ch3 = GPIOD::GetInstance()->GetPin(GPIO_PIN15);
    ch0->SetupGPIO_OutAltPP();
    ch1->SetupGPIO_OutAltPP();
    ch2->SetupGPIO_OutAltPP();
    ch3->SetupGPIO_OutAltPP();
    return timer;

}

TIM4*   GPIO_Helper::SetupTIM4_PB_6_7_8_9()
{
    TIM4* timer = TIM4::GetInstance();
    timer->EnablePeripheralClock(true);
    AFIO_Remap_TIM4(false);
    GPIOB::GetInstance()->EnablePeripheralClock(true);
    GPIO_PIN* ch0 = GPIOB::GetInstance()->GetPin(GPIO_PIN6);
    GPIO_PIN* ch1 = GPIOB::GetInstance()->GetPin(GPIO_PIN7);
    GPIO_PIN* ch2 = GPIOB::GetInstance()->GetPin(GPIO_PIN8);
    GPIO_PIN* ch3 = GPIOB::GetInstance()->GetPin(GPIO_PIN9);
    ch0->SetupGPIO_OutAltPP();
    ch1->SetupGPIO_OutAltPP();
    ch2->SetupGPIO_OutAltPP();
    ch3->SetupGPIO_OutAltPP();
    return timer;

}
#endif

#if defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL)
TIM5*  GPIO_Helper::SetupTIM5_PA_0_1_2_3()
{
    TIM5* timer = TIM5::GetInstance();
    timer->EnablePeripheralClock(true);
    GPIOA::GetInstance()->EnablePeripheralClock(true);
    GPIO_PIN* ch0 = GPIOA::GetInstance()->GetPin(GPIO_PIN0);
    GPIO_PIN* ch1 = GPIOA::GetInstance()->GetPin(GPIO_PIN1);
    GPIO_PIN* ch2 = GPIOA::GetInstance()->GetPin(GPIO_PIN2);
    GPIO_PIN* ch3 = GPIOA::GetInstance()->GetPin(GPIO_PIN3);
    ch0->SetupGPIO_OutAltPP();
    ch1->SetupGPIO_OutAltPP();
    ch2->SetupGPIO_OutAltPP();
    ch3->SetupGPIO_OutAltPP();
    return timer;
}
#endif

#if defined(STM32F10X_XL) || defined(STM32F10X_HD)
TIM8*  GPIO_Helper::SetupTIM8_PC_6_7_8_9()
{
    TIM8* timer = TIM8::GetInstance();
    timer->EnablePeripheralClock(true);
    GPIOC::GetInstance()->EnablePeripheralClock(true);
    GPIO_PIN* ch0 = GPIOC::GetInstance()->GetPin(GPIO_PIN6);
    GPIO_PIN* ch1 = GPIOC::GetInstance()->GetPin(GPIO_PIN7);
    GPIO_PIN* ch2 = GPIOC::GetInstance()->GetPin(GPIO_PIN8);
    GPIO_PIN* ch3 = GPIOC::GetInstance()->GetPin(GPIO_PIN9);
    ch0->SetupGPIO_OutAltPP();
    ch1->SetupGPIO_OutAltPP();
    ch2->SetupGPIO_OutAltPP();
    ch3->SetupGPIO_OutAltPP();
    return timer;

}
#endif

#endif


#ifdef USE_I2C


I2C* GPIO_Helper::SetupI2Cx (I2C* i2c, uint32_t clockSpeed,  GPIO_PORT* port,  GPIO_PIN_N sclPin, GPIO_PIN_N sdaPin)
{
    if (!port->IsClockEnabled())
    {
        port->EnablePeripheralClock(true);
    }

    port->SetupGPIO_OutAltOD (sclPin);  //I2C_SCL
    port->SetupGPIO_OutAltOD (sdaPin);  //I2C_SDA

    bool isDuty16_9 = false;
    bool isFmMode = false;
    i2c->Initialize(clockSpeed, isDuty16_9, isFmMode);
    i2c->SetModeI2C();
    i2c->EnableACK(false);
    i2c->SetOwnAddr7Bit(0x00);

    return i2c;


}

I2C1*   GPIO_Helper::SetupI2C1_PB_6_7(uint32_t clockSpeed)
{
	AFIO_Remap_I2C1(false);
    return (I2C1*)SetupI2Cx(I2C1::GetInstance(), clockSpeed, GPIOB::GetInstance(), GPIO_PIN6, GPIO_PIN7);
}

I2C1*   GPIO_Helper::SetupI2C1_PB_8_9(uint32_t clockSpeed)
{
	AFIO_Remap_I2C1(true);
    return (I2C1*)SetupI2Cx(I2C1::GetInstance(), clockSpeed, GPIOB::GetInstance(), GPIO_PIN8, GPIO_PIN9);
}


#endif

#ifdef USE_USART
USART* GPIO_Helper::SetupUSARTx(GPIO_PORT* port, GPIO_PIN_N txPinNo, GPIO_PIN_N rxPinNo, USART* usart, uint32_t clockSpeed)
{
    port->EnablePeripheralClock(true);
    GPIO_PIN* txPin = port->GetPin(txPinNo);
    GPIO_PIN* rxPin = port->GetPin(rxPinNo);


    txPin->SetupGPIO_OutAltPP();
    txPin->SetSpeedHigh();

    rxPin->SetupGPIO_OutAltPP();
    rxPin->SetSpeedHigh();

    usart->Enable(true);
    usart->SetBaudRate(clockSpeed);
    usart->EnableTransmitter(true);
    usart->EnableReceiver(true);
    return usart;

}


USART1* GPIO_Helper::SetupUSART1_PA_9_10(uint32_t clockSpeed)
{
	AFIO_Remap_USART1(false);
    return (USART1*)SetupUSARTx(GPIOA::GetInstance(), GPIO_PIN9, GPIO_PIN10, USART1::GetInstance(), clockSpeed);
}

USART1* GPIO_Helper::SetupUSART1_PB_6_7(uint32_t clockSpeed)
{
	AFIO_Remap_USART1(true);
    return (USART1*)SetupUSARTx(GPIOB::GetInstance(), GPIO_PIN6, GPIO_PIN7, USART1::GetInstance(), clockSpeed);
}

USART2* GPIO_Helper::SetupUSART2_PA_2_3(uint32_t clockSpeed)
{
	AFIO_Remap_USART2(false);
    return (USART2*)SetupUSARTx(GPIOA::GetInstance(), GPIO_PIN2, GPIO_PIN3, USART2::GetInstance(), clockSpeed);
}

USART2* GPIO_Helper::SetupUSART2_PD_5_6(uint32_t clockSpeed)
{
	AFIO_Remap_USART2(true);
    return (USART2*)SetupUSARTx(GPIOD::GetInstance(), GPIO_PIN5, GPIO_PIN6, USART2::GetInstance(), clockSpeed);
}


USART3* GPIO_Helper::SetupUSART3_PB_10_11(uint32_t clockSpeed)
{
	AFIO_Remap_USART3(false, false);
    return (USART3*)SetupUSARTx(GPIOB::GetInstance(), GPIO_PIN10, GPIO_PIN11, USART3::GetInstance(), clockSpeed);
}

USART3* GPIO_Helper::SetupUSART3_PC_10_11(uint32_t clockSpeed)
{
	AFIO_Remap_USART3(true, false);
    return (USART3*)SetupUSARTx(GPIOC::GetInstance(), GPIO_PIN10, GPIO_PIN11, USART3::GetInstance(), clockSpeed);
}

USART3* GPIO_Helper::SetupUSART3_PD_8_9(uint32_t clockSpeed)
{
	AFIO_Remap_USART3(true, true);
    return (USART3*)SetupUSARTx(GPIOD::GetInstance(), GPIO_PIN8, GPIO_PIN9, USART3::GetInstance(), clockSpeed);
}




#endif
