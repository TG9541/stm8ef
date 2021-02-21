; STM8EF for STM8S (Value line and Access Line devices)
;
; This is derived work based on
; http://www.forth.org/svfig/kk/07-2010.html
;
; Please refer to LICENSE.md for more information.
;
;--------------------------------------------------------
; Original author, and copyright:
;       STM8EF, Version 2.1, 13jul10cht
;       Copyright (c) 2000
;       Dr. C. H. Ting
;       156 14th Avenue
;       San Mateo, CA 94402
;       (650) 571-7639
;
; Original main description:
;       FORTH Virtual Machine:
;       Subroutine threaded model
;       SP Return stack pointer
;       X Data stack pointer
;       A,Y Scratch pad registers
;
;--------------------------------------------------------
; The latest version of this code is available at
; https://github.com/TG9541/stm8ef
;
;
; Docs for the SDCC integrated assembler are scarce, thus
; SDCC was used to write the skeleton for this file.
; However, the code in this file isn't SDCC code.
;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (Linux)
;--------------------------------------------------------

        .module forth
        .optsdcc -mstm8

;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------

        .globl _TRAP_Handler
        .globl _forth

;--------------------------------------------------------
; ram data
;--------------------------------------------------------
        .area DATA

;--------------------------------------------------------
; ram data
;--------------------------------------------------------
        .area INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
        .area DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
        .area HOME
        .area GSINIT
        .area GSFINAL
        .area GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
        .area HOME
        .area HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
        .area CODE

        ;************************************
        ;******  1) General Constants  ******
        ;************************************

        TRUEE   =     0xFFFF    ; true flag
        COMPO   =     0x40      ; "COMPO" lexicon compile only bit
        IMEDD   =     0x80      ; "IMEDD" lexicon immediate bit
        MASKK   =     0x1F7F    ; "MASKK" lexicon bit mask

        TIBLENGTH =   80        ; size of TIB (starting at TIBOFFS)
        PADOFFS =     80        ; "PADOFFS" offset text buffer above dictionary
        CELLL   =      2        ; size of a cell
        BASEE   =     10        ; default radix
        BKSPP   =      8        ; backspace
        LF      =     10        ; line feed
        PACE    =     11        ; pace character for host handshake (ASCII VT)
        CRR     =     13        ; carriage return
        ERR     =     27        ; error escape
        TIC     =     39        ; tick

        EXIT_OPC =    0x81      ; RET opcode
        DOLIT_OPC =   0x83      ; TRAP opcode as DOLIT
        CALLR_OPC =   0xAD      ; CALLR opcode for relative addressing
        BRAN_OPC =    0xCC      ; JP opcode
        CALL_OPC =    0xCD      ; CALL opcode

        ; Chip type (set of peripheral addresses and features)
        STM8S_LOD        = 103  ; STM8S Low Density
        STM8S_MED        = 105  ; STM8S Medium Density
        STM8S_HID        = 207  ; STM8S High Density
        STM8L_LOD        = 051  ; STM8L Low Density, RM0031 family
        STM8L_101        = 101  ; STM8L Low Density, RM0013 family
        STM8L_MHD        = 152  ; STM8L Medium and High Density

        ; STM8 family flags
        STM8S            = 0    ; FAMILY: STM8S device
        STM8L            = 1    ; FAMILY: STM8L device

        ; legacy chip type (deprecated - preferably use the chip type constants)
        STM8L101F3 = STM8L_101  ; L core, 8K flash incl EEPROM, 1.5K RAM, UART1
        STM8L051F3 = STM8L_LOD  ; L core, 8K flash, 1K RAM, 256 EEPROM, UART1
        STM8L152C6 = STM8L_MHD  ; L core, 32K flash, 2K RAM, 1K EEPROM, UART1
        STM8L152R8 = STM8L_MHD  ; L core, 64K flash, 4K RAM, 2K EEPROM, UART1
        STM8S003F3 = STM8S_LOD  ; 8K flash, 1K RAM, 128 EEPROM, UART1
        STM8S103F3 = STM8S_LOD  ; like STM8S003F3, 640 EEPROM
        STM8S105K4 = STM8S_MED  ; 16K/32K flash, 2K RAM, 1K EEPROM, UART2
        STM8S207RB = STM8S_HID  ; 32K+96K flash, 6K RAM, 2K EEPROM, UART1 or UART2

        DEFOSCFREQ     = 16000  ; default oscillator frequency in kHz (HSI)

        ;********************************************
        ;******  2) Device hardware addresses  ******
        ;********************************************

        ;******  STM8 memory addresses ******
        RAMBASE =       0x0000  ; STM8 RAM start

        ; STM8 device specific include (provided by file in board folder)
        ; sets "TARGET" and memory layout
        .include        "target.inc"

        ; STM8 Flash Block Size (depends on "TARGET")
        .ifeq   (TARGET - STM8S_LOD) * (TARGET - STM8L_101) * (TARGET - STM8L_LOD)
          PAGESIZE   =     0x40      ; "PAGESIZE" STM8 Low Density: 64 byte page size
        .else
          PAGESIZE   =     0x80      ; "PAGESIZE" STM8 M/H Density: 128 byte page size
        .endif

        ; STM8 family register addresses (depends on "TARGET")
        .ifeq   (TARGET - STM8S_LOD) * (TARGET - STM8S_MED) * (TARGET - STM8S_HID)
          FAMILY = STM8S
          .include  "stm8device.inc"
        .endif
        .ifeq   (TARGET - STM8L_101) * (TARGET - STM8L_LOD) * (TARGET - STM8L_MHD)
          FAMILY = STM8L
          .include  "stm8ldevice.inc"
        .endif


        ;**********************************
        ;******  3) Global defaults  ******
        ;**********************************
        ; Note: add defaults for new features here
        ;       and configure them in globconf.inc

        .include  "defconf.inc"

        ;********************************************
        ;******  4) Device dependent features  ******
        ;********************************************
        ; Define memory location for device dependent features here

        .include "globconf.inc"

        .include "linkopts.inc"

        ; console configuration: check if TX simulation has priority over UART
        .ifge   HAS_TXSIM - HAS_TXUART
        .ifeq  PNTX-PNRX
        CONSOLE_HALF_DUPLEX = 1 ; single wire RX/TX simulation is half duplex
        .else
        CONSOLE_HALF_DUPLEX = 0 ; RX/TX simulation supports full duplex
        .endif
        .else
        CONSOLE_HALF_DUPLEX = HALF_DUPLEX ; use hardware UART settings
        .endif

        OSCFREQ   = DEFOSCFREQ  ; "OSCFREQ" oscillator frequency in kHz
        CRAMLEN   = FORTHRAM    ; "CRAMLEN" RAM starting from 0 not used by Forth

        ;**************************************
        ;******  5) Board Driver Memory  ******
        ;**************************************
        ; Memory for board related code, e.g. interrupt routines

        RAMPOOL =    FORTHRAM   ; RAM for variables (growing up)

        .macro  RamByte varname
        varname = RAMPOOL
        RAMPOOL = RAMPOOL + 1
        .endm

        .macro  RamWord varname
        varname = RAMPOOL
        RAMPOOL = RAMPOOL + 2
        .endm

        .macro  RamBlck varname, size
        varname = RAMPOOL
        RAMPOOL = RAMPOOL + size
        .endm


        ;**************************************************
        ;******  6) General User & System Variables  ******
        ;**************************************************

        ; ****** Indirect variables for code in NVM *****
        .ifne   HAS_CPNVM
        ISPPSIZE  =     16      ; Size of data stack for interrupt tasks
        .else
        ISPPSIZE  =     0       ; no interrupt tasks without NVM
        .endif

        UPP   = UPPLOC          ; "C_UPP"  offset user area
        PADBG = UPPLOC-1        ; PAD in background task growing down from here
        CTOP  = CTOPLOC         ; dictionary start, growing up
                                ; note: PAD is inbetween CTOP and SPP
        SPP   = ISPP-ISPPSIZE   ; "C_SPP"  data stack, growing down (with SPP-1 first)
        ISPP  = SPPLOC-BSPPSIZE ; "C_ISPP" Interrupt data stack, growing down
        BSPP  = SPPLOC          ; "C_BSPP" Background data stack, growing down
        TIBB  = SPPLOC          ; "C_TIB"  Term. Input Buf. TIBLENGTH between SPPLOC and RPP
        RPP   = RPPLOC          ; "C_RPP"  return stack, growing down

        ; Core variables (same order as 'BOOT initializer block)

        USRRAMINIT = USREMIT

        USREMIT  =   UPP+0      ; "'EMIT" execution vector of EMIT
        USRQKEY =    UPP+2      ; "'?KEY" execution vector of QKEY
        USRBASE =    UPP+4      ; "BASE" radix base for numeric I/O
        ; USR_6 =    UPP+6      ; free
        USRPROMPT =  UPP+8      ; "'PROMPT" point to prompt word (default .OK)
        USRCP   =    UPP+10     ; "CP" point to top of dictionary
        USRLAST =    UPP+12     ; "LAST" currently last name in dictionary
        NVMCP   =    UPP+14     ; point to top of dictionary in Non Volatile Memory

        ; Null initialized core variables (growing down)

        USRCTOP  =   UPP+16     ; "CTOP" point to the start of RAM dictionary
        USRVAR  =    UPP+18     ; "VAR" point to next free USR RAM location
        NVMCONTEXT = UPP+20     ; point to top of dictionary in Non Volatile Memory
        USRCONTEXT = UPP+22     ; "CONTEXT" start vocabulary search
        USREVAL =    UPP+24     ; "'EVAL" execution vector of EVAL
        USRNTIB =    UPP+26     ; "#TIB" count in terminal input buffer
        USR_IN  =    UPP+28     ; ">IN" hold parsing pointer
        USRBUFFER =  UPP+30     ; "BUFFER" address, defaults to TIBB

        ; More core variables in zero page (instead of assigning fixed addresses)
        RamWord USRHLD          ; "HLD" hold a pointer of output string
        RamWord YTEMP           ; extra working register for core words
        RamWord USRIDLE         ; "'IDLE" idle routine in KEY

        ;***********************
        ;******  7) Code  ******
        ;***********************

;        ==============================================
;        Forth header macros
;        Macro support in SDCC's assembler "SDAS" has some quirks:
;          * strings with "," and ";" aren't allowed in parameters
;          * after include files, the first macro call may fail
;            unless it's preceded by unconditional code
;         ==============================================

        LINK =          0       ;

        .macro  HEADER Label wName
        .ifeq   UNLINK_'Label
        .dw     LINK
        LINK    = .
        .db      (102$ - 101$)
101$:
        .ascii  wName
102$:
        .endif
;'Label:
        .endm

        .macro  HEADFLG Label wName wFlag
        .ifeq   UNLINK_'Label
        .dw     LINK
        LINK    = .
        .db      ((102$ - 101$) + wFlag)
101$:
        .ascii  wName
102$:
        .endif
;'Label:
        .endm

;       ==============================================
;               Low level code
;       ==============================================

;       TRAP handler for DOLIT
;       Push the inline literal following the TRAP instruction
_TRAP_Handler:
        .ifeq  USE_CALLDOLIT
        DECW    X
        DECW    X
        LDW     (3,SP),X               ; XH,XL
        EXGW    X,Y
        LDW     X,(8,SP)               ; PC MSB/LSB
        LDW     X,(X)
        LDW     (Y),X
        LDW     (5,SP),X               ; YH,YL
        LDW     X,(8,SP)
        INCW    X
        INCW    X
        LDW     (8,SP),X
        IRET

;       Macros for inline literals using the TRAP approach

        .macro DoLitC c
        TRAP
        .dw     c
        .endm

        .macro DoLitW w
        TRAP
        .dw     w
        .endm

        .else

;       Macros for inline literals using CALL DOLIT / CALL DOLITC
        .macro DoLitC c
        call    DOLITC
        .db     c
        .endm

        .macro DoLitW w
        call    DOLIT
        .dw     w
        .endm

        .endif

; ==============================================

;       Includes for board support code
;       Board I/O initialization and E/E mapping code
;       Hardware dependent words, e.g.  BKEY, OUT!
        .include "boardcore.inc"

;       ADC routines depending on STM8 family
        .include "stm8_adc.inc"

;       Generic board I/O: 7S-LED rendering, board key mapping
        .include "board_io.inc"

;       Simulate serial interface code
        .include "sser.inc"

;       Background Task: context switch with wakeup unit or timer
        .include "bgtask.inc"

; ==============================================

;       Configuation table with shadow data for RESET

;       'BOOT   ( -- a )
;       The application startup vector and NVM USR setting array

        HEADER  TBOOT "'BOOT"
