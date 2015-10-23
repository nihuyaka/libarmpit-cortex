#include "IRRemote.h"
#include "RCC_Helper.h"

void TestIR()
{

    //SetupGPIO (&GPIOB_CR, PIN2, GPIO_CNF_IFLOAT, GPIO_MODE_INP);
    //SetupGPIO (&GPIOB_CR, PIN2, GPIO_CNF_IPUPD, GPIO_MODE_INP);

    GPIO_PORT* irPort = GPIOE::GetInstance();
    irPort->EnablePeripheralClock(true);
    GPIO_PIN* irPin = irPort->GetPin(GPIO_PIN2);
    irPin->SetupGPIO_InFloat();
    irPin->SpeedHigh();

    IRRemote irRemote (irPin);

    TIM2* tim2 = TIM2::GetInstance();
    tim2->EnablePeripheralClock(true);
    tim2->SetUpdatePeriod_us(50);
    tim2->EnableNVICInterrupt(true);
    tim2->EnableUpdateInterrupt(true);
    tim2->AddInterruptHandler(&irRemote);
    tim2->EnableCounter(true);


    volatile DECODE_TYPE type;
    volatile uint32_t  value;

    while (1)
    {
        if (irRemote.decode())
        {

            //if (irRemote.isVolumeDown())
            {
                type = irRemote.getType();
                value = irRemote.getValue();
            }

            type = irRemote.getType();
            value = irRemote.getValue();
            //printf ("%x: %lu\n", results.value, results.value);
            //if ((results.value & 0xffff) == 0x06f9)


            //if (results.decode_type == 0xb)



            {
                //LED on
            }

            irRemote.resume(); // Receive the next value
        }
    }
    //delay(100);
}

int main()
{
    F4_EnableHSI_100Mhz();
    TestIR();
}
