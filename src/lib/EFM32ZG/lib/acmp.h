#ifndef _ACMP_H
#define _ACMP_H

#define ACMP_BASE 0x40001000

#define ACMPn_CTRL     (*(volatile uint32_t*)(ACMP_BASE + 0x000))
#define ACMPn_INPUTSEL (*(volatile uint32_t*)(ACMP_BASE + 0x004))
#define ACMPn_STATUS   (*(volatile uint32_t*)(ACMP_BASE + 0x008))
#define ACMPn_IEN      (*(volatile uint32_t*)(ACMP_BASE + 0x00C))
#define ACMPn_IF       (*(volatile uint32_t*)(ACMP_BASE + 0x010))
#define ACMPn_IFS      (*(volatile uint32_t*)(ACMP_BASE + 0x014))
#define ACMPn_IFC      (*(volatile uint32_t*)(ACMP_BASE + 0x018))
#define ACMPn_ROUTE    (*(volatile uint32_t*)(ACMP_BASE + 0x01C))


#endif