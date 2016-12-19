; STM8EF for STM8S003F3 (Value Line) devices
;
; This is derived work based on 
; http://www.forth.org/svfig/kk/07-2010.html
; 
; Refer to LICENSE.md for license information.
;
;--------------------------------------------------------
; Original author, and copyright:
;       STM8EF, Version 2.1, 13jul10cht
;       Copyright (c) 2000
;       Dr. C. H. Ting
;       156 14th Avenue
;       San Mateo, CA 94402
;       (650) 571-7639

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
; Non-functional changes and code refactoring:
; * SDCC tool chain "ASxxxx V2.0" syntax
; * STM8S105C6 dependencies removed (e.g. UART2)
; * support for different target boards
; * configuration files for code options
; * 1K RAM layout, symbols for RAM loc. ROM size options
; * binary size optimization
;
; New features, e.g.:
; * board support:
;       - W1209 LED display & half-duplex with SW TX 
;       - C0135 Relay-4 Board
;       - STM8S103F3 "$0.70" breakout board
; * preemptive background operation with fixed cycle time
; * configurable startup & default constants: 'BOOT
; * configurable vocabulary subsets for binary size reduction
; * CREATE-DOES> for defining words
; * New loop structure words: DO LEAVE LOOP +LOOP
; * native BRANCH and EXIT
; * words for STM8 ADC control: ADC! ADC@ 
; * words for board keys, outputs, LEDs: OUT OUT!
; * words for EEPROM, FLASH lock/unlock: LOCK ULOCK LOCKF ULOCKF
; * words for bit operations, inv. order word access: BSR 2C@ 2C! 
; * words for compile to Flash memory: NVR RAM RESET
; * words for ASCII file transfer: FILE HAND
;
; Docs for the SDCC integrated assembler are scarce, and
; hence SDCC was used to create a template for this file:
;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (Linux)
;--------------------------------------------------------

	.module forth
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------

        .globl _TIM2_UO_IRQHandler
	.globl _TIM4_IRQHandler
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

        ;**********************************
        ;******  1) Global defaults  ******
        ;**********************************
        ; Note: add defaults for new features here but 
        ;       configure them in globconf.inc  

        STM8S_DISCOVERY = 0     ; (currently broken)
        BOARD_MINDEV =    0     ; STM8S103F3 "minimum development board"
        BOARD_W1209 =     0     ; W1209 Thermostat board
        BOARD_C0135 =     0     ; C0135 "Relay Board-4 STM8S"

        STM8S003F3   =    0     ; 8K flash, 1K RAM, 128 EEPROM, UART1
        STM8S103F3   =    0     ; like STM8S003F3, 640 EEPROM 
        STM8S105C6   =    0     ; 32K flash, 2K RAM, 1K EEPROM, UART2

        HALF_DUPLEX  =    0     ; RS232 shared Rx/Tx line, bus style
        TERM_LINUX   =    1     ; LF terminates line 

        HAS_TXDSIM   =    0     ; TxD SW simulation
        HAS_LED7SEG  =    0     ; 7-seg LED on board
        HAS_KEYS     =    0     ; Board has keys
        HAS_OUTPUTS  =    0     ; Board outputs, e.g. relays
        HAS_INPUTS   =    0     ; Board digital inputs
        HAS_ADC      =    0     ; Board analog inputs
        
        HAS_BACKGROUND =  0     ; Background Forth task (TIM2 ticker)
        HAS_CPNVM    =    0     ; Can compile to Flash, always interpret to RAM 
        HAS_DOES     =    0     ; DOES> extension
        HAS_DOLOOP   =    0     ; DO .. LOOP extension: DO LEAVE LOOP +LOOP

        BCKGRND_EMIT = DROP     ; "NUL" background EMIT vector
        BCKGRND_QKEY = ZERO     ; "NUL" background QKEY vector

        CASEINSENSITIVE = 0     ; Case insensitive dictionary search
        SPEEDOVERSIZE   = 0     ; Speed-over-size in core words ROT - = < 
        BAREBONES       = 0     ; Remove or unlink some more: hi HERE .R U.R SPACES        

        WORDS_LINKCOMP =  0     ; Link words for compiler extensions: doLit donxt ?branch branch EXECUTE EXIT doVAR [COMPILE] COMPILE $,"
        WORDS_LINKCOMPC = 0     ; Link composing words of compiler: cp last do$ OVERT $"| ."| $,n NVM? dodoes 
        WORDS_LINKINTER = 0     ; Link interpreter core words: hi 'BOOT tmp >IN 'eval CONTEXT pars PARSE WORD TOKEN NAME> SAME? find ABORT aborq $INTERPRET INTER? .OK ?STACK EVAL PRESET QUIT ?UNIQUE $COMPILE
        WORDS_LINKCHAR =  0     ; Link char I/O core words: ACCEPT TAP kTAP QUERY #TIB hld TIB >CHAR COUNT DIGIT <# HOLD # #S SIGN #> str DIGIT? NUMBER? _TYPE 
        WORDS_LINKMISC =  0     ; Link composing words of SEE DUMP WORDS NVM 

        WORDS_EXTRASTACK = 0    ; Link/include stack core words: rp@ rp! sp! sp@ DEPTH 
        WORDS_EXTRADEBUG = 0    ; Extra debug words: SEE
        WORDS_EXTRACORE  = 0    ; Extra core words: =0 I
        WORDS_EXTRAMEM   = 0    ; Extra memory words: BSR 2C@ 2C!
        WORDS_EXTRAEEPR  = 0    ; Extra EEPROM lock/unlock words: LOCK ULOCK 
        WORDS_HWREG      = 0    ; Peripheral Register words

        ;*************************************************
        ;******  2) Hardware/board type selection  ******
        ;*************************************************

        ; sdasstm8 doesn't accept constants on the command line. 
        ; work-around: define directory for reading the config with 
        ; the "-I" option 

        .include "globconf.inc"

        ;**********************************************
        ;******  3) Device dependent features  ******
        ;**********************************************
        ; Define memory location for device dependent features here

	;******  STM8S memory addresses ******
	RAMBASE =	0x0000	; STM8S RAM start
        EEPROMBASE =    0x4000  ; STM8S EEPROM start

        .ifne   STM8S003F3
        EEPROMEND =     0x407F  ; STM8S003F3: 128 bytes EEPROM
        .endif

        .ifne   STM8S103F3
        EEPROMEND =     0x427F  ; STM8S103F3: 640 bytes EEPROM
        .endif

        .ifne   (STM8S003F3 + STM8S103F3)
        ;******  STM8SF103 Memory Layout ******
        RAMEND =        0x03FF	; system (return) stack, growing down

        FORTHRAM =      0x0020  ; Start of RAM controlled by Forth
        UPPLOC  =       0x0060  ; UPP (user/system area) location for 1K RAM
        CTOPLOC =       0x0080  ; CTOP (user dictionary) location for 1K RAM
        SPPLOC  =       0x0350  ; SPP (data stack top), TIB start
        RPPLOC  =       RAMEND  ; RPP (return stack top)
        
        FLASHEND =      0x9FFF  ; 8K devices 
       
	;******  STM8SF103 Registers  ******
        .include        "stm8s003f3.inc"
        .endif


        ;************************************************
        ;******  4) Board Driver Memory  ******
        ;************************************************
        ; Memory for board related code, e.g. interrupt routines
         
        ; ****** Indirect variables for code in NVM *****
        .ifne   HAS_CPNVM
        USRPOOL =    FORTHRAM   ; RAM for indirect variables (grow up)  
        .endif


        
	;******  Background task variables  ******
        .ifne   HAS_BACKGROUND
        PADBG     =     0x4F    ; PAD in background task growing down from here 

        BGADDR   =      0x50    ; address of background routine (0: off) 
        TICKCNT =       0x52    ; 16 bit ticker (counts up)
        TICKCNTL =      0x53    ; ticker LSB

        .ifne   HAS_KEYS
        KEYREPET =      0x54    ; board key repetition control (8 bit)
        .endif
        
        BSPPSIZE  =     32      ; Size of data stack for background tasks

        .else
        BSPPSIZE  =     0       ;  no background, no extra data stack
        .endif

	;******  Board variables  ******
        .ifne   HAS_TXDSIM
        TIM4TCNT =      0x58    ; TIM4 TX interrupt counter
        TIM4TXREG  =    0x59    ; TIM4 char for TX
        .endif

        .ifne   HAS_OUTPUTS
        OUTPUTS =       0x5A    ; outputs, like relays, LEDs, etc. (16 bit)
        .endif


        .ifne   HAS_LED7SEG
        LED7MSB  =      0x5C    ; word 7S LEDs digits  43..
        LED7LSB  =      0x5E    ; word 7S LEDs digits  ..21
        .endif

        ;**************************************************
	;******  5) General User & System Variables  ******
        ;**************************************************

        UPP   = UPPLOC          ; offset user area
        CTOP  = CTOPLOC         ; dictionary start, growing up
                                ; note: PAD is inbetween CTOP and SPP
	SPP   = SPPLOC-BSPPSIZE	; data stack, growing down (with SPP-1 first)
        BSPP  = SPPLOC          ; Background data stack, grouwing down
        TIBB  = SPPLOC          ; Term. Input Buf. TIBLENGTH between SPPLOC and RPP
	RPP   = RPPLOC          ; return stack, growing down
        
        ; Core variables (same order as 'BOOT initializer block)

        ; TODO: refactor into BGPP, UPP and UPP0 
        USRRAMINIT = USREMIT

        USREMIT  =   UPP+0      ; excection vector of EMIT
        USRQKEY =    UPP+2      ; excection vector of QKEY
        USRBASE =    UPP+4      ; radix base for numeric I/O
        USREVAL =    UPP+6      ; execution vector of EVAL
        USRPROMPT =  UPP+8      ; point to prompt word (default .OK)
        USRCP   =    UPP+10     ; point to top of dictionary
        USRLAST =    UPP+12     ; currently last name in dictionary (init: to LASTN)
        NVMCP   =    UPP+14     ; point to top of dictionary in Non Volatile Memory 

        ; Null initialized core variables (growing down)

        NVMCONTEXT = UPP+18     ; point to top of dictionary in Non Volatile Memory 
        USRCONTEXT = UPP+20     ; start vocabulary search
        USRHLD  =    UPP+22     ; hold a pointer of output string
        USRNTIB =    UPP+24     ; count in terminal input buffer 
        USR_IN  =    UPP+26     ; hold parsing pointer
        USRTEMP =    UPP+28     ; temporary storage for interpreter (VARIABLE tmp)
        YTEMP	=    UPP+30	; extra working register for core words

        ;************************************
	;******  6) General Constants  ******
        ;************************************

	VER     =     2         ; Version major release version
	EXT     =     2         ; Version minor extension

	TRUEE   =     0xFFFF    ; true flag
	COMPO   =     0x40      ; lexicon compile only bit
	IMEDD   =     0x80      ; lexicon immediate bit
	MASKK   =     0x1F7F    ; lexicon bit mask

        TIBLENGTH =   80        ; size of TIB (starting at TIBOFFS)
        PADOFFS =     80        ; offset text buffer above dictionary 
	CELLL   =      2        ; size of a cell
	BASEE   =     10        ; default radix
        BKSPP   =      8        ; backspace
	LF      =     10        ; line feed
        PACE    =     11        ; pace character for host handshake (ASCII VT) 
	CRR     =     13        ; carriage return
	ERR     =     27        ; error escape
	TIC     =     39        ; tick

        EXIT_OPC =    0x81      ; RET opcode
	BRAN_OPC =    0xCC      ; JP opcode
	CALL_OPC =    0xCD      ; CALL opcode


        ;***********************
	;******  7) Code  ******
        ;***********************


; Main entry points and COLD start data

;	COLD	( -- )
;	The hilevel cold start sequence.

	.dw	0
	
	LINK =	.
	.db	4
	.ascii	"COLD"
_forth:                         ; SDCC entry 
        ; Note: no return to main.c possible unless RAMEND equals SP, 
        ; and RPP init skipped

COLD:
        SIM                     ; disable interrupts 
        
        LDW     X,#(RAMEND-FORTHRAM) 
1$:	CLR     (FORTHRAM,X)                    
	DECW    X
	JRPL    1$

	LDW	X,#RPP	        ; initialize return stack
	LDW	SP,X
	LDW	X,#SPP          ; Pre-initialize data stack

	CALL	DOLIT
	.dw	UZERO
	CALL	DOLITC
        .db     USRRAMINIT
	CALL	DOLITC
	.db	(ULAST-UZERO)
	CALL	CMOVE	        ; initialize user area

	CALL	PRESE	        ; initialize data stack, TIB 

         ; Board I/O initialization
        .include "boardinit.inc"

        .ifne   HAS_OUTPUTS
        CALL    ZERO
        CALL    OUTSTOR
        .endif

        ; Hardware initialization complete
        RIM                     ; enable interrupts 

 	CALL	TBOOT
	CALL	ATEXE	        ; application boot
        CALL	OVERT           ; initialize CONTEXT from USRLAST 
	JP	QUIT	        ; start interpretation


;	'BOOT	( -- a )
;	The application startup vector and NVM USR setting array 

        .ifne   (WORDS_LINKINTER + HAS_CPNVM)
	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"'BOOT"
        .endif
TBOOT:
	CALL	DOVAR
        UBOOT = .
	.dw	HI	        ;application to boot

        ; COLD start initiates these variables.
        UZERO = .
	.dw	TXSTOR	        ; EMIT vector
        .dw     QRX             ; ?KEY vector
	.dw	BASEE	        ; BASE
	.dw	INTER	        ; 'EVAL
        .dw     DOTOK           ; 'PROMPT 
	.dw	CTOP	        ; CP in RAM
        COLDCONTEXT = .
	.dw	LASTN	        ; USRLAST 
        .ifne   HAS_CPNVM
        COLDNVMCP = .
        .dw     END_SDCC_FLASH  ; CP in NVM
        ULAST = .

        ; Second copy of USR setting for NVM reset
        UDEFAULTS = .
        .dw     HI              ; 'BOOT 
	.dw	TXSTOR	        ; EMIT vector
        .dw     QRX             ; ?KEY vector
	.dw	BASEE	        ; BASE
	.dw	INTER	        ; 'EVAL
        .dw     DOTOK           ; 'PROMPT 
	.dw	CTOP	        ; CP in RAM
	.dw	LASTN	        ; CONTEXT pointer
        .dw     END_SDCC_FLASH  ; CP in NVM
        .else
        ULAST = .
        .endif


        .ifeq   BAREBONES
;	hi	( -- )
;	Display sign-on message.

        .ifne   (WORDS_LINKINTER + HAS_CPNVM)
	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"hi"
        .endif
