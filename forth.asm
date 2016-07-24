;===============================================================
; STM8EF for STM8S003F3 (Value Line) devives
;
; This is derived work based on 
; http://www.forth.org/svfig/kk/07-2010.html
;--------------------------------------------------------
; Original author:
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
;--------------------------------------------------------
; So far my attempts to contact the author over copyright 
; questions remained without reply. From early eForth  
; publications, I conclude that the license is akin to
; an open source license that requires derived work to be 
; published under the same condtions.
;
; Changes and code refactoring due to the following:
; * conditional code for different target devices
; * memory usage explicit, calculated from few constants
; * STM8S105C6 dependencies removed (e.g. UART2)
; * compactness (size over speed, 1K RAM layout)
; * new features, e.g. W1209 display & TxD with TIM4
; * SDCC tool chain "ASxxxx V2.0" syntax
;
; The docs for the SDCC integated assembler are very 
; thin. SDCC was used to create a template:
;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (Linux)
;--------------------------------------------------------

	.module forth
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
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

        ;*************************************************
        ;******  1) Hardware module type selection  ******
        ;*************************************************
        ; Note: add new variants here 
        STM8S_DISCOVERY = 0     ; (currently broken)
        MODULE_MINIMAL =  1     ; generic STM8S103F3 breakout board 
        MODULE_W1209 =    0     ; W1209 thermostat module 
        MODULE_RELAY =    0     ; "Relay Board-4", STM8S relay module

        ;**********************************
        ;******  2) Global defaults  ******
        ;**********************************
        STM8S103F3   =    0     ; 8K flash, 1K RAM, 640 bytes EEPROM
        STM8S003F3   =    0     ; like STM8S103F3, 128 bytes EEPROM 

        HALF_DUPLEX  =    0     ; RS232 shared Rx/Tx line, bus style
        TERM_LINUX   =    1     ; LF terminates line 
        HWREG_WORDS  =    0     ; Peripheral Register words
        HAS_LED7SEG  =    0     ; 7-seg LED on module
        HAS_OUTPUTS  =    0     ; Outputs, like relays, on module

        ;********************************************************
        ;******  3) Hardware module feature configuration  ******
        ;********************************************************
        ; Note: add new variants here 

        .ifne   MODULE_MINIMAL
        ; Clock: HSI (no crystal)
        STM8S103F3   =    1 
        HWREG_WORDS  =    1
        .endif

        .ifne   MODULE_W1209
        ; UART half-duplex PD_6 (RxD) SW simulation "bus style"
        ; Multiplexed 3 digit 7 seg LED display
        ; Clock: HSI (no crystal)
        STM8S003F3   =    1 
        HALF_DUPLEX  =    1     ; RS232 Half Duplex Mode
        HAS_LED7SEG  =    1     ; 7-seg LED on module
        HAS_OUTPUTS  =    1     ; Outputs, like relays, on module
        .endif

        .ifne   MODULE_RELAY
        ; Clock: HSI (8MHz crystal not used)
        STM8S103F3   =    1 
        HAS_OUTPUTS  =    1     ; Outputs, like relays, on module
        .endif

        ;**********************************************
        ;******  4) Device dependent features  ******
        ;**********************************************
        ; Note: add new STM8S device types here 

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

        MODDLOC =       0x0050  ; Hardware module driver data 
        UPPLOC  =       0x0060  ; UPP (user/system area) location for 1K RAM
        CTOPLOC =       0x0080  ; CTOP (user dictionary) location for 1K RAM
        SPPLOC  =       0x0380  ; SPP (data stack) location for 1K RAM
        RPPLOC  =       RAMEND  ; RPP (return stack) location for 1K RAM
        
        
	;******  STM8SF103 Registers  ******
	PA_ODR	=	0x5000	; Port A data output latch register
	PA_IDR	=	0x5001	; Port A input pin value register
	PA_DDR	=	0x5002	; Port A data direction register
	PA_CR1	=	0x5003	; Port A control register 1
	PA_CR2	=	0x5004	; Port A control register 2
	PB_ODR	=	0x5005	; Port B data output latch register
	PB_IDR	=	0x5006	; Port B input pin value register
	PB_DDR	=	0x5007	; Port B data direction register
	PB_CR1	=	0x5008	; Port B control register
	PB_CR2	=	0x5009	; Port B control register
	PC_ODR	=	0x500A	; Port C data output latch register
	PC_IDR	=	0x500B	; Port C input pin value register
	PC_DDR	=	0x500C	; Port C data direction register
	PC_CR1	=	0x500D	; Port C control register 1
	PC_CR2	=	0x500E	; Port C control register 2
	PD_ODR	=	0x500F	; Port D data output latch register
	PD_IDR	=	0x5010	; Port D input pin value register
	PD_DDR	=	0x5011	; Port D data direction register
	PD_CR1	=	0x5012	; Port D control register 1
	PD_CR2	=	0x5013	; Port D control register 2

        ; *** Non-Volatile Memory Control ***
        FLASH_IAPSR =   0x505F  ; Flash in-application programming status register
        FLASH_DUKR =    0x5064  ; Data EEPROM unprotection register

         ; *** Clock Control ***
        CLK_CKDIVR =    0x50C6  ; Clock divider register

	; *** UART1 ***
        UART1_SR   =	0x5230	;UART status reg
	UART1_DR   =	0x5231	;UART data reg
	UART1_BRR1  =	0x5232	;baud rate control 1
	UART1_BRR2  =	0x5233	;baud rate control 2
	UART1_CR1  =	0x5234	;UART control reg 2
	UART1_CR2  =	0x5235	;UART control reg 2
	UART1_CR3  =	0x5236	;UART control reg 2

        ; *** TIM4 (e.g. for RS232 TxD simulation) ***
        TIM4_CR1 =      0x5340  ; 1 (ENABLE)
        TIM4_IER =      0x5343  ; 1 (ENABLE)     
        TIM4_SR =       0x5344  ; 0 (clear)
        TIM4_EGR =      0x5345
        TIM4_CNTR =     0x5346
        TIM4_PSCR =     0x5347  ; 3 (1/8)
        TIM4_ARR =      0x5348  ; 0xCF (Reload 0.104 ms)
        .endif


        ;************************************************
        ;******  5) Module Driver Memory  ******
        ;************************************************
        ; Memory for module hardware related things, e.g. interrupt routines
         
        
        .ifne   MODULE_W1209
	;******  W1209 Variables  ******
        TIM4TX7S =      0x58    ; TIM4 TxD & LED interrupt states 
        TIM4TXREG  =    0x59    ; W1209 TxD simulation register 
        .endif

        .ifne   HAS_OUTPUTS
        OUTPUTS =       0x5A    ; outputs, like relays, LEDs, etc. 
        .endif

        .ifne   HAS_LED7SEG
        LED7FLAG =      0x5B    ; 7S output control flags 
        LED7MSB  =      0x5C    ; word 7S LEDs digits  43..
        LED7LSB  =      0x5E    ; word 7S LEDs digits  ..21
        .endif


        ;**************************************************
	;******  6) General User & System Variables  ******
        ;**************************************************

        ;Note: "RAMBASE +" made more sense for multi-user/multi-tasking
        ;      the STM8EF implementation has addressing mode limitations.
        ;      "VARIABLE words" like "BASE" can add an UPP offset, but
        ;      code accessing scratchpad (XTENP, etc) must be refactored, too!

        UPP   = UPPLOC          ; offset user area
        CTOP  = CTOPLOC         ; dictionary start, growing up
                                ; note: PAD is inbetween CTOP and SPP
	SPP   = SPPLOC	        ; data stack, growing down (with SPP-1 first)
        TIBB  = SPPLOC          ; Term. Input Buf. TIBLENGTH between SPP and RPP
	RPP   = RPPLOC          ; return stack, growing down
        
        ; Regular user variables
        USRBASE =    UPP+0      ; radix base for numeric I/O
        USREVAL =    UPP+2      ; execution vector of EVAL 
        USRCONTEXT=  UPP+4      ; start vocabulary search
        USRCP   =    UPP+6      ; point to top of dictionary
        USRLAST =    UPP+8      ; point to last name in dictionary
        USRTIB  =    UPP+10     ; address of terminal input buffer
        USRNTIB =    UPP+12     ; count in terminal input buffer 
        USR_IN  =    UPP+14     ; hold parsing pointer
        USRHLD  =    UPP+16     ; hold a pointer of output string
        USRTEMP =    UPP+18     ; temporary storage (VARIABLE tmp)
	SP0	=    UPP+20     ; initial data stack pointer
	RP0	=    UPP+22	; initial return stack pointer

        ; Scratchpad memory, directly used in assembler code
	XTEMP	=    UPP+24	; scratchpad (usually for X)
	YTEMP	=    UPP+26	; scratchpad (usually for Y)
	PROD1   =    XTEMP	; scratchpad alias for UM*
        PROD2   =    YTEMP      ; scratchpad alias for UM*
	PROD3   =    UPP+28     ; scratchpad for UM* 
	CARRY   =    UPP+30     ; scratchpad for UM* 


        ;************************************
	;******  7) General Constants  ******
        ;************************************

	;; Version control
	VER     =     2         ; major release version
	EXT     =     1         ; minor extension

	TRUEE   =     0xFFFF   ; true flag
	COMPO   =     0x40     ; lexicon compile only bit
	IMEDD   =     0x80     ; lexicon immediate bit
	MASKK   =     0x1F7F   ; lexicon bit mask

        TIBLENGTH =   80       ; size of TIB (starting at TIBOFFS)
        PADOFFS =     80       ; offset text buffer above dictionary 
	CELLL   =      2       ; size of a cell
	BASEE   =     10       ; default radix
        BKSPP   =      8       ; backspace
	LF      =     10       ; line feed
	CRR     =     13       ; carriage return
	ERR     =     27       ; error escape
	TIC     =     39       ; tick
	CALLL   =     0xCD     ; CALL opcodes


        ;***********************
	;******  8) Code  ******
        ;***********************

