; STM8EF Global Configuration File
; Minimal config for STM8S Value Line, just the defaults
; Clock: HSI (no crystal)

        STM8S003F3   =    1 

        HAS_OUTPUTS      = 0    ; no 
        HAS_ADC          = 0    ; Analog input words
        
        HAS_BACKGROUND   = 0    ; Background Forth task (TIM2 ticker)
        HAS_CPNVM        = 0    ; Can compile to Flash, always interpret to RAM 
        HAS_DOES         = 0    ; CREATE-DOES> extension

        CASEINSENSITIVE  = 0    ; Case insensitive dictionary search
        SPEEDOVERSIZE    = 0    ; Speed-over-size in core words: ROT - = < 
        BAREBONES        = 1    ; Remove or unlink some more: hi HERE .R U.R SPACES VARIABLE

        WORDS_LINKCOMP   = 0    ; Link words for compiler extensions: doLit donxt ?branch branch EXECUTE EXIT doVAR [COMPILE] COMPILE $,"
        WORDS_LINKCOMPC  = 0    ; Link composing words of compiler: cp last do$ OVERT $"| ."| $,n NVM? dodoes 
        WORDS_LINKINTER  = 0    ; Link interpreter core words: hi 'BOOT tmp >IN 'eval CONTEXT pars PARSE WORD TOKEN NAME> SAME? find ABORT aborq $INTERPRET INTER? .OK ?STACK EVAL PRESET QUIT ?UNIQUE $COMPILE
        WORDS_LINKCHAR   = 0    ; Link char I/O core words: ACCEPT TAP kTAP QUERY #TIB hld TIB >CHAR COUNT DIGIT <# HOLD # #S SIGN #> str DIGIT? NUMBER? _TYPE 
        WORDS_LINKMISC   = 0    ; Link core words of SEE DUMP WORDS 

        WORDS_EXTRASTACK = 0    ; Link/include stack core words: rp@ rp! sp! sp@ DEPTH 
        WORDS_EXTRADEBUG = 0    ; Extra debug words: SEE
        WORDS_EXTRACORE  = 0    ; Extra core words: =0 I
        WORDS_EXTRAMEM   = 0    ; Extra memory words: BSR 2C@ 2C!
        WORDS_EXTRAEEPR  = 0    ; Extra EEPROM lock/unlock words: LOCK ULOCK  
        WORDS_HWREG      = 0    ; Peripheral Register words

