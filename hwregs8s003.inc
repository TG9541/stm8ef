; STM8S003F3P6 and STM8S103F3P6 register addresses
; ***** 6.2.1 I/O port hardware register map
; ***** Port A
;       PA_ODR    ( -- a )
; Port A data output latch register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PA_ODR"
PAODR:
         DoLitW PA_ODR
         RET

;       PA_IDR    ( -- a )
; Port A input pin value register (0xXX)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PA_IDR"
PAIDR:
         DoLitW PA_IDR
         RET

;       PA_DDR    ( -- a )
; Port A data direction register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PA_DDR"
PADDR:
         DoLitW PA_DDR
         RET

;       PA_CR1    ( -- a )
; Port A control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PA_CR1"
PACR1:
         DoLitW PA_CR1
         RET

;       PA_CR2    ( -- a )
; Port A control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PA_CR2"
PACR2:
         DoLitW PA_CR2
         RET

; ***** Port B
;       PB_ODR    ( -- a )
; Port B data output latch register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PB_ODR"
PBODR:
         DoLitW PB_ODR
         RET

;       PB_IDR    ( -- a )
; Port B input pin value register (0xXX)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PB_IDR"
PBIDR:
         DoLitW PB_IDR
         RET

;       PB_DDR    ( -- a )
; Port B data direction register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PB_DDR"
PBDDR:
         DoLitW PB_DDR
         RET

;       PB_CR1    ( -- a )
; Port B control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PB_CR1"
PBCR1:
         DoLitW PB_CR1
         RET

;       PB_CR2    ( -- a )
; Port B control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PB_CR2"
PBCR2:
         DoLitW PB_CR2
         RET

; ***** Port C
;       PC_ODR    ( -- a )
; Port C data output latch register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PC_ODR"
PCODR:
         DoLitW PC_ODR
         RET

;       PC_IDR    ( -- a )
; Port C input pin value register (0xXX)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PC_IDR"
PCIDR:
         DoLitW PC_IDR
         RET

;       PC_DDR    ( -- a )
; Port C data direction register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PC_DDR"
PCDDR:
         DoLitW PC_DDR
         RET

;       PC_CR1    ( -- a )
; Port C control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PC_CR1"
PCCR1:
         DoLitW PC_CR1
         RET

;       PC_CR2    ( -- a )
; Port C control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PC_CR2"
PCCR2:
         DoLitW PC_CR2
         RET

; ***** Port D
;       PD_ODR    ( -- a )
; Port D data output latch register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PD_ODR"
PDODR:
         DoLitW PD_ODR
         RET

;       PD_IDR    ( -- a )
; Port D input pin value register (0xXX)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PD_IDR"
PDIDR:
         DoLitW PD_IDR
         RET

;       PD_DDR    ( -- a )
; Port D data direction register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PD_DDR"
PDDDR:
         DoLitW PD_DDR
         RET

;       PD_CR1    ( -- a )
; Port D control register 1 (0x02)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PD_CR1"
PDCR1:
         DoLitW PD_CR1
         RET

;       PD_CR2    ( -- a )
; Port D control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PD_CR2"
PDCR2:
         DoLitW PD_CR2
         RET

; ***** Port E
        .ifne  0

;       PE_ODR    ( -- a )
; Port E data output latch register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PE_ODR"
PEODR:
         DoLitW PE_ODR
         RET

;       PE_IDR    ( -- a )
; Port E input pin value register (0xXX)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PE_IDR"
PEIDR:
         DoLitW PE_IDR
         RET

;       PE_DDR    ( -- a )
; Port E data direction register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PE_DDR"
PEDDR:
         DoLitW PE_DDR
         RET

;       PE_CR1    ( -- a )
; Port E control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PE_CR1"
PECR1:
         DoLitW PE_CR1
         RET

;       PE_CR2    ( -- a )
; Port E control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PE_CR2"
PECR2:
         DoLitW PE_CR2
         RET

        .endif

; ***** Port F
        .ifne  0

;       PF_ODR    ( -- a )
; Port F data output latch register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PF_ODR"
PFODR:
         DoLitW PF_ODR
         RET

;       PF_IDR    ( -- a )
; Port F input pin value register (0xXX)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PF_IDR"
PFIDR:
         DoLitW PF_IDR
         RET

;       PF_DDR    ( -- a )
; Port F data direction register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PF_DDR"
PFDDR:
         DoLitW PF_DDR
         RET

;       PF_CR1    ( -- a )
; Port F control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PF_CR1"
PFCR1:
         DoLitW PF_CR1
         RET

