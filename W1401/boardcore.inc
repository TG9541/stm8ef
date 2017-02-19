; XH-W1401 STM8S device dependent HW routines


;       BOARDINIT  ( -- )
;       Init board GPIO (except COM ports)
BOARDINIT:
        ; Board I/O initialization

        ; W1401 STM8S003F3 init GPIO
        MOV     PA_DDR,#0b00000100 ; ----krk- r:relay   k:key
        MOV     PA_CR1,#0b00001110 ; ----v-^- v:stop-v  ^:stop-^

        MOV     PB_DDR,#0b00100000 ; ---gk--- g:grLED   k:key
        MOV     PB_CR1,#0b00110000 ; ----^--- ^:start-^

        MOV     PC_DDR,#0b11111000 ; 15d32--- d:SRdata
        MOV     PC_CR1,#0b11111000 ;

        MOV     PD_DDR,#0b00001110 ; -k--46c- k:key     c:SRclk
        MOV     PD_CR1,#0b01001110 ; -v------ v:start-v
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

;       turn off all digits
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
        AND     A,#7
        CP      A,#6
        JRUGE   LEDMPXEND

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
        LD      A,#8            ; 8 clock pulses for 74HC164
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
        BCCM    PA_ODR,#2       ; W1401 relay and red LED
        RRC     A
        CCF
        BCCM    PB_ODR,#5       ; W1401 green LED

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
        ; Keys "start ^" (1), "start v" (2), "stop ^" (4), "stop v" (8)
        CLR     A
        BTJT    PB_IDR,#4,1$    ; test "start ^"
        OR      A,#0x01
1$:     BTJT    PD_IDR,#6,2$    ; test "start v"
        OR      A,#0x02
2$:     BTJT    PA_IDR,#1,3$    ; test "stop ^"
        OR      A,#0x04
3$:     BTJT    PA_IDR,#3,4$    ; test "stop v"
        OR      A,#0x08
4$:     JP      ASTOR

;       BKEYC  ( -- c )   ( TOS STM8: -- A,Z,N )
;       Read and translate board dependent key bitmap into char

BKEYCHAR:
        CALLR   BKEY
        JREQ    1$
        ADD     A,#'@'
        LD      (1,X),A
1$:     RET
       .endif