HI:
        .ifne   HAS_LED7SEG
        MOV     LED7MSB+1,#0x66 ; 7S LEDs .4..
        MOV     LED7LSB,  #0x78 ; 7S LEDs ..t.
        MOV     LED7LSB+1,#0x74 ; 7S LEDs ...h
        .endif
	
        CALL	CR
	CALL	DOTQP	        ; initialize I/O
	.db	15
	.ascii	"stm8eForth v"
	.db	(VER+'0')
	.ascii	"."
	.db	(EXT+'0')       ;version

	JP	CR
        .endif



;      Device dependent I/O


_TIM4_IRQHandler:

        .ifne   HAS_TXDSIM
        ; TIM4 interrupt handler W1209 software TxD. 
        ; RxD (PD_6) is on the board's sensor header, 
        ; STM8S UART1 half-duplex mode requires TxD (PD_5) 
        ; Work-around: change from RxD to GPIO for SW-TX
        ; To use, write char to TIM4TXREG, then 0x0A to TIM4TCNT
        ; BCPL    PA_ODR,#3     ; pin debug
        BRES    TIM4_SR,#0      ; clear TIM4 UIF 
        LD      A,TIM4TCNT
        JRNE    TIM4_TRANS      ; transmit in progress
        BRES    TIM4_IER,#0     ; disable TIM4 interrupt
        JRNE    TIM4_END        ; nothing to transmit
TIM4_TRANS:        
        CP      A,#0x0B         ; TIM4TCNT > 0x0A: count down
        JRMI    TIM4_START      
        JRA     TIM4_DEC       

TIM4_START:  
        CP      A,#10
        JRNE    TIM4_STOP

        ; configure PD_6 from RX to GPIO 
        BRES	UART1_CR2,#2	; disable RX
        BSET    PD_DDR,#PDTX    ; set PD_6 to output

        RCF                     ; start bit, set PD_6 low 
        JRA     TIM4_BIT         

TIM4_STOP:  
        CP      A,#1
        JRNE    TIM4_SER
        ; TIM4TCNT == 1 
        SCF                     ; stop bit, set PD_6 high 
        JRA     TIM4_BIT         
               
TIM4_SER:
        ; TIM4TCNT == 9:2
        SRL     TIM4TXREG    
        ; fall through

TIM4_BIT:
        ; Set RxTx port to CF 
        BCCM    PD_ODR,#PDTX
        ; fall through

TIM4_DEC:             
        DEC     TIM4TCNT        ; next TXD TIM4 state
        JRNE    TIM4_END

        ; TIM4TCNT == 0
        BRES    PD_DDR,#PDTX    ; set PD_6 to input
        BSET	UART1_CR2,#2	; re-enable RX
        ; fall through

TIM4_END:             
        ; BCPL    PA_ODR,#3
        IRET 
        .endif


;       TIM2 interrupt handler for background task 
_TIM2_UO_IRQHandler:
        .ifne   (HAS_LED7SEG + HAS_BACKGROUND)
        ; BSET    PA_ODR,#3     ; pin debug
        BRES    TIM2_SR1,#0     ; clear TIM2 UIF 

        .ifne   HAS_LED7SEG
        CALL    LED_MPX
        .endif

        .ifne   HAS_BACKGROUND 
        LDW     X,TICKCNT
        INCW    X
        LDW     TICKCNT,X

        LDW     Y,BGADDR        ; address of background task
        TNZW    Y               ; 0: background operation off 
        JREQ    1$

        LDW     X,YTEMP         ; Save context 
        PUSHW   X

        
        PUSH    USRBASE+1     ; 8bit since BASE should be < 36
        MOV     USRBASE+1,#10

        LDW     X,USREMIT       ; save EMIT exection vector
        PUSHW   X
        LDW     X,#(BCKGRND_EMIT)
        LDW     USREMIT,X
        
        LDW     X,USRQKEY       ; save QKEY exection vector
        PUSHW   X
        LDW     X,#(BCKGRND_QKEY)
        LDW     USRQKEY,X

        LDW     X,USRHLD
        PUSHW   X
        LDW     X,#(PADBG)      ; in background task, alway start with an empty PAD
        LDW     USRHLD,X
        
        LDW     X,#(BSPP)       ; init data stack for background task to BSPP 
        CALL    (Y)

        POPW    X
        LDW     USRHLD,X

        POPW    X
        LDW     USRQKEY,X

        POPW    X
        LDW     USREMIT,X
        
        POP     USRBASE+1

        POPW    X
        LDW     YTEMP,X
1$:
        .endif

        ; BRES    PA_ODR,#3
        IRET
        .endif


        .ifne   HAS_LED7SEG
;       Multiplexed 7-seg LED display
LED_MPX:        
        LD      A,TICKCNTL
        AND	A,#3        
        .ifne   BOARD_W1209        
        BSET    PD_ODR,#4       ; clear digit outputs .321
        BSET    PB_ODR,#5
        BSET    PB_ODR,#4

        JRNE    1$
        LD      A,LED7MSB+1
        BRES    PD_ODR,#4       ; digit .3.. 
        JRA     3$

1$:     CP      A,#1
        JRNE    2$
        LD      A,LED7LSB
        BRES    PB_ODR,#5       ; digit ..2.
        JRA     3$

2$:     CP      A,#2
        JRNE    4$  
        LD      A,LED7LSB+1 
        BRES    PB_ODR,#4       ; digit ...1
        ; fall through
         
3$:
        ; W1209 7S LED display row
        ; bit 76453210 input (parameter A)
        ;  PA .....FB.
        ;  PC CG...... 
        ;  PD ..A.DPE.
        RRC     A
        BCCM    PD_ODR,#5       ; A
        RRC     A
        BCCM    PA_ODR,#2       ; B
        RRC     A
        BCCM    PC_ODR,#7       ; C
        RRC     A
        BCCM    PD_ODR,#3       ; D
        RRC     A
        BCCM    PD_ODR,#1       ; E
        RRC     A
        BCCM    PA_ODR,#1       ; F
        RRC     A
        BCCM    PC_ODR,#6       ; G
        RRC     A
        BCCM    PD_ODR,#2       ; P
4$:        
        .else
        ; implement board LED port mapping 
        .endif
        RET

        .endif

; ==============================================

;	?KEY	( -- c T | F )  ( TOS STM8: -- Y,Z,N )
;	Return input char and true, or false.
	.dw	LINK
	LINK =	.
	.db	4
	.ascii	"?KEY"
QKEY:
        .ifeq   BAREBONES
        JP      [USRQKEY]


;	?RX	( -- c T | F )  ( TOS STM8: -- Y,Z,N )
;	Return serial interface input char from and true, or false.
	.dw	LINK
	LINK =	.
	.db	3
	.ascii	"?RX"
        .endif
QRX:
        CLR     A               ; A: flag false
	BTJF    UART1_SR,#5,QRXSTOR
	LD	A,UART1_DR	; get char in A
ATOKEY:
        CALLR   QRXSTOR         ; push char
        JP      ONE             ; flag true
QRXSTOR:
        JP      ASTOR           ; push char or flag false


;	EMIT	( c -- )
;	Send character c to output device.

	.dw	LINK
	LINK =	.
	.db	4
	.ascii	"EMIT"
EMIT:
        .ifeq   BAREBONES
        JP      [USREMIT]

;	TX!	( c -- )
;	Send character c to the serial interface.

	.dw	LINK
	LINK =	.
	.db	3
	.ascii	"TX!"
        .endif
TXSTOR:
        .ifne   HALF_DUPLEX
	BRES	UART1_CR2,#2	; disable rx

        .ifne   BOARD_W1209

1$:     BTJT    TIM4_IER,#0,1$  ; wait for end of TX
 	LD      A,(1,X)
        INCW    X               ; ADDW   X,#2 
        INCW    X
        LD      TIM4TXREG,A
        MOV     TIM4TCNT,#11     ; init next transfer 
        BSET    TIM4_IER,#0     ; enabale TIM4 interrupt
         
        .else                   ; HALF_DUPLEX, not BOARD_W1209
	LD	A,(1,X)
        INCW    X               ; ADDW   X,#2 
        INCW    X
1$:	BTJF	UART1_SR,#7,1$  ; loop until tdre
	LD	UART1_DR,A	; send A
2$:	BTJF	UART1_SR,#6,2$  ; loop until tc
	BSET	UART1_CR2,#2	; enable rx
        .endif  

        .else                   ; not HALF_DUPLEX
	LD	A,(1,X)
        INCW    X               ; ADDW   X,#2 
        INCW    X
3$:	BTJF	UART1_SR,#7,3$  ; loop until tdre
	LD	UART1_DR,A	; send A
        .endif
	RET


; The kernel
;	doLit	( -- w )
;	Push an inline literal.

	.ifne	WORDS_LINKCOMP
	.dw	LINK
	LINK =	.
	.db	(COMPO+5)
	.ascii	"doLit"
	.endif
DOLIT:
	
        DECW    X               ;SUBW	X,#2    
        DECW    X
        LDW     Y,(1,SP)
	LDW     Y,(Y)
	LDW     (X),Y
	POPW	Y
	JP      (2,Y)

;	PUSHLIT	( -- C )
;	Subroutine for DOLITC and CCOMMALIT
PUSHLIT:
        LDW     Y,(3,SP)
        DECW    X               ; LSB = literal 
	LD      A,(Y)
	LD      (X),A
        DECW    X               ; MSB = 0
        CLR     A
	LD      (X),A
        RET

;	DOLITC	( -- C )
;	Push an inline literal character (8 bit).
DOLITC:
        CALLR   PUSHLIT
CSKIPRET:
        POPW	Y
	JP      (1,Y)

;       CCOMMALIT ( -- )
;	Compile inline literall byte into code dictionary.
CCOMMALIT:
        CALLR   PUSHLIT
	CALL    CCOMMA
	JRA     CSKIPRET     

        .ifne   HAS_DOLOOP 
        ;	(+loop)	( +n -- )
        ;	Add n to index R@ and test for lower than limit (R-CELL)@.

        .ifne	WORDS_LINKCOMP
        .dw	LINK
        LINK =	.
	.db	(COMPO+8)
        .ascii	"(+loop)"
        .endif
DOPLOOP:
	LDW	Y,(5,SP)
        LDW	YTEMP,Y
        LDW     Y,X
        LDW     Y,(Y)
        INCW    X
        INCW    X
	ADDW	Y,(3,SP)
        CPW	Y,YTEMP
        JRSGE	LEAVE
        LDW	(3,SP),Y
        JRA	BRAN

;	LEAVE	( -- )
;	Leave a DO .. LOOP/+LOOP loop.

	.dw	LINK

	LINK =	.
	.db	(COMPO+5)
	.ascii	"LEAVE"
LEAVE:
        POPW	Y
        ADDW	SP,#4
	JP	(2,Y)
        .endif

;	next	( -- )
;	Code for single index loop.

	.ifne	WORDS_LINKCOMP
	.dw	LINK
	LINK =	.
	.db	(COMPO+5)
	.ascii	"donxt"
	.endif
DONXT:
	LDW     Y,(3,SP)
	DECW    Y
	JRPL    NEX1
	POPW	Y
	POP	A
	POP	A
	JP      (2,Y)
NEX1:   LDW     (3,SP),Y
        JRA     BRAN

;	?branch ( f -- )
;	Branch if flag is zero.

	.ifne	WORDS_LINKCOMP
	.dw	LINK
	LINK =	.
	.db	(COMPO+7)
	.ascii	"?branch"
	.endif
QBRAN:
	LDW     Y,X
        INCW    X               ; ADDW   X,#2 
        INCW    X
	LDW     Y,(Y)
	JREQ	BRAN
	POPW	Y
	JP      (2,Y)
	
;	branch	( -- )
;	Branch to an inline address.

	.ifne	WORDS_LINKCOMP
	.dw	LINK
	LINK =	.
	.db	(COMPO+6)
	.ascii	"branch"
	.endif
BRAN:
	POPW	Y
YJPIND:
	LDW     Y,(Y)
	JP	(Y)

;	EXECUTE ( ca -- )
;	Execute	word at ca.

	.dw	LINK
	LINK =	.
	.db	7
	.ascii	"EXECUTE"
EXECU:
	LDW     Y,X
        INCW    X               ; ADDW   X,#2 
        INCW    X
        JRA     YJPIND

;	EXIT	( -- )
;	Terminate a colon definition.

	.ifne	WORDS_LINKCOMP
	.dw	LINK
	LINK =	.
	.db	4
	.ascii	"EXIT"
	.endif
EXIT:
	POPW	Y
	RET

;	@	( a -- w )      ( TOS STM8: -- Y,Z,N )
;	Push memory location to stack.

	.dw	LINK
	LINK =	.
	.db	1
	.ascii	"@"
AT:
	LDW     Y,X	        ; Y = a
	LDW     Y,(Y)           
	LDW     Y,(Y)
	LDW     (X),Y           ; w = @Y
	RET	

;	!	( w a -- )      ( TOS STM8: -- Y,Z,N )
;	Pop data stack to memory.

	.dw	LINK
	LINK =	.
	.db	1
	.ascii	"!"
STORE:
	LDW     Y,X
	LDW     Y,(Y)	        ; Y=a
	LDW     YTEMP,Y
	LDW     Y,X
	LDW     Y,(2,Y)
	LDW     [YTEMP],Y
        JRA     DDROP


;	C@	( b -- c )      ( TOS STM8: -- A,Z,N )
;	Push byte in memory to stack.
;       STM8: Z,N

	.dw	LINK
	LINK =	.
	.db	2
	.ascii	"C@"
CAT:
	LDW     Y,X	        ; Y=b
	LDW     Y,(Y)
	LD      A,(Y)
	CLR     (X)
	LD      (1,X),A
	RET	

;	C!	( c b -- )
;	Pop	data stack to byte memory.

	.dw	LINK
	LINK =	.
	.db	2
	.ascii	"C!"
CSTOR:
	LDW     Y,X
	LDW     Y,(Y)	        ; Y=b
	LD      A,(3,X)	        ; D = c
	LD	(Y),A	        ; store c at b
	JRA     DDROP

        .ifne   WORDS_EXTRASTACK
;	RP@	( -- a )     ( TOS STM8: -- Y,Z,N )
;	Push current RP to data stack.

	.dw	LINK
	LINK =	.
	.db	3
	.ascii	"rp@"
RPAT:
	LDW     Y,SP	        ; save return addr
        JRA     YSTOR
        .endif

;	RP!	( a -- )
;	Set return stack pointer.

	.ifne   (WORDS_LINKINTER + WORDS_EXTRASTACK)
        .dw	LINK
	LINK =	.
	.db	(COMPO+3)
	.ascii	"rp!"
        .endif
RPSTO:
	POPW	Y
	LDW     YTEMP,Y
	LDW     Y,X
	LDW     Y,(Y)
	LDW     SP,Y
	JP      [YTEMP]

;	R>	( -- w )     ( TOS STM8: -- Y,Z,N )
;	Pop return stack to data stack.

	.dw	LINK
	LINK =	.
	.db	(COMPO+2)
	.ascii	"R>"
