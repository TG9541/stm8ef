; STM8S register addresses

; ***** 6.2.1 I/O port hardware register map

        PORTA        = PA_ODR
        PORTB        = PB_ODR
        PORTC        = PC_ODR
        PORTD        = PD_ODR
        PORTE        = PE_ODR
        PORTF        = PF_ODR
        PORTG        = PG_ODR
        PORTH        = PH_ODR
        PORTI        = PI_ODR
        PORTX        = 0

        ODR          = 0
        IDR          = 1
        DDR          = 2
        CR1          = 3
        CR2          = 4

; ***** Option Bytes in EEPROM

        OPT0         = 0x4800   ; Read-out protection                   (0x00)
        OPT1         = 0x4801   ; User Boot Code (UBC)                  (0x00)
        NOPT1        = 0x4802   ;                                       (0xFF)
        OPT2         = 0x4803   ; Alternate Function Mapping            (0x00)
        NOPT2        = 0x4804   ;                                       (0xFF)
        OPT3         = 0x4805   ; Watchdog option                       (0x00)
        NOPT3        = 0x4806   ;                                       (0xFF)
        OPT4         = 0x4807   ; Clock option                          (0x00)
        NOPT4        = 0x4808   ;                                       (0xFF)
        OPT5         = 0x4809   ; HSE Clock startup                     (0x00)
        NOPT5        = 0x480A   ;                                       (0xFF)
        OPT6         = 0x480B   ; TMU (Reserved)                        (0x00)
        NOPT6        = 0x480C   ;                                       (0xFF)
        OPT7         = 0x480D   ; Alternate Function Mapping            (0x00)
        NOPT7        = 0x480E   ;                                       (0xFF)

;       OPT8         = 0x4810   ; TMU_KEY 1
;       ...
;       OPT16        = 0x4818   ; TMU_KEY 8

        OPTBL        = 0x487E   ; Bootloader                            (0x00)
        NOPTBL       = 0x487F   ;                                       (0xFF)

; ***** Port A

        PA_ODR       = 0x5000   ; Port A data output latch register     (0x00)
        PA_IDR       = 0x5001   ; Port A input pin value register       (0xXX)
        PA_DDR       = 0x5002   ; Port A data direction register        (0x00)
        PA_CR1       = 0x5003   ; Port A control register 1             (0x00)
        PA_CR2       = 0x5004   ; Port A control register 2             (0x00)

; ***** Port B

        PB_ODR       = 0x5005   ; Port B data output latch register     (0x00)
        PB_IDR       = 0x5006   ; Port B input pin value register       (0xXX)
        PB_DDR       = 0x5007   ; Port B data direction register        (0x00)
        PB_CR1       = 0x5008   ; Port B control register 1             (0x00)
        PB_CR2       = 0x5009   ; Port B control register 2             (0x00)

; ***** Port C

        PC_ODR       = 0x500A   ; Port C data output latch register     (0x00)
        PC_IDR       = 0x500B   ; Port C input pin value register       (0xXX)
        PC_DDR       = 0x500C   ; Port C data direction register        (0x00)
        PC_CR1       = 0x500D   ; Port C control register 1             (0x00)
        PC_CR2       = 0x500E   ; Port C control register 2             (0x00)

; ***** Port D

        PD_ODR       = 0x500F   ; Port D data output latch register     (0x00)
        PD_IDR       = 0x5010   ; Port D input pin value register       (0xXX)
        PD_DDR       = 0x5011   ; Port D data direction register        (0x00)
        PD_CR1       = 0x5012   ; Port D control register 1             (0x02)
        PD_CR2       = 0x5013   ; Port D control register 2             (0x00)

; ***** Port E
;.ifne  0
        PE_ODR       = 0x5014   ; Port E data output latch register     (0x00)
        PE_IDR       = 0x5015   ; Port E input pin value register       (0xXX)
        PE_DDR       = 0x5016   ; Port E data direction register        (0x00)
        PE_CR1       = 0x5017   ; Port E control register 1             (0x00)
        PE_CR2       = 0x5018   ; Port E control register 2             (0x00)