TBOOT:
        CALL    DOVAR
        UBOOT = .
        .dw     HI              ; start-up code (can be changed with 'BOOT !)

        ; COLD initialization data (can be changed with <offset> 'BOOT + !)
        UZERO = .
        .ifge   (HAS_TXUART-HAS_TXSIM)
        .dw     TXSTOR          ; TX! as EMIT vector
        .dw     QRX             ; ?KEY as ?KEY vector
        .else
        .dw     TXPSTOR         ; TXP! as EMIT vector if (HAS_TXSIM > HAS_TXUART)
        .dw     QRXP            ; ?RXP as ?KEY vector
        .endif
        .dw     BASEE           ; BASE
        .dw     0               ; (vacant)
        .dw     DOTOK           ; 'PROMPT
        COLDCTOP = .
        .dw     CTOP            ; CP in RAM
        COLDCONTEXT = .
        .dw     LASTN           ; USRLAST
        .ifne   HAS_CPNVM
        COLDNVMCP = .
        .dw     END_SDCC_FLASH  ; CP in NVM
        ULAST = .

        ; Shadow initialization data for RESET (can be changed with PERSIST)
        UDEFAULTS = .
        .dw     HI              ; 'BOOT
        .ifge   (HAS_TXUART-HAS_TXSIM)
        .dw     TXSTOR          ; TX! as EMIT vector
        .dw     QRX             ; ?KEY as ?KEY vector
        .else
        .dw     TXPSTOR         ; TXP! as EMIT vector
        .dw     QRXP            ; ?RXP as ?KEY vector
        .endif
        .dw     BASEE           ; BASE
        .dw     0               ; (vacant)
        .dw     DOTOK           ; 'PROMPT
        .dw     CTOP            ; CP in RAM
        .dw     LASTN           ; CONTEXT pointer
        .dw     END_SDCC_FLASH  ; CP in NVM
        .else
        ULAST = .
        .endif

;       Main entry points and COLD start data

;       COLD    ( -- )
;       The hilevel cold start sequence.
        HEADER  COLD "COLD"

_forth:                         ; SDCC entry
        ; Note: no return to main.c possible unless RAMEND equals SP,
        ; and RPP init skipped

COLD:
        SIM                     ; disable interrupts
        MOV     CLK_CKDIVR,#0   ; Clock divider register

        LDW     X,#(RAMEND-FORTHRAM)
1$:     CLR     (FORTHRAM,X)
        DECW    X
        JRPL    1$

        LDW     X,#RPP          ; return stack, growing down
        LDW     SP,X            ; initialize return stack

        ; see "boardcore.inc")
        CALL    BOARDINIT       ; "PC_BOARDINIT" Board initialization

        BGTASK_Init             ; macro for init of BG task timer, refer to bgtask.inc

        .ifne   HAS_RXUART+HAS_TXUART
        ; Init RS232 communication port
        ; STM8S[01]003F3 init UART
        LDW     X,#CUARTBRR      ; "UARTBRR" def. $6803 / 9600 baud
        LDW     UART_BRR1,X
        .ifne   HAS_RXUART*HAS_TXUART
        MOV     UART_CR2,#0x0C  ; Use UART1 full duplex
        .ifne   HALF_DUPLEX
        .ifeq   (FAMILY - STM8S)
        .ifeq   (HALF_DUPLEX - 1)
        ; STM8S UART1, UART4: pull-up for PD5 single-wire UART
        BRES    PD_DDR,#5       ; PD5 GPIO input high
        BSET    PD_CR1,#5       ; PD5 GPIO pull-up
        .endif
        .ifeq   (HALF_DUPLEX - 2)
        ; STM8S903 type Low Density devices can re-map UART-TX to PA3
        LD      A,OPT2
        AND     A,#0x03
        CP      A,#0x03
        JREQ    $1
        ; pull-up for PD5 single-wire UART
        BRES    PD_DDR,#5       ; PD5 GPIO input high
        BSET    PD_CR1,#5       ; PD5 GPIO pull-up
        JRA     $2
$1:
        ; pull-up for PA3 single-wire UART
        BRES    PA_DDR,#3       ; PA3 GPIO input high
        BSET    PA_CR1,#3       ; PA3 GPIO pull-up
$2:
        .endif
        .endif
        MOV     UART_CR5,#0x08 ; UART1 Half-Duplex
        .endif
        .else
        .ifne   HAS_TXUART
        MOV     UART_CR2,#0x08  ; UART1 enable tx
        .endif
        .ifne   HAS_RXUART
        MOV     UART_CR2,#0x04  ; UART1 enable rx
        .endif
        .endif
        .endif

        SSER_Init               ; macro for init of simulated serial, refer to sser.inc

        Board_IO_Init           ; macro board_io initialization (7S-LED)

        CALL    PRESE           ; initialize data stack, TIB

        DoLitW  UZERO
        DoLitC  USRRAMINIT
        DoLitC  (ULAST-UZERO)
        CALL    CMOVE           ; initialize user area

        CALL    WIPE            ; initialize dictionary

        ; Hardware initialization complete
        RIM                     ; enable interrupts

        CALL    [TBOOT+3]       ; application boot
        JP      QUIT            ; start interpretation

; ==============================================

;       Device dependent I/O

        .ifne   HAS_RXUART
;       ?RX     ( -- c T | F )  ( TOS STM8: -- Y,Z,N )
;       Return serial interface input char from and true, or false.

        HEADER  QRX "?RX"
QRX:
        CLR     A               ; A: flag false
        BTJF    UART_SR,#5,1$
        LD      A,UART_DR      ; get char in A
1$:     JP      ATOKEY          ; push char or flag false
        .endif

        .ifne   HAS_TXUART
;       TX!     ( c -- )
;       Send character c to the serial interface.

        HEADER  TXSTOR "TX!"
TXSTOR:
        INCW    X
        LD      A,(X)
        INCW    X

        .ifne   HALF_DUPLEX
        ; HALF_DUPLEX with normal UART (e.g. wired-or Rx and Tx)
1$:     BTJF    UART_SR,#7,1$  ; loop until tdre
        BRES    UART_CR2,#2    ; disable rx
        LD      UART_DR,A      ; send A
2$:     BTJF    UART_SR,#6,2$  ; loop until tc
        BSET    UART_CR2,#2    ; enable rx
        .else                  ; not HALF_DUPLEX
1$:     BTJF    UART_SR,#7,1$  ; loop until tdre
        LD      UART_DR,A      ; send A
        .endif
        RET
        .endif


; ==============================================

;       Device independent I/O

;       ?KEY    ( -- c T | F )  ( TOS STM8: -- Y,Z,N )
;       Return input char and true, or false.
        HEADER  QKEY "?KEY"
QKEY:
        JP      [USRQKEY]

;       EMIT    ( c -- )
;       Send character c to output device.

        HEADER  EMIT "EMIT"
EMIT:
        JP      [USREMIT]

; ==============================================
; The kernel

;       PUSHLIT ( - C )
;       Subroutine for DOLITC and CCOMMALIT
PUSHLIT:
        LDW     Y,(3,SP)
        DECW    X               ; LSB = literal
        LD      A,(Y)
        LD      (X),A
        DECW    X               ; MSB = 0
        CLR     A
        LD      (X),A
        RET

;       CCOMMALIT ( - )
;       Compile inline literall byte into code dictionary.
CCOMMALIT:
        CALLR   PUSHLIT
        CALL    CCOMMA
CSKIPRET:
        POPW    Y
        JP      (1,Y)

        .ifne   USE_CALLDOLIT

;       DOLITC  ( - C )
;       Push an inline literal character (8 bit).
DOLITC:
        CALLR   PUSHLIT
        JRA     CSKIPRET

;       doLit   ( -- w )
;       Push an inline literal.

        HEADFLG DOLIT "doLit" COMPO
DOLIT:
        DECW    X               ;SUBW   X,#2
        DECW    X

        LDW     Y,(1,SP)
        LDW     Y,(Y)
        LDW     (X),Y
        JRA     POPYJPY
        .endif

        .ifne   HAS_DOLOOP
;       (+loop) ( +n -- )
;       Add n to index R@ and test for lower than limit (R-CELL)@.

        HEADFLG DOPLOOP "(+loop)" COMPO
DOPLOOP:
        LDW     Y,(5,SP)
        LDW     YTEMP,Y
        LDW     Y,X
        LDW     Y,(Y)
        LD      A,YH
        INCW    X
        INCW    X
        ADDW    Y,(3,SP)
        CPW     Y,YTEMP
        PUSH    CC
        TNZ     A
        JRMI    1$
        POP     CC
        JRSGE   LEAVE
        JRA     2$
1$:     POP     CC
        JRSLT   LEAVE
2$:     LDW     (3,SP),Y
        JRA     BRAN

;       LEAVE   ( -- )
;       Leave a DO .. LOOP/+LOOP loop.

        HEADFLG LEAVE "LEAVE" COMPO
LEAVE:
        ADDW    SP,#6
        POPW    Y               ; DO leaves the address of +loop on the R-stack
        JP      (2,Y)
        .endif

;       donext    ( -- )
;       Code for single index loop.

        HEADFLG DONXT "donxt" COMPO
DONXT:
        LDW     Y,(3,SP)
        DECW    Y
        JRPL    NEX1
        POPW    Y
        POP     A
        POP     A
        JP      (2,Y)
NEX1:   LDW     (3,SP),Y
        JRA     BRAN

;       QDQBRAN     ( n - n )
;       QDUP QBRANCH phrase
QDQBRAN:
        CALL    QDUP
        JRA     QBRAN

;       ?branch ( f -- )
;       Branch if flag is zero.

        HEADFLG QBRAN "?branch" COMPO
QBRAN:
        CALL    YFLAGS          ; Pull TOS to Y, flags
        JREQ    BRAN
POPYJPY:
        POPW    Y
        JP      (2,Y)


;       branch  ( -- )
;       Branch to an inline address.

        HEADFLG BRAN "branch" COMPO    ; NOALIAS
BRAN:
        POPW    Y
        LDW     Y,(Y)
        JP      (Y)


;       EXECUTE ( ca -- )
;       Execute word at ca.

        HEADER  EXECU "EXECUTE"
EXECU:
        CALL    YFLAGS          ; Pull TOS to Y, flags
        JP      (Y)


        .ifeq   REMOVE_EXIT
;       EXIT    ( -- )
;       Terminate a colon definition.

        HEADER  EXIT "EXIT"
EXIT:
        POPW    Y
        RET
        .endif

        .ifeq   BOOTSTRAP
;       2!      ( d a -- )      ( TOS STM8: -- Y,Z,N )
;       Store double integer to address a.

        HEADER  DSTOR "2!"
DSTOR:
        CALL    SWAPP
        CALL    OVER
        CALLR   STORE
        CALL    CELLP
        JRA     STORE
        .endif

        .ifeq   BOOTSTRAP
;       2@      ( a -- d )
;       Fetch double integer from address a.

        HEADER  DAT "2@"
DAT:
        CALL    DUPP
        CALL    CELLP
        CALLR   AT
        CALL    SWAPP
        JRA     AT
        .endif


        .ifne   WORDS_EXTRAMEM
;       2C!  ( n a -- )
;       Store word C-wise to 16 bit HW registers "MSB first"

        HEADER  DCSTOR "2C!"
DCSTOR:
        CALL    YFLAGS          ; a
        LD      A,(X)
        LD      (Y),A           ; write MSB(n) to a
        INCW    X
        LD      A,(X)
        LD      (1,Y),A         ; write LSB(n) to a+1
        INCW    X
        RET


;       2C@  ( a -- n )
;       Fetch word C-wise from 16 bit HW config. registers "MSB first"

        HEADER  DCAT "2C@"
DCAT:
        LDW     Y,X
        LDW     X,(X)
        LD      A,(X)
        LD      (Y),A
        LD      A,(1,X)
        EXGW    X,Y
        LD      (1,X),A
        RET


;       B! ( t a u -- )
;       Set/reset bit #u (0..7) in the byte at address a to bool t
;       Note: creates/executes BSER/BRES + RET code on Data Stack
        HEADER  BRSS "B!"
BRSS:
        LD      A,#0x72         ; Opcode BSET/BRES
        LD      (X),A
        LD      A,(1,X)         ; 2nd byte of BSET/BRES
        SLA     A               ; n *= 2 -> A
        OR      A,#0x10
        LDW     Y,X
        LDW     Y,(4,Y)         ; bool b (0..15) -> Z
        JRNE    1$              ; b!=0: BSET
        INC     A               ; b==0: BRES
1$:     LD      (1,X),A
        LD      A,#EXIT_OPC     ; Opcode RET
        LD      (4,X),A
        LDW     Y,X
        ADDW    X,#6
        JP      (Y)

        .endif


;       @       ( a -- w )      ( TOS STM8: -- Y,Z,N )
;       Push memory location to stack.

        HEADER  AT "@"
AT:
        LDW     Y,X
        LDW     X,(X)
        LDW     X,(X)
        EXGW    X,Y
        LDW     (X),Y
        RET

;       !       ( w a -- )      ( TOS STM8: -- Y,Z,N )
;       Pop data stack to memory.

        HEADER  STORE "!"
STORE:
        CALL    YFLAGS          ; a
        PUSHW   X
        LDW     X,(X)           ; w
        LDW     (Y),X
        POPW    X
        JRA     DROP

;       C@      ( a -- c )      ( TOS STM8: -- A,Z,N )
;       Push byte in memory to stack.
;       STM8: Z,N

        HEADER  CAT "C@"
CAT:
        LDW     Y,X             ; Y=a
        LDW     Y,(Y)
YCAT:
        LD      A,(Y)
        CLR     (X)
        LD      (1,X),A
        RET

;       C!      ( c a -- )
;       Pop     data stack to byte memory.

        HEADER  CSTOR "C!"
CSTOR:
        CALL    YFLAGS
        INCW    X
        LD      A,(X)
        LD      (Y),A
        INCW    X
        RET


;       R>      ( -- w )     ( TOS STM8: -- Y,Z,N )
;       Pop return stack to data stack.

        HEADFLG RFROM "R>" COMPO
RFROM:
        POPW    Y               ; save return addr
        LDW     YTEMP,Y
        POPW    Y
        DECW    X
        DECW    X
        LDW     (X),Y
        JP      [YTEMP]


        .ifne  HAS_CPNVM
;       doVARPTR ( - a )    ( TOS STM8: - Y,Z,N )
DOVARPTR:
        POPW    Y               ; get return addr (pfa)
        LDW     Y,(Y)
        JRA     YSTOR
        .endif

;       doVAR   ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Code for VARIABLE and CREATE.

        HEADFLG DOVAR "doVar" COMPO
DOVAR:
        POPW    Y               ; get return addr (pfa)
        ; fall through

;       Y>  ( -- n )     ( TOS STM8: - Y,Z,N )
;       push Y to stack

;       GENALIAS  YSTOR "Y>"
YSTOR:
        DECW    X               ; SUBW  X,#2
        DECW    X
        LDW     (X),Y           ; push on stack
        RET                     ; go to RET of EXEC

;       R@      ( -- w )        ( TOS STM8: -- Y,Z,N )
;       Copy top of return stack to stack (or the FOR - NEXT index value).

        HEADER  RAT "R@"
RAT:
        LDW     Y,(3,SP)
        JRA     YSTOR

;       >R      ( w -- )      ( TOS STM8: -- Y,Z,N )
;       Push data stack to return stack.

        HEADFLG TOR ">R" COMPO
TOR:
        EXGW    X,Y
        LDW     X,(1,SP)
        PUSHW   X
        LDW     X,Y
        LDW     X,(X)
        EXGW    X,Y
        LDW     (3,SP),Y
        JRA     DROP


;       NIP     ( n1 n2 -- n2 )
;       Drop 2nd item on the stack

        HEADER  NIP "NIP"
NIP:
        CALLR   SWAPP
        JRA     DROP

;       DROP    ( w -- )        ( TOS STM8: -- Y,Z,N )
;       Discard top stack item.

        HEADER  DROP "DROP"
DROP:
        INCW    X               ; ADDW   X,#2
        INCW    X
        LDW     Y,X
        LDW     Y,(Y)
        RET

;       2DROP   ( w w -- )       ( TOS STM8: -- Y,Z,N )
;       Discard two items on stack.

        HEADER  DDROP "2DROP"
DDROP:
        ADDW    X,#4
        RET

;       DUP     ( w -- w w )    ( TOS STM8: -- Y,Z,N )
;       Duplicate top stack item.

        HEADER  DUPP "DUP"
DUPP:
        LDW     Y,X
        LDW     Y,(Y)
        JRA     YSTOR

;       SWAP ( w1 w2 -- w2 w1 ) ( TOS STM8: -- Y,Z,N )
;       Exchange top two stack items.

        HEADER  SWAPP "SWAP"
SWAPP:
        LDW     Y,X
        LDW     X,(2,X)
        PUSHW   X
        LDW     X,Y
        LDW     X,(X)
        EXGW    X,Y
        LDW     (2,X),Y
        POPW    Y
        LDW     (X),Y
        RET

;       OVER    ( w1 w2 -- w1 w2 w1 ) ( TOS STM8: -- Y,Z,N )
;       Copy second stack item to top.

        HEADER  OVER "OVER"
OVER:
        LDW     Y,X
        LDW     Y,(2,Y)
        JRA     YSTOR

        .ifne   WORDS_EXTRACORE
;       I       ( -- n )     ( TOS STM8: -- Y,Z,N )
;       Get inner FOR-NEXT or DO-LOOP index value
        HEADER  IGET "I"
IGET:
        .ifne   HAS_ALIAS
        JP      RAT             ; CF JP: NAME> resolves I as ' R@"
        .else
        JRA     RAT
        .endif
        .endif

        .ifeq   BOOTSTRAP
;       UM+     ( u u -- udsum )
;       Add two unsigned single
;       and return a double sum.

        HEADER  UPLUS "UM+"
UPLUS:
        CALLR   PLUS
        CLR     A
        RLC     A
        JP      ASTOR
        .endif

;       +       ( w w -- sum ) ( TOS STM8: -- Y,Z,N )
;       Add top two items.

        HEADER  PLUS "+"

PLUS:
        LD      A,(1,X) ;D=w
        ADD     A,(3,X)
        LD      (3,X),A
        LD      A,(X)
        ADC     A,(2,X)
LDADROP:
        LD      (2,X),A
        JRA     DROP

;       XOR     ( w w -- w )    ( TOS STM8: -- Y,Z,N )
;       Bitwise exclusive OR.

        HEADER  XORR "XOR"
XORR:
        LD      A,(1,X)         ; D=w
        XOR     A,(3,X)
        LD      (3,X),A
        LD      A,(X)
        XOR     A,(2,X)
        JRA     LDADROP

;       AND     ( w w -- w )    ( TOS STM8: -- Y,Z,N )
;       Bitwise AND.

        HEADER  ANDD "AND"
ANDD:
        LD      A,(1,X)         ; D=w
        AND     A,(3,X)
        LD      (3,X),A
        LD      A,(X)
        AND     A,(2,X)
        JRA     LDADROP

        .ifeq   BOOTSTRAP
;       OR      ( w w -- w )    ( TOS STM8: -- immediate Y,Z,N )
;       Bitwise inclusive OR.

        HEADER  ORR "OR"
ORR:
        LD      A,(1,X)         ; D=w
        OR      A,(3,X)
        LD      (3,X),A
        LD      A,(X)
        OR      A,(2,X)
        JRA     LDADROP
        .endif

;       0<      ( n -- t ) ( TOS STM8: -- A,Z )
;       Return true if n is negative.

        HEADER  ZLESS "0<"
ZLESS:
        CLR     A
        TNZ     (X)
        JRPL    ZL1
        CPL     A               ; true
ZL1:    LD      (X),A
        LD      (1,X),A
        RET

;       -   ( n1 n2 -- n1-n2 )  ( TOS STM8: -- Y,Z,N )
;       Subtraction.

        HEADER  SUBB "-"

SUBB:
        .ifeq   SPEEDOVERSIZE
        CALL    NEGAT           ; (15 cy)
        JRA     PLUS            ; 25 cy (15+10)
        .else
        LDW     Y,X
        LDW     Y,(Y)
        LDW     YTEMP,Y
        INCW    X
        INCW    X
        LDW     Y,X
        LDW     Y,(Y)
        SUBW    Y,YTEMP
        LDW     (X),Y
        RET                     ; 18 cy
        .endif


;       CONTEXT ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Start vocabulary search.

        HEADER  CNTXT "CONTEXT"
        .ifeq  HAS_CPNVM
CNTXT:
        .endif
CNTXT_ALIAS:
        LD      A,#(USRCONTEXT)
        JRA     ASTOR
        .ifne  HAS_CPNVM
CNTXT:
        TNZ     USRCP
        JRPL    CNTXT_ALIAS           ; link NVM to NVM
        LD      A,#(NVMCONTEXT)
        JRA     ASTOR
        .endif


;       CP      ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Point to top of dictionary.

        HEADER  CPP "cp"               ; NOALIAS
CPP:
        LD      A,#(USRCP)
        JRA     ASTOR

; System and user variables

;       BASE    ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Radix base for numeric I/O.

        HEADER  BASE "BASE"
BASE:
        LD      A,#(USRBASE)
        JRA     ASTOR

        .ifeq    UNLINK_INN
;       >IN     ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Hold parsing pointer.

        HEADER  INN ">IN"
INN:
        LD      A,#(USR_IN)
        JRA     ASTOR
        .endif

        .ifeq    UNLINK_NTIB
;       #TIB    ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Count in terminal input buffer.

        HEADER  NTIB "#TIB"
NTIB:
        LD      A,#(USRNTIB)
        JRA     ASTOR
        .endif

        .ifeq    UNLINK_TEVAL
;       'eval   ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Execution vector of EVAL.

        HEADER  TEVAL "'eval"
TEVAL:
        LD      A,#(USREVAL)
        JRA     ASTOR
        .endif

        .ifeq    UNLINK_HLD
;       HLD     ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Hold a pointer of output string.

        HEADER  HLD "hld"
HLD:
        LD      A,#(USRHLD)
        JRA     ASTOR
        .endif

;       'EMIT   ( -- a )     ( TOS STM8: -- A,Z,N )
;       Core variable holding the xt of EMIT for the console

        .ifeq   BAREBONES
        HEADER  TEMIT "'EMIT"
TEMIT:
        LD      A,#(USREMIT)
        JRA     ASTOR
        .endif

;       '?KEY   ( -- a )     ( TOS STM8: -- A,Z,N )
;       Core variable holding the xt of ?KEY for the console

        .ifeq   BAREBONES
        HEADER  TQKEY "'?KEY"
TQKEY:
        LD      A,#(USRQKEY)
        JRA     ASTOR
        .endif

;       LAST    ( -- a )        ( TOS STM8: -- Y,Z,N )
;       Point to last name in dictionary

        HEADER  LAST "last"
LAST:
        LD      A,#(USRLAST)

;       A>  ( -- n )     ( TOS STM8: - Y,Z,N )
;       push A to stack

;       GENALIAS  ASTOR "A>"
ASTOR:
        CLRW    Y
        LD      YL,A
AYSTOR:
        DECW    X               ; SUBW  X,#2
        DECW    X
        LDW     (X),Y           ; push on stack
        RET


;       ATOKEY core ( - c T | f )    ( TOS STM8: - Y,Z,N )
;       Return input char and true, or false.
ATOKEY:
        TNZ     A
        JREQ    1$
        CALLR   1$              ; push char
        JRA     MONE            ; flag true
1$:     JRA     ASTOR           ; push char or flag false


;       TIB     ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Return address of terminal input buffer.

        .ifeq   UNLINK_TIB
        HEADER  TIB "TIB"
TIB:
        DoLitW  TIBB
        RET
        .endif

; Constants

;       BL      ( -- 32 )     ( TOS STM8: -- Y,Z,N )
;       Return 32, blank character.

        HEADER  BLANK "BL"
BLANK:
        LD      A,#32
        JRA     ASTOR

;       0       ( -- 0)     ( TOS STM8: -- Y,Z,N )
;       Return 0.

        HEADER  ZERO "0"
ZERO:
        CLR     A
        JRA     ASTOR

;       1       ( -- 1)     ( TOS STM8: -- Y,Z,N )
;       Return 1.

        HEADER  ONE "1"
ONE:
        LD      A,#1
        JRA     ASTOR

;       -1      ( -- -1)     ( TOS STM8: -- Y,Z,N )
;       Return -1

        HEADER  MONE "-1"
MONE:
        LDW     Y,#0xFFFF
        JRA     AYSTOR

;       'PROMPT ( -- a)     ( TOS STM8: -- Y,Z,N )
;       Return address of PROMPT vector

        .ifeq   UNLINK_TPROMPT
        HEADER  TPROMPT "'PROMPT"
TPROMPT:
        LD      A,#(USRPROMPT)
        JRA     ASTOR
        .endif


        .ifne   HAS_FILEHAND
;       ( -- ) EMIT pace character for handshake in FILE mode
PACEE:
        DoLitC  PACE      ; pace character for host handshake
        JP      [USREMIT]

;       HAND    ( -- )
;       set PROMPT vector to interactive mode
        HEADER  HANDD "HAND"
HANDD:
        LDW     Y,#(DOTOK)
YPROMPT:
        LDW     USRPROMPT,Y
        RET

;       FILE    ( -- )
;       set PROMPT vector to file transfer mode
        HEADER  FILEE "FILE"
FILEE:
        LDW     Y,#(PACEE)
        JRA     YPROMPT
        .endif


; Common functions


;       ?DUP    ( w -- w w | 0 )   ( TOS STM8: -- Y,Z,N )
;       Dup tos if its not zero.
        HEADER  QDUP "?DUP"
QDUP:
        LDW     Y,X
        LDW     Y,(Y)
        JREQ    QDUP1
        DECW    X
        DECW    X
        LDW     (X),Y
QDUP1:  RET

;       ROT     ( w1 w2 w3 -- w2 w3 w1 ) ( TOS STM8: -- Y,Z,N )
;       Rot 3rd item to top.

        HEADER  ROT "ROT"
ROT:
        .ifeq   SPEEDOVERSIZE
        CALL    TOR
        CALLR   1$
        CALL    RFROM
1$:     JP      SWAPP
        .else
        LDW     Y,X
        LDW     X,(4,X)
        PUSHW   X
        LDW     X,Y
        LDW     X,(2,X)
        PUSHW   X
        LDW     X,Y
        LDW     X,(X)
        EXGW    X,Y
        LDW     (2,X),Y
        POPW    Y
        LDW     (4,X),Y
        POPW    Y
        LDW     (X),Y
        RET
        .endif

;       2DUP    ( w1 w2 -- w1 w2 w1 w2 )
;       Duplicate top two items.

        HEADER  DDUP "2DUP"
DDUP:
        CALLR    1$
1$:
        JP      OVER

        .ifeq   UNLINKCORE
;       DNEGATE ( d -- -d )     ( TOS STM8: -- Y,Z,N )
;       Two's complement of top double.

        HEADER  DNEGA "DNEGATE"
DNEGA:
        LDW     Y,X
        LDW     Y,(2,Y)
        NEGW    Y
        PUSH    CC
        LDW     (2,X),Y
        LDW     Y,X
        LDW     Y,(Y)
        CPLW    Y
        POP     CC
        JRC     DN1
        INCW    Y
DN1:    LDW     (X),Y
        RET
        .endif

        ; .ifeq   BOOTSTRAP
;       =       ( w w -- t )    ( TOS STM8: -- Y,Z,N )
;       Return true if top two are equal.

        HEADER  EQUAL "="
EQUAL:
        .ifeq   SPEEDOVERSIZE
        CALL    XORR
        JP      ZEQUAL                 ; 31 cy= (18+13)
        .else
        LD      A,#0x0FF         ; true
        LDW     Y,X              ; D = n2
        LDW     Y,(Y)
        LDW     YTEMP,Y
        INCW    X
        INCW    X
        LDW     Y,X
        LDW     Y,(Y)
        CPW     Y,YTEMP ;if n2 <> n1
        JREQ    EQ1
        CLR     A
EQ1:    LD      (X),A
        LD      (1,X),A
        LDW     Y,X
        LDW     Y,(Y)
        RET                            ; 24 cy
       .endif
        ; .endif


;       U<      ( u u -- t )    ( TOS STM8: -- Y,Z,N )
;       Unsigned compare of top two items.

        HEADER  ULESS "U<"
ULESS:
        CLR     A
        CALLR   YTEMPCMP
        JRUGE   1$
        CPL     A
1$:     LD      YL,A
        LD      YH,A
        LDW     (X),Y
        RET

        .ifeq   BOOTSTRAP
;       <       ( n1 n2 -- t )
;       Signed compare of top two items.

        HEADER  LESS "<"
LESS:
        .ifeq   SPEEDOVERSIZE
        CALL    SUBB             ; (29cy)
        JP      ZLESS            ; 41 cy (12+29)
        .else
        CLR     A
        LDW     Y,X
        LDW     Y,(Y)
        LDW     YTEMP,Y
        INCW    X
        INCW    X
        LDW     Y,X
        LDW     Y,(Y)
        CPW     Y,YTEMP
        JRSGE   1$
        CPL     A
1$:     LD      (X),A
        LD      (1,X),A
        LDW     Y,X
        LDW     Y,(Y)
        RET                      ; 26 cy
        .endif
        .endif

;       YTEMPCMP       ( n n - n )      ( TOS STM8: - Y,Z,N )
;       Load (TOS) to YTEMP and (TOS-1) to Y, DROP, CMP to STM8 flags
YTEMPCMP:
        LDW     Y,X
        INCW    X
        INCW    X
        EXGW    X,Y
        LDW     X,(X)
        LDW     YTEMP,X
        LDW     X,Y
        LDW     X,(X)
        CPW     X,YTEMP
        EXGW    X,Y
        RET

        .ifeq   BOOTSTRAP
;       MAX     ( n n -- n )    ( TOS STM8: -- Y,Z,N )
;       Return greater of two top items.

        HEADER  MAX "MAX"
MAX:
        CALLR   YTEMPCMP
        JRSGT   MMEXIT
YTEMPTOS:
        LDW     Y,YTEMP
        LDW     (X),Y
MMEXIT:
        RET
        .endif

        .ifeq   BOOTSTRAP
;       MIN     ( n n -- n )    ( TOS STM8: -- Y,Z,N )
;       Return smaller of top two items.

        HEADER  MIN "MIN"
MIN:
        CALLR   YTEMPCMP
        JRSLT   MMEXIT
        JRA     YTEMPTOS
        .endif

        .ifeq   UNLINK_WITHI
;       WITHIN ( u ul uh -- t ) ( TOS STM8: -- Y,Z,N )
;       Return true if u is within
;       range of ul and uh. ( ul <= u < uh )

        HEADER  WITHI "WITHIN"
WITHI:
        CALL    OVER
        CALL    SUBB
        CALL    TOR
        CALL    SUBB
        CALL    RFROM
        JRA     ULESS
        .endif

; Divide

;       UM/MOD  ( udl udh un -- ur uq )
;       Unsigned divide of a double by a
;       single. Return mod and quotient.

        HEADER  UMMOD "UM/MOD"
UMMOD:
        LDW     Y,X             ; stack pointer to Y
        LDW     X,(X)           ; un
        LDW     YTEMP,X         ; save un
        LDW     X,Y
        INCW    X               ; drop un
        INCW    X
        PUSHW   X               ; save stack pointer
        LDW     X,(X)           ; X=udh
        LDW     Y,(4,Y)         ; Y=udl (offset before drop)
        CPW     X,YTEMP
        JRULT   MMSM1           ; X is still on the R-stack
        POPW    X               ; restore stack pointer
        LDW     Y,#0xFFFF       ; overflow result:
        LDW     (X),Y           ; quotient max. 16 bit value
        CLRW    Y
        LDW     (2,X),Y         ; remainder 0
        RET
MMSM1:
        LD      A,#16           ; loop count
        SLLW    Y               ; udl shift udl into udh
MMSM3:
        RLCW    X               ; rotate udl bit into uhdh (= remainder)
        JRC     MMSMa           ; if carry out of rotate
        CPW     X,YTEMP         ; compare udh to un
        JRULT   MMSM4           ; can't subtract
MMSMa:
        SUBW    X,YTEMP         ; can subtract
        RCF
MMSM4:
        CCF                     ; quotient bit
        RLCW    Y               ; rotate into quotient, rotate out udl
        DEC     A               ; repeat
        JRNE    MMSM3           ; if A == 0
MMSMb:
        LDW     YTEMP,X         ; done, save remainder
        POPW    X               ; restore stack pointer
        LDW     (X),Y           ; save quotient
        LDW     Y,YTEMP         ; remainder onto stack
        LDW     (2,X),Y
        RET

        .ifeq   UNLINKCORE
;       M/MOD   ( d n -- r q )
;       Signed floored divide of double by
;       single. Return mod and quotient.

        HEADER  MSMOD "M/MOD"
MSMOD:
        LD      A,(X)           ; DUPP ZLESS
        PUSH    A               ; DUPP TOR
        JRPL    MMOD1           ; QBRAN
        CALL    NEGAT
        CALL    TOR
        CALL    DNEGA
        CALL    RFROM
MMOD1:
        CALL    TOR
        JRPL    MMOD2           ; DUPP ZLESS QBRAN
        CALL    RAT
        CALL    PLUS
MMOD2:  CALL    RFROM
        CALLR   UMMOD
        POP     A               ; RFROM
        TNZ     A
        JRPL    MMOD3           ; QBRAN
        CALL    SWAPP
        CALL    NEGAT
        CALL    SWAPP
MMOD3:  RET

;       /MOD    ( n n -- r q )
;       Signed divide. Return mod and quotient.

        HEADER  SLMOD "/MOD"
SLMOD:
        CALL    OVER
        CALL    ZLESS
        CALL    SWAPP
        JRA     MSMOD

;       MOD     ( n n -- r )    ( TOS STM8: -- Y,Z,N )
;       Signed divide. Return mod only.

        HEADER  MMOD "MOD"
MMOD:
        CALLR   SLMOD
        JP      DROP

;       /       ( n n -- q )    ( TOS STM8: -- Y,Z,N )
;       Signed divide. Return quotient only.

        HEADER  SLASH "/"
SLASH:
        CALLR   SLMOD
        JP      NIP
        .endif

; Multiply

;       UM*     ( u u -- ud )
;       Unsigned multiply. Return double product.

        HEADER  UMSTA "UM*"
UMSTA:                          ; stack have 4 bytes u1=a,b u2=c,d
        LD      A,(2,X)         ; b
        LD      YL,A
        LD      A,(X)           ; d
        MUL     Y,A
        PUSHW   Y               ; PROD1 temp storage
        LD      A,(3,X)         ; a
        LD      YL,A
        LD      A,(X)           ; d
        MUL     Y,A
        PUSHW   Y               ; PROD2 temp storage
        LD      A,(2,X)         ; b
        LD      YL,A
        LD      A,(1,X)         ; c
        MUL     Y,A
        PUSHW   Y               ; PROD3,CARRY temp storage
        LD      A,(3,X)         ; a
        LD      YL,A
        LD      A,(1,X)         ; c
        MUL     Y,A             ; least signifiant product
        CLR     A
        RRWA    Y
        LD      (3,X),A         ; store least significant byte
        ADDW    Y,(1,SP)        ; PROD3
        CLR     A
        RLC     A               ; save carry
        LD      (1,SP),A        ; CARRY
        ADDW    Y,(3,SP)        ; PROD2
        LD      A,(1,SP)        ; CARRY
        ADC     A,#0            ; add 2nd carry
        LD      (1,SP),A        ; CARRY
        CLR     A
        RRWA    Y
        LD      (2,X),A         ; 2nd product byte
        ADDW    Y,(5,SP)        ; PROD1
        RRWA    Y
        LD      (1,X),A         ; 3rd product byte
        RRWA    Y               ; 4th product byte now in A
        ADC     A,(1,SP)        ; CARRY
        LD      (X),A
        ADDW    SP,#6           ; drop temp storage
        RET

;       *       ( n n -- n )    ( TOS STM8: -- Y,Z,N )
;       Signed multiply. Return single product.

        HEADER  STAR "*"
STAR:
        CALLR   UMSTA
        JP      DROP

        .ifeq   UNLINKCORE
;       M*      ( n n -- d )
;       Signed multiply. Return double product.
        HEADER  MSTAR "M*"
MSTAR:
        LD      A,(2,X)         ; DDUP
        XOR     A,(X)           ; XORR
        PUSH    A               ; TOR
        CALL    ABSS
        CALL    SWAPP
        CALL    ABSS
        CALLR   UMSTA
        POP     A               ; RFROM
        TNZ     A
        JRPL    MSTA1           ; QBRAN
        CALL    DNEGA
MSTA1:  RET

;       */MOD   ( n1 n2 n3 -- r q )
;       Multiply n1 and n2, then divide
;       by n3. Return mod and quotient.
        HEADER  SSMOD "*/MOD"
SSMOD:
        CALL    TOR
        CALLR   MSTAR
        CALL    RFROM
        JP      MSMOD

;       */      ( n1 n2 n3 -- q )    ( TOS STM8: -- Y,Z,N )
;       Multiply n1 by n2, then divide
;       by n3. Return quotient only.
        HEADER  STASL "*/"
STASL:
        CALLR   SSMOD
        JP      NIP
        .endif

; Miscellaneous


        .ifeq   BAREBONES
;       EXG      ( n -- n )      ( TOS STM8: -- Y,Z,N )
;       Exchange high with low byte of n.

        HEADER  EXG "EXG"
EXG:
        CALLR   DOXCODE
        SWAPW   X
        RET
        .endif

        .ifeq   BOOTSTRAP
;       2/      ( n -- n )      ( TOS STM8: -- Y,Z,N )
;       Divide tos by 2.

        HEADER  TWOSL "2/"
TWOSL:
        CALLR   DOXCODE
        SRAW    X
        RET

;       2*      ( n -- n )      ( TOS STM8: -- Y,Z,N )
;       Multiply tos by 2.

        HEADER  CELLS "2*"
CELLS:
        CALLR   DOXCODE
        SLAW    X
        RET
        .endif

;       2-      ( a -- a )      ( TOS STM8: -- Y,Z,N )
;       Subtract 2 from tos.

        HEADER  CELLM "2-"
CELLM:
        CALLR   DOXCODE
        DECW    X
        DECW    X
        RET

;       2+      ( a -- a )      ( TOS STM8: -- Y,Z,N )
;       Add 2 to tos.

        HEADER  CELLP "2+"
CELLP:
        CALLR   DOXCODE
        INCW    X
        INCW    X
        RET

;       1-      ( n -- n )      ( TOS STM8: -- Y,Z,N )
;       Subtract 1 from tos.

        HEADER  ONEM "1-"
ONEM:
        CALLR   DOXCODE
        DECW    X
        RET

;       1+      ( n -- n )      ( TOS STM8: -- Y,Z,N )
;       Add 1 to tos.

        HEADER  ONEP "1+"
ONEP:
        CALLR   DOXCODE
        INCW    X
        RET


;       DOXCODE   ( n -- n )   ( TOS STM8: - Y,Z,N )
;       precede assembly code for a primitive word
;       Caution: no other Forth word can be called from assembly!
;       In the assembly code: X=(TOS), YTEMP=TOS. (TOS)=X after RET

;       GENALIAS  DOXCODE "DOXCODE"
DOXCODE:
        POPW    Y
        LDW     YTEMP,X
        LDW     X,(X)
        CALL    (Y)
        EXGW    X,Y
        LDW     X,YTEMP
        LDW     (X),Y
        RET

;       NOT     ( w -- w )     ( TOS STM8: -- Y,Z,N )
;       One's complement of TOS.

        HEADER  INVER "NOT"
INVER:
        CALLR   DOXCODE
        CPLW    X
        RET

;       NEGATE  ( n -- -n )     ( TOS STM8: -- Y,Z,N )
;       Two's complement of TOS.

        HEADER  NEGAT "NEGATE"
NEGAT:
        CALLR   DOXCODE
        NEGW    X
        RET

;       ABS     ( n -- n )      ( TOS STM8: -- Y,Z,N )
;       Return  absolute value of n.

        HEADER  ABSS "ABS"
ABSS:
        CALLR   DOXCODE
        JRPL    1$              ; positive?
        NEGW    X               ; else negate
1$:     RET

;       0=      ( n -- t )      ( TOS STM8: -- Y,Z,N ))
;       Return true if n is equal to 0

        HEADER  ZEQUAL "0="