RFROM:
	POPW	Y	        ; save return addr
	LDW     YTEMP,Y
	POPW	Y
PUSHJPYTEMP:
        DECW    X
        DECW    X
	LDW     (X),Y
	JP      [YTEMP]

        .ifne   WORDS_EXTRACORE
;	I	( -- n )     ( TOS STM8: -- Y,Z,N )
;	Get inner FOR-NEXT or DO-LOOP index value
	.dw	LINK

	LINK =	.
	.db	(1)
	.ascii	"I"
IGET:
        JRA     RAT
        .endif

;	doVAR	( -- a )     ( TOS STM8: -- Y,Z,N )
;	Code for VARIABLE and CREATE.

	.ifne	WORDS_LINKCOMP
	.dw	LINK
	LINK =	.
	.db	(COMPO+5)
	.ascii	"doVar"
	.endif
DOVAR:
	POPW	Y	        ; get return addr (pfa)
        ; fall through

;       YSTOR core ( -- n )     ( TOS STM8: -- Y,Z,N )
;       push Y to stack
YSTOR:        
        DECW    X               ; SUBW	X,#2    
        DECW    X
	LDW     (X),Y	        ; push on stack
	RET	                ; go to RET of EXEC

;	DROP	( w -- )        ( TOS STM8: -- Y,Z,N )
;	Discard top stack item.

	.dw	LINK
	LINK =	.
	.db	4
	.ascii	"DROP"
DROP:
        INCW    X               ; ADDW   X,#2 
        INCW    X
YTOS:
        LDW     Y,X
        LDW     Y,(Y)
	RET	

;	2DROP	( w w -- )
;	Discard two items on stack.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"2DROP"
DDROP:
	INCW    X
        INCW    X
        JRA     DROP

;	R@	( -- w )        ( TOS STM8: -- Y,Z,N )
;	Copy top of return stack to stack (or the FOR - NEXT index value).

	.dw	LINK
	LINK =	.
	.db	2
	.ascii	"R@"
RAT:
	LDW     Y,(3,SP)
        JRA     YSTOR

;	>R	( w -- )      ( TOS STM8: -- Y,Z,N )
;	Push data stack to return stack.

	.dw	LINK
	LINK =	.
	.db	(COMPO+2)
	.ascii	">R"
TOR:
	POPW	Y	        ; save return addr
	LDW     YTEMP,Y
	LDW     Y,X
	LDW     Y,(Y)
	PUSHW   Y	        ; restore return addr
        LDW     Y,YTEMP
        PUSHW   Y
        JRA     DROP


;	SP@	( -- a )        ( TOS STM8: -- Y,Z,N )
;	Push current stack pointer.

        .ifne   WORDS_EXTRASTACK
	.dw	LINK
	LINK =	.
	.db	3
	.ascii	"sp@"
        .endif
SPAT:
	LDW     Y,X
        JRA      YSTOR


;	DUP	( w -- w w )    ( TOS STM8: -- Y,Z,N )
;	Duplicate top stack item.

	.dw	LINK
	LINK =	.
	.db	3
	.ascii	"DUP"
DUPP:
	LDW     Y,X
	LDW     Y,(Y)
        JRA     YSTOR

;	SWAP ( w1 w2 -- w2 w1 ) ( TOS STM8: -- Y,Z,N )
;	Exchange top two stack items.

	.dw	LINK
	LINK =	.
	.db	4
	.ascii	"SWAP"
SWAPP:
	LDW     Y,X
	LDW     Y,(2,Y)
        PUSHW   Y
	LDW     Y,X
	LDW     Y,(Y)
	LDW     (2,X),Y
        POPW    Y
	LDW     (X),Y
	RET	


;	OVER	( w1 w2 -- w1 w2 w1 ) ( TOS STM8: -- Y,Z,N )
;	Copy second stack item to top.

	.dw	LINK
	LINK =	.
	.db	4
	.ascii	"OVER"
OVER:
	LDW     Y,X
	LDW     Y,(2,Y)
        JRA     YSTOR

;	+	( w w -- sum ) ( TOS STM8: -- Y,Z,N )
;	Add top two items.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"+"

PLUS:
	LD	A,(1,X)	;D=w
	ADD     A,(3,X)
	LD      (3,X),A
	LD      A,(X)
	ADC     A,(2,X)
LDADROP:
	LD      (2,X),A
        JRA     DROP

;	XOR	( w w -- w )    ( TOS STM8: -- Y,Z,N )
;	Bitwise exclusive OR.

	.dw	LINK
	LINK =	.
	.db	3
	.ascii	"XOR"
XORR:
	LD	A,(1,X)	        ; D=w
	XOR	A,(3,X)
	LD      (3,X),A
	LD      A,(X)
	XOR	A,(2,X)
        JRA     LDADROP

;	AND	( w w -- w )    ( TOS STM8: -- Y,Z,N )
;	Bitwise AND.

	.dw	LINK
	LINK =	.
	.db	3
	.ascii	"AND"
ANDD:
	LD	A,(1,X)	        ; D=w
	AND	A,(3,X)
	LD      (3,X),A
	LD      A,(X)
	AND	A,(2,X)
        JRA     LDADROP

;	OR	( w w -- w )    ( TOS STM8: -- Y,Z,N )
;	Bitwise inclusive OR.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"OR"
ORR:
	LD	A,(1,X)	        ; D=w
	OR	A,(3,X)
	LD      (3,X),A
	LD      A,(X)
	OR	A,(2,X)
        JRA     LDADROP

;	0<	( n -- t ) ( TOS STM8: -- A,Z )
;	Return true if n is negative.

	.dw	LINK
	LINK =	.
	.db	2
	.ascii	"0<"
ZLESS:
	CLR     A
	LDW     Y,X
	LDW     Y,(Y)
	JRPL	ZL1
	CPL     A	        ; true
ZL1:    LD      (X),A
	LD      (1,X),A
	RET	

;	-   ( n1 n2 -- n1-n2 )  ( TOS STM8: -- Y,Z,N )
;	Subtraction.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"-"

SUBB:
        .ifne   SPEEDOVERSIZE
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
        .else
        CALL    NEGAT           ; (15 cy)
        JRA     PLUS            ; 25 cy (15+10) 
        .endif
 
;	UM+	( u u -- udsum )
;	Add two unsigned single
;	and return a double sum.

	.dw	LINK
	LINK =	.
	.db	3
	.ascii	"UM+"
UPLUS:
	LD      A,#1
	LDW     Y,X
	LDW     Y,(2,Y)
	LDW     YTEMP,Y
	LDW     Y,X
	LDW     Y,(Y)
	ADDW    Y,YTEMP
	LDW     (2,X),Y
	JRC	UPL1
	CLR     A
UPL1:   LD      (1,X),A
	CLR     (X)
	RET

;	SP!	( a -- )
;	Set data stack pointer.

        .ifne   WORDS_EXTRASTACK
	.dw	LINK
	LINK =	.
	.db	3
	.ascii	"sp!"
        .endif
SPSTO:
	LDW	X,(X)	;X = a
	RET	


;	CONTEXT ( -- a )     ( TOS STM8: -- Y,Z,N )
;	Start vocabulary search.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	7
	.ascii	"CONTEXT"
        .endif
CNTXT:
        .ifne  HAS_CPNVM
        CALL    COMPIQ
        JREQ    1$
        CALL    NVMQ
        JREQ    1$
        LD      A,#(RAMBASE+NVMCONTEXT)
        JRA     ASTOR
1$:
        .endif
	LD      A,#(RAMBASE+USRCONTEXT)
        JRA     ASTOR


;	CP	( -- a )     ( TOS STM8: -- Y,Z,N )
;	Point to top of dictionary.

        .ifne   WORDS_LINKCOMPC
	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"cp"
        .endif
CPP:
	LD      A,#(RAMBASE+USRCP)
        JRA     ASTOR

; System and user variables

;	BASE	( -- a )     ( TOS STM8: -- Y,Z,N )
;	Radix base for numeric I/O.

	.dw	LINK
	LINK =	.
	.db	4
	.ascii	"BASE"
BASE:
	LD      A,#(RAMBASE+USRBASE)
        JRA     ASTOR

;	tmp	( -- a )     ( TOS STM8: -- Y,Z,N )
;	A temporary storage.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"tmp"
	.endif
TEMP:
	LD      A,#(RAMBASE+USRTEMP)
        JRA     ASTOR

;	>IN	( -- a )     ( TOS STM8: -- Y,Z,N )
;	Hold parsing pointer.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	">IN"
        .endif
INN:
	LD      A,#(RAMBASE+USR_IN)
        JRA     ASTOR

;	#TIB	( -- a )     ( TOS STM8: -- Y,Z,N )
;	Count in terminal input buffer.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"#TIB"
	.endif
NTIB:
	LD      A,#(RAMBASE+USRNTIB)
        JRA     ASTOR

;	'eval	( -- a )     ( TOS STM8: -- Y,Z,N )
;	Execution vector of EVAL.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"'eval"
	.endif
TEVAL:
	LD      A,#(RAMBASE+USREVAL)
        JRA     ASTOR


;	HLD	( -- a )     ( TOS STM8: -- Y,Z,N )
;	Hold a pointer of output string.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"hld"
	.endif
HLD:
	LD      A,#(RAMBASE+USRHLD)
        JRA     ASTOR



;	LAST	( -- a )        ( TOS STM8: -- Y,Z,N )
;	Point to last name in dictionary.

	.ifne	WORDS_LINKCOMPC
	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"last"
        .endif
LAST:
	LD      A,#(RAMBASE+USRLAST)

;       ASTOR core ( -- n )     ( TOS STM8: -- Y,Z,N )
;       push A to stack
ASTOR:
        DECW    X
        LD      (X),A
        DECW    X
        CLR     (X)

        LDW     Y,X
        LDW     Y,(Y)
        RET


;	TIB	( -- a )     ( TOS STM8: -- Y,Z,N )
;	Return address of terminal input buffer.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"TIB"
        .endif
TIB:
	LDW     Y,#(TIBB)
        JP      YSTOR

        .ifne   HAS_OUTPUTS
;	OUT	( -- a )     ( TOS STM8: -- Y,Z,N )
;	Return address of OUTPUTS register

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"OUT"
OUTA:
	LD      A,#(OUTPUTS)
        JRA     ASTOR
        .endif

; Constants

;	BL	( -- 32 )     ( TOS STM8: -- Y,Z,N )
;	Return 32, blank character.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"BL"
BLANK:
	LD      A,#32
        JRA     ASTOR

;	0	( -- 0)     ( TOS STM8: -- Y,Z,N )
;	Return 0.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"0"
ZERO:
	CLR     A
        JRA     ASTOR

;	1	( -- 1)     ( TOS STM8: -- Y,Z,N )
;	Return 1.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"1"
ONE:
	LD      A,#1
        JRA     ASTOR

;	-1	( -- -1)     ( TOS STM8: -- Y,Z,N )
;	Return -1

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"-1"
MONE:
        CALLR   ONE
        JRA     NEGAT

        .ifne   HAS_BACKGROUND
;	TIM	( -- T)     ( TOS STM8: -- Y,Z,N )
;	Return TICKCNT as timer
	
        .dw	LINK

	LINK =	.
	.db	3
	.ascii	"TIM"
TIMM:
	LDW     Y,TICKCNT
        JP      YSTOR


;	BG	( -- a)     ( TOS STM8: -- Y,Z,N )
;	Return address of BGADDR vector
	
        .dw	LINK

	LINK =	.
	.db	2
	.ascii	"BG"
BGG:
	LD      A,#(BGADDR)
        JRA     ASTOR
        .endif


        .ifne   HAS_CPNVM
;	'PROMPT	( -- a)     ( TOS STM8: -- Y,Z,N )
;	Return address of PROMPT vector
	
	.ifne	WORDS_LINKINTER
        .dw	LINK

	LINK =	.
	.db	7
	.ascii	"'PROMPT"
TPROMPT:
	LD      A,#(USRPROMPT)
        JRA     ASTOR
        .endif


;       ( -- ) EMIT pace character for handshake in FILE mode 
PACEE:
        CALL    DOLITC
	.db     PACE      ; pace character for host handshake 
        JP      [USREMIT]


;	HAND	( -- )
;	set PROMPT vector to interactive mode
	
        .dw	LINK

	LINK =	.
	.db	4
	.ascii	"HAND"
HANDD:
	LDW     Y,#(DOTOK)
        LDW     USRPROMPT,Y
        RET

;	FILE	( -- )
;	set PROMPT vector to file transfer mode
	
        .dw	LINK

	LINK =	.
	.db	4
	.ascii	"FILE"
FILEE:
	LDW     Y,#(PACEE)
        LDW     USRPROMPT,Y
        RET
        .endif


; Common functions

;	NOT	( w -- w )     ( TOS STM8: -- Y,Z,N )
;	One's complement of TOS.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"NOT"
INVER:
	LDW     Y,X
	LDW     Y,(Y)
	CPLW    Y
	LDW     (X),Y
	RET

;	NEGATE	( n -- -n )     ( TOS STM8: -- Y,Z,N )
;	Two's complement of TOS.

	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"NEGATE"
NEGAT:
	LDW     Y,X
	LDW     Y,(Y)
	NEGW    Y
	LDW     (X),Y
	RET

;	?DUP	( w -- w w | 0 )   ( TOS STM8: -- Y,Z,N )
;	Dup tos if its not zero.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"?DUP"
QDUP:
	LDW     Y,X
	LDW     Y,(Y)
	JREQ	QDUP1
        DECW    X
        DECW    X
	LDW     (X),Y
QDUP1:	RET

;	ROT	( w1 w2 w3 -- w2 w3 w1 ) ( TOS STM8: -- Y,Z,N )
;	Rot 3rd item to top.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"ROT"
ROT:
        .ifne   SPEEDOVERSIZE
	LDW     Y,X
	LDW     Y,(4,Y)
        PUSHW   Y
	LDW     Y,X
	LDW     Y,(2,Y)
	PUSHW   Y
        LDW     Y,X
	LDW     Y,(Y)
	LDW     (2,X),Y
        POPW    Y 
	LDW     (4,X),Y
        POPW    Y
	LDW     (X),Y
	RET
        .else
        CALL    TOR
        CALL    SWAPP
        CALL    RFROM
        JP      SWAPP
        .endif

;	2DUP	( w1 w2 -- w1 w2 w1 w2 )
;	Duplicate top two items.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"2DUP"
DDUP:
	CALLR    1$
1$:        
        JP      OVER

;	DNEGATE ( d -- -d )     ( TOS STM8: -- Y,Z,N )
;	Two's complement of top double.

	.dw	LINK
	
	LINK =	.
	.db	7
	.ascii	"DNEGATE"
DNEGA:
	LDW     Y,X
	LDW     Y,(Y)
	CPLW    Y	
        PUSHW   Y
	LDW     Y,X
	LDW     Y,(2,Y)
	CPLW    Y
	INCW    Y
	LDW     (2,X),Y
	POPW    Y
	JRNC    DN1 
	INCW    Y
