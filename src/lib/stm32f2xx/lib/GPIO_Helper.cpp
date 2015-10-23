#include "GPIO_Helper.h" 

#ifdef USE_SPI

SPI* GPIO_Helper::SetupSPIx (bool isMasterMode, bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate,
        GPIO_PORT* port,  GPIO_PIN_N clkPin, GPIO_PIN_N misoPin, GPIO_PIN_N mosiPin, SPI* spi, GPIO_AF af)
{
    port->EnablePeripheralClock(true);
    GPIO_PIN* CLK_pin = port->GetPin (clkPin);
    GPIO_PIN* MISO_pin = port->GetPin (misoPin);
    GPIO_PIN* MOSI_pin = port->GetPin (mosiPin);

    MOSI_pin->SetAF (af);
    CLK_pin->SetAF (af);
    MISO_pin->SetAF (af);

    MOSI_pin->SetupGPIO_OutAltPP();
    MOSI_pin->PullDown();
    MOSI_pin->SetSpeedHigh();

    CLK_pin->SetupGPIO_OutAltPP();
    CLK_pin->PullDown();
    CLK_pin->SetSpeedHigh();

    MISO_pin->SetupGPIO_OutAltPP();
    MISO_pin->PullDown();
    MISO_pin->SetSpeedHigh();

    spi->Enable(true);

    bool isFullDuplex = true;
    bool isLSBFirst = false;
    bool isSetSSM = true;

    spi->Initialize(isMasterMode, isFullDuplex, baudRate,  isClockPhase2, isClockPolarity1, isLSBFirst, isSetSSM);
    return spi;

}

SPI1* GPIO_Helper::SetupSPI1_MasterMode_PA_5_6_7(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate)
{
    return (SPI1*)SetupSPIx(true, isClockPhase2, isClockPolarity1, baudRate, GPIOA::GetInstance(), GPIO_PIN5, GPIO_PIN6, GPIO_PIN7, SPI1::GetInstance(), AF5);
}

SPI1* GPIO_Helper::SetupSPI1_MasterMode_PB_3_4_5(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate)
{
    return (SPI1*)SetupSPIx(true, isClockPhase2, isClockPolarity1, baudRate, GPIOB::GetInstance(), GPIO_PIN3, GPIO_PIN4, GPIO_PIN5, SPI1::GetInstance(), AF5);
}

SPI2* GPIO_Helper::SetupSPI2_MasterMode_PB_13_14_15(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate)
{
    return (SPI2*)SetupSPIx(true, isClockPhase2, isClockPolarity1, baudRate, GPIOB::GetInstance(), GPIO_PIN13, GPIO_PIN14, GPIO_PIN15, SPI1::GetInstance(), AF5);

}

SPI3* GPIO_Helper::SetupSPI3_MasterMode_PB_3_4_5(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate)
{
    return (SPI3*)SetupSPIx(true, isClockPhase2, isClockPolarity1, baudRate, GPIOB::GetInstance(), GPIO_PIN3, GPIO_PIN4, GPIO_PIN5, SPI1::GetInstance(), AF6);

}

SPI3* GPIO_Helper::SetupSPI3_MasterMode_PC_10_11_12(bool isClockPhase2, bool isClockPolarity1, SPI_BAUD_RATE baudRate)
{
    return (SPI3*)SetupSPIx(true, isClockPhase2, isClockPolarity1, baudRate, GPIOC::GetInstance(), GPIO_PIN10, GPIO_PIN11, GPIO_PIN12, SPI1::GetInstance(), AF6);

}


#endif

#ifdef USE_TIMER


void  GPIO_Helper::SetupTIMx(GPIO_PORT* port, GPIO_PIN_N ch0, GPIO_PIN_N ch1, GPIO_PIN_N ch2, GPIO_PIN_N ch3, GPIO_AF af)
{
    port->EnablePeripheralClock(true);

    port->SetAF(af, ch0);
    port->SetAF(af, ch1);
    port->SetAF(af, ch2);
    port->SetAF(af, ch3);

    port->SetupGPIO_OutAltPP(ch0);
    port->SetupGPIO_OutAltPP(ch1);
    port->SetupGPIO_OutAltPP(ch2);
    port->SetupGPIO_OutAltPP(ch3);



}

