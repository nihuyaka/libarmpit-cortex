#ifndef _VCMP_H
#define _VCMP_H

#define VCMP_BASE 0x40000000

#define VCMP_CTRL      (*(volatile uint32_t*)(VCMP_BASE + 0x000)) 
#define VCMP_INPUTSEL  (*(volatile uint32_t*)(VCMP_BASE + 0x004)) 
#define VCMP_STATUS    (*(volatile uint32_t*)(VCMP_BASE + 0x008)) 
#define VCMP_IEN       (*(volatile uint32_t*)(VCMP_BASE + 0x00C)) 
#define VCMP_IF        (*(volatile uint32_t*)(VCMP_BASE + 0x010)) 
#define VCMP_IFS       (*(volatile uint32_t*)(VCMP_BASE + 0x014)) 
#define VCMP_IFC       (*(volatile uint32_t*)(VCMP_BASE + 0x018)) 



#endif
