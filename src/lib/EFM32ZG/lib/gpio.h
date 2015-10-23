#ifndef _GPIO_H
#define _GPIO_H

#include "common.h"

#define GPIO_BASE 0x40006000

#define GPIO_PORT_RANGE      0x24

#define GPIOA_BASE GPIO_BASE + GPIO_PORT_RANGE*0
#define GPIOB_BASE GPIO_BASE + GPIO_PORT_RANGE*1
#define GPIOC_BASE GPIO_BASE + GPIO_PORT_RANGE*2
#define GPIOD_BASE GPIO_BASE + GPIO_PORT_RANGE*3
#define GPIOE_BASE GPIO_BASE + GPIO_PORT_RANGE*4
#define GPIOF_BASE GPIO_BASE + GPIO_PORT_RANGE*5

#define GPIO_Px_OFFSET_CTRL     0x00
#define GPIO_Px_OFFSET_MODEL    0x04
#define GPIO_Px_OFFSET_MODEH    0x08
#define GPIO_Px_OFFSET_DOUT     0x0C
#define GPIO_Px_OFFSET_DOUTSET  0x10
#define GPIO_Px_OFFSET_DOUTCLR  0x14
#define GPIO_Px_OFFSET_DOUTTGL  0x18
#define GPIO_Px_OFFSET_DIN      0x1C
#define GPIO_Px_OFFSET_PINLOCKN 0x20



#define GPIO_PA_CTRL           (*(volatile uint32_t*)(GPIOA_BASE + GPIO_Px_OFFSET_CTRL))
#define GPIO_PB_CTRL           (*(volatile uint32_t*)(GPIOB_BASE + GPIO_Px_OFFSET_CTRL))
#define GPIO_PC_CTRL           (*(volatile uint32_t*)(GPIOC_BASE + GPIO_Px_OFFSET_CTRL))
#define GPIO_PD_CTRL           (*(volatile uint32_t*)(GPIOD_BASE + GPIO_Px_OFFSET_CTRL))
#define GPIO_PE_CTRL           (*(volatile uint32_t*)(GPIOE_BASE + GPIO_Px_OFFSET_CTRL))
#define GPIO_PF_CTRL           (*(volatile uint32_t*)(GPIOF_BASE + GPIO_Px_OFFSET_CTRL))

#define GPIO_Px_CTRL_DRIVERMODE_STANDARD (1<<0)
#define GPIO_Px_CTRL_DRIVERMODE_LOWEST   (1<<1)
#define GPIO_Px_CTRL_DRIVERMODE_HIGH     (1<<2)
#define GPIO_Px_CTRL_DRIVERMODE_LOW      (1<<3)
#define GPIO_Px_CTRL_DRIVERMODE_CLEARMASK    (1<<3)




#define GPIO_PA_MODEL          (*(volatile uint32_t*)(GPIOA_BASE + GPIO_Px_OFFSET_MODEL))
#define GPIO_PB_MODEL          (*(volatile uint32_t*)(GPIOB_BASE + GPIO_Px_OFFSET_MODEL))
#define GPIO_PC_MODEL          (*(volatile uint32_t*)(GPIOC_BASE + GPIO_Px_OFFSET_MODEL))
#define GPIO_PD_MODEL          (*(volatile uint32_t*)(GPIOD_BASE + GPIO_Px_OFFSET_MODEL))
#define GPIO_PE_MODEL          (*(volatile uint32_t*)(GPIOE_BASE + GPIO_Px_OFFSET_MODEL))
#define GPIO_PF_MODEL          (*(volatile uint32_t*)(GPIOF_BASE + GPIO_Px_OFFSET_MODEL))

#define GPIO_PA_MODEH          (*(volatile uint32_t*)(GPIOA_BASE + GPIO_Px_OFFSET_MODEH))
#define GPIO_PB_MODEH          (*(volatile uint32_t*)(GPIOB_BASE + GPIO_Px_OFFSET_MODEH))
#define GPIO_PC_MODEH          (*(volatile uint32_t*)(GPIOC_BASE + GPIO_Px_OFFSET_MODEH))
#define GPIO_PD_MODEH          (*(volatile uint32_t*)(GPIOD_BASE + GPIO_Px_OFFSET_MODEH))
#define GPIO_PE_MODEH          (*(volatile uint32_t*)(GPIOE_BASE + GPIO_Px_OFFSET_MODEH))
#define GPIO_PF_MODEH          (*(volatile uint32_t*)(GPIOF_BASE + GPIO_Px_OFFSET_MODEH))