;.endif

; ***** Port F
;.ifne  0
        PF_ODR       = 0x5019   ; Port F data output latch register     (0x00)
        PF_IDR       = 0x501A   ; Port F input pin value register       (0xXX)
        PF_DDR       = 0x501B   ; Port F data direction register        (0x00)
        PF_CR1       = 0x501C   ; Port F control register 1             (0x00)
        PF_CR2       = 0x501D   ; Port F control register 2             (0x00)
;.endif

; ***** Port G
;.ifne  0
        PG_ODR       = 0x501E   ; Port G data output latch register     (0x00)
        PG_IDR       = 0x501F   ; Port G input pin value register       (0xXX)
        PG_DDR       = 0x5020   ; Port G data direction register        (0x00)
        PG_CR1       = 0x5021   ; Port G control register 1             (0x00)
        PG_CR2       = 0x5022   ; Port G control register 2             (0x00)
;.endif

; ***** Port H
;.ifne  0
        PH_ODR       = 0x5023   ; Port H data output latch register     (0x00)
        PH_IDR       = 0x5024   ; Port H input pin value register       (0xXX)
        PH_DDR       = 0x5025   ; Port H data direction register        (0x00)
        PH_CR1       = 0x5026   ; Port H control register 1             (0x00)
        PH_CR2       = 0x5027   ; Port H control register 2             (0x00)
;.endif

; ***** Port I
;.ifne  0
        PI_ODR       = 0x5028   ; Port I data output latch register     (0x00)
        PI_IDR       = 0x5029   ; Port I input pin value register       (0xXX)
        PI_DDR       = 0x502A   ; Port I data direction register        (0x00)
        PI_CR1       = 0x502B   ; Port I control register 1             (0x00)
        PI_CR2       = 0x502C   ; Port I control register 2             (0x00)
;.endif

; ***** 6.2.2 General hardware register map

; ***** Flash
;.ifne  0
        FLASH_CR1    = 0x505A   ; Flash control register 1              (0x00)
        FLASH_CR2    = 0x505B   ; Flash control register 2              (0x00)
        FLASH_NCR2   = 0x505C   ; Flash complementary control register 2 (0xFF)
        FLASH_FPR    = 0x505D   ; Flash protection register             (0x00)
        FLASH_NFPR   = 0x505E   ; Flash complementary protection register (0xFF)
        FLASH_IAPSR  = 0x505F   ; Flash in-application programming status register (0x00)
        FLASH_PUKR   = 0x5062   ; Flash Program memory unprotection register (0x00)
        FLASH_DUKR   = 0x5064   ; Data EEPROM unprotection register     (0x00)
;.endif

; ***** ITC

;.ifne  0
        EXTI_CR1     = 0x50A0   ; External interrupt control register 1 (0x00)
        EXTI_CR2     = 0x50A1   ; External interrupt control register 2 (0x00)
;.endif

; ***** RST

        RST_SR       = 0x50B3   ; Reset status register                 (0xXX)

; ***** CLK

;.ifne  0
        CLK_ICKR     = 0x50C0   ; Internal clock control register       (0x01)
        CLK_ECKR     = 0x50C1   ; External clock control register       (0x00)
        CLK_CMSR     = 0x50C3   ; Clock master status register          (0xE1)
        CLK_SWR      = 0x50C4   ; Clock master switch register          (0xE1)
        CLK_SWCR     = 0x50C5   ; Clock switch control register         (0xXX)
        CLK_CKDIVR   = 0x50C6   ; Clock divider register                (0x18)
        CLK_PCKENR1  = 0x50C7   ; Peripheral clock gating register 1    (0xFF)
        CLK_CSSR     = 0x50C8   ; Clock security system register        (0x00)
        CLK_CCOR     = 0x50C9   ; Configurable clock control register   (0x00)
        CLK_PCKENR2  = 0x50CA   ; Peripheral clock gating register 2    (0xFF)
        CLK_CANCCR   = 0x50CB   ; CAN clock control register            (0x00)
        CLK_HSITRIMR = 0x50CC   ; HSI clock calibration trimming register (0x00)
        CLK_SWIMCCR  = 0x50CD   ; SWIM clock control register     (0bXXXXXXX0)