ZEQUAL:
        CALLR   DOXCODE
        JREQ    1$
        CLRW    X
        RET
1$:     CPLW    X               ; else -1
        RET

;       PICK    ( ... +n -- ... w )      ( TOS STM8: -- Y,Z,N )
;       Copy    nth stack item to tos.

        HEADER  PICK "PICK"
PICK:
        CALLR   DOXCODE
        INCW    X
        SLAW    X
        ADDW    X,YTEMP
        LDW     X,(X)
        RET

        .ifeq   BOOTSTRAP
;       >CHAR   ( c -- c )      ( TOS STM8: -- A,Z,N )
;       Filter non-printing characters.

        HEADER  TCHAR ">CHAR"
TCHAR:
        LD      A,(1,X)
        CP      A,#0x7F
        JRUGE   1$
        CP      A,#(' ')
        JRUGE   2$
1$:     LD      A,#('_')
2$:     LD      (1,X),A
        RET
        .endif

;       DEPTH   ( -- n )      ( TOS STM8: -- Y,Z,N )
;       Return  depth of data stack.

        HEADER  DEPTH "DEPTH"
DEPTH:
        LDW     Y,X
        NEGW    X
        ADDW    X,#SPP
        SRAW    X
        ;DECW    X               ; fixed: off-by-one to compensate error in "rp!"
        EXGW    X,Y
        JP      YSTOR

