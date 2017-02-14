; STM8S103F3P6 "Minimal System Board" STM8S device dependent routines


;       BOARDINIT  ( -- )
;       Init board GPIO (except COM ports)

BOARDINIT:
        ; "Nano PLC Relay board" GPIO for relay & LED
        MOV     PB_DDR,#0x10
        MOV     PC_DDR,#0x38
        MOV     PD_DDR,#0x10
        MOV     PD_CR1,#0x10

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
;       LED_MPX driver ( -- )
;       Code called from ISR for LED MPX

LED_MPX:
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
        XOR     A,#0x0F         ; C0135 Relay-4 Board
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
        ; Key "S2" port PA3 (inverted)
        LD      A,PA_IDR
        SLA     A
        SWAP    A
        CPL     A
        AND     A,#0x01
        JP      ASTOR


;       BKEYC  (  -- c )   ( TOS STM8: -- A,Z,N )
;       Read and translate board dependent key bitmap into char

BKEYCHAR:
        CALLR   BKEY
        JREQ    1$
        ADD     A,#'@'
        LD      (1,X),A
1$:     RET
       .endif

