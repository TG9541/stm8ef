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

         .ifne  BAREBONES
        UNLINK_QRX       = 2    ; "?RX"
        UNLINK_TXSTOR    = 2    ; "TX!"
        UNLINK_LAST      = 2    ; "last"
        UNLINK_DEPTH     = 2    ; "DEPTH"
        UNLINK_COUNT     = 2    ; "COUNT"
        UNLINK_UDOTR     = 2    ; "U.R"
        UNLINK_NAMET     = 1    ; "NAME>"
        UNLINK_BCOMP     = 2    ; "[COMPILE]"
        UNLINK_COMPI     = 2    ; "COMPILE"
        UNLINK_ABRTQ     = 1    ; 'ABORT"'
        UNLINK_EXIT      = 1    ; "EXIT"
        REMOVE_EXIT      = 1    ; remove "EXIT"
        .endif

        .ifne  MINIDICT
        UNLINK_CREAT     = 2    ; "CREATE"
        UNLINK_SPACE     = 2    ; "SPACE"
        UNLINK_DECIM     = 2    ; "DECIMAL"
        UNLINK_VARIA     = 2    ; "VARIABLE"
        UNLINK_ALLOT     = 2    ; "ALLOT"
        UNLINK_NEGAT     = 2    ; "NEGATE"
        UNLINK_UNTIL     = 2    ; "UNTIL"
        UNLINK_AGAIN     = 2    ; "AGAIN"
        UNLINK_EXECU     = 2    ; "EXECUTE"
        UNLINK_JSRC      = 2    ; "CALL,"
        UNLINK_ELSE      = 2    ; "ELSE"
        UNLINK_PICK      = 2    ; "PICK"
        UNLINK_EMIT      = 2    ; "EMIT"
        UNLINK_TYPES     = 2    ; "TYPE"
        UNLINK_HERE      = 2    ; "HERE"
        UNLINK_QKEY      = 2    ; "?KEY"
        UNLINK_ADCSTOR   = 2    ; "ADC!"
        UNLINK_ADCAT     = 2    ; "ADC@"
        UNLINK_HEX       = 2    ; "HEX"
        UNLINK_ABSS      = 2    ; "ABS"
        UNLINK_MMOD      = 2    ; "MOD"
        UNLINK_ROT       = 2    ; "ROT"
        UNLINK_ANDD      = 2    ; "AND"
        UNLINK_MSTAR     = 2    ; "M*"
        UNLINK_DCSTOR    = 2    ; "2C!"
        UNLINK_DCAT      = 2    ; "2C@"
        UNLINK_NIP       = 2    ; "NIP"
        UNLINK_DDROP     = 2    ; "2DROP"
        UNLINK_XORR      = 2    ; "XOR"
        UNLINK_UPLUS     = 2    ; "UM+"
        UNLINK_QDUP      = 2    ; "?DUP"
        UNLINK_DDUP      = 2    ; "2DUP"
        UNLINK_CMOVE     = 2    ; "CMOVE"
        UNLINK_FILL      = 2    ; "FILL"
        UNLINK_ERASE     = 2    ; "ERASE"
        UNLINK_KEY       = 2    ; "KEY"
        UNLINK_MAX       = 2    ; "MAX"
        UNLINK_MIN       = 2    ; "MIN"
        UNLINK_WITHI     = 2    ; "WITHIN"
        UNLINK_UMSTA     = 2    ; "UM*"
        UNLINK_FOR       = 2    ; "FOR"
        UNLINK_NEXT      = 2    ; "NEXT"
        UNLINK_LEAVE     = 2    ; "LEAVE"
        UNLINK_LOOP      = 2    ; "LOOP"
        UNLINK_PLOOP     = 2    ; "+LOOP"
        UNLINK_AFT       = 2    ; "AFT"
        UNLINK_DOESS     = 2    ; "DOES>"
        UNLINK_SAVEC     = 2    ; "SAVEC"
        UNLINK_RESTC     = 2    ; "IRET"
        .endif