; Memory access

;       +!      ( n a -- )      ( TOS STM8: -- Y,Z,N )
;       Add n to contents at address a.

        HEADER  PSTOR "+!"
PSTOR:
        LDW     Y,X
        LDW     X,(X)
        LDW     YTEMP,X
        LDW     X,Y
        LDW     X,(2,X)
        PUSHW   X
        LDW     X,[YTEMP]
        ADDW    X,(1,SP)
        LDW     [YTEMP],X
        POPW    X
        EXGW    X,Y
        JP      DDROP

;       COUNT   ( b -- b +n )      ( TOS STM8: -- A,Z,N )
;       Return count byte of a string
;       and add 1 to byte address.

        HEADER  COUNT "COUNT"
COUNT:
        CALL    DUPP
        CALL    ONEP
        CALL    SWAPP
        JP      CAT

        .ifne  HAS_CPNVM
RAMHERE:
        TNZ     USRCP
        JRPL    HERE            ; NVM: CP points to NVM, NVMCP points to RAM
        LD      A,#(NVMCP)      ; 'eval in Interpreter mode: HERE returns pointer to RAM
        JP      AAT
        .else
        RAMHERE = HERE
        .endif

;       HERE    ( -- a )      ( TOS STM8: -- Y,Z,N )
;       Return  top of  code dictionary.

        HEADER  HERE "HERE"
HERE:
        CALL    CPP
        JP      AT

;       PAD     ( -- a )  ( TOS STM8: invalid )
;       Return address of text buffer
;       above code dictionary.

        HEADER  PAD "PAD"
PAD:
        .ifne   HAS_BACKGROUND
        ; get PAD area address (offset or dedicated) for PAD area
        PUSH    CC              ; Test interrupt level flags in CC
        POP     A
        AND     A,#0x20
        JRNE    1$
        DoLitC  (PADBG+1)       ; dedicated memory for PAD in background task
        RET
1$:
        .endif
        CALLR   RAMHERE         ; regular PAD with offset to HERE
        DoLitC  PADOFFS
        JP      PLUS

        .ifeq   UNLINK_ATEXE
;       @EXECUTE        ( a -- )  ( TOS STM8: undefined )
;       Execute vector stored in address a.

        HEADER  ATEXE "@EXECUTE"
ATEXE:
        CALL    YFLAGS
        LDW     Y,(Y)
        JREQ    1$
        JP      (Y)
1$:     RET
        .endif

