;--------------------------------------------------------
;       STM8EF for STM8S (Value line and Access Line devices)
;       Simulated serial I/O - single GPIO - Half Duplex
;--------------------------------------------------------



        RamByte TIM4TCNT        ; TIM4 RX/TX interrupt counter
        RamByte TIM4TXREG       ; TIM4 TX transmit buffer and shift register
        RamByte TIM4RXREG       ; TIM4 RX shift register
        RamByte TIM4RXBUF       ; TIM4 RX receive buffer

        .ifne   SERPRIOTIM
        RamWord TIMSERIAL       ; "TIMSERIAL" Timer: use PSIM,PNRX for serial while not 0
        RamByte TIMRELOAD       ; Reload value for TIMSERIAL, set by receive interrupt, reset by timer
        .endif

        .ifne   HAS_RXSIM
;       ?RXP     ( -- c T | F )  ( TOS STM8: -- Y,Z,N )
;       Return char from a simulated serial interface and true, or false.

        .ifeq   BAREBONES
        .ifne   HAS_RXUART
        HEADER  QRXP "?RXP"
        .else
        HEADER  QRX "?RX"
        .endif
        .endif
        .ifeq   HAS_RXUART
QRX:
        .endif
QRXP:
        CLR     A
        EXG     A,TIM4RXBUF     ; read and consume char
        JP      ATOKEY
        .endif

        .ifne   HAS_TXSIM
;       TXP!     ( c -- )
;       Send character c to a simulated serial interface.

        .ifeq   BAREBONES
        .ifne   HAS_TXUART
        HEADER  TXPSTOR "TXP!"
        .else
        HEADER  TXSTOR "TX!"
        .endif
        .endif

        .ifeq   HAS_TXUART
TXSTOR:
        .endif
TXPSTOR:
        .ifne   SERPRIOTIM
        MOV     TIMSERIAL,TIMRELOAD ; load MSB msec ticker
        .endif

        INCW    X
        LD      A,(X)
        INCW    X

1$:     TNZ     TIM4TCNT
        JRNE    1$              ; wait for free TIM4 RX-TX

        BRES    PSIM+CR2,#PNRX  ; disable PNRX external interrupt
        LD      TIM4TXREG,A     ; char to TXSIM output register
        MOV     TIM4TCNT,#10    ; init next transfer
        CLR     TIM4_CNTR       ; reset TIM4, trigger update interrupt
        BSET    TIM4_IER,#0     ; enable TIM4 interrupt
        RET
        .endif

;       RxD through GPIO start-bit interrupt handler
;       of course, the interrupt vectors can set anew by Forth code

        .ifne   HAS_RXSIM
        .globl _EXTI0_IRQHandler
        .globl _EXTI1_IRQHandler
        .globl _EXTI2_IRQHandler
        .globl _EXTI3_IRQHandler
        .globl _EXTI4_IRQHandler
        .globl _EXTI5_IRQHandler
        .globl _EXTI6_IRQHandler
        .globl _EXTI7_IRQHandler

_EXTI0_IRQHandler:
_EXTI1_IRQHandler:
_EXTI2_IRQHandler:
_EXTI3_IRQHandler:
_EXTI4_IRQHandler:
_EXTI5_IRQHandler:
_EXTI6_IRQHandler:
_EXTI7_IRQHandler:

        BRES    PSIM+CR2,#PNRX    ; disable PNRX external interrupt

        .ifeq   (FAMILY - STM8L)
        BSET    EXTI_SR1,#PNRX  ; STM8L: clear interrupt
        .endif

        .ifne   SERPRIOTIM
        MOV     TIMRELOAD,#(SERPRIOTIM/256) ; load MSB msec reload
        MOV     TIMSERIAL,TIMRELOAD ; load MSB msec ticker
        .endif

        ; Set-up TIM4 for 8N1 Rx sampling at half bit time
        MOV     TIM4TCNT,#(-9)  ; set sequence counter for RX
        MOV     TIM4_CNTR,#(CTIM4ARR/2)
        BRES    TIM4_SR,#0      ; clear TIM4 UIF
        BSET    TIM4_IER,#0     ; enable TIM4 interrupt
        IRET
        .endif

        .globl _TIM4_IRQHandler
_TIM4_IRQHandler:
        ; TIM4 interrupt handler for half-duplex Rx+Tx

        BRES    TIM4_SR,#0      ; clear TIM4 UIF

        LD      A,TIM4TCNT      ; TIM4CNT is the step counter
        JRMI    TIM4_RECVE      ; negative index: receive
        JRNE    TIM4_TRANS      ; positive index: transmit
        ; fall through

TIM4_OFF:
        BSET    PSIM+CR2,#PNRX  ; enable PNRX external interrupt
        BRES    PSIM+DDR,#PNRX  ; set shared GPIO to input
        BRES    TIM4_IER,#0     ; disable TIM4 interrupt
        IRET

TIM4_RECVE:
        BTJT    PSIM+IDR,#PNRX,1$ ; dummy branch, copy GPIO to CF
1$:     RRC     TIM4RXREG
        INC     TIM4TCNT
        JRNE    TIM4_END
        MOV     TIM4RXBUF,TIM4RXREG ; save result (CF is now start-bit)
        JRA     TIM4_OFF

TIM4_TRANS:
        CP      A,#10           ; startbit? (also sets CF)
        JRNE    TIM4_SER
        BSET    PSIM+DDR,#PNRX  ; port PD1=PNRX to output
        JRA     TIM4_BIT        ; emit start bit (CF=0 from "CP A")

TIM4_SER:
        RRC     TIM4TXREG       ; get data bit, shift in stop bit (CF=1 from "CP A")
        ; fall through

TIM4_BIT:
        BCCM    PSIM+ODR,#PNTX  ; Set GPIO to CF
        DEC     TIM4TCNT        ; next TXD TIM4 state
        JREQ    TIM4_OFF        ; complete when TIM4CNT is zero
        ; fall through

TIM4_END:
        IRET