;; Entry point 
_forth:
        LDW     X,#(MODDLOC)
	; LDW     X,#0x300     ; Just clear stacks 
        ; CLRW    X              ; Clear all RAM 
1$:
	CLR     (X)                    
	INCW    X
	CPW     X,#(RAMEND+1)
	JRULE   1$

;; Main entry points and COLD start data
	
ORIG:	
	LDW	X,#RPP	        ;initialize return stack
	LDW	SP,X
	LDW	RP0,X
	LDW	X,#SPP          ; initialize data stack
	LDW	SP0,X
       
	JP	COLD	;default=MN1

; COLD start initiates these variables.

UZERO:
	.dw	BASEE	; BASE
	.dw	INTER	; 'EVAL
	.dw	LASTN	; CONTEXT pointer
	.dw	CTOP	; CP in RAM
	.dw	LASTN	; LAST
ULAST:                  ; end of UZERO block

;	COLD	( -- )
;	The hilevel cold start sequence.

	.dw	0
	
	LINK =	.
	.db	4
	.ascii	"COLD"
COLD:
	CALL	DOLIT
	.dw	UZERO
	CALL	DOLIT
	.dw	UPP
	CALL	DOLIT
	.dw	(ULAST-UZERO)
	CALL	CMOVE	        ;initialize user area
	CALL	PRESE	        ;initialize data stack and TIB

        ;; Device dependent HW initialization
PORTINIT:
        .ifne   STM8S_DISCOVERY
        ; STM8S Discovery init GPIO & UART
	MOV	PD_DDR,#0x01	; LED, SWIM
	MOV	PD_CR1,#0x03	; pullups
	MOV	PD_CR2,#0x01	; speed
	BSET    CLK_SWCR,#1     ; enable external clcok
	MOV     CLK_SWR,#0x0B4  ; external cyrstal clock
WAIT0:	BTJF    CLK_SWCR,#3,WAIT0 ; wait SWIF
	BRES    CLK_SWCR,#3     ; clear SWIF
	MOV	UART2_BD2,#0x003	; 9600 baud
	MOV	UART2_BD1,#0x068	; 0068 9600 baud
	MOV	UART2_CR1,#0x006	; 8 data bits, no parity
	MOV	UART2_CR3,#0x000	; 1 stop bit
        .endif

        .ifne  (STM8S003F3 + STM8S103F3)
        ; STM8S[01]003F3 init UART
        MOV     CLK_CKDIVR,#0           ; Clock divider register
	MOV	UART1_BRR2,#0x003	; 9600 baud
	MOV	UART1_BRR1,#0x068	; 0068 9600 baud
	;MOV	UART1_CR1,#0x006	; 8 data bits, no parity
          .ifne HALF_DUPLEX
	MOV	UART1_CR2,#0x004	; enable rx 
          .else              
	MOV	UART1_CR2,#0x00C	; enable tx & rx
          .endif
        .endif 

        .ifne   MODULE_W1209
        ; W1209 STM8S003F3 init GPIO & UART
        MOV     PA_DDR,#0b00001110 ; relay,B,F        
        MOV     PA_CR1,#0b00001110         
        MOV     PB_DDR,#0b00110000 ; d2,d3
        MOV     PB_CR1,#0b00110000 
        MOV     PC_DDR,#0b11000000 ; G,C        
        MOV     PC_CR1,#0b11000000         
        MOV     PD_DDR,#0b00111110 ; A,DP,D,d1,A
        MOV     PD_CR1,#0b00111110 
        MOV     TIM4_PSCR,#0x03 ; prescaler 1/8
        MOV     TIM4_ARR,#0xCF  ; reload 0.104 ms (9600 baud)
        MOV     TIM4_CR1,#0x01  ; enable TIM4
        MOV     TIM4_IER,#0x01  ; enable TIM4 interrupt
        RIM                     ; enable interrupts 
        .endif
        
        .ifne   MODULE_MINIMAL
        ; STM8S103F3 minimal breakout board init GPIO
        BSET     PB_DDR,#5  
        BSET     PB_CR1,#5 
        BSET     PB_ODR,#5      ; LED off
        .endif
        
        .ifne   MODULE_RELAY
        ; "Nano PLC Relay module"
        MOV     PB_DDR,#0x10
        MOV     PC_DDR,#0x38
        MOV     PD_DDR,#0x10
        MOV     PD_CR1,#0x10
        .endif

        .ifne   HAS_OUTPUTS
        CALL    ZERO
        CALL    OUTSTOR
        .endif

 	CALL	TBOOT
	CALL	ATEXE	        ;application boot
	CALL	OVERT
	JP	QUIT	        ;start interpretation

;	hi	( -- )
;	Display sign-on message.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"hi"
HI:
	CALL	CR
	CALL	DOTQP	        ; initialize I/O
	.db	15
	.ascii	"stm8eForth v"
	.db	(VER+'0')
	.ascii	"."
	.db	(EXT+'0')       ;version
	JP	CR


;	'BOOT	( -- a )
;	The application startup vector.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"'BOOT"
TBOOT:
	CALL	DOVAR
	.dw	HI	        ;application to boot


        ;; Device dependent I/O

        .ifne   MODULE_W1209

        ; TIM4 interrupt handler for 7-seg LED MPX and W1209 SW TxD. 
        ; RS232 TX works by writing a char to uint8_t TIM4TXREG, 
        ; and clearing TIM4TX7S Bit4.

        ; The W1209 has RxD (PD_6) on the sensor header, but STM8S UART1 
        ; half-duplex mode requires TxD (PD_5). The work-around here is 
        ; SW-TxD through PD_6 by switching between RxD, and GPIO. 
        ; Hint: bits TIM4TX7S.1:0 act as the LED MPX column counter.
        ; This is convoluted (= bad) code but the TxD phase won't be 
        ; disturbed by the LED MPX, and TxD needs a counter, anyway.

_TIM4_IRQHandler:
        PDTX =  6
        BRES    TIM4_SR,#0      ; clear TIM4 UIF 
        
        LD      A,TIM4TX7S
        JREQ    TIM4_ENDTX

        ; TIM4TX7S == 0x1F:0x1D ?
        CP     A,#0x1D         
        JRPL    TIM4_LED        ; State is "Wait"

        ; TIM4TX7S < 0x10 ?
        CP      A,#0x10         ; Active state?   
        JRMI    TIM4_ACTIVE_SYNC

        ; 0x1C <= TIM4TX7S >= 0x10
        MOV     TIM4TX7S,#0x20  ; Renew state "Wait", set TIM4TX7S to (0x20-1)
        JRA     TIM4_LED

TIM4_ACTIVE_SYNC:      
        CP      A,#0x0C         ; After clearing TIM4TX7S.4 we'll get here after some ticks
        JRMI    TIM4_TEST      
        JRA     TIM4_LED        ; State is "Sync"

TIM4_TEST:
        CP      A,#0x0B
        JRNE    TIM4_START
        
        BRES	UART1_CR2,#2	; disable RX
        ; TODO: if RX isn't free, 
        ;    return to (0x1F - 1)
        JRA     TIM4_LED

TIM4_START:  
        CP      A,#0x0A
        JRNE    TIM4_STOP
        ; TIM4TX7S == A 
        ; set PD_6 LOW
        BSET    PD_DDR,#PDTX    ; set PD_6 to output
        RCF
        JRA     TIM4_BIT         

TIM4_STOP:  
        CP      A,#0x01
        JRNE    TIM4_SER
        ; TIM4TX7S == 1 
        ; set PD_6 high
        SCF
        JRA     TIM4_BIT         

TIM4_ENDTX: 
        ; TIM4TX7S == 0
        BRES    PD_DDR,#PDTX    ; set PD_6 to input
        BSET	UART1_CR2,#2	; enable RX
        ; fall through
                
TIM4_SER:
        ; TIM4TX7S == 9:2
        SRL     TIM4TXREG    
        ; fall through

TIM4_BIT:
        ; Set RxTx port to CF value
        BCCM    PD_ODR,#PDTX

TIM4_LED:   
        ; W1209 multiplexed 7-seg LED display
        ; A contains TIM4TX7S, bis 1:0 are display counter  
        BSET    PD_ODR,#4       ; clear digit outputs .321
        BSET    PB_ODR,#5
        BSET    PB_ODR,#4

        AND     A,#3        
        JRNE    1$
        LD      A,LED7MSB+1
        BRES    PD_ODR,#4       ; digit .3.. 
        JRA     TIM4_SSEG