#define GPIO_Px_MODE_DISABLED                0
#define GPIO_Px_MODE_INPUT                   1
#define GPIO_Px_MODE_INPUTPULL               2
#define GPIO_Px_MODE_INPUTPULLFILTER         3
#define GPIO_Px_MODE_PUSHPULL                4
#define GPIO_Px_MODE_PUSHPULLDRIVE           5
#define GPIO_Px_MODE_WIREDOR                 6
#define GPIO_Px_MODE_WIREDORPULLDOWN         7
#define GPIO_Px_MODE_WIREDAND                8
#define GPIO_Px_MODE_WIREDANDFILTER          9
#define GPIO_Px_MODE_WIREDANDPULLUP          10
#define GPIO_Px_MODE_WIREDANDPULLUPFILTER    11
#define GPIO_Px_MODE_WIREDANDDRIVE           12
#define GPIO_Px_MODE_WIREDANDDRIVEFILTER     13
#define GPIO_Px_MODE_WIREDANDDRIVEPULLUP     14
#define GPIO_Px_MODE_WIREDANDDRIVEPULLUPFILTER 15
#define GPIO_Px_MODE_CLEARMASK 0xF


#define GPIO_PA_DOUT           (*(volatile uint32_t*)(GPIOA_BASE + GPIO_Px_OFFSET_DOUT))
#define GPIO_PB_DOUT           (*(volatile uint32_t*)(GPIOB_BASE + GPIO_Px_OFFSET_DOUT))
#define GPIO_PC_DOUT           (*(volatile uint32_t*)(GPIOC_BASE + GPIO_Px_OFFSET_DOUT))
#define GPIO_PD_DOUT           (*(volatile uint32_t*)(GPIOD_BASE + GPIO_Px_OFFSET_DOUT))
#define GPIO_PE_DOUT           (*(volatile uint32_t*)(GPIOE_BASE + GPIO_Px_OFFSET_DOUT))
#define GPIO_PF_DOUT           (*(volatile uint32_t*)(GPIOF_BASE + GPIO_Px_OFFSET_DOUT))

#define GPIO_PA_DOUTSET        (*(volatile uint32_t*)(GPIOA_BASE + GPIO_Px_OFFSET_DOUTSET))
#define GPIO_PB_DOUTSET        (*(volatile uint32_t*)(GPIOB_BASE + GPIO_Px_OFFSET_DOUTSET))
#define GPIO_PC_DOUTSET        (*(volatile uint32_t*)(GPIOC_BASE + GPIO_Px_OFFSET_DOUTSET))
#define GPIO_PD_DOUTSET        (*(volatile uint32_t*)(GPIOD_BASE + GPIO_Px_OFFSET_DOUTSET))
#define GPIO_PE_DOUTSET        (*(volatile uint32_t*)(GPIOE_BASE + GPIO_Px_OFFSET_DOUTSET))
#define GPIO_PF_DOUTSET        (*(volatile uint32_t*)(GPIOF_BASE + GPIO_Px_OFFSET_DOUTSET))

#define GPIO_PA_DOUTCLR        (*(volatile uint32_t*)(GPIOA_BASE + GPIO_Px_OFFSET_DOUTCLR))
#define GPIO_PB_DOUTCLR        (*(volatile uint32_t*)(GPIOB_BASE + GPIO_Px_OFFSET_DOUTCLR))
#define GPIO_PC_DOUTCLR        (*(volatile uint32_t*)(GPIOC_BASE + GPIO_Px_OFFSET_DOUTCLR))
#define GPIO_PD_DOUTCLR        (*(volatile uint32_t*)(GPIOD_BASE + GPIO_Px_OFFSET_DOUTCLR))
#define GPIO_PE_DOUTCLR        (*(volatile uint32_t*)(GPIOE_BASE + GPIO_Px_OFFSET_DOUTCLR))
#define GPIO_PF_DOUTCLR        (*(volatile uint32_t*)(GPIOF_BASE + GPIO_Px_OFFSET_DOUTCLR))



