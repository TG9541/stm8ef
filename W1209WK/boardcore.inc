; DCDC STM8S device dependent HW routines


;       BOARDINIT  ( -- )
;       Init board GPIO (except COM ports)
BOARDINIT:
        ; Board I/O initialization

        ; DCDC STM8S003F3 init GPIO
        MOV     PA_DDR,#0b00001110 ; ----3rb-
        MOV     PA_CR1,#0b00001110 ;     ree
        MOV     PB_DDR,#0b00110000 ; --21----
        MOV     PB_CR1,#0b00110000 ;   rr
        MOV     PC_DDR,#0b11111000 ; CGBFA--- PC7:SET
        MOV     PC_CR1,#0b11111000 ; s
        MOV     PD_DDR,#0b01111110 ; -321EDD- PD3:ain PD1:C/F
        MOV     PD_CR1,#0b01111110 ;  bbba P

        JP      PRESE              ; initialize data stack, TIB


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
        RamWord ADCSENS         ; Sensor header ADC read in-phase with MPX
        RamWord TIMSERIAL       ; Timer: use PC7 for serial while > 0
        RamByte BKEYLMPX        ; status of board keys

;       LED MPX key reader ( -- )
LMPXKEY:
        ; pressing a front panel key pulls a segment GPIO low
        ; two-pass operation because of slow settling time

        JRNE    LMPXREADKEY     ; N flag is (MPX value)==6
        ; MPX == 6

        ; prepare reading the front panel keys
        BRES    PC_DDR,#7       ; key "SET": seg C off, PC7 to input
        BRES    PD_DDR,#1       ; key "C/F": seg DP off, PD1 to input

        ; prepare reading the sensor input
        BRES    PD_DDR,#3       ; Sensor: seg E off, PD3 to input
        MOV     ADC_CSR,#4      ; select Ain4 (PD3)
        BSET    ADC_CR2,#3      ; align ADC to LSB
        BSET    ADC_CR1,#0      ; enable ADC

        RET

LMPXREADKEY:
        ; MPX == 7

        ; read the sensor input
        BRES    ADC_CSR,#7      ; reset EOC
        BSET    ADC_CR1,#0      ; start ADC
0$:     BTJF    ADC_CSR,#7,0$   ; wait until EOC
        LDW     Y,ADC_DRH       ; read ADC
        LDW     ADCSENS,Y
        MOV     ADC_CSR,#0      ; deselect Ain4 (enable PD3)
        BSET    PD_DDR,#3       ; Seg E: PD3 to output

        ; Keys "SET" (1), "C/F" (2)
        BTJF    PC_IDR,#7,1$    ; key "SET"
1$:     CCF
        BCCM    BKEYLMPX,#0
        BSET    PC_DDR,#7       ; restore seg C GPIO

        BTJF    PD_IDR,#1,2$    ; key "C/F"
2$:     CCF
        BCCM    BKEYLMPX,#1
        JRNC    4$              ; key not pressed?

        TNZ     TIM4TCNT
        JRNE    4$              ; serial COM active
        CLRW    X
        LDW     TIMSERIAL,X     ; enforce COM non-active
4$:
LMPXEXITKEY:
        ; fall through

        RET


;       LED_MPX driver ( -- )
;       Output bit pattern in A to 7S-LED digit hardware
LED_MPX:
;       beeper 500Hz hack
        BTJF    OUTPUTS+1,#1,1$
        BCPL    PA_ODR,#1
1$:

;       Reset all digit MPX outputs
        BSET    PA_ODR,#3       ; Digit 3..... red
        BSET    PB_ODR,#5       ; Digit .2.... red
        BSET    PB_ODR,#4       ; Digit ..1... red
        BSET    PD_ODR,#6       ; Digit ...3.. blue
        BSET    PD_ODR,#5       ; Digit ....2. blue
        BSET    PD_ODR,#4       ; Digit .....1 blue

