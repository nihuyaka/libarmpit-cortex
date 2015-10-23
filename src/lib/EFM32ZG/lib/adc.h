#ifndef _ADC_H
#define _ADC_H

#define ADC_BASE 0x40002000

#define ADCn_CTRL             (*(volatile uint32_t*)(ADC_BASE + 0x000)) 
#define ADCn_CMD              (*(volatile uint32_t*)(ADC_BASE + 0x004)) 
#define ADCn_STATUS           (*(volatile uint32_t*)(ADC_BASE + 0x008)) 
#define ADCn_SINGLECTRL       (*(volatile uint32_t*)(ADC_BASE + 0x00C)) 
#define ADCn_SCANCTRL         (*(volatile uint32_t*)(ADC_BASE + 0x010)) 
#define ADCn_IEN              (*(volatile uint32_t*)(ADC_BASE + 0x014)) 
#define ADCn_IF               (*(volatile uint32_t*)(ADC_BASE + 0x018)) 
#define ADCn_IFS              (*(volatile uint32_t*)(ADC_BASE + 0x01C)) 
#define ADCn_IFC              (*(volatile uint32_t*)(ADC_BASE + 0x020)) 
#define ADCn_SINGLEDATA       (*(volatile uint32_t*)(ADC_BASE + 0x024)) 
#define ADCn_SCANDATA         (*(volatile uint32_t*)(ADC_BASE + 0x028)) 
#define ADCn_SINGLEDATAP      (*(volatile uint32_t*)(ADC_BASE + 0x02C)) 
#define ADCn_SCANDATAP        (*(volatile uint32_t*)(ADC_BASE + 0x030)) 
#define ADCn_CAL              (*(volatile uint32_t*)(ADC_BASE + 0x034)) 
#define ADCn_BIASPROG         (*(volatile uint32_t*)(ADC_BASE + 0x03C)) 



#endif


