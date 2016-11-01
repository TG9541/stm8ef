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
        HAS_CPNVM    =    1     ; Can compile to Flash, always interpret to RAM 

        WORDS_LINKCOMP =  1     ; Link compiler words.: doLit next ?branch branch EXECUTE EXIT doVAR HERE $"| ."| [COMPILE] COMPILE LITERAL $," do$
        WORDS_LINKINTER = 1     ; Link interpreter words: hi 'BOOT rp! cp tmp >IN 'eval CONTEXT last parse PARSE WORD TOKEN NAME> SAME? find ^h TAP kTAP ACCEPT QUERY ABORT abort $INTERPRET INTER? .OK ?STACK EVAL PRESET QUIT ?UNIQUE $,n $COMPILE OVERT 
        WORDS_LINKCHAR =  0     ; Link char I/O words: #TIB hld TIB >CHAR COUNT DIGIT <# HOLD # #S SIGN #> str DIGIT? NUMBER? _TYPE 
        WORDS_LINKMISC =  0     ; Link base words of SEE DUMP WORDS 

        WORDS_EXTRASTACK = 1    ; Link/include stack core words: rp@ rp! R@ sp! sp@ DEPTH 
        WORDS_EXTRADEBUG = 0    ; Extra debug words: SEE
        WORDS_EXTRACORE = 1     ; Extra core words: I =0
        WORDS_EXTRAMEM =  1     ; Extra memory words: BSR 2C@ 2C! LCK ULCK