;       CMOVE   ( b1 b2 u -- )
;       Copy u bytes from b1 to b2.

        HEADER  CMOVE "CMOVE"
CMOVE:
        CALL    TOR
        JRA     CMOV2
CMOV1:  CALL    TOR
        CALL    DUPPCAT
        CALL    RAT
        CALL    CSTOR
        CALL    ONEP
        CALL    RFROM
        CALL    ONEP
CMOV2:  CALL    DONXT
        .dw     CMOV1
        JP      DDROP

;       FILL    ( b u c -- )
;       Fill u bytes of character c
;       to area beginning at b.

        HEADER  FILL "FILL"
FILL:
        CALL    SWAPP
        CALL    TOR
        CALL    SWAPP
        JRA     FILL2
FILL1:  CALL    DDUP
        CALL    CSTOR
        CALL    ONEP
FILL2:  CALL    DONXT
        .dw     FILL1
        JP      DDROP

        .ifeq   BAREBONES
;       ERASE   ( b u -- )
;       Erase u bytes beginning at b.

        HEADER  ERASE "ERASE"
ERASE:
        CALL    ZERO
        JRA     FILL
        .endif

;       PACK$   ( b u a -- a )
;       Build a counted string with
;       u characters from b. Null fill.

        HEADER  PACKS "PACK$"
PACKS:
        CALL    DUPP
        CALL    TOR             ; strings only on cell boundary
        CALL    DDUP
        CALL    CSTOR
        CALL    ONEP            ; save count
        CALL    SWAPP
        CALLR   CMOVE
        CALL    RFROM
        RET

; Numeric output, single precision

;       DIGIT   ( u -- c )      ( TOS STM8: -- Y,Z,N )
;       Convert digit u to a character.

        HEADER  DIGIT "DIGIT"
DIGIT:
        LD      A,(1,X)
        CP      A,#10
        JRMI    1$
        ADD     A,#7
1$:     ADD     A,#48
        LD      (1,X),A
        RET

;       EXTRACT ( n base -- n c )   ( TOS STM8: -- Y,Z,N )
;       Extract least significant digit from n.

        HEADER  EXTRC "EXTRACT"
EXTRC:
        CALL    ZERO
        CALL    SWAPP
        CALL    UMMOD
        CALL    SWAPP
        JRA     DIGIT

;       #>      ( w -- b u )
;       Prepare output string.

        HEADER  EDIGS "#>"
EDIGS:
        LDW     Y,USRHLD        ; DROP HLD
        LDW     (X),Y
        CALL    PAD
        CALL    OVER
        JP      SUBB

;       #       ( u -- u )    ( TOS STM8: -- Y,Z,N )
;       Extract one digit from u and
;       append digit to output string.

        HEADER  DIG "#"
DIG:
        CALLR   BASEAT
        CALLR   EXTRC
        JRA     HOLD

;       #S      ( u -- 0 )
;       Convert u until all digits
;       are added to output string.

        HEADER  DIGS "#S"
DIGS:
DIGS1:  CALLR   DIG
        JRNE    DIGS1
        RET

;       HOLD    ( c -- )    ( TOS STM8: -- Y,Z,N )
;       Insert a character into output string.

        HEADER  HOLD "HOLD"
HOLD:
        LD      A,(1,X)         ; A < c
        EXGW    X,Y
        LDW     X,USRHLD        ; HLD @
        DECW    X               ; 1 -
        LDW     USRHLD,X        ; DUP HLD !
        LD      (X),A           ; C!
        EXGW    X,Y
H_DROP:
        JP      DROP

;       SIGN    ( n -- )
;       Add a minus sign to
;       numeric output string.

        HEADER  SIGN "SIGN"
SIGN:
        TNZ     (X)
        JRPL    H_DROP
        LD      A,#('-')
        LD      (1,X),A
        JRA     HOLD

;       <#      ( -- )   ( TOS STM8: -- Y,Z,N )
;       Initiate numeric output process.

        HEADER  BDIGS "<#"
BDIGS:
        CALL    PAD
        DoLitC  USRHLD
        JP      STORE

;       str     ( w -- b u )
;       Convert a signed integer
;       to a numeric string.

        HEADER  STR "str"
STR:
        CALL    DUPP
        CALL    TOR
        CALL    ABSS
        CALLR   BDIGS
        CALLR   DIGS
        CALL    RFROM
        CALLR   SIGN
        JRA     EDIGS

;       HEX     ( -- )
;       Use radix 16 as base for
;       numeric conversions.

        HEADER  HEX "HEX"
HEX:
        LD      A,#16
        JRA     BASESET

;       DECIMAL ( -- )
;       Use radix 10 as base
;       for numeric conversions.

        HEADER  DECIM "DECIMAL"
DECIM:
        LD      A,#10
BASESET:
        LD      USRBASE+1,A
        CLR     USRBASE
        RET

;       BASE@     ( -- u )
;       Get BASE value
BASEAT:
        LD      A,USRBASE+1
        JP      ASTOR

; Numeric input, single precision

;       NUMBER? ( a -- n T | a F )
;       Convert a number string to
;       integer. Push a flag on tos.

        HEADER  NUMBQ "NUMBER?"
NUMBQ:
        LDW      Y,USRBASE
        PUSHW    Y              ; note: (1,SP) used as sign flag

        CALL    ZERO
        CALL    OVER
        CALL    COUNT
NUMQ0:
        CALL    OVER
        CALL    CAT
        CALL    AFLAGS

        CP      A,#('$')
        JRNE    1$
        CALLR   HEX
        JRA     NUMQSKIP
1$:
        .ifne   EXTNUMPREFIX
        CP      A,#('%')
        JRNE    2$
        MOV     USRBASE+1,#2
        JRA     NUMQSKIP
2$:
        CP      A,#('&')
        JRNE    3$
        CALLR   DECIM
        JRA     NUMQSKIP
3$:
        .endif
        CP      A,#('-')
        JRNE    NUMQ1
        POP     A
        PUSH    #0x80           ; flag ?sign

NUMQSKIP:
        CALL    SWAPP
        CALL    ONEP
        CALL    SWAPP
        CALL    ONEM
        JRNE    NUMQ0           ; check for more modifiers

NUMQ1:
        CALL    QDQBRAN
        .dw     NUMQ6
        CALL    ONEM
        CALL    TOR             ; FOR
NUMQ2:  CALL    DUPP
        CALL    TOR
        CALL    CAT
        CALLR   BASEAT
        CALLR   DIGTQ
        CALL    QBRAN           ; WHILE ( no digit -> LEAVE )
        .dw     NUMLEAVE

        CALL    SWAPP
        CALLR   BASEAT
        CALL    STAR
        CALL    PLUS

        CALL    RFROM
        CALL    ONEP

        CALL    DONXT           ; NEXT
        .dw     NUMQ2

        CALLR   NUMDROP         ; drop b

        LD      A,(1,SP)        ; test sign flag
        JRPL    NUMPLUS
        CALL    NEGAT
NUMPLUS:
        CALL    SWAPP
        JRA     NUMQ5
NUMLEAVE:                       ; LEAVE ( clean-up FOR .. NEXT )
        ADDW    SP,#4           ; RFROM,RFROM,DDROP
        CALLR   NUMDROP         ; DDROP 0
        CLR     (X)
        CLR     (1,X)
        ; fall through
NUMQ5:                          ; THEN
        CALL    DUPP
        ; fall through
NUMQ6:
        POP     A               ; discard sign flag
        POP     A               ; restore BASE
        LD      USRBASE+1,A
NUMDROP:
        JP      DROP

;       DIGIT?  ( c base -- u t )
;       Convert a character to its numeric
;       value. A flag indicates success.

        HEADER  DIGTQ "DIGIT?"
DIGTQ:
        CALL    TOR
        LD      A,YL
        SUB     A,#'0'
        CP      A,#10
        JRMI    DGTQ1
        SUB     A,#7
        .ifne   CASEINSENSITIVE
        AND     A,#0xDF
        .endif
        CP      A,#10
        JRPL    DGTQ1
        CPL     A               ; make sure A > base
DGTQ1:  LD      (1,X),A
        CALL    DUPP
        CALL    RFROM
        JP      ULESS


; Basic I/O

;       KEY     ( -- c )
;       Wait for and return an
;       input character.

        HEADER  KEY "KEY"
KEY:
KEY1:   CALL    [USRQKEY]
        CALL    YFLAGS
        JRNE    RETIDLE
        LD      A,USRIDLE
        OR      A,USRIDLE+1
        JREQ    KEY2
        CALL    [USRIDLE]       ; IDLE must be fast (unless ?RX is buffered) and stack neutral
KEY2:
        JRA     KEY1
RETIDLE:
        RET

        .ifeq   REMOVE_NUFQ
;       NUF?    ( -- t )
;       Return false if no input,
;       else pause and if CR return true.

        HEADER  NUFQ "NUF?"
NUFQ:
        .ifne   CONSOLE_HALF_DUPLEX
        ; slow EMIT down to free the line for RX
        .ifne   HAS_BACKGROUND
        LD      A,TICKCNT+1
        ADD     A,#3
1$:     CP      A,TICKCNT+1
        JRNE    1$
        .else
        CLRW    Y
1$:     DECW    Y
        JRNE    1$
        .endif
        .endif
        CALL    [USRQKEY]
        LD      A,(1,X)
        JREQ    NUFQ1
        CALL    DDROP
        CALLR   KEY
        DoLitC  CRR
        JP      EQUAL
NUFQ1:  RET
        .endif

;       SPACE   ( -- )
;       Send    blank character to
;       output device.

        HEADER  SPACE "SPACE"
SPACE:

        CALL    BLANK
        JP      [USREMIT]

        .ifeq   UNLINKCORE
;       SPACES  ( +n -- )
;       Send n spaces to output device.

        .ifeq   BAREBONES
        HEADER  SPACS "SPACES"
SPACS:
        CALL    ZERO
        CALL    MAX
        .else
SPACS:
        .endif
        CALL    TOR
        JRA     CHAR2
CHAR1:  CALLR   SPACE
CHAR2:  CALL    DONXT
        .dw     CHAR1
        RET
        .endif

;       do$     ( -- a )
;       Return  address of a compiled string.

        HEADFLG DOSTR "do$" COMPO
DOSTR:
        CALL    RFROM
        CALL    RAT
        CALL    RFROM
        CALL    COUNT
        CALL    PLUS
        CALL    TOR
        CALL    SWAPP
        CALL    TOR
        RET

;       $"|     ( -- a )
;       Run time routine compiled by $".
;       Return address of a compiled string.

        HEADFLG STRQP '$"|' COMPO

STRQP:
        CALLR   DOSTR
        RET

;       ."|     ( -- )
;       Run time routine of ." .
;       Output a compiled string.

        HEADFLG DOTQP '."|' COMPO
DOTQP:
        CALLR   DOSTR
COUNTTYPES:
        CALL    COUNT
        JRA     TYPES

        .ifeq   BAREBONES
;       .R      ( n +n -- )
;       Display an integer in a field
;       of n columns, right justified.

        HEADER  DOTR ".R"
DOTR:
        CALL    TOR
        CALL    STR
        JRA     RFROMTYPES
        .endif

;       U.R     ( u +n -- )
;       Display an unsigned integer
;       in n column, right justified.

        HEADER  UDOTR "U.R"
UDOTR:
        CALL    TOR
        CALLR   BDEDIGS
RFROMTYPES:
        CALL    RFROM
        CALL    OVER
        CALL    SUBB
        CALLR   SPACS
        JRA     TYPES

;       TYPE    ( b u -- )
;       Output u characters from b.

        HEADER  TYPES "TYPE"
TYPES:
        CALL    TOR
        JRA     TYPE2
TYPE1:  CALL    DUPPCAT
        CALL    [USREMIT]
        CALL    ONEP
TYPE2:
        CALL    DONXT
        .dw     TYPE1
        JP      DROP

        .ifeq   BOOTSTRAP
;       U.      ( u -- )
;       Display an unsigned integer
;       in free format.

        HEADER  UDOT "U."
UDOT:
        CALLR   BDEDIGS
        CALL    SPACE
        JRA     TYPES

;       UDOT helper routine
BDEDIGS:
        CALL    BDIGS
        CALL    DIGS
        JP      EDIGS
        .endif

        .ifeq   BOOTSTRAP
;       .       ( w -- )
;       Display an integer in free
;       format, preceeded by a space.

        HEADER  DOT "."
DOT:
        LD      A,USRBASE+1
        XOR     A,#10
        JREQ    1$
        JRA     UDOT
1$:     CALL    STR
        CALL    SPACE
        JRA     TYPES
        .endif

        .ifeq   BOOTSTRAP
;       ?       ( a -- )
;       Display contents in memory cell.

        HEADER  QUEST "?"
QUEST:
        CALL    AT
        JRA     DOT
        .endif


; Parsing

;       >Y  ( n -- )       ( TOS STM8: - Y,Z,N )
;       Consume TOS to CPU Y and Flags

;       GENALIAS  YFLAGS ">Y"
YFLAGS:
        LDW     Y,X
        INCW    X
        INCW    X
        LDW     Y,(Y)
        RET


;       >A   ( c -- )       ( TOS STM8: - A,Z,N )
;       Consume TOS to CPU A and Flags

;       GENALIAS  AFLAGS ">A"
AFLAGS:
        INCW    X
        LD      A,(X)
        INCW    X
        TNZ     A
        RET

;       SPARSE   ( b u c -- b u delta ; <string> )
;       Scan string delimited by c.
;       Return found string and its offset.

        HEADER  PARS "SPARSE"
PARS:
        CALLR   AFLAGS          ; TEMP CSTOR
        PUSH    A
        CALL    OVER
        CALL    TOR
        JRNE    1$
        CALL    OVER
        CALL    RFROM
        JRA     PARSEND
1$:     CALL    ONEM
        ld      A,(3,SP)        ; TEMP CAT
        CP      A,#' '          ; BLANK EQUAL
        JRNE    PARS3
        CALL    TOR
PARS1:
        LD      A,#' '
        LDW     Y,X
        LDW     Y,(Y)
        CP      A,(Y)
        JRMI    PARS2
        CALL    ONEP
        CALL    DONXT
        .dw     PARS1
        ADDW    SP,#2           ; RFROM DROP
        CALL    ZERO
        POP     A               ; discard TEMP
DUPPARS:
        JP      DUPP
