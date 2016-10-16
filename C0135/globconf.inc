; STM8EF Global Configuration File
; Config for C0135 "Relay Board-4 STM8S"

        BOARD_C0135 =     1     ; C0135 "Relay Board-4 STM8S" 

        ; Clock: HSI (8MHz crystal not used)
        STM8S103F3   =    1 
        HAS_KEYS     =    1     ; yes, 1 key 
        HAS_OUTPUTS  =    4     ; yes, 4 relays
        HAS_ADC      =    1     ; Analog input words
        HAS_BACKGROUND =  1     ; Background Forth task (TIM2 ticker)
        WORDS_EXTRACORE = 1     ; Extra core words: I =0
        WORDS_EXTRAMEM =  1     ; Extra memory words: BSR 2C@ 2C! LCK ULCK