DN1:    LDW     (X),Y
	RET

;	ABS	( n -- n )      ( TOS STM8: -- Y,Z,N )
;	Return	absolute value of n.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"ABS"
ABSS:
	LDW     Y,X
	LDW     Y,(Y)
	JRPL	1$	;positive?
	NEGW	Y	;else negate 
	LDW     (X),Y
1$:     RET

;	=	( w w -- t )    ( TOS STM8: -- Y,Z,N )
;	Return true if top two are equal.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"="
EQUAL:
        .ifne   SPEEDOVERSIZE
	LD      A,#0x0FF	;true
	LDW     Y,X	;D = n2
	LDW     Y,(Y)
	LDW     YTEMP,Y
	INCW    X
        INCW    X
	LDW     Y,X
	LDW     Y,(Y)
	CPW     Y,YTEMP	;if n2 <> n1
	JREQ	EQ1
	CLR     A
EQ1:    LD      (X),A
	LD      (1,X),A
        LDW     Y,X
        LDW     Y,(Y)
        RET                            ; 24 cy
        .else
        CALL    XORR
        JRA     ZEQUAL                 ; 31 cy= (18+13) 
        .endif
        
        .ifne   WORDS_EXTRACORE
;	0=	( n -- t        ( TOS STM8: -- Y,Z,N ))
;	Return true if n is equal to 0
	.dw	LINK
	
        LINK =	.
	.db	(2)
	.ascii	"0="
        .endif
ZEQUAL:
	LDW     Y,X
        LDW     Y,(Y)
        JREQ    1$
        CLRW    Y
        JRT     2$        
1$:     CPLW    Y
2$:     LDW     (X),Y
        RET
        
;	U<	( u u -- t )    ( TOS STM8: -- Y,Z,N )
;	Unsigned compare of top two items.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"U<"
ULESS:
	CLR     A
        CALLR   YTEMPCMP
	JRUGE	1$
	CPL     A
1$:     LD      (X),A
	LD      (1,X),A
        LDW     Y,X
        LDW     Y,(Y)
	RET	

;	<	( n1 n2 -- t )
;	Signed compare of top two items.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"<"
LESS:
        .ifne   SPEEDOVERSIZE
	CLR     A
	LDW     Y,X
	LDW     Y,(Y)
	LDW     YTEMP,Y
        INCW    X
        INCW    X
	LDW     Y,X
	LDW     Y,(Y)
	CPW     Y,YTEMP	
	JRSGE	1$
	CPL     A
1$:     LD      (X),A
	LD      (1,X),A
        LDW     Y,X
        LDW     Y,(Y)
	RET                      ; 26 cy	
        .else
        CALL    SUBB             ; (29cy) 
        JP      ZLESS            ; 41 cy (12+29)
        .endif

;       YTEMPCMP       ( n n -- n )      ( TOS STM8: -- Y,Z,N )
;       Load (TOS) to YTEMP and (TOS-1) to Y, DROP, CMP to STM8 flags
YTEMPCMP:        
	LDW     Y,X
	LDW     Y,(Y)
	LDW     YTEMP,Y
        INCW    X
        INCW    X
	LDW     Y,X
	LDW     Y,(Y)
	CPW     Y,YTEMP
        RET

;	MAX	( n n -- n )    ( TOS STM8: -- Y,Z,N )
;	Return greater of two top items.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"MAX"
MAX:
        CALLR   YTEMPCMP
	JRSGT	MMEXIT
YTEMPTOS:
        LDW     Y,YTEMP
	LDW     (X),Y
MMEXIT: 
        RET

;	MIN	( n n -- n )    ( TOS STM8: -- Y,Z,N )
;	Return smaller of top two items.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"MIN"
MIN:
        CALLR   YTEMPCMP
	JRSLT	MMEXIT
        JRA     YTEMPTOS

;	WITHIN ( u ul uh -- t ) ( TOS STM8: -- Y,Z,N )
;	Return true if u is within
;	range of ul and uh. ( ul <= u < uh )

	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"WITHIN"
WITHI:
	CALL	OVER
	CALL	SUBB
	CALL	TOR
	CALL	SUBB
	CALL	RFROM
	JP	ULESS

; Divide

;	UM/MOD	( udl udh un -- ur uq )
;	Unsigned divide of a double by a
;	single. Return mod and quotient.

	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"UM/MOD"
UMMOD:
	PUSHW   X	; save stack pointer
        LDW     X,(X)	; un
	LDW     YTEMP,X ; save un
        LDW     Y,(1,SP); X stack pointer
	LDW     Y,(4,Y) ; Y=udl
        LDW     X,(1,SP); X
	LDW     X,(2,X)	; X=udh
	CPW     X,YTEMP
	JRULE   MMSM1   ; X is still on the R-stack
        POPW    X
        INCW    X               ; pop off 1 level
        INCW    X               ; ADDW   X,#2 
	LDW     Y,#0xFFFF
	LDW     (X),Y
	CLRW    Y
	LDW     (2,X),Y
	RET
MMSM1:
	LD      A,#17	; loop count
MMSM3:
	CPW     X,YTEMP	; compare udh to un
	JRULT   MMSM4	; can't subtract
	SUBW    X,YTEMP	; can subtract
MMSM4:
	CCF	        ; quotient bit
	RLCW    Y	; rotate into quotient
	RLCW    X	; rotate into remainder
	DEC     A	; repeat
	JRUGT   MMSM3
	SRAW    X
	LDW     YTEMP,X	; done, save remainder
        POPW    X
        INCW    X               ; drop 
        INCW    X               ; ADDW   X,#2 
	LDW     (X),Y
	LDW     Y,YTEMP	; save quotient
	LDW     (2,X),Y
	RET
	
;	M/MOD	( d n -- r q )
;	Signed floored divide of double by
;	single. Return mod and quotient.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"M/MOD"
MSMOD:
	CALL	DUPP
	CALL	ZLESS
	CALL	DUPP
	CALL	TOR
	CALL	QBRAN
	.dw	MMOD1
	CALL	NEGAT
	CALL	TOR
	CALL	DNEGA
	CALL	RFROM
MMOD1:	CALL	TOR
	CALL	DUPP
	CALL	ZLESS
	CALL	QBRAN
	.dw	MMOD2
	CALL	RAT
	CALL	PLUS
MMOD2:	CALL	RFROM
	CALL	UMMOD
	CALL	RFROM
	CALL	QBRAN
	.dw	MMOD3
	CALL	SWAPP
	CALL	NEGAT
	CALL	SWAPP
MMOD3:	RET

;	/MOD	( n n -- r q )
;	Signed divide. Return mod and quotient.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"/MOD"
SLMOD:
	CALL	OVER
	CALL	ZLESS
	CALL	SWAPP
	JP	MSMOD

;	MOD	( n n -- r )    ( TOS STM8: -- Y,Z,N )	
;	Signed divide. Return mod only.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"MOD"
MODD:
	CALL	SLMOD
	JP	DROP

;	/	( n n -- q )    ( TOS STM8: -- Y,Z,N )
;	Signed divide. Return quotient only.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"/"
SLASH:
	CALL	SLMOD
        ; fall through

;       NIP     ( n1 n2 -- n1 ) 

NIP:
	CALL	SWAPP
	JP	DROP

; Multiply

;	UM*	( u u -- ud )
;	Unsigned multiply. Return double product.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"UM*"
UMSTA:	                        ; stack have 4 bytes u1=a,b u2=c,d
	LD      A,(2,X)	; b
	LD      YL,A
	LD      A,(X)	; d
	MUL     Y,A
        PUSHW   Y       ; PROD1 temp storage
	LD      A,(3,X)	; a
	LD      YL,A
	LD      A,(X)	; d
	MUL     Y,A
        PUSHW   Y       ; PROD2 temp storage
	LD      A,(2,X)	; b
	LD      YL,A
	LD      A,(1,X)	; c
	MUL     Y,A
	PUSHW   Y       ; PROD3,CARRY temp storage 
        LD      A,(3,X)	; a
	LD      YL,A
	LD      A,(1,X)	; c
	MUL     Y,A	; least signifiant product
	CLR     A
	RRWA    Y
	LD      (3,X),A	; store least significant byte
	ADDW    Y,(1,SP); PROD3
	CLR     A
	ADC     A,#0	; save carry
        LD      (1,SP),A; CARRY
	ADDW    Y,(3,SP); PROD2
        LD      A,(1,SP); CARRY
        ADC     A,#0	; add 2nd carry
        LD      (1,SP),A; CARRY
        CLR     A
	RRWA    Y
	LD      (2,X),A	; 2nd product byte
	ADDW    Y,(5,SP); PROD1
	RRWA    Y
	LD      (1,X),A	; 3rd product byte
	RRWA    Y		; 4th product byte now in A
        ADC     A,(1,SP); CARRY
        LD      (X),A
        ADDW    SP,#6   ; drop temp storage
        RET

;	*	( n n -- n )    ( TOS STM8: -- Y,Z,N )
;	Signed multiply. Return single product.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"*"
STAR:
	CALL	UMSTA
	JP	DROP

;	M*	( n n -- d )
;	Signed multiply. Return double product.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"M*"
MSTAR:
	CALL	DDUP
	CALL	XORR
	CALL	ZLESS
	CALL	TOR
	CALL	ABSS
	CALL	SWAPP
	CALL	ABSS
	CALL	UMSTA
	CALL	RFROM
	CALL	QBRAN
	.dw	MSTA1
	CALL	DNEGA
MSTA1:	RET

;	*/MOD	( n1 n2 n3 -- r q )
;	Multiply n1 and n2, then divide
;	by n3. Return mod and quotient.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"*/MOD"
SSMOD:
	CALL	TOR
	CALL	MSTAR
	CALL	RFROM
	JP	MSMOD

;	*/	( n1 n2 n3 -- q )    ( TOS STM8: -- Y,Z,N )
;	Multiply n1 by n2, then divide
;	by n3. Return quotient only.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"*/"
STASL:
	CALL	SSMOD
	JP	NIP

; Miscellaneous

;	2+	( a -- a )      ( TOS STM8: -- Y,Z,N )
;	Add 2 to tos.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"2+"
CELLP:
	LDW     Y,X
	LDW     Y,(Y)
	ADDW    Y,#2
	LDW     (X),Y
	RET

;	2-	( a -- a )      ( TOS STM8: -- Y,Z,N )
;	Subtract 2 from tos.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"2-"
CELLM:
	LDW     Y,X
	LDW     Y,(Y)
	SUBW    Y,#2
	LDW     (X),Y
	RET

;	2*	( n -- n )      ( TOS STM8: -- Y,Z,N )
;	Multiply tos by 2.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"2*"
CELLS:
	LDW     Y,X
	LDW     Y,(Y)
	SLAW    Y
	LDW     (X),Y
	RET

;	1+	( n -- n )      ( TOS STM8: -- Y,Z,N )
;	Add 1 to tos.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"1+"
ONEP:
	LDW     Y,X
	LDW     Y,(Y)
	INCW    Y
	LDW     (X),Y
	RET

;	1-	( n -- n )      ( TOS STM8: -- Y,Z,N )
;	Subtract 1 from tos.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"1-"
ONEM:
	LDW     Y,X
	LDW     Y,(Y)
	DECW    Y
	LDW     (X),Y
	RET

;	2/	( n -- n )      ( TOS STM8: -- Y,Z,N )
;	Multiply tos by 2.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"2/"
TWOSL:
	LDW     Y,X
	LDW     Y,(Y)
	SRAW    Y
	LDW     (X),Y
	RET

;	>CHAR	( c -- c )      ( TOS STM8: -- A,Z,N )
;	Filter non-printing characters.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	">CHAR"
	.endif
TCHAR:
        LD      A,(1,X)
        AND     A,#0x7F
        CP      A,#0x7F
        JREQ    1$
        CP      A,#(' ')
        JRUGE   2$
1$:     LD      A,#('_')
2$:     LD      (1,X),A
        RET

;	DEPTH	( -- n )      ( TOS STM8: -- Y,Z,N )
;	Return	depth of data stack.

	.ifne   WORDS_EXTRASTACK
        .dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"DEPTH"
        .endif
DEPTH:
	LDW     Y,#SPP  ;save data stack ptr	
	LDW     YTEMP,X
	SUBW    Y,YTEMP	;#bytes = SP0 - X
	SRAW    Y	;D = #stack items
	DECW    Y
        DECW    X               ;SUBW	X,#2    
        DECW    X
	LDW     (X),Y	; if neg, underflow
	RET

;	PICK	( ... +n -- ... w )      ( TOS STM8: -- Y,Z,N )
;	Copy	nth stack item to tos.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"PICK"
PICK:
	LDW     Y,X	;D = n1
	LDW     Y,(Y)
	SLAW    Y
	LDW     YTEMP,X
	ADDW    Y,YTEMP
	LDW     Y,(Y)
	LDW     (X),Y
	RET

; Memory access

;	+!	( n a -- )      ( TOS STM8: -- Y,Z,N )
;	Add n tor contents at address a.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"+!"
PSTOR:
        .ifne   SPEEDOVERSIZE
        LDW     Y,X
        LDW     Y,(2,Y)
        LDW     YTEMP,Y
        LDW     Y,X
        LDW     Y,(Y)
        LDW     Y,(Y)
        ADDW    Y,YTEMP
        LDW     (2,X),Y
        JP      STORE
        .else 
	CALL	SWAPP
	CALL	OVER
	CALL	AT
	CALL	PLUS
	CALL	SWAPP
	JP	STORE
        .endif 

;	2!	( d a -- )      ( TOS STM8: -- Y,Z,N )
;	Store double integer to address a.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"2!"
DSTOR:
	CALL	SWAPP
	CALL	OVER
	CALL	STORE
	CALL	CELLP
	JP	STORE

;	2@	( a -- d )
;	Fetch double integer from address a.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"2@"
DAT:
	CALL	DUPP
	CALL	CELLP
	CALL	AT
	CALL	SWAPP
	JP	AT

;	COUNT	( b -- b +n )      ( TOS STM8: -- A,Z,N )
;	Return count byte of a string
;	and add 1 to byte address.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"COUNT"
        .endif
COUNT:
	CALL	DUPP
	CALL	ONEP
	CALL	SWAPP
	JP	CAT

;	HERE	( -- a )      ( TOS STM8: -- A,Z,N )
;	Return	top of	code dictionary.

	.ifeq	BAREBONES
	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"HERE"
        .endif
HERE:

        .ifne  HAS_CPNVM
        CALL    NVMQ            
        JREQ    1$              ; NVM: CP points to NVM, NVMCP points to RAM
        CALL    COMPIQ         
        JRNE    1$

        CALL    DOLIT
        .dw     NVMCP        ; 'eval in Interpreter mode: HERE returns pointer to RAM 
        JP	AT
        .endif