PARS2:  CALL    RFROM
PARS3:  CALL    OVER
        CALL    SWAPP
        CALL    TOR
PARS4:
        LD      A,(5,SP)        ; TEMP CAT
        CALL    ASTOR
        CALL    OVER
        CALL    CAT
        CALLR   SUBPARS         ; scan for delimiter
        LD      A,(5,SP)        ; TEMP CAT
        CP      A,#' '          ; BLANK EQUAL
        JRNE    PARS5
        CALL    ZLESS
PARS5:  CALL    QBRAN
        .dw     PARS6
        CALL    ONEP
        CALL    DONXT
        .dw     PARS4
        CALLR   DUPPARS
        CALL    TOR
        JRA     PARS7
PARS6:  ADDW    SP,#2           ; RFROM DROP
        CALLR   DUPPARS
        CALL    ONEP
        CALL    TOR
PARS7:  CALL    OVER
        CALLR   SUBPARS
        CALL    RFROM
        CALL    RFROM
PARSEND:
        POP     A               ; discard TEMP
SUBPARS:
        JP      SUBB

;       PARSE   ( c -- b u ; <string> )
;       Scan input stream and return
;       counted string delimited by c.

        HEADER  PARSE "PARSE"
PARSE:
        LD      A,#(USRBUFFER)
        CALL    AAT
        ADDW    Y,USR_IN        ; current input buffer pointer
        LDW     (X),Y
        LD      A,USRNTIB+1
        SUB     A,USR_IN+1      ; remaining count
        CALL    ASTOR
        CALL    ROT
        CALL    PARS
        DoLitC  USR_IN
        JP      PSTOR

        .ifeq   BAREBONES
;       .(      ( -- )
;       Output following string up to next ) .

        HEADFLG DOTPR ".(" IMEDD
DOTPR:
        DoLitC  41      ; ")"
        CALLR   PARSE
        JP      TYPES
        .endif

        .ifeq   BOOTSTRAP
;       (       ( -- )
;       Ignore following string up to next ).
;       A comment.

        HEADFLG PAREN "(" IMEDD
PAREN:
        DoLitC  41      ; ")"
        CALLR   PARSE
        JP      DDROP
        .endif

;       \       ( -- )
;       Ignore following text till
;       end of line.

        HEADFLG BKSLA "\" IMEDD
BKSLA:
        MOV       USR_IN+1,USRNTIB+1
        RET

;       TOKEN   ( -- a ; <string> )
;       Parse a word from input stream
;       and copy it to code dictionary or to RAM.

        HEADER  TOKEN "TOKEN"

TOKEN:
        CALL    BLANK
        JRA     WORDD

;       WORD    ( c -- a ; <string> )
;       Parse a word from input stream
;       and copy it to code dictionary or to RAM.

        HEADER  WORDD "WORD"
WORDD:
        CALLR   PARSE
        CALL    RAMHERE
CPPACKS:
        CALL    CELLP
        JP      PACKS

;       TOKEN_$,n  ( <word> -- <dict header> )
;       copy token to the code dictionary
;       and build a new dictionary name
;       note: for defining words (e.g. :, CREATE)

;       GENALIAS  TOKSNAME "TOKEN_$,n"
TOKSNAME:
        CALL    BLANK
        CALLR   PARSE
        CALL    HERE
        CALLR   CPPACKS
        JP      SNAME

; Dictionary search
;       NAME>   ( na -- ca )
;       Return a code address given
;       a name address.

        HEADER  NAMET "NAME>"
NAMET:
        CALL    COUNT
        DoLitC  31
        CALL    ANDD
        .ifeq   HAS_ALIAS
        JP      PLUS
        .else
        CALL    PLUS            ; ALIAS: return the target address of a JP
        LD      A,(Y)           ; DUP C@
        CP      A,#BRAN_OPC     ; BRAN_OPC =
        JRNE    1$              ; IF
        INCW    Y               ; 1+
        LDW     Y,(Y)           ; @
        LDW     (X),Y
1$:     RET                     ; THEN
        .endif

;       R@ indexed char lookup for SAME?
SAMEQCAT:
        CALL    OVER
        ADDW    Y,(3,SP)        ; R-OVER> PLUS
        .ifne   CASEINSENSITIVE
        CALL    YCAT
        JRA   CUPPER
        .else
        JP      YCAT
        .endif

;       SAME?   ( a a u -- a a f \ -0+ )
;       Compare u cells in two
;       strings. Return 0 if identical.

        HEADER  SAMEQ "SAME?"
SAMEQ:
        CALL    ONEM
        CALL    TOR
        JRA     SAME2
SAME1:
        CALLR   SAMEQCAT
        CALLR   SAMEQCAT
        CALL    XORR
        CALL    QDQBRAN
        .dw     SAME2
        POPW    Y               ; RFROM DROP
        RET
SAME2:  CALL    DONXT
        .dw     SAME1
        JP      ZERO

        .ifne   CASEINSENSITIVE
;       CUPPER  ( c -- c )
;       convert char to upper case

        HEADER  CUPPER "CUPPER"
CUPPER:
        LD      A,(1,X)
        CP      A,#('a')
        JRULT   1$
        CP      A,#('z')
        JRUGT   1$
        AND     A,#0xDF
        LD      (1,X),A
1$:     RET
        .endif

;       NAME?   ( a -- ca na | a F )
;       Search vocabularies for a string.

        HEADER  NAMEQ "NAME?"
NAMEQ:
        .ifne   HAS_ALIAS
        CALL    CNTXT_ALIAS     ; "PC_NAME?" patch point for CURRENT
        .else
        CALL    CNTXT
        .endif

        JRA     FIND

;       find    ( a va -- ca na | a F )
;       Search vocabulary for string.
;       Return ca and na if succeeded.

        HEADER  FIND "find"
FIND:
        CALLR   SWAPPF          ; SWAPP
        LDW     Y,(Y)           ; DUPP CAT TEMP CSTOR DUPP AT
        LD      A,YH
        PUSH    A               ; (push TEMP)
        PUSHW   Y               ; TOR
        CALL    CELLP
        CALLR   SWAPPF
FIND1:  CALL    AT
        JREQ    FIND6
        CALL    YAT             ; DUPP AT
        DoLitW  MASKK
        CALL    ANDD
        .ifne   CASEINSENSITIVE
        CALLR   CUPPER
        .endif
        CALL    RAT
        .ifne   CASEINSENSITIVE
        CALLR   CUPPER
        .endif
        CALL    XORR
        CALL    QBRAN
        .dw     FIND2
        CALL    CELLP
        CALL    MONE            ; 0xFFFF
        JRA     FIND3
FIND2:  CALL    CELLP
        LD      A,(3,SP)        ; TEMP CAT
        CALL    ASTOR
        CALL    SAMEQ
FIND3:  JRA     FIND4
FIND6:  ADDW    SP,#3           ; (pop TEMP) RFROM DROP
        CALLR   SWAPPF
        CALL    CELLM
        JRA     SWAPPF
FIND4:  CALL    QBRAN
        .dw     FIND5
        CALL    CELLM
        CALL    CELLM
        JRA     FIND1
FIND5:  ADDW    SP,#3           ; (pop TEMP) RFROM DROP
        CALL    NIP
        CALL    CELLM
        CALL    DUPP
        CALL    NAMET
SWAPPF:
        JP      SWAPP

; Terminal response

;       ^H      ( bot eot cur -- bot eot cur )
;       Backup cursor by one character.

        HEADER  BKSP "^h"
BKSP:
        LD      A,(4,X)         ; backspace if CUR != BOT
        CP      A,(X)
        JRNE    BACK0
        LD      A,(5,X)
        CP      A,(1,X)
        JREQ    BACK1
BACK0:
        .ifeq   CONSOLE_HALF_DUPLEX
        CALLR   BACKSP
        .endif
        CALL    ONEM
        CALL    SPACE
BACKSP:
        DoLitC  BKSPP
        JP      [USREMIT]
BACK1:  RET

;       TAP     ( bot eot cur c -- bot eot cur )
;       Accept and echo key stroke
;       and bump cursor.

        HEADER  TAP "TAP"
TAP:
        .ifeq   CONSOLE_HALF_DUPLEX
        CALL    DUPP
        CALL    [USREMIT]
        .endif
        CALL    OVER
        CALL    CSTOR
        JP      ONEP

;       kTAP    ( bot eot cur c -- bot eot cur )
;       Process a key stroke,
;       CR or backspace.

        HEADER  KTAP "kTAP"
KTAP:
        LD      A,(1,X)
        CP      A,#CRR
        JREQ    KTAP2

        DoLitC  BKSPP
        CALL    XORR
        CALL    QBRAN
        .dw     KTAP1

        CALL    BLANK
        JRA     TAP
KTAP1:  JRA     BKSP
KTAP2:  CALL    DROP
        CALL    NIP
        JP      DUPP

;       ACCEPT  ( b u -- b u )
;       Accept one line of characters to input
;       buffer. Return with actual count.

        HEADER  ACCEP "ACCEPT"
ACCEP:
        CALL    OVER
        CALL    PLUS
        CALL    OVER
ACCP1:  CALL    DDUP
        CALL    XORR
        CALL    QBRAN
        .dw     ACCP4
        CALL    KEY
        LD      A,(1,X)         ; DUPP
        JRMI    ACCP2           ; BL 127 WITHIN
        CP      A,#32
        JRMI    ACCP2           ; ?branch ACC2
        CALLR   TAP
        JRA     ACCP3
ACCP2:  CALLR   KTAP
ACCP3:  JRA     ACCP1
ACCP4:  CALL    DROP
        CALL    OVER
        JP      SUBB

;       QUERY   ( -- )
;       Accept one line from input stream to
;       terminal input buffer.

        HEADER  QUERY "QUERY"
QUERY:
        LD      A,#(USRBUFFER)
        CALL    AAT
        DoLitC  TIBLENGTH
        CALLR   ACCEP
        CALL    AFLAGS          ; NTIB !
        LD      USRNTIB+1,A
        CLR     USR_IN
        CLR     USR_IN+1
        JP      DROP

;       ABORT   ( -- )
;       Reset data stack and
;       jump to QUIT.

        HEADER  ABORT "ABORT"
ABORT:
        CALLR   PRESE
        JP      QUIT

;       aborq  ( f -- )
;       Run time routine of ABORT".
;       Abort with a message.

        HEADFLG ABORQ "aborq" COMPO
ABORQ:
        CALL    QBRAN
        .dw     ABOR2           ; text flag
        CALL    DOSTR
ABOR1:  CALL    SPACE
        CALL    COUNTTYPES
        CALL    DOTQP
        .ifne   HAS_OLDOK
        .db     2, 63,  10       ; ?<CR>
        .else
        .db     3, 63,  7, 10   ; ?<BEL><CR>
        .endif
        JRA     ABORT           ; pass error string
ABOR2:  CALL    DOSTR
        JP      DROP

;       PRESET  ( -- )
;       Reset data stack pointer and
;       terminal input buffer.

        HEADER  PRESE "PRESET"
PRESE:
        CLRW    X
        LDW     USRNTIB,X
        LDW     X,#TIBB         ; "TIB" addr. const. Terminal Input Buffer
        LDW     USRBUFFER,X
        LDW     X,#SPP          ; "SPP" addr. const. top of data stack
        RET

; The text interpreter

;       $INTERPRET      ( a -- )
;       Interpret a word. If failed,
;       try to convert it to an integer.

        HEADER  INTER "$INTERPRET"
INTER:
        CALL    NAMEQ
        CALL    QDQBRAN         ; ?defined
        .dw     INTE1
        CALL    CAT             ; get byte at name address na
        AND     A,#COMPO        ; compile only lexicon bits
        LD      (1,X),A
        CALLR   ABORQ
        .db     13
        .ascii  " compile only"
        JP      EXECU
INTE1:  CALL    NUMBQ           ; convert a number
        CALL    QBRAN
        .dw     ABOR1
        RET

