; STM8S003F3P6 "Core" STM8S device dependent routine default code

; Note: for supporting a new board create a new board configuration
;       folder with a "globconfig.inc" and a copy of this file.

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

;       BOARDINIT  ( -- )
;       Init board GPIO (except COM ports)

BOARDINIT:
        ; Board I/O initialization
        MOV     PA_DDR, #0b00000000 ; All as input
        MOV     PC_DDR, #0b00000000 ; All as input
        ; Inputs:Duty+ [PA1], Duty- [PA2]
        MOV     PA_ODR, #0b00000110
        MOV     PA_CR1, #0b00000110 ; Inputs with pullup
        MOV     PA_CR2, #0b00000000 ; No external interrupt
        ; Inputs: Freq+ [PC4], Freq- [PC3]
        ; Outputs: HT1621: DATA [PC7], CLK(nWR) [PC6], nCS [PC5]
        MOV     PC_ODR, #0b11100000
        MOV     PC_CR1, #0b11111000 ; push-pull outputs, pullup inputs
        MOV     PC_CR2, #0b11100000
        MOV     PC_DDR, #0b11100000 ; HT1621B pins is output

        ; Init HT1621B
        LD      A, #0x28 ; Bias 1/2, 4 commons
        CALLR   LCD_CMD
        LD      A, #0x18 ; RC 256KHz
        CALLR   LCD_CMD
        LD      A, #0x00 ; Sys disable
        CALLR   LCD_CMD
        LD      A, #0x05 ; WDT disable
        CALLR   LCD_CMD
        LD      A, #0x01 ; System enable
        CALLR   LCD_CMD
        LD      A, #0x03 ; LCD on
        CALLR   LCD_CMD

        ; Reset display data
        LD      A, #0
        LDW     Y, #0xffff ; #0xfafa
        CALL    LCD_DATA
        LD      A, #4
        LDW     Y, #0xffff ; #0xfafb
        CALL    LCD_DATA
        LD      A, #8
        LDW     Y, #0xffff ; #0x0afa
        CALL    LCD_DATA
        LD      A, #12
        LDW     Y, #0xffff ; #0x0000
        CALL    LCD_DATA
        LD      A, #16
        LDW     Y, #0xff00 ; #0x0100
        CALL    LCD_DATA

        RET

; ==============================================

; HT1621B address map
; addr  b3      b2      b1      b0
; -------------------------------------
;  0    2.1A    2.1F    2.1E    2.1D
;  1    2.1B    2.1G    2.1C    2.1dot
;  2    2.2A    2.2F    2.2E    2.2D
;  3    2.2B    2.2G    2.2C    2.2dot
;  4    2.3A    2.3F    2.3E    2.3D
;  5    2.3B    2.3G    2.3C    2.3dot
;  6    2.4A    2.4F    2.4E    2.4D
;  7    2.4B    2.4G    2.4C    2.colon
;  8    2.W     2.%     2.h     2.A
;  9    1.4B    1.4G    1.4C    1.V
; 10    1.4A    1.4F    1.4E    1.4A
; 11    1.3B    1.3G    1.3C    1.3dot
; 12    1.3A    1.3F    1.3E    1.3A
; 13    1.2B    1.2G    1.2C    1.2dot
; 14    1.2A    1.2F    1.2E    1.2A
; 15    1.1B    1.1G    1.1C    1.1dot
; 16    1.1A    1.1F    1.1E    1.1A
; 17    1.IN    1.OUT   2.SET   1.°C

; Send command to LCD. reg A - command
LCD_CMD:
        BRES    PC_ODR, #5 ; CS active
        CALLR   LCD_BIT1
        CALLR   LCD_BIT0
        CALLR   LCD_BIT0
        ; Send command
        CALLR   LCD_BYTE_A
        CALLR   LCD_BIT0
        BSET    PC_ODR, #5 ; CS inactive
        RET


; ==============================================
;       LCD!  ( w addr -- )
;       Put w (4 nibbles) to LCD data registers
        .dw     LINK

        LINK =  .
        .db     (4)
        .ascii  "LCD!"
