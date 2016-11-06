; STM8EF Global Configuration File
; Config for STM8S103F3P6 Minmal Development Board
; Clock: HSI (no crystal)

        BOARD_MINDEV =    1     ; STM8S103F3 "minimum development board"

        STM8S103F3   =    1 
        HAS_OUTPUTS  =    1     ; yes, one LED 
        HAS_ADC      =    1     ; Analog input words
        HAS_BACKGROUND =  1     ; Background Forth task (TIM2 ticker)
       
        HAS_CPNVM    =    1     ; Can compile to Flash, always interpret to RAM
 
        WORDS_LINKCOMP =  0     ; Link compiler words.: doLit next ?branch branch EXECUTE EXIT doVAR HERE $"| ."| [COMPILE] COMPILE LIT
        WORDS_LINKINTER = 0     ; Link interpreter words: hi rp! cp tmp >IN 'eval CONTEXT last parse PARSE WORD TOKEN NAME> SAME? find
        WORDS_LINKCHAR =  0     ; Link char I/O words: #TIB hld TIB >CHAR COUNT DIGIT <# HOLD # #S SIGN #> str DIGIT? NUMBER? _TYPE
        WORDS_LINKMISC =  0     ; Link base words of SEE DUMP WORDS
 
        WORDS_EXTRASTACK = 0    ; Link/include stack core words: rp@ rp! R@ sp! sp@ DEPTH
        WORDS_EXTRADEBUG = 0    ; Extra debug words: SEE

        WORDS_EXTRACORE = 1     ; Extra core words: =0
        WORDS_EXTRAMEM =  1     ; Extra memory words: BSR 2C@ 2C! LOCK ULOCK LOCKF ULOCKF 
        WORDS_HWREG  =    0     ; Peripheral Register words
 