TIM1*  GPIO_Helper::SetupTIM1_PA_8_9_10_11()
{
    TIM1* timer = TIM1::GetInstance();
    timer->EnablePeripheralClock(true);
    SetupTIMx(GPIOA::GetInstance(), GPIO_PIN8, GPIO_PIN9, GPIO_PIN10, GPIO_PIN11, AF1);
    return timer;

}

TIM2*  GPIO_Helper::SetupTIM2_PA_0_1_2_3()
{
    TIM2* timer = TIM2::GetInstance();
    timer->EnablePeripheralClock(true);
    SetupTIMx(GPIOA::GetInstance(), GPIO_PIN0, GPIO_PIN1, GPIO_PIN2, GPIO_PIN3, AF1);
    return timer;

}

TIM3*  GPIO_Helper::SetupTIM3_PC_6_7_8_9()
{
    TIM3* timer = TIM3::GetInstance();
    timer->EnablePeripheralClock(true);
    SetupTIMx(GPIOC::GetInstance(), GPIO_PIN6, GPIO_PIN7, GPIO_PIN8, GPIO_PIN9, AF2);
    return timer;

}


TIM3*  GPIO_Helper::SetupTIM3_PB_4_5_0_1()
{
    TIM3* timer = TIM3::GetInstance();
    timer->EnablePeripheralClock(true);
    SetupTIMx(GPIOB::GetInstance(), GPIO_PIN4, GPIO_PIN5, GPIO_PIN0, GPIO_PIN1, AF2);
    return timer;
}


TIM4*   GPIO_Helper::SetupTIM4_PD_12_13_14_15()
{
    TIM4* timer = TIM4::GetInstance();
    timer->EnablePeripheralClock(true);
    SetupTIMx(GPIOD::GetInstance(), GPIO_PIN12, GPIO_PIN13, GPIO_PIN14, GPIO_PIN15, AF2);
    return timer;

}

TIM4*   GPIO_Helper::SetupTIM4_PB_6_7_8_9()
{
    TIM4* timer = TIM4::GetInstance();
    timer->EnablePeripheralClock(true);
    SetupTIMx(GPIOB::GetInstance(), GPIO_PIN6, GPIO_PIN7, GPIO_PIN8, GPIO_PIN9, AF2);
    return timer;

}

TIM5*  GPIO_Helper::SetupTIM5_PA_0_1_2_3()
{
    TIM5* timer = TIM5::GetInstance();
    timer->EnablePeripheralClock(true);
    SetupTIMx(GPIOA::GetInstance(), GPIO_PIN0, GPIO_PIN1, GPIO_PIN2, GPIO_PIN3, AF2);
    return timer;

}


TIM8*  GPIO_Helper::SetupTIM8_PC_6_7_8_9()
{
    TIM8* timer = TIM8::GetInstance();
    timer->EnablePeripheralClock(true);
    SetupTIMx(GPIOC::GetInstance(), GPIO_PIN6, GPIO_PIN7, GPIO_PIN8, GPIO_PIN9, AF3);
    return timer;

}


#endif


#ifdef USE_I2C
I2C1*   GPIO_Helper::SetupI2C1_PB_6_9(uint32_t clockSpeed)
{
    GPIO_PORT* i2c1_port = GPIOB::GetInstance();
    i2c1_port->EnablePeripheralClock(false);
    i2c1_port->EnablePeripheralClock(true);
    GPIO_PIN* SDA_pin = i2c1_port->GetPin(GPIO_PIN9);
    GPIO_PIN* SCK_pin = i2c1_port->GetPin(GPIO_PIN6);

    SDA_pin->SetAF(AF4); //apparently has to remap first before configuring open drain etc
    SCK_pin->SetAF(AF4);

    SDA_pin->SetupGPIO_OutAltOD();
    SDA_pin->PullUp();
    SDA_pin->SetSpeedMedium();

    SCK_pin->SetupGPIO_OutAltOD();
    SCK_pin->SetSpeedMedium();
    SCK_pin->PullUp();


    DMA1* dma1 = DMA1::GetInstance();
    dma1->EnablePeripheralClock(true);

    DMA_Stream* txStream = dma1->GetStream(DMA_STREAM_6);
    txStream->SetChannel(DMA_CHANNEL_1);
    DMA_Stream* rxStream = dma1->GetStream(DMA_STREAM_5);
    rxStream->SetChannel(DMA_CHANNEL_1);

    I2C1* i2c = I2C1::GetInstance();

    bool isDuty16_9 = false;
    bool isFmMode = false;
    i2c->Initialize(clockSpeed, isDuty16_9, isFmMode);
    i2c->SetModeI2C();
    i2c->EnableACK(false);
    i2c->SetOwnAddr7Bit(0x00);
    i2c->SetDMA_TxStream(txStream);
    i2c->SetDMA_RxStream(rxStream);


    return i2c;
}