1$:
HERECP: 
        CALL	CPP
        JP	AT

;	PAD	( -- a )  ( TOS STM8: invalid )
;	Return address of text buffer
;	above code dictionary.

        .ifne   WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"PAD"
        .endif
PAD:
        .ifne   HAS_BACKGROUND
        ; hack for background task PAD
        ; create offset for PAD area
        PUSH	CC              ; Test interrupt level flags in CC 
        POP	A
        AND	A,#0x20
        JRNE    1$
       	CALL	DOLITC              
	.db	(PADBG+1)       ; dedicated memory for PAD in background task
        RET     
1$:
        .endif        
	CALL	HERE            ; regular PAD with offset to HERE
	CALL	DOLITC
	.db	PADOFFS
	JP	PLUS

;	@EXECUTE	( a -- )  ( TOS STM8: undefined )
;	Execute vector stored in address a.

	.ifne	WORDS_LINKCOMP
	.dw	LINK
	
	LINK =	.
	.db	8
	.ascii	"@EXECUTE"
        .endif        
ATEXE:
	CALL	AT              ; @ sets Z and N
        JRNE    1$
        JP      DROP
1$:	JP	EXECU	        ; execute if non-zero


;	CMOVE	( b1 b2 u -- )
;	Copy u bytes from b1 to b2.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"CMOVE"
CMOVE:
	CALL	TOR
        JRA     CMOV2
CMOV1:	CALL	TOR
	CALL	DUPP
	CALL	CAT
	CALL	RAT
	CALL	CSTOR
	CALL	ONEP
	CALL	RFROM
	CALL	ONEP
CMOV2:	CALL	DONXT
	.dw	CMOV1
	JP	DDROP

;	FILL	( b u c -- )
;	Fill u bytes of character c
;	to area beginning at b.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"FILL"
FILL:
	CALL	SWAPP
	CALL	TOR
	CALL	SWAPP
        JRA     FILL2
FILL1:	CALL	DDUP
	CALL	CSTOR
	CALL	ONEP
FILL2:	CALL	DONXT
	.dw	FILL1
	JP	DDROP

;	ERASE	( b u -- )
;	Erase u bytes beginning at b.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"ERASE"
ERASE:
	CALL	ZERO
	JP	FILL

;	PACK$	( b u a -- a )
;	Build a counted string with
;	u characters from b. Null fill.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"PACK$"
        .endif
PACKS:
	CALL	DUPP
	CALL	TOR	;strings only on cell boundary
	CALL	DDUP
	CALL	CSTOR
	CALL	ONEP ;save count
	CALL	SWAPP
	CALL	CMOVE
	CALL	RFROM
	RET

; Numeric output, single precision

;	DIGIT	( u -- c )      ( TOS STM8: -- Y,Z,N )
;	Convert digit u to a character.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"DIGIT"
        .endif
DIGIT:
	CALL	DOLITC
	.db     9
	CALL	OVER
	CALL	LESS
	CALL	DOLITC
	.db	7
	CALL	ANDD
	CALL	PLUS
	CALL	DOLITC
	.db	48	;'0'
	JP	PLUS

;	EXTRACT ( n base -- n c )   ( TOS STM8: -- Y,Z,N )
;	Extract least significant digit from n.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	7
	.ascii	"EXTRACT"
	.endif
EXTRC:
	CALL	ZERO
	CALL	SWAPP
	CALL	UMMOD
	CALL	SWAPP
	JP	DIGIT

;	<#	( -- )   ( TOS STM8: -- Y,Z,N )
;	Initiate	numeric output process.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"<#"
        .endif
BDIGS:
	CALL	PAD
	CALL	HLD
	JP	STORE

;	HOLD	( c -- )    ( TOS STM8: -- Y,Z,N )
;	Insert a character into output string.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"HOLD"
        .endif
HOLD:
        LDW     Y,USRHLD
        DECW    Y
        LDW     USRHLD,Y
        LD      A,(1,X)
        LD      (Y),A
        JP      DROP


;	#	( u -- u )    ( TOS STM8: -- Y,Z,N )
;	Extract one digit from u and
;	append digit to output string.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"#"
        .endif
DIG:
	CALL	BASE
	CALL	AT
	CALL	EXTRC
	JRA	HOLD

;	#S	( u -- 0 )
;	Convert u until all digits
;	are added to output string.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"#S"
        .endif
DIGS:
DIGS1:	CALLR	DIG
        JRNE    DIGS1
        RET

;	SIGN	( n -- )
;	Add a minus sign to
;	numeric output string.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"SIGN"
        .endif
SIGN:
	CALL	ZLESS
	CALL	QBRAN
	.dw	SIGN1
	CALL	DOLITC
	.db	45	;"-"
	JRA	HOLD
SIGN1:	RET

;	#>	( w -- b u )
;	Prepare output string.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"#>"
        .endif
EDIGS:
	CALL	DROP
	CALL	HLD
	CALL	AT
	CALL	PAD
	CALL	OVER
	JP	SUBB

;	str	( w -- b u )
;	Convert a signed integer
;	to a numeric string.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"str"
	.endif
STR:
	CALL	DUPP
	CALL	TOR
	CALL	ABSS
	CALL	BDIGS
	CALL	DIGS
	CALL	RFROM
	CALL	SIGN
	JP	EDIGS

;	HEX	( -- )
;	Use radix 16 as base for
;	numeric conversions.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"HEX"
HEX:
	CALL	DOLITC
	.db	16
	CALL	BASE
	JP	STORE

;	DECIMAL ( -- )
;	Use radix 10 as base
;	for numeric conversions.

	.dw	LINK
	
	LINK =	.
	.db	7
	.ascii	"DECIMAL"
DECIM:
	CALL	DOLITC
	.db	10
	CALL	BASE
	JP	STORE

; Numeric input, single precision

;	DIGIT?	( c base -- u t )
;	Convert a character to its numeric
;	value. A flag indicates success.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"DIGIT?"
	.endif
DIGTQ:
	CALL	TOR
	CALL	DOLITC
	.db	48	; "0"
	CALL	SUBB
	CALL	DOLITC
	.db	9
	CALL	OVER
	CALL	LESS
	CALL	QBRAN
	.dw	DGTQ1
	CALL	DOLITC
	.db	7
	CALL	SUBB
	CALL	DUPP
	CALL	DOLITC
	.db	10
	CALL	LESS
	CALL	ORR
DGTQ1:	CALL	DUPP
	CALL	RFROM
	JP	ULESS

;	NUMBER? ( a -- n T | a F )
;	Convert a number string to
;	integer. Push a flag on tos.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	7
	.ascii	"NUMBER?"
	.endif
NUMBQ:
	PUSH    USRBASE+1
        PUSH    #0                     ; sign flag

	CALL	ZERO
	CALL	OVER
	CALL	COUNT
NUMQ0:
	CALL	OVER
	CALL	CAT
        CALL    AFLAGS

        CP      A,#('$')
        JRNE    1$ 
	CALL	HEX
        JRA     NUMQSKIP
1$:
        .ifeq   BAREBONES
        CP      A,#('%')
        JRNE    2$
        MOV     USRBASE+1,#2
        JRA     NUMQSKIP
2$:        
        CP      A,#('&')
        JRNE    3$
        MOV     USRBASE+1,#10
	CALL	DECIM
        JRA     NUMQSKIP
3$:
        .endif
        CP      A,#('-')
        JRNE    NUMQ1
        POP     A
        PUSH    #0x80                   ; flag ?sign

NUMQSKIP:	
	CALL	SWAPP
	CALL	ONEP
	CALL	SWAPP
	CALL	ONEM
        JRNE    NUMQ0            ; check for more modifiers

NUMQ1:
	CALL	QDUP
	CALL	QBRAN
	.dw	NUMQ6
	CALL	ONEM  
	CALL	TOR             ; FOR
NUMQ2:	CALL	DUPP
	CALL	TOR
	CALL	CAT
	CALL	BASE
	CALL	AT
	CALL	DIGTQ
	CALL	QBRAN           ; WHILE ( no digit -> LEAVE )
	.dw	NUMLEAVE

	CALL	SWAPP
	CALL	BASE
	CALL	AT
	CALL	STAR
	CALL	PLUS
	CALL	RFROM
	CALL	ONEP

	CALL	DONXT
	.dw	NUMQ2

        CALLR   NUMDROP         ; drop b

        LD      A,(1,SP)        ; test sign flag 
        JRPL    NUMPLUS
	CALL	NEGAT                            
NUMPLUS:
        CALL	SWAPP                            
	JRA	NUMQ5                             
NUMLEAVE:                       ; LEAVE ( clean-up FOR .. NEXT )	
        ADDW    SP,#4           ; RFROM,RFROM,DDROP
        CALL	DDROP             
	CALL	ZERO
        ; fall through
NUMQ5:
        CALL	DUPP                             
        ; fall through
NUMQ6:	
        POP     A               ; sign flag
        POP     USRBASE+1       ; restore BASE
NUMDROP:
        JP      DROP


; Basic I/O

;	KEY	( -- c )
;	Wait for and return an
;	input character.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"KEY"
KEY:
KEY1:	CALL	[USRQKEY]
	CALL	QBRAN
	.dw	KEY1
	RET

;	NUF?	( -- t )
;	Return false if no input,
;	else pause and if CR return true.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"NUF?"
NUFQ:
        .ifne   HALF_DUPLEX
        ; slow EMIT down to free the line for RX 
        .ifne   HAS_BACKGROUND * HALF_DUPLEX 
        LD      A,TICKCNTL
        ADD     A,#3
1$:     CP      A,TICKCNTL
        JRNE    1$ 
        .else
        CLRW    Y            
1$:     DECW    Y             
        JRNE    1$
        .endif
        .endif
	CALL	[USRQKEY]
	CALL	DUPP
	CALL	QBRAN
	.dw	NUFQ1
	CALL	DDROP
	CALL	KEY
	CALL	DOLITC
	.db	CRR
	JP	EQUAL
NUFQ1:	RET

;	SPACE	( -- )
;	Send	blank character to
;	output device.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"SPACE"
SPACE:

	CALL	BLANK
	JP	[USREMIT]

;	SPACES	( +n -- )
;	Send n spaces to output device.

        .ifeq   BAREBONES
	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"SPACES"
SPACS:
	CALL	ZERO
	CALL	MAX
        .else
SPACS:
        .endif
	CALL	TOR
	JRA	CHAR2
CHAR1:	CALL	SPACE
CHAR2:	CALL	DONXT
	.dw	CHAR1
	RET

;	CR	( -- )
;	Output a carriage return
;	and a line feed.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"CR"
CR:
        .ifeq TERM_LINUX
	CALL	DOLITC
	.db	CRR
	CALL	[USREMIT]
        .endif
	CALL	DOLITC
	.db	LF
	JP	[USREMIT]


;	do$	( -- a )
;	Return	address of a compiled
;	string.

	.ifne	WORDS_LINKCOMPC
	.dw	LINK
	
	LINK =	.
	.db	(COMPO+3)
	.ascii	"do$"
	.endif
DOSTR:
	CALL	RFROM
	CALL	RAT
	CALL	RFROM
	CALL	COUNT
	CALL	PLUS
	CALL	TOR
	CALL	SWAPP
	CALL	TOR
	RET

;	$"|	( -- a )
;	Run time routine compiled by $".
;	Return address of a compiled string.

	.ifne	WORDS_LINKCOMPC
	.dw	LINK
	
	LINK =	.
	.db	(COMPO+3)
	.ascii	'$"|'
	.endif
STRQP:
	CALL	DOSTR
	RET

;	."|	( -- )
;	Run time routine of ." .
;	Output a compiled string.

	.ifne	WORDS_LINKCOMPC
	.dw	LINK
	
	LINK =	.
	.db	(COMPO+3)
	.ascii	'."|'
	.endif
DOTQP:
	CALL	DOSTR
	CALL	COUNT
	JRA	TYPES

        .ifeq   BAREBONES
;	.R	( n +n -- )
;	Display an integer in a field
;	of n columns, right justified.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	".R"
DOTR:
	CALL	TOR
	CALL	STR
        JRA     RFROMTYPES
        .endif

;	U.R	( u +n -- )
;	Display an unsigned integer
;	in n column, right justified.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"U.R"
UDOTR:
	CALL	TOR
	CALLR   BDEDIGS
RFROMTYPES:        
	CALL	RFROM
	CALL	OVER
	CALL	SUBB
	CALL	SPACS
	JRA	TYPES

;	TYPE	( b u -- )
;	Output u characters from b.

        .ifeq   BAREBONES
	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"TYPE"
        .endif
TYPES:
	CALL	TOR
	JRA	TYPE2
TYPE1:	CALL	DUPP
	CALL	CAT
	CALL	[USREMIT]
	CALL	ONEP
TYPE2:	
        CALL	DONXT
	.dw	TYPE1
	JP	DROP

;	U.	( u -- )
;	Display an unsigned integer
;	in free format.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"U."
UDOT:
	CALLR   BDEDIGS
        CALL	SPACE
	JRA	TYPES

;       UDOT helper routine
BDEDIGS:
	CALL	BDIGS
	CALL	DIGS
	JP	EDIGS

;	.	( w -- )
;	Display an integer in free
;	format, preceeded by a space.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"."
DOT:
        LD      A,USRBASE+1
	XOR     A,#10
        JREQ    1$
	JP	UDOT
1$:	CALL	STR
	CALL	SPACE
	JRA	TYPES

;	?	( a -- )
;	Display contents in memory cell.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"?"
QUEST:
	CALL	AT
	JRA     DOT


; Parsing

;       YFLAGS  ( n -- )       ( TOS STM8: -- Y,Z,N ) 
;       Consume TOS to CPU Y and Flags

YFLAGS:
        LDW     Y,X
        INCW    X
        INCW    X
        LDW     Y,(Y)
        RET

;       AFLAGS  ( c -- )       ( TOS STM8: -- A,Z,N ) 
;       Consume TOS to CPU A and Flags

AFLAGS:
        INCW    X
        LD      A,(X)
        INCW    X
        TNZ     A
        RET

;       parse helper routine
TEMPATBLEQ:        
	CALL	TEMP
	CALL	AT
	CALL	BLANK
	JP	EQUAL

;	parse	( b u c -- b u delta ; <string> )
;	Scan string delimited by c.
;	Return found string and its offset.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"pars"
	.endif
PARS:
	CALL	TEMP
	CALL	STORE
	CALL	OVER
	CALL	TOR
        JRNE    1$
        CALL	OVER
	CALL	RFROM
	JP	SUBB
1$:
	CALL	ONEM
        CALLR   TEMPATBLEQ
	CALL	QBRAN
	.dw	PARS3
	CALL	TOR
PARS1:	CALL	BLANK
	CALL	OVER
	CALL	CAT	;skip leading blanks ONLY
	CALL	SUBB
	CALLR   YFLAGS
        JRMI    PARS2    
	CALL	ONEP
	CALL	DONXT
	.dw	PARS1
	CALL	RFROM
	CALL	DROP
	CALL	ZERO
	JP	DUPP
