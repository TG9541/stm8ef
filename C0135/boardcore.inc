; STM8S103F3P6 "Minimal System Board" STM8S device dependent routines

;       TIM4 interrupt routin, dummy label
;       TODO: reset the µC if a unepected interrupt occurs?
_TIM4_IRQHandler:


        ; STM8S Device dependent HW initialization

BOARDINIT:
        ; "Nano PLC Relay board" GPIO for relay & LED
        MOV     PB_DDR,#0x10
        MOV     PC_DDR,#0x38
        MOV     PD_DDR,#0x10
        MOV     PD_CR1,#0x10

        ; Board I/O initialization

        ; Init RS232 communication port

        ; STM8S[01]003F3 init UART
        MOV     CLK_CKDIVR,#0           ; Clock divider register
        MOV     UART1_BRR2,#0x003       ; 9600 baud
        MOV     UART1_BRR1,#0x068       ; 0068 9600 baud
        ;MOV    UART1_CR1,#0x006        ; 8 data bits, no parity


        ; Use UART1 full duplex
        MOV     UART1_CR2,#0x00C        ; UART1 enable tx & rx

        .ifne   HAS_TXDSIM
        MOV     TIM4_PSCR,#0x03 ; prescaler 1/8
        MOV     TIM4_ARR,#0xCF  ; reload 0.104 ms (9600 baud)
        MOV     ITC_SPR6,#0x3F  ; Interrupt prio. high for TIM4 (Int23)
        MOV     TIM4_CR1,#0x01  ; enable TIM4 (don't enable interrupt)
        .endif

        .ifne   HAS_BACKGROUND
        ; init 5ms timer interrupt
        MOV     TIM2_PSCR,#0x03 ; prescaler 1/8
        MOV     TIM2_ARRH,#0x26 ; reload 5ms H 
        MOV     TIM2_ARRL,#0xDE ;        5ms L
        MOV     ITC_SPR4,#0xF7  ; Interrupt prio. low for TIM2 (Int13)
        MOV     TIM2_CR1,#0x01  ; enable TIM2
        MOV     TIM2_IER,#0x01  ; enable TIM2 interrupt
        .endif
        RET

; ==============================================

;      Device dependent I/O

;       ?RX     ( -- c T | F )  ( TOS STM8: -- Y,Z,N )
;       Return serial interface input char from and true, or false.

        .ifeq   BAREBONES
        .dw     LINK
        LINK =  .
        .db     3
        .ascii  "?RX"
        .endif
QRX:
        CLR     A               ; A: flag false
        BTJF    UART1_SR,#5,QRXSTOR
        LD      A,UART1_DR      ; get char in A
ATOKEY:
        CALLR   QRXSTOR         ; push char
        JP      ONE             ; flag true
QRXSTOR:
        JP      ASTOR           ; push char or flag false


;       TX!     ( c -- )
;       Send character c to the serial interface.

        .ifeq   BAREBONES
        .dw     LINK
        LINK =  .
        .db     3
        .ascii  "TX!"
        .endif
TXSTOR:
        .ifne   HALF_DUPLEX
        ; HALF_DUPLEX with normal UART (e.g. ORed Rx and Tx)
        BRES    UART1_CR2,#2    ; disable rx
        INCW    X
        LD      A,(X)
        INCW    X
1$:     BTJF    UART1_SR,#7,1$  ; loop until tdre
        LD      UART1_DR,A      ; send A
2$:     BTJF    UART1_SR,#6,2$  ; loop until tc
        BSET    UART1_CR2,#2    ; enable rx

        .else                   ; not HALF_DUPLEX
        INCW    X
        LD      A,(X)
        INCW    X
1$:     BTJF    UART1_SR,#7,1$  ; loop until tdre
        LD      UART1_DR,A      ; send A
        .endif
        RET


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
        .ifne   BOARD_W1209
        RRC     A
        BCCM    PA_ODR,#3       ; W1209 relay
        .endif
        .ifne   BOARD_C0135
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
        .endif
        .ifne   BOARD_MINDEV
        RRC     A
        CCF
        BCCM    PB_ODR,#5       ; PB5 LED
        .endif
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


;       BKEYC  ( -- c )   ( TOS STM8: -- A,Z,N )
;       Read and translate board dependent key bitmap into char 

BKEYCHAR:
        CALLR   BKEY
        JREQ    1$
        ADD     A,#'@'
        LD      (1,X),A
1$:     RET
       
        .endif

