; STM8EF Global Configuration File
; Config for W1209 Thermostat Module
; Clock: HSI (no crystal)

        BOARD_W1209 =     1     ; W1209 thermostat board 

        ; UART half-duplex PD_6 (RxD) SW simulation "bus style"
        ; Multiplexed 3 digit 7S-LED display, 3 keys, relay
        ; Clock: HSI (no crystal)
        STM8S003F3   =    1 
        HALF_DUPLEX  =    1     ; RS232 Half Duplex Mode
        HAS_TXDSIM   =    1     ; TxD SW simulation
        PDTX         =    6     ; GPIO for SW half-duplex /w TIM4

        HAS_LED7SEG  =    3     ; yes, 3 dig. 7-seg LED on module
        HAS_KEYS     =    3     ; yes, 3 keys on module
        HAS_OUTPUTS  =    1     ; yes, one relay 
        HAS_ADC      =    1     ; Analog input words
        HAS_BACKGROUND =  1     ; Background Forth task (TIM2 ticker)
        WORDS_EXTRACORE = 1     ; Extra core words: I =0
        WORDS_EXTRAMEM =  1     ; Extra memory words: BSR 2C@ 2C! LCK ULCK