PARS2:	CALL	RFROM
PARS3:	CALL	OVER
	CALL	SWAPP
	CALL	TOR
PARS4:	CALL	TEMP
	CALL	AT
	CALL	OVER
	CALL	CAT
	CALL	SUBB	;scan for delimiter
        CALLR   TEMPATBLEQ
	CALL	QBRAN
	.dw	PARS5
	CALL	ZLESS
PARS5:	CALL	QBRAN
	.dw	PARS6
	CALL	ONEP
	CALL	DONXT
	.dw	PARS4
	CALL	DUPP
	CALL	TOR
	JRA	PARS7
PARS6:	CALL	RFROM
	CALL	DROP
	CALL	DUPP
	CALL	ONEP
	CALL	TOR
PARS7:	CALL	OVER
	CALL	SUBB
	CALL	RFROM
	CALL	RFROM
	JP	SUBB



;	PARSE	( c -- b u ; <string> )
;	Scan input stream and return
;	counted string delimited by c.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"PARSE"
	.endif
PARSE:
	CALL	TOR
	CALL	TIB
	CALL	INN
	CALL	AT
	CALL	PLUS	;current input buffer pointer
	CALL	NTIB
	CALL	AT
	CALL	INN
	CALL	AT
	CALL	SUBB	;remaining count
	CALL	RFROM
	CALL	PARS
	CALL	INN
	JP	PSTOR

;	.(	( -- )
;	Output following string up to next ) .

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+2)
	.ascii	".("
DOTPR:
	CALL	DOLITC
	.db	41	; ")"
	CALL	PARSE
	JP	TYPES

;	(	( -- )
;	Ignore following string up to next ).
;	A comment.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+1)
	.ascii	"("
PAREN:
	CALL	DOLITC
	.db	41	; ")"
	CALL	PARSE
	JP	DDROP

;	\	( -- )
;	Ignore following text till
;	end of line.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+1)
	.ascii	"\\"
BKSLA:
	CALL	NTIB
	CALL	AT
	CALL	INN
	JP	STORE

;	WORD	( c -- a ; <string> )
;	Parse a word from input stream
;	and copy it to code dictionary.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"WORD"
	.endif
WORDD:
	CALL	PARSE
	CALL	HERE
	CALL	CELLP
	JP	PACKS

;	TOKEN	( -- a ; <string> )
;	Parse a word from input stream
;	and copy it to name dictionary.

	.ifne	WORDS_LINKCOMP
	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"TOKEN"
	.endif
TOKEN:
	CALL	BLANK
	JP	WORDD

; Dictionary search

;	NAME>	( na -- ca )
;	Return a code address given
;	a name address.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"NAME>"
        .endif
NAMET:
	CALL	COUNT
	CALL	DOLITC
	.db	31
	CALL	ANDD
	JP	PLUS

;	SAME?	( a a u -- a a f \ -0+ )
;	Compare u cells in two
;	strings. Return 0 if identical.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"SAME?"
	.endif
SAMEQ:
	CALL	ONEM
	CALL	TOR
	JRA	SAME2
SAME1:	CALL	OVER
	CALL	RAT
	CALL	PLUS
	CALL	CAT
        .ifne   CASEINSENSITIVE
        CALLR   CUPPER
        .endif
	CALL	OVER
	CALL	RAT
	CALL	PLUS
	CALL	CAT
        .ifne   CASEINSENSITIVE
        CALLR   CUPPER
        .endif
        CALL	SUBB
	CALL	QDUP
	CALL	QBRAN
	.dw	SAME2
	CALL	RFROM
	JP	DROP
SAME2:	CALL	DONXT
	.dw	SAME1
	JP	ZERO

        .ifne   CASEINSENSITIVE
;	CUPPER	( c -- c )
;       convert char to upper case

	.ifne	WORDS_LINKINTER
	.dw	LINK

	LINK =	.
	.db	4
	.ascii	"CUPPER"
	.endif
CUPPER:
        LD      A,(1,X)
        CP      A,#('a')
        JRULT   1$
        CP      A,#('z')
        JRUGT   1$
        AND     A,#0xDF
        LD      (1,X),A
1$:      RET
        .endif

;	NAME?	( a -- ca na | a F )
;	Search vocabularies for a string.

        .ifne   WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"NAME?"
        .endif
NAMEQ:
	CALL	CNTXT
	JRA	FIND

;	find	( a va -- ca na | a F )
;	Search vocabulary for string.
;	Return ca and na if succeeded.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"find"
	.endif
FIND:
	CALL	SWAPP
	CALL	DUPP
	CALL	CAT
	CALL	TEMP
	CALL	STORE
	CALL	DUPP
	CALL	AT
	CALL	TOR
	CALL	CELLP
	CALL	SWAPP
FIND1:	CALL	AT
	JREQ    FIND6
	CALL	DUPP
	CALL	AT
	CALL	DOLIT
	.dw	MASKK
	CALL	ANDD
        .ifne   CASEINSENSITIVE
        CALLR   CUPPER
        .endif
        CALL	RAT
        .ifne   CASEINSENSITIVE
        CALLR   CUPPER
        .endif
	CALL	XORR
	CALL	QBRAN
	.dw	FIND2
	CALL	CELLP
        CALL    MONE                   ; 0xFFFF
	JRA	FIND3
FIND2:	CALL	CELLP
	CALL	TEMP
	CALL	AT
	CALL	SAMEQ
FIND3:	JRA	FIND4
FIND6:	CALL	RFROM
	CALL	DROP
	CALL	SWAPP
	CALL	CELLM
	JP	SWAPP
FIND4:	CALL	QBRAN
	.dw	FIND5
	CALL	CELLM
	CALL	CELLM
	JRA	FIND1
FIND5:	CALL	RFROM
	CALL	DROP
	CALL	NIP
	CALL	CELLM
	CALL	DUPP
	CALL	NAMET
	JP	SWAPP

; Terminal response

;	^H	( bot eot cur -- bot eot cur )
;	Backup cursor by one character.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"^h"
	.endif
BKSP:
	CALL	TOR
	CALL	OVER
	CALL	RFROM
	CALL	SWAPP
	CALL	OVER
	CALL	XORR
	CALL	QBRAN
	.dw	BACK1
        .ifeq   HALF_DUPLEX
	CALL	DOLITC
	.db	BKSPP
	CALL	[USREMIT]
        .endif
	CALL	ONEM
	CALL	BLANK
	CALL	[USREMIT]
	CALL	DOLITC
	.db	BKSPP
	JP	[USREMIT]
BACK1:	RET

;	TAP	( bot eot cur c -- bot eot cur )
;	Accept and echo key stroke
;	and bump cursor.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"TAP"
	.endif
TAP:
        .ifeq   HALF_DUPLEX
	CALL	DUPP
	CALL	[USREMIT]
        .endif
	CALL	OVER
	CALL	CSTOR
	JP	ONEP

;	kTAP	( bot eot cur c -- bot eot cur )
;	Process a key stroke,
;	CR or backspace.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"kTAP"
	.endif
KTAP:
        LD      A,(1,X)
        CP     A,#CRR
        JREQ    KTAP2

	;CALL    YFLAGS
        ;CPW     Y,#BKSPP
        ;JREQ    KTAP1
        CALL	DOLITC
	.db	BKSPP
	CALL	XORR
	CALL	QBRAN
	.dw	KTAP1

	CALL	BLANK
	JP	TAP
KTAP1:	JP	BKSP
KTAP2:	CALL	DROP
	CALL	NIP
	JP	DUPP

;	accept	( b u -- b u )
;	Accept characters to input
;	buffer. Return with actual count.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"ACCEPT"
	.endif
ACCEP:
	CALL	OVER
	CALL	PLUS
	CALL	OVER
ACCP1:	CALL	DDUP
	CALL	XORR
	CALL	QBRAN
	.dw	ACCP4
	CALL	KEY
	CALL	DUPP
	CALL	BLANK
	CALL	DOLITC
	.db	127
	CALL	WITHI
	CALL	QBRAN
	.dw	ACCP2
	CALL	TAP
	JRA	ACCP3
ACCP2:	CALL	KTAP
ACCP3:	JRA	ACCP1
ACCP4:	CALL	DROP
	CALL	OVER
	JP	SUBB

;	QUERY	( -- )
;	Accept input stream to
;	terminal input buffer.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"QUERY"
	.endif
QUERY:
	CALL	TIB
	CALL	DOLITC
	.db	TIBLENGTH                      
	CALL	ACCEP                         
	CALL	NTIB
	CALL	STORE
	CALL	DROP
	CALL	ZERO
	CALL	INN
	JP	STORE

;	ABORT	( -- )
;	Reset data stack and
;	jump to QUIT.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"ABORT"
        .endif
ABORT:
	CALL	PRESE
	JP	QUIT

;	abort"	( f -- )
;	Run time routine of ABORT".
;	Abort with a message.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	(COMPO+5)
	.ascii	"aborq"
	.endif
ABORQ:
	CALL	QBRAN
	.dw	ABOR2	;text flag
	CALL	DOSTR
ABOR1:	CALL	SPACE
	CALL	COUNT
	CALL	TYPES
	CALL	DOLITC
	.db	63 ; "?"
	CALL	[USREMIT]
	CALL	CR
	JP	ABORT	;pass error string
ABOR2:	CALL	DOSTR
	JP	DROP

; The text interpreter

;	$INTERPRET	( a -- )
;	Interpret a word. If failed,
;	try to convert it to an integer.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	10
	.ascii	"$INTERPRET"
	.endif
INTER:
	CALL	NAMEQ
	CALL	QDUP	;?defined
	CALL	QBRAN
	.dw	INTE1
	CALL	AT
	CALL	DOLIT
	.dw	0x04000	; COMPO*256
	CALL	ANDD	;?compile only lexicon bits
	CALL	ABORQ
	.db	13
	.ascii	" compile only"
	JP	EXECU
INTE1:	CALL	NUMBQ	;convert a number
	CALL	QBRAN
	.dw	ABOR1
	RET

;	[	( -- )
;	Start	text interpreter.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+1)
	.ascii	"["
LBRAC:
	CALL	DOLIT
	.dw	INTER
	CALL	TEVAL
	JP	STORE


;	Test if 'EVAL points to $INTERPRETER
COMPIQ:
        LDW     Y,USREVAL
	CPW     Y,#(INTER)
        RET

;	.OK	( -- )
;	Display 'ok' while interpreting.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	".OK"
	.endif
DOTOK:
	CALLR	COMPIQ
	JRNE    DOTO1

        .ifne   BAREBONES
HI:
        .endif
	CALL	DOTQP
	.db	3
	.ascii	" ok"
DOTO1:	JP	CR

;	?STACK	( -- )
;	Abort if stack underflows.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"?STACK"
	.endif
QSTAC:
	CALL	DEPTH
	CALL	ZLESS	;check only for underflow
	CALL	ABORQ
	.db	11
	.ascii	" underflow "
	RET

;	EVAL	( -- )
;	Interpret	input stream.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"EVAL"
	.endif
EVAL:
EVAL1:	CALL	TOKEN
	CALL	DUPP
	CALL	CAT	        ; ?input stream empty
	CALL	QBRAN
	.dw	EVAL2
	CALL	TEVAL
	CALL	ATEXE
	CALL	QSTAC	        ; evaluate input, check stack
	JRA     EVAL1
EVAL2:	CALL	DROP
	JP	[USRPROMPT]     ; DOTOK or PACE

;	PRESET	( -- )
;	Reset data stack pointer and
;	terminal input buffer.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"PRESET"
	.endif
PRESE:
        CLRW    Y
        LDW     RAMBASE+USRNTIB,Y
	LDW	X,#SPP          ; initialize data stack
        RET

;	QUIT	( -- )
;	Reset return stack pointer
;	and start text interpreter.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"QUIT"
        .endif
QUIT:
	CALL	DOLIT
	.dw	RPP
	CALL	RPSTO	;reset return stack pointer
QUIT1:	CALL	LBRAC	;start interpretation
QUIT2:	CALL	QUERY	;get input
	CALL	EVAL
	JRA	QUIT2	;continue till error

; The compiler

;	'	( -- ca )
;	Search vocabularies for
;	next word in input stream.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"'"
TICK:
	CALL	TOKEN
	CALL	NAMEQ	;?defined
	CALL	QBRAN
	.dw	ABOR1
	RET	;yes, push code address

;	Allocate n bytes to code DICTIONARY.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"ALLOT"
ALLOT:
	CALL	CPP
	JP	PSTOR

;	,	( w -- )
;	Compile an integer into
;	code dictionary.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	","
COMMA:
	CALL	HERECP                    ; directly write to CP
	CALL	DUPP
	CALL	CELLP	;cell boundary
	CALL	CPP
	CALL	STORE
	JP	STORE

;	C,	( c -- )
;	Compile a byte into code dictionary.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"C,"
CCOMMA:
	CALL	HERECP                    ; directly write to CP
	CALL	DUPP
	CALL	ONEP
	CALL	CPP
	CALL	STORE
	JP	CSTOR

;	[COMPILE]	( -- ; <string> )
;	Compile next immediate
;	word into code dictionary.

	.ifne	WORDS_LINKCOMP
	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+9)
	.ascii	"[COMPILE]"
        .endif
BCOMP:
	CALL	TICK
	JP	JSRC

;	COMPILE ( -- )
;	Compile next jsr in
;	colon list to code dictionary.

	.ifne	WORDS_LINKCOMP
	.dw	LINK
	
	LINK =	.
	.db	(COMPO+7)
	.ascii	"COMPILE"
	.endif
COMPI:
	CALL	RFROM
	CALL	ONEP
	CALL	DUPP
	CALL	AT
	CALL	JSRC	        ; compile subroutine
	CALL	CELLP
	CALL	TOR       ; this was a JP - a serious bug that took a while to find
        RET

;	LITERAL ( w -- )
;	Compile tos to dictionary
;	as an integer literal.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+7)
	.ascii	"LITERAL"
LITER:
	CALL	COMPI
	CALL	DOLIT
	JP	COMMA

;	$,"	( -- )
;	Compile a literal string
;	up to next " .

	.ifne	WORDS_LINKCOMP
	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	'$,"'
        .endif
STRCQ:
	CALL	DOLITC
	.db	34	; "
	CALL	PARSE
	CALL	HERECP
	CALL	PACKS	;string to code dictionary
CNTPCPPSTORE:
	CALL	COUNT
	CALL	PLUS	;calculate aligned end of string
	CALL	CPP
	JP	STORE

; Structures

;	FOR	( -- a )
;	Start a FOR-NEXT loop
;	structure in a colon definition.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+3)
	.ascii	"FOR"
FOR:
	CALL	COMPI
	CALL	TOR
	JP	HERE

