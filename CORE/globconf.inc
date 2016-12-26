; STM8EF Global Configuration File
; Minimal config for STM8S Value Line, just the defaults
; Clock: HSI (no crystal)

        STM8S003F3      = 1 

        HAS_OUTPUTS     = 0    ; no 
        HAS_ADC         = 0    ; Analog input words
        
        HAS_BACKGROUND  = 0    ; Background Forth task (TIM2 ticker)
        HAS_CPNVM       = 1    ; Can compile to Flash, always interpret to RAM 
        HAS_DOES        = 0    ; CREATE-DOES> extension
        HAS_DOLOOP      = 0    ; DO .. LOOP extension: DO LEAVE LOOP +LOOP

        CASEINSENSITIVE = 0    ; Case insensitive dictionary search
        SPEEDOVERSIZE   = 0    ; Speed-over-size in core words: ROT - = < 
        BAREBONES       = 1    ; Remove or unlink some more: hi HERE .R U.R SPACES @EXECUTE AHEAD CALL, EXIT COMPILE [COMPILE]

        WORDS_LINKINTER = 0     ; Link interpreter words: ACCEPT QUERY TAP kTAP hi 'BOOT tmp >IN 'TIB #TIB eval CONTEXT pars PARSE NUMBER? DIGIT? WORD TOKEN NAME> SAME? find ABORT aborq $INTERPRET INTER? .OK ?STACK EVAL PRESET QUIT $COMPILE
        WORDS_LINKCOMP  = 0     ; Link compiler words: cp last OVERT $"| ."| $,n 
        WORDS_LINKRUNTI = 0     ; Link runtime words: doLit do$ doVAR donxt dodoes ?branch branch 
        WORDS_LINKCHAR =  0     ; Link char out words: DIGIT <# # #S SIGN #> str hld HOLD 
        WORDS_LINKMISC =  0     ; Link composing words of SEE DUMP WORDS: >CHAR _TYPE dm+ .ID >NAME  

        WORDS_EXTRASTACK = 0    ; Link/include stack core words: rp@ rp! sp! sp@ DEPTH 
        WORDS_EXTRADEBUG = 0    ; Extra debug words: SEE
        WORDS_EXTRACORE  = 0    ; Extra core words: =0 I
        WORDS_EXTRAMEM   = 0    ; Extra memory words: BSR 2C@ 2C!
        WORDS_EXTRAEEPR  = 0    ; Extra EEPROM lock/unlock words: LOCK ULOCK ULOCKF LOCKF 
        WORDS_HWREG      = 0    ; Peripheral Register words