1$:     CP      A,#1
        JRNE    2$
        LD      A,LED7LSB
        BRES    PB_ODR,#5       ; digit ..2.
        JRA     TIM4_SSEG

2$:     CP      A,#2
        JRNE    TIM4_END  
        LD      A,LED7LSB+1 
        BRES    PB_ODR,#4       ; digit ...1
        ; fall through
         
TIM4_SSEG:
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

TIM4_END:             
        DEC     TIM4TX7S        ; next (convoluted) TXD TIM4 state/LED column
        JRPL    1$
        MOV     TIM4TX7S,#0x1F
1$:     
        IRET        

        .else

        ; Minimal IRQ handler for TIM4
_TIM4_IRQHandler:
        BRES    TIM4_SR,#0              ; clear TIM4 UIF 
        IRET 

        .endif


;	?RX	( -- c T | F )
;	Return input byte and true, or false.
	.dw	LINK
	LINK =	.
	.db	4
	.ascii	"?KEY"
QKEY:
	BTJF    UART1_SR,#5,INCH ;check status
	LD	A,UART1_DR	;get char in A
	SUBW	X,#2
	LD	(1,X),A
	CLR	(X)
	SUBW	X,#2
	LDW	Y,#0x0FFFF
	LDW	(X),Y
	RET
INCH:   CLRW    Y
	SUBW	X,#2
	LDW	(X),Y
	RET


;	TX!	( c -- )
;	Send character c to output device.

	.dw	LINK
	LINK =	.
	.db	4
	.ascii	"EMIT"
EMIT:
        .ifne   HALF_DUPLEX
	BRES	UART1_CR2,#2	;disable rx

        .ifne   MODULE_W1209
1$:     BTJF    TIM4TX7S,#4,1$
 	LD      A,(1,X)
        ADDW    X,#2       
        LD      TIM4TXREG,A
        BRES    TIM4TX7S,#4
2$:     BTJT    TIM4TX7S,#3,2$
        .else                   ; HALF_DUPLEX, not MODULE_W1209
	LD	A,(1,X)
	ADDW	X,#2
1$:	BTJF	UART1_SR,#7,1$  ;loop until tdre
	LD	UART1_DR,A	;send A
2$:	BTJF	UART1_SR,#6,2$  ;loop until tc
	BSET	UART1_CR2,#2	;enable rx
        .endif  

        .else                   ; not HALF_DUPLEX
	LD	A,(1,X)
	ADDW	X,#2
11$:	BTJF	UART1_SR,#7,11$ ;loop until tdre
	LD	UART1_DR,A	;send A
        .endif
	RET


;; The kernel
;	doLIT	( -- w )
;	Push an inline literal.

	.dw	LINK
	LINK =	.
	.db	(COMPO+5)
	.ascii	"doLit"
DOLIT:
	SUBW    X,#2
	POPW	Y
	LDW     YTEMP,Y
	LDW     Y,(Y)
	LDW     (X),Y
	LDW     Y,YTEMP
	JP      (2,Y)

;	next	( -- )
;	Code for single index loop.

	.dw	LINK
	LINK =	.
	.db	(COMPO+4)
	.ascii	"next"
DONXT:
	LDW     Y,(3,SP)
	DECW    Y
	JRPL    NEX1
	POPW	Y
	POP     A
	POP     A
	JP      (2,Y)
NEX1:   LDW     (3,SP),Y
	POPW	Y
	LDW     Y,(Y)
	JP      (Y)

;	?branch ( f -- )
;	Branch if flag is zero.

	.dw	LINK
	LINK =	.
	.db	(COMPO+7)
	.ascii	"?branch"
QBRAN:
	LDW     Y,X
	ADDW    X,#2
	LDW     Y,(Y)
	JREQ	BRAN
	POPW	Y
	JP      (2,Y)
	
;	branch	( -- )
;	Branch to an inline address.

	.dw	LINK
	LINK =	.
	.db	(COMPO+6)
	.ascii	"branch"
BRAN:
	POPW	Y
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
	ADDW    X,#2
	LDW	Y,(Y)
	JP	(Y)

;	EXIT	( -- )
;	Terminate a colon definition.

	.dw	LINK
	LINK =	.
	.db	4
	.ascii	"EXIT"
EXIT:
	POPW	Y
	RET

;	!	( w a -- )
;	Pop data stack to memory.

	.dw	LINK
	LINK =	.
	.db	1
	.ascii	"!"
STORE:
	LDW     Y,X
	LDW     Y,(Y)	        ;Y=a
	LDW     YTEMP,Y
	LDW     Y,X
	LDW     Y,(2,Y)
	LDW     [YTEMP],Y
	ADDW    X,#4            ;store w at a
	RET	

;	@	( a -- w )
;	Push memory location to stack.

	.dw	LINK
	LINK =	.
	.db	1
	.ascii	"@"
AT:
	LDW     Y,X	        ;Y = a
	LDW     Y,(Y)           
	LDW     Y,(Y)
	LDW     (X),Y           ;w = @Y
	RET	

;	C!	( c b -- )
;	Pop	data stack to byte memory.

	.dw	LINK
	LINK =	.
	.db	2
	.ascii	"C!"
CSTOR:
	LDW     Y,X
	LDW     Y,(Y)	;Y=b
	LD      A,(3,X)	;D = c
	LD	(Y),A	;store c at b
	ADDW    X,#4
	RET	

;	C@	( b -- c )
;	Push byte in memory to	stack.

	.dw	LINK
	LINK =	.
	.db	2
	.ascii	"C@"
CAT:
	LDW     Y,X	        ;Y=b
	LDW     Y,(Y)
	LD      A,(Y)
	LD      (1,X),A
	CLR     (X)
	RET	

;	RP@	( -- a )
;	Push current RP to data stack.

	.dw	LINK
	LINK =	.
	.db	3
	.ascii	"rp@"
RPAT:
	LDW     Y,SP	        ;save return addr
	SUBW    X,#2
	LDW     (X),Y
	RET	

;	RP!	( a -- )
;	Set	return stack pointer.

	.dw	LINK
	LINK =	.
	.db	(COMPO+3)
	.ascii	"rp!"
RPSTO:
	POPW	Y
	LDW     YTEMP,Y
	LDW     Y,X
	LDW     Y,(Y)
	LDW     SP,Y
	JP      [YTEMP]

;	R>	( -- w )
;	Pop return stack to data stack.

	.dw	LINK
	LINK =	.
	.db	(COMPO+2)
	.ascii	"R>"
RFROM:
	POPW	Y	        ;save return addr
	LDW     YTEMP,Y
	POPW	Y
	SUBW    X,#2
	LDW     (X),Y
	JP      [YTEMP]

;	R@	( -- w )
;	Copy top of return stack to stack.

	.dw	LINK
	LINK =	.
	.db	2
	.ascii	"R@"
RAT:
	POPW	Y
	LDW     YTEMP,Y
	POPW	Y
	PUSHW   Y
	SUBW    X,#2
	LDW     (X),Y
	JP      [YTEMP]

;	>R	( w -- )
;	Push data stack to return stack.

	.dw	LINK
	LINK =	.
	.db	(COMPO+2)
	.ascii	">R"
TOR:
	POPW	Y	;save return addr
	LDW     YTEMP,Y
	LDW     Y,X
	LDW     Y,(Y)
	PUSHW   Y	;restore return addr
	ADDW    X,#2
	JP      [YTEMP]


;	DROP	( w -- )
;	Discard top stack item.

	.dw	LINK
	LINK =	.
	.db	4
	.ascii	"DROP"
DROP:
	ADDW X,#2	
	RET	

;	DUP	( w -- w w )
;	Duplicate top stack item.

	.dw	LINK
	LINK =	.
	.db	3
	.ascii	"DUP"
DUPP:
	LDW     Y,X
	SUBW    X,#2
	LDW     Y,(Y)
	LDW     (X),Y
	RET	

;	SWAP  	( w1 w2 -- w2 w1 )
;	Exchange top two stack items.

	.dw	LINK
	LINK =	.
	.db	4
	.ascii	"SWAP"
SWAPP:
	LDW     Y,X
	LDW     Y,(Y)
	LDW     YTEMP,Y
	LDW     Y,X
	LDW     Y,(2,Y)
	LDW     (X),Y
	LDW     Y,YTEMP
	LDW     (2,X),Y
	RET	

;	OVER	( w1 w2 -- w1 w2 w1 )
;	Copy second stack item to top.

	.dw	LINK
	LINK =	.
	.db	4
	.ascii	"OVER"
OVER:
	SUBW    X,#2
	LDW     Y,X
	LDW     Y,(4,Y)
	LDW     (X),Y
	RET	

;	0<	( n -- t )
;	Return true if n is negative.

	.dw	LINK
	LINK =	.
	.db	2
	.ascii	"0<"
ZLESS:
	LD      A,#0x0FF
	LDW     Y,X
	LDW     Y,(Y)
	JRMI	ZL1
	CLR     A	;false