;.endif

; ***** SWIM

;.ifne  0
        CLK_SWIMCCR  = 0x50CD   ; clock control register                (0bXXXXXXX0)
;.endif

; ***** WWDG

;.ifne  0
        WWDG_CR      = 0x50D1   ; WWDG control register                 (0x7F)
        WWDG_WR      = 0x50D2   ; WWDR window register                  (0x7F)
;.endif

; ***** IWDG

        IWDG_KR      = 0x50E0   ; IWDG key register                     (0xXX)
        IWDG_PR      = 0x50E1   ; IWDG prescaler register               (0x00)
        IWDG_RLR     = 0x50E2   ; IWDG reload register                  (0xFF)

; ***** AWU

        AWU_CSR1     = 0x50F0   ; AWU control/status register 1         (0x00)
        AWU_APR      = 0x50F1   ; AWU asynchronous prescaler buffer register (0x3F)
        AWU_TBR      = 0x50F2   ; AWU timebase selection register       (0x00)

; ***** BEEP

        BEEP_CSR     = 0x50F3   ; BEEP control/status register          (0x1F)

; ***** SPI

        SPI_CR1      = 0x5200   ; SPI control register 1                (0x00)
        SPI_CR2      = 0x5201   ; SPI control register 2                (0x00)
        SPI_ICR      = 0x5202   ; SPI interrupt control register        (0x00)
        SPI_SR       = 0x5203   ; SPI status register                   (0x02)
        SPI_DR       = 0x5204   ; SPI data register                     (0x00)
        SPI_CRCPR    = 0x5205   ; SPI CRC polynomial register           (0x07)
        SPI_RXCRCR   = 0x5206   ; SPI Rx CRC register                   (0x00)
        SPI_TXCRCR   = 0x5207   ; SPI Tx CRC register                   (0x00)

; ***** I2C

        I2C_CR1      = 0x5210   ; I2C control register 1                (0x00)
        I2C_CR2      = 0x5211   ; I2C control register 2                (0x00)
        I2C_FREQR    = 0x5212   ; I2C frequency register                (0x00)
        I2C_OARL     = 0x5213   ; I2C own address register low          (0x00)
        I2C_OARH     = 0x5214   ; I2C own address register high         (0x00)
        I2C_DR       = 0x5216   ; I2C data register                     (0x00)
        I2C_SR1      = 0x5217   ; I2C status register 1                 (0x00)
        I2C_SR2      = 0x5218   ; I2C status register 2                 (0x00)
        I2C_SR3      = 0x5219   ; I2C status register 3                 (0x00)
        I2C_ITR      = 0x521A   ; I2C interrupt control register        (0x00)
        I2C_CCRL     = 0x521B   ; I2C clock control register low        (0x00)
        I2C_CCRH     = 0x521C   ; I2C clock control register high       (0x00)
        I2C_TRISER   = 0x521D   ; I2C TRISE register                    (0x02)
        I2C_PECR     = 0x521E   ; I2C packet error checking register    (0x00)