;       [       ( -- )
;       Start   text interpreter.
        HEADFLG LBRAC "[" IMEDD
LBRAC:
        LDW     Y,#INTER
        LDW     USREVAL,Y
        RET

;       CR      ( -- )
;       Output a carriage return
;       and a line feed.

        HEADER  CR "CR"
CR:
        .ifeq TERM_LINUX
        DoLitC  CRR
        CALL    [USREMIT]
        .endif
        DoLitC  LF
        JP      [USREMIT]

;       COMPILE?   ( -- n )
;       0 if 'EVAL points to $INTERPRETER
;       GENALIAS  COMPIQ "COMPILE?"
COMPIQ:
        LDW     Y,USREVAL
        SUBW    Y,#INTER
        RET

;       .OK     ( -- )
;       Display 'ok' while interpreting.

        HEADER  DOTOK ".OK"
DOTOK:
        CALLR   COMPIQ
        JREQ    DOTO1
        .ifne   HAS_OLDOK
        JRA     CR
        .else
        CALL    DOTQP            ; e4thcom handshake (which also works with ' ok')
        .db     4
        .ascii  " OK"
        .db     LF
        RET
        .endif

        .ifeq   BAREBONES
;       hi      ( -- )
;       Display sign-on message.

        HEADER  HI "hi"
HI:
        CALL    DOTQP           ; initialize I/O
        .db     18, 10
        .ifne   PRE_REL
        .ascii  "STM8EF2.2."
        .db     (RELVER1+'0')
        .db     (RELVER0+'0')   ; version
        .ascii  ".pre"
        .db     (PRE_REL+'0')
        .else
        .ascii  "STM8eForth 2.2."
        .db     (RELVER1+'0')
        .db     (RELVER0+'0')   ; version
        .endif

         ; fall through
        .else
HI:
        .endif
DOTO1:
        CALL    DOTQP
        .db     4
        .ascii  " ok"
        .db     10
        RET


;       ?STACK  ( -- )
;       Abort if stack underflows.

        HEADER  QSTAC "?STACK"
QSTAC:
        CALL    DEPTH
        CALL    ZLESS           ; check only for underflow
        CALL    ABORQ
        .db     10
        .ascii  " underflow"
        RET

;       QUIT    ( -- )
;       Reset return stack pointer
;       and start text interpreter.

        HEADER  QUIT "QUIT"
QUIT:
        LDW     Y,#RPP          ; initialize return stack
        LDW     SP,Y
        ; fall through

;       OUTER  ( -- n )     ( TOS STM8: - Y,Z,N )
;       Outer interpreter (use EXIT with 2x R-address drop)

;       GENALIAS  OUTER "OUTER"
OUTER:
        CALLR   LBRAC           ; start interpretation
QUIT2:  CALL    QUERY           ; get input
        CALLR   EVAL
        JRA     QUIT2           ; continue till error

;       EVAL    ( -- )
;       Interpret input stream.

        HEADER  EVAL "EVAL"
EVAL:
EVAL1:  CALL    TOKEN
        LD      A,(Y)
        JREQ    EVAL2
        CALL    [USREVAL]
        CALLR   QSTAC           ; evaluate input, check stack
        JRA     EVAL1
EVAL2:
        INCW    X
        INCW    X
        JP      [USRPROMPT]     ; DOTOK or PACE

; The compiler

;       '       ( -- ca )
;       Search vocabularies for
;       next word in input stream.

        HEADER  TICK "'"
TICK:
        CALL    TOKEN
        CALL    NAMEQ           ; ?defined
        CALL    QBRAN
        .dw     ABOR1
        RET                     ; yes, push code address

        .ifeq BOOTSTRAP
;       [COMPILE]       ( -- ; <string> )
;       Compile next immediate
;       word into code dictionary.

        HEADFLG BCOMP "[COMPILE]" IMEDD
BCOMP:
        CALLR   TICK
        JRA     JSRC
        .endif

;       ,       ( w -- )
;       Compile an integer into
;       code dictionary.

        HEADER  COMMA ^/","/
COMMA:
        DoLitC  2
        CALLR   OMMA
        JP      STORE

;       C,      ( c -- )
;       Compile a byte into code dictionary.

        HEADER  CCOMMA ^/"C,"/
CCOMMA:
        CALL    ONE
        CALLR   OMMA
        JP      CSTOR

;       common part of COMMA and CCOMMA
OMMA:
        CALL    HERE
        CALL    SWAPP
        CALL    CPP
        JP      PSTOR

;       CALL,   ( ca -- )
;       Compile a subroutine call.

        HEADER  JSRC ^/"CALL,"/
JSRC:
        CALL    DUPP
        CALL    HERE
        CALL    CELLP
        CALL    SUBB            ; Y now contains the relative call address
        LD      A,YH
        INC     A
        JRNE    1$              ; YH must be 0xFF
        LD      A,YL
        TNZ     A
        JRPL    1$              ; YL must be negative
        LD      A,#CALLR_OPC
        LD      YH,A            ; replace YH with opcode CALLR
        LDW     (2,X),Y
        JRA     2$
1$:
        CALL    CCOMMALIT
        .db     CALL_OPC         ; opcode CALL
2$:
        CALL    DROP             ; drop relative address
        .ifne   HAS_CPNVM
        JRMI    3$               ; DROP leaves CALL, data in Y
        TNZ     USRCP
        JRPL    3$               ; call to RAM from RAM
        CALL    ABORQ            ; error: call to RAM from NVM
        .db     7
        .ascii  " target"
3$:
        .endif
        JRA     COMMA            ; store absolute address or "CALLR reladdr"

;       LITERAL ( w -- )
;       Compile tos to dictionary
;       as an integer literal.

        HEADFLG LITER "LITERAL" IMEDD
LITER:
        .ifne  USE_CALLDOLIT
        CALLR   COMPI
        CALL    DOLIT
        .else
        CALL    CCOMMALIT
        .db     DOLIT_OPC
        .endif
        JRA      COMMA

;       COMPILE ( -- )
;       Compile next jsr in
;       colon list to code dictionary.

        HEADFLG COMPI "COMPILE" COMPO
COMPI:
        EXGW    X,Y
        POPW    X
        LD      A,(X)
        INCW    X
        CP      A,#CALL_OPC
        JRNE    COMPIO1
        LDW     YTEMP,X         ; COMPILE CALL address
        INCW    X
        INCW    X
        PUSHW   X
        LDW     X,[YTEMP]
        JRA     COMPIO2
COMPIO1:
        LD      A,(X)           ; COMPILE CALLR offset
        INCW    X
        PUSHW   X               ; return address
        CLRW    X               ; offset i8_t to i16_t
        TNZ     A
        JRPL    1$
        DECW    X
1$:     LD      XL,A
        ADDW    X,(1,SP)        ; add offset in X to address of next instruction
COMPIO2:
        EXGW    X,Y
        CALL    YSTOR
        JRA     JSRC            ; compile subroutine


;       $,"     ( -- )
;       Compile a literal string
;       up to next " .

        HEADER  STRCQ ^/'$,"'/
STRCQ:
        DoLitC  34              ; "
        CALL    PARSE
        CALL    HERE
        CALL    PACKS           ; string to code dictionary
CNTPCPPSTORE:
        CALL    COUNT
        CALL    PLUS            ; calculate aligned end of string
        CALL    CPP
        JP      STORE

; Structures

        .ifeq   BOOTSTRAP
;       FOR     ( -- a )
;       Start a FOR-NEXT loop
;       structure in a colon definition.

        HEADFLG FOR "FOR" IMEDD
FOR:
        CALLR   COMPI
        CALL    TOR
        JP      HERE

;       NEXT    ( a -- )
;       Terminate a FOR-NEXT loop.

        HEADFLG NEXT "NEXT" IMEDD
NEXT:
        CALLR   COMPI
        CALL    DONXT
        JP      COMMA
        .endif

        .ifne   HAS_DOLOOP
;       DO      ( n1 n2 -- )
;       Start a DO LOOP loop from n1 to n2
;       structure in a colon definition.

        HEADFLG DOO "DO" IMEDD
DOO:
        CALL    CCOMMALIT
        .db     DOLIT_OPC       ; LOOP address cell for usage by LEAVE at runtime
        CALL    ZEROCOMMA       ; changes here require an offset adjustment in PLOOP
        CALLR   COMPI
        CALL    TOR
        CALLR   COMPI
        CALL    SWAPP
        CALLR   COMPI
        CALL    TOR
        JRA     FOR

;       LOOP    ( a -- )
;       Terminate a DO-LOOP loop.

        HEADFLG LOOP "LOOP" IMEDD
LOOP:
        CALL    COMPI
        CALL    ONE
        JRA     PLOOP

;       +LOOP   ( a +n -- )
;       Terminate a DO - +LOOP loop.

        HEADFLG PLOOP "+LOOP" IMEDD
PLOOP:
        CALL    COMPI
        CALL    DOPLOOP
        CALL    HERE
        CALL    OVER            ; use mark from DO/FOR, apply negative offset
        DoLitC  14
        CALL    SUBB
        CALL    STORE           ; patch DO runtime code for LEAVE
        JP      COMMA
        .endif

        .ifeq   BOOTSTRAP
;       BEGIN   ( -- a )
;       Start an infinite or
;       indefinite loop structure.

        HEADFLG BEGIN "BEGIN" IMEDD
BEGIN:
        JP      HERE

;       UNTIL   ( a -- )
;       Terminate a BEGIN-UNTIL
;       indefinite loop structure.

        HEADFLG UNTIL "UNTIL" IMEDD
UNTIL:
        CALL    COMPI
        CALL    QBRAN
        JP      COMMA

;       AGAIN   ( a -- )
;       Terminate a BEGIN-AGAIN
;       infinite loop structure.

        HEADFLG AGAIN "AGAIN" IMEDD
AGAIN:
        CALL    CCOMMALIT
        .db     BRAN_OPC
        JP      COMMA

;       IF      ( -- A )
;       Begin a conditional branch.

        HEADFLG IFF "IF" IMEDD
IFF:
        CALL    COMPI
        CALL    QBRAN
        JRA     HERE0COMMA

;       THEN    ( A -- )
;       Terminate a conditional branch structure.

        HEADFLG THENN "THEN" IMEDD
THENN:
        CALL    HERE
        CALLR   SWAPLOC
        JP      STORE

;       ELSE    ( A -- A )
;       Start the false clause in an IF-ELSE-THEN structure.

        HEADFLG ELSE "ELSE" IMEDD
ELSE:
        CALLR   AHEAD
        CALLR   SWAPLOC
        JRA     THENN

;       AHEAD   ( -- A )
;       Compile a forward branch instruction.

        HEADFLG AHEAD "AHEAD" IMEDD
AHEAD:
        CALL    CCOMMALIT
        .db     BRAN_OPC
HERE0COMMA:
        CALL    HERE
        .endif
ZEROCOMMA:
        CALL    ZERO
        JP      COMMA

        .ifeq   BOOTSTRAP
;       WHILE   ( a -- A a )
;       Conditional branch out of a BEGIN-WHILE-REPEAT loop.

        HEADFLG WHILE "WHILE" IMEDD
WHILE:
        CALLR   IFF
SWAPLOC:
        JP      SWAPP

;       REPEAT  ( A a -- )
;       Terminate a BEGIN-WHILE-REPEAT indefinite loop.

        HEADFLG REPEA "REPEAT" IMEDD
REPEA:
        CALLR   AGAIN
        JRA     THENN

;       AFT     ( a -- a A )
;       Jump to THEN in a FOR-AFT-THEN-NEXT loop the first time through.

        HEADFLG AFT "AFT" IMEDD
AFT:
        CALL    DROP
        CALLR   AHEAD
        CALL    HERE
        JRA     SWAPLOC
        .endif

        .ifeq   BOOTSTRAP
;       ABORT"  ( -- ; <string> )
;       Conditional abort with an error message.

        HEADFLG ABRTQ 'ABORT"' IMEDD
ABRTQ:
        CALL    COMPI
        CALL    ABORQ
        JRA     STRCQLOC
        .endif

;       $"      ( -- ; <string> )
;       Compile an inline string literal.

        .ifne   WORDS_LINKCHAR
        HEADFLG STRQ '$"' IMEDD
        .endif
STRQ:
        CALL    COMPI
        CALL    STRQP
STRCQLOC:
        JP      STRCQ

        .ifeq   BOOTSTRAP
;       ."      ( -- ; <string> )
;       Compile an inline string literal to be typed out at run time.

        HEADFLG DOTQ '."' IMEDD
DOTQ:
        CALL    COMPI
        CALL    DOTQP
        JRA     STRCQLOC
        .endif

; Name compiler

;       ?UNIQUE ( a -- a )
;       Display a warning message
;       if word already exists.

        HEADER  UNIQU "?UNIQUE"
UNIQU:
        CALL    DUPP
        CALL    NAMEQ           ; "PC_?UNIQUE" patch point for CURRENT
        CALL    QBRAN           ;  name exists?
        .dw     UNIQ1
        CALL    DOTQP           ; redef are OK
        .db     7
        .ascii  " reDef "
        CALL    OVER
        CALL    COUNTTYPES      ; just in case
UNIQ1:  JP      DROP


;       $,n     ( na -- )
;       Build a new dictionary name
;       using string at na.

        HEADER  SNAME ^/"$,n"/
SNAME:
        CALL    DUPPCAT         ; ?null input
        CALL    QBRAN
        .dw     PNAM1
        CALLR   UNIQU           ; ?redefinition
        CALL    DUPP
        CALL    CNTPCPPSTORE
        CALL    DUPP
        CALL    LAST
        CALL    STORE           ; save na for vocabulary link
        CALL    CELLM           ; link address
        CALL    CNTXT
        CALL    AT
        CALL    SWAPP
        JP      STORE           ; save code pointer
PNAM1:  CALL    STRQP
        .db     5
        .ascii  " name"         ; null input
        JP      ABOR1

; FORTH compiler

;       $COMPILE        ( a -- )
;       Compile next word to
;       dictionary as a token or literal.

        HEADER  SCOMP "$COMPILE"
SCOMP:
        CALL    NAMEQ
        CALL    QDQBRAN         ; ?defined
        .dw     SCOM2
        CALL    CAT
        INCW    X
        INCW    X
        AND     A,#IMEDD
        JREQ    SCOM1

        JP      EXECU
SCOM1:  JP      JSRC
SCOM2:  CALL    NUMBQ           ; try to convert to number
        CALL    QBRAN
        .dw     ABOR1
        JP      LITER

;       OVERT   ( -- )
;       Link a new word into vocabulary.

        HEADER  OVERT "OVERT"
OVERT:
        .ifne   HAS_CPNVM
        LDW     Y,USRLAST
        JRMI    1$              ; check if USRLAST points to NVM
        LDW     USRCONTEXT,Y
        RET
1$:
        LDW     NVMCONTEXT,Y    ; update NVMCONTEXT
        LDW     [USRCTOP],Y     ; update link from RAM dictionary
        RET

        .else
        LDW     Y,USRLAST
        LDW     USRCONTEXT,Y
        RET
        .endif

;       ;       ( -- )
;       Terminate a colon definition.

        HEADFLG SEMIS ^/";"/ (IMEDD+COMPO)
SEMIS:
        CALL    CCOMMALIT
        .db     EXIT_OPC
        CALL    LBRAC
        JRA     OVERT

;       :       ( -- ; <string> )
;       Start a new colon definition
;       using next word as its name.
        HEADER  COLON ":"
COLON:
        CALLR   RBRAC           ; do "]" first to set HERE to compile state
        JP      TOKSNAME        ; copy token to dictionary


;       ]       ( -- )
;       Start compiling words in
;       input stream.
        HEADER  RBRAC "]"
RBRAC:
        LDW     Y,#SCOMP
        LDW     USREVAL,Y
        RET

; Defining words

        .ifne   HAS_DOES
;       DOES>   ( -- )
;       Define action of defining words

        HEADFLG DOESS "DOES>" IMEDD
DOESS:
        CALL    COMPI
        CALLR   DODOES          ; 3 CALL dodoes>
        CALL    HERE
        .ifne  USE_CALLDOLIT
        DoLitC  9
        .else
        DoLitC  7
        .endif
        CALL    PLUS
        CALL    LITER           ; 3 CALL doLit + 2 (HERE+9)
        CALL    COMPI
        CALL    COMMA           ; 3 CALL COMMA
        CALL    CCOMMALIT
        .db     EXIT_OPC        ; 1 RET (EXIT)
        RET

;       dodoes  ( -- )
;       link action to words created by defining words

        HEADER  DODOES "dodoes" ; NOALIAS
