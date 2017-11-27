; XH-W1219 STM8S device dependent HW routines


;       BOARDINIT  ( -- )
;       Init board GPIO (except COM ports)
BOARDINIT:
        ; Board I/O initialization

        ; W1219 STM8S003F3 init GPIO
        MOV     PA_DDR,#0b00001000 ; ----rkk-    k:key
        MOV     PA_CR1,#0b00001110 ; -----sp- 

        MOV     PB_DDR,#0b00010000 ; ---6---- 
        MOV     PB_CR1,#0b00010000 ; ---6---- 

        MOV     PC_DDR,#0b11111000 ; 12345--- 
        MOV     PC_CR1,#0b11111000 ; 12345--- 

        MOV     PD_DDR,#0b00011110 ; -k-lcds-  l:led c:SRclk d:SRdata s:serialInterface 
        MOV     PD_CR1,#0b01011110 ; -m----i- 
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

SEGSTAB:  
        .db  0x01,0x10,0x40,0x04,0x08,0x80,0x20,0x02

;       LED_MPX driver ( -- )
;       Code called from ISR for LED MPX

LED_MPX:
;       turn off all digits
        MOV     PC_ODR,#0xF8    ; Digit 12345...
        BSET    PB_ODR,#4       ; Digit .....6..

;       Get MPX digit number
        LD      A,TICKCNT+1
        AND     A,#7            ; 6 digits MPX
        CP      A,#6
        JRUGE   LEDMPXEND

        CLRW    X
        LD      XL,A
        PUSH    A               ; digit #             
        LD      A,(LED7FIRST,X)

        PUSH    A               ; LED pattern (1,SP)
        LDW     X,#8            ; 8 rounds for mapping seg bits
        CLR     A
LEDSEGS:
        SLL     (1,SP)
        JRNC    1$
        OR      A,(SEGSTAB-1,X)
1$:     DECW    X
        JRNE    LEDSEGS
        LD      (1,SP),A


;       LED segment clock out 
LEDMPXGO:
        ; PUSH    A               ; LED pattern (2,SP)
        LD      A,#8            ; 8 clock pulses for 74HC164
        PUSH    A               ; set counter (1,SP)

        ;LD      A,PD_ODR
        ;BSET    PD_DDR,#3
7$:     SLL     (2,SP)
        BCCM    PD_ODR,#2
        BRES    PD_ODR,#3       ; 74HC164 CLK pulse
        BSET    PD_ODR,#3
        DEC     (1,SP)
        JRNE    7$

        POP     A               ; remove counter
        POP     A               ; remove LED pattern variable

;       Set active LED digit
        POP     A
        ;LD      A,XL            ; XL holds the digit number

        TNZ     A
        JRNE    1$
        BRES    PC_ODR,#7       ; Digit 1.....
        JRA     LEDMPXEND

1$:     CP      A,#1
        JRNE    2$
        BRES    PC_ODR,#6       ; Digit .2....
        JRA     LEDMPXEND

2$:     CP      A,#2
        JRNE    3$
        BRES    PC_ODR,#5       ; Digit ..3...
        JRA     LEDMPXEND

3$:     CP      A,#3
        JRNE    4$
        BRES    PC_ODR,#4       ; Digit ...4..
        JRA     LEDMPXEND

4$:     CP      A,#4
        JRNE    5$
        BRES    PC_ODR,#3       ; Digit ....5.
        JRA     LEDMPXEND

5$:     CP      A,#5
        JRNE    LEDMPXEND
        BRES    PB_ODR,#4       ; Digit .....6
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
        BCCM    PA_ODR,#3       ; W1219 relay
        RRC     A
        CCF
        BCCM    PD_ODR,#4       ; W1219 blue LED

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
        ; Keys "S" (1), "+" (2), "-" (4)
        CLR     A
        BTJT    PA_IDR,#2,1$    ; test "set"
        OR      A,#0x01
1$:     BTJT    PA_IDR,#1,2$    ; test "+"
        OR      A,#0x02
2$:     BTJT    PD_IDR,#6,3$    ; test "-"
        OR      A,#0x04
3$:     JP      ASTOR

;       BKEYC  ( -- c )   ( TOS STM8: -- A,Z,N )
;       Read and translate board dependent key bitmap into char

BKEYCHAR:
        CALLR   BKEY
        JREQ    1$
        ADD     A,#'@'
        LD      (1,X),A
1$:     RET
       .endif