; ***** UART1
;.ifeq HAS_TXUART+HAS_RXUART

        UART1_SR     = 0x5230   ; UART1 status register                 (0xC0)
        UART1_DR     = 0x5231   ; UART1 data register                   (0xXX)
        UART1_BRR1   = 0x5232   ; UART1 baud rate register 1            (0x00)
        UART1_BRR2   = 0x5233   ; UART1 baud rate register 2            (0x00)
        UART1_CR1    = 0x5234   ; UART1 control register 1              (0x00)
        UART1_CR2    = 0x5235   ; UART1 control register 2              (0x00)
        UART1_CR3    = 0x5236   ; UART1 control register 3              (0x00)
        UART1_CR4    = 0x5237   ; UART1 control register 4              (0x00)
        UART1_CR5    = 0x5238   ; UART1 control register 5              (0x00)
        UART1_GTR    = 0x5239   ; UART1 guard time register             (0x00)
        UART1_PSCR   = 0x523A   ; UART1 prescaler register              (0x00)

        UART2_SR     = 0x5240   ; UART2 status register                 (0xC0)
        UART2_DR     = 0x5241   ; UART2 data register                   (0xXX)
        UART2_BRR1   = 0x5242   ; UART2 baud rate register 1            (0x00)
        UART2_BRR2   = 0x5243   ; UART2 baud rate register 2            (0x00)
        UART2_CR1    = 0x5244   ; UART2 control register 1              (0x00)
        UART2_CR2    = 0x5245   ; UART2 control register 2              (0x00)
        UART2_CR3    = 0x5246   ; UART2 control register 3              (0x00)
        UART2_CR4    = 0x5247   ; UART2 control register 4              (0x00)
        UART2_CR5    = 0x5248   ; UART2 control register 5              (0x00)
        UART2_CR6    = 0x5249   ; UART2 control register 6              (0x00)
        UART2_GTR    = 0x524A   ; UART2 guard time register             (0x00)
        UART2_PSCR   = 0x524B   ; UART2 prescaler register              (0x00)

        UART3_SR     = 0x5240   ; UART3 status register                 (0xC0)
        UART3_DR     = 0x5241   ; UART3 data register                   (0xXX)
        UART3_BRR1   = 0x5242   ; UART3 baud rate register 1            (0x00)
        UART3_BRR2   = 0x5243   ; UART3 baud rate register 2            (0x00)
        UART3_CR1    = 0x5244   ; UART3 control register 1              (0x00)
        UART3_CR2    = 0x5245   ; UART3 control register 2              (0x00)
        UART3_CR3    = 0x5246   ; UART3 control register 3              (0x00)
        UART3_CR4    = 0x5247   ; UART3 control register 4              (0x00)
        ;              0x5248
        UART3_CR6    = 0x5249   ; UART3 control register 6              (0x00)

        .ifeq   (TARGET - STM8S105K4)
        UART_DR   = UART2_DR
        UART_SR   = UART2_SR
        UART_BRR1 = UART2_BRR1
        UART_CR2  = UART2_CR2
        .else
        UART_DR   = UART1_DR    ; STM8S103 and STM8S207
        UART_SR   = UART1_SR
        UART_BRR1 = UART1_BRR1
        UART_CR2  = UART1_CR2
        .endif
;.endif