ZL1:    LD      (X),A
	LD      (1,X),A
	RET	

;	AND	( w w -- w )
;	Bitwise AND.

	.dw	LINK
	LINK =	.
	.db	3
	.ascii	"AND"
ANDD:
	LD	A,(X)	;D=w
	AND     A,(2,X)
	LD      (2,X),A
	LD      A,(1,X)
	AND     A,(3,X)
LDADROP:
	LD      (3,X),A
	ADDW    X,#2
	RET

;	OR	( w w -- w )
;	Bitwise inclusive OR.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"OR"
ORR:
	LD	A,(X)	;D=w
	OR      A,(2,X)
	LD      (2,X),A
	LD      A,(1,X)
	OR      A,(3,X)
;	LD      (3,X),A
;	ADDW    X,#2
;	RET
        JRA     LDADROP


;	XOR	( w w -- w )
;	Bitwise exclusive OR.

	.dw	LINK
	LINK =	.
	.db	3
	.ascii	"XOR"
XORR:
	LD	A,(X)	;D=w
	XOR     A,(2,X)
	LD      (2,X),A
	LD      A,(1,X)
	XOR     A,(3,X)
;	LD      (3,X),A
;	ADDW    X,#2
;	RET
        JRA     LDADROP

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

	.dw	LINK
	LINK =	.
	.db	3
	.ascii	"sp!"
SPSTO:
	LDW	X,(X)	;X = a
	RET	

;	SP@	( -- a )
;	Push current stack pointer.

	.dw	LINK
	LINK =	.
	.db	3
	.ascii	"sp@"
SPAT:
	LDW     Y,X
;	SUBW    X,#2
;	LDW     (X),Y
;	RET	
        JRA     YSTOR

;; System and user variables

;	doVAR	( -- a )
;	Code for VARIABLE and CREATE.

	.dw	LINK
	LINK =	.
	.db	(COMPO+5)
	.ascii	"doVar"
DOVAR:
	POPW	Y	;get return addr (pfa)
;	SUBW    X,#2
;	LDW     (X),Y	;push on stack
;	RET	;go to RET of EXEC
        JRA     YSTOR

;	BASE	( -- a )
;	Radix base for numeric I/O.

	.dw	LINK
	LINK =	.
	.db	4
	.ascii	"BASE"
BASE:
	LDW     Y,#(RAMBASE+USRBASE)
;	SUBW    X,#2
;	LDW     (X),Y
;	RET
        JRA     YSTOR

;	tmp	( -- a )
;	A temporary storage.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"tmp"
TEMP:
	LDW     Y,#(RAMBASE+USRTEMP)
;	SUBW    X,#2
;	LDW     (X),Y
;	RET
        JRA     YSTOR

;	>IN	( -- a )
;	Hold parsing pointer.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	">IN"
INN:
	LDW     Y,#(RAMBASE+USR_IN)
;	SUBW    X,#2
;	LDW     (X),Y
;	RET
        JRA     YSTOR

;	#TIB	( -- a )
;	Count in terminal input buffer.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"#TIB"
NTIB:
	LDW     Y,#(RAMBASE+USRNTIB)
;	SUBW    X,#2
;	LDW     (X),Y
;	RET
        JRA     YSTOR

;	"EVAL	( -- a )
;	Execution vector of EVAL.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"'eval"
TEVAL:
	LDW     Y,#(RAMBASE+USREVAL)
;	SUBW    X,#2
;	LDW     (X),Y
;	RET
        JRA     YSTOR


;	HLD	( -- a )
;	Hold a pointer of output string.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"hld"
HLD:
	LDW     Y,#(RAMBASE+USRHLD)
;	SUBW    X,#2
;	LDW     (X),Y
;	RET
        JRA     YSTOR

;	CONTEXT ( -- a )
;	Start vocabulary search.

	.dw	LINK
	
	LINK =	.
	.db	7
	.ascii	"CONTEXT"
CNTXT:
	LDW     Y,#(RAMBASE+USRCONTEXT)
;	SUBW    X,#2
;	LDW     (X),Y
;	RET
        JRA     YSTOR

;	CP	( -- a )
;	Point to top of dictionary.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"cp"
CPP:
	LDW     Y,#(RAMBASE+USRCP)
;	SUBW    X,#2
;	LDW     (X),Y
;	RET
        JRA     YSTOR


;	LAST	( -- a )
;	Point to last name in dictionary.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"last"
LAST:
	LDW     Y,#(RAMBASE+USRLAST)

; "!" for Y for variable addresses, and constants
YSTOR:        
	SUBW    X,#2
	LDW     (X),Y
	RET

;	TIB	( -- a )
;	Return address of terminal input buffer.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"TIB"
TIB:
	LDW     Y,#(RAMBASE+USRTIB)
;	SUBW    X,#2
;	LDW     (X),Y
;	RET
        JRA     YSTOR

;	OUT	( -- a )
;	Return address of OUTPUTS register

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"OUT"
OUTA:
	LDW     Y,#(OUTPUTS)
;	SUBW    X,#2
;	LDW     (X),Y
;	RET
        JRA     YSTOR


;; Constants

;	BL	( -- 32 )
;	Return 32, blank character.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"BL"
BLANK:
	LDW     Y,#32
;	SUBW    X,#2
;	LDW     (X),Y
;	RET
        JRA     YSTOR

;	0	( -- 0)
;	Return 0.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"0"
ZERO:
	CLRW    Y
;	SUBW    X,#2
;	LDW     (X),Y
;	RET
        JRA     YSTOR

;	1	( -- 1)
;	Return 1.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"1"
ONE:
	LDW     Y,#1
;	SUBW    X,#2
;	LDW     (X),Y
;	RET
        JRA     YSTOR

;	-1	( -- -1)
;	Return 32, blank character.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"-1"
MONE:
	LDW     Y,#0x0FFFF
;	SUBW    X,#2
;	LDW     (X),Y
;	RET
        JRA     YSTOR



;; Common functions

;	?DUP	( w -- w w | 0 )
;	Dup tos if its is not zero.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"?DUP"
QDUP:
	LDW     Y,X
	LDW     Y,(Y)
	JREQ	QDUP1
	SUBW    X,#2
	LDW     (X),Y
QDUP1:	RET

;	ROT	( w1 w2 w3 -- w2 w3 w1 )
;	Rot 3rd item to top.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"ROT"
ROT:
	LDW     Y,X
	LDW     Y,(4,Y)
	LDW     YTEMP,Y
	LDW     Y,X
	LDW     Y,(2,Y)
	LDW     XTEMP,Y
	LDW     Y,X
	LDW     Y,(Y)
	LDW     (2,X),Y
	LDW     Y,XTEMP
	LDW     (4,X),Y
	LDW     Y,YTEMP
	LDW     (X),Y
	RET

;	2DROP	( w w -- )
;	Discard two items on stack.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"2DROP"
DDROP:
	ADDW    X,#4
	RET

;	2DUP	( w1 w2 -- w1 w2 w1 w2 )
;	Duplicate top two items.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"2DUP"
DDUP:
	SUBW    X,#4
	LDW     Y,X
	LDW     Y,(6,Y)
	LDW     (2,X),Y
	LDW     Y,X
	LDW     Y,(4,Y)
	LDW     (X),Y
	RET

;	+	( w w -- sum )
;	Add top two items.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"+"
PLUS:
	LDW     Y,X
	LDW     Y,(Y)
	LDW     YTEMP,Y
	ADDW    X,#2
	LDW     Y,X
	LDW     Y,(Y)
	ADDW    Y,YTEMP
	LDW     (X),Y
	RET

;	NOT	( w -- w )
;	One's complement of tos.

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

;	NEGATE	( n -- -n )
;	Two's complement of tos.

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

;	DNEGATE ( d -- -d )
;	Two's complement of top double.

	.dw	LINK
	
	LINK =	.
	.db	7
	.ascii	"DNEGATE"
DNEGA:
	LDW     Y,X
	LDW     Y,(Y)
	CPLW    Y	
	LDW     YTEMP,Y
	LDW     Y,X
	LDW     Y,(2,Y)
	CPLW    Y
	INCW    Y
	LDW     (2,X),Y
	LDW     Y,YTEMP
	JRNC    DN1 
	INCW    Y
DN1:    LDW     (X),Y
	RET

;	-	( n1 n2 -- n1-n2 )
;	Subtraction.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"-"
SUBB:
	LDW     Y,X
	LDW     Y,(Y)
	LDW     YTEMP,Y
	ADDW    X,#2
	LDW     Y,X
	LDW     Y,(Y)
	SUBW    Y,YTEMP
	LDW     (X),Y
	RET

;	ABS	( n -- n )
;	Return	absolute value of n.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"ABS"
ABSS:
	LDW     Y,X
	LDW     Y,(Y)
	JRPL	AB1	;negate:
	NEGW	Y	;else negate hi byte
	LDW     (X),Y
AB1:    RET

