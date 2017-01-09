;       DOLITEXIT   ( -- w )    ( TOS STM8: -- Y,Z,N )
;       Push an inline literal and exit

DOLITEXIT:
        DECW    X
        DECW    X
        EXGW    X,Y ; Y is discarded
        POPW    X
        LDW     X,(X)
        EXGW    X,Y
        LDW     (X),Y
        RET

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
         CALL    DOLITEXIT
         .dw PA_ODR

;       PA_IDR    ( -- a )
; Port A input pin value register (0xXX)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PA_IDR"
PAIDR:
         CALL    DOLITEXIT
         .dw PA_IDR

;       PA_DDR    ( -- a )
; Port A data direction register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PA_DDR"
PADDR:
         CALL    DOLITEXIT
         .dw PA_DDR

;       PA_CR1    ( -- a )
; Port A control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PA_CR1"
PACR1:
         CALL    DOLITEXIT
         .dw PA_CR1

;       PA_CR2    ( -- a )
; Port A control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PA_CR2"
PACR2:
         CALL    DOLITEXIT
         .dw PA_CR2

; ***** Port B
;       PB_ODR    ( -- a )
; Port B data output latch register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PB_ODR"
PBODR:
         CALL    DOLITEXIT
         .dw PB_ODR

;       PB_IDR    ( -- a )
; Port B input pin value register (0xXX)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PB_IDR"
PBIDR:
         CALL    DOLITEXIT
         .dw PB_IDR

;       PB_DDR    ( -- a )
; Port B data direction register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PB_DDR"
PBDDR:
         CALL    DOLITEXIT
         .dw PB_DDR

;       PB_CR1    ( -- a )
; Port B control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PB_CR1"
PBCR1:
         CALL    DOLITEXIT
         .dw PB_CR1

;       PB_CR2    ( -- a )
; Port B control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PB_CR2"
PBCR2:
         CALL    DOLITEXIT
         .dw PB_CR2

; ***** Port C
;       PC_ODR    ( -- a )
; Port C data output latch register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PC_ODR"
PCODR:
         CALL    DOLITEXIT
         .dw PC_ODR

;       PC_IDR    ( -- a )
; Port C input pin value register (0xXX)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PC_IDR"
PCIDR:
         CALL    DOLITEXIT
         .dw PC_IDR

;       PC_DDR    ( -- a )
; Port C data direction register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PC_DDR"
PCDDR:
         CALL    DOLITEXIT
         .dw PC_DDR

;       PC_CR1    ( -- a )
; Port C control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PC_CR1"
PCCR1:
         CALL    DOLITEXIT
         .dw PC_CR1

;       PC_CR2    ( -- a )
; Port C control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PC_CR2"
PCCR2:
         CALL    DOLITEXIT
         .dw PC_CR2

; ***** Port D
;       PD_ODR    ( -- a )
; Port D data output latch register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PD_ODR"
PDODR:
         CALL    DOLITEXIT
         .dw PD_ODR

;       PD_IDR    ( -- a )
; Port D input pin value register (0xXX)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PD_IDR"
PDIDR:
         CALL    DOLITEXIT
         .dw PD_IDR

;       PD_DDR    ( -- a )
; Port D data direction register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PD_DDR"
PDDDR:
         CALL    DOLITEXIT
         .dw PD_DDR

;       PD_CR1    ( -- a )
; Port D control register 1 (0x02)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PD_CR1"
PDCR1:
         CALL    DOLITEXIT
         .dw PD_CR1

;       PD_CR2    ( -- a )
; Port D control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PD_CR2"
PDCR2:
         CALL    DOLITEXIT
         .dw PD_CR2

; ***** Port E
        .ifne  0

;       PE_ODR    ( -- a )
; Port E data output latch register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PE_ODR"
PEODR:
         CALL    DOLITEXIT
         .dw PE_ODR

;       PE_IDR    ( -- a )
; Port E input pin value register (0xXX)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PE_IDR"
PEIDR:
         CALL    DOLITEXIT
         .dw PE_IDR

;       PE_DDR    ( -- a )
; Port E data direction register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PE_DDR"
PEDDR:
         CALL    DOLITEXIT
         .dw PE_DDR

;       PE_CR1    ( -- a )
; Port E control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PE_CR1"
PECR1:
         CALL    DOLITEXIT
         .dw PE_CR1

;       PE_CR2    ( -- a )
; Port E control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PE_CR2"
PECR2:
         CALL    DOLITEXIT
         .dw PE_CR2

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
         CALL    DOLITEXIT
         .dw PF_ODR

;       PF_IDR    ( -- a )
; Port F input pin value register (0xXX)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PF_IDR"
PFIDR:
         CALL    DOLITEXIT
         .dw PF_IDR

;       PF_DDR    ( -- a )
; Port F data direction register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PF_DDR"
PFDDR:
         CALL    DOLITEXIT
         .dw PF_DDR

