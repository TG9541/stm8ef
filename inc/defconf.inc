;--------------------------------------------------------
;       STM8 eForth for STM8S and STM8L devices
;       Default settings for all options
;--------------------------------------------------------
        RELVER1          = 2    ; Revision digit 1
        RELVER0          = 10   ; Revision digit 0
        PRE_REL          = 1    ; Pre Release digit 0 (0: release)

        TERM_LINUX       = 1    ; LF terminates line

        HALF_DUPLEX      = 0    ; Use the STM8S Low Density UART in half duplex mode (1: PD5, 2: PA3)
        USE_UART2        = 0    ; Use the 2nd UART for the console (STM8S207: optional, STM8S105: default, STM8L152: optional)
        USE_UART3        = 0    ; Use the 3rd UART for the console (STM8L152: optional)
        ALT_USART_STM8L  = 0    ; Alternative STM8L USART GPIO mapping (e.g. PA3/PA2 instead of PC2/PC3)
        CUARTBRR    = 0x6803    ; default value for UARTBRR 9600 baud (refer to mcu/UART_DIV)
        HAS_RXUART       = 1    ; Enable UART RXD, word ?RX
        HAS_TXUART       = 1    ; Enable UART TXD, word TX!

        HAS_RXSIM        = 0    ; Enable RxD via GPIO/TIM4, word ?RXGP
        HAS_TXSIM        = 0    ; like HAS_RXSIM, word TXGP!, use for console if > HAS_TXUART
        PSIM         = PORTX    ; Port for UART simulation
        PNRX             = 1    ; Port GPIO# for HAS_RXDSIM
        PNTX             = 1    ; Port GPIO# for HAS_TXDSIM
        CTIM4ARR      = 0xCF    ; reload 104 µs (9600 baud) @ CTIM4PSCR=3
        CTIM4PSCR        = 3    ; TIM4 prescaler 1/(2^n), n: (STM8S 0..7), (STM8L: 0..15)
        SERPRIOTIM       = 0    ; PSIM-PRNX priority to anything that uses that GPIO -> TIMRELOAD

        EMIT_BG  = DROP         ; vectored NUL background EMIT vector
        QKEY_BG  = ZERO         ; NUL background QKEY vector

        HAS_LED7SEG      = 0    ; 7-seg LED display, number of groups (0: none)
        LEN_7SGROUP      = 3    ; default: 3 dig. 7-seg LED

        HAS_KEYS         = 0    ; Board has keys
        HAS_OUTPUTS      = 0    ; Board outputs, e.g. relays
        HAS_INPUTS       = 0    ; Board digital inputs
        HAS_ADC          = 0    ; Board analog inputs

        HAS_BACKGROUND   = 0    ; Background Forth task (TIM1, TIM2 or TIM3 ticker)
        BG_USE_TIM1      = 0    ; Use TIM1 for the Background Task (instead of TIM2)
        BG_USE_TIM3      = 0    ; Use TIM3 for the Background Task (instead of TIM2)
        BG_TIM_REL  = 0x26DE    ; Reload value for Background Task timer (default for 5ms @ HSI 16MHz/8)
        BG_RUNMASK       = 0    ; BG task runs if "(BG_RUNMASK AND TICKCNT) equals 0"
        BSPPSIZE         = 32   ; Default size in bytes of data stack for background tasks

        HAS_CPNVM        = 0    ; Can compile to Flash, always interpret to RAM
        HAS_DOES         = 0    ; DOES> extension
        HAS_DOLOOP       = 0    ; DO .. LOOP extension: DO LEAVE LOOP +LOOP
        HAS_ALIAS        = 1    ; NAME> resolves "alias" (RigTig style), aliases can be in RAM
        HAS_FILEHAND     = 0    ; FILE and HAND for file upload
        HAS_OLDOK        = 0    ; Disable e4thcom file upload support

        USE_CALLDOLIT    = 0    ; use CALL DOLIT instead of the DOLIT TRAP handler (deprecated)
        CASEINSENSITIVE  = 0    ; Case insensitive dictionary search
        EXTNUMPREFIX     = 1    ; Extended number prefix: %: binary, &: decimal
        SPEEDOVERSIZE    = 0    ; Speed-over-size in core words ROT - = < -1 0 1
        MINIDICT         = 0    ; Dictionary in Flash and EEPROM, marks words for unlinking
        BAREBONES        = 0    ; Removes words: '?KEY 'EMIT EXIT EXG @EXECUTE ERASE
                                ;   Drops headers: ?RX TX! ?RXP ?RX TXP! TX! LAST DEPTH COUNT
                                ;     SPACES .R NAME> ABORT" AHEAD
                                ; Drops support for entry of binary (%) and decimal (&)
        BOOTSTRAP        = 0    ; Remove words: (+loop) EXIT 2! 2/ UM+ OR = MAX MIN U. . ? .(
                                ;  [COMPILE] FOR DO BEGIN WHILE ABORT" ." _TYPE dm+ DUMP .S
                                ;  .ID >CHAR <
        UNLINKCORE       = 0    ; Drops headers on everything except: (TODO)
                                ;  ABORT" AFT AGAIN AHEAD BEGIN DO DUMP ELSE EXG FOR IF LEAVE
                                ;  LOOP MAX MIN NEXT OR REPEAT SEE SPACES THEN U. U.R UM+
                                ;  UNTIL WHILE WORDS [COMPILE] _TYPE dm+
        HAS_VARIABLE     = 1    ; VARIABLE and feature "VARIABLE in Flash allocates RAM"
        RAM_VARIABLE    = 32    ; Amount of RAM for VARIABLE claimed by WIPE

        WORDS_LINKINTER  = 0    ; Link interpreter words
        WORDS_LINKCOMP   = 0    ; Link compiler words: cp last OVERT $,n ?UNIQUE $COMPILE
        WORDS_LINKRUNTI  = 0    ; Link runtime words: doLit do$ doVAR donxt dodoes ?branch branch
                                ;    (+loop) $"| ."|
        WORDS_LINKCHAR   = 0    ; Link char out words: DIGIT <# # #S SIGN #> str hld HOLD PACK$
        WORDS_LINKMISC   = 0    ; Link composing words of: >CHAR _TYPE dm+ .ID >NAME

        WORDS_EXTRASTACK = 0    ; Link/include stack core words: rp@ rp! sp! sp@
        WORDS_EXTRADEBUG = 0    ; Extra debug words: >NAME
        WORDS_EXTRACORE  = 0    ; Extra core words: 0= I
        WORDS_EXTRAMEM   = 0    ; Extra memory words: B! 2C@ 2C!
        WORDS_EXTRAEEPR  = 0    ; Extra EEPROM lock/unlock words: LOCK ULOCK


        UNLINK_COLD      = 0    ; "COLD"
        UNLINK_TBOOT     = 2    ; "'BOOT"
        UNLINK_HI        = 2    ; "hi"
        UNLINK_QRX       = 0    ; "?RX"
        UNLINK_TXSTOR    = 0    ; "TX!"
        UNLINK_QRXP      = 0    ; "?RXP"
        UNLINK_QRX       = 0    ; "?RX"
        UNLINK_TXPSTOR   = 0    ; "TXP!"
        UNLINK_TXSTOR    = 0    ; "TX!"
        UNLINK_QKEY      = 0    ; "?KEY"
        UNLINK_EMIT      = 0    ; "EMIT"
        UNLINK_DOLIT     = 1    ; "doLit"
        UNLINK_DOPLOOP   = 1    ; "(+loop)"
        UNLINK_LEAVE     = 0    ; "LEAVE"
        UNLINK_DONXT     = 1    ; "donxt"
        UNLINK_QBRAN     = 1    ; "?branch"
        UNLINK_BRAN      = 1    ; "branch"
        UNLINK_EXECU     = 0    ; "EXECUTE"
        UNLINK_EXIT      = 0    ; "EXIT"
        REMOVE_EXIT      = 0    ; remove "EXIT"
        UNLINK_DSTOR     = 0    ; "2!"
        UNLINK_DAT       = 0    ; "2@"
        UNLINK_DCSTOR    = 0    ; "2C!"
        UNLINK_DCAT      = 0    ; "2C@"
        UNLINK_BRSS      = 0    ; "B!"
        UNLINK_AT        = 0    ; "@"
        UNLINK_STORE     = 0    ; "!"
        UNLINK_CAT       = 0    ; "C@"
        UNLINK_CSTOR     = 0    ; "C!"
        UNLINK_IGET      = 0    ; "I"
        UNLINK_RFROM     = 0    ; "R>"
        UNLINK_DOVARPTR  = 1    ; "doVarPtr"
        UNLINK_DOVAR     = 1    ; "doVar"
        UNLINK_RAT       = 0    ; "R@"
        UNLINK_TOR       = 0    ; ">R"
        UNLINK_NIP       = 0    ; "NIP"
        UNLINK_DROP      = 0    ; "DROP"
        UNLINK_DDROP     = 0    ; "2DROP"
        UNLINK_DUPP      = 0    ; "DUP"
        UNLINK_SWAPP     = 0    ; "SWAP"
        UNLINK_OVER      = 0    ; "OVER"
        UNLINK_UPLUS     = 0    ; "UM+"
        UNLINK_PLUS      = 0    ; "+"
        UNLINK_XORR      = 0    ; "XOR"
        UNLINK_ANDD      = 0    ; "AND"
        UNLINK_ORR       = 0    ; "OR"
        UNLINK_ZLESS     = 0    ; "0<"
        UNLINK_SUBB      = 0    ; "-"
        UNLINK_CNTXT     = 1    ; "CONTEXT"
        UNLINK_CPP       = 1    ; "cp"
        UNLINK_BASE      = 0    ; "BASE"
        UNLINK_INN       = 1    ; ">IN"
        UNLINK_NTIB      = 1    ; "#TIB"
        UNLINK_TEVAL     = 1    ; "'eval"
        UNLINK_HLD       = 1    ; "hld"
        UNLINK_TEMIT     = 0    ; "'EMIT"
        UNLINK_TQKEY     = 0    ; "'?KEY"
        UNLINK_LAST      = 0    ; "last"
        UNLINK_TIB       = 1    ; "TIB"
        UNLINK_OUTA      = 0    ; "OUT"
        UNLINK_BLANK     = 1    ; "BL"
        UNLINK_ZERO      = 0    ; "0"
        UNLINK_ONE       = 0    ; "1"
        UNLINK_MONE      = 0    ; "-1"
        UNLINK_TIMM      = 0    ; "TIM"
        UNLINK_BGG       = 0    ; "BG"
        UNLINK_TPROMPT   = 1    ; "'PROMPT"
        UNLINK_HANDD     = 0    ; "HAND"
        UNLINK_FILEE     = 0    ; "FILE"
        UNLINK_QDUP      = 0    ; "?DUP"
        UNLINK_ROT       = 0    ; "ROT"
        UNLINK_DDUP      = 0    ; "2DUP"
        UNLINK_DNEGA     = 2    ; "DNEGATE"
        UNLINK_EQUAL     = 0    ; "="
        UNLINK_ULESS     = 0    ; "U<"
        UNLINK_LESS      = 0    ; "<"
        UNLINK_MAX       = 0    ; "MAX"
        UNLINK_MIN       = 0    ; "MIN"
        UNLINK_WITHI     = 0    ; "WITHIN"
        UNLINK_UMMOD     = 0    ; "UM/MOD"
        UNLINK_MSMOD     = 0    ; "M/MOD"
        UNLINK_SLMOD     = 0    ; "/MOD"
        UNLINK_MMOD      = 0    ; "MOD"
        UNLINK_SLASH     = 0    ; "/"
        UNLINK_UMSTA     = 0    ; "UM*"
        UNLINK_STAR      = 0    ; "*"
        UNLINK_MSTAR     = 0    ; "M*"
        UNLINK_SSMOD     = 0    ; "*/MOD"
        UNLINK_STASL     = 0    ; "*/"
        UNLINK_EXG       = 0    ; "EXG"
        UNLINK_TWOSL     = 0    ; "2/"
        UNLINK_CELLS     = 0    ; "2*"
        UNLINK_CELLM     = 0    ; "2-"
        UNLINK_CELLP     = 0    ; "2+"
        UNLINK_ONEM      = 0    ; "1-"
        UNLINK_ONEP      = 0    ; "1+"
        UNLINK_INVER     = 0    ; "NOT"
        UNLINK_NEGAT     = 0    ; "NEGATE"
        UNLINK_ABSS      = 0    ; "ABS"
        UNLINK_ZEQUAL    = 2    ; "0="
        UNLINK_PICK      = 0    ; "PICK"
        UNLINK_TCHAR     = 1    ; ">CHAR"
        UNLINK_DEPTH     = 0    ; "DEPTH"
        UNLINK_PSTOR     = 0    ; "+!"
        UNLINK_COUNT     = 0    ; "COUNT"
        UNLINK_HERE      = 0    ; "HERE"
        UNLINK_PAD       = 1    ; "PAD"
        UNLINK_ATEXE     = 1    ; "@EXECUTE"
        UNLINK_CMOVE     = 0    ; "CMOVE"
        UNLINK_FILL      = 0    ; "FILL"
        UNLINK_ERASE     = 0    ; "ERASE"
        UNLINK_PACKS     = 1    ; "PACK$"
        UNLINK_DIGIT     = 1    ; "DIGIT"
        REMOVE_DIGIT     = 1    ; remove "DIGIT"
        UNLINK_EXTRC     = 1    ; "EXTRACT"
        REMOVE_EXTRC     = 1    ; remove "EXTRACT"
        UNLINK_BDIGS     = 2    ; "<#"
        UNLINK_HOLD      = 2    ; "HOLD"
        UNLINK_DIG       = 2    ; "#"
        UNLINK_DIGS      = 2    ; "#S"
        UNLINK_SIGN      = 2    ; "SIGN"
        UNLINK_EDIGS     = 2    ; "#>"
        UNLINK_STR       = 1    ; "str"
        UNLINK_HEX       = 0    ; "HEX"
        UNLINK_DECIM     = 0    ; "DECIMAL"
        UNLINK_NUMBQ     = 1    ; "NUMBER?"
        UNLINK_DIGTQ     = 1    ; "DIGIT?"
        UNLINK_KEY       = 0    ; "KEY"
        UNLINK_NUFQ      = 1    ; "NUF?"
        REMOVE_NUFQ      = 1    ; remove "NUF?"
        UNLINK_SPACE     = 0    ; "SPACE"
        UNLINK_SPACS     = 1    ; "SPACES"
        UNLINK_CR        = 0    ; "CR"
        UNLINK_DOSTR     = 1    ; "do$"
        UNLINK_STRQP     = 1    ; '$"|'
        UNLINK_DOTQP     = 1    ; '."|'
        UNLINK_DOTR      = 0    ; ".R"
        UNLINK_UDOTR     = 0    ; "U.R"
        UNLINK_TYPES     = 0    ; "TYPE"
        UNLINK_UDOT      = 0    ; "U."
        UNLINK_DOT       = 0    ; "."
        UNLINK_QUEST     = 0    ; "?"
        UNLINK_PARS      = 1    ; "SPARSE"
        UNLINK_PARSE     = 1    ; "PARSE"
        UNLINK_DOTPR     = 0    ; ".("
        UNLINK_PAREN     = 0    ; "("
        UNLINK_BKSLA     = 0    ; "\"
        UNLINK_WORDD     = 1    ; "WORD"
        UNLINK_TOKEN     = 1    ; "TOKEN"
        UNLINK_NAMET     = 0    ; "NAME>"
        UNLINK_SAMEQ     = 1    ; "SAME?"
        UNLINK_CUPPER    = 1    ; "CUPPER"
        UNLINK_NAMEQ     = 1    ; "NAME?"
        UNLINK_FIND      = 1    ; "find"
        UNLINK_BKSP      = 1    ; "^h"
        UNLINK_TAP       = 1    ; "TAP"
        UNLINK_KTAP      = 1    ; "kTAP"
        UNLINK_ACCEP     = 1    ; "ACCEPT"
        UNLINK_QUERY     = 1    ; "QUERY"
        UNLINK_ABORT     = 2    ; "ABORT"
        UNLINK_ABORQ     = 1    ; "aborq"
        UNLINK_PRESE     = 1    ; "PRESET"
        UNLINK_INTER     = 1    ; "$INTERPRET"
        UNLINK_LBRAC     = 0    ; "["
        UNLINK_DOTOK     = 1    ; ".OK"
        UNLINK_QSTAC     = 1    ; "?STACK"
        UNLINK_EVAL      = 1    ; "EVAL"
        UNLINK_QUIT      = 1    ; "QUIT"
        UNLINK_TICK      = 0    ; "'"
        UNLINK_COMMA     = 0    ; ","
        UNLINK_CCOMMA    = 0    ; "C,"
        UNLINK_JSRC      = 0    ; "CALL,"
        UNLINK_LITER     = 0    ; "LITERAL"
        UNLINK_BCOMP     = 1    ; "[COMPILE]"
        REMOVE_BCOMP     = 1    ; remove "[COMPILE]"
        UNLINK_COMPI     = 1    ; "COMPILE"
        REMOVE_COMPI     = 1    ; remove "COMPILE"
        UNLINK_STRCQ     = 1    ; "$,""
        UNLINK_FOR       = 0    ; "FOR"
        UNLINK_NEXT      = 0    ; "NEXT"
        UNLINK_DOO       = 0    ; "DO"
        UNLINK_LOOP      = 0    ; "LOOP"
        UNLINK_PLOOP     = 0    ; "+LOOP"
        UNLINK_BEGIN     = 0    ; "BEGIN"
        UNLINK_UNTIL     = 0    ; "UNTIL"
        UNLINK_AGAIN     = 0    ; "AGAIN"
        UNLINK_IFF       = 0    ; "IF"
        UNLINK_THENN     = 0    ; "THEN"
        UNLINK_ELSE      = 0    ; "ELSE"
        UNLINK_AHEAD     = 1    ; "AHEAD"
        UNLINK_WHILE     = 0    ; "WHILE"
        UNLINK_REPEA     = 0    ; "REPEAT"
        UNLINK_AFT       = 0    ; "AFT"
        UNLINK_ABRTQ     = 0    ; 'ABORT"'
        UNLINK_STRQ      = 0    ; '$"'
        UNLINK_DOTQ      = 0    ; '."'
        UNLINK_UNIQU     = 1    ; "?UNIQUE"
        UNLINK_SNAME     = 1    ; "$,n"
        UNLINK_SCOMP     = 1    ; "$COMPILE"
        UNLINK_OVERT     = 0    ; "OVERT"
        UNLINK_SEMIS     = 0    ; ";"
        UNLINK_COLON     = 0    ; ":"
        UNLINK_RBRAC     = 0    ; "]"
        UNLINK_DOESS     = 0    ; "DOES>"
        UNLINK_DODOES    = 1    ; "dodoes"
        UNLINK_CREAT     = 0    ; "CREATE"
        UNLINK_CONST     = 0    ; "CONSTANT"
        UNLINK_DOCON     = 1    ; "docon"
        UNLINK_VARIA     = 0    ; "VARIABLE"
        UNLINK_ALLOT     = 0    ; "ALLOT"
        UNLINK_IMMED     = 0    ; "IMMEDIATE"
        UNLINK_UTYPE     = 1    ; "_TYPE"
        UNLINK_DUMPP     = 1    ; "dm+"
        UNLINK_DUMP      = 0    ; "DUMP"
        REMOVE_DUMP      = 0    ; remove "DUMP"
        UNLINK_DOTS      = 0    ; ".S"
        REMOVE_DOTS      = 0    ; remove ".S"
        UNLINK_DOTID     = 1    ; ".ID"
        UNLINK_TNAME     = 1    ; ">NAME"
        REMOVE_TNAME     = 1    ; remove ">TNAME"
        UNLINK_WORDS     = 0    ; "WORDS"
        UNLINK_EMIT7S    = 0    ; "E7S"
        UNLINK_PUT7S     = 0    ; "P7S"
        UNLINK_QKEYB     = 0    ; "?KEYB"
        UNLINK_ADCSTOR   = 0    ; "ADC!"
        UNLINK_ADCAT     = 0    ; "ADC@"
        UNLINK_SPSTO     = 0    ; "sp!"
        UNLINK_SPAT      = 0    ; "sp@"
        UNLINK_RPAT      = 0    ; "rp@"
        UNLINK_RPSTO     = 0    ; "rp!"
        UNLINK_ULOCK     = 0    ; "ULOCK"
        UNLINK_LOCK      = 0    ; "LOCK"
        UNLINK_UNLOCK_FLASH = 1 ; "ULOCKF"
        UNLINK_LOCK_FLASH = 1   ; "LOCKF"
        UNLINK_NVMM      = 0    ; "NVM"
        UNLINK_RAMM      = 0    ; "RAM"
        UNLINK_RESETT    = 0    ; "RESET"
        UNLINK_SAVEC     = 0    ; "SAVEC"
        UNLINK_RESTC     = 0    ; "IRET"
        UNLINK_WIPE      = 1    ; "WIPE"
        UNLINK_POSTP     = 0    ; "POSTPONE"