; ***** TIM1

        TIM1_CR1     = 0x5250   ; TIM1 control register 1               (0x00)
        TIM1_CR2     = 0x5251   ; TIM1 control register 2               (0x00)
        TIM1_SMCR    = 0x5252   ; TIM1 slave mode control register      (0x00)
        TIM1_ETR     = 0x5253   ; TIM1 external trigger register        (0x00)
        TIM1_IER     = 0x5254   ; TIM1 Interrupt enable register        (0x00)
        TIM1_SR1     = 0x5255   ; TIM1 status register 1                (0x00)
        TIM1_SR2     = 0x5256   ; TIM1 status register 2                (0x00)
        TIM1_EGR     = 0x5257   ; TIM1 event generation register        (0x00)
        TIM1_CCMR1   = 0x5258   ; TIM1 capture/compare mode register 1  (0x00)
        TIM1_CCMR2   = 0x5259   ; TIM1 capture/compare mode register 2  (0x00)
        TIM1_CCMR3   = 0x525A   ; TIM1 capture/compare mode register 3  (0x00)
        TIM1_CCMR4   = 0x525B   ; TIM1 capture/compare mode register 4  (0x00)
        TIM1_CCER1   = 0x525C   ; TIM1 capture/compare enable register 1 (0x00)
        TIM1_CCER2   = 0x525D   ; TIM1 capture/compare enable register 2 (0x00)
        TIM1_CNTRH   = 0x525E   ; TIM1 counter high                     (0x00)
        TIM1_CNTRL   = 0x525F   ; TIM1 counter low                      (0x00)
        TIM1_PSCRH   = 0x5260   ; TIM1 prescaler register high          (0x00)
        TIM1_PSCRL   = 0x5261   ; TIM1 prescaler register low           (0x00)
        TIM1_ARRH    = 0x5262   ; TIM1 auto-reload register high        (0xFF)
        TIM1_ARRL    = 0x5263   ; TIM1 auto-reload register low         (0xFF)
        TIM1_RCR     = 0x5264   ; TIM1 repetition counter register      (0x00)
        TIM1_CCR1H   = 0x5265   ; TIM1 capture/compare register 1 high  (0x00)
        TIM1_CCR1L   = 0x5266   ; TIM1 capture/compare register 1 low   (0x00)
        TIM1_CCR2H   = 0x5267   ; TIM1 capture/compare register 2 high  (0x00)
        TIM1_CCR2L   = 0x5268   ; TIM1 capture/compare register 2 low   (0x00)
        TIM1_CCR3H   = 0x5269   ; TIM1 capture/compare register 3 high  (0x00)
        TIM1_CCR3L   = 0x526A   ; TIM1 capture/compare register 3 low   (0x00)
        TIM1_CCR4H   = 0x526B   ; TIM1 capture/compare register 4 high  (0x00)
        TIM1_CCR4L   = 0x526C   ; TIM1 capture/compare register 4 low   (0x00)
        TIM1_BKR     = 0x526D   ; TIM1 break register                   (0x00)
        TIM1_DTR     = 0x526E   ; TIM1 dead-time register               (0x00)
        TIM1_OISR    = 0x526F   ; TIM1 output idle state register       (0x00)

; ***** TIM2
;.ifeq HAS_BACKGROUND

        TIM2_CR1     = 0x5300   ; TIM2 control register 1               (0x00)
        .ifne   (TARGET - STM8S103F3)
        TIM2_IER     = 0x5301   ; TIM2 interrupt enable register        (0x00)
        TIM2_SR1     = 0x5302   ; TIM2 status register 1                (0x00)
        TIM2_SR2     = 0x5303   ; TIM2 status register 2                (0x00)
        TIM2_EGR     = 0x5304   ; TIM2 event generation register        (0x00)
        TIM2_CCMR1   = 0x5305   ; TIM2 capture/compare mode register 1  (0x00)
        TIM2_CCMR2   = 0x5306   ; TIM2 capture/compare mode register 2  (0x00)
        TIM2_CCMR3   = 0x5307   ; TIM2 capture/compare mode register 3  (0x00)
        TIM2_CCER1   = 0x5308   ; TIM2 capture/compare enable register 1 (0x00)
        TIM2_CCER2   = 0x5309   ; TIM2 capture/compare enable register 2 (0x00)
        TIM2_CNTRH   = 0x530A   ; TIM2 counter high                     (0x00)
        TIM2_CNTRL   = 0x530B   ; TIM2 counter low                      (0x00)
        TIM2_PSCR    = 0x530C   ; TIM2 prescaler register               (0x00)
        TIM2_ARRH    = 0x530D   ; TIM2 auto-reload register high        (0xFF)
        TIM2_ARRL    = 0x530E   ; TIM2 auto-reload register low         (0xFF)
        TIM2_CCR1H   = 0x530F   ; TIM2 capture/compare register 1 high  (0x00)
        TIM2_CCR1L   = 0x5310   ; TIM2 capture/compare register 1 low   (0x00)
        TIM2_CCR2H   = 0x5311   ; TIM2 capture/compare reg. 2 high      (0x00)
        TIM2_CCR2L   = 0x5312   ; TIM2 capture/compare register 2 low   (0x00)
        TIM2_CCR3H   = 0x5313   ; TIM2 capture/compare register 3 high  (0x00)
        TIM2_CCR3L   = 0x5314   ; TIM2 capture/compare register 3 low   (0x00)
        .else
        TIM2_IER     = 0x5303   ; TIM2 interrupt enable register        (0x00)
        TIM2_SR1     = 0x5304   ; TIM2 status register 1                (0x00)
        TIM2_SR2     = 0x5305   ; TIM2 status register 2                (0x00)
        TIM2_EGR     = 0x5306   ; TIM2 event generation register        (0x00)
        TIM2_CCMR1   = 0x5307   ; TIM2 capture/compare mode register 1  (0x00)
        TIM2_CCMR2   = 0x5308   ; TIM2 capture/compare mode register 2  (0x00)
        TIM2_CCMR3   = 0x5309   ; TIM2 capture/compare mode register 3  (0x00)
        TIM2_CCER1   = 0x530A   ; TIM2 capture/compare enable register 1 (0x00)
        TIM2_CCER2   = 0x530B   ; TIM2 capture/compare enable register 2 (0x00)
        TIM2_CNTRH   = 0x530C   ; TIM2 counter high                     (0x00)
        TIM2_CNTRL   = 0x530D   ; TIM2 counter low                      (0x00)
        TIM2_PSCR    = 0x530E   ; TIM2 prescaler register               (0x00)
        TIM2_ARRH    = 0x530F   ; TIM2 auto-reload register high        (0xFF)
        TIM2_ARRL    = 0x5310   ; TIM2 auto-reload register low         (0xFF)
        TIM2_CCR1H   = 0x5311   ; TIM2 capture/compare register 1 high  (0x00)
        TIM2_CCR1L   = 0x5312   ; TIM2 capture/compare register 1 low   (0x00)
        TIM2_CCR2H   = 0x5313   ; TIM2 capture/compare reg. 2 high      (0x00)
        TIM2_CCR2L   = 0x5314   ; TIM2 capture/compare register 2 low   (0x00)
        TIM2_CCR3H   = 0x5315   ; TIM2 capture/compare register 3 high  (0x00)
        TIM2_CCR3L   = 0x5316   ; TIM2 capture/compare register 3 low   (0x00)
        .endif
