; DCDC STM8S device dependent HW routines


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

        CALL    PRESE           ; initialize data stack, TIB

        DoLitW  1000
        CALL    INITPWM

        CALL    ZERO
        JP      PWMM

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
        RamWord TIMSERIAL       ; Timer: use PC7 for serial while > 0
        RamByte BKEYLMPX        ; status of board keys

;       LED_MPX driver ( -- )
;       Output bit pattern in A to 7S-LED digit hardware
LED_MPX:

;       PD1/SWIM dual use as SWIM and as segment C
;       enable use as SWIM when segment C is inactive
        BRES    PD_DDR,#1       ; port PD1=SWIM to input

;       PNRX=PC7 dual use for simulated serial port and segment DP
;       disaable DP while the simulated COM port is active (with time delay)

        TNZ     TIM4TCNT        ; active sim COM: disable DP for some time
        JREQ    LMPX1
        MOV     TIMSERIAL,#(60000/256); load MSB msec ticker
LMPX1:
        LDW     X,TIMSERIAL     ; decrement COM use timer
        JREQ    LMPX3           ; no COM: use DP
        DECW    X               ; active COM: don't change PNRX properties
        LDW     TIMSERIAL,X

LMPX3:
        BSET    PA_ODR,#3       ; Digit .3..
        BSET    PD_ODR,#6       ; Digit ..2.
        BSET    PD_ODR,#5       ; Digit ...1

        LD      A,TICKCNT+1
        AND     A,#0x03         ; 3 digits MPX
        LD      YL,A
        CLRW    X
        LD      XL,A
        LD      A,(LED7LAST-2,X)
        EXG     A,YL
        JREQ    LMPXSEGS

        TNZ     A
        JRNE    1$
        BRES    PA_ODR,#3       ; digit .3..
        JRA     LMPXSEGS

1$:     CP      A,#1
        JRNE    2$
        BRES    PD_ODR,#6       ; digit ..2.
        JRA     LMPXSEGS

2$:     CP      A,#2
        JRNE    LMPXKEY
        BRES    PD_ODR,#5       ; digit ...1
        ; fall through

LMPXSEGS:
        LD      A,YL           ; 8 bit LED pattern
        TNZ     TIMSERIAL
        JREQ    1$
        CP      A,#0x40        ; compare patter with sign ("-", segment G set)
        JRNE    1$
        OR      A,#0x02        ; set one more segment, or else COM simulation won't work

1$:
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

;       handle DP / sim. COM port
        TNZ     TIMSERIAL
        JRNE    LMPXEXIT

        RRC     A
        JRC     LMPXDP
        BRES    PSIM+DDR,#PNRX  ; DP off: port to input
        BSET    PSIM+CR2,#PNRX  ; enable PNRX external interrupt
        JRA     LMPXEXIT
LMPXDP:
        BRES    PSIM+CR2,#PNRX  ; disable PNRX external interrupt
        BSET    PSIM+DDR,#PNRX  ; serial interface port to output
        BSET    PSIM+ODR,#PNRX  ; use port for 7S-LED
        JRA     LMPXEXIT

LMPXKEY:
        ; pressing a board key connects the segment E or G to GND
        ; pre-load GPIO - the weak pull-up isn't fast enough
        ; Keys "IN" (1), "OUT" (2)
        BSET    PD_ODR,#2       ; key "OUT"
        BRES    PD_DDR,#2
        BTJT    PD_IDR,#2,1$
1$:     RLC     A
        BRES    PD_ODR,#2
        BSET    PD_DDR,#2
        BSET    PC_ODR,#5       ; key "IN"
        BRES    PC_DDR,#5
        BTJT    PC_IDR,#5,2$
2$:     RLC     A
        BRES    PC_ODR,#5
        BSET    PC_DDR,#5
        CPL     A
        AND     A,#0x03
        LD      BKEYLMPX,A      ; status of board keys
        ; fall through

LMPXEXIT:
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
        CPL     A
        RRC     A
        BCCM    PB_ODR,#4       ; DCDC LED out (or LM2596 !ON/OFF)
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
        LD      A,BKEYLMPX      ; status of board keys from LMPXKEY
        JP      ASTOR

;       BKEYC  ( -- c )   ( TOS STM8: -- A,Z,N )
;       Read and translate board dependent key bitmap into char

BKEYCHAR:
        CALLR   BKEY
        JREQ    1$
        ADD     A,#'@' ; map keys to 'A' (IN), 'B' (OUT) or 'C' (IN+OUT)
        LD      (1,X),A
1$:     RET
       .endif

;       INITPWM  ( n -- )
;       set DCDC bias PWM (e.g. 1000)
        .dw     LINK

        LINK =  .
        .db     (7)
        .ascii  "INITPWM"
INITPWM:
        DOLitW  TIM1_ARRH
        CALL    DCSTOR
        CALL    ONE
        MOV     TIM1_CCER2,#1
        MOV     TIM1_BKR,#0x80
        MOV     TIM1_CCMR3,#0x60
        MOV     TIM1_CR1,#1
        RET

;       PWM  ( n -- )
;       set DCDC bias PWM (e.g 0..999)
        .dw     LINK

        LINK =  .
        .db     (3)
        .ascii  "PWM"
PWMM:
        DoLitW  TIM1_CCR3H
        JP      DCSTOR