DODOES:
        LD      A,#(USRLAST)    ; ( link field of current word )
        CALLR   AAT
        CALL    NAMET           ; ' ( 'last  )
        DoLitC  BRAN_OPC        ; ' JP
        CALL    OVER            ; ' JP '
        CALL    CSTOR           ; ' \ CALL <- JP
        CALL    HERE            ; ' HERE
        CALL    OVER            ; ' HERE '
        CALL    ONEP            ; ' HERE ('+1)
        CALL    STORE           ; ' \ CALL DOVAR <- JP HERE
        .ifne  USE_CALLDOLIT
        CALL    COMPI
        CALL    DOLIT           ; ' \ HERE <- DOLIT
        .else
        CALL    CCOMMALIT
        .db     DOLIT_OPC       ; \ HERE <- DOLIT <- ('+3) <- branch
        .endif
        DoLitC  3               ; ' 3
        CALL    PLUS            ; ('+3)
        CALL    COMMA           ; \ HERE <- DOLIT <-('+3)
        CALL    CCOMMALIT
        .db     BRAN_OPC        ; \ HERE <- DOLIT <- ('+3) <- branch
        RET
        .endif

;       A@   ( A:shortAddr -- n )
;       push contents of A:shortAddr on stack
;       GENALIAS  AAT "A@"
AAT:
        CLRW    Y
        LD      YL,A
        ; fall through

;       Y@   ( Y:Addr -- n )
;       push contents of Y:Addr on stack
;       GENALIAS  YAT "Y@"
YAT:
        LDW     Y,(Y)
        JP      YSTOR

;       CREATE  ( -- ; <string> )
;       Compile a new array
;       without allocating space.

        HEADER  CREAT "CREATE"
CREAT:
        CALL    TOKSNAME        ; copy token to dictionary
        CALL    OVERT
        CALL    COMPI
        CALL    DOVAR
        RET

        .ifeq   UNLINK_CONST
;       CONSTANT ( "name" n -- )
;       Create a named constant with state dependant action

        HEADER CONST "CONSTANT"
CONST:
        CALL    COLON
        CALL    COMPI
        CALLR   DOCON           ; compile action code
        CALL    COMMA           ; compile constant
        CALL    LBRAC
        CALL    OVERT
        JRA     IMMED           ; make immediate

;       docon ( -- )
;       state dependent action code of constant

        HEADER  DOCON "docon"   ; NOALIAS
DOCON:
        POPW    Y
        CALLR   YAT             ; R> AT push constant in interpreter mode
        CALL    COMPIQ
        JREQ    1$
        CALL    LITER           ; compile constant in compiler mode
1$:     RET
        .endif

        .ifne   HAS_VARIABLE
;       VARIABLE        ( -- ; <string> )
;       Compile a new variable
;       initialized to 0.

        HEADER  VARIA "VARIABLE"
VARIA:
        CALLR   CREAT
        CALL    ZERO
        .ifne   HAS_CPNVM
        TNZ     USRCP
        JRPL    1$              ; NVM: allocate space in RAM
        DoLitW  DOVARPTR        ; overwrite call address "DOVAR" with "DOVARPTR"
        CALL    HERE
        CALL    CELLM
        CALL    STORE
        LDW     Y,USRVAR
        LDW     (X),Y           ; overwrite ZERO with RAM address for COMMA
        DoLitC  2               ; Allocate space for variable in RAM
        CALLR   ALLOT
        .endif
1$:     JP      COMMA
        .endif


        .ifne   HAS_VARIABLE
;       ALLOT   ( n -- )
;       Allocate n bytes to code DICTIONARY.

        HEADER  ALLOT "ALLOT"
ALLOT:
        CALL    CPP
        .ifne   HAS_CPNVM
        TNZ     USRCP
        JRPL    1$              ; NVM: allocate space in RAM
        LD      A,#(USRVAR)
        LD      (1,X),A
1$:
        .endif
        JP      PSTOR
        .endif

; Tools

;       IMMEDIATE       ( -- )
;       Make last compiled word
;       an immediate word.

        HEADER  IMMED "IMMEDIATE"
IMMED:
        LD      A,[USRLAST]
        OR      A,#IMEDD
        LD      [USRLAST],A
        RET

DUPPCAT:
        CALL    DUPP
        JP      CAT

        .ifeq   BOOTSTRAP
;       _TYPE   ( b u -- )
;       Display a string. Filter
;       non-printing characters.

        HEADER  UTYPE "_TYPE"
UTYPE:
        CALL    TOR             ; start count down loop
        JRA     UTYP2           ; skip first pass
UTYP1:  CALLR   DUPPCAT
        CALL    TCHAR
        CALL    [USREMIT]       ; display only printable
        CALL    ONEP            ; increment address
UTYP2:  CALL    DONXT
        .dw     UTYP1           ; loop till done
        JP      DROP
        .endif

        .ifeq   REMOVE_DUMP
;       dm+     ( a u -- a )
;       Dump u bytes from ,
;       leaving a+u on  stack.

        HEADER  DUMPP "dm+"
DUMPP:
        CALL    OVER
        DoLitC  4
        CALL    UDOTR           ; display address
        CALL    SPACE
        CALL    TOR             ; start count down loop
        JRA     PDUM2           ; skip first pass
PDUM1:  CALLR   DUPPCAT
        DoLitC  3
        CALL    UDOTR           ; display numeric data
        CALL    ONEP            ; increment address
PDUM2:  CALL    DONXT
        .dw     PDUM1           ; loop till done
        RET
        .endif

        .ifeq   REMOVE_DUMP
;       DUMP    ( a u -- )
;       Dump u bytes from a,
;       in a formatted manner.

        HEADER  DUMP "DUMP"
DUMP:
        PUSH    USRBASE+1       ; BASE AT TOR save radix
        CALL    HEX             ; leaves 16 in A
        CALL    YFLAGS
        DIV     Y,A             ; / change count to lines
        PUSHW   Y               ; start count down loop
DUMP1:  CALL    CR
        DoLitC  16
        CALL    DDUP
        CALLR   DUMPP           ; display numeric
        CALL    ROT
        CALL    ROT
        CALL    SPACE
        CALL    SPACE
        CALLR   UTYPE           ; display printable characters
        CALL    DONXT
        .dw     DUMP1           ; loop till done
DUMP3:
        POP     A
        LD      USRBASE+1,A     ; restore radix
        JP      DROP
        .endif

        .ifeq   REMOVE_DOTS
;       .S      ( ... -- ... )
;       Display contents of stack.

        HEADER  DOTS ".S"
DOTS:
        CALL    CR
        CALL    DEPTH           ; stack depth
        CALL    TOR             ; start count down loop
        JRA     DOTS2           ; skip first pass
DOTS1:  CALL    RAT
        CALL    PICK
        CALL    DOT             ; index stack, display contents
DOTS2:  CALL    DONXT
        .dw     DOTS1           ; loop till done
        CALL    DOTQP
        .db     5
        .ascii  " <sp "
        RET
        .endif

        .ifeq   BOOTSTRAP
;       .ID     ( na -- )
;       Display name at address.

        HEADER  DOTID ".ID"
DOTID:
        CALL    QDQBRAN         ; if zero no name
        .dw     DOTI1
        CALL    COUNT
        DoLitC  0x01F
        CALL    ANDD            ; mask lexicon bits
        JP      UTYPE
DOTI1:  CALL    DOTQP
        .db     9
        .ascii  " (noName)"
        RET
        .endif


        .ifeq   REMOVE_TNAME
;       >NAME   ( ca -- na | F )
;       Convert code address
;       to a name address.

        HEADER  TNAME ">NAME"
TNAME:
        CALL    CNTXT           ; vocabulary link
TNAM2:  CALL    AT
        CALL    DUPP            ; ?last word in a vocabulary
        CALL    QBRAN
        .dw     TNAM4
        CALL    DDUP
        CALL    NAMET
        CALL    XORR            ; compare
        CALL    QBRAN
        .dw     TNAM3
        CALL    CELLM           ; continue with next word
        JRA     TNAM2
TNAM3:  JP      NIP
TNAM4:  CALL    DDROP
        JP      ZERO
        .endif

        .ifeq   UNLINKCORE
;       WORDS   ( -- )
;       Display names in vocabulary.

        HEADER  WORDS "WORDS"
WORDS:
        CALL    CR
        CALL    CNTXT_ALIAS     ; only in context
WORS1:  CALL    AT              ; @ sets Z and N
        JREQ    1$              ; ?at end of list
        CALL    DUPP
        CALL    SPACE           ; "PC_WORDS" patch point for CURRENT
        CALL    DOTID           ; display a name
        CALL    CELLM
        JRA     WORS1
1$:     JP      DROP
        .endif

;===============================================================

        .ifne   WORDS_EXTRASTACK

;       SP!     ( a -- )
;       Set data stack pointer.

        HEADER  SPSTO "sp!"
SPSTO:
        LDW     X,(X)   ;X = a
        RET

;       SP@     ( -- a )        ( TOS STM8: -- Y,Z,N )
;       Push current stack pointer.

        HEADER  SPAT "sp@"
SPAT:
        LDW     Y,X
        JP      YSTOR

;       RP@     ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Push current RP to data stack.

        HEADER  RPAT "rp@"
RPAT:
        LDW     Y,SP            ; save return addr
        JP      YSTOR

;       RP!     ( a -- )
;       Set return stack pointer.

        HEADFLG RPSTO "rp!" COMPO
RPSTO:
        POPW    Y
        LDW     YTEMP,Y
        CALL    YFLAGS          ; fixed error: TOS not consumed
        LDW     SP,Y
        JP      [YTEMP]

        .endif

;===============================================================

        .ifne   WORDS_EXTRAEEPR
;       ULOCK  ( -- )
;       Unlock EEPROM (STM8S)

        HEADER  ULOCK "ULOCK"
ULOCK:
        MOV     FLASH_DUKR,#0xAE
        MOV     FLASH_DUKR,#0x56
1$:     BTJF    FLASH_IAPSR,#3,1$    ; PM0051 4.1 requires polling bit3=1 before writing
        RET


;       LOCK  ( -- )
;       Lock EEPROM (STM8S)

        HEADER  LOCK "LOCK"
LOCK:
        BRES    FLASH_IAPSR,#3
        RET
        .endif

        .ifne   HAS_CPNVM
;       ULOCKF  ( -- )
;       Unlock Flash (STM8S)

        HEADER  UNLOCK_FLASH "ULOCKF"
UNLOCK_FLASH:
        MOV     FLASH_PUKR,#0x56
        MOV     FLASH_PUKR,#0xAE
1$:     BTJF    FLASH_IAPSR,#1,1$    ; PM0051 4.1 requires polling bit1=1 before writing
        RET

;       LOCKF  ( -- )
;       Lock Flash (STM8S)

        HEADER  LOCK_FLASH "LOCKF"
LOCK_FLASH:
        BRES    FLASH_IAPSR,#1
        RET

;       Helper routine: swap USRCP and NVMCP
SWAPCP:
        LDW     X,USRCP
        MOV     USRCP,NVMCP
        MOV     USRCP+1,NVMCP+1
        LDW     NVMCP,X
        EXGW    X,Y
        RET

;       NVM  ( -- )
;       Compile to NVM (enter mode NVM)

        HEADER  NVMM "NVM"
NVMM:
        TNZ     USRCP
        JRMI    1$           ; state entry action?
        ; in NVM mode only link words in NVM
        EXGW    X,Y
        LDW     X,NVMCONTEXT
        LDW     USRLAST,X
        CALLR   SWAPCP
        CALLR   UNLOCK_FLASH
1$:
        RET

;       RAM  ( -- )
;       Compile to RAM (enter mode RAM)

        HEADER  RAMM "RAM"
RAMM:
        TNZ     USRCP
        JRPL    1$

        EXGW    X,Y
        LDW     X,USRVAR
        LDW     COLDCTOP,X
        LDW     X,USRCP
        LDW     COLDNVMCP,X
        LDW     X,NVMCONTEXT
        LDW     COLDCONTEXT,X
        LDW     X,USRCONTEXT
        LDW     USRLAST,X
        CALLR   SWAPCP          ; Switch back to mode RAM
        CALLR   LOCK_FLASH
1$:
        RET

;       RESET  ( -- )
;       Reset Flash dictionary and 'BOOT to defaults and restart

        HEADER  RESETT "RESET"
RESETT:
        CALLR   UNLOCK_FLASH
        DoLitW  UDEFAULTS
        DoLitW  UBOOT
        DoLitC  (ULAST-UBOOT)
        CALL    CMOVE           ; initialize user area
        CALLR   LOCK_FLASH
        JP      COLD

;       SAVEC ( -- )
;       Minimal context switch for low level interrupt code
;       This should be the first word called in the interrupt handler

        HEADER  SAVEC "SAVEC"
SAVEC:
        POPW    Y
        LDW     X,YTEMP
        PUSHW   X
        LDW     X,#ISPP         ; "ISPP" const. top of int. data stack
        JP      (Y)

;       IRET ( -- )
;       Restore context and return from low level interrupt code
;       This should be the last word called in the interrupt handler

        HEADER  RESTC "IRET"
RESTC:
        POPW    X               ; discard CALL return address
        POPW    X
        LDW     YTEMP,X         ; restore context
        IRET                    ; resturn from interrupt

        .endif

;       WIPE   ( -- )   ( TOS STM8: - )
;       Return to RAM mode, claim VARIABLE RAM, init dictionary in RAM

        HEADER  WIPE "WIPE"
WIPE:
        .ifeq  HAS_CPNVM
        JP      OVERT           ; initialize CONTEXT from USRLAST
        .else
        CALLR   RAMM
        PUSHW   X
        LDW     X,COLDCTOP      ; reserve some space for user variable
        LDW     USRVAR,X
        ADDW    X,#RAM_VARIABLE
        LDW     USRCTOP,X       ; store new CTOP
        LDW     Y,COLDCONTEXT
        LDW     NVMCONTEXT,Y
        LDW     (X),Y           ; create dummy word in RAM ...
        INCW    X
        INCW    X
        CLR     (X)             ; ... with NULL string
        LDW     USRLAST,X       ; prepare OVERT
        INCW    X
        LDW     USRCP,X         ; done
        POPW    X
        JP      OVERT           ; initialize CONTEXT from USRLAST
        .endif

;===============================================================

        LASTN   =       LINK    ;last name defined
        END_SDCC_FLASH = .

        .area CODE
        .area INITIALIZER
        .area CABS (ABS)