;	NEXT	( a -- )
;	Terminate a FOR-NEXT loop.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+4)
	.ascii	"NEXT"
NEXT:
	CALL	COMPI
	CALL	DONXT
	JP	COMMA

        .ifne   HAS_DOLOOP 
;	DO	( -- a )
;	Start a DO LOOP loop
;	structure in a colon definition.

        .dw	LINK

        LINK =	.
        .db	(IMEDD+2)
        .ascii	"DO"
DOO:
	CALL	COMPI
	CALL	SWAPP
	CALL	COMPI
	CALL	TOR
	JRA	FOR

;	LOOP	( a -- )
;	Terminate a DO-LOOP loop.

	.dw	LINK

	LINK =	.
	.db	(IMEDD+4)
	.ascii	"LOOP"
LOOP:
        CALL	COMPI
        CALL    ONE
        JRA     PLOOP

;	+LOOP	( a +n -- )
;	Terminate a DO - +LOOP loop.

	.dw	LINK

	LINK =	.
	.db	(IMEDD+5)
	.ascii	"+LOOP"
PLOOP:        
        CALL	COMPI
        CALL	DOPLOOP
        JP	COMMA
        .endif

;	BEGIN	( -- a )
;	Start an infinite or
;	indefinite loop structure.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+5)
	.ascii	"BEGIN"
BEGIN:
	JP	HERE

;	UNTIL	( a -- )
;	Terminate a BEGIN-UNTIL
;	indefinite loop structure.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+5)
	.ascii	"UNTIL"
UNTIL:
	CALL	COMPI
	CALL	QBRAN
	JP	COMMA

;	AGAIN	( a -- )
;	Terminate a BEGIN-AGAIN
;	infinite loop structure.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+5)
	.ascii	"AGAIN"
AGAIN:
	CALL    CCOMMALIT
        .db     BRAN_OPC
        JP	COMMA	
        
;	IF	( -- A )
;	Begin a conditional branch.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+2)
	.ascii	"IF"
IFF:
	CALL	COMPI
	CALL	QBRAN
	CALL	HERE
	CALL	ZERO
	JP	COMMA

;	THEN	( A -- )
;	Terminate a conditional branch structure.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+4)
	.ascii	"THEN"
THENN:
	CALL	HERE
	CALL	SWAPP
	JP	STORE

;	ELSE	( A -- A )
;	Start the false clause in an IF-ELSE-THEN structure.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+4)
	.ascii	"ELSE"
ELSEE:
	CALLR   AHEAD
        CALL	SWAPP
	CALL	HERE
	CALL	SWAPP
	JP	STORE

;	AHEAD	( -- A )
;	Compile a forward branch instruction.

	.ifne	WORDS_LINKCOMP
	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+5)
	.ascii	"AHEAD"
        .endif
AHEAD:
	CALL    CCOMMALIT
        .db     BRAN_OPC
	CALL	HERE
	CALL	ZERO
        JP	COMMA



;	WHILE	( a -- A a )
;	Conditional branch out of a BEGIN-WHILE-REPEAT loop.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+5)
	.ascii	"WHILE"
WHILE:
        CALL    IFF
	JP	SWAPP

;	REPEAT	( A a -- )
;	Terminate a BEGIN-WHILE-REPEAT indefinite loop.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+6)
	.ascii	"REPEAT"
REPEA:
	CALLR   AGAIN
	CALL	HERE
	CALL	SWAPP
	JP	STORE

;	AFT	( a -- a A )
;	Jump to THEN in a FOR-AFT-THEN-NEXT loop the first time through.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+3)
	.ascii	"AFT"
AFT:
	CALL	DROP
	CALL	AHEAD
	CALL	HERE
	JP	SWAPP

;	ABORT"	( -- ; <string> )
;	Conditional abort with an error message.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+6)
	.ascii	"ABORT"
	.db	'"
ABRTQ:
	CALL	COMPI
	CALL	ABORQ
	JP	STRCQ

;	$"	( -- ; <string> )
;	Compile an inline string literal.

	.ifne	WORDS_LINKCOMP
	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+2)
	.ascii	'$"'
        .endif
STRQ:
	CALL	COMPI
	CALL	STRQP
	JP	STRCQ

;	."	( -- ; <string> )
;	Compile an inline string literal to be typed out at run time.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+2)
	.ascii	'."'
DOTQ:
	CALL	COMPI
	CALL	DOTQP
	JP	STRCQ

; Name compiler

;	?UNIQUE ( a -- a )
;	Display a warning message
;	if word already exists.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	7
	.ascii	"?UNIQUE"
	.endif
UNIQU:
	CALL	DUPP
	CALL	NAMEQ	;?name exists
	CALL	QBRAN
	.dw	UNIQ1
	CALL	DOTQP	;redef are OK
	.db	7
	.ascii	" reDef "	
	CALL	OVER
	CALL	COUNT
	CALL	TYPES	;just in case
UNIQ1:	JP	DROP

;	$,n	( na -- )
;	Build a new dictionary name
;	using string at na.

	.ifne	WORDS_LINKCOMPC
	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"$,n"
	.endif
SNAME:
	CALL	DUPP
	CALL	CAT	;?null input
	CALL	QBRAN
	.dw	PNAM1
	CALL	UNIQU	;?redefinition
	CALL	DUPP
        CALL    CNTPCPPSTORE
        CALL	DUPP
	CALL	LAST
	CALL	STORE	;save na for vocabulary link
	CALL	CELLM	;link address
	CALL	CNTXT
	CALL	AT
	CALL	SWAPP
	CALL	STORE
	RET	;save code pointer
PNAM1:	CALL	STRQP
	.db	5
	.ascii	" name" ;null input
	JP	ABOR1

; FORTH compiler

;	$COMPILE	( a -- )
;	Compile next word to
;	dictionary as a token or literal.

	.ifne	WORDS_LINKINTER
	.dw	LINK
	
	LINK =	.
	.db	8
	.ascii	"$COMPILE"
	.endif
SCOMP:
	CALL	NAMEQ
	CALL	QDUP	;?defined
	CALL	QBRAN
	.dw	SCOM2
	CALL	AT
	CALL	DOLIT
	.dw	0x08000	;	IMEDD*256
	CALL	ANDD	;?immediate
	CALL	QBRAN
	.dw	SCOM1
	JP	EXECU
SCOM1:	JP	JSRC
SCOM2:	CALL	NUMBQ	;try to convert to number
	CALL	QBRAN
	.dw	ABOR1
	JP	LITER

;	OVERT	( -- )
;	Link a new word into vocabulary.

	.ifne	WORDS_LINKCOMPC
	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"OVERT"
	.endif
OVERT:
	CALL	LAST
	CALL	AT

        .ifne   HAS_CPNVM
        CALL    DUPP
        CALL    NVMADRQ         ; does USRLAST point to NVM?
        CALL    QBRAN
        .dw     1$
        CALL    DUPP             
        CALL    DOLITC
        .db     NVMCONTEXT
        CALL    STORE           ; update NVMCONTEXT
        CALL    DOLITC
        .db     CTOP            ; is there any vocabulary in RAM?
        CALL    DUPP
        CALL    AT
        CALL    QBRAN
        .dw     2$
        JP      STORE           ; link dictionary in RAM
2$:
        CALL    DROP
1$:
        CALL    DOLITC
        .db     USRCONTEXT            
        JP      STORE           ; or update USRCONTEXT
        .else
	CALL	CNTXT
	JP	STORE
        .endif

;	;	( -- )
;	Terminate a colon definition.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+COMPO+1)
	.ascii	";"
SEMIS:
        CALL    CCOMMALIT
        .db     EXIT_OPC
	CALL	LBRAC
	JP	OVERT

;	]	( -- )
;	Start compiling words in
;	input stream.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"]"
RBRAC:
	CALL	DOLIT
	.dw	SCOMP
	CALL	TEVAL
	JP	STORE

;	CALL,	( ca -- )
;	Compile a subroutine call.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"CALL,"
JSRC:
	CALL	CCOMMALIT
	.db	CALL_OPC	 ; opcode CALL
	JP	COMMA

;	:	( -- ; <string> )
;	Start a new colon definition
;	using next word as its name.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	":"
COLON:
        .ifne  HAS_CPNVM
	CALL	RBRAC   ; directly do "]" to indicate to HERE that we're no longer interpreting
	CALL	TOKEN
	JP	SNAME
        .else
	CALL	TOKEN
	CALL	SNAME
       	JP	RBRAC
        .endif

;	IMMEDIATE	( -- )
;	Make last compiled word
;	an immediate word.

	.dw	LINK
	
	LINK =	.
	.db	9
	.ascii	"IMMEDIATE"
IMMED:
	CALL	DOLIT
	.dw	0x08000	;	IMEDD*256
	CALL	LAST
	CALL	AT
	CALL	AT
	CALL	ORR
	CALL	LAST
	CALL	AT
	JP	STORE

; Defining words

;	CREATE	( -- ; <string> )
;	Compile a new array
;	without allocating space.

	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"CREATE"
CREAT:
        .ifne   HAS_CPNVM
        CALL    TEVAL
        CALL    AT
        CALL    TOR             ; save TEVAL
        CALL    RBRAC           ; "]" make HERE return CP even in INTERPRETER mode
        .endif

	CALL	TOKEN
	CALL	SNAME
        CALL    OVERT

        .ifne   HAS_CPNVM
        CALL    RFROM
        CALL    TEVAL           ; restore TEVAL
        CALL    STORE           ; from here on ',', 'C,', '$,"' and 'ALLOT' write to CP
        .endif

	CALL	COMPI
	CALL	DOVAR
	RET


        .ifne   HAS_DOES

;	DOES> 	( -- )
;	Define action of defining words

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+5)
	.ascii	"DOES>"
DOESS:
        CALL    COMPI
        CALL    DODOES          ; 3 CALL dodoes>
        CALL    HERECP
        CALL    DOLITC
        .db     9
        CALL    PLUS
        CALL    LITER           ; 3 CALL doLit + 2 (HERECP+9)
        CALL    COMPI
        CALL    COMMA           ; 3 CALL COMMA
        CALL    CCOMMALIT
        .db     EXIT_OPC        ; 1 RET (EXIT)
        RET 

;	dodoes	( -- )
;	link action to words created by defining words

	.ifne	WORDS_LINKCOMPC
	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"dodoes"
        .endif
