; STM8S003F3P6 and STM8S103F3P6 register addresses

; ***** 6.2.1 I/O port hardware register map


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

        PE_ODR       = 0x5014   ; Port E data output latch register     (0x00)
        PE_IDR       = 0x5015   ; Port E input pin value register       (0xXX)
        PE_DDR       = 0x5016   ; Port E data direction register        (0x00)
        PE_CR1       = 0x5017   ; Port E control register 1             (0x00)
        PE_CR2       = 0x5018   ; Port E control register 2             (0x00)

; ***** Port F

        PF_ODR       = 0x5019   ; Port F data output latch register     (0x00)
        PF_IDR       = 0x501A   ; Port F input pin value register       (0xXX)
        PF_DDR       = 0x501B   ; Port F data direction register        (0x00)
        PF_CR1       = 0x501C   ; Port F control register 1             (0x00)
        PF_CR2       = 0x501D   ; Port F control register 2             (0x00)

; ***** 6.2.2 General hardware register map


; ***** Flash

        FLASH_CR1    = 0x505A   ; Flash control register 1              (0x00)
        FLASH_CR2    = 0x505B   ; Flash control register 2              (0x00)
        FLASH_NCR2   = 0x505C   ; Flash complementary control register 2 (0xFF)
        FLASH_FPR    = 0x505D   ; Flash protection register             (0x00)
        FLASH_NFPR   = 0x505E   ; Flash complementary protection register (0xFF)
        FLASH_IAPSR  = 0x505F   ; Flash in-application programming status register (0x00)
        FLASH_PUKR   = 0x5062   ; Flash Program memory unprotection register (0x00)
        FLASH_DUKR   = 0x5064   ; Data EEPROM unprotection register     (0x00)

; ***** ITC

        EXTI_CR1     = 0x50A0   ; External interrupt control register 1 (0x00)
        EXTI_CR2     = 0x50A1   ; External interrupt control register 2 (0x00)

; ***** RST

        RST_SR       = 0x50B3   ; Reset status register                 (0xXX)

; ***** CLK

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
        CLK_HSITRIMR = 0x50CC   ; HSI clock calibration trimming register  (0x00)

; ***** SWIM

        CLK_SWIMCCR  = 0x50CD   ; clock control register                (0bXXXXXXX0)

; ***** WWDG

        WWDG_CR      = 0x50D1   ; WWDG control register                 (0x7F)
        WWDG_WR      = 0x50D2   ; WWDR window register                  (0x7F)

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

; ***** I2C

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

        TIM2_CR1     = 0x5300   ; TIM2 control register 1               (0x00)
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

; ***** TIM4

        TIM4_CR1     = 0x5340   ; TIM4 control register 1               (0x00)
        TIM4_IER     = 0x5343   ; TIM4 interrupt enable register        (0x00)
        TIM4_SR      = 0x5344   ; TIM4 status register                  (0x00)
        TIM4_EGR     = 0x5345   ; TIM4 event generation register        (0x00)
        TIM4_CNTR    = 0x5346   ; TIM4 counter                          (0x00)
        TIM4_PSCR    = 0x5347   ; TIM4 prescaler register               (0x00)
        TIM4_ARR     = 0x5348   ; TIM4 auto-reload register             (0xFF)

; ***** ADC1

        ADC_DBxR     = 0x53E0   ; ADC data buffer registers 0x53E0 to 0x53F3 (0x00)
        ADC_CSR      = 0x5400   ; ADC control/status register           (0x00)
        ADC_CR1      = 0x5401   ; ADC configuration register 1          (0x00)
        ADC_CR2      = 0x5402   ; ADC configuration register 2          (0x00)
        ADC_CR3      = 0x5403   ; ADC configuration register 3          (0x00)
        ADC_DRH      = 0x5404   ; ADC data register high                (0xXX)
        ADC_DRL      = 0x5405   ; ADC data register low                 (0xXX)
        ADC_TDRH     = 0x5406   ; ADC Schmitt trigger disable register high (0x00)
        ADC_TDRL     = 0x5407   ; ADC Schmitt trigger disable register low (0x00)
        ADC_HTRH     = 0x5408   ; ADC high threshold register high      (0x03)
        ADC_HTRL     = 0x5409   ; ADC high threshold register low       (0xFF)
        ADC_LTRH     = 0x540A   ; ADC low threshold register high       (0x00)
        ADC_LTRL     = 0x540B   ; ADC low threshold register low        (0x00)
        ADC_AWSRH    = 0x540C   ; ADC analog watchdog status register high (0x00)
        ADC_AWSRL    = 0x540D   ; ADC analog watchdog status register low (0x00)
        ADC_AWCRH    = 0x540E   ; ADC analog watchdog control register high (0x00)
        ADC_AWCRL    = 0x540F   ; ADC analog watchdog control register low (0x00)

; ***** 6.2.3 CPU/SWIM/debug module/interrupt controller registers


; ***** CPU

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

; ***** CPU

        CFG_GCR      = 0x7F60   ; Global configuration register         (0x00)

; ***** ITC

        ITC_SPR1     = 0x7F70   ; Interrupt software priority register 1 (0xFF)
        ITC_SPR2     = 0x7F71   ; Interrupt software priority register 2 (0xFF)
        ITC_SPR3     = 0x7F72   ; Interrupt software priority register 3 (0xFF)
        ITC_SPR4     = 0x7F73   ; Interrupt software priority register 4 (0xFF)
        ITC_SPR5     = 0x7F74   ; Interrupt software priority register 5 (0xFF)
        ITC_SPR6     = 0x7F75   ; Interrupt software priority register 6 (0xFF)
        ITC_SPR7     = 0x7F76   ; Interrupt software priority register 7 (0xFF)
        ITC_SPR8     = 0x7F77   ; Interrupt software priority register 8 (0xFF)

; ***** SWIM

        SWIM_CSR     = 0x7F80   ; SWIM control status register          (0x00)

; ***** DM

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
