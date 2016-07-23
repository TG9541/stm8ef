;       PA_ODR    ( -- a )
; Port A data output latch register
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PA_ODR"
PAODR:
         LDW     Y,#(PA_ODR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PA_IDR    ( -- a )
; Port A input pin value register
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PA_IDR"
PAIDR:
         LDW     Y,#(PA_IDR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PA_DDR    ( -- a )
; Port A data direction register
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PA_DDR"
PADDR:
         LDW     Y,#(PA_DDR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PA_CR1    ( -- a )
; Port A control register 1
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PA_CR1"
PACR1:
         LDW     Y,#(PA_CR1)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PA_CR2    ( -- a )
; Port A control register 2
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PA_CR2"
PACR2:
         LDW     Y,#(PA_CR2)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PB_ODR    ( -- a )
; Port B data output latch register
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PB_ODR"
PBODR:
         LDW     Y,#(PB_ODR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PB_IDR    ( -- a )
; Port B input pin value register
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PB_IDR"
PBIDR:
         LDW     Y,#(PB_IDR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PB_DDR    ( -- a )
; Port B data direction register
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PB_DDR"
PBDDR:
         LDW     Y,#(PB_DDR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PB_CR1    ( -- a )
; Port B control register
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PB_CR1"
PBCR1:
         LDW     Y,#(PB_CR1)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PB_CR2    ( -- a )
; Port B control register
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PB_CR2"
PBCR2:
         LDW     Y,#(PB_CR2)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PC_ODR    ( -- a )
; Port C data output latch register
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PC_ODR"
PCODR:
         LDW     Y,#(PC_ODR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PC_IDR    ( -- a )
; Port C input pin value register
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PC_IDR"
PCIDR:
         LDW     Y,#(PC_IDR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PC_DDR    ( -- a )
; Port C data direction register
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PC_DDR"
PCDDR:
         LDW     Y,#(PC_DDR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PC_CR1    ( -- a )
; Port C control register 1
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PC_CR1"
PCCR1:
         LDW     Y,#(PC_CR1)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PC_CR2    ( -- a )
; Port C control register 2
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PC_CR2"
PCCR2:
         LDW     Y,#(PC_CR2)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PD_ODR    ( -- a )
; Port D data output latch register
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PD_ODR"
PDODR:
         LDW     Y,#(PD_ODR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PD_IDR    ( -- a )
; Port D input pin value register
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PD_IDR"
PDIDR:
         LDW     Y,#(PD_IDR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PD_DDR    ( -- a )
; Port D data direction register
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PD_DDR"
PDDDR:
         LDW     Y,#(PD_DDR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PD_CR1    ( -- a )
; Port D control register 1
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PD_CR1"
PDCR1:
         LDW     Y,#(PD_CR1)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       PD_CR2    ( -- a )
; Port D control register 2
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PD_CR2"
PDCR2:
         LDW     Y,#(PD_CR2)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       FLASH_IAPSR    ( -- a )
; Flash in-application programming status register
         .dw     LINK
         LINK =  .
         .db     11
         .ascii  "FLASH_IAPSR"
FLASHIAPSR:
         LDW     Y,#(FLASH_IAPSR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       FLASH_DUKR    ( -- a )
; Data EEPROM unprotection register
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "FLASH_DUKR"
FLASHDUKR:
         LDW     Y,#(FLASH_DUKR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       CLK_CKDIVR    ( -- a )
; Clock divider register
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "CLK_CKDIVR"
CLKCKDIVR:
         LDW     Y,#(CLK_CKDIVR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       UART1_SR    ( -- a )
;UART status reg
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "UART1_SR"
UART1SR:
         LDW     Y,#(UART1_SR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       UART1_DR    ( -- a )
;UART data reg
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "UART1_DR"
UART1DR:
         LDW     Y,#(UART1_DR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       UART1_BRR1    ( -- a )
;baud rate control 1
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "UART1_BRR1"
UART1BRR1:
         LDW     Y,#(UART1_BRR1)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       UART1_BRR2    ( -- a )
;baud rate control 2
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "UART1_BRR2"
UART1BRR2:
         LDW     Y,#(UART1_BRR2)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       UART1_CR1    ( -- a )
;UART control reg 2
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "UART1_CR1"
UART1CR1:
         LDW     Y,#(UART1_CR1)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       UART1_CR2    ( -- a )
;UART control reg 2
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "UART1_CR2"
UART1CR2:
         LDW     Y,#(UART1_CR2)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       UART1_CR3    ( -- a )
;UART control reg 2
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "UART1_CR3"
UART1CR3:
         LDW     Y,#(UART1_CR3)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       TIM4_CR1    ( -- a )
; 1 (ENABLE)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM4_CR1"
TIM4CR1:
         LDW     Y,#(TIM4_CR1)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       TIM4_IER    ( -- a )
; 1 (ENABLE)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM4_IER"
TIM4IER:
         LDW     Y,#(TIM4_IER)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       TIM4_SR    ( -- a )
; 0 (clear)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "TIM4_SR"
TIM4SR:
         LDW     Y,#(TIM4_SR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       TIM4_EGR    ( -- a )

         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM4_EGR"
TIM4EGR:
         LDW     Y,#(TIM4_EGR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       TIM4_CNTR    ( -- a )

         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM4_CNTR"
TIM4CNTR:
         LDW     Y,#(TIM4_CNTR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       TIM4_PSCR    ( -- a )
; 3 (1/8)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM4_PSCR"
TIM4PSCR:
         LDW     Y,#(TIM4_PSCR)
         SUBW    X,#2
         LDW     (X),Y
         RET

;       TIM4_ARR    ( -- a )
; 0xCF (Reload 0.104 ms)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM4_ARR"
TIM4ARR:
         LDW     Y,#(TIM4_ARR)
         SUBW    X,#2
         LDW     (X),Y
         RET

