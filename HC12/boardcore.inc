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

