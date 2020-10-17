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

        .macro  PSET_TX PUART, TXPIN
        .ifeq   HALF_DUPLEX
        BSET    PUART+DDR,#TXPIN ; HDSEL: USART controls the data direction
        .endif
        BSET    PUART+CR1,#TXPIN
        .endm

BOARDINIT:
        ; Board I/O initialization

        .ifne   HAS_BACKGROUND
        .ifne   BG_USE_TIM3
        BSET    CLK_PCKENR1,#1   ; TIM3[1]
        .else
        BSET    CLK_PCKENR1,#0   ; TIM2[0]
        .endif
        .endif

        .ifne   HAS_TXUART
        BSET    CLK_PCKENR1,#5  ; Enable USART1 clock

        .ifeq   ALT_USART_STM8L
        ; Map USART1 to PC5[TX] and PC6[RX]
        PSET_TX PORTC, 5
        .endif

        .ifeq   (ALT_USART_STM8L-1)
        ; Map USART1 to PA2[TX] and PA3[RX]
        BSET    SYSCFG_RMPCR1,#4
        PSET_TX PORTA, 2

        .ifeq   (ALT_USART_STM8L-2)
        ; Map USART1 to PC3[TX] and PC2[RX]
        PSET_TX PORTC, 3
        .endif

        .endif
        .endif

        RET