;.endif

; ***** TIM3 (High Density)

        TIM3_CR1     = 0x5320   ; TIM3 control register 1               (0x00)
        TIM3_IER     = 0x5321   ; TIM3 interrupt enable register        (0x00)
        TIM3_SR1     = 0x5322   ; TIM3 status register 1                (0x00)
        TIM3_SR2     = 0x5323   ; TIM3 status register 2                (0x00)
        TIM3_EGR     = 0x5324   ; TIM3 event generation register        (0x00)
        TIM3_CCMR1   = 0x5325   ; TIM3 capture/compare mode register 1  (0x00)
        TIM3_CCMR2   = 0x5326   ; TIM3 capture/compare mode register 2  (0x00)
        TIM3_CCER1   = 0x5327   ; TIM3 capture/compare enable register 1 (0x00)
        TIM3_CNTRH   = 0x5328   ; TIM3 counter high                     (0x00)
        TIM3_CNTRL   = 0x5329   ; TIM3 counter low                      (0x00)
        TIM3_PSCR    = 0x532A   ; TIM3 prescaler register               (0x00)
        TIM3_ARRH    = 0x532B   ; TIM3 auto-reload register high        (0xFF)
        TIM3_ARRL    = 0x532C   ; TIM3 auto-reload register low         (0xFF)
        TIM3_CCR1H   = 0x532D   ; TIM3 capture/compare register 1 high  (0x00)
        TIM3_CCR1L   = 0x532E   ; TIM3 capture/compare register 1 low   (0x00)
        TIM3_CCR2H   = 0x532F   ; TIM3 capture/compare reg. 2 high      (0x00)
        TIM3_CCR2L   = 0x5330   ; TIM3 capture/compare register 2 low   (0x00)

; ***** TIM4