;       PF_CR1    ( -- a )
; Port F control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PF_CR1"
PFCR1:
         CALL    DOLITEXIT
         .dw PF_CR1

;       PF_CR2    ( -- a )
; Port F control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "PF_CR2"
PFCR2:
         CALL    DOLITEXIT
         .dw PF_CR2

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
         CALL    DOLITEXIT
         .dw FLASH_CR1

;       FLASH_CR2    ( -- a )
; Flash control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "FLASH_CR2"
FLASHCR2:
         CALL    DOLITEXIT
         .dw FLASH_CR2

;       FLASH_NCR2    ( -- a )
; Flash complementary control register 2 (0xFF)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "FLASH_NCR2"
FLASHNCR2:
         CALL    DOLITEXIT
         .dw FLASH_NCR2

;       FLASH_FPR    ( -- a )
; Flash protection register (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "FLASH_FPR"
FLASHFPR:
         CALL    DOLITEXIT
         .dw FLASH_FPR

;       FLASH_NFPR    ( -- a )
; Flash complementary protection register (0xFF)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "FLASH_NFPR"
FLASHNFPR:
         CALL    DOLITEXIT
         .dw FLASH_NFPR

;       FLASH_IAPSR    ( -- a )
; Flash in-application programming status register (0x00)
         .dw     LINK
         LINK =  .
         .db     11
         .ascii  "FLASH_IAPSR"
FLASHIAPSR:
         CALL    DOLITEXIT
         .dw FLASH_IAPSR

;       FLASH_PUKR    ( -- a )
; Flash Program memory unprotection register (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "FLASH_PUKR"
FLASHPUKR:
         CALL    DOLITEXIT
         .dw FLASH_PUKR

;       FLASH_DUKR    ( -- a )
; Data EEPROM unprotection register (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "FLASH_DUKR"
FLASHDUKR:
         CALL    DOLITEXIT
         .dw FLASH_DUKR

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
         CALL    DOLITEXIT
         .dw EXTI_CR1

;       EXTI_CR2    ( -- a )
; External interrupt control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "EXTI_CR2"
EXTICR2:
         CALL    DOLITEXIT
         .dw EXTI_CR2

        .endif

; ***** RST
;       RST_SR    ( -- a )
; Reset status register (0xXX)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "RST_SR"
RSTSR:
         CALL    DOLITEXIT
         .dw RST_SR

; ***** CLK
        .ifne  0

;       CLK_ICKR    ( -- a )
; Internal clock control register (0x01)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "CLK_ICKR"
CLKICKR:
         CALL    DOLITEXIT
         .dw CLK_ICKR

;       CLK_ECKR    ( -- a )
; External clock control register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "CLK_ECKR"
CLKECKR:
         CALL    DOLITEXIT
         .dw CLK_ECKR

;       CLK_CMSR    ( -- a )
; Clock master status register (0xE1)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "CLK_CMSR"
CLKCMSR:
         CALL    DOLITEXIT
         .dw CLK_CMSR

;       CLK_SWR    ( -- a )
; Clock master switch register (0xE1)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "CLK_SWR"
CLKSWR:
         CALL    DOLITEXIT
         .dw CLK_SWR

;       CLK_SWCR    ( -- a )
; Clock switch control register (0xXX)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "CLK_SWCR"
CLKSWCR:
         CALL    DOLITEXIT
         .dw CLK_SWCR

;       CLK_CKDIVR    ( -- a )
; Clock divider register (0x18)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "CLK_CKDIVR"
CLKCKDIVR:
         CALL    DOLITEXIT
         .dw CLK_CKDIVR

;       CLK_PCKENR1    ( -- a )
; Peripheral clock gating register 1 (0xFF)
         .dw     LINK
         LINK =  .
         .db     11
         .ascii  "CLK_PCKENR1"
CLKPCKENR1:
         CALL    DOLITEXIT
         .dw CLK_PCKENR1

;       CLK_CSSR    ( -- a )
; Clock security system register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "CLK_CSSR"
CLKCSSR:
         CALL    DOLITEXIT
         .dw CLK_CSSR

;       CLK_CCOR    ( -- a )
; Configurable clock control register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "CLK_CCOR"
CLKCCOR:
         CALL    DOLITEXIT
         .dw CLK_CCOR

;       CLK_PCKENR2    ( -- a )
; Peripheral clock gating register 2 (0xFF)
         .dw     LINK
         LINK =  .
         .db     11
         .ascii  "CLK_PCKENR2"
CLKPCKENR2:
         CALL    DOLITEXIT
         .dw CLK_PCKENR2

;       CLK_HSITRIMR    ( -- a )
; HSI clock calibration trimming register (0x00)
         .dw     LINK
         LINK =  .
         .db     12
         .ascii  "CLK_HSITRIMR"
CLKHSITRIMR:
         CALL    DOLITEXIT
         .dw CLK_HSITRIMR

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
         CALL    DOLITEXIT
         .dw CLK_SWIMCCR

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
         CALL    DOLITEXIT
         .dw WWDG_CR

;       WWDG_WR    ( -- a )
; WWDR window register (0x7F)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "WWDG_WR"
WWDGWR:
         CALL    DOLITEXIT
         .dw WWDG_WR

        .endif

; ***** IWDG
;       IWDG_KR    ( -- a )
; IWDG key register (0xXX)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "IWDG_KR"
IWDGKR:
         CALL    DOLITEXIT
         .dw IWDG_KR

;       IWDG_PR    ( -- a )
; IWDG prescaler register (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "IWDG_PR"
IWDGPR:
         CALL    DOLITEXIT
         .dw IWDG_PR

;       IWDG_RLR    ( -- a )
; IWDG reload register (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "IWDG_RLR"
IWDGRLR:
         CALL    DOLITEXIT
         .dw IWDG_RLR

; ***** AWU
;       AWU_CSR1    ( -- a )
; AWU control/status register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "AWU_CSR1"
AWUCSR1:
         CALL    DOLITEXIT
         .dw AWU_CSR1

;       AWU_APR    ( -- a )
; AWU asynchronous prescaler buffer register (0x3F)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "AWU_APR"
AWUAPR:
         CALL    DOLITEXIT
         .dw AWU_APR

;       AWU_TBR    ( -- a )
; AWU timebase selection register (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "AWU_TBR"
AWUTBR:
         CALL    DOLITEXIT
         .dw AWU_TBR

; ***** BEEP
;       BEEP_CSR    ( -- a )
; BEEP control/status register (0x1F)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "BEEP_CSR"
BEEPCSR:
         CALL    DOLITEXIT
         .dw BEEP_CSR

; ***** SPI
;       SPI_CR1    ( -- a )
; SPI control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "SPI_CR1"
SPICR1:
         CALL    DOLITEXIT
         .dw SPI_CR1

;       SPI_CR2    ( -- a )
; SPI control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "SPI_CR2"
SPICR2:
         CALL    DOLITEXIT
         .dw SPI_CR2

;       SPI_ICR    ( -- a )
; SPI interrupt control register (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "SPI_ICR"
SPIICR:
         CALL    DOLITEXIT
         .dw SPI_ICR

;       SPI_SR    ( -- a )
; SPI status register (0x02)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "SPI_SR"
SPISR:
         CALL    DOLITEXIT
         .dw SPI_SR

;       SPI_DR    ( -- a )
; SPI data register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "SPI_DR"
SPIDR:
         CALL    DOLITEXIT
         .dw SPI_DR

;       SPI_CRCPR    ( -- a )
; SPI CRC polynomial register (0x07)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "SPI_CRCPR"
SPICRCPR:
         CALL    DOLITEXIT
         .dw SPI_CRCPR

;       SPI_RXCRCR    ( -- a )
; SPI Rx CRC register (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "SPI_RXCRCR"
SPIRXCRCR:
         CALL    DOLITEXIT
         .dw SPI_RXCRCR

;       SPI_TXCRCR    ( -- a )
; SPI Tx CRC register (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "SPI_TXCRCR"
SPITXCRCR:
         CALL    DOLITEXIT
         .dw SPI_TXCRCR

; ***** I2C
;       I2C_CR1    ( -- a )
; I2C control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "I2C_CR1"
I2CCR1:
         CALL    DOLITEXIT
         .dw I2C_CR1

;       I2C_CR2    ( -- a )
; I2C control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "I2C_CR2"
I2CCR2:
         CALL    DOLITEXIT
         .dw I2C_CR2

;       I2C_FREQR    ( -- a )
; I2C frequency register (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "I2C_FREQR"
I2CFREQR:
         CALL    DOLITEXIT
         .dw I2C_FREQR

;       I2C_OARL    ( -- a )
; I2C own address register low (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "I2C_OARL"
I2COARL:
         CALL    DOLITEXIT
         .dw I2C_OARL

;       I2C_OARH    ( -- a )
; I2C own address register high (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "I2C_OARH"
I2COARH:
         CALL    DOLITEXIT
         .dw I2C_OARH

;       I2C_DR    ( -- a )
; I2C data register (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "I2C_DR"
I2CDR:
         CALL    DOLITEXIT
         .dw I2C_DR

;       I2C_SR1    ( -- a )
; I2C status register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "I2C_SR1"
I2CSR1:
         CALL    DOLITEXIT
         .dw I2C_SR1

;       I2C_SR2    ( -- a )
; I2C status register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "I2C_SR2"
I2CSR2:
         CALL    DOLITEXIT
         .dw I2C_SR2

;       I2C_SR3    ( -- a )
; I2C status register 3 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "I2C_SR3"
I2CSR3:
         CALL    DOLITEXIT
         .dw I2C_SR3

;       I2C_ITR    ( -- a )
; I2C interrupt control register (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "I2C_ITR"
I2CITR:
         CALL    DOLITEXIT
         .dw I2C_ITR

;       I2C_CCRL    ( -- a )
; I2C clock control register low (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "I2C_CCRL"
I2CCCRL:
         CALL    DOLITEXIT
         .dw I2C_CCRL

;       I2C_CCRH    ( -- a )
; I2C clock control register high (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "I2C_CCRH"
I2CCCRH:
         CALL    DOLITEXIT
         .dw I2C_CCRH

;       I2C_TRISER    ( -- a )
; I2C TRISE register (0x02)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "I2C_TRISER"
I2CTRISER:
         CALL    DOLITEXIT
         .dw I2C_TRISER

;       I2C_PECR    ( -- a )
; I2C packet error checking register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "I2C_PECR"
I2CPECR:
         CALL    DOLITEXIT
         .dw I2C_PECR

; ***** UART1 
        .ifeq HAS_TXUART+HAS_RXUART

;       UART1_SR    ( -- a )
; UART1 status register (0xC0)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "UART1_SR"
UART1SR:
         CALL    DOLITEXIT
         .dw UART1_SR

;       UART1_DR    ( -- a )
; UART1 data register (0xXX)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "UART1_DR"
UART1DR:
         CALL    DOLITEXIT
         .dw UART1_DR

;       UART1_BRR1    ( -- a )
; UART1 baud rate register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "UART1_BRR1"
UART1BRR1:
         CALL    DOLITEXIT
         .dw UART1_BRR1

;       UART1_BRR2    ( -- a )
; UART1 baud rate register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "UART1_BRR2"
UART1BRR2:
         CALL    DOLITEXIT
         .dw UART1_BRR2

;       UART1_CR1    ( -- a )
; UART1 control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "UART1_CR1"
UART1CR1:
         CALL    DOLITEXIT
         .dw UART1_CR1

;       UART1_CR2    ( -- a )
; UART1 control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "UART1_CR2"
UART1CR2:
         CALL    DOLITEXIT
         .dw UART1_CR2

;       UART1_CR3    ( -- a )
; UART1 control register 3 (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "UART1_CR3"
UART1CR3:
         CALL    DOLITEXIT
         .dw UART1_CR3

;       UART1_CR4    ( -- a )
; UART1 control register 4 (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "UART1_CR4"
UART1CR4:
         CALL    DOLITEXIT
         .dw UART1_CR4

;       UART1_CR5    ( -- a )
; UART1 control register 5 (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "UART1_CR5"
UART1CR5:
         CALL    DOLITEXIT
         .dw UART1_CR5

;       UART1_GTR    ( -- a )
; UART1 guard time register (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "UART1_GTR"
UART1GTR:
         CALL    DOLITEXIT
         .dw UART1_GTR

;       UART1_PSCR    ( -- a )
; UART1 prescaler register (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "UART1_PSCR"
UART1PSCR:
         CALL    DOLITEXIT
         .dw UART1_PSCR

        .endif

; ***** TIM1
;       TIM1_CR1    ( -- a )
; TIM1 control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_CR1"
TIM1CR1:
         CALL    DOLITEXIT
         .dw TIM1_CR1

;       TIM1_CR2    ( -- a )
; TIM1 control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_CR2"
TIM1CR2:
         CALL    DOLITEXIT
         .dw TIM1_CR2

;       TIM1_SMCR    ( -- a )
; TIM1 slave mode control register (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM1_SMCR"
TIM1SMCR:
         CALL    DOLITEXIT
         .dw TIM1_SMCR

;       TIM1_ETR    ( -- a )
; TIM1 external trigger register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_ETR"
TIM1ETR:
         CALL    DOLITEXIT
         .dw TIM1_ETR

;       TIM1_IER    ( -- a )
; TIM1 Interrupt enable register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_IER"
TIM1IER:
         CALL    DOLITEXIT
         .dw TIM1_IER

;       TIM1_SR1    ( -- a )
; TIM1 status register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_SR1"
TIM1SR1:
         CALL    DOLITEXIT
         .dw TIM1_SR1

;       TIM1_SR2    ( -- a )
; TIM1 status register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_SR2"
TIM1SR2:
         CALL    DOLITEXIT
         .dw TIM1_SR2

;       TIM1_EGR    ( -- a )
; TIM1 event generation register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_EGR"
TIM1EGR:
         CALL    DOLITEXIT
         .dw TIM1_EGR

;       TIM1_CCMR1    ( -- a )
; TIM1 capture/compare mode register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCMR1"
TIM1CCMR1:
         CALL    DOLITEXIT
         .dw TIM1_CCMR1

;       TIM1_CCMR2    ( -- a )
; TIM1 capture/compare mode register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCMR2"
TIM1CCMR2:
         CALL    DOLITEXIT
         .dw TIM1_CCMR2

;       TIM1_CCMR3    ( -- a )
; TIM1 capture/compare mode register 3 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCMR3"
TIM1CCMR3:
         CALL    DOLITEXIT
         .dw TIM1_CCMR3

;       TIM1_CCMR4    ( -- a )
; TIM1 capture/compare mode register 4 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCMR4"
TIM1CCMR4:
         CALL    DOLITEXIT
         .dw TIM1_CCMR4

;       TIM1_CCER1    ( -- a )
; TIM1 capture/compare enable register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCER1"
TIM1CCER1:
         CALL    DOLITEXIT
         .dw TIM1_CCER1

;       TIM1_CCER2    ( -- a )
; TIM1 capture/compare enable register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCER2"
TIM1CCER2:
         CALL    DOLITEXIT
         .dw TIM1_CCER2

;       TIM1_CNTRH    ( -- a )
; TIM1 counter high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CNTRH"
TIM1CNTRH:
         CALL    DOLITEXIT
         .dw TIM1_CNTRH

;       TIM1_CNTRL    ( -- a )
; TIM1 counter low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CNTRL"
TIM1CNTRL:
         CALL    DOLITEXIT
         .dw TIM1_CNTRL

;       TIM1_PSCRH    ( -- a )
; TIM1 prescaler register high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_PSCRH"
TIM1PSCRH:
         CALL    DOLITEXIT
         .dw TIM1_PSCRH

;       TIM1_PSCRL    ( -- a )
; TIM1 prescaler register low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_PSCRL"
TIM1PSCRL:
         CALL    DOLITEXIT
         .dw TIM1_PSCRL

;       TIM1_ARRH    ( -- a )
; TIM1 auto-reload register high (0xFF)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM1_ARRH"
TIM1ARRH:
         CALL    DOLITEXIT
         .dw TIM1_ARRH

;       TIM1_ARRL    ( -- a )
; TIM1 auto-reload register low (0xFF)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM1_ARRL"
TIM1ARRL:
         CALL    DOLITEXIT
         .dw TIM1_ARRL

;       TIM1_RCR    ( -- a )
; TIM1 repetition counter register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_RCR"
TIM1RCR:
         CALL    DOLITEXIT
         .dw TIM1_RCR

;       TIM1_CCR1H    ( -- a )
; TIM1 capture/compare register 1 high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCR1H"
TIM1CCR1H:
         CALL    DOLITEXIT
         .dw TIM1_CCR1H

;       TIM1_CCR1L    ( -- a )
; TIM1 capture/compare register 1 low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCR1L"
TIM1CCR1L:
         CALL    DOLITEXIT
         .dw TIM1_CCR1L

;       TIM1_CCR2H    ( -- a )
; TIM1 capture/compare register 2 high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCR2H"
TIM1CCR2H:
         CALL    DOLITEXIT
         .dw TIM1_CCR2H

;       TIM1_CCR2L    ( -- a )
; TIM1 capture/compare register 2 low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCR2L"
TIM1CCR2L:
         CALL    DOLITEXIT
         .dw TIM1_CCR2L

;       TIM1_CCR3H    ( -- a )
; TIM1 capture/compare register 3 high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCR3H"
TIM1CCR3H:
         CALL    DOLITEXIT
         .dw TIM1_CCR3H

;       TIM1_CCR3L    ( -- a )
; TIM1 capture/compare register 3 low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCR3L"
TIM1CCR3L:
         CALL    DOLITEXIT
         .dw TIM1_CCR3L

;       TIM1_CCR4H    ( -- a )
; TIM1 capture/compare register 4 high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCR4H"
TIM1CCR4H:
         CALL    DOLITEXIT
         .dw TIM1_CCR4H

;       TIM1_CCR4L    ( -- a )
; TIM1 capture/compare register 4 low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM1_CCR4L"
TIM1CCR4L:
         CALL    DOLITEXIT
         .dw TIM1_CCR4L

;       TIM1_BKR    ( -- a )
; TIM1 break register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_BKR"
TIM1BKR:
         CALL    DOLITEXIT
         .dw TIM1_BKR

;       TIM1_DTR    ( -- a )
; TIM1 dead-time register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM1_DTR"
TIM1DTR:
         CALL    DOLITEXIT
         .dw TIM1_DTR

;       TIM1_OISR    ( -- a )
; TIM1 output idle state register (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM1_OISR"
TIM1OISR:
         CALL    DOLITEXIT
         .dw TIM1_OISR

; ***** TIM2 
        .ifeq HAS_BACKGROUND

;       TIM2_CR1    ( -- a )
; TIM2 control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM2_CR1"
TIM2CR1:
         CALL    DOLITEXIT
         .dw TIM2_CR1

;       TIM2_IER    ( -- a )
; TIM2 interrupt enable register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM2_IER"
TIM2IER:
         CALL    DOLITEXIT
         .dw TIM2_IER

;       TIM2_SR1    ( -- a )
; TIM2 status register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM2_SR1"
TIM2SR1:
         CALL    DOLITEXIT
         .dw TIM2_SR1

;       TIM2_SR2    ( -- a )
; TIM2 status register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM2_SR2"
TIM2SR2:
         CALL    DOLITEXIT
         .dw TIM2_SR2

;       TIM2_EGR    ( -- a )
; TIM2 event generation register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM2_EGR"
TIM2EGR:
         CALL    DOLITEXIT
         .dw TIM2_EGR

;       TIM2_CCMR1    ( -- a )
; TIM2 capture/compare mode register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCMR1"
TIM2CCMR1:
         CALL    DOLITEXIT
         .dw TIM2_CCMR1

;       TIM2_CCMR2    ( -- a )
; TIM2 capture/compare mode register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCMR2"
TIM2CCMR2:
         CALL    DOLITEXIT
         .dw TIM2_CCMR2

;       TIM2_CCMR3    ( -- a )
; TIM2 capture/compare mode register 3 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCMR3"
TIM2CCMR3:
         CALL    DOLITEXIT
         .dw TIM2_CCMR3

;       TIM2_CCER1    ( -- a )
; TIM2 capture/compare enable register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCER1"
TIM2CCER1:
         CALL    DOLITEXIT
         .dw TIM2_CCER1

;       TIM2_CCER2    ( -- a )
; TIM2 capture/compare enable register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCER2"
TIM2CCER2:
         CALL    DOLITEXIT
         .dw TIM2_CCER2

;       TIM2_CNTRH    ( -- a )
; TIM2 counter high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CNTRH"
TIM2CNTRH:
         CALL    DOLITEXIT
         .dw TIM2_CNTRH

;       TIM2_CNTRL    ( -- a )
; TIM2 counter low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CNTRL"
TIM2CNTRL:
         CALL    DOLITEXIT
         .dw TIM2_CNTRL

;       TIM2_PSCR    ( -- a )
; TIM2 prescaler register (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM2_PSCR"
TIM2PSCR:
         CALL    DOLITEXIT
         .dw TIM2_PSCR

;       TIM2_ARRH    ( -- a )
; TIM2 auto-reload register high (0xFF)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM2_ARRH"
TIM2ARRH:
         CALL    DOLITEXIT
         .dw TIM2_ARRH

;       TIM2_ARRL    ( -- a )
; TIM2 auto-reload register low (0xFF)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM2_ARRL"
TIM2ARRL:
         CALL    DOLITEXIT
         .dw TIM2_ARRL

;       TIM2_CCR1H    ( -- a )
; TIM2 capture/compare register 1 high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCR1H"
TIM2CCR1H:
         CALL    DOLITEXIT
         .dw TIM2_CCR1H

;       TIM2_CCR1L    ( -- a )
; TIM2 capture/compare register 1 low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCR1L"
TIM2CCR1L:
         CALL    DOLITEXIT
         .dw TIM2_CCR1L

;       TIM2_CCR2H    ( -- a )
; TIM2 capture/compare reg. 2 high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCR2H"
TIM2CCR2H:
         CALL    DOLITEXIT
         .dw TIM2_CCR2H

;       TIM2_CCR2L    ( -- a )
; TIM2 capture/compare register 2 low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCR2L"
TIM2CCR2L:
         CALL    DOLITEXIT
         .dw TIM2_CCR2L

;       TIM2_CCR3H    ( -- a )
; TIM2 capture/compare register 3 high (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCR3H"
TIM2CCR3H:
         CALL    DOLITEXIT
         .dw TIM2_CCR3H

;       TIM2_CCR3L    ( -- a )
; TIM2 capture/compare register 3 low (0x00)
         .dw     LINK
         LINK =  .
         .db     10
         .ascii  "TIM2_CCR3L"
TIM2CCR3L:
         CALL    DOLITEXIT
         .dw TIM2_CCR3L

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
         CALL    DOLITEXIT
         .dw TIM4_CR1

;       TIM4_IER    ( -- a )
; TIM4 interrupt enable register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM4_IER"
TIM4IER:
         CALL    DOLITEXIT
         .dw TIM4_IER

;       TIM4_SR    ( -- a )
; TIM4 status register (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "TIM4_SR"
TIM4SR:
         CALL    DOLITEXIT
         .dw TIM4_SR

;       TIM4_EGR    ( -- a )
; TIM4 event generation register (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM4_EGR"
TIM4EGR:
         CALL    DOLITEXIT
         .dw TIM4_EGR

;       TIM4_CNTR    ( -- a )
; TIM4 counter (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM4_CNTR"
TIM4CNTR:
         CALL    DOLITEXIT
         .dw TIM4_CNTR

;       TIM4_PSCR    ( -- a )
; TIM4 prescaler register (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "TIM4_PSCR"
TIM4PSCR:
         CALL    DOLITEXIT
         .dw TIM4_PSCR

;       TIM4_ARR    ( -- a )
; TIM4 auto-reload register (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "TIM4_ARR"
TIM4ARR:
         CALL    DOLITEXIT
         .dw TIM4_ARR

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
         CALL    DOLITEXIT
         .dw ADC_DBxR

;       ADC_CSR    ( -- a )
; ADC control/status register (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "ADC_CSR"
ADCCSR:
         CALL    DOLITEXIT
         .dw ADC_CSR

;       ADC_CR1    ( -- a )
; ADC configuration register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "ADC_CR1"
ADCCR1:
         CALL    DOLITEXIT
         .dw ADC_CR1

;       ADC_CR2    ( -- a )
; ADC configuration register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "ADC_CR2"
ADCCR2:
         CALL    DOLITEXIT
         .dw ADC_CR2

;       ADC_CR3    ( -- a )
; ADC configuration register 3 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "ADC_CR3"
ADCCR3:
         CALL    DOLITEXIT
         .dw ADC_CR3

;       ADC_DRH    ( -- a )
; ADC data register high (0xXX)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "ADC_DRH"
ADCDRH:
         CALL    DOLITEXIT
         .dw ADC_DRH

;       ADC_DRL    ( -- a )
; ADC data register low (0xXX)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "ADC_DRL"
ADCDRL:
         CALL    DOLITEXIT
         .dw ADC_DRL

;       ADC_TDRH    ( -- a )
; ADC Schmitt trigger disable register high (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ADC_TDRH"
ADCTDRH:
         CALL    DOLITEXIT
         .dw ADC_TDRH

;       ADC_TDRL    ( -- a )
; ADC Schmitt trigger disable register low (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ADC_TDRL"
ADCTDRL:
         CALL    DOLITEXIT
         .dw ADC_TDRL

;       ADC_HTRH    ( -- a )
; ADC high threshold register high (0x03)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ADC_HTRH"
ADCHTRH:
         CALL    DOLITEXIT
         .dw ADC_HTRH

;       ADC_HTRL    ( -- a )
; ADC high threshold register low (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ADC_HTRL"
ADCHTRL:
         CALL    DOLITEXIT
         .dw ADC_HTRL

;       ADC_LTRH    ( -- a )
; ADC low threshold register high (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ADC_LTRH"
ADCLTRH:
         CALL    DOLITEXIT
         .dw ADC_LTRH

;       ADC_LTRL    ( -- a )
; ADC low threshold register low (0x00)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ADC_LTRL"
ADCLTRL:
         CALL    DOLITEXIT
         .dw ADC_LTRL

;       ADC_AWSRH    ( -- a )
; ADC analog watchdog status register high (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "ADC_AWSRH"
ADCAWSRH:
         CALL    DOLITEXIT
         .dw ADC_AWSRH

;       ADC_AWSRL    ( -- a )
; ADC analog watchdog status register low (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "ADC_AWSRL"
ADCAWSRL:
         CALL    DOLITEXIT
         .dw ADC_AWSRL

;       ADC_AWCRH    ( -- a )
; ADC analog watchdog control register high (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "ADC_AWCRH"
ADCAWCRH:
         CALL    DOLITEXIT
         .dw ADC_AWCRH

;       ADC_AWCRL    ( -- a )
; ADC analog watchdog control register low (0x00)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "ADC_AWCRL"
ADCAWCRL:
         CALL    DOLITEXIT
         .dw ADC_AWCRL

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
         CALL    DOLITEXIT
         .dw CPU_A

;       CPU_PCE    ( -- a )
; Program counter extended (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "CPU_PCE"
CPUPCE:
         CALL    DOLITEXIT
         .dw CPU_PCE

;       CPU_PCH    ( -- a )
; Program counter high (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "CPU_PCH"
CPUPCH:
         CALL    DOLITEXIT
         .dw CPU_PCH

;       CPU_PCL    ( -- a )
; Program counter low (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "CPU_PCL"
CPUPCL:
         CALL    DOLITEXIT
         .dw CPU_PCL

;       CPU_XH    ( -- a )
; X index register high (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "CPU_XH"
CPUXH:
         CALL    DOLITEXIT
         .dw CPU_XH

;       CPU_XL    ( -- a )
; X index register low (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "CPU_XL"
CPUXL:
         CALL    DOLITEXIT
         .dw CPU_XL

;       CPU_YH    ( -- a )
; Y index register high (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "CPU_YH"
CPUYH:
         CALL    DOLITEXIT
         .dw CPU_YH

;       CPU_YL    ( -- a )
; Y index register low (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "CPU_YL"
CPUYL:
         CALL    DOLITEXIT
         .dw CPU_YL

;       CPU_SPH    ( -- a )
; Stack pointer high (0x03)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "CPU_SPH"
CPUSPH:
         CALL    DOLITEXIT
         .dw CPU_SPH

;       CPU_SPL    ( -- a )
; Stack pointer low (0xFF)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "CPU_SPL"
CPUSPL:
         CALL    DOLITEXIT
         .dw CPU_SPL

;       CPU_CCR    ( -- a )
; Condition code register (0x28)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "CPU_CCR"
CPUCCR:
         CALL    DOLITEXIT
         .dw CPU_CCR

        .endif

; ***** CFG
;       CFG_GCR    ( -- a )
; Global configuration register (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "CFG_GCR"
CFGGCR:
         CALL    DOLITEXIT
         .dw CFG_GCR

; ***** ITC
        .ifne  0

;       ITC_SPR1    ( -- a )
; Interrupt software priority register 1 (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ITC_SPR1"
ITCSPR1:
         CALL    DOLITEXIT
         .dw ITC_SPR1

;       ITC_SPR2    ( -- a )
; Interrupt software priority register 2 (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ITC_SPR2"
ITCSPR2:
         CALL    DOLITEXIT
         .dw ITC_SPR2

;       ITC_SPR3    ( -- a )
; Interrupt software priority register 3 (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ITC_SPR3"
ITCSPR3:
         CALL    DOLITEXIT
         .dw ITC_SPR3

;       ITC_SPR4    ( -- a )
; Interrupt software priority register 4 (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ITC_SPR4"
ITCSPR4:
         CALL    DOLITEXIT
         .dw ITC_SPR4

;       ITC_SPR5    ( -- a )
; Interrupt software priority register 5 (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ITC_SPR5"
ITCSPR5:
         CALL    DOLITEXIT
         .dw ITC_SPR5

;       ITC_SPR6    ( -- a )
; Interrupt software priority register 6 (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ITC_SPR6"
ITCSPR6:
         CALL    DOLITEXIT
         .dw ITC_SPR6

;       ITC_SPR7    ( -- a )
; Interrupt software priority register 7 (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ITC_SPR7"
ITCSPR7:
         CALL    DOLITEXIT
         .dw ITC_SPR7

;       ITC_SPR8    ( -- a )
; Interrupt software priority register 8 (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "ITC_SPR8"
ITCSPR8:
         CALL    DOLITEXIT
         .dw ITC_SPR8

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
         CALL    DOLITEXIT
         .dw SWIM_CSR

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
         CALL    DOLITEXIT
         .dw DM_BK1RE

;       DM_BK1RH    ( -- a )
; DM breakpoint 1 register high byte (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "DM_BK1RH"
DMBK1RH:
         CALL    DOLITEXIT
         .dw DM_BK1RH

;       DM_BK1RL    ( -- a )
; DM breakpoint 1 register low byte (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "DM_BK1RL"
DMBK1RL:
         CALL    DOLITEXIT
         .dw DM_BK1RL

;       DM_BK2RE    ( -- a )
; DM breakpoint 2 register extended byte (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "DM_BK2RE"
DMBK2RE:
         CALL    DOLITEXIT
         .dw DM_BK2RE

;       DM_BK2RH    ( -- a )
; DM breakpoint 2 register high byte (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "DM_BK2RH"
DMBK2RH:
         CALL    DOLITEXIT
         .dw DM_BK2RH

;       DM_BK2RL    ( -- a )
; DM breakpoint 2 register low byte (0xFF)
         .dw     LINK
         LINK =  .
         .db     8
         .ascii  "DM_BK2RL"
DMBK2RL:
         CALL    DOLITEXIT
         .dw DM_BK2RL

;       DM_CR1    ( -- a )
; DM debug module control register 1 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "DM_CR1"
DMCR1:
         CALL    DOLITEXIT
         .dw DM_CR1

;       DM_CR2    ( -- a )
; DM debug module control register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     6
         .ascii  "DM_CR2"
DMCR2:
         CALL    DOLITEXIT
         .dw DM_CR2

;       DM_CSR1    ( -- a )
; DM debug module control/status register 1 (0x10)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "DM_CSR1"
DMCSR1:
         CALL    DOLITEXIT
         .dw DM_CSR1

;       DM_CSR2    ( -- a )
; DM debug module control/status register 2 (0x00)
         .dw     LINK
         LINK =  .
         .db     7
         .ascii  "DM_CSR2"
DMCSR2:
         CALL    DOLITEXIT
         .dw DM_CSR2

;       DM_ENFCTR    ( -- a )
; DM enable function register (0xFF)
         .dw     LINK
         LINK =  .
         .db     9
         .ascii  "DM_ENFCTR"
DMENFCTR:
         CALL    DOLITEXIT
         .dw DM_ENFCTR

        .endif