;       PF_CR2    ( -- a )
; Port F control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PF_CR2"
PFCR2:
         DoLitW PF_CR2
         RET

        .endif

; ***** 6.2.2 General hardware register map
; ***** Flash
        .ifne  0

;       FLASH_CR1    ( -- a )
; Flash control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "FLASH_CR1"
FLASHCR1:
         DoLitW FLASH_CR1
         RET

;       FLASH_CR2    ( -- a )
; Flash control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "FLASH_CR2"
FLASHCR2:
         DoLitW FLASH_CR2
         RET

;       FLASH_NCR2    ( -- a )
; Flash complementary control register 2 (0xFF)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "FLASH_NCR2"
FLASHNCR2:
         DoLitW FLASH_NCR2
         RET

;       FLASH_FPR    ( -- a )
; Flash protection register (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "FLASH_FPR"
FLASHFPR:
         DoLitW FLASH_FPR
         RET

;       FLASH_NFPR    ( -- a )
; Flash complementary protection register (0xFF)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "FLASH_NFPR"
FLASHNFPR:
         DoLitW FLASH_NFPR
         RET

;       FLASH_IAPSR    ( -- a )
; Flash in-application programming status register (0x00)
         .dw     LINK
         LINK =  .
         .db     11
         .ascii  "FLASH_IAPSR"
FLASHIAPSR:
         DoLitW FLASH_IAPSR
         RET

;       FLASH_PUKR    ( -- a )
; Flash Program memory unprotection register (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "FLASH_PUKR"
FLASHPUKR:
         DoLitW FLASH_PUKR
         RET

;       FLASH_DUKR    ( -- a )
; Data EEPROM unprotection register (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "FLASH_DUKR"
FLASHDUKR:
         DoLitW FLASH_DUKR
         RET

        .endif

; ***** ITC
        .ifne  0

;       EXTI_CR1    ( -- a )
; External interrupt control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "EXTI_CR1"
EXTICR1:
         DoLitW EXTI_CR1
         RET

;       EXTI_CR2    ( -- a )
; External interrupt control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "EXTI_CR2"
EXTICR2:
         DoLitW EXTI_CR2
         RET

        .endif

; ***** RST
;       RST_SR    ( -- a )
; Reset status register (0xXX)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "RST_SR"
RSTSR:
         DoLitW RST_SR
         RET

; ***** CLK
        .ifne  0

;       CLK_ICKR    ( -- a )
; Internal clock control register (0x01)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "CLK_ICKR"
CLKICKR:
         DoLitW CLK_ICKR
         RET

;       CLK_ECKR    ( -- a )
; External clock control register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "CLK_ECKR"
CLKECKR:
         DoLitW CLK_ECKR
         RET

;       CLK_CMSR    ( -- a )
; Clock master status register (0xE1)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "CLK_CMSR"
CLKCMSR:
         DoLitW CLK_CMSR
         RET

;       CLK_SWR    ( -- a )
; Clock master switch register (0xE1)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "CLK_SWR"
CLKSWR:
         DoLitW CLK_SWR
         RET

;       CLK_SWCR    ( -- a )
; Clock switch control register (0xXX)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "CLK_SWCR"
CLKSWCR:
         DoLitW CLK_SWCR
         RET

;       CLK_CKDIVR    ( -- a )
; Clock divider register (0x18)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "CLK_CKDIVR"
CLKCKDIVR:
         DoLitW CLK_CKDIVR
         RET

;       CLK_PCKENR1    ( -- a )
; Peripheral clock gating register 1 (0xFF)
         .dw     LINK
         LINK =  .
         .db     11
         .ascii  "CLK_PCKENR1"
CLKPCKENR1:
         DoLitW CLK_PCKENR1
         RET

;       CLK_CSSR    ( -- a )
; Clock security system register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "CLK_CSSR"
CLKCSSR:
         DoLitW CLK_CSSR
         RET

;       CLK_CCOR    ( -- a )
; Configurable clock control register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "CLK_CCOR"
CLKCCOR:
         DoLitW CLK_CCOR
         RET

;       CLK_PCKENR2    ( -- a )
; Peripheral clock gating register 2 (0xFF)
         .dw     LINK
         LINK =  .
         .db     11
         .ascii  "CLK_PCKENR2"
CLKPCKENR2:
         DoLitW CLK_PCKENR2
         RET

;       CLK_HSITRIMR    ( -- a )
; HSI clock calibration trimming register (0x00)
         .dw     LINK
         LINK =  .
         .db     12
         .ascii  "CLK_HSITRIMR"
CLKHSITRIMR:
         DoLitW CLK_HSITRIMR
         RET

        .endif

; ***** SWIM
        .ifne  0

;       CLK_SWIMCCR    ( -- a )
; clock control register (0bXXXXXXX0)
         .dw     LINK
         LINK =  .
         .db     11
         .ascii  "CLK_SWIMCCR"
CLKSWIMCCR:
         DoLitW CLK_SWIMCCR
         RET

        .endif

; ***** WWDG
        .ifne  0

;       WWDG_CR    ( -- a )
; WWDG control register (0x7F)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "WWDG_CR"
WWDGCR:
         DoLitW WWDG_CR
         RET

;       WWDG_WR    ( -- a )
; WWDR window register (0x7F)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "WWDG_WR"
WWDGWR:
         DoLitW WWDG_WR
         RET

        .endif

; ***** IWDG
;       IWDG_KR    ( -- a )
; IWDG key register (0xXX)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "IWDG_KR"
IWDGKR:
         DoLitW IWDG_KR
         RET

;       IWDG_PR    ( -- a )
; IWDG prescaler register (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "IWDG_PR"
IWDGPR:
         DoLitW IWDG_PR
         RET

;       IWDG_RLR    ( -- a )
; IWDG reload register (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "IWDG_RLR"
IWDGRLR:
         DoLitW IWDG_RLR
         RET

; ***** AWU
;       AWU_CSR1    ( -- a )
; AWU control/status register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "AWU_CSR1"
AWUCSR1:
         DoLitW AWU_CSR1
         RET

;       AWU_APR    ( -- a )
; AWU asynchronous prescaler buffer register (0x3F)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "AWU_APR"
AWUAPR:
         DoLitW AWU_APR
         RET

;       AWU_TBR    ( -- a )
; AWU timebase selection register (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "AWU_TBR"
AWUTBR:
         DoLitW AWU_TBR
         RET

; ***** BEEP
;       BEEP_CSR    ( -- a )
; BEEP control/status register (0x1F)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "BEEP_CSR"
BEEPCSR:
         DoLitW BEEP_CSR
         RET

; ***** SPI
;       SPI_CR1    ( -- a )
; SPI control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "SPI_CR1"
SPICR1:
         DoLitW SPI_CR1
         RET

;       SPI_CR2    ( -- a )
; SPI control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "SPI_CR2"
SPICR2:
         DoLitW SPI_CR2
         RET

;       SPI_ICR    ( -- a )
; SPI interrupt control register (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "SPI_ICR"
SPIICR:
         DoLitW SPI_ICR
         RET

;       SPI_SR    ( -- a )
; SPI status register (0x02)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "SPI_SR"
SPISR:
         DoLitW SPI_SR
         RET

;       SPI_DR    ( -- a )
; SPI data register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "SPI_DR"
SPIDR:
         DoLitW SPI_DR
         RET

;       SPI_CRCPR    ( -- a )
; SPI CRC polynomial register (0x07)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "SPI_CRCPR"
SPICRCPR:
         DoLitW SPI_CRCPR
         RET

;       SPI_RXCRCR    ( -- a )
; SPI Rx CRC register (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "SPI_RXCRCR"
SPIRXCRCR:
         DoLitW SPI_RXCRCR
         RET

;       SPI_TXCRCR    ( -- a )
; SPI Tx CRC register (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "SPI_TXCRCR"
SPITXCRCR:
         DoLitW SPI_TXCRCR
         RET

; ***** I2C
;       I2C_CR1    ( -- a )
; I2C control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "I2C_CR1"
I2CCR1:
         DoLitW I2C_CR1
         RET

;       I2C_CR2    ( -- a )
; I2C control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "I2C_CR2"
I2CCR2:
         DoLitW I2C_CR2
         RET

;       I2C_FREQR    ( -- a )
; I2C frequency register (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "I2C_FREQR"
I2CFREQR:
         DoLitW I2C_FREQR
         RET

;       I2C_OARL    ( -- a )
; I2C own address register low (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "I2C_OARL"
I2COARL:
         DoLitW I2C_OARL
         RET

;       I2C_OARH    ( -- a )
; I2C own address register high (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "I2C_OARH"
I2COARH:
         DoLitW I2C_OARH
         RET

;       I2C_DR    ( -- a )
; I2C data register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "I2C_DR"
I2CDR:
         DoLitW I2C_DR
         RET

;       I2C_SR1    ( -- a )
; I2C status register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "I2C_SR1"
I2CSR1:
         DoLitW I2C_SR1
         RET

;       I2C_SR2    ( -- a )
; I2C status register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "I2C_SR2"
I2CSR2:
         DoLitW I2C_SR2
         RET

;       I2C_SR3    ( -- a )
; I2C status register 3 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "I2C_SR3"
I2CSR3:
         DoLitW I2C_SR3
         RET

;       I2C_ITR    ( -- a )
; I2C interrupt control register (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "I2C_ITR"
I2CITR:
         DoLitW I2C_ITR
         RET

;       I2C_CCRL    ( -- a )
; I2C clock control register low (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "I2C_CCRL"
I2CCCRL:
         DoLitW I2C_CCRL
         RET

;       I2C_CCRH    ( -- a )
; I2C clock control register high (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "I2C_CCRH"
I2CCCRH:
         DoLitW I2C_CCRH
         RET

;       I2C_TRISER    ( -- a )
; I2C TRISE register (0x02)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "I2C_TRISER"
I2CTRISER:
         DoLitW I2C_TRISER
         RET

;       I2C_PECR    ( -- a )
; I2C packet error checking register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "I2C_PECR"
I2CPECR:
         DoLitW I2C_PECR
         RET

; ***** UART1 
        .ifeq HAS_TXUART+HAS_RXUART

;       UART1_SR    ( -- a )
; UART1 status register (0xC0)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "UART1_SR"
UART1SR:
         DoLitW UART1_SR
         RET

;       UART1_DR    ( -- a )
; UART1 data register (0xXX)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "UART1_DR"
UART1DR:
         DoLitW UART1_DR
         RET

;       UART1_BRR1    ( -- a )
; UART1 baud rate register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "UART1_BRR1"
UART1BRR1:
         DoLitW UART1_BRR1
         RET

;       UART1_BRR2    ( -- a )
; UART1 baud rate register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "UART1_BRR2"
UART1BRR2:
         DoLitW UART1_BRR2
         RET

;       UART1_CR1    ( -- a )
; UART1 control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "UART1_CR1"
UART1CR1:
         DoLitW UART1_CR1
         RET

;       UART1_CR2    ( -- a )
; UART1 control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "UART1_CR2"
UART1CR2:
         DoLitW UART1_CR2
         RET

;       UART1_CR3    ( -- a )
; UART1 control register 3 (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "UART1_CR3"
UART1CR3:
         DoLitW UART1_CR3
         RET

;       UART1_CR4    ( -- a )
; UART1 control register 4 (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "UART1_CR4"
UART1CR4:
         DoLitW UART1_CR4
         RET

;       UART1_CR5    ( -- a )
; UART1 control register 5 (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "UART1_CR5"
UART1CR5:
         DoLitW UART1_CR5
         RET

;       UART1_GTR    ( -- a )
; UART1 guard time register (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "UART1_GTR"
UART1GTR:
         DoLitW UART1_GTR
         RET

;       UART1_PSCR    ( -- a )
; UART1 prescaler register (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "UART1_PSCR"
UART1PSCR:
         DoLitW UART1_PSCR
         RET

        .endif

; ***** TIM1
;       TIM1_CR1    ( -- a )
; TIM1 control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_CR1"
TIM1CR1:
         DoLitW TIM1_CR1
         RET

;       TIM1_CR2    ( -- a )
; TIM1 control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_CR2"
TIM1CR2:
         DoLitW TIM1_CR2
         RET

;       TIM1_SMCR    ( -- a )
; TIM1 slave mode control register (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM1_SMCR"
TIM1SMCR:
         DoLitW TIM1_SMCR
         RET

;       TIM1_ETR    ( -- a )
; TIM1 external trigger register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_ETR"
TIM1ETR:
         DoLitW TIM1_ETR
         RET

;       TIM1_IER    ( -- a )
; TIM1 Interrupt enable register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_IER"
TIM1IER:
         DoLitW TIM1_IER
         RET

;       TIM1_SR1    ( -- a )
; TIM1 status register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_SR1"
TIM1SR1:
         DoLitW TIM1_SR1
         RET

;       TIM1_SR2    ( -- a )
; TIM1 status register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_SR2"
TIM1SR2:
         DoLitW TIM1_SR2
         RET

;       TIM1_EGR    ( -- a )
; TIM1 event generation register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_EGR"
TIM1EGR:
         DoLitW TIM1_EGR
         RET

;       TIM1_CCMR1    ( -- a )
; TIM1 capture/compare mode register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCMR1"
TIM1CCMR1:
         DoLitW TIM1_CCMR1
         RET

;       TIM1_CCMR2    ( -- a )
; TIM1 capture/compare mode register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCMR2"
TIM1CCMR2:
         DoLitW TIM1_CCMR2
         RET

;       TIM1_CCMR3    ( -- a )
; TIM1 capture/compare mode register 3 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCMR3"
TIM1CCMR3:
         DoLitW TIM1_CCMR3
         RET

;       TIM1_CCMR4    ( -- a )
; TIM1 capture/compare mode register 4 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCMR4"
TIM1CCMR4:
         DoLitW TIM1_CCMR4
         RET

;       TIM1_CCER1    ( -- a )
; TIM1 capture/compare enable register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCER1"
TIM1CCER1:
         DoLitW TIM1_CCER1
         RET

;       TIM1_CCER2    ( -- a )
; TIM1 capture/compare enable register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCER2"
TIM1CCER2:
         DoLitW TIM1_CCER2
         RET

;       TIM1_CNTRH    ( -- a )
; TIM1 counter high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CNTRH"
TIM1CNTRH:
         DoLitW TIM1_CNTRH
         RET

;       TIM1_CNTRL    ( -- a )
; TIM1 counter low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CNTRL"
TIM1CNTRL:
         DoLitW TIM1_CNTRL
         RET

;       TIM1_PSCRH    ( -- a )
; TIM1 prescaler register high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_PSCRH"
TIM1PSCRH:
         DoLitW TIM1_PSCRH
         RET

;       TIM1_PSCRL    ( -- a )
; TIM1 prescaler register low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_PSCRL"
TIM1PSCRL:
         DoLitW TIM1_PSCRL
         RET

;       TIM1_ARRH    ( -- a )
; TIM1 auto-reload register high (0xFF)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM1_ARRH"
TIM1ARRH:
         DoLitW TIM1_ARRH
         RET

;       TIM1_ARRL    ( -- a )
; TIM1 auto-reload register low (0xFF)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM1_ARRL"
TIM1ARRL:
         DoLitW TIM1_ARRL
         RET

;       TIM1_RCR    ( -- a )
; TIM1 repetition counter register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_RCR"
TIM1RCR:
         DoLitW TIM1_RCR
         RET

;       TIM1_CCR1H    ( -- a )
; TIM1 capture/compare register 1 high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCR1H"
TIM1CCR1H:
         DoLitW TIM1_CCR1H
         RET

;       TIM1_CCR1L    ( -- a )
; TIM1 capture/compare register 1 low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCR1L"
TIM1CCR1L:
         DoLitW TIM1_CCR1L
         RET

;       TIM1_CCR2H    ( -- a )
; TIM1 capture/compare register 2 high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCR2H"
TIM1CCR2H:
         DoLitW TIM1_CCR2H
         RET

;       TIM1_CCR2L    ( -- a )
; TIM1 capture/compare register 2 low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCR2L"
TIM1CCR2L:
         DoLitW TIM1_CCR2L
         RET

;       TIM1_CCR3H    ( -- a )
; TIM1 capture/compare register 3 high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCR3H"
TIM1CCR3H:
         DoLitW TIM1_CCR3H
         RET

;       TIM1_CCR3L    ( -- a )
; TIM1 capture/compare register 3 low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCR3L"
TIM1CCR3L:
         DoLitW TIM1_CCR3L
         RET

;       TIM1_CCR4H    ( -- a )
; TIM1 capture/compare register 4 high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCR4H"
TIM1CCR4H:
         DoLitW TIM1_CCR4H
         RET

;       TIM1_CCR4L    ( -- a )
; TIM1 capture/compare register 4 low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCR4L"
TIM1CCR4L:
         DoLitW TIM1_CCR4L
         RET

;       TIM1_BKR    ( -- a )
; TIM1 break register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_BKR"
TIM1BKR:
         DoLitW TIM1_BKR
         RET

;       TIM1_DTR    ( -- a )
; TIM1 dead-time register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_DTR"
TIM1DTR:
         DoLitW TIM1_DTR
         RET

;       TIM1_OISR    ( -- a )
; TIM1 output idle state register (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM1_OISR"
TIM1OISR:
         DoLitW TIM1_OISR
         RET

; ***** TIM2 
        .ifeq HAS_BACKGROUND

;       TIM2_CR1    ( -- a )
; TIM2 control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM2_CR1"
TIM2CR1:
         DoLitW TIM2_CR1
         RET

;       TIM2_IER    ( -- a )
; TIM2 interrupt enable register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM2_IER"
TIM2IER:
         DoLitW TIM2_IER
         RET

;       TIM2_SR1    ( -- a )
; TIM2 status register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM2_SR1"
TIM2SR1:
         DoLitW TIM2_SR1
         RET

;       TIM2_SR2    ( -- a )
; TIM2 status register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM2_SR2"
TIM2SR2:
         DoLitW TIM2_SR2
         RET

;       TIM2_EGR    ( -- a )
; TIM2 event generation register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM2_EGR"
TIM2EGR:
         DoLitW TIM2_EGR
         RET

;       TIM2_CCMR1    ( -- a )
; TIM2 capture/compare mode register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCMR1"
TIM2CCMR1:
         DoLitW TIM2_CCMR1
         RET

;       TIM2_CCMR2    ( -- a )
; TIM2 capture/compare mode register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCMR2"
TIM2CCMR2:
         DoLitW TIM2_CCMR2
         RET

;       TIM2_CCMR3    ( -- a )
; TIM2 capture/compare mode register 3 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCMR3"
TIM2CCMR3:
         DoLitW TIM2_CCMR3
         RET

;       TIM2_CCER1    ( -- a )
; TIM2 capture/compare enable register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCER1"
TIM2CCER1:
         DoLitW TIM2_CCER1
         RET

;       TIM2_CCER2    ( -- a )
; TIM2 capture/compare enable register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCER2"
TIM2CCER2:
         DoLitW TIM2_CCER2
         RET

;       TIM2_CNTRH    ( -- a )
; TIM2 counter high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CNTRH"
TIM2CNTRH:
         DoLitW TIM2_CNTRH
         RET

;       TIM2_CNTRL    ( -- a )
; TIM2 counter low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CNTRL"
TIM2CNTRL:
         DoLitW TIM2_CNTRL
         RET

;       TIM2_PSCR    ( -- a )
; TIM2 prescaler register (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM2_PSCR"
TIM2PSCR:
         DoLitW TIM2_PSCR
         RET

;       TIM2_ARRH    ( -- a )
; TIM2 auto-reload register high (0xFF)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM2_ARRH"
TIM2ARRH:
         DoLitW TIM2_ARRH
         RET

;       TIM2_ARRL    ( -- a )
; TIM2 auto-reload register low (0xFF)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM2_ARRL"
TIM2ARRL:
         DoLitW TIM2_ARRL
         RET

;       TIM2_CCR1H    ( -- a )
; TIM2 capture/compare register 1 high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCR1H"
TIM2CCR1H:
         DoLitW TIM2_CCR1H
         RET

;       TIM2_CCR1L    ( -- a )
; TIM2 capture/compare register 1 low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCR1L"
TIM2CCR1L:
         DoLitW TIM2_CCR1L
         RET

;       TIM2_CCR2H    ( -- a )
; TIM2 capture/compare reg. 2 high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCR2H"
TIM2CCR2H:
         DoLitW TIM2_CCR2H
         RET

;       TIM2_CCR2L    ( -- a )
; TIM2 capture/compare register 2 low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCR2L"
TIM2CCR2L:
         DoLitW TIM2_CCR2L
         RET

;       TIM2_CCR3H    ( -- a )
; TIM2 capture/compare register 3 high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCR3H"
TIM2CCR3H:
         DoLitW TIM2_CCR3H
         RET

;       TIM2_CCR3L    ( -- a )
; TIM2 capture/compare register 3 low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCR3L"
TIM2CCR3L:
         DoLitW TIM2_CCR3L
         RET

        .endif

; ***** TIM4 
        .ifeq HAS_TXSIM+HAS_RXSIM

;       TIM4_CR1    ( -- a )
; TIM4 control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM4_CR1"
TIM4CR1:
         DoLitW TIM4_CR1
         RET

;       TIM4_IER    ( -- a )
; TIM4 interrupt enable register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM4_IER"
TIM4IER:
         DoLitW TIM4_IER
         RET

;       TIM4_SR    ( -- a )
; TIM4 status register (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "TIM4_SR"
TIM4SR:
         DoLitW TIM4_SR
         RET

;       TIM4_EGR    ( -- a )
; TIM4 event generation register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM4_EGR"
TIM4EGR:
         DoLitW TIM4_EGR
         RET

;       TIM4_CNTR    ( -- a )
; TIM4 counter (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM4_CNTR"
TIM4CNTR:
         DoLitW TIM4_CNTR
         RET

;       TIM4_PSCR    ( -- a )
; TIM4 prescaler register (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM4_PSCR"
TIM4PSCR:
         DoLitW TIM4_PSCR
         RET

;       TIM4_ARR    ( -- a )
; TIM4 auto-reload register (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM4_ARR"
TIM4ARR:
         DoLitW TIM4_ARR
         RET

        .endif

; ***** ADC1 
        .ifeq HAS_ADC

;       ADC_DBxR    ( -- a )
; ADC data buffer registers 0x53E0 to 0x53F3 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ADC_DBxR"
ADCDBxR:
         DoLitW ADC_DBxR
         RET

;       ADC_CSR    ( -- a )
; ADC control/status register (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "ADC_CSR"
ADCCSR:
         DoLitW ADC_CSR
         RET

;       ADC_CR1    ( -- a )
; ADC configuration register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "ADC_CR1"
ADCCR1:
         DoLitW ADC_CR1
         RET

;       ADC_CR2    ( -- a )
; ADC configuration register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "ADC_CR2"
ADCCR2:
         DoLitW ADC_CR2
         RET

;       ADC_CR3    ( -- a )
; ADC configuration register 3 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "ADC_CR3"
ADCCR3:
         DoLitW ADC_CR3
         RET

;       ADC_DRH    ( -- a )
; ADC data register high (0xXX)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "ADC_DRH"
ADCDRH:
         DoLitW ADC_DRH
         RET

;       ADC_DRL    ( -- a )
; ADC data register low (0xXX)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "ADC_DRL"
ADCDRL:
         DoLitW ADC_DRL
         RET

;       ADC_TDRH    ( -- a )
; ADC Schmitt trigger disable register high (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ADC_TDRH"
ADCTDRH:
         DoLitW ADC_TDRH
         RET

;       ADC_TDRL    ( -- a )
; ADC Schmitt trigger disable register low (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ADC_TDRL"
ADCTDRL:
         DoLitW ADC_TDRL
         RET

;       ADC_HTRH    ( -- a )
; ADC high threshold register high (0x03)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ADC_HTRH"
ADCHTRH:
         DoLitW ADC_HTRH
         RET

;       ADC_HTRL    ( -- a )
; ADC high threshold register low (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ADC_HTRL"
ADCHTRL:
         DoLitW ADC_HTRL
         RET

;       ADC_LTRH    ( -- a )
; ADC low threshold register high (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ADC_LTRH"
ADCLTRH:
         DoLitW ADC_LTRH
         RET

;       ADC_LTRL    ( -- a )
; ADC low threshold register low (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ADC_LTRL"
ADCLTRL:
         DoLitW ADC_LTRL
         RET

;       ADC_AWSRH    ( -- a )
; ADC analog watchdog status register high (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "ADC_AWSRH"
ADCAWSRH:
         DoLitW ADC_AWSRH
         RET

;       ADC_AWSRL    ( -- a )
; ADC analog watchdog status register low (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "ADC_AWSRL"
ADCAWSRL:
         DoLitW ADC_AWSRL
         RET

;       ADC_AWCRH    ( -- a )
; ADC analog watchdog control register high (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "ADC_AWCRH"
ADCAWCRH:
         DoLitW ADC_AWCRH
         RET

;       ADC_AWCRL    ( -- a )
; ADC analog watchdog control register low (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "ADC_AWCRL"
ADCAWCRL:
         DoLitW ADC_AWCRL
         RET

        .endif

; ***** 6.2.3 CPU/SWIM/debug module/interrupt controller registers
; ***** CPU
        .ifne  0

;       CPU_A    ( -- a )
; Accumulator (0x00)
         .dw     LINK
         LINK =  .
         .db     5
         .ascii  "CPU_A"
CPUA:
         DoLitW CPU_A
         RET

;       CPU_PCE    ( -- a )
; Program counter extended (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "CPU_PCE"
CPUPCE:
         DoLitW CPU_PCE
         RET

;       CPU_PCH    ( -- a )
; Program counter high (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "CPU_PCH"
CPUPCH:
         DoLitW CPU_PCH
         RET

;       CPU_PCL    ( -- a )
; Program counter low (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "CPU_PCL"
CPUPCL:
         DoLitW CPU_PCL
         RET

;       CPU_XH    ( -- a )
; X index register high (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "CPU_XH"
CPUXH:
         DoLitW CPU_XH
         RET

;       CPU_XL    ( -- a )
; X index register low (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "CPU_XL"
CPUXL:
         DoLitW CPU_XL
         RET

;       CPU_YH    ( -- a )
; Y index register high (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "CPU_YH"
CPUYH:
         DoLitW CPU_YH
         RET

;       CPU_YL    ( -- a )
; Y index register low (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "CPU_YL"
CPUYL:
         DoLitW CPU_YL
         RET

;       CPU_SPH    ( -- a )
; Stack pointer high (0x03)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "CPU_SPH"
CPUSPH:
         DoLitW CPU_SPH
         RET

;       CPU_SPL    ( -- a )
; Stack pointer low (0xFF)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "CPU_SPL"
CPUSPL:
         DoLitW CPU_SPL
         RET

;       CPU_CCR    ( -- a )
; Condition code register (0x28)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "CPU_CCR"
CPUCCR:
         DoLitW CPU_CCR
         RET

        .endif

; ***** CFG
;       CFG_GCR    ( -- a )
; Global configuration register (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "CFG_GCR"
CFGGCR:
         DoLitW CFG_GCR
         RET

; ***** ITC
        .ifne  HAS_CPNVM

;       ITC_SPR1    ( -- a )
; Interrupt software priority register 1 (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ITC_SPR1"
ITCSPR1:
         DoLitW ITC_SPR1
         RET

;       ITC_SPR2    ( -- a )
; Interrupt software priority register 2 (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ITC_SPR2"
ITCSPR2:
         DoLitW ITC_SPR2
         RET

;       ITC_SPR3    ( -- a )
; Interrupt software priority register 3 (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ITC_SPR3"
ITCSPR3:
         DoLitW ITC_SPR3
         RET

;       ITC_SPR4    ( -- a )
; Interrupt software priority register 4 (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ITC_SPR4"
ITCSPR4:
         DoLitW ITC_SPR4
         RET

;       ITC_SPR5    ( -- a )
; Interrupt software priority register 5 (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ITC_SPR5"
ITCSPR5:
         DoLitW ITC_SPR5
         RET

;       ITC_SPR6    ( -- a )
; Interrupt software priority register 6 (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ITC_SPR6"
ITCSPR6:
         DoLitW ITC_SPR6
         RET

;       ITC_SPR7    ( -- a )
; Interrupt software priority register 7 (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ITC_SPR7"
ITCSPR7:
         DoLitW ITC_SPR7
         RET

;       ITC_SPR8    ( -- a )
; Interrupt software priority register 8 (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ITC_SPR8"
ITCSPR8:
         DoLitW ITC_SPR8
         RET

        .endif

; ***** SWIM
        .ifne  0

;       SWIM_CSR    ( -- a )
; SWIM control status register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "SWIM_CSR"
SWIMCSR:
         DoLitW SWIM_CSR
         RET

        .endif

; ***** DM
        .ifne  0

;       DM_BK1RE    ( -- a )
; DM breakpoint 1 register extended byte (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "DM_BK1RE"
DMBK1RE:
         DoLitW DM_BK1RE
         RET

;       DM_BK1RH    ( -- a )
; DM breakpoint 1 register high byte (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "DM_BK1RH"
DMBK1RH:
         DoLitW DM_BK1RH
         RET

;       DM_BK1RL    ( -- a )
; DM breakpoint 1 register low byte (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "DM_BK1RL"
DMBK1RL:
         DoLitW DM_BK1RL
         RET

;       DM_BK2RE    ( -- a )
; DM breakpoint 2 register extended byte (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "DM_BK2RE"
DMBK2RE:
         DoLitW DM_BK2RE
         RET

;       DM_BK2RH    ( -- a )
; DM breakpoint 2 register high byte (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "DM_BK2RH"
DMBK2RH:
         DoLitW DM_BK2RH
         RET

;       DM_BK2RL    ( -- a )
; DM breakpoint 2 register low byte (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "DM_BK2RL"
DMBK2RL:
         DoLitW DM_BK2RL
         RET

;       DM_CR1    ( -- a )
; DM debug module control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "DM_CR1"
DMCR1:
         DoLitW DM_CR1
         RET

;       DM_CR2    ( -- a )
; DM debug module control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "DM_CR2"
DMCR2:
         DoLitW DM_CR2
         RET

;       DM_CSR1    ( -- a )
; DM debug module control/status register 1 (0x10)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "DM_CSR1"
DMCSR1:
         DoLitW DM_CSR1
         RET

;       DM_CSR2    ( -- a )
; DM debug module control/status register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "DM_CSR2"
DMCSR2:
         DoLitW DM_CSR2
         RET

;       DM_ENFCTR    ( -- a )
; DM enable function register (0xFF)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "DM_ENFCTR"
DMENFCTR:
         DoLitW DM_ENFCTR
         RET

        .endif