;.ifeq HAS_TXSIM+HAS_RXSIM

        TIM4_CR1     = 0x5340   ; TIM4 control register 1               (0x00)
        .ifeq   (TARGET - STM8S105K4)
        TIM4_IER     = 0x5341   ; TIM4 interrupt enable register        (0x00)
        TIM4_SR      = 0x5342   ; TIM4 status register                  (0x00)
        TIM4_EGR     = 0x5343   ; TIM4 event generation register        (0x00)
        TIM4_CNTR    = 0x5344   ; TIM4 counter                          (0x00)
        TIM4_PSCR    = 0x5345   ; TIM4 prescaler register               (0x00)
        TIM4_ARR     = 0x5346   ; TIM4 auto-reload register             (0xFF)
        .else
        TIM4_IER     = 0x5343   ; TIM4 interrupt enable register        (0x00)
        TIM4_SR      = 0x5344   ; TIM4 status register                  (0x00)
        TIM4_EGR     = 0x5345   ; TIM4 event generation register        (0x00)
        TIM4_CNTR    = 0x5346   ; TIM4 counter                          (0x00)
        TIM4_PSCR    = 0x5347   ; TIM4 prescaler register               (0x00)
        TIM4_ARR     = 0x5348   ; TIM4 auto-reload register             (0xFF)
        .endif
;.endif

; ***** ADC1

;.ifeq HAS_ADC

        ADC_DBxR     = 0x53E0   ; ADC data buffer registers 0x53E0 to 0x53F3 (0x00)
        ; High Density ADC2 start
        ADC_CSR      = 0x5400   ; ADC control/status register           (0x00)
        ADC_CR1      = 0x5401   ; ADC configuration register 1          (0x00)
        ADC_CR2      = 0x5402   ; ADC configuration register 2          (0x00)
        ADC_CR3      = 0x5403   ; ADC configuration register 3          (0x00)
        ADC_DRH      = 0x5404   ; ADC data register high                (0xXX)
        ADC_DRL      = 0x5405   ; ADC data register low                 (0xXX)
        ADC_TDRH     = 0x5406   ; ADC Schmitt trigger disable register high (0x00)
        ADC_TDRL     = 0x5407   ; ADC Schmitt trigger disable register low (0x00)
        ; High Density ADC2 end
        ADC_HTRH     = 0x5408   ; ADC high threshold register high      (0x03)
        ADC_HTRL     = 0x5409   ; ADC high threshold register low       (0xFF)
        ADC_LTRH     = 0x540A   ; ADC low threshold register high       (0x00)
        ADC_LTRL     = 0x540B   ; ADC low threshold register low        (0x00)
        ADC_AWSRH    = 0x540C   ; ADC analog watchdog status register high (0x00)
        ADC_AWSRL    = 0x540D   ; ADC analog watchdog status register low (0x00)
        ADC_AWCRH    = 0x540E   ; ADC analog watchdog control register high (0x00)
        ADC_AWCRL    = 0x540F   ; ADC analog watchdog control register low (0x00)
;.endif

        CAN_MCR      = 0x5420 ; CAN master control register 0x02
        CAN_MSR      = 0x5421 ; CAN master status register 0x02
        CAN_TSR      = 0x5422 ; CAN transmit status register 0x00
        CAN_TPR      = 0x5423 ; CAN transmit priority register 0x0C
        CAN_RFR      = 0x5424 ; CAN receive FIFO register 0x00
        CAN_IER      = 0x5425 ; CAN interrupt enable register 0x00
        CAN_DGR      = 0x5426 ; CAN diagnosis register 0x0C
        CAN_FPSR     = 0x5427 ; CAN page selection register 0x00

        CAN_P0       = 0x5428 ; CAN paged register 0 0xXX (3)
        CAN_P1       = 0x5429 ; CAN paged register 1 0xXX (3)
        CAN_P2       = 0x542A ; CAN paged register 2 0xXX (3)
        CAN_P3       = 0x542B ; CAN paged register 3 0xXX (3)
        CAN_P4       = 0x542C ; CAN paged register 4 0xXX (3)
        CAN_P5       = 0x542D ; CAN paged register 5 0xXX (3)
        CAN_P6       = 0x542E ; CAN paged register 6 0xXX (3)
        CAN_P7       = 0x542F ; CAN paged register 7 0xXX (3)
        CAN_P8       = 0x5430 ; CAN paged register 8 0xXX (3)
        CAN_P9       = 0x5431 ; CAN paged register 9 0xXX (3)
        CAN_PA       = 0x5432 ; CAN paged register A 0xXX (3)
        CAN_PB       = 0x5433 ; CAN paged register B 0xXX (3)
        CAN_PC       = 0x5434 ; CAN paged register C 0xXX (3)
        CAN_PD       = 0x5435 ; CAN paged register D 0xXX (3)
        CAN_PE       = 0x5436 ; CAN paged register E 0xXX (3)
        CAN_PF       = 0x5437 ; CAN paged register F 0xXX (3)