#endif

#ifdef USE_USART
USART* GPIO_Helper::SetupUSARTx(GPIO_PORT* port, GPIO_PIN_N txPinNo, GPIO_PIN_N rxPinNo, GPIO_AF af, USART* usart, uint32_t clockSpeed)
{
    port->EnablePeripheralClock(true);
    GPIO_PIN* txPin = port->GetPin(txPinNo);
    GPIO_PIN* rxPin = port->GetPin(rxPinNo);

    txPin->SetAF(AF7);
    rxPin->SetAF(AF7);

    txPin->SetupGPIO_OutAltPP();
    txPin->SetSpeedMedium();

    rxPin->SetupGPIO_OutAltPP();
    rxPin->SetSpeedMedium();

    usart->Enable(true);
    usart->SetBaudRate(clockSpeed);
    usart->EnableTransmitter(true);
    usart->EnableReceiver(true);
    return usart;

}


USART1* GPIO_Helper::SetupUSART1_PA_9_10(uint32_t clockSpeed)
{
    return (USART1*)SetupUSARTx(GPIOA::GetInstance(), GPIO_PIN9, GPIO_PIN10, AF7, USART1::GetInstance(), clockSpeed);
}

USART1* GPIO_Helper::SetupUSART1_PB_6_7(uint32_t clockSpeed)
{
    return (USART1*)SetupUSARTx(GPIOB::GetInstance(), GPIO_PIN6, GPIO_PIN7, AF7, USART1::GetInstance(), clockSpeed);
}

USART2* GPIO_Helper::SetupUSART2_PA_2_3(uint32_t clockSpeed)
{
    return (USART2*)SetupUSARTx(GPIOA::GetInstance(), GPIO_PIN2, GPIO_PIN3, AF7, USART2::GetInstance(), clockSpeed);
}

USART2* GPIO_Helper::SetupUSART2_PD_5_6(uint32_t clockSpeed)
{
    return (USART2*)SetupUSARTx(GPIOD::GetInstance(), GPIO_PIN5, GPIO_PIN6, AF7, USART2::GetInstance(), clockSpeed);
}


USART3* GPIO_Helper::SetupUSART3_PB_10_11(uint32_t clockSpeed)
{
    return (USART3*)SetupUSARTx(GPIOB::GetInstance(), GPIO_PIN10, GPIO_PIN11, AF7, USART3::GetInstance(), clockSpeed);
}

USART3* GPIO_Helper::SetupUSART3_PC_10_11(uint32_t clockSpeed)
{
    return (USART3*)SetupUSARTx(GPIOC::GetInstance(), GPIO_PIN10, GPIO_PIN11, AF7, USART3::GetInstance(), clockSpeed);
}

USART6* GPIO_Helper::SetupUSART3_PC_6_7(uint32_t clockSpeed)
{
    return (USART6*)SetupUSARTx(GPIOC::GetInstance(), GPIO_PIN6, GPIO_PIN7, AF7, USART6::GetInstance(), clockSpeed);
}

USART6* GPIO_Helper::SetupUSART3_PG_14_9(uint32_t clockSpeed)
{
    return (USART6*)SetupUSARTx(GPIOG::GetInstance(), GPIO_PIN14, GPIO_PIN9, AF7, USART6::GetInstance(), clockSpeed);
}

#endif



