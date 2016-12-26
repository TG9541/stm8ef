; XH-W1209 STM8S device dependent HW routines

BOARDINIT:

        ; Board I/O initialization
        ; W1209 STM8S003F3 init GPIO
        MOV     PA_DDR,#0b00001110 ; relay,B,F        
        MOV     PA_CR1,#0b00001110         
        MOV     PB_DDR,#0b00110000 ; d2,d3
        MOV     PB_CR1,#0b00110000 
        MOV     PC_DDR,#0b11000000 ; G,C        
        MOV     PC_CR1,#0b11111000 ; G,C-+S... Key pullups        
        MOV     PD_DDR,#0b00111110 ; A,DP,D,d1,A
        MOV     PD_CR1,#0b00111110 


        ; Init RS232 communication port
        ; STM8S[01]003F3 init UART
        MOV     CLK_CKDIVR,#0           ; Clock divider register
        MOV     UART1_BRR2,#0x003       ; 9600 baud
        MOV     UART1_BRR1,#0x068       ; 0068 9600 baud
        ;MOV    UART1_CR1,#0x006        ; 8 data bits, no parity
        ; HALF_DUPLEX
        MOV     UART1_CR2,#0x004        ; enable rx 

        ;  HAS_TXDSIM
        MOV     TIM4_PSCR,#0x03 ; prescaler 1/8
        MOV     TIM4_ARR,#0xCF  ; reload 0.104 ms (9600 baud)
        MOV     ITC_SPR6,#0x3F  ; Interrupt prio. high for TIM4 (Int23)
        MOV     TIM4_CR1,#0x01  ; enable TIM4 (don't enable interrupt)

        ; HAS_BACKGROUND + HAS_LED7SEG
        ; init 5ms timer interrupt
        MOV     TIM2_PSCR,#0x03 ; prescaler 1/8
        MOV     TIM2_ARRH,#0x26 ; reload 5ms H 
        MOV     TIM2_ARRL,#0xDE ;        5ms L
        MOV     ITC_SPR4,#0xF7  ; Interrupt prio. low for TIM2 (Int13)
        MOV     TIM2_CR1,#0x01  ; enable TIM2
        MOV     TIM2_IER,#0x01  ; enable TIM2 interrupt
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
        BRES    UART1_CR2,#2    ; disable rx

1$:     BTJT    TIM4_IER,#0,1$  ; wait for end of TX
        INCW    X
        LD      A,(X)
        INCW    X
        LD      TIM4TXREG,A
        MOV     TIM4TCNT,#11     ; init next transfer 
        BSET    TIM4_IER,#0     ; enabale TIM4 interrupt
         
        RET

; ==============================================

_TIM4_IRQHandler:
        .ifne   HAS_TXDSIM
        ; TIM4 interrupt handler W1209 software TxD. 
        ; RxD (PD_6) is on the board's sensor header, 
        ; STM8S UART1 half-duplex mode requires TxD (PD_5) 
        ; Work-around: change from RxD to GPIO for SW-TX
        ; To use, write char to TIM4TXREG, then 0x0A to TIM4TCNT
        ; BCPL    PA_ODR,#3     ; pin debug
        BRES    TIM4_SR,#0      ; clear TIM4 UIF 
        LD      A,TIM4TCNT
        JRNE    TIM4_TRANS      ; transmit in progress
        BRES    TIM4_IER,#0     ; disable TIM4 interrupt
        JRNE    TIM4_END        ; nothing to transmit
TIM4_TRANS:        
        CP      A,#0x0B         ; TIM4TCNT > 0x0A: count down
        JRMI    TIM4_START      
        JRA     TIM4_DEC       

TIM4_START:  
        CP      A,#10
        JRNE    TIM4_STOP

        ; configure PD_6 from RX to GPIO 
        BRES    UART1_CR2,#2    ; disable RX
        BSET    PD_DDR,#PDTX    ; set PD_6 to output

        RCF                     ; start bit, set PD_6 low 
        JRA     TIM4_BIT         

TIM4_STOP:  
        CP      A,#1
        JRNE    TIM4_SER
        ; TIM4TCNT == 1 
        SCF                     ; stop bit, set PD_6 high 
        JRA     TIM4_BIT         
               
TIM4_SER:
        ; TIM4TCNT == 9:2
        SRL     TIM4TXREG    
        ; fall through

TIM4_BIT:
        ; Set RxTx port to CF 
        BCCM    PD_ODR,#PDTX
        ; fall through

TIM4_DEC:             
        DEC     TIM4TCNT        ; next TXD TIM4 state
        JRNE    TIM4_END

        ; TIM4TCNT == 0
        BRES    PD_DDR,#PDTX    ; set PD_6 to input
        BSET    UART1_CR2,#2    ; re-enable RX
        ; fall through

TIM4_END:             
        ; BCPL    PA_ODR,#3
        IRET 
        .endif


; ==============================================


;       Multiplexed 7-seg LED display
LED_MPX:        
        LD      A,TICKCNT+1
        AND     A,#3        
        .ifne   BOARD_W1209        
        BSET    PD_ODR,#4       ; clear digit outputs .321
        BSET    PB_ODR,#5
        BSET    PB_ODR,#4

        JRNE    1$
        LD      A,LED7MSB+1
        BRES    PD_ODR,#4       ; digit .3.. 
        JRA     3$

1$:     CP      A,#1
        JRNE    2$
        LD      A,LED7LSB
        BRES    PB_ODR,#5       ; digit ..2.
        JRA     3$

2$:     CP      A,#2
        JRNE    4$  
        LD      A,LED7LSB+1 
        BRES    PB_ODR,#4       ; digit ...1
        ; fall through
         
3$:
        ; W1209 7S LED display row
        ; bit 76453210 input (parameter A)
        ;  PA .....FB.
        ;  PC CG...... 
        ;  PD ..A.DPE.
        RRC     A
        BCCM    PD_ODR,#5       ; A
        RRC     A
        BCCM    PA_ODR,#2       ; B
        RRC     A
        BCCM    PC_ODR,#7       ; C
        RRC     A
        BCCM    PD_ODR,#3       ; D
        RRC     A
        BCCM    PD_ODR,#1       ; E
        RRC     A
        BCCM    PA_ODR,#1       ; F
        RRC     A
        BCCM    PC_ODR,#6       ; G
        RRC     A
        BCCM    PD_ODR,#2       ; P
4$:        
        .else
        ; implement board LED port mapping 
        .endif
        RET

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
        ; Keys "set" (1), "+" (2), and "-" (4) on PC.3:5
        LD      A,PC_IDR
        SLA     A
        SWAP    A
        CPL     A
        AND     A,#0x07
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