; ***** 6.2.3 CPU/SWIM/debug module/interrupt controller registers


; ***** CPU

;.ifne  0
        CPU_A        = 0x7F00   ; Accumulator                           (0x00)
        CPU_PCE      = 0x7F01   ; Program counter extended              (0x00)
        CPU_PCH      = 0x7F02   ; Program counter high                  (0x00)
        CPU_PCL      = 0x7F03   ; Program counter low                   (0x00)
        CPU_XH       = 0x7F04   ; X index register high                 (0x00)
        CPU_XL       = 0x7F05   ; X index register low                  (0x00)
        CPU_YH       = 0x7F06   ; Y index register high                 (0x00)
        CPU_YL       = 0x7F07   ; Y index register low                  (0x00)
        CPU_SPH      = 0x7F08   ; Stack pointer high                    (0x03)
        CPU_SPL      = 0x7F09   ; Stack pointer low                     (0xFF)
        CPU_CCR      = 0x7F0A   ; Condition code register               (0x28)
;.endif

; ***** CFG

        CFG_GCR      = 0x7F60   ; Global configuration register         (0x00)

; ***** ITC

;.ifne  HAS_CPNVM
        ITC_SPR1     = 0x7F70   ; Interrupt software priority register 1 (0xFF)
        ITC_SPR2     = 0x7F71   ; Interrupt software priority register 2 (0xFF)
        ITC_SPR3     = 0x7F72   ; Interrupt software priority register 3 (0xFF)
        ITC_SPR4     = 0x7F73   ; Interrupt software priority register 4 (0xFF)
        ITC_SPR5     = 0x7F74   ; Interrupt software priority register 5 (0xFF)
        ITC_SPR6     = 0x7F75   ; Interrupt software priority register 6 (0xFF)
        ITC_SPR7     = 0x7F76   ; Interrupt software priority register 7 (0xFF)
        ITC_SPR8     = 0x7F77   ; Interrupt software priority register 8 (0xFF)
;.endif

; ***** SWIM

;.ifne  0
        SWIM_CSR     = 0x7F80   ; SWIM control status register          (0x00)
;.endif

; ***** DM

;.ifne  0
        DM_BK1RE     = 0x7F90   ; DM breakpoint 1 register extended byte (0xFF)
        DM_BK1RH     = 0x7F91   ; DM breakpoint 1 register high byte    (0xFF)
        DM_BK1RL     = 0x7F92   ; DM breakpoint 1 register low byte     (0xFF)
        DM_BK2RE     = 0x7F93   ; DM breakpoint 2 register extended byte (0xFF)
        DM_BK2RH     = 0x7F94   ; DM breakpoint 2 register high byte    (0xFF)
        DM_BK2RL     = 0x7F95   ; DM breakpoint 2 register low byte     (0xFF)
        DM_CR1       = 0x7F96   ; DM debug module control register 1    (0x00)
        DM_CR2       = 0x7F97   ; DM debug module control register 2    (0x00)
        DM_CSR1      = 0x7F98   ; DM debug module control/status register 1 (0x10)
        DM_CSR2      = 0x7F99   ; DM debug module control/status register 2 (0x00)
        DM_ENFCTR    = 0x7F9A   ; DM enable function register           (0xFF)
;.endif
