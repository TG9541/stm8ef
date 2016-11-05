; STM8EF Global Configuration File
; Minimal config for STM8S Value Line, just the defaults
; Clock: HSI (no crystal)
        STM8S003F3   =    1 
        WORDS_BAREBONES  = 1    ; Remove convenience words: hi 


         HAS_BACKGROUND =  0     ; Background Forth task (TIM2 ticker)
         HAS_CPNVM    =    0     ; Can compile to Flash, always interpret to RAM
 
         WORDS_LINKCOMP =  0     ; Link compiler words.: doLit next ?branch branch EXECUTE EXIT doVAR HERE $"| ."| [COMPILE] COMPILE LIT
         WORDS_LINKINTER = 0     ; Link interpreter words: hi rp! cp tmp >IN 'eval CONTEXT last parse PARSE WORD TOKEN NAME> SAME? find
         WORDS_LINKCHAR =  0     ; Link char I/O words: #TIB hld TIB >CHAR COUNT DIGIT <# HOLD # #S SIGN #> str DIGIT? NUMBER? _TYPE
         WORDS_LINKMISC =  0     ; Link base words of SEE DUMP WORDS
 
         WORDS_EXTRASTACK = 0    ; Link/include stack core words: rp@ rp! R@ sp! sp@ DEPTH
         WORDS_EXTRADEBUG = 0    ; Extra debug words: SEE
         WORDS_EXTRACORE =  0    ; Extra core words: I =0
         WORDS_EXTRAMEM =   0    ; Extra memory words: BSR 2C@ 2C! LCK ULCK
