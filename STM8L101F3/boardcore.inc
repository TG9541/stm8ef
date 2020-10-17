; STM8L101F3P6 "Core" STM8L device dependent routine default code

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
        .ifne   HAS_BACKGROUND
        .ifne   BG_USE_TIM3
        BSET    CLK_PCKENR1,#1   ; TIM3[1]
        .else
        BSET    CLK_PCKENR1,#0   ; TIM2[0]
        .endif
        .endif

        .ifne   HAS_TXUART
        ; Clock init: enable USART clock
        BSET    CLK_PCKENR1,#5  ; Enable USART1 clock
        ; Board I/O for UART: enable USART push/pull (careful with STM8L001J3!)
;        BSET    PC_DDR,#3        ; TX->PC3, RX->PC2
;        BSET    PC_CR1,#3
        .endif
        RET
