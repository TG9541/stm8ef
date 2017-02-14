; STM8S003F3P6 "HC12" STM8S device dependent routine default code

; Note: for supporting a new board create a new board configuration
;       folder with a "globconfig.inc" and a copy of this file.

; HC-12 I/O mapping of STM8S003P6:
;
; Pin# | Function          | board pin/signal
; 1    | PD4               | Si4463 p1 - SDN
; 2    | PD5/UART1_TX      | header TXD pad via level shifter
; 3    | PD6/UART1_RX      | header RXD pad via level shifter
; 4    | nRST              | reset test point nearest header RXD pad
; 11   | PB5               | header SET pad via level shifter
; 12   | PB4               | Si4463 p9  - GPIO0
; 13   | PC3               | Si4463 p10 - GPIO1
; 14   | PC4               | Si4463 p11 - nIRQ
; 15   | PC5/SPI_SCK       | Si4463 p12 - SCLK
; 16   | PC6/SPI_MOSI      | Si4463 p14 - SDI
; 17   | PC7/SPI_MISO      | Si4463 p13 - SDO
; 18   | PD1/SWIM          | SWIM test point nearest header TXD pad
; 19   | PD2               | Si4463 p15 - nSEL


;       BOARDINIT  ( -- )
;       Init board GPIO (except COM ports)

BOARDINIT:
        ; Board I/O initialization

        MOV     PD_ODR  ,#0x004       ; nSEL on PD2, SDN disabled by default
        MOV     PD_DDR  ,#0x014
        MOV     PD_CR1  ,#0x074       ; P-P for nSEL,SDN,UART1_TX, p/u for UART1_RX
        MOV     PC_CR1  ,#0x0F8       ; P-P for MOSI,SCLK, p/u for MISO,GPIO1
        MOV     PC_DDR  ,#0x060       ; OE for SCK and MOSI
        MOV     PB_CR1  ,#0x030       ; p/u for SET,GPIO0

        ; Set up SPI
        MOV     SPI_CR1 ,#0x014       ; master, CLK/8, CPOL=CPHA=0, MSB first
        MOV     SPI_CR2 ,#0x001       ; no NSS, FD, no CRC
        MOV     SPI_CR1 ,#0x054       ; enable SPI
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

; ==============================================
;       SPI  ( c -- c)
;       Perform SPI byte cycle with result c
        .dw     LINK

        LINK =  .
        .db     (3)
        .ascii  "SPI"
SPI:
        LD      A,(1,X)
        LD      SPI_DR,A
SPITXE_WAIT:
        BTJF    SPI_SR,#1,SPITXE_WAIT ;TXE
SPIRXNE_WAIT:
        BTJF    SPI_SR,#0,SPIRXNE_WAIT ;RXNE
        LD      A,SPI_DR
        LD      (1,X),A
        RET

;       SPIS    ( --  )
;       SPI frame start
; ===========================================================
        .dw     LINK
        LINK =  .
        .db     (4)
        .ascii  "SPIS"
SPIS:
        BRES    PD_ODR,#2  ; clear nRES
        RET 

;       SPIE   ( --  )
;       SPI frame end
; ===========================================================
        .dw     LINK
        LINK =  .
        .db     (4)
        .ascii  "SPIE"
SPIE:
        BSET    PD_ODR,#2  ; set nRES
        RET

;       EZE   ( -- )
;       Enable EZRadio
; ===========================================================
        .dw     LINK
        LINK =  .
        .db     (3)
        .ascii  "EZE"
EZE:
        BRES    PD_ODR,#4  ; set SDN 
        RET

;       EZD   ( --  )
;       Disable EZRadio
; ===========================================================
        .dw     LINK
        LINK =  .
        .db     (3)
        .ascii  "EZD"
EZD:
        BRES    PD_ODR,#4  ; clear SDN 
        RET
