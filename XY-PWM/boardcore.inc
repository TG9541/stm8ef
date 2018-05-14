; XY-PWM/HW-0515 STM8S device dependent HW routines


;       BOARDINIT  ( -- )
;       Init board GPIO (except COM ports)
BOARDINIT:
        ; Board I/O initialization

        ; HW-0515 STM8S003F3 init GPIO
        MOV     PA_ODR,#0b00000010
        MOV     PA_CR1,#0b00000100 ; 
        MOV     PA_DDR,#0b00000110 ; PA1 cat3, PA2 seg e/set

        MOV     PB_ODR,#0b00110000
        MOV     PB_CR1,#0b00000000 ; 
        MOV     PB_DDR,#0b00110000 ; PB4 cat2, PB5 cat1

        MOV     PC_CR1,#0b11110000 ; 
        MOV     PC_DDR,#0b11110000 ; PC3 pwm2, PC4 seg g/up, PC5 seg c, PC6 seg h/down, PC7 seg d

        MOV     PD_CR1,#0b00010110 ; 
        MOV     PD_DDR,#0b00010110 ; PD1 seg f, PD2 seg b, PD3 pwm1, PD4 a, PD5 UTX, PD6 URX
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
;       Code called from ISR for LED MPX

LED_MPX:
;       turn off all digits
        BSET    PA_ODR,#1       ; Digit .3..
        BSET    PB_ODR,#4       ; Digit ..2.
        BSET    PB_ODR,#5       ; Digit ...1

        .ifne   HAS_KEYS
;       Read keys
        BSET    PA_ODR,#2       ; Set  [PA2]
        BSET    PC_ODR,#4       ; Up   [PC4]
        BSET    PC_ODR,#6       ; Down [PC6]

        BRES    PA_DDR,#2       ; Set  [PA2]
        BRES    PC_DDR,#4       ; Up   [PC4]
        BRES    PC_DDR,#6       ; Down [PC6]

        ; Keys "S" (1), "+" (2), "-" (4)
        CLR     A
        BTJT    PA_IDR,#2,5$    ; test "set"
        OR      A,#0x01
5$:     BTJT    PC_IDR,#4,6$    ; test "up"
        OR      A,#0x02
6$:     BTJT    PC_IDR,#6,7$    ; test "down"
        OR      A,#0x04
7$:     LD      KEY_STORAGE, A
        BSET    PA_DDR,#2       ; Set  [PA2]
        BSET    PC_DDR,#4       ; Up   [PC4]
        BSET    PC_DDR,#6       ; Down [PC6]
        .endif

; Display
        LD      A,TICKCNT+1
        AND     A,#0x03         ; 3 digits MPX

        JRNE    1$
        BRES    PA_ODR,#1       ; digit .3..
        JRA     3$

1$:     CP      A,#1
        JRNE    2$
        BRES    PB_ODR,#4       ; digit ..2.
        JRA     3$

2$:     CP      A,#2
        JRNE    4$
        BRES    PB_ODR,#5       ; digit ...1
        ; fall through

3$:     CLRW    X
        LD      XL,A
        LD      A,(LED7LAST-2,X)

        ; W1209 7S LED display row
        ; bit 76453210 input (parameter A)
        ;  PA .....FB.
        ;  PC CG......
        ;  PD ..A.DPE.
        RRC     A
        BCCM    PD_ODR,#4       ; A
        RRC     A
        BCCM    PD_ODR,#2       ; B
        RRC     A
        BCCM    PC_ODR,#5       ; C
        RRC     A
        BCCM    PC_ODR,#7       ; D
        RRC     A
        BCCM    PA_ODR,#2       ; E
        RRC     A
        BCCM    PD_ODR,#1       ; F
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
        ; BCCM    PA_ODR,#3       ; W1219 relay
        RRC     A
        CCF
        ; BCCM    PD_ODR,#4       ; W1219 blue LED

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
        LD      A, KEY_STORAGE
        JP      ASTOR

;       BKEYC  ( -- c )   ( TOS STM8: -- A,Z,N )
;       Read and translate board dependent key bitmap into char

BKEYCHAR:
        CALLR   BKEY
        JREQ    1$
        ADD     A,#'@'
        LD      (1,X),A
1$:     RET

        ; Keys storage
        RamByte KEY_STORAGE
       .endif


