#ifndef _IRQ_H
#define _IRQ_H

#if defined(STM32F401xC)  || defined(STM32F401xE) || defined(STM32F401xx)
  #include "irq_f401xx.h"
#elif defined(STM32F405xx)
  #include "irq_f405xx.h"
#elif defined(STM32F407xx)
  #include "irq_f407xx.h"
#elif defined(STM32F411xE)
  #include "irq_f411xx.h"
#elif defined(STM32F415xx)
  #include "irq_f415xx.h"
#elif defined(STM32F417xx)
  #include "irq_f417xx.h"
#elif defined(STM32F427xx)
  #include "irq_f427xx.h"
#elif defined(STM32F429xx)
  #include "irq_f429xx.h"
#elif defined(STM32F437xx)
  #include "irq_f437xx.h"
#elif defined(STM32F439xx)
  #include "irq_f439xx.h"
#elif defined(STM32F446xx)
  #include "irq_f446xx.h"
#elif defined(STM32F469xx)
  #include "irq_f469xx.h"
#else
 #error "Please select first the target STM32F4xx device used in your application in the project settings"
#endif


#endif

