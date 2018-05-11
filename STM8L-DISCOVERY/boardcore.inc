; STM8L152C6 "Core" STM8L device dependent routine default code

; Note: for supporting a new board create a new board configuration
;       folder with a "globconfig.inc" and a copy of this file.

;===============================================================

;       BOARDINIT  ( -- )
;       Init board GPIO (except COM ports)

; PE7 LED green
; PC7 LED blue

BOARDINIT:
        ; Board I/O initialization
        MOV     CLK_PCKENR1,#0x21   ; Enable USART1[5] and TIM2[0]
        MOV     SYSCFG_RMPCR1,#0x10 ; Map USART1 to PA2[TX] and PA3[RX]

        ; Leds init
        BSET    PE_DDR,#7 ; PE7 LED green
        BSET    PE_CR1,#7
        BSET    PC_DDR,#7 ; PC7 LED blue
        BSET    PC_CR1,#7

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
        INCW    X
        LD      A,(X)
        LD      OUTPUTS+1,A
        INCW    X
        RRC     A
        BCCM    PE_ODR,#7       ; PE7 LED green
        RRC     A
        BCCM    PC_ODR,#7       ; PC7 LED blue
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
        ; PC1 Button
        LD      A,PC_IDR
        SRL     A
        CPL     A
        AND     A,#1
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

