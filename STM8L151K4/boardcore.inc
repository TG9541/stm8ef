; STM8L152C6 "Core" STM8L device dependent routine default code

; Note: for supporting a new board create a new board configuration
;       folder with a "globconfig.inc" and a copy of this file.

;===============================================================

;       BOARDINIT  ( -- )
;       Init board GPIO (except COM ports)

        .macro  PSET_TX PUART, TXPIN
        .ifeq   HALF_DUPLEX
        BSET    PUART+DDR,#TXPIN ; HDSEL: USART controls the data direction
        .endif
        BSET    PUART+CR1,#TXPIN
        .endm

BOARDINIT:
        ; Board I/O initialization

        .ifne   HAS_BACKGROUND
        .ifne   BG_USE_TIM1
        BSET    CLK_PCKENR2,#1   ; TIM1[1]
        .else
        .ifne   BG_USE_TIM3
        BSET    CLK_PCKENR1,#1   ; TIM3[1]
        .else
        BSET    CLK_PCKENR1,#0   ; TIM2[0]
        .endif
        .endif
        .endif

        .ifne   HAS_TXUART
        BSET    CLK_PCKENR1,#5  ; Enable USART1 clock

        .ifeq   ALT_USART_STM8L
        ; Map USART1 to PC3[TX] and PC2[RX]
        PSET_TX PORTC, 3
        .endif

        .ifeq   (ALT_USART_STM8L-1)
        ; Map USART1 to PA2[TX] and PA3[RX]
        BSET    SYSCFG_RMPCR1,#4
        PSET_TX PORTA, 2
        .endif

        .ifeq   (ALT_USART_STM8L-2)
        ; Map USART1 to PC5[TX] and PC6[RX]
        BSET    SYSCFG_RMPCR1,#5
        PSET_TX PORTC, 5
        .endif
        .endif


        .ifne   HAS_OUTPUTS
        ; Leds init
        BSET    PE_DDR,#7 ; PE7 LED green
        BSET    PE_CR1,#7
        BSET    PC_DDR,#7 ; PC7 LED blue
        BSET    PC_CR1,#7
        .endif

        .ifne   HAS_LCD
        MOV     CLK_CRTCR, #0x04    ; Eanble RTC clock drived by LSI generator.
        BSET    CLK_PCKENR2, #3     ; Enable internal LCD driver
        MOV     LCD_CR1, #0x06 ; Drive method: multiplexed 1/4 duty, 1/3 bias
        MOV     LCD_CR2, #0x0E ; Contrast
        MOV     LCD_FRQ, #0x10 ; Refresh frequence
        MOV     LCD_PM0, #0xFF ; Enable SEG00..07
        MOV     LCD_PM1, #0xFF ; Enable SEG08..15
        MOV     LCD_PM2, #0xFF ; Enable SEG16..23
        MOV     LCD_CR3, #0x40 ; Enable LCD
        ; Clean LCD
        CLR     A
        CALL    LCD_FILL
        .endif

        .ifne   HAS_OUTPUTS
        CLR     A
        JRA     AOUTSTOR
        .else
        RET
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
        RamWord OUTPUTS         ; "OUT", e.g. relays, LEDs, etc. (16 bit)

;       OUT!  ( c -- )
;       Put c to board outputs, storing a copy in OUTPUTS
        .dw     LINK

        LINK =  .
        .db     (4)
        .ascii  "OUT!"
OUTSTOR:
        INCW    X
        LD      A,(X)
        INCW    X
AOUTSTOR:
        LD      OUTPUTS+1,A
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

;===============================================================
; LCD routines

        .ifne   HAS_LCD
;       LCDF  ( b -- )     ( TOS STM8: -- A,Z,N )
;       Fill (Clean) LCD buffer
        .dw     LINK

        LINK =  .
        .db     (4)
        .ascii  "LCDF"
LCDF:
        INCW    X
        LD      A, (X)
        INCW    X
LCD_FILL:
        PUSHW   X
        LDW     X, #LCD_RAM0
3$:     LD      (X), A
        INCW    X
        CPW     X, #(LCD_RAM0+HAS_LCD)
        JRNE    3$
        POPW    X
        RET

;       LCD!  ( w a -- )     ( TOS STM8: -- A,Z,N )
;       Write data w to LCD position a[0:5]
;       w bits [Cl Dp Q P N K J H M G F E D C B A]
        .dw     LINK

        LINK =  .
        .db     (4)
        .ascii  "LCD!"
