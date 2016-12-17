; STM8EF Global Configuration File
; Config for W1209 Thermostat Module
; Clock: HSI (no crystal)

        BOARD_W1209      = 1    ; W1209 thermostat board 

        ; UART half-duplex PD_6 (RxD) SW simulation "bus style"
        ; Multiplexed 3 digit 7S-LED display, 3 keys, relay
        ; Clock: HSI (no crystal)
        STM8S003F3       = 1 
        HALF_DUPLEX      = 1    ; RS232 Half Duplex Mode
        HAS_TXDSIM       = 1    ; TxD SW simulation
        PDTX             = 6    ; GPIO for SW half-duplex /w TIM4

        HAS_LED7SEG      = 3    ; yes, 3 dig. 7-seg LED on module
        HAS_KEYS         = 3    ; yes, 3 keys on module
        HAS_OUTPUTS      = 1    ; yes, one relay 
        HAS_ADC          = 1    ; Analog input words

        HAS_BACKGROUND   = 1    ; Background Forth task (TIM2 ticker)
        HAS_CPNVM        = 1    ; Can compile to Flash, always interpret to RAM 
        HAS_DOES         = 1    ; CREATE-DOES> extension
        HAS_DOLOOP       = 1    ; DO .. LOOP extension: DO LEAVE LOOP +LOOP

        BCKGRND_EMIT = EMIT7S   ; LED7SEG for background EMIT
        CASEINSENSITIVE  = 1    ; Case insensitive dictionary search
        SPEEDOVERSIZE    = 0    ; Speed-over-size in core words: ROT - = < 
        BAREBONES        = 0    ; Remove or unlink some more: hi HERE .R U.R SPACES VARIABLE

        WORDS_LINKCOMP   = 0    ; Link words for compiler extensions: doLit donxt ?branch branch EXECUTE EXIT doVAR [COMPILE] COMPILE $,"
        WORDS_LINKCOMPC  = 0    ; Link composing words of compiler: cp last do$ OVERT $"| ."| $,n NVM? dodoes 
        WORDS_LINKINTER  = 0    ; Link interpreter core words: hi 'BOOT tmp >IN 'eval CONTEXT pars PARSE WORD TOKEN NAME> SAME? find ABORT aborq $INTERPRET INTER? .OK ?STACK EVAL PRESET QUIT ?UNIQUE $COMPILE
        WORDS_LINKCHAR   = 0    ; Link char I/O core words: ACCEPT TAP kTAP QUERY #TIB hld TIB >CHAR COUNT DIGIT <# HOLD # #S SIGN #> str DIGIT? NUMBER? _TYPE 
        WORDS_LINKMISC   = 0    ; Link core words of SEE DUMP WORDS 

        WORDS_EXTRASTACK = 0    ; Link/include stack core words: rp@ rp! sp! sp@ DEPTH 
        WORDS_EXTRADEBUG = 0    ; Extra debug words: SEE
        WORDS_EXTRACORE  = 0    ; Extra core words: =0 I
        WORDS_EXTRAMEM   = 0    ; Extra memory words: BSR 2C@ 2C!
        WORDS_EXTRAEEPR  = 1    ; Extra EEPROM lock/unlock words: LOCK ULOCK  
        WORDS_HWREG      = 0    ; Peripheral Register words