;	=	( w w -- t )
;	Return true if top two are equal.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"="
EQUAL:
	LD      A,#0x0FF	;true
	LDW     Y,X	;D = n2
	LDW     Y,(Y)
	LDW     YTEMP,Y
	ADDW    X,#2
	LDW     Y,X
	LDW     Y,(Y)
	CPW     Y,YTEMP	;if n2 <> n1
	JREQ	EQ1
	CLR     A
EQ1:    LD      (X),A
	LD      (1,X),A
	RET	

;	U<	( u u -- t )
;	Unsigned compare of top two items.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"U<"
ULESS:
	LD      A,#0x0FF	;true
	LDW     Y,X	;D = n2
	LDW     Y,(Y)
	LDW     YTEMP,Y
	ADDW    X,#2
	LDW     Y,X
	LDW     Y,(Y)
	CPW     Y,YTEMP	;if n2 <> n1
	JRULT	ULES1
	CLR     A
ULES1:  LD      (X),A
	LD      (1,X),A
	RET	

;	<	( n1 n2 -- t )
;	Signed compare of top two items.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"<"
LESS:
	LD      A,#0x0FF	;true
	LDW     Y,X	;D = n2
	LDW     Y,(Y)
	LDW     YTEMP,Y
	ADDW    X,#2
	LDW     Y,X
	LDW     Y,(Y)
	CPW     Y,YTEMP	;if n2 <> n1
	JRSLT	LT1
	CLR     A
LT1:    LD      (X),A
	LD      (1,X),A
	RET	

;	MAX	( n n -- n )
;	Return greater of two top items.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"MAX"
MAX:
	LDW     Y,X	;D = n2
	LDW     Y,(2,Y)
	LDW     YTEMP,Y
	LDW     Y,X
	LDW     Y,(Y)
	CPW     Y,YTEMP	;if n2 <> n1
	JRSLT	MAX1
	LDW     (2,X),Y
MAX1:   ADDW    X,#2
	RET	

;	MIN	( n n -- n )
;	Return smaller of top two items.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"MIN"
MIN:
	LDW     Y,X	;D = n2
	LDW     Y,(2,Y)
	LDW     YTEMP,Y
	LDW     Y,X
	LDW     Y,(Y)
	CPW     Y,YTEMP	;if n2 <> n1
	JRSGT	MIN1
	LDW     (2,X),Y
MIN1:   ADDW    X,#2
	RET	

;	WITHIN	( u ul uh -- t )
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

;; Divide

;	UM/MOD	( udl udh un -- ur uq )
;	Unsigned divide of a double by a
;	single. Return mod and quotient.

	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"UM/MOD"
UMMOD:
	LDW     XTEMP,X	; save stack pointer
	LDW     X,(X)	; un
	LDW     YTEMP,X ; save un
	LDW     Y,XTEMP	; stack pointer
	LDW     Y,(4,Y) ; Y=udl
	LDW     X,XTEMP
	LDW     X,(2,X)	; X=udh
	CPW     X,YTEMP
	JRULE   MMSM1
	LDW     X,XTEMP
	ADDW    X,#2	; pop off 1 level
	LDW     Y,#0x0FFFF
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
	LDW     X,XTEMP
	ADDW    X,#2	; drop
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

;	MOD	( n n -- r )
;	Signed divide. Return mod only.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"MOD"
MODD:
	CALL	SLMOD
	JP	DROP

;	/	( n n -- q )
;	Signed divide. Return quotient only.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"/"
SLASH:
	CALL	SLMOD
	CALL	SWAPP
	JP	DROP

;; Multiply

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
	LDW     PROD1,Y
	LD      A,(3,X)	; a
	LD      YL,A
	LD      A,(X)	; d
	MUL     Y,A
	LDW     PROD2,Y
	LD      A,(2,X)	; b
	LD      YL,A
	LD      A,(1,X)	; c
	MUL     Y,A
	LDW     PROD3,Y
	LD      A,(3,X)	; a
	LD      YL,A
	LD      A,(1,X)	; c
	MUL     Y,A	; least signifiant product
	CLR     A
	RRWA    Y
	LD      (3,X),A	; store least significant byte
	ADDW    Y,PROD3
	CLR     A
	ADC     A,#0	; save carry
	LD      CARRY,A
	ADDW    Y,PROD2
	LD      A,CARRY
	ADC     A,#0	; add 2nd carry
	LD      CARRY,A
	CLR     A
	RRWA    Y
	LD      (2,X),A	; 2nd product byte
	ADDW    Y,PROD1
	RRWA    Y
	LD      (1,X),A	; 3rd product byte
	RRWA    Y		; 4th product byte now in A
	ADC     A,CARRY	; fill in carry bits
	LD      (X),A
	RET

;	*	( n n -- n )
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

;	*/	( n1 n2 n3 -- q )
;	Multiply n1 by n2, then divide
;	by n3. Return quotient only.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"*/"
STASL:
	CALL	SSMOD
	CALL	SWAPP
	JP	DROP

;; Miscellaneous

;	CELL+	( a -- a )
;	Add cell size in byte to address.

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

;	CELL-	( a -- a )
;	Subtract 2 from address.

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

;	CELLS	( n -- n )
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

;	1+	( n -- n )
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

;	1-	( n -- n )
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

;	2/	( n -- n )
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

;	>CHAR	( c -- c )
;	Filter non-printing characters.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	">CHAR"
TCHAR:
	CALL	DOLIT
	.dw	0x07F
	CALL	ANDD
	CALL	DUPP	;mask msb
	CALL	DOLIT
	.dw	127
	CALL	BLANK
	CALL	WITHI	;check for printable
	CALL	QBRAN
	.dw	TCHA1
	CALL	DROP
	CALL	DOLIT
	.dw	0x05F	; "_"	;replace non-printables
TCHA1:	RET

;	DEPTH	( -- n )
;	Return	depth of	data stack.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"DEPTH"
DEPTH:
	LDW     Y,SP0	;save data stack ptr
	LDW     XTEMP,X
	SUBW    Y,XTEMP	;#bytes = SP0 - X
	SRAW    Y	;D = #stack items
	DECW    Y
	SUBW    X,#2
	LDW     (X),Y	; if neg, underflow
	RET

;	PICK	( ... +n -- ... w )
;	Copy	nth stack item to tos.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"PICK"
PICK:
	LDW     Y,X	;D = n1
	LDW     Y,(Y)
	SLAW    Y
	LDW     XTEMP,X
	ADDW    Y,XTEMP
	LDW     Y,(Y)
	LDW     (X),Y
	RET

;; Memory access

;	+!	( n a -- )
;	Add n to	contents at address a.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"+!"
PSTOR:
	CALL	SWAPP
	CALL	OVER
	CALL	AT
	CALL	PLUS
	CALL	SWAPP
	JP	STORE

;	2!	( d a -- )
;	Store	double integer to address a.

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

;	COUNT	( b -- b +n )
;	Return count byte of a string
;	and add 1 to byte address.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"COUNT"
COUNT:
	CALL	DUPP
	CALL	ONEP
	CALL	SWAPP
	JP	CAT

;	HERE	( -- a )
;	Return	top of	code dictionary.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"HERE"
HERE:
	CALL	CPP
	JP	AT

;	PAD	( -- a )
;	Return address of text buffer
;	above	code dictionary.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"PAD"
PAD:
	CALL	HERE
	CALL	DOLIT
	.dw	PADOFFS
	JP	PLUS

;	@EXECUTE	( a -- )
;	Execute vector stored in address a.

	.dw	LINK
	
	LINK =	.
	.db	8
	.ascii	"@EXECUTE"
ATEXE:
	CALL	AT
	CALL	QDUP	;?address or zero
	CALL	QBRAN
	.dw	EXE1
	CALL	EXECU	;execute if non-zero
EXE1:	RET	;do nothing if zero

;	CMOVE	( b1 b2 u -- )
;	Copy u bytes from b1 to b2.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"CMOVE"
CMOVE:
	CALL	TOR
	CALL	BRAN
	.dw	CMOV2
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
	CALL	BRAN
	.dw	FILL2
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

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"PACK$"
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

;; Numeric output, single precision

;	DIGIT	( u -- c )
;	Convert digit u to a character.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"DIGIT"
DIGIT:
	CALL	DOLIT
	.dw	9
	CALL	OVER
	CALL	LESS
	CALL	DOLIT
	.dw	7
	CALL	ANDD
	CALL	PLUS
	CALL	DOLIT
	.dw	48	;'0'
	JP	PLUS

;	EXTRACT ( n base -- n c )
;	Extract least significant digit from n.

	.dw	LINK
	
	LINK =	.
	.db	7
	.ascii	"EXTRACT"
EXTRC:
	CALL	ZERO
	CALL	SWAPP
	CALL	UMMOD
	CALL	SWAPP
	JP	DIGIT

;	<#	( -- )
;	Initiate	numeric output process.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"<#"
BDIGS:
	CALL	PAD
	CALL	HLD
	JP	STORE

;	HOLD	( c -- )
;	Insert a character into output string.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"HOLD"
HOLD:
	CALL	HLD
	CALL	AT
	CALL	ONEM
	CALL	DUPP
	CALL	HLD
	CALL	STORE
	JP	CSTOR

