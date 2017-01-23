; STM8S103F3P6 "Minimal System Board" STM8S device dependent routines


;       BOARDINIT  ( -- )
;       Init board GPIO (except COM ports)

BOARDINIT:
        ; Board I/O initialization
        BSET     PB_DDR,#5
        BSET     PB_CR1,#5

        RET


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
        LD      OUTPUTS,A
        INCW    X
        RRC     A
        CCF
        BCCM    PB_ODR,#5       ; PB5 LED
        RET
        .endif

;===============================================================

        .ifne   HAS_KEYS

;       BKEY  ( -- f )     ( TOS STM8: -- A,Z,N )
;       Read board key state as a bitfield

        .dw     LINK

        LINK =  .
        .db     (4)
        .ascii  "BKEY"
BKEY:
        CLR     A
        JP      ASTOR


;       BKEYC  (  -- c )   ( TOS STM8: -- A,Z,N )
;       Read and translate board dependent key bitmap into char

BKEYCHAR:
        JRA     BKEY            ; Dummy: get "no key" and leave it as it is

       .endif

