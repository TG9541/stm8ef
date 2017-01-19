; XH-W1209 STM8S device dependent HW routines


;       BOARDINIT  ( -- )
;       Init board GPIO (except COM ports)
BOARDINIT:
        ; Board I/O initialization

        ; W1401 STM8S003F3 init GPIO
        MOV     PA_DDR,#0b00000000 ;
        MOV     PA_CR1,#0b00000000
        MOV     PB_DDR,#0b00000000 ;
        MOV     PB_CR1,#0b00000000
        MOV     PC_DDR,#0b11111000 ; 15d32---
        MOV     PC_CR1,#0b11111000 ;
        MOV     PD_DDR,#0b00001110 ; ----46c-
        MOV     PD_CR1,#0b00001110
        RET

;===============================================================

        .ifne   HAS_LED7SEG
;       LED_MPX driver ( -- )
;       Code called from ISR for LED MPX

LED_MPX:

        BRES    PC_ODR,#7       ; Digit 1..... 
        BRES    PC_ODR,#3       ; Digit .2.... 
        BRES    PD_ODR,#3       ; Digit ..3...
        BRES    PC_ODR,#4       ; Digit ...4.. 
        BRES    PD_ODR,#2       ; Digit ....5. 
        BRES    PC_ODR,#6       ; Digit .....6 

        ;CP      A,#0
        JRNE    1$
        BSET    PC_ODR,#7       ; Digit 1..... 
        JRA     6$

1$:     CP      A,#1
        JRNE    2$
        BSET    PC_ODR,#3       ; Digit .2.... 
        JRA     6$

2$:     CP      A,#2
        JRNE    3$
        BSET    PD_ODR,#3       ; Digit ..3...
        JRA     6$

3$:     CP      A,#3
        JRNE    4$
        BSET    PC_ODR,#4       ; Digit ...4.. 
        JRA     6$

4$:     CP      A,#4
        JRNE    5$
        BSET    PD_ODR,#2       ; Digit ....5. 
        JRA     6$

5$:     CP      A,#5
        JRNE    LEDMPXEND 
        BSET    PC_ODR,#6       ; Digit .....6 
        ; fall through

6$:     CLRW    X
        LD      XL,A
        LD      A,(LED7LAST-5,X)
        CPL     A

        TNZ     TIM4TCNT
        JRNE    LEDMPXEND

        BRES   PD_CR2,#PNRX    ; disable PNRX external interrupt
        push    A
        LD      A,#8
        push    A

        LD     A,PD_ODR
        BSET   PD_DDR,#PNRX
7$:     SLL    (2,SP)
        BCCM   PC_ODR,#5
        BRES   PD_ODR,#PNRX
        LD     PD_ODR,A
        DEC    (1,SP)
        JRNE   7$

        BRES   PD_DDR,#PNRX
        pop    A
        pop    A
        BSET   PD_CR2,#PNRX    ; enable PNRX external interrupt

LEDMPXEND:        
        RET
        .endif

;===============================================================

        .ifne   HAS_OUTPUTS
;       OUT!  ( c -- )
;       Put c to board outputs, storing a copy in OUTPUTS
        .dw     LINK

        LINK =  .
        .db     (4)
        .ascii  "OUT!"
OUTSTOR:
        INCW    X
        LD      A,(X)
        LD      OUTPUTS,A
        INCW    X
        RRC     A
        BCCM    PA_ODR,#3       ; W1209 relay
        RET
        .endif

;===============================================================

        .ifne   HAS_KEYS
;       BKEY  ( -- c )     ( TOS STM8: -- A,Z,N )
;       Read board key state as a bitfield
        .dw     LINK

        LINK =  .
        .db     (4)
        .ascii  "BKEY"
BKEY:
        ; Keys "set" (1), "+" (2), and "-" (4) on PC.3:5
        LD      A,PC_IDR
        SLA     A
        SWAP    A
        CPL     A
        AND     A,#0x07
        JP      ASTOR

;       BKEYC  ( -- c )   ( TOS STM8: -- A,Z,N )
;       Read and translate board dependent key bitmap into char

BKEYCHAR:
        CALLR   BKEY
        JREQ    1$
        ADD     A,#'@'
        LD      (1,X),A
1$:     RET
       .endif