LCD_STOR:
        ; Load word
        PUSHW   X
        LD      A, (#1, X)
        LDW     X, (#2, X)
        TNZ     A
        JRNE    1$
        CALLR   LCDS1
        JRA     6$
1$:
        DEC     A
        JRNE    2$
        CALLR   LCDS2
        JRA     6$
2$:
        DEC     A
        JRNE    3$
        CALL    LCDS3
        JRA     6$
3$:
        DEC     A
        JRNE    4$
        CALL    LCDS4
        JRA     6$
4$:
        DEC     A
        JRNE    5$
        CALL    LCDS5
        JRA     6$
5$:
        DEC     A
        JRNE    6$
        CALL    LCDS6
6$:
        POPW    X
        ADDW    X, #4
        RET

;       In: X [Cl Dp Q P N K J H M G F E D C B A]
LCDS1:
        SRLW    X
        BCCM    LCD_RAM0+6, #2 ; A
        SRLW    X
        BCCM    LCD_RAM0+2, #6 ; B
        SRLW    X
        BCCM    LCD_RAM0+3, #5 ; C
        SRLW    X
        BCCM    LCD_RAM0+3, #4 ; D
        SRLW    X
        BCCM    LCD_RAM0+0, #0 ; E
        SRLW    X
        BCCM    LCD_RAM0+6, #3 ; F
        SRLW    X
        BCCM    LCD_RAM0+2, #7 ; G
        SRLW    X
        BCCM    LCD_RAM0+0, #1 ; M
        SRLW    X
        BCCM    LCD_RAM0+13, #3 ; H
        SRLW    X
        BCCM    LCD_RAM0+13, #2 ; J
        SRLW    X
        BCCM    LCD_RAM0+9, #6 ; K
        SRLW    X
        BCCM    LCD_RAM0+10, #4 ; N
        SRLW    X
        BCCM    LCD_RAM0+7, #0 ; P
        SRLW    X
        BCCM    LCD_RAM0+9, #7 ; Q
        SRLW    X
        BCCM    LCD_RAM0+10, #5 ; DP
        SRLW    X
        BCCM    LCD_RAM0+7, #1 ; COLON
        RET

;       In: X [Cl Dp Q P N K J H M G F E D C B A]
LCDS2:
        SRLW    X
        BCCM    LCD_RAM0+6, #0 ; A
        SRLW    X
        BCCM    LCD_RAM0+2, #4 ; B
        SRLW    X
        BCCM    LCD_RAM0+3, #7 ; C
        SRLW    X
        BCCM    LCD_RAM0+3, #6 ; D
        SRLW    X
        BCCM    LCD_RAM0+0, #2 ; E
        SRLW    X
        BCCM    LCD_RAM0+6, #1 ; F
        SRLW    X
        BCCM    LCD_RAM0+2, #5 ; G
        SRLW    X
        BCCM    LCD_RAM0+0, #3 ; M
        SRLW    X
        BCCM    LCD_RAM0+13, #1 ; H
        SRLW    X
        BCCM    LCD_RAM0+13, #0 ; J
        SRLW    X
        BCCM    LCD_RAM0+9, #4 ; K
        SRLW    X
        BCCM    LCD_RAM0+10, #6 ; N
        SRLW    X
        BCCM    LCD_RAM0+7, #2 ; P
        SRLW    X
        BCCM    LCD_RAM0+9, #5 ; Q
        SRLW    X
        BCCM    LCD_RAM0+10, #7 ; DP
        SRLW    X
        BCCM    LCD_RAM0+7, #3 ; COLON
        RET

;       In: X [Cl Dp Q P N K J H M G F E D C B A]
LCDS3:
        SRLW    X
        BCCM    LCD_RAM0+5, #6 ; A
        SRLW    X
        BCCM    LCD_RAM0+2, #2 ; B
        SRLW    X
        BCCM    LCD_RAM0+4, #1 ; C
        SRLW    X
        BCCM    LCD_RAM0+4, #0 ; D
        SRLW    X
        BCCM    LCD_RAM0+0, #4 ; E
        SRLW    X
        BCCM    LCD_RAM0+5, #7 ; F
        SRLW    X
        BCCM    LCD_RAM0+2, #3 ; G
        SRLW    X
        BCCM    LCD_RAM0+0, #5 ; M
        SRLW    X
        BCCM    LCD_RAM0+12, #7 ; H
        SRLW    X
        BCCM    LCD_RAM0+12, #6 ; J
        SRLW    X
        BCCM    LCD_RAM0+9, #2 ; K
        SRLW    X
        BCCM    LCD_RAM0+11, #0 ; N
        SRLW    X
        BCCM    LCD_RAM0+7, #4 ; P
        SRLW    X
        BCCM    LCD_RAM0+9, #3 ; Q
        SRLW    X
        BCCM    LCD_RAM0+11, #1 ; DP
        SRLW    X
        BCCM    LCD_RAM0+7, #5 ; COLON
        RET

;       In: X [Cl Dp Q P N K J H M G F E D C B A]
LCDS4:
        SRLW    X
        BCCM    LCD_RAM0+5, #4 ; A
        SRLW    X
        BCCM    LCD_RAM0+2, #0 ; B
        SRLW    X
        BCCM    LCD_RAM0+4, #3 ; C
        SRLW    X
        BCCM    LCD_RAM0+4, #2 ; D
        SRLW    X
        BCCM    LCD_RAM0+0, #6 ; E
        SRLW    X
        BCCM    LCD_RAM0+5, #5 ; F
        SRLW    X
        BCCM    LCD_RAM0+2, #1 ; G
        SRLW    X
        BCCM    LCD_RAM0+0, #7 ; M
        SRLW    X
        BCCM    LCD_RAM0+12, #5 ; H
        SRLW    X
        BCCM    LCD_RAM0+12, #4 ; J
        SRLW    X
        BCCM    LCD_RAM0+9, #0 ; K
        SRLW    X
        BCCM    LCD_RAM0+11, #2 ; N
        SRLW    X
        BCCM    LCD_RAM0+7, #6 ; P
        SRLW    X
        BCCM    LCD_RAM0+9, #1 ; Q
        SRLW    X
        BCCM    LCD_RAM0+11, #3 ; DP
        SRLW    X
        BCCM    LCD_RAM0+7, #7 ; COLON
        RET

;       In: X [Cl Dp Q P N K J H M G F E D C B A]
LCDS5:
        SRLW    X
        BCCM    LCD_RAM0+5, #2 ; A
        SRLW    X
        BCCM    LCD_RAM0+1, #6 ; B
        SRLW    X
        BCCM    LCD_RAM0+4, #5 ; C
        SRLW    X
        BCCM    LCD_RAM0+4, #4 ; D
        SRLW    X
        BCCM    LCD_RAM0+1, #0 ; E
        SRLW    X
        BCCM    LCD_RAM0+5, #3 ; F
        SRLW    X
        BCCM    LCD_RAM0+1, #7 ; G
        SRLW    X
        BCCM    LCD_RAM0+1, #1 ; M
        SRLW    X
        BCCM    LCD_RAM0+12, #3 ; H
        SRLW    X
        BCCM    LCD_RAM0+12, #2 ; J
        SRLW    X
        BCCM    LCD_RAM0+8, #6 ; K
        SRLW    X
        BCCM    LCD_RAM0+11, #4 ; N
        SRLW    X
        BCCM    LCD_RAM0+8, #0 ; P
        SRLW    X
        BCCM    LCD_RAM0+8, #7 ; Q
        SRLW    X
        BCCM    LCD_RAM0+11, #5 ; DP
        SRLW    X
        BCCM    LCD_RAM0+8, #1 ; COLON
        RET

;       In: X [Cl Dp Q P N K J H M G F E D C B A]
LCDS6:
        SRLW    X
        BCCM    LCD_RAM0+5, #0 ; A
        SRLW    X
        BCCM    LCD_RAM0+1, #4 ; B
        SRLW    X
        BCCM    LCD_RAM0+4, #7 ; C
        SRLW    X
        BCCM    LCD_RAM0+4, #6 ; D
        SRLW    X
        BCCM    LCD_RAM0+1, #2 ; E
        SRLW    X
        BCCM    LCD_RAM0+5, #1 ; F
        SRLW    X
        BCCM    LCD_RAM0+1, #5 ; G
        SRLW    X
        BCCM    LCD_RAM0+1, #3 ; M
        SRLW    X
        BCCM    LCD_RAM0+12, #1 ; H
        SRLW    X
        BCCM    LCD_RAM0+12, #0 ; J
        SRLW    X
        BCCM    LCD_RAM0+8, #4 ; K
        SRLW    X
        BCCM    LCD_RAM0+11, #6 ; N
        SRLW    X
        BCCM    LCD_RAM0+8, #2 ; P
        SRLW    X
        BCCM    LCD_RAM0+8, #5 ; Q
        SRLW    X
        BCCM    LCD_RAM0+11, #7 ; DP
        SRLW    X
        BCCM    LCD_RAM0+8, #3 ; COLON
        RET

       .endif


