#if defined(STM32F405xx) \
|| defined(STM32F415xx) \
|| defined(STM32F407xx) \
|| defined(STM32F417xx) \
|| defined(STM32F427xx) \
|| defined(STM32F437xx) \
|| defined(STM32F429xx) \
|| defined(STM32F439xx) \
|| defined(STM32F401xx) \
|| defined(STM32F401xC) \
|| defined(STM32F401xE) \
|| defined(STM32F411xE) \
|| defined(STM32F446xx) \
|| defined(STM32F469xx)


#ifndef STM32F4
#define STM32F4
#endif

#define STM32

#elif defined (STM32F10X_LD) || defined (STM32F10X_LD_VL) \
|| defined (STM32F10X_MD) || defined (STM32F10X_MD_VL)  \
|| defined (STM32F10X_HD) || defined (STM32F10X_HD_VL)  \
|| defined (STM32F10X_XL) || defined (STM32F10X_CL) 

#ifndef STM32F1
#define STM32F1
#endif

#if defined(STM32F10X_LD_VL) || (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL) 
#define VALUE_LINE
#endif

#define STM32

#elif defined(STM32F205xx) || defined(STM32F215xx) || defined(STM32F207xx) || defined(STM32F217xx) 

#ifndef STM32F2
#define STM32F2
#endif

#define STM32

#endif


