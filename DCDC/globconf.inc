; STM8EF Global Configuration File
; Config for W1209 Thermostat Module
; Clock: HSI (no crystal)

        HALF_DUPLEX      = 0    ; Use UART in half duplex mode
        HAS_TXUART       = 0    ; No UART TXD, word TX!
        HAS_RXUART       = 0    ; No UART RXD, word ?RX
        HAS_TXSIM        = 1    ; Like HAS_RXSIM, word TXGP!, use for console if > HAS_TXUART
        HAS_RXSIM        = 1    ; Enable RxD via GPIO/TIM4, word ?RXGP
        PSIM     = PORTC        ; Port for UART simulation
        PNRX             = 7    ; Port GPIO# for HAS_RXDSIM
        PNTX             = 7    ; Port GPIO# for HAS_TXDSIM
        SERPRIOTIM   = 30000    ; RXSIM priority in BG ticks

        EMIT_BG  = EMIT7S       ; 7S-LED background EMIT vector
        QKEY_BG  = QKEYB        ; Board keys background QKEY vector

        HAS_LED7SEG      = 1    ; yes, 1*3 dig. 7-seg LED on module

        HAS_KEYS         = 2    ; yes, 3 keys on module
        HAS_OUTPUTS      = 1    ; yes, power on/off
        HAS_ADC          = 1    ; Analog input words

        HAS_BACKGROUND   = 1    ; Background Forth task (TIM2 ticker)
        BG_TIM_REL  = 0x08FC    ; 1ms ticker for 7S-LED MPX
        BG_RUNMASK  =      0    ; BG task runs if "(BG_RUNMASK AND TICKCNT) equals 0"
        HAS_CPNVM        = 1    ; Can compile to Flash, always interpret to RAM
        HAS_DOES         = 1    ; CREATE-DOES> extension
        HAS_DOLOOP       = 1    ; DO .. LOOP extension: DO LEAVE LOOP +LOOP


        CASEINSENSITIVE  = 1    ; Case insensitive dictionary search
        SPEEDOVERSIZE    = 0    ; Speed-over-size in core words: ROT - = <
        BAREBONES        = 0    ; Remove or unlink some more: hi HERE .R U.R SPACES @EXECUTE AHEAD CALL, EXIT COMPILE [COMPILE]

        WORDS_LINKINTER  = 0    ; Link interpreter words: ACCEPT QUERY TAP kTAP hi 'BOOT tmp >IN 'TIB #TIB eval CONTEXT pars PARSE NUMBER? DIGIT? WORD TOKEN NAME> SAME? find ABORT aborq $INTERPRET INTER? .OK ?STACK EVAL PRESET QUIT $COMPILE
        WORDS_LINKCOMP   = 0    ; Link compiler words: cp last OVERT $"| ."| $,n
        WORDS_LINKRUNTI  = 0    ; Link runtime words: doLit do$ doVAR donxt dodoes ?branch branch
        WORDS_LINKCHAR   = 1    ; Link char out words: DIGIT <# # #S SIGN #> str hld HOLD
        WORDS_LINKMISC   = 0    ; Link composing words of SEE DUMP WORDS: >CHAR _TYPE dm+ .ID >NAME

        WORDS_EXTRASTACK = 0    ; Link/include stack core words: rp@ rp! sp! sp@ DEPTH
        WORDS_EXTRADEBUG = 0    ; Extra debug words: SEE
        WORDS_EXTRACORE  = 1    ; Extra core words: =0 I
        WORDS_EXTRAMEM   = 1    ; Extra memory words: B! 2C@ 2C!
        WORDS_EXTRAEEPR  = 1    ; Extra EEPROM lock/unlock words: LOCK ULOCK ULOCKF LOCKF
