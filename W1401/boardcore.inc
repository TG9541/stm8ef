; XH-W1401 STM8S device dependent HW routines


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

;      Dummy labels for PSIM interrupts declared in main.c

        .ifne   PSIM-PORTA
;       Dummy label for _EXTIA_IRQHandler
_EXTI0_IRQHandler:
        .endif

        .ifne   PSIM-PORTB
;       Dummy label for _EXTIB_IRQHandler
_EXTI1_IRQHandler:
        .endif

        .ifne   PSIM-PORTC
;       Dummy label for _EXTIC_IRQHandler
_EXTI2_IRQHandler:
        .endif

        .ifne   PSIM-PORTD
;       Dummy label for _EXTID_IRQHandler
_EXTI3_IRQHandler:
        .endif

;===============================================================

        .ifne   HAS_LED7SEG

        RamByte TIMSERIAL       ; Timer: use PD1 for serial while > 0

;       LED_MPX driver ( -- )
;       Code called from ISR for LED MPX

LED_MPX:

        LD      A,#0b00100111   ; Digits 16.42...
        AND     A,PC_ODR
        LD      PC_ODR,A
        ;       PC_ODR,#7       ; Digit 1.....
        ;       PC_ODR,#3       ; Digit .2....
        BRES    PD_ODR,#3       ; Digit ..3...
        ;       PC_ODR,#4       ; Digit ...4..
        BRES    PD_ODR,#2       ; Digit ....5.
        ;       PC_ODR,#6       ; Digit .....6

        LD      A,TICKCNT+1
        AND     A,#HAS_LED7SEG

; 6$:
        CLRW    X
        LD      XL,A
        LD      A,(LED7LAST-5,X)
        CPL     A

        TNZ     TIM4TCNT
        JREQ    1$
        MOV     TIMSERIAL,#0xFF
        JRNE    LEDMPXEND
1$:     TNZ     TIMSERIAL
        JREQ    LEDMPXGO
        DEC     TIMSERIAL
        JRA     LEDMPXEND

;       LED segment clock out while PD1/SWIM is not used as UART 
LEDMPXGO:
        BRES    PD_CR2,#PNRX    ; disable PNRX external interrupt
        PUSH    A               ; LED pattern (2,SP)
        LD      A,#8
        PUSH    A               ; set counter (1,SP)

        LD      A,PD_ODR
        BSET    PD_DDR,#PNRX
7$:     SLL     (2,SP)
        BCCM    PC_ODR,#5
        BRES    PD_ODR,#PNRX    ; reset 74HC164 CLK (shared with PNRX)
        LD      PD_ODR,A        ; 1 cycle CLK pulse w/ old PD_ODR value in A
        DEC     (1,SP)
        JRNE    7$

        BRES    PD_DDR,#PNRX
        BSET    PD_CR2,#PNRX    ; enable PNRX external interrupt
        POP     A               ; remove counter
        POP     A               ; remove LED pattern variable

;       Set active LED digit
        LD      A,XL            ; XL holds the digit number
        TNZ     A

        JRNE    1$
        BSET    PC_ODR,#7       ; Digit 1.....
        JRA     LEDMPXEND

1$:     CP      A,#1
        JRNE    2$
        BSET    PC_ODR,#3       ; Digit .2....
        JRA     LEDMPXEND

2$:     CP      A,#2
        JRNE    3$
        BSET    PD_ODR,#3       ; Digit ..3...
        JRA     LEDMPXEND

3$:     CP      A,#3
        JRNE    4$
        BSET    PC_ODR,#4       ; Digit ...4..
        JRA     LEDMPXEND

4$:     CP      A,#4
        JRNE    5$
        BSET    PD_ODR,#2       ; Digit ....5.
        JRA     LEDMPXEND

5$:     CP      A,#5
        JRNE    LEDMPXEND
        BSET    PC_ODR,#6       ; Digit .....6
        ; fall through

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
        LD      OUTPUTS+1,A
        INCW    X
        RRC     A
        BCCM    PA_ODR,#3       ; W1401 relay
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


