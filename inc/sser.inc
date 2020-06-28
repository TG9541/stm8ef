;--------------------------------------------------------
;       STM8 eForth Simulated Serial I/O
;       Init and default code
;--------------------------------------------------------

;       Simulated serial I/O
;       either full or half duplex

        .ifeq  HAS_TXSIM + HAS_RXSIM

        .macro SSER_Init
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

        .macro SSER_Init
        .ifne   HAS_RXSIM+HAS_TXSIM

          .ifeq   (FAMILY - STM8L)
        BSET    CLK_PCKENR1,#2  ; STM8L clock tree: enable TIM4
          .endif

         ; TIM4 based RXD or TXD: initialize timer
        MOV     TIM4_ARR,#CTIM4ARR

        MOV     TIM4_PSCR,#CTIM4PSCR ; prescaler 1/(2^n)
        MOV     TIM4_CR1,#0x01  ; enable TIM4
        .endif

        .ifne   HAS_TXSIM*((PNRX-PNTX)+(1-HAS_RXSIM))
        ; init TxD through GPIO if not shared pin with PNRX
        BSET    PSIM+ODR,#PNTX  ; PNTX GPIO high
        BSET    PSIM+DDR,#PNTX  ; PNTX GPIO output
        BSET    PSIM+CR1,#PNTX  ; enable PNTX push-pull
        .endif

        .ifne   (HAS_RXSIM)
          ; init RxD EXTI for GPIO
          .ifeq   (FAMILY - STM8L)
            ; STM8L EXTI for port bit 0..7
            .ifeq   (PNRX / 4)
        BSET    EXTI_CR1,#1+PNRX*2     ; ext. int. port bit 0..3 falling edge
            .else
        BSET    EXTI_CR2,#1+(PNRX-4)*2 ; ext. int. port bit 4..7 falling edge
            .endif
          .else
            ; STM8S EXTI for 8 bit port
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
        .endif
        BRES    PSIM+DDR,#PNRX    ; 0: input (default)
        BSET    PSIM+CR1,#PNRX    ; enable PNRX pull-up
        BSET    PSIM+CR2,#PNRX    ; enable PNRX external interrupt
        .endif
        .endm

        ; include required serial I/O code
          .ifne  PNRX^PNTX
            .include "sser_fdx.inc" ; Full Duplex serial
          .else
            .include "sser_hdx.inc" ; Half Duplex serial
          .endif
        .endif