#define GPIO_PA_DOUTTGL        (*(volatile uint32_t*)(GPIOA_BASE + GPIO_Px_OFFSET_DOUTTGL))
#define GPIO_PB_DOUTTGL        (*(volatile uint32_t*)(GPIOB_BASE + GPIO_Px_OFFSET_DOUTTGL))
#define GPIO_PC_DOUTTGL        (*(volatile uint32_t*)(GPIOC_BASE + GPIO_Px_OFFSET_DOUTTGL))
#define GPIO_PD_DOUTTGL        (*(volatile uint32_t*)(GPIOD_BASE + GPIO_Px_OFFSET_DOUTTGL))
#define GPIO_PE_DOUTTGL        (*(volatile uint32_t*)(GPIOE_BASE + GPIO_Px_OFFSET_DOUTTGL))
#define GPIO_PF_DOUTTGL        (*(volatile uint32_t*)(GPIOF_BASE + GPIO_Px_OFFSET_DOUTTGL))


#define GPIO_PA_DIN            (*(volatile uint32_t*)(GPIOA_BASE + GPIO_Px_OFFSET_DIN))
#define GPIO_PB_DIN            (*(volatile uint32_t*)(GPIOB_BASE + GPIO_Px_OFFSET_DIN))
#define GPIO_PC_DIN            (*(volatile uint32_t*)(GPIOC_BASE + GPIO_Px_OFFSET_DIN))
#define GPIO_PD_DIN            (*(volatile uint32_t*)(GPIOD_BASE + GPIO_Px_OFFSET_DIN))
#define GPIO_PE_DIN            (*(volatile uint32_t*)(GPIOE_BASE + GPIO_Px_OFFSET_DIN))
#define GPIO_PF_DIN            (*(volatile uint32_t*)(GPIOF_BASE + GPIO_Px_OFFSET_DIN))

#define GPIO_PA_PINLOCKN       (*(volatile uint32_t*)(GPIOA_BASE + GPIO_Px_OFFSET_PINLOCKN))
#define GPIO_PB_PINLOCKN       (*(volatile uint32_t*)(GPIOB_BASE + GPIO_Px_OFFSET_PINLOCKN))
#define GPIO_PC_PINLOCKN       (*(volatile uint32_t*)(GPIOC_BASE + GPIO_Px_OFFSET_PINLOCKN))
#define GPIO_PD_PINLOCKN       (*(volatile uint32_t*)(GPIOD_BASE + GPIO_Px_OFFSET_PINLOCKN))
#define GPIO_PE_PINLOCKN       (*(volatile uint32_t*)(GPIOE_BASE + GPIO_Px_OFFSET_PINLOCKN))
#define GPIO_PF_PINLOCKN       (*(volatile uint32_t*)(GPIOF_BASE + GPIO_Px_OFFSET_PINLOCKN))


#define GPIO_OFFSET_EXTIPSELL  0x100
#define GPIO_OFFSET_EXTIPSELH  0x104
#define GPIO_EXTIPSELL         (*(volatile uint32_t*)(GPIO_BASE + GPIO_OFFSET_EXTIPSELL))
#define GPIO_EXTIPSELH         (*(volatile uint32_t*)(GPIO_BASE + GPIO_OFFSET_EXTIPSELH))
#define GPIO_EXTIPSEL_CLEARMASK 0xf

#define GPIO_OFFSET_EXTIRISE  0x108
#define GPIO_EXTIRISE        (*(volatile uint32_t*)(GPIO_BASE + GPIO_OFFSET_EXTIRISE))
#define GPIO_OFFSET_EXTIFALL  0x10C
#define GPIO_EXTIFALL        (*(volatile uint32_t*)(GPIO_BASE + #define GPIO_OFFSET_EXTIFALL))

