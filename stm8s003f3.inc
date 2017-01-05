; STM8S003F3P6 and STM8S103F3P6 register addresses

  PA_ODR	=	0x5000	; Port A data output latch register
	PA_IDR	=	0x5001	; Port A input pin value register
	PA_DDR	=	0x5002	; Port A data direction register
	PA_CR1	=	0x5003	; Port A control register 1
	PA_CR2	=	0x5004	; Port A control register 2
	PB_ODR	=	0x5005	; Port B data output latch register
	PB_IDR	=	0x5006	; Port B input pin value register
	PB_DDR	=	0x5007	; Port B data direction register
	PB_CR1	=	0x5008	; Port B control register
	PB_CR2	=	0x5009	; Port B control register
	PC_ODR	=	0x500A	; Port C data output latch register
	PC_IDR	=	0x500B	; Port C input pin value register
	PC_DDR	=	0x500C	; Port C data direction register
	PC_CR1	=	0x500D	; Port C control register 1
	PC_CR2	=	0x500E	; Port C control register 2
	PD_ODR	=	0x500F	; Port D data output latch register
	PD_IDR	=	0x5010	; Port D input pin value register
	PD_DDR	=	0x5011	; Port D data direction register
	PD_CR1	=	0x5012	; Port D control register 1
	PD_CR2	=	0x5013	; Port D control register 2

        ; *** Non-Volatile Memory Control ***
        FLASH_IAPSR =   0x505F  ; Flash in-application programming status register
        FLASH_PUKR =    0x5062  ; Flash unprotection register
        FLASH_DUKR =    0x5064  ; Data EEPROM unprotection register
       
  EXTI_CR1 = 0x50A0 ; External interrupt control register 1
  EXTI_CR2 = 0x50A1 ; External interrupt control register 2


         ; *** Clock Control ***
        CLK_CKDIVR =    0x50C6  ; Clock divider register

	; *** UART1 ***
        UART1_SR   =	0x5230	; UART status reg
	UART1_DR   =	0x5231	; UART data reg
	UART1_BRR1  =	0x5232	; baud rate control 1
	UART1_BRR2  =	0x5233	; baud rate control 2
	UART1_CR1  =	0x5234	; UART control reg 2
	UART1_CR2  =	0x5235	; UART control reg 2
	UART1_CR3  =	0x5236	; UART control reg 2

        ; *** TIM2 for background task ***
	TIM2_CR1  =	0x5300	; TIM2 control register 1 (0x00)
	TIM2_IER  =	0x5303	; TIM2 interrupt enable register (0x00)
	TIM2_SR1  =	0x5304	; TIM2 status register 1 (0x00)
	TIM2_SR2  =	0x5305	; TIM2 status register 2 (0x00)
	TIM2_EGR  =	0x5306	; TIM2 event generation register (0x00)
	TIM2_CCMR1  =	0x5307	; TIM2 capture/compare mode register 1 (0x00)
	TIM2_CCMR2  =	0x5308	; TIM2 capture/compare mode register 2 (0x00)
	TIM2_CCMR3  =	0x5309	; TIM2 capture/compare mode register 3 (0x00)
	TIM2_CCER1  =	0x530A	; TIM2 capture/compare enable register (1)
	TIM2_CCER2  =	0x530B	; TIM2 capture/compare enable register (2)
	TIM2_CNTRH  =	0x530C	; TIM2 counter high (0x00)
	TIM2_CNTRL  =	0x530D	; TIM2 counter low (0x00)
	TIM2_PSCR  =	0x530E	; TIM2 prescaler register (0x00)
	TIM2_ARRH  =	0x530F	; TIM2 auto-reload register high (0xFF)
	TIM2_ARRL  =	0x5310	; TIM2 auto-reload register low (0xFF)
	TIM2_CCR1H  =	0x5311	; TIM2 capture/compare register 1 high (0x00)
	TIM2_CCR1L  =	0x5312	; TIM2 capture/compare register 1 low (0x00)
	TIM2_CCR2H  =	0x5313	; TIM2 capture/compare register 2 high (0x00)
	TIM2_CCR2L  =	0x5314	; TIM2 capture/compare register 2 low (0x00)
	TIM2_CCR3H  =	0x5315	; TIM2 capture/compare register 3 high (0x00)
	TIM2_CCR3L  =	0x5316	; TIM2 capture/compare register 3 low (0x00)

        ; *** TIM4 (e.g. for RS232 TxD simulation) ***
        TIM4_CR1 =      0x5340  ; 1 (ENABLE)
        TIM4_IER =      0x5343  ; 1 (ENABLE)     
        TIM4_SR =       0x5344  ; 0 (clear)
        TIM4_EGR =      0x5345
        TIM4_CNTR =     0x5346
        TIM4_PSCR =     0x5347  ; 3 (1/8)
        TIM4_ARR =      0x5348  ; 0xCF (Reload 0.104 ms)
         
        ; Global configuation 
	CFG_GCR  =	0x7F60	; Global configuration register (0x00)
         
        ; interrupt priorities
	ITC_SPR1  =	0x7F70	; Interrupt software priority register 1 (0xFF)
	ITC_SPR2  =	0x7F71	; Interrupt software priority register 2 (0xFF)
	ITC_SPR3  =	0x7F72	; Interrupt software priority register 3 (0xFF)
	ITC_SPR4  =	0x7F73	; Interrupt software priority register 4 (0xFF)
	ITC_SPR5  =	0x7F74	; Interrupt software priority register 5 (0xFF)
	ITC_SPR6  =	0x7F75	; Interrupt software priority register 6 (0xFF)
	ITC_SPR7  =	0x7F76	; Interrupt software priority register 7 (0xFF)
	ITC_SPR8  =	0x7F77	; Interrupt software priority register 8 (0xFF)

