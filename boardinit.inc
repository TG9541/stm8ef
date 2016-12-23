        ; STM8S Device dependent HW initialization

PORTINIT:
        .ifne   STM8S_DISCOVERY
        ; STM8S Discovery init GPIO & clock
  MOV	PD_DDR,#0x01	; LED, SWIM
	MOV	PD_CR1,#0x03	; pullups
	MOV	PD_CR2,#0x01	; speed
	BSET    CLK_SWCR,#1     ; enable external clcok
	MOV     CLK_SWR,#0x0B4  ; external cyrstal clock
WAIT0:	BTJF    CLK_SWCR,#3,WAIT0 ; wait SWIF
	BRES    CLK_SWCR,#3     ; clear SWIF
        .endif

        .ifne   BOARD_MINDEV
        ; STM8S103F3 minimal breakout board init GPIO
        BSET     PB_DDR,#5  
        BSET     PB_CR1,#5 
        .endif

        .ifne   BOARD_W1209
        ; W1209 STM8S003F3 init GPIO
        MOV     PA_DDR,#0b00001110 ; relay,B,F        
        MOV     PA_CR1,#0b00001110         
        MOV     PB_DDR,#0b00110000 ; d2,d3
        MOV     PB_CR1,#0b00110000 
        MOV     PC_DDR,#0b11000000 ; G,C        
        MOV     PC_CR1,#0b11111000 ; G,C-+S... Key pullups        
        MOV     PD_DDR,#0b00111110 ; A,DP,D,d1,A
        MOV     PD_CR1,#0b00111110 
        .endif
       
      OV     ITC_SPR4,#0xF7  ; Interrupt prio. low for TIM2 (Int13)
        MOV     TIM2_CR1,#0x01  ; enable TIM2
        MOV     TIM2_IER,#0x01  ; enable TIM2 interrupt
        .endif 
        .ifne   BOARD_C0135
        ; "Nano PLC Relay board"
        MOV     PB_DDR,#0x10
        MOV     PC_DDR,#0x38
        MOV     PD_DDR,#0x10
        MOV     PD_CR1,#0x10
        .endif

        ; Board I/O initialization

        ; Init RS232 communication port

        .ifne  (STM8S003F3 + STM8S103F3)
        ; STM8S[01]003F3 init UART
        MOV     CLK_CKDIVR,#0           ; Clock divider register
	MOV	UART1_BRR2,#0x003	; 9600 baud
	MOV	UART1_BRR1,#0x068	; 0068 9600 baud
	;MOV	UART1_CR1,#0x006	; 8 data bits, no parity
        .ifne HALF_DUPLEX
	MOV	UART1_CR2,#0x004	; enable rx 
        .else              
	MOV	UART1_CR2,#0x00C	; enable tx & rx
        .endif
        .else                           
        ; Other STM8S controller - UART2, assume 16MHz clock  
	MOV	UART2_BD2,#0x003	; 9600 baud
	MOV	UART2_BD1,#0x068	; 0068 9600 baud
	MOV	UART2_CR1,#0x006	; 8 data bits, no parity
	MOV	UART2_CR3,#0x000	; 1 stop bit
        .endif 

        .ifne   HAS_TXDSIM
        MOV     TIM4_PSCR,#0x03 ; prescaler 1/8
        MOV     TIM4_ARR,#0xCF  ; reload 0.104 ms (9600 baud)
 	MOV     ITC_SPR6,#0x3F  ; Interrupt prio. high for TIM4 (Int23)
        MOV     TIM4_CR1,#0x01  ; enable TIM4 (don't enable interrupt)
        .endif

        .ifne   (HAS_BACKGROUND + HAS_LED7SEG)
        ; init 5ms timer interrupt
        MOV     TIM2_PSCR,#0x03 ; prescaler 1/8
        MOV     TIM2_ARRH,#0x26 ; reload 5ms H 
        MOV     TIM2_ARRL,#0xDE ;        5ms L
 	MOV     ITC_SPR4,#0xF7  ; Interrupt prio. low for TIM2 (Int13)
        MOV     TIM2_CR1,#0x01  ; enable TIM2
        MOV     TIM2_IER,#0x01  ; enable TIM2 interrupt
        .endif