#define GPIO_OFFSET_IEN  0x110
#define GPIO_OFFSET_IF   0x114
#define GPIO_OFFSET_IFS  0x118
#define GPIO_OFFSET_IFC  0x11C
#define GPIO_IEN             (*(volatile uint32_t*)(GPIO_BASE + GPIO_OFFSET_IEN))
#define GPIO_IF              (*(volatile uint32_t*)(GPIO_BASE + GPIO_OFFSET_IF))
#define GPIO_IFS             (*(volatile uint32_t*)(GPIO_BASE + GPIO_OFFSET_IFS))
#define GPIO_IFC             (*(volatile uint32_t*)(GPIO_BASE + GPIO_OFFSET_IFC))

#define GPIO_OFFSET_ROUTE 0x120
#define GPIO_ROUTE           (*(volatile uint32_t*)(GPIO_BASE + GPIO_OFFSET_ROUTE))
#define GPIO_ROUTE_SWCLKPEN (1<<0)
#define GPIO_ROUTE_SWDIOPEN (1<<1)

#define GPIO_OFFSET_INSENSE 0x124
#define GPIO_INSENSE         (*(volatile uint32_t*)(GPIO_BASE + GPIO_OFFSET_INSENSE))
#define GPIO_INSENSE_INT (1<<0)
#define GPIO_INSENSE_PRS (1<<1)

#define GPIO_OFFSET_LOCK 0x128
#define GPIO_LOCK            (*(volatile uint32_t*)(GPIO_BASE + GPIO_OFFSET_LOCK))
#define GPIO_LOCK_UNLOCKED     (1<<0)
#define GPIO_LOCK_UNLOCK_CODE  0xA534

#define GPIO_OFFSET_CTRL 0x12C
#define GPIO_CTRL            (*(volatile uint32_t*)(GPIO_BASE + GPIO_OFFSET_CTRL))
#define GPIO_CTRL_EM4RET  (1<<0)

#define GPIO_OFFSET_CMD  0x130
#define GPIO_CMD             (*(volatile uint32_t*)(GPIO_BASE + GPIO_OFFSET_CMD))
#define GPIO_CMD_EM4WUCLR  (1<<0)

#define GPIO_OFFSET_EM4WUEN 0x134
#define GPIO_EM4WUEN         (*(volatile uint32_t*)(GPIO_BASE + GPIO_OFFSET_EM4WUEN))
#define GPIO_EM4WUEN_A0 0x1
#define GPIO_EM4WUEN_C9 0x4
#define GPIO_EM4WUEN_F1 0x8
#define GPIO_EM4WUEN_F2 0x10
#define GPIO_EM4WUEN_E13 0x20
#define GPIO_EM4WUEN_CLEARMASK 0x3F


#define GPIO_OFFSET_EM4WUPOL 0x138
#define GPIO_EM4WUPOL        (*(volatile uint32_t*)(GPIO_BASE + GPIO_OFFSET_EM4WUPOL))
#define GPIO_EM4WUPOL_A0 0x1
#define GPIO_EM4WUPOL_C9 0x4
#define GPIO_EM4WUPOL_F1 0x8
#define GPIO_EM4WUPOL_F2 0x10
#define GPIO_EM4WUPOL_E13 0x20
#define GPIO_EM4WUPOL_CLEARMASK 0x3F

#define GPIO_OFFSET_EM4WUCAUSE  0x13C
#define GPIO_EM4WUCAUSE      (*(volatile uint32_t*)(GPIO_BASE + GPIO_OFFSET_EM4WUCAUSE))
#define GPIO_EM4WUCAUSE_A0 0x1
#define GPIO_EM4WUCAUSE_C9 0x4
#define GPIO_EM4WUCAUSE_F1 0x8
#define GPIO_EM4WUCAUSE_F2 0x10
#define GPIO_EM4WUCAUSE_E13 0x20
#define GPIO_EM4WUCAUSE_CLEARMASK 0x3F







