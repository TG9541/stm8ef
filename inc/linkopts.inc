        .ifne  HAS_CPNVM
        UNLINK_TBOOT     = 0    ; "'BOOT"
        UNLINK_HI        = 0    ; "hi"
        .endif

        .ifne WORDS_LINKINTER
        UNLINK_TBOOT     = 0    ; "'BOOT"   ; INIT
        UNLINK_HI        = 0    ; "hi"      ; INIT
        UNLINK_CNTXT     = 0    ; "CONTEXT" ; parser
        UNLINK_INN       = 0    ; ">IN"     ; charInput
        UNLINK_NTIB      = 0    ; "#TIB"    ; charInput
        UNLINK_TEVAL     = 0    ; "'eval"   ; REPL
        UNLINK_TPROMPT   = 0    ; "'PROMPT"
        UNLINK_NUMBQ     = 0    ; "NUMBER?" ; parser
        UNLINK_DIGITQ    = 0    ; "DIGIT?"  ; parser
        UNLINK_PARS      = 0    ; "pars"    ; parser
        UNLINK_PARSE     = 0    ; "PARSE"   ; parser
        UNLINK_WORDD     = 0    ; "WORD"    ; parser
        UNLINK_TOKEN     = 0    ; "TOKEN"   ; parser
        UNLINK_SAMEQ     = 0    ; "SAME?"   ; parser
        UNLINK_CUPPER    = 0    ; "CUPPER"  ; parser
        UNLINK_NAMEQ     = 0    ; "NAME?"   ; parser
        UNLINK_FIND      = 0    ; "find"    ; parser
        UNLINK_BKSP      = 0    ; "^h"     ; charInput
        UNLINK_TAP       = 0    ; "TAP"    ; charInput
        UNLINK_KTAP      = 0    ; "kTAP"   ; charInput 
        UNLINK_ACCEP     = 0    ; "ACCEPT" ; charInput
        UNLINK_QUERY     = 0    ; "QUERY"  ; charInput
        UNLINK_ABORT     = 0    ; "ABORT"  ; REPL
        UNLINK_ABORQ     = 0    ; "aborq"  ; REPL -
        UNLINK_PRESE     = 0    ; "PRESET" ; REPL
        UNLINK_INTER     = 0    ; "$INTERPRET" ; REPL -
        UNLINK_SCOMP     = 0    ; "$COMPILE" ; REPL -
        UNLINK_DOTOK     = 0    ; ".OK" ; REPL
        UNLINK_QSTAC     = 0    ; "?STACK" ; REPL  
        UNLINK_EVAL      = 0    ; "EVAL"  ; REPL 
        UNLINK_QUIT      = 0    ; "QUIT"  ; REPL
        .endif