LCD_STOR:
        ; Load address
        INCW    X ; Skip msb byte
        LD      A,(X) ; Get lsb byte
        INCW    X
        ; Load data
        LDW     Y, X
        LDW     Y, (Y)
        INCW    X
        INCW    X
        ; Load values and now write to HT1621B

LCD_DATA:
        CALLR   LCD_ADDR
        ; Send data
        LD      A,YH
        CALLR   LCD_BYTE_A
        LD      A,YL
        CALLR   LCD_BYTE_A

        BSET    PC_ODR, #5 ; CS inactive
        RET

; ==============================================
;       LCDC!  ( c addr -- )
;       Put c (2 nibbles) to LCD data registers
        .dw     LINK

        LINK =  .
        .db     (5)
        .ascii  "LCDC!"
LCDC_STOR:
        ; Load address
        INCW    X ; Skip msb byte
        LD      A,(X) ; Get lsb byte
        INCW    X
        ; Load data
        LDW     Y, X
        LDW     Y, (Y)
        INCW    X
        INCW    X
        ; Load values and now write to HT1621B
LCDC_DATA:
        CALLR   LCD_ADDR
        ; Send data
        LD      A,YL
        CALLR   LCD_BYTE_A

        BSET    PC_ODR, #5 ; CS inactive
        RET


LCD_ADDR:
        BRES    PC_ODR, #5 ; CS active
        CALLR   LCD_BIT1
        CALLR   LCD_BIT0
        CALLR   LCD_BIT1
        ; Send addr
        RLC     A
        RLC     A
        CALLR   LCD_BIT_A
        CALLR   LCD_BIT_A
        CALLR   LCD_BIT_A
        CALLR   LCD_BIT_A
        CALLR   LCD_BIT_A
        CALLR   LCD_BIT_A
        RET

LCD_BIT1:
        BSET    PC_ODR, #7 ; Data 1
        JRA     LCD_CLK

LCD_BIT0:
        BRES    PC_ODR, #7 ; Data 0
        JRA     LCD_CLK

LCD_BYTE_A:
        CALLR   LCD_BIT_A
        CALLR   LCD_BIT_A
        CALLR   LCD_BIT_A
        CALLR   LCD_BIT_A
        CALLR   LCD_BIT_A
        CALLR   LCD_BIT_A
        CALLR   LCD_BIT_A
LCD_BIT_A:
        RLC     A
        BCCM    PC_ODR, #7 ; Data
LCD_CLK:
        BRES    PC_ODR, #6 ; Clock down
        BSET    PC_ODR, #6 ; Clock up
        RET

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
;       Inputs: Freq+ [PC4], Freq- [PC3]
;       Inputs: Duty+ [PA1], Duty- [PA2]
        .dw     LINK

        LINK =  .
        .db     (4)
        .ascii  "BKEY"
BKEY:
        CLR     A
        BTJF    PC_IDR, #4, 1$
1$:     RLC     A
        BTJF    PC_IDR, #3, 2$
2$:     RLC     A
        BTJF    PA_IDR, #1, 3$
3$:     RLC     A
        BTJF    PA_IDR, #2, 4$
4$:     RLC     A
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

;       WRST  ( -- )
;       Emulate software reset trought WWDG
        .dw     LINK

        LINK =  .
        .db     (4)
        .ascii  "WRST"
WRST:
        MOV     WWDG_CR, #0xC0
WRSTLOOP:
        JRA     WRSTLOOP

;===============================================================
;       SWAPN  ( c -- c )     ( TOS STM8: -- A,Z,N )
;       swap nibbles in byte
        .dw     LINK

        LINK =  .
        .db     (5)
        .ascii  "SWAPN"
SWAPN:
        SWAP    (1,X)
        RET

;===============================================================
;       SWAPW  ( w -- w )     ( TOS STM8: -- A,Z,N )
;       swap bytes in word
        .dw     LINK

        LINK =  .
        .db     (5)
        .ascii  "SWAPW"
SWAPW:
        LDW     Y,X
        LDW     Y,(Y)
        SWAPW   Y
        LDW     (X),Y
        RET