typedef enum
{
    EXTI_LINE0 = 0,
    EXTI_LINE1 = 1,
    EXTI_LINE2 = 2,
    EXTI_LINE3 = 3,
    EXTI_LINE4 = 4,
    EXTI_LINE5 = 5,
    EXTI_LINE6 = 6,
    EXTI_LINE7 = 7,
    EXTI_LINE8 = 8,
    EXTI_LINE9 = 9,
    EXTI_LINE10 = 10,
    EXTI_LINE11 = 11,
    EXTI_LINE12 = 12,
    EXTI_LINE13 = 13,
    EXTI_LINE14 = 14,
    EXTI_LINE15 = 15,
    EXTI_LINE16 = 16,
    EXTI_LINE17 = 17,
    EXTI_LINE18 = 18,
    EXTI_LINE19 = 19

} EXTI_LINE;


typedef enum
{
    GPIOA = 0,
    GPIOB = 1,
    GPIOC = 2,
    GPIOD = 3,
    GPIOE = 4,
    GPIOF = 5,
} GPIO_PORT_N;

typedef enum
{
 GPIO_PIN0  = 0,
 GPIO_PIN1  = 1,
 GPIO_PIN2  = 2,
 GPIO_PIN3  = 3,
 GPIO_PIN4  = 4,
 GPIO_PIN5  = 5,
 GPIO_PIN6  = 6,
 GPIO_PIN7  = 7,
 GPIO_PIN8  = 8,
 GPIO_PIN9  = 9,
 GPIO_PIN10 = 10,
 GPIO_PIN11 = 11,
 GPIO_PIN12 = 12,
 GPIO_PIN13 = 13,
 GPIO_PIN14 = 14,
 GPIO_PIN15 = 15
} GPIO_PIN_N;



typedef struct
{
  GPIO_PIN_N pinNumber;
  GPIO_PORT_N portNumber;
} GPIO_PIN;

typedef struct
{
	GPIO_PORT_N portNo;

	volatile uint32_t*  Px_CTRL;
	volatile uint32_t*  Px_MODEL;
	volatile uint32_t*  Px_MODEH;
	volatile uint32_t*  Px_DOUT;
	volatile uint32_t*  Px_DOUTSET;
	volatile uint32_t*  Px_DOUTCLR;
	volatile uint32_t*  Px_DOUTTGL;
	volatile uint32_t*  Px_DIN;
	volatile uint32_t*  Px_PINLOCKN;
	volatile uint32_t*  EXTIPSELL;
	volatile uint32_t*  EXTIPSELH;
	volatile uint32_t*  EXTIRISE;
	volatile uint32_t*  EXTIFALL;
	volatile uint32_t*  IEN;
	volatile uint32_t*  IF;
	volatile uint32_t*  IFS;
	volatile uint32_t*  IFC;
	volatile uint32_t*  ROUTE;
	volatile uint32_t*  INSENSE;
	volatile uint32_t*  LOCK;
	volatile uint32_t*  CTRL;
	volatile uint32_t*  CMD;
	volatile uint32_t*  EM4WUEN;
	volatile uint32_t*  EM4WUPOL;
	volatile uint32_t*  EM4WUCAUSE;

	GPIO_PIN pins[16];

} GPIO_PORT;



GPIO_PORT* GPIO_GetPort(GPIO_PORT_N port);
GPIO_PIN*  GPIO_GetPin(GPIO_PORT* port, GPIO_PORT_N pinNumber);


void GPIO_SetDriveMode_STANDARD(GPIO_PORT* port);
void GPIO_SetDriveMode_LOWEST(GPIO_PORT* port);
void GPIO_SetDriveMode_HIGH(GPIO_PORT* port);
void GPIO_SetDriveMode_LOW(GPIO_PORT* port);

void GPIO_DisablePin (GPIO_PIN* pin);

void GPIO_SetupInFloat (GPIO_PIN* pin);
void GPIO_SetupInPullUp (GPIO_PIN* pin);
void GPIO_SetupInPullDown (GPIO_PIN* pin);

void GPIO_SetupOutPP (GPIO_PIN* pin);
void GPIO_SetupOutOD (GPIO_PIN* pin);


void GPIO_Set (GPIO_PIN* pin);
void GPIO_Toggle (GPIO_PIN* pin);
void GPIO_Reset (GPIO_PIN* pin);
BOOL GPIO_IsSet (GPIO_PIN* pin);



void GPIO_RemapEXTI(GPIO_PORT* port, EXTI_LINE line);


#endif
