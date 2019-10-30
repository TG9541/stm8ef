; XH-W1209 STM8S device dependent HW routines


;       BOARDINIT  ( -- )
;       Init board GPIO (except COM ports)
BOARDINIT:
        ; Board I/O initialization

        ; W1209 STM8S003F3 init GPIO
        MOV     PA_DDR,#0b00001110 ; d3,d2,d1
        MOV     PA_CR1,#0b00001110
        MOV     PB_DDR,#0b00110000 ; A,F
        MOV     PB_CR1,#0b00110000
        MOV     PC_DDR,#0b11111000 ; D,DP,C,G,B
        MOV     PC_CR1,#0b11111000 ; 
        MOV     PD_DDR,#0b00000110 ; set,+,-, adc,E,relay
        MOV     PD_CR1,#0b11110111
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

        .ifne   PSIM-PORTE
;       Dummy label for _EXTIE_IRQHandler
_EXTI4_IRQHandler:
        .endif

;===============================================================

        .ifne   HAS_LED7SEG
;       LED_MPX driver ( -- )
;       Output bit pattern in A to 7S-LED digit hardware

; Common Anode display:
;   Digits - active high
;   Segments - active low

LED_MPX:
        BRES    PA_ODR,#3       ; Digit .3..
        BRES    PA_ODR,#2       ; Digit ..2.
        BRES    PA_ODR,#1       ; Digit ...1
        LD      A,TICKCNT+1
        AND     A,#0x03         ; 3 digits MPX

        JRNE    1$
        BSET    PA_ODR,#1       ; digit .3..
        JRA     3$

1$:     CP      A,#1
        JRNE    2$
        BSET    PA_ODR,#2       ; digit ..2.
        JRA     3$

2$:     CP      A,#2
        JRNE    4$
        BSET    PA_ODR,#3       ; digit ...1
        ; fall through

3$:     CLRW    X
        LD      XL,A
        LD      A,(LED7LAST-2,X)

        CPL     A               ; invert bits for active low
        ; W1209 7S LED display row
        ; bit 76543210 input (parameter A)
        ;  PB ..BF....
        ;  PC CG......
        ;  PD ..A.DPE.
        RRC     A
        BCCM    PB_ODR,#5       ; A
        RRC     A
        BCCM    PC_ODR,#3       ; B
        RRC     A
        BCCM    PC_ODR,#5       ; C
        RRC     A
        BCCM    PC_ODR,#7       ; D
        RRC	A
        BCCM    PD_ODR,#2       ; E
        RRC     A
        BCCM    PB_ODR,#4       ; F
        RRC     A
        BCCM    PC_ODR,#4       ; G
        RRC     A
        BCCM    PC_ODR,#6       ; P
4$:     RET
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
        BCCM    PD_ODR,#1       ; W1209 relay
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
        ; Keys "set" (1), "+" (2), and "-" (4) on PC.3:5 (PD 6,5,4) 
        LD      A,PD_IDR
;        SLA     A
        SWAP    A
        CPL     A
        AND     A,#0x07
        JP      ASTOR

;       BKEYC  ( -- c )   ( TOS STM8: -- A,Z,N )
;       Read and translate board dependent key bitmap into char


        .dw     LINK

        LINK =  .
        .db     (5)
        .ascii  "BKEYC"
BKEYCHAR:
        CALLR   BKEY
        JREQ    1$
        ADD     A,#'@'
        LD      (1,X),A
1$:     RET
       .endif

