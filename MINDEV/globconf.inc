; STM8EF Global Configuration File
; Config for STM8S103F3P6 Minmal Development Board
; Clock: HSI (no crystal)

        BOARD_MINDEV =    1     ; STM8S103F3 "minimum development board"

        STM8S103F3   =    1 
        HAS_OUTPUTS  =    1     ; yes, one LED 
        HAS_ADC      =    1     ; Analog input words
        HAS_BACKGROUND =  1     ; Background Forth task (TIM2 ticker)

        WORDS_EXTRACORE = 1     ; Extra core words: I =0
        WORDS_EXTRAMEM =  1     ; Extra memory words: BSR 2C@ 2C! LCK ULCK 
        WORDS_HWREG  =    0     ; Peripheral Register words
        