;	#	( u -- u )
;	Extract one digit from u and
;	append digit to output string.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"#"
DIG:
	CALL	BASE
	CALL	AT
	CALL	EXTRC
	JP	HOLD

;	#S	( u -- 0 )
;	Convert u until all digits
;	are added to output string.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"#S"
DIGS:
DIGS1:	CALL	DIG
	CALL	DUPP
	CALL	QBRAN
	.dw	DIGS2
	JRA	DIGS1
DIGS2:	RET

;	SIGN	( n -- )
;	Add a minus sign to
;	numeric output string.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"SIGN"
SIGN:
	CALL	ZLESS
	CALL	QBRAN
	.dw	SIGN1
	CALL	DOLIT
	.dw	45	;"-"
	JP	HOLD
SIGN1:	RET

;	#>	( w -- b u )
;	Prepare output string.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"#>"
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

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"str"
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
	CALL	DOLIT
	.dw	16
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
	CALL	DOLIT
	.dw	10
	CALL	BASE
	JP	STORE

;; Numeric input, single precision

;	DIGIT?	( c base -- u t )
;	Convert a character to its numeric
;	value. A flag indicates success.

	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"DIGIT?"
DIGTQ:
	CALL	TOR
	CALL	DOLIT
	.dw	48	; "0"
	CALL	SUBB
	CALL	DOLIT
	.dw	9
	CALL	OVER
	CALL	LESS
	CALL	QBRAN
	.dw	DGTQ1
	CALL	DOLIT
	.dw	7
	CALL	SUBB
	CALL	DUPP
	CALL	DOLIT
	.dw	10
	CALL	LESS
	CALL	ORR
DGTQ1:	CALL	DUPP
	CALL	RFROM
	JP	ULESS

;	NUMBER? ( a -- n T | a F )
;	Convert a number string to
;	integer. Push a flag on tos.

	.dw	LINK
	
	LINK =	.
	.db	7
	.ascii	"NUMBER?"
NUMBQ:
	CALL	BASE
	CALL	AT
	CALL	TOR
	CALL	ZERO
	CALL	OVER
	CALL	COUNT
	CALL	OVER
	CALL	CAT
	CALL	DOLIT
	.dw	36	; "0x0"
	CALL	EQUAL
	CALL	QBRAN
	.dw	NUMQ1
	CALL	HEX
	CALL	SWAPP
	CALL	ONEP
	CALL	SWAPP
	CALL	ONEM
NUMQ1:	CALL	OVER
	CALL	CAT
	CALL	DOLIT
	.dw	45	; "-"
	CALL	EQUAL
	CALL	TOR
	CALL	SWAPP
	CALL	RAT
	CALL	SUBB
	CALL	SWAPP
	CALL	RAT
	CALL	PLUS
	CALL	QDUP
	CALL	QBRAN
	.dw	NUMQ6
	CALL	ONEM
	CALL	TOR
NUMQ2:	CALL	DUPP
	CALL	TOR
	CALL	CAT
	CALL	BASE
	CALL	AT
	CALL	DIGTQ
	CALL	QBRAN
	.dw	NUMQ4
	CALL	SWAPP
	CALL	BASE
	CALL	AT
	CALL	STAR
	CALL	PLUS
	CALL	RFROM
	CALL	ONEP
	CALL	DONXT
	.dw	NUMQ2
	CALL	RAT
	CALL	SWAPP
	CALL	DROP
	CALL	QBRAN
	.dw	NUMQ3
	CALL	NEGAT
NUMQ3:	CALL	SWAPP
	JRA	NUMQ5
NUMQ4:	CALL	RFROM
	CALL	RFROM
	CALL	DDROP
	CALL	DDROP
	CALL	ZERO
NUMQ5:	CALL	DUPP
NUMQ6:	CALL	RFROM
	CALL	DDROP
	CALL	RFROM
	CALL	BASE
	JP	STORE

;; Basic I/O

;	KEY	( -- c )
;	Wait for and return an
;	input character.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"KEY"
KEY:
KEY1:	CALL	QKEY
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
        CLRW    Y            ; delay to slow EMIT down 
1$:     DECW    Y             
        JRNE    1$
        .endif
	CALL	QKEY
	CALL	DUPP
	CALL	QBRAN
	.dw	NUFQ1
	CALL	DDROP
	CALL	KEY
	CALL	DOLIT
	.dw	CRR
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
        .ifne  MODULE_W1209
        TNZ     LED7FLAG        ; NZ: don't emit blank on W1209 7-seg LED 
        JREQ    1$  
        BSET    LED7FLAG,#7
        RET
        .endif

1$:	CALL	BLANK
	JP	EMIT

;	SPACES	( +n -- )
;	Send n spaces to output device.

	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"SPACES"
SPACS:
	CALL	ZERO
	CALL	MAX
	CALL	TOR
	JRA	CHAR2
CHAR1:	CALL	SPACE
CHAR2:	CALL	DONXT
	.dw	CHAR1
	RET

;	TYPE	( b u -- )
;	Output u characters from b.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"TYPE"
TYPES:
	CALL	TOR
	JRA	TYPE2
TYPE1:	CALL	DUPP
	CALL	CAT
        .ifne  MODULE_W1209
        TNZ     LED7FLAG        ; NZ: output c on W1209 7-seg LED 
        JREQ    1$  
	CALL	EMIT7S	        ;display on 7-seg
        JRA     2$
        .endif

1$:	CALL	EMIT
2$:	CALL	ONEP
TYPE2:	
        CALL	DONXT
	.dw	TYPE1
        .ifne   MODULE_W1209
        TNZ     LED7FLAG         ; B7 set: output c on W1209 7-seg LED 
        JRPL    1$  
        CLR     LED7FLAG
        .endif
1$:	JP	DROP

;	CR	( -- )
;	Output a carriage return
;	and a line feed.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"CR"
CR:
        .ifeq TERM_LINUX
	CALL	DOLIT
	.dw	CRR
	CALL	EMIT
        .endif
	CALL	DOLIT
	.dw	LF
	JP	EMIT

;	do$	( -- a )
;	Return	address of a compiled
;	string.

	.dw	LINK
	
	LINK =	.
	.db	(COMPO+3)
	.ascii	"do$"
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

	.dw	LINK
	
	LINK =	.
	.db	(COMPO+3)
	.ascii	'$"|'
STRQP:
	CALL	DOSTR
	RET

;	."|	( -- )
;	Run time routine of ." .
;	Output a compiled string.

	.dw	LINK
	
	LINK =	.
	.db	(COMPO+3)
	.ascii	'."|'
DOTQP:
	CALL	DOSTR
	CALL	COUNT
	JP	TYPES

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
	CALL	RFROM
	CALL	OVER
	CALL	SUBB
	CALL	SPACS
	JP	TYPES

;	U.R	( u +n -- )
;	Display an unsigned integer
;	in n column, right justified.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"U.R"
UDOTR:
	CALL	TOR
	CALL	BDIGS
	CALL	DIGS
	CALL	EDIGS
	CALL	RFROM
	CALL	OVER
	CALL	SUBB
	CALL	SPACS
	JP	TYPES

;	U.	( u -- )
;	Display an unsigned integer
;	in free format.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"U."
UDOT:
	CALL	BDIGS
	CALL	DIGS
	CALL	EDIGS
	CALL	SPACE
	JP	TYPES

;	.	( w -- )
;	Display an integer in free
;	format, preceeded by a space.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"."
DOT:
	CALL	BASE
	CALL	AT
	CALL	DOLIT
	.dw	10
	CALL	XORR	;?decimal
	CALL	QBRAN
	.dw	DOT1
	JP	UDOT
DOT1:	CALL	STR
	CALL	SPACE
	JP	TYPES

;	?	( a -- )
;	Display contents in memory cell.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	"?"
QUEST:
	CALL	AT
	JP	DOT

;; Parsing

;	parse	( b u c -- b u delta ; <string> )
;	Scan string delimited by c.
;	Return found string and its offset.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"parse"
PARS:
	CALL	TEMP
	CALL	STORE
	CALL	OVER
	CALL	TOR
	CALL	DUPP
	CALL	QBRAN
	.dw	PARS8
	CALL	ONEM
	CALL	TEMP
	CALL	AT
	CALL	BLANK
	CALL	EQUAL
	CALL	QBRAN
	.dw	PARS3
	CALL	TOR
PARS1:	CALL	BLANK
	CALL	OVER
	CALL	CAT	;skip leading blanks ONLY
	CALL	SUBB
	CALL	ZLESS
	CALL	INVER
	CALL	QBRAN
	.dw	PARS2
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
	CALL	TEMP
	CALL	AT
	CALL	BLANK
	CALL	EQUAL
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
PARS8:	CALL	OVER
	CALL	RFROM
	JP	SUBB

;	PARSE	( c -- b u ; <string> )
;	Scan input stream and return
;	counted string delimited by c.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"PARSE"
PARSE:
	CALL	TOR
	CALL	TIB
	CALL	AT
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
	CALL	DOLIT
	.dw	41	; ")"
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
	CALL	DOLIT
	.dw	41	; ")"
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

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"WORD"
WORDD:
	CALL	PARSE
	CALL	HERE
	CALL	CELLP
	JP	PACKS

