;--------------------------------------------------------
;       STM8 eForth Simulated Serial I/O 
;       Init and default code
;--------------------------------------------------------

;       Simulated serial I/O
;       either full or half duplex

        .ifeq  HAS_TXSIM + HAS_RXSIM

        .macro SSER_INIT
        .endm
        
        .globl _TIM4_IRQHandler
        .globl _EXTI0_IRQHandler
        .globl _EXTI1_IRQHandler
        .globl _EXTI2_IRQHandler
        .globl _EXTI3_IRQHandler
        .globl _EXTI4_IRQHandler
        .globl _EXTI5_IRQHandler
        .globl _EXTI6_IRQHandler
        .globl _EXTI7_IRQHandler

        ; dummy for linker - can be overwritten by Forth application

_EXTI0_IRQHandler:
_EXTI1_IRQHandler:
_EXTI2_IRQHandler:
_EXTI3_IRQHandler:
_EXTI4_IRQHandler:
_EXTI5_IRQHandler:
_EXTI6_IRQHandler:
_EXTI7_IRQHandler:
_TIM4_IRQHandler:

        .else

        .ifne   HAS_RXSIM+HAS_TXSIM
        ; TIM4 based RXD or TXD: initialize timer
        TIM4RELOAD = 0xCF       ; reload 0.104 ms (9600 baud)
        MOV     TIM4_ARR,#TIM4RELOAD
        MOV     TIM4_PSCR,#0x03 ; prescaler 1/8
        MOV     TIM4_CR1,#0x01  ; enable TIM4
        .endif

        .ifne   HAS_TXSIM*((PNRX-PNTX)+(1-HAS_RXSIM))
        ; init TxD through GPIO if not shared pin with PNRX
        BSET    PSIM+ODR,#PNTX    ; PNTX GPIO high
        BSET    PSIM+DDR,#PNTX    ; PNTX GPIO output
        BSET    PSIM+CR1,#PNTX    ; enable PNTX push-pull
        .endif

        .ifne   (HAS_RXSIM)
        ; init RxD through GPIO

        .ifeq   (PSIM-PORTA)
        BSET    EXTI_CR1,#1     ; External interrupt Port A falling edge
        .else

        .ifeq   (PSIM-PORTB)
        BSET    EXTI_CR1,#3     ; External interrupt Port B falling edge
        .else

        .ifeq   (PSIM-PORTC)
        BSET    EXTI_CR1,#5     ; External interrupt Port C falling edge
        .else
        BSET    EXTI_CR1,#7     ; External interrupt Port D falling edge
        .endif

        .endif
        .endif
        BRES    PSIM+DDR,#PNRX    ; 0: input (default)
        BSET    PSIM+CR1,#PNRX    ; enable PNRX pull-up
        BSET    PSIM+CR2,#PNRX    ; enable PNRX external interrupt
        .endif
        
        ; include required serial I/O code
          .ifne  PNRX^PNTX
            .include "sser_fdx.inc" ; Full Duplex serial
          .else
            .include "sser_hdx.inc" ; Half Duplex serial
          .endif
        .endif

