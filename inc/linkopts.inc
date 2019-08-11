        .ifne  HAS_CPNVM
        UNLINK_TBOOT     = 0    ; "'BOOT"
        UNLINK_HI        = 0    ; "hi"
        .endif

        .ifne  HAS_ALIAS
        UNLINK_OVERT     = 0    ; "OVERT"
        .endif

        .ifne  WORDS_LINKCOMP
        UNLINK_CPP       = 0    ; "cp"
        UNLINK_UNIQU     = 0    ; "?UNIQUE"
        UNLINK_OVERT     = 0    ; "OVERT"
        .endif

        .ifne  WORDS_LINKRUNTI
        UNLINK_DOSTR     = 0    ; "do$"
        UNLINK_STRQP     = 0    ; '$"|'
        UNLINK_DOTQP     = 0    ; '."|'
        UNLINK_DODOES    = 0    ; "dodoes"
        UNLINK_DOLIT     = 0    ; "doLit"
        UNLINK_DOPLOOP   = 0    ; "(+loop)"
        UNLINK_DONXT     = 0    ; "donxt"
        UNLINK_QBRAN     = 0    ; "?branch"
        UNLINK_BRAN      = 0    ; "branch"
        UNLINK_DOVAR     = 0    ; "doVar"
        .endif

        .ifne  WORDS_LINKINTER
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

        .ifne  BAREBONES
        EXTNUMPREFIX     = 0    ; Extended number prefix: %: binary, &: decimal
        UNLINK_QRX       = 1    ; "?RX"
        UNLINK_TXSTOR    = 1    ; "TX!"
        UNLINK_LAST      = 1    ; "last"
        UNLINK_DEPTH     = 1    ; "DEPTH"
        UNLINK_COUNT     = 1    ; "COUNT"
        UNLINK_UDOTR     = 1    ; "U.R"
        UNLINK_NAMET     = 1    ; "NAME>"
        UNLINK_BCOMP     = 1    ; "[COMPILE]"
        UNLINK_COMPI     = 1    ; "COMPILE"
        UNLINK_ABRTQ     = 1    ; 'ABORT"'
        UNLINK_EXIT      = 1    ; "EXIT"
        REMOVE_EXIT      = 1    ; remove "EXIT"
        .endif

        .ifne   WORDS_LINKCHAR
        UNLINK_BDIGS     = 0    ; "<#"
        UNLINK_HOLD      = 0    ; "HOLD"
        UNLINK_SIGN      = 0    ; "SIGN"
        UNLINK_DIG       = 0    ; "#"
        UNLINK_DIGS      = 0    ; "#S"
        UNLINK_EDIGS     = 0    ; "#>"
        .endif

        .ifne   WORDS_LINKMISC
        UNLINK_TCHAR     = 0    ; ">CHAR"
        UNLINK_UTYPE     = 0    ; "_TYPE"
        UNLINK_DOTID     = 0    ; ".ID"
        UNLINK_DUMPP     = 0    ; "dm+"
        .endif

        .ifne   WORDS_EXTRADEBUG
        UNLINK_TNAME     = 0    ; ">NAME"
        REMOVE_TNAME     = 0    ; remove ">TNAME"
        .endif

        .ifne   WORDS_EXTRACORE
        UNLINK_ZEQUAL    = 0    ; "0="
        .endif