;	TOKEN	( -- a ; <string> )
;	Parse a word from input stream
;	and copy it to name dictionary.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"TOKEN"
TOKEN:
	CALL	BLANK
	JP	WORDD

;; Dictionary search

;	NAME>	( na -- ca )
;	Return a code address given
;	a name address.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"NAME>"
NAMET:
	CALL	COUNT
	CALL	DOLIT
	.dw	31
	CALL	ANDD
	JP	PLUS

;	SAME?	( a a u -- a a f \ -0+ )
;	Compare u cells in two
;	strings. Return 0 if identical.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"SAME?"
SAMEQ:
	CALL	ONEM
	CALL	TOR
	JRA	SAME2
SAME1:	CALL	OVER
	CALL	RAT
	CALL	PLUS
	CALL	CAT
	CALL	OVER
	CALL	RAT
	CALL	PLUS
	CALL	CAT
	CALL	SUBB
	CALL	QDUP
	CALL	QBRAN
	.dw	SAME2
	CALL	RFROM
	JP	DROP
SAME2:	CALL	DONXT
	.dw	SAME1
	JP	ZERO

;	find	( a va -- ca na | a F )
;	Search vocabulary for string.
;	Return ca and na if succeeded.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"find"
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
	CALL	DUPP
	CALL	QBRAN
	.dw	FIND6
	CALL	DUPP
	CALL	AT
	CALL	DOLIT
	.dw	MASKK
	CALL	ANDD
	CALL	RAT
	CALL	XORR
	CALL	QBRAN
	.dw	FIND2
	CALL	CELLP
	CALL	DOLIT
	.dw	0x0FFFF
	JRA	FIND3
FIND2:	CALL	CELLP
	CALL	TEMP
	CALL	AT
	CALL	SAMEQ
FIND3:	CALL	BRAN
	.dw	FIND4
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
	CALL	SWAPP
	CALL	DROP
	CALL	CELLM
	CALL	DUPP
	CALL	NAMET
	JP	SWAPP

;	NAME?	( a -- ca na | a F )
;	Search vocabularies for a string.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"NAME?"
NAMEQ:
	CALL	CNTXT
	JP	FIND

;; Terminal response

;	^H	( bot eot cur -- bot eot cur )
;	Backup cursor by one character.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"^h"
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
	CALL	DOLIT
	.dw	BKSPP
	CALL	EMIT
        .endif
	CALL	ONEM
	CALL	BLANK
	CALL	EMIT
	CALL	DOLIT
	.dw	BKSPP
	JP	EMIT
BACK1:	RET

;	TAP	( bot eot cur c -- bot eot cur )
;	Accept and echo key stroke
;	and bump cursor.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"TAP"
TAP:
        .ifeq   HALF_DUPLEX
	CALL	DUPP
	CALL	EMIT
        .endif
	CALL	OVER
	CALL	CSTOR
	JP	ONEP

;	kTAP	( bot eot cur c -- bot eot cur )
;	Process a key stroke,
;	CR or backspace.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"kTAP"
KTAP:
	CALL	DUPP
	CALL	DOLIT
	.dw	CRR
	CALL	XORR
	CALL	QBRAN
	.dw	KTAP2

	CALL	DOLIT
	.dw	BKSPP
	CALL	XORR
	CALL	QBRAN
	.dw	KTAP1

	CALL	BLANK
	JP	TAP
KTAP1:	JP	BKSP
KTAP2:	CALL	DROP
	CALL	SWAPP
	CALL	DROP
	JP	DUPP

;	accept	( b u -- b u )
;	Accept characters to input
;	buffer. Return with actual count.

	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"ACCEPT"
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
	CALL	DOLIT
	.dw	127
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

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"QUERY"
QUERY:
	CALL	TIB
	CALL	AT
	CALL	DOLIT
	.dw	TIBLENGTH                      
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

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"ABORT"
ABORT:
	CALL	PRESE
	JP	QUIT

;	abort"	( f -- )
;	Run time routine of ABORT".
;	Abort with a message.

	.dw	LINK
	
	LINK =	.
	.db	(COMPO+6)
	.ascii	"abort"
	.db 	'"
ABORQ:
	CALL	QBRAN
	.dw	ABOR2	;text flag
	CALL	DOSTR
ABOR1:	CALL	SPACE
	CALL	COUNT
	CALL	TYPES
	CALL	DOLIT
	.dw	63 ; "?"
	CALL	EMIT
	CALL	CR
	JP	ABORT	;pass error string
ABOR2:	CALL	DOSTR
	JP	DROP

;; The text interpreter

;	$INTERPRET	( a -- )
;	Interpret a word. If failed,
;	try to convert it to an integer.

	.dw	LINK
	
	LINK =	.
	.db	10
	.ascii	"$INTERPRET"
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

;	.OK	( -- )
;	Display 'ok' while interpreting.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	".OK"
DOTOK:
	CALL	DOLIT
	.dw	INTER
	CALL	TEVAL
	CALL	AT
	CALL	EQUAL
	CALL	QBRAN
	.dw	DOTO1
	CALL	DOTQP
	.db	3
	.ascii	" ok"
DOTO1:	JP	CR

;	?STACK	( -- )
;	Abort if stack underflows.

	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"?STACK"
QSTAC:
	CALL	DEPTH
	CALL	ZLESS	;check only for underflow
	CALL	ABORQ
	.db	11
	.ascii	" underflow "
	RET

;	EVAL	( -- )
;	Interpret	input stream.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"EVAL"
EVAL:
EVAL1:	CALL	TOKEN
	CALL	DUPP
	CALL	CAT	;?input stream empty
	CALL	QBRAN
	.dw	EVAL2
	CALL	TEVAL
	CALL	ATEXE
	CALL	QSTAC	;evaluate input, check stack
	CALL	BRAN
	.dw	EVAL1
EVAL2:	CALL	DROP
	JP	DOTOK

;	PRESET	( -- )
;	Reset data stack pointer and
;	terminal input buffer.

	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"PRESET"
PRESE:
	CALL	DOLIT
	.dw	SPP
	CALL	SPSTO
	CALL	DOLIT
	.dw	TIBB
	CALL	TIB
	JP	STORE    ; TIB

;	QUIT	( -- )
;	Reset return stack pointer
;	and start text interpreter.

	.dw	LINK
	
	LINK =	.
	.db	4
	.ascii	"QUIT"
QUIT:
	CALL	DOLIT
	.dw	RPP
	CALL	RPSTO	;reset return stack pointer
QUIT1:	CALL	LBRAC	;start interpretation
QUIT2:	CALL	QUERY	;get input
	CALL	EVAL
	JRA	QUIT2	;continue till error

;; The compiler

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

;	ALLOT	( n -- )
;	Allocate n bytes to	code dictionary.

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
	CALL	HERE
	CALL	DUPP
	CALL	CELLP	;cell boundary
	CALL	CPP
	CALL	STORE
	JP	STORE

;	C,	( c -- )
;	Compile a byte into
;	code dictionary.

	.dw	LINK
	
	LINK =	.
	.db	2
	.ascii	"C,"
CCOMMA:
	CALL	HERE
	CALL	DUPP
	CALL	ONEP
	CALL	CPP
	CALL	STORE
	JP	CSTOR

;	[COMPILE]	( -- ; <string> )
;	Compile next immediate
;	word into code dictionary.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+9)
	.ascii	"[COMPILE]"
BCOMP:
	CALL	TICK
	JP	JSRC

;	COMPILE ( -- )
;	Compile next jsr in
;	colon list to code dictionary.

	.dw	LINK
	
	LINK =	.
	.db	(COMPO+7)
	.ascii	"COMPILE"
COMPI:
	CALL	RFROM
	CALL	ONEP
	CALL	DUPP
	CALL	AT
	CALL	JSRC	;compile subroutine
	CALL	CELLP
	JP	TOR

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

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	'$,"'
STRCQ:
	CALL	DOLIT
	.dw	34	; "
	CALL	PARSE
	CALL	HERE
	CALL	PACKS	;string to code dictionary
	CALL	COUNT
	CALL	PLUS	;calculate aligned end of string
	CALL	CPP
	JP	STORE

;; Structures

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
	CALL	COMPI
	CALL	BRAN
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
	CALL	COMPI
	CALL	BRAN
	CALL	HERE
	CALL	ZERO
	CALL	COMMA
	CALL	SWAPP
	CALL	HERE
	CALL	SWAPP
	JP	STORE

;	AHEAD	( -- A )
;	Compile a forward branch instruction.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+5)
	.ascii	"AHEAD"
AHEAD:
	CALL	COMPI
	CALL	BRAN
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
	CALL	COMPI
	CALL	QBRAN
	CALL	HERE
	CALL	ZERO
	CALL	COMMA
	JP	SWAPP

;	REPEAT	( A a -- )
;	Terminate a BEGIN-WHILE-REPEAT indefinite loop.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+6)
	.ascii	"REPEAT"
REPEA:
	CALL	COMPI
	CALL	BRAN
	CALL	COMMA
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

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+2)
	.ascii	'$"'
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

;; Name compiler