DODOES:
        CALL    LAST                   ; ( link field of current word )
        CALL    AT
        CALL    NAMET                  ; ' ( 'last  )
        CALL    DOLITC
        .db     BRAN_OPC               ; ' JP
        CALL    OVER                   ; ' JP '
        CALL    CSTOR                  ; ' \ CALL <- JP
        CALL    HERECP                 ; ' HERE
        CALL    OVER                   ; ' HERE '
        CALL    ONEP                   ; ' HERE ('+1)
        CALL    STORE                  ; ' \ CALL DOVAR <- JP HERE
        CALL    COMPI
        CALL    DOLIT                  ; ' \ HERE <- DOLIT
        CALL    DOLITC
        .db     3                      ; ' 3
        CALL    PLUS                   ; ('+3)
        CALL    COMMA                  ; \ HERE <- DOLIT <-('+3)
        CALL    CCOMMALIT
        .db     BRAN_OPC               ; \ HERE <- DOLIT <- ('+3) <- branch
        RET
        .endif 

        .ifeq   BAREBONES
;	VARIABLE	( -- ; <string> )
;	Compile a new variable
;	initialized to 0.

	.dw	LINK
	
	LINK =	.
	.db	8
	.ascii	"VARIABLE"
VARIA:
	CALL	CREAT
	CALL	ZERO
	JP	COMMA
        .endif

; Tools

;	_TYPE	( b u -- )
;	Display a string. Filter
;	non-printing characters.

	.ifne	WORDS_LINKCHAR
	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"_TYPE"
        .endif
UTYPE:
	CALL	TOR	;start count down loop
	JRA	UTYP2	;skip first pass
UTYP1:	CALL	DUPP
	CALL	CAT
	CALL	TCHAR
	CALL	[USREMIT]	;display only printable
	CALL	ONEP	;increment address
UTYP2:	CALL	DONXT
	.dw	UTYP1	;loop till done
	JP	DROP

;	dm+	( a u -- a )
;	Dump u bytes from ,
;	leaving a+u on	stack.

	.ifne	WORDS_LINKMISC
	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"dm+"
	.endif
DUMPP:
	CALL	OVER
	CALL	DOLITC
	.db	4
	CALL	UDOTR	;display address
	CALL	SPACE
	CALL	TOR	;start count down loop
	JRA	PDUM2	;skip first pass
PDUM1:	CALL	DUPP
	CALL	CAT
	CALL	DOLITC
	.db	3
	CALL	UDOTR	;display numeric data
	CALL	ONEP	;increment address
PDUM2:	CALL	DONXT
	.dw	PDUM1	;loop till done
	RET

;	DUMP	( a u -- )
;	Dump u bytes from a,
;	in a formatted manner.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"DUMP"
DUMP:
	CALL	BASE
	CALL	AT
	CALL	TOR
	CALL	HEX	;save radix, set hex
	CALL	DOLITC
	.db	16
	CALL	SLASH	;change count to lines
	CALL	TOR	;start count down loop
DUMP1:	CALL	CR
	CALL	DOLITC
	.db	16
	CALL	DDUP
	CALL	DUMPP	;display numeric
	CALL	ROT
	CALL	ROT
	CALL	SPACE
	CALL	SPACE
	CALL	UTYPE	;display printable characters
	CALL	DONXT
	.dw	DUMP1	;loop till done
DUMP3:	CALL	DROP
	CALL	RFROM
	CALL	BASE
	JP	STORE	;restore radix

;	.S	( ... -- ... )
;	Display	contents of stack.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	".S"
DOTS:
	CALL	CR
	CALL	DEPTH	;stack depth
	CALL	TOR	;start count down loop
	JRA	DOTS2	;skip first pass
DOTS1:	CALL	RAT
	CALL    ONEP
	CALL	PICK
	CALL	DOT	;index stack, display contents
DOTS2:	CALL	DONXT
	.dw	DOTS1	;loop till done
	CALL	DOTQP
	.db	5
	.ascii	" <sp "
	RET

;	.ID	( na -- )
;	Display	name at address.

	.ifne	WORDS_LINKMISC
	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	".ID"
        .endif
DOTID:
	CALL	QDUP	;if zero no name
	CALL	QBRAN
	.dw	DOTI1
	CALL	COUNT
	CALL	DOLITC
	.db	0x01F
	CALL	ANDD	;mask lexicon bits
	JP	UTYPE
DOTI1:	CALL	DOTQP
	.db	9
	.ascii	" (noName)"
	RET

        .ifne   WORDS_EXTRADEBUG
;	>NAME	( ca -- na | F )
;	Convert code address
;	to a name address.

	.ifne	WORDS_LINKMISC
	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	">NAME"
        .endif
TNAME:
	CALL	CNTXT	;vocabulary link
TNAM2:	CALL	AT
	CALL	DUPP	;?last word in a vocabulary
	CALL	QBRAN
	.dw	TNAM4
	CALL	DDUP
	CALL	NAMET
	CALL	XORR	;compare
	CALL	QBRAN
	.dw	TNAM3
	CALL	CELLM	;continue with next word
	JRA	TNAM2
TNAM3:	JP	NIP
TNAM4:	CALL	DDROP
	JP	ZERO

;	SEE	( -- ; <string> )
;	A simple decompiler.
;	Updated for byte machines.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"SEE"
SEE:
	CALL	TICK	;starting address
	CALL	CR
	CALL	ONEM
SEE1:
	CALL	CELLP   ;Fixed tg9541
	CALL	DUPP
	CALL	AT
	CALL	DUPP	;?does it contain a zero
	CALL	QBRAN
	.dw	SEE2
	CALL	TNAME	;?is it a name
SEE2:	CALL	QDUP	;name address or zero
	CALL	QBRAN
	.dw	SEE3
	CALL	SPACE
	CALL	DOTID	;display name
	CALL	ONEP
	JRA	SEE4
SEE3:	CALL	DUPP
	CALL	CAT
	CALL	UDOT	;display number
SEE4:	CALL	NUFQ	;user control
	CALL	QBRAN
	.dw	SEE1
	JP	DROP
        .endif

;	WORDS	( -- )
;	Display names in vocabulary.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"WORDS"
WORDS:
	CALL	CR
	CALL	CNTXT	        ; only in context
WORS1:	CALL	AT              ; @ sets Z and N
        JREQ    1$              ; ?at end of list
	CALL	DUPP
	CALL	SPACE
	CALL	DOTID	        ; display a name
	CALL	CELLM
        JRA     WORS1
1$:	CALL	DROP
	RET

	
;	
;===============================================================

        .ifne   WORDS_EXTRAMEM
;	BSR ( t a b -- )
;	Set/Reset bit #b (0..7) at address a to bool t
;       Note: creates/executes BSER/BRES + RET code on Data Stack
	.dw	LINK
	
        LINK =	.
	.db	(3)
	.ascii	"BSR"
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
        CALL    (Y)             ; call code to avoid "use after free"
        ADDW    X,#6            
        RET


;       2C!  ( n b -- )
;       Store word C-wise to 16 bit HW registers "MSB first" 
	.dw	LINK
	
        LINK =	.
	.db	(3)
	.ascii	"2C!"
DCSTOR:        
        CALL    DDUP
        LD      A,(2,X)
        LD      (3,X),A
        CALL    CSTOR
        CALL    ONEP
        CALL    CSTOR
        RET


;       2C@  ( a -- n )
;       Fetch word C-wise from 16 bit HW config. registers "MSB first" 
	.dw	LINK
        
        LINK =  .
	.db	(3)
	.ascii	"2C@"
DCAT:        
        CALL    DUPP
        CALL    CAT
        CALL    SWAPP
        CALL    ONEP
        CALL    CAT
        LD      A,(3,X)
        LD      (2,X),A
        LD      A,(1,X)
        LD      (3,X),A
        CALL    DROP
        RET
        .endif


        .ifne   WORDS_EXTRAEEPR
;       ULOCK  ( -- )
;       Unlock EEPROM (STM8S)
	.dw	LINK
        
        LINK =  .
	.db	(5)
	.ascii	"ULOCK"
ULOCK:
        MOV     FLASH_DUKR,#0xAE
        MOV     FLASH_DUKR,#0x56
1$:     BTJF    FLASH_IAPSR,#3,1$    ; PM0051 4.1 requires polling bit3=1 before writing
        RET


;       LOCK  ( -- )
;       Lock EEPROM (STM8S)
	.dw	LINK
        
        LINK =  .
	.db	(4)
	.ascii	"LOCK"
LOCK:
        BRES    FLASH_IAPSR,#3
        RET
        .endif

         
        .ifne   HAS_CPNVM 
;       ULOCKF  ( -- )
;       Unlock Flash (STM8S)
        .ifne   WORDS_LINKMISC
	.dw	LINK
        
        LINK =  .
	.db	(6)
	.ascii	"ULOCKF"
        .endif
UNLOCK_FLASH:
        MOV     FLASH_PUKR,#0x56
        MOV     FLASH_PUKR,#0xAE
1$:     BTJF    FLASH_IAPSR,#1,1$    ; PM0051 4.1 requires polling bit1=1 before writing
        RET


;       LOCKF  ( -- )
;       Lock Flash (STM8S)
        .ifne   WORDS_LINKMISC
	.dw	LINK
        
        LINK =  .
	.db	(5)
	.ascii	"LOCKF"
        .endif
LOCK_FLASH:
        BRES    FLASH_IAPSR,#1
        RET
        .endif

         
;-----------------------------------------------
        .ifne   HAS_KEYS

;	?KEYB	( -- c T | F )  ( TOS STM8: -- Y,Z,N )
;	Return keyboard char and true, or false if no key pressed.
	.dw	LINK
	LINK =	.
	.db	5
	.ascii	"?KEYB"
QKEYB:
        CALLR   BKEY
        CALL    AFLAGS
        JRNE    KEYBPRESS
        ; Bit7: flag press + 100*5ms hold before repetition
        MOV     KEYREPET,#(0x80 + 100)
        JRA     NOKEYB
KEYBPRESS:
        ADD     A,#0x40         ; bit values 1,2,4 to 'A','B','D'
        BTJF    KEYREPET,#7,KEYBHOLD
        BRES    KEYREPET,#7
        JRA     ATOKEYB
KEYBHOLD:
        DEC     KEYREPET
        JRNE    NOKEYB
        MOV     KEYREPET,#30    ; repetition time: n*5ms
ATOKEYB:
        JP      ATOKEY          ; push char and flag true
NOKEYB:
        JP      ZERO            ; push flag false

;       BKEY  ( -- n )     ( TOS STM8: -- A,Z,N )
;       Read board key state as a bitfield
	.dw	LINK
        
        LINK =  .
	.db	(4)
	.ascii	"BKEY"
BKEY:   
        .ifne   BOARD_W1209
        ; Keys "set" (1), "+" (2), and "-" (4) on PC.3:5
        LD      A,PC_IDR
        SLA     A
        SWAP    A
        CPL     A
        AND     A,#0x07
        .else
        .ifne   BOARD_C0135
        ; Key "S2" port PA3 (inverted)
        LD      A,PA_IDR
        SLA     A
        SWAP    A
        CPL     A
        AND     A,#0x01
        .else
        CLR     A
        .endif
        .endif
        JP      ASTOR
       .endif


        .ifne   HAS_LED7SEG

;       7-seg LED patterns, "70s chique"
PAT7SM9:   
        .db     0x00, 0x40, 0x80, 0x52 ; ,,-,.,/ (',' as blank)
        .db     0x3F, 0x06, 0x5B, 0x4F ; 0,1,2,3
        .db     0x66, 0x6D, 0x7D, 0x07 ; 4,5,6,7
        .db     0x7F, 0x6F             ; 8,9 
PAT7SAZ:
        .db           0x77, 0x7C, 0x39 ;   A,B,C
        .db     0x5E, 0x79, 0x71, 0x3D ; D,E,F,G
        .db     0x74, 0x30, 0x1E, 0x7A ; H,I,J,K
        .db     0x38, 0x55, 0x54, 0x5C ; L,M,N,O
        .db     0x73, 0x67, 0x50, 0x6D ; P,Q,R,S
        .db     0x78, 0x3E, 0x1C, 0x1D ; T,U,V,W
        .db     0x76, 0x6E, 0x6D       ; X,Y,Z

;       E7S  ( c -- )
;       Convert char to 7-seg LED pattern, and insert it in display buffer
	.dw	LINK
        
        LINK =  .
	.db	(3)
	.ascii	"E7S"
EMIT7S: 
        LD      A,(1,X)         ; c to A

        CP      A,#32
        JRNE    1$
        CLRW    Y 
        LDW     LED7MSB,Y
        LDW     LED7LSB,Y
        JRA     E7END

1$:     CP      A,#'.'
        JREQ    E7DOT
        CP      A,#','
        JRMI    E7END
        CP      A,#'z'
        JRPL    E7END
        CP      A,#'A'
        JRUGE   E7ALPH

        ; '-'--'9' (and '@') 
        SUB     A,#','
        LD      (1,X),A
        CALL    DOLIT
        .dw     PAT7SM9
        JRA     E7LOOKA 
E7ALPH:
        ; 'A'--'z'
        AND	A,#0x5F         ; convert to uppercase
        SUB     A,#'A'
        LD      (1,X),A
        CALL    DOLIT
        .dw     PAT7SAZ
E7LOOKA:
        CALL    PLUS
        CALL    CAT
        JP      PUT7S

E7DOT:
        LD      A,#0x80         ; 7-seg P (dot) 
        OR      A,LED7LSB+1
        LD      LED7LSB+1,A
        JRA     E7END
        
E7END:
        JP      DROP


;       P7S  ( c -- )
;       Insert 7-seg pattern at left side of LED display buffer, rotate buffer left
	.dw	LINK
        
        LINK =  .
	.db	(3)
	.ascii	"P7S"
PUT7S:       
        LDW     Y,X             ; w to AX
        LD      A,(1,Y)
PUT7SA:
        LDW     Y,LED7LSB
        RLWA    Y
        LDW     LED7LSB,Y
        LDW     Y,LED7MSB
        RLWA    Y
        LDW     LED7MSB,Y
        INCW    X               ; ADDW   X,#2 
        INCW    X
        RET
        .endif

        .ifne   HAS_OUTPUTS
;       OUT!  ( c -- )
;       Put c to board outputs, storing a copy in OUTPUTS  
	.dw	LINK
        
        LINK =  .
	.db	(4)
	.ascii	"OUT!"
OUTSTOR:
        LD      A,(1,X)
        LD      OUTPUTS,A
        INCW    X               ; ADDW   X,#2 
        INCW    X
        .ifne   BOARD_W1209
        RRC     A
        BCCM    PA_ODR,#3       ; W1209 relay
        .endif
        .ifne   BOARD_C0135
        XOR     A,#0x0F         ; C0135 Relay-4 Board 
        RRC     A
        BCCM    PB_ODR,#4       ; Relay1
        RRC     A
        BCCM    PC_ODR,#3       ; Relay2
        RRC     A
        BCCM    PC_ODR,#4       ; Relay3
        RRC     A
        BCCM    PC_ODR,#5       ; Relay4
        RRC     A
        BCCM    PD_ODR,#4       ; LED
        .endif
        .ifne   BOARD_MINDEV
        RRC     A
        CCF
        BCCM    PB_ODR,#5       ; PB5 LED
        .endif
        RET       
        .endif

        .ifne   HAS_ADC
;       ADC!  ( c -- )
;       Init ADC, select channel for conversion 
	.dw	LINK
        
        LINK =  .
	.db	(4)
	.ascii	"ADC!"
        ADC_CSR = 0x5400
        ADC_CR1 = 0x5401
        ADC_CR2 = 0x5402
ADCSTOR:
        LD      A,(1,X)
        INCW    X
        INCW    X
        AND     A,#0x0F
        LD      ADC_CSR,A       ; select channel
        BSET    ADC_CR2,#3      ; align ADC to LSB
        BSET    ADC_CR1,#0      ; enable ADC
        RET

;       ADC@  ( -- w )
;       start ADC conversion, read result
	.dw	LINK
        
        LINK =  .
	.db	(4)
	.ascii	"ADC@"

        ADC_DRH = 0x5404
ADCAT:
        BRES    ADC_CSR,#7      ; reset EOC
        BSET    ADC_CR1,#0      ; start ADC
        DECW    X
        DECW    X
1$:     BTJF    ADC_CSR,#7,1$   ; wait until EOC 
        LDW     Y,ADC_DRH       ; read ADC
        LDW     (X),Y
        RET
        .endif



        .ifne WORDS_HWREG * (STM8S003F3 + STM8S103F3)
          .include "hwregs8s003.inc"
        .endif

;===============================================================

        .ifne  HAS_CPNVM

;	Test if CP points doesn't point to RAM
NVMQ:
	LD      A,USRCP
        AND     A,#0xF8
        RET

;       return 0 if address is in RAM
NVMADRQ:
	CALL	DOLIT
	.dw	0xf800
        JP      ANDD


;       Helper routine: swap USRCP and NVMCP
SWAPCP:        
        LDW     Y,USRCP
        MOV     USRCP,NVMCP
        MOV     USRCP+1,NVMCP+1
        LDW     NVMCP,Y
        RET


;       NVM  ( -- )
;       Compile to NVM (enter mode NVM)
	.dw	LINK
        
        LINK =  .
	.db	(3)
	.ascii	"NVM"
NVMM:        
        CALL    NVMQ
        JRNE    1$           ; state entry action?
        ; in NVM mode only link words in NVM
        MOV     USRLAST,NVMCONTEXT
        MOV     USRLAST+1,NVMCONTEXT+1
        CALL    SWAPCP
        CALL    UNLOCK_FLASH
1$:
        RET


;       RAM  ( -- )
;       Compile to RAM (enter mode RAM)
	.dw	LINK
        
        LINK =  .
	.db	(3)
	.ascii	"RAM"
RAMM:        
        CALL    NVMQ
        JREQ    1$
        CALL    SWAPCP          ; Switch back to mode RAM

        MOV     COLDNVMCP,NVMCP ; Store NCM pointers for init in COLD 
        MOV     COLDNVMCP+1,NVMCP+1
        MOV     COLDCONTEXT,NVMCONTEXT
        MOV     COLDCONTEXT+1,NVMCONTEXT+1

        CALL    CNTXT           ; Does USRCONTEXT point to word in RAM?
        CALL    NVMADRQ                 
        CALL    QBRAN
        .dw     2$
        MOV     USRCONTEXT,NVMCONTEXT
        MOV     USRCONTEXT+1,NVMCONTEXT+1
2$:
        MOV     USRLAST,USRCONTEXT
        MOV     USRLAST+1,USRCONTEXT+1
        CALL    LOCK_FLASH
1$:
        RET


;       RESET  ( -- )
;       Reset Flash dictionary and 'BOOT to defaults and restart
	.dw	LINK
        
        LINK =  .
	.db	(5)
	.ascii	"RESET"
RESETT:        
	CALL    UNLOCK_FLASH
        CALL	DOLIT
	.dw     UDEFAULTS	
	CALL	DOLIT
        .dw     UBOOT
	CALL	DOLITC
	.db	(ULAST-UBOOT)
	CALL	CMOVE	        ; initialize user area
	CALL    LOCK_FLASH
        JP      COLD
 

        .endif

       
         
;===============================================================
	LASTN	=	LINK	;last name defined

 	.area CODE
	.area INITIALIZER
        END_SDCC_FLASH = .
	.area CABS (ABS)

