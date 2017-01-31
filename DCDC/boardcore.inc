; XH-W1209 STM8S device dependent HW routines


;       BOARDINIT  ( -- )
;       Init board GPIO (except COM ports)
BOARDINIT:
        ; Board I/O initialization

        ; DCDC STM8S003F3 init GPIO
        MOV     PA_DDR,#0b00001110 ; ----3AF-
        MOV     PA_CR1,#0b00001110
        MOV     PB_DDR,#0b00010000 ; --.o---- PB4:LEDout
        MOV     PB_CR1,#0b00010000
        MOV     PC_DDR,#0b11101000 ; PDE.i--- PC3:LEDin PC4:Vin PC5:E/keyIn
        MOV     PC_CR1,#0b11101000
        MOV     PD_DDR,#0b01110110 ; -21B.GC- PD2:G/keyOut PD3:Vout
        MOV     PD_CR1,#0b01110110
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

        RamWord TIMSERIAL       ; Timer: use PC7 for serial while > 0
        .ifne   HAS_LED7SEG

;       LED_MPX driver ( -- )
;       Output bit pattern in A to 7S-LED digit hardware
LED_MPX:

;       PD1/SWIM dual use as SWIM and as segment C
;       enable use as SWIM when segment C is off

        BRES    PD_DDR,#1       ; port PD1=SWIM to input

;       PNRX=PC7 dual use for simulated serial port and DP
;       When using as DP: enable COM interrupt while DP is off

        TNZ     TIM4TCNT        ; active sim COM: disable DP for 1 minute
        JREQ    LMPX1
        MOV     TIMSERIAL,#(60000/256)
LMPX1:
        LDW     X,TIMSERIAL     ; decrement COM use timer
        JREQ    LMPX2           ; no COM: use DP
        DECW    X               ; active COM: don't change PNRX properties
        LDW     TIMSERIAL,X
        JRA     LMPX3
LMPX2:
        BRES    PC_DDR,#7       ; DP off: port to input
        BSET    PC_CR2,#7       ; enable PNRX external interrupt

LMPX3:
        BSET    PA_ODR,#3       ; Digit .3..
        BSET    PD_ODR,#6       ; Digit ..2.
        BSET    PD_ODR,#5       ; Digit ...1

        LD      A,TICKCNT+1
        AND     A,#HAS_LED7SEG
        JRNE    1$
        BRES    PA_ODR,#3       ; digit .3..
        JRA     3$

1$:     CP      A,#1
        JRNE    2$
        BRES    PD_ODR,#6       ; digit ..2.
        JRA     3$

2$:     CP      A,#2
        JRNE    4$
        BRES    PD_ODR,#5       ; digit ...1
        ; fall through

3$:     CLRW    X
        LD      XL,A
        LD      A,(LED7LAST-2,X)

        ; DCDC 7S LED display row
        ; bit 76453210 input (parameter A)
        ;  PA -----AF-
        ;  PC PDE-----
        ;  PD ---B-GC-
        RRC     A
        BCCM    PA_ODR,#2       ; A
        RRC     A
        BCCM    PD_ODR,#4       ; B

        RRC     A
        JRNC    5$
        BSET    PD_DDR,#1       ; C is active: PD1=SWIM to output
        BSET    PD_ODR,#1
5$:
        RRC     A
        BCCM    PC_ODR,#6       ; D
        RRC     A
        BCCM    PC_ODR,#5       ; E
        RRC     A
        BCCM    PA_ODR,#1       ; F
        RRC     A
        BCCM    PD_ODR,#2       ; G
        RRC     A
        JRNC    4$
        TNZ     TIMSERIAL
        JRNE    4$
        BRES    PC_CR2,#7       ; disable PNRX external interrupt
        BSET    PC_DDR,#7       ; port to output
        BSET    PC_ODR,#7       ; P

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
        CPL     A
        RRC     A
        BCCM    PC_ODR,#3       ; DCDC LED in
        RRC     A
        BCCM    PB_ODR,#4       ; DCDC LED out
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