;	?UNIQUE ( a -- a )
;	Display a warning message
;	if word already exists.

	.dw	LINK
	
	LINK =	.
	.db	7
	.ascii	"?UNIQUE"
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

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"$,n"
SNAME:
	CALL	DUPP
	CALL	CAT	;?null input
	CALL	QBRAN
	.dw	PNAM1
	CALL	UNIQU	;?redefinition
	CALL	DUPP
	CALL	COUNT
	CALL	PLUS
	CALL	CPP
	CALL	STORE
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

;; FORTH compiler

;	$COMPILE	( a -- )
;	Compile next word to
;	dictionary as a token or literal.

	.dw	LINK
	
	LINK =	.
	.db	8
	.ascii	"$COMPILE"
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

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"OVERT"
OVERT:
	CALL	LAST
	CALL	AT
	CALL	CNTXT
	JP	STORE

;	;	( -- )
;	Terminate a colon definition.

	.dw	LINK
	
	LINK =	.
	.db	(IMEDD+COMPO+1)
	.ascii	";"
SEMIS:
	CALL	COMPI
	CALL	EXIT
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
	.db	4
	.ascii	"CALL,"
JSRC:
	CALL	DOLIT
	.dw	CALLL	;CALL
	CALL	CCOMMA
	JP	COMMA

;	:	( -- ; <string> )
;	Start a new colon definition
;	using next word as its name.

	.dw	LINK
	
	LINK =	.
	.db	1
	.ascii	":"
COLON:
	CALL	TOKEN
	CALL	SNAME
	JP	RBRAC

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

;; Defining words

;	CREATE	( -- ; <string> )
;	Compile a new array
;	without allocating space.

	.dw	LINK
	
	LINK =	.
	.db	6
	.ascii	"CREATE"
CREAT:
	CALL	TOKEN
	CALL	SNAME
	CALL	OVERT
	CALL	COMPI
	CALL	DOVAR
	RET

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

;; Tools

;	_TYPE	( b u -- )
;	Display a string. Filter
;	non-printing characters.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"_TYPE"
UTYPE:
	CALL	TOR	;start count down loop
	JRA	UTYP2	;skip first pass
UTYP1:	CALL	DUPP
	CALL	CAT
	CALL	TCHAR
	CALL	EMIT	;display only printable
	CALL	ONEP	;increment address
UTYP2:	CALL	DONXT
	.dw	UTYP1	;loop till done
	JP	DROP

;	dm+	( a u -- a )
;	Dump u bytes from ,
;	leaving a+u on	stack.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	"dm+"
DUMPP:
	CALL	OVER
	CALL	DOLIT
	.dw	4
	CALL	UDOTR	;display address
	CALL	SPACE
	CALL	TOR	;start count down loop
	JRA	PDUM2	;skip first pass
PDUM1:	CALL	DUPP
	CALL	CAT
	CALL	DOLIT
	.dw	3
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
	CALL	DOLIT
	.dw	16
	CALL	SLASH	;change count to lines
	CALL	TOR	;start count down loop
DUMP1:	CALL	CR
	CALL	DOLIT
	.dw	16
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

;	>NAME	( ca -- na | F )
;	Convert code address
;	to a name address.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	">NAME"
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
TNAM3:	CALL	SWAPP
	JP	DROP
TNAM4:	CALL	DDROP
	JP	ZERO

;	.ID	( na -- )
;	Display	name at address.

	.dw	LINK
	
	LINK =	.
	.db	3
	.ascii	".ID"
DOTID:
	CALL	QDUP	;if zero no name
	CALL	QBRAN
	.dw	DOTI1
	CALL	COUNT
	CALL	DOLIT
	.dw	0x01F
	CALL	ANDD	;mask lexicon bits
	JP	UTYPE
DOTI1:	CALL	DOTQP
	.db	9
	.ascii	" (noName)"
	RET

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

;	WORDS	( -- )
;	Display names in vocabulary.

	.dw	LINK
	
	LINK =	.
	.db	5
	.ascii	"WORDS"
WORDS:
	CALL	CR
	CALL	CNTXT	;only in context
WORS1:	CALL	AT
	CALL	QDUP	;?at end of list
	CALL	QBRAN
	.dw	WORS2
	CALL	DUPP
	CALL	SPACE
	CALL	DOTID	;display a name
	CALL	CELLM
	CALL	BRAN
	.dw	WORS1
	CALL	DROP
WORS2:	RET

	
;	
;===============================================================

;; tg9541 additions

;	I	( -- n )
;	Get inner FOR - NEXT index
	.dw	LINK

	LINK =	.
	.db	(1)
	.ascii	"I"
IGET:
	SUBW    X,#2        
	LDW     Y,(3,SP)
        LDW     (X),Y
        RET


;	BSR ( t a b -- )
;	Set/RESET bit# b (0..7) at address a to bool t
;       Creates/executes BSER/BRES + RET on data stack  
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
        JRNE    $1              ; b!=0: BSET
        INC     A               ; b==0: BRES
$1:     LD      (1,X),A
        LD      A,#0x81         ; Opcode RET
        LD      (4,X),A
        LDW     Y,X
        ADDW    X,#6
        JP      (Y)


;	0=	( n -- t )
;	Return true if n is equal to 0
	.dw	LINK
	
        LINK =	.
	.db	(2)
	.ascii	"0="
ZEQS:
	LDW     Y,X
        LDW     Y,(Y)
        JREQ    1$
        CLRW    Y
        JRT     2$        
1$:     CPLW    Y
2$:     LDW     (X),Y
        RET


;       2C!  ( n b -- )
;       Store word C-wise to 16 bit HW registers 
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
;       Fetch word C-wise from 16 bit HW config. registers 
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


;       ULCK  ( -- )
;       Unlock EEPROM (STM8S)
	.dw	LINK
        
        LINK =  .
	.db	(4)
	.ascii	"ULCK"
UNLOCK:
        MOV     FLASH_DUKR,#0xAE
        MOV     FLASH_DUKR,#0x56
1$:     BTJF    FLASH_IAPSR,#3,1$    ; PM0051 4.1 requires polling bit3=1 before writing
        RET


;       LCK  ( -- )
;       Lock EEPROM (STM8S)
	.dw	LINK
        
        LINK =  .
	.db	(3)
	.ascii	"LCK"
LOCK:
        BRES    FLASH_IAPSR,#3
        RET

         
;-----------------------------------------------
        .ifne   MODULE_W1209

;       WKEY  ( -- n )
;       Read W1209 key value "set" (1), "+" (2), and "-" (4) as a bitfield
	.dw	LINK
        
        LINK =  .
	.db	(4)
	.ascii	"KEY@"
WKEY:   
        CALL    DOLIT
        .dw     PC_IDR
        CALL    CAT
        CALL    INVER
        CALL    DOLIT
        .dw     8
        CALL    SLASH
        CALL    DOLIT
        .dw     7
        CALL    ANDD
        RET
        .endif

        .ifne   HAS_LED7SEG
;       7S  ( -- )
;       Temporarily redirect "TYPE" to W1209 7-seg LED buffer 
;       up to end of string *after* the first non-rendered char 
	.dw	LINK
        
        LINK =  .
	.db	(2)
	.ascii	"7S"
SSEG:   
        CLRW    Y 
        LDW     LED7MSB,Y
        LDW     LED7LSB,Y
        MOV     LED7FLAG,#1     ; redirect EMIT from TYPE and SPACE
        RET

;       7S rendered chars 7-seg patterns: 
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
;       Convert char to 7-seg LED pattern, and put to W1209 display buffer
	.dw	LINK
        
        LINK =  .
	.db	(3)
	.ascii	"E7S"
EMIT7S: 
        LD      A,(1,X)         ; c to A

        CP      A,#'.'
        JREQ    E7DOT
        CP      A,#','
        JRMI    E7NOR
        CP      A,#'z'
        JRPL    E7NOR
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
        AND     A,#0x5F         ; convert to uppercase
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
        
E7NOR:
        BSET    LED7FLAG,#7     ; "TYPE" no longer calls EMIT7S after this string
E7END:
        JP      DROP


;       P7S  ( c -- )
;       Insert 7-seg pattern at left side of W1209 LED display buffer, rotate buffer left
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
        ADDW    X,#2
        RET
        .endif

        .ifne   HAS_OUTPUTS
;       OUT!  ( c -- )
;       Put c to module outputs, storing a copy in OUTPUTS  
	.dw	LINK
        
        LINK =  .
	.db	(4)
	.ascii	"OUT!"
OUTSTOR:
        LD      A,(1,X)
        LD      OUTPUTS,A
        ADDW    X,#2
        .ifne   MODULE_W1209
        RRC     A
        BCCM    PA_ODR,#3       ; W1209 relay
         .endif
        .ifne   MODULE_RELAY
        XOR     A,#0x0F
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
        RET       
        .endif


        .ifne HWREG_WORDS * (STM8S003F3 + STM8S103F3)
            .include "hwregs8s003.inc"
        .endif
        

;===============================================================

	LASTN	=	LINK	;last name defined

 	.area CODE
	.area INITIALIZER
	.area CABS (ABS)