;       PNRX=PD1 dual use for simulated serial port and segment DP
;       disable DP while the simulated COM port is active (with time delay)

        TNZ     TIM4TCNT        ; active sim COM: disable DP for some time
        JRPL    NORECEIVE
        MOV     TIMSERIAL,#(6000/256); load MSB msec ticker
        JRA     LMPX1
NORECEIVE:
        JREQ    LMPX1
        MOV     TIMSERIAL,#(10000/256); load MSB msec ticker
LMPX1:
        LDW     X,TIMSERIAL     ; decrement COM use timer
        JREQ    LMPX3           ; no COM: use DP
        DECW    X               ; active COM: don't change PNRX properties
        LDW     TIMSERIAL,X
        CPW     X,#5000
        JRUGT   LMPXEXITKEY
LMPX3:
;       Get MPX digit number
        CLRW    X               ; clear index/segments
        LD      A,TICKCNT+1
        AND     A,#7            ; 6 digits MPX
        CP      A,#6
        JRULT   0$
        JP      LMPXKEY         ; use MPX scan gap for COM & Key
0$:
        LD      XL,A
        LD      A,(LED7FIRST,X)
        EXG     A,XL            ; A contains MPX index, XL segments data
        JREQ    LMPXSEGS

        TNZ     A
        JRNE    1$
        BRES    PA_ODR,#3       ; digit 3.....
        JRA     LMPXSEGS

1$:     CP      A,#1
        JRNE    2$
        BRES    PB_ODR,#5       ; digit .2....
        JRA     LMPXSEGS

2$:     CP      A,#2
        JRNE    3$
        BRES    PB_ODR,#4       ; digit ..1...
        JRA     LMPXSEGS

3$:     CP      A,#3
        JRNE    4$
        BRES    PD_ODR,#6       ; Digit ...3..
        JRA     LMPXSEGS

4$:     CP      A,#4
        JRNE    5$
        BRES    PD_ODR,#5       ; Digit ....2.
        JRA     LMPXSEGS

5$:     CP      A,#5
        JRNE    LMPXEXIT
        BRES    PD_ODR,#4       ; Digit .....1
        ; fall through

LMPXSEGS:
        LD      A,TIMSERIAL
        JREQ    LMPXNOCOM


;       handle DP / sim. COM port
LMPXXOUT:

        LD      A,XL

        ; 8 bit LED pattern
        RLC     A
        JRC     LMPXDP
        BRES    PD_DDR,#1  ; DP off: port to input
        BSET    PD_CR2,#1       ; enable PNRX external interrupt
        JRA     LMPXREST
LMPXDP:
        BRES    PD_CR2,#1       ; disable PNRX external interrupt
        BSET    PD_DDR,#1       ; serial interface port to output
        BSET    PD_ODR,#1       ; use port for 7S-LED
        JRA     LMPXREST

;       Use DP normally
LMPXNOCOM:
        LD      A,XL            ; 8 bit LED pattern
        RLC     A
        BCCM    PD_ODR,#1       ; DP
        BSET    PD_DDR,#1       ; serial interface port to output
        ; fall through

LMPXREST:
        ; bit 76543210 input (parameter A)
        ;  PC CGBFA---
        ;  PD ----EDP-
        RLC     A
        BCCM    PC_ODR,#6       ; G
        RLC     A
        BCCM    PC_ODR,#4       ; F
        RLC     A
        BCCM    PD_ODR,#3       ; E
        RLC     A
        BCCM    PD_ODR,#2       ; D
        RLC     A
        BCCM    PC_ODR,#7       ; C
        RLC     A
        BCCM    PC_ODR,#5       ; B
        RLC     A
        BCCM    PC_ODR,#3       ; A

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
        RRC     A
        BCCM    PA_ODR,#2       ; Relay + LED out
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
        ADD     A,#'@' ; map keys to 'A' (SET), 'B' (C/F) or 'C' (both)
        LD      (1,X),A
1$:     RET
       .endif

;       ADC@  ( -- w )
;       Get in-phase ADC conversion value
        .dw     LINK

        LINK =  .
        .db     (4)
        .ascii  "ADC@"

ADCAT:
        LDW     Y,ADCSENS
        JP      YSTOR
