            IF :DEF:STM32F401xC || :DEF:STM32F401xE || :DEF:STM32F401xx
            GET startup_stm32f401xx.s
            ELIF :DEF:STM32F405xx
            GET startup_stm32f405xx.s
            ELIF :DEF:STM32F407xx
            GET startup_stm32f407xx.s
            ELIF :DEF:STM32F411xE
            GET startup_stm32f411xe.s
            ELIF :DEF:STM32F415xx
            GET startup_stm32f415xx.s
            ELIF :DEF:STM32F417xx
            GET startup_stm32f417xx.s
            ELIF :DEF:STM32F427xx
            GET startup_stm32f427xx.s
            ELIF :DEF:STM32F429xx
            GET startup_stm32f429xx.s
            ELIF :DEF:STM32F437xx
            GET startup_stm32f437xx.s
            ELIF :DEF:STM32F439xx
            GET startup_stm32f439xx.s
            ELIF :DEF:STM32F446xx
            GET startup_stm32f446xx.s
            ELIF :DEF:STM32F469xx
            GET startup_stm32f469xx.s
            ENDIF   
            END