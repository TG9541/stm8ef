; STM8L051F3P6 "Core" STM8L device dependent routine default code

; Note: for supporting a new board create a new board configuration
;       folder with a "globconfig.inc" and a copy of this file.

; ==============================================

        .ifne   HAS_LED7SEG
;       LED_MPX driver ( -- )
;       Code called from ISR for LED MPX

LED_MPX:
        RET
        .endif

; ==============================================

        .ifne   HAS_OUTPUTS
;       OUT!  ( c -- )
;       Put c to board outputs, storing a copy in OUTPUTS
        .dw     LINK

        LINK =  .
        .db     (4)
        .ascii  "OUT!"
OUTSTOR:
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

;===============================================================

;       BOARDINIT  ( -- )
;       Init board GPIO

BOARDINIT:
        ; Board I/O initialization: enable USART TX->PA2, RX->PA3
        MOV     CLK_PCKENR1,#0x21
        .ifne HALF_DUPLEX
        BSET    PA_DDR,#2       ; HDSEL: USART controls the data direction
        .endif
        BSET    PA_CR1,#2
        MOV     SYSCFG_RMPCR1,#0x1C
        RET
