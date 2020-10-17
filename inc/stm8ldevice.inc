; STM8L register addresses

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

; Port A
 PA_ODR = 0x5000 ; Port A data output latch register 0x00
 PA_IDR = 0x5001 ; Port A in put pin value register 0xXX
 PA_DDR = 0x5002 ; Port A data direction register 0x00
 PA_CR1 = 0x5003 ; Port A control register 1 0x01
 PA_CR2 = 0x5004 ; Port A control register 2 0x00
; Port B
 PB_ODR = 0x5005 ; Port B data output latch register 0x00
 PB_IDR = 0x5006 ; Port B input pin value register 0xXX
 PB_DDR = 0x5007 ; Port B data direction register 0x00
 PB_CR1 = 0x5008 ; Port B control register 1 0x00
 PB_CR2 = 0x5009 ; Port B control register 2 0x00
; Port C
 PC_ODR = 0x500A ; Port C data output latch register 0x00
 PC_IDR = 0x500B ; Port C input pin value register 0xXX
 PC_DDR = 0x500C ; Port C data direction register 0x00
 PC_CR1 = 0x500D ; Port C control register 1 0x00
 PC_CR2 = 0x500E ; Port C control register 2 0x00
; Port D
 PD_ODR = 0x500F ; Port D data output latch register 0x00
 PD_IDR = 0x5010 ; Port D input pin value register 0xXX
 PD_DDR = 0x5011 ; Port D data direction register 0x00
 PD_CR1 = 0x5012 ; Port D control register 1 0x00
 PD_CR2 = 0x5013 ; Port D control register 2 0x00
; Port E
 PE_ODR = 0x5014 ; Port E data output latch register 0x00
 PE_IDR = 0x5015 ; Port E input pin value register 0xXX
 PE_DDR = 0x5016 ; Port E data direction register 0x00
 PE_CR1 = 0x5017 ; Port E control register 1 0x00
 PE_CR2 = 0x5018 ; Port E control register 2 0x00
; Port F
 PF_ODR = 0x5019 ; Port F data output latch register 0x00
 PF_IDR = 0x501A ; Port F input pin value register 0xXX
 PF_DDR = 0x501B ; Port F data direction register 0x00
 PF_CR1 = 0x501C ; Port F control register 1 0x00
 PF_CR2 = 0x501D ; Port F control register 2 0x00
; Port G
 PG_ODR = 0x501E ; Port G data output latch register 0x00
 PG_IDR = 0x501F ; Port G input pin value register 0xXX
 PG_DDR = 0x5020 ; Port G data direction register 0x00
 PG_CR1 = 0x5021 ; Port G control register 1 0x00
 PG_CR2 = 0x5022 ; Port G control register 2 0x00
; Port H
 PH_ODR = 0x5023 ; Port H data output latch register 0x00
 PH_IDR = 0x5024 ; Port H input pin value register 0xXX
 PH_DDR = 0x5025 ; Port H data direction register 0x00
 PH_CR1 = 0x5026 ; Port H control register 1 0x00
 PH_CR2 = 0x5027 ; Port H control register 2 0x00
; Port I
 PI_ODR = 0x5028 ; Port I data output latch register 0x00
 PI_IDR = 0x5029 ; Port I input pin value register 0xXX
 PI_DDR = 0x502A ; Port I data direction register 0x00
 PI_CR1 = 0x502B ; Port I control register 1 0x00
 PI_CR2 = 0x502C ; Port I control register 2 0x00
; 0x00 5014 to 0x00 501D Reserved area (0 bytes)
; 0x00 502E to 0x00 5049 Reserved area (44 bytes)
; Flash
 FLASH_CR1 = 0x5050 ; Flash control register 1 0x00
 FLASH_CR2 = 0x5051 ; Flash control register 2 0x00
 FLASH_PUKR = 0x5052 ; Flash program memory unprotection key register 0x00
 FLASH_DUKR = 0x5053 ; Data EEPROM unprotection key register 0x00
 FLASH_IAPSR = 0x5054 ; Flash in-application programming status register 0x00
; 0x00 5055 to 0x00 506F Reserved area (27 bytes)
; DMA1
 DMA1_GCSR = 0x5070 ; DMA1 global configuration & status register 0xFC
 DMA1_GIR1 = 0x5071 ; DMA1 global interrupt register 1 0x00
; 0x00 5072 to 0x00 5074 Reserved area (3 bytes)
 DMA1_C0CR = 0x5075 ; DMA1 channel 0 configuration register 0x00
 DMA1_C0SPR = 0x5076 ; DMA1 channel 0 status & priority register 0x00
 DMA1_C0NDTR = 0x5077 ; DMA1 number of data to transfer register (channel 0) 0x00
 DMA1_C0PARH = 0x5078 ; DMA1 peripheral address high register (channel 0) 0x52
 DMA1_C0PARL = 0x5079 ; DMA1 peripheral address low register (channel 0) 0x00
; 0x00 507A Reserved area (1 byte)
 DMA1_C0M0ARH = 0x507B ; DMA1 memory 0 address high register (channel 0) 0x00
 DMA1_C0M0ARL = 0x507C ; DMA1 memory 0 address low register (channel 0) 0x00
; 0x00 507D to 0x00 507E Reserved area (2 bytes)
 DMA1_C1CR = 0x507F ; DMA1 channel 1 configuration register 0x00
 DMA1_C1SPR = 0x5080 ; DMA1 channel 1 status & priority register 0x00
 DMA1_C1NDTR = 0x5081 ; DMA1 number of data to transfer register (channel 1) 0x00
 DMA1_C1PARH = 0x5082 ; DMA1 peripheral address high register (channel 1) 0x52
 DMA1_C1PARL = 0x5083 ; DMA1 peripheral address low register (channel 1) 0x00
; 0x00 5084 Reserved area (1 byte)
 DMA1_C1M0ARH = 0x5085 ; DMA1 memory 0 address high register (channel 1) 0x00
 DMA1_C1M0ARL = 0x5086 ; DMA1 memory 0 address low register (channel 1) 0x00
; 0x00 5087 0x00 5088 Reserved area (2 bytes)
 DMA1_C2CR = 0x5089 ; DMA1 channel 2 configuration register 0x00
 DMA1_C2SPR = 0x508A ; DMA1 channel 2 status & priority register 0x00
 DMA1_C2NDTR = 0x508B ; DMA1 number of data to transfer register (channel 2) 0x00
 DMA1_C2PARH = 0x508C ; DMA1 peripheral address high register (channel 2) 0x52
 DMA1_C2PARL = 0x508D ; DMA1 peripheral address low register (channel 2) 0x00
; 0x00 508E Reserved area (1 byte)
 DMA1_C2M0ARH = 0x508F ; DMA1 memory 0 address high register (channel 2) 0x00
 DMA1_C2M0ARL = 0x5090 ; DMA1 memory 0 address low register (channel 2) 0x00
; 0x00 5091 0x00 5092 Reserved area (2 bytes)
 DMA1_C3CR = 0x5093 ; DMA1 channel 3 configuration register 0x00
 DMA1_C3SPR = 0x5094 ; DMA1 channel 3 status & priority register 0x00
 DMA1_C3NDTR = 0x5095 ; DMA1 number of data to transfer register (channel 3) 0x00
 DMA1_C3PARH_C3M1ARH = 0x5096 ; DMA1 peripheral address high register (channel 3) 0x40
 DMA1_C3PARL_C3M1ARL = 0x5097 ; DMA1 peripheral address low register (channel 3) 0x00
; DMA1
 DMA_C3M0EAR = 0x5098 ; DMA channel 3 memory 0 extended address register 0x00
 DMA1_C3M0ARH = 0x5099 ; DMA1 memory 0 address high register (channel 3) 0x00
 DMA1_C3M0ARL = 0x509A ; DMA1 memory 0 address low register (channel 3) 0x00
; 0x00 509B to 0x00 509C Reserved area (3 bytes)
; SYSCFG
 SYSCFG_RMPCR3 = 0x509D ; Remapping register 3 0x00
 SYSCFG_RMPCR1 = 0x509E ; Remapping register 1 0x00
 SYSCFG_RMPCR2 = 0x509F ; Remapping register 2 0x00
; ITC - EXTI
 EXTI_CR1 = 0x50A0 ; External interrupt control register 1 0x00
 EXTI_CR2 = 0x50A1 ; External interrupt control register 2 0x00
 EXTI_CR3 = 0x50A2 ; External interrupt control register 3 0x00
 EXTI_SR1 = 0x50A3 ; External interrupt status register 1 0x00
 EXTI_SR2 = 0x50A4 ; External interrupt status register 2 0x00
 EXTI_CONF1 = 0x50A5 ; External interrupt port select register 1 0x00
; WFE
 WFE_CR1 = 0x50A6 ; WFE control register 1 0x00
 WFE_CR2 = 0x50A7 ; WFE control register 2 0x00
 WFE_CR3 = 0x50A8 ; WFE control register 3 0x00
 WFE_CR4 = 0x50A9 ; WFE control register 4 0x00
; ITC - EXTI
 EXTI_CR4 = 0x50AA ; External interrupt control register 4 0x00
 EXTI_CONF2 = 0x50AB ; External interrupt port select register 2 0x00
; 0x00 50A9 to 0x00 50AF Reserved area (7 bytes)
; RST
 RST_CR = 0x50B0 ; Reset control register 0x00
 RST_SR = 0x50B1 ; Reset status register 0x01
; PWR
 PWR_CSR1 = 0x50B2 ; Power control and status register 1 0x00
 PWR_CSR2 = 0x50B3 ; Power contro l and status register 2 0x00
; 0x00 50B4 to 0x00 50BF Reserved area (12 bytes)
; CLK
 CLK_CKDIVR = 0x50C0 ; CLK Clock master divider register 0x03
 CLK_CRTCR = 0x50C1 ; CLK Clock RTC register 0x00 (1)
 CLK_ICKCR = 0x50C2 ; CLK Internal clock control register  0x11
 CLK_PCKENR1 = 0x50C3 ; CLK Peripheral clock gating register 1 0x00
; CLK
 CLK_PCKENR2 = 0x50C4 ; CLK Peripheral clock gating register 2 0x00
 CLK_CCOR = 0x50C5 ; CLK Configurable clock control register 0x00
 CLK_ECKCR = 0x50C6 ; CLK External clock control register 0x00
 CLK_SCSR = 0x50C7 ; CLK System clock status register 0x01
 CLK_SWR = 0x50C8 ; CLK System clock switch register  0x01
 CLK_SWCR = 0x50C9 ; CLK Clock switch control register  0xX0
 CLK_CSSR = 0x50CA ; CLK Clock security system register 0x00
 CLK_CBEEPR = 0x50CB ; CLK Clock BEEP register 0x00
 CLK_HSICALR = 0x50CC ; CLK HSI calibration register 0xXX
 CLK_HSITRIMR = 0x50CD ; CLK HSI clock calibration trimming register  0x00
 CLK_HSIUNLCKR = 0x50CE ; CLK HSI unlock register  0x00
 CLK_REGCSR = 0x50CF ; CLK Main regulator control status register 0bxx11100X
 CLK_PCKENR3 = 0x50D0 ; CLK Peripheral clock gating register 3 0x00
; 0x00 50D1 to 0x00 50D2 Reserved area (2 bytes)
; WWDG
 WWDG_CR = 0x50D3 ; WWDG control register 0x7F
 WWDG_WR = 0x50D4 ; WWDR window register 0x7F
; 0x00 50D5 to 00 50DF Reserved area (11 bytes)
; IWDG
 IWDG_KR = 0x50E0 ; IWDG key register 0x01
 IWDG_PR = 0x50E1 ; IWDG prescaler register 0x00
 IWDG_RLR = 0x50E2 ; IWDG reload register 0xFF
; 0x00 50E3 to 0x00 50EF Reserved area (13 bytes)
; BEEP
 BEEP_CSR1 = 0x50F0 ; BEEP control/status register 1 0x00
; 0x00 50F1 0x00 50F2 Reserved area (2 bytes)
 BEEP_CSR2 = 0x50F3 ; BEEP control/status register 2 0x1F
; 0x00 50F4 to 0x00 513F Reserved area (76 bytes)
; RTC
 RTC_TR1 = 0x5140 ; RTC Time register 1 0x00
 RTC_TR2 = 0x5141 ; RTC Time register 2 0x00
 RTC_TR3 = 0x5142 ; RTC Time register 3 0x00
; 0x00 5143 Reserved area (1 byte)
; RTC
 RTC_DR1 = 0x5144 ; RTC Date register 1 0x01
 RTC_DR2 = 0x5145 ; RTC Date register 2 0x21
 RTC_DR3 = 0x5146 ; RTC Date register 3 0x00
; 0x00 5147 Reserved area (1 byte)
 RTC_CR1 = 0x5148 ; RTC Control register 1 0x00 (1)
 RTC_CR2 = 0x5149 ; RTC Control register 2 0x00 (1)
 RTC_CR3 = 0x514A ; RTC Control register 3 0x00 (1)
; 0x00 514B Reserved area (1 byte)
 RTC_ISR1 = 0x514C ; RTC Initialization and status register 1 0x01
 RTC_ISR2 = 0x514D ; RTC Initialization and Status register 2 0x00
; 0x00 514E 0x00 514F Reserved area (2 bytes)
 RTC_SPRERH = 0x5150 ; RTC Synchronous prescaler register high 0x00 (1)
 RTC_SPRERL = 0x5151 ; RTC Synchronous prescaler register low 0xFF (1)
 RTC_APRER = 0x5152 ; RTC Asynchronous prescaler register 0x7F (1)
; 0x00 5153 Reserved area (1 byte)
 RTC_WUTRH = 0x5154 ; RTC Wakeup timer register high 0xFF (1)
 RTC_WUTRL = 0x5155 ; RTC Wakeup timer register low 0xFF (1)
; 0x00 5156 Reserved area (1 byte)
 RTC_SSRL = 0x5157 ; RTC Subsecond register low 0x00
 RTC_SSRH = 0x5158 ; RTC Subsecond register high 0x00
 RTC_WPR = 0x5159 ; RTC Write protection register 0x00
 RTC_SSRH = 0x5158 ; RTC Subsecond register high 0x00
 RTC_WPR = 0x5159 ; RTC Write protection register 0x00
 RTC_SHIFTRH = 0x515A ; RTC Shift register high 0x00
 RTC_SHIFTRL = 0x515B ; RTC Shift register low 0x00
 RTC_ALRMAR1 = 0x515C ; RTC Alarm A register 1 0x00 (1)
 RTC_ALRMAR2 = 0x515D ; RTC Alarm A register 2 0x00 (1)
 RTC_ALRMAR3 = 0x515E ; RTC Alarm A register 3 0x00 (1)
 RTC_ALRMAR4 = 0x515F ; RTC Alarm A register 4 0x00 (1)
; 0x00 5160 to 0x00 5163 Reserved area (4 bytes)
 RTC_ALRMASSRH = 0x5164 ; RTC Alarm A subsecond register high  0x00 (1)
 RTC_ALRMASSRL = 0x5165 ; RTC Alarm A subsecond register low 0x00 (1)
; RTC
 RTC_ALRMASSMSKR = 0x5166 ; RTC Alarm A masking register  0x00 (1)
; 0x00 5167 to 0x00 5169 Reserved area (3 bytes)
 RTC_CALRH = 0x516A ; RTC Calibration register high 0x00 (1)
 RTC_CALRL = 0x516B ; RTC Calibration register low 0x00 (1)
 RTC_TCR1 = 0x516C ; RTC Tamper control register 1 0x00 (1)
 RTC_TCR2 = 0x516D ; RTC Tamper control register 2 0x00 (1)
; 0x00 516E to 0x00 518A Reserved area (36 bytes)
 CSSLSE_CSR = 0x5190 ; CSS on LSE control and status register 0x00 (1)
; 0x00 519A to 0x00 51FF Reserved area (111 bytes)
; SPI1
 SPI1_CR1 = 0x5200 ; SPI1 control register 1 0x00
 SPI1_CR2 = 0x5201 ; SPI1 control register 2 0x00
 SPI1_ICR = 0x5202 ; SPI1 interrupt control register 0x00
 SPI1_SR = 0x5203 ; SPI1 status register 0x02
 SPI1_DR = 0x5204 ; SPI1 data register 0x00
 SPI1_CRCPR = 0x5205 ; SPI1 CRC polynomial register 0x07
 SPI1_RXCRCR = 0x5206 ; SPI1 Rx CRC register 0x00
 SPI1_TXCRCR = 0x5207 ; SPI1 Tx CRC register 0x00
; 0x00 5208 to 0x00 520F Reserved area (8 bytes)
; I2C1
 I2C1_CR1 = 0x5210 ; I2C1 control register 1 0x00
 I2C1_CR2 = 0x5211 ; I2C1 control register 2 0x00
 I2C1_FREQR = 0x5212 ; I2C1 frequency register  0x00
 I2C1_OARL = 0x5213 ; I2C1 own address register low 0x00
 I2C1_OARH = 0x5214 ; I2C1 own address register high 0x00
 I2C1_OAR2 = 0x5215 ; I2C1 own address register for dual mode 0x00
 I2C1_DR = 0x5216 ; I2C1 data register 0x00
 I2C1_SR1 = 0x5217 ; I2C1 status register 1 0x00
 I2C1_SR2 = 0x5218 ; I2C1 status register 2 0x00
 I2C1_SR3 = 0x5219 ; I2C1 status register 3 0x0X
 I2C1_ITR = 0x521A ; I2C1 interrupt control register 0x00
 I2C1_CCRL = 0x521B ; I2C1 clock control register low 0x00
 I2C1_CCRH = 0x521C ; I2C1 clock control register high 0x00
; I2C1
 I2C1_TRISER = 0x521D ; I2C1 TRISE register 0x02
 I2C1_PECR = 0x521E ; I2C1 packet error checking register 0x00
; 0x00 521F to 0x00 522F Reserved area (17 bytes)
; USART1
 USART1_SR = 0x5230 ; USART1 status register 0xC0
 USART1_DR = 0x5231 ; USART1 data register 0xXX
 USART1_BRR1 = 0x5232 ; USART1 baud rate register 1 0x00
 USART1_BRR2 = 0x5233 ; USART1 baud rate register 2 0x00
 USART1_CR1 = 0x5234 ; USART1 control register 1 0x00
 USART1_CR2 = 0x5235 ; USART1 control register 2 0x00
 USART1_CR3 = 0x5236 ; USART1 control register 3 0x00
 USART1_CR4 = 0x5237 ; USART1 control register 4 0x00
 USART1_CR5 = 0x5238 ; USART1 control register 5 0x00
 USART1_GTR = 0x5239 ; USART1 guard time register  0x00
 USART1_PSCR = 0x523A ; USART1 prescaler register  0x00

        ; 0x00 523B to 0x00 524F Reserved area (21 bytes)
; TIM2
 TIM2_CR1 = 0x5250 ; TIM2 control register 1 0x00
 TIM2_CR2 = 0x5251 ; TIM2 control register 2 0x00
 TIM2_SMCR = 0x5252 ; TIM2 Slave mode control register  0x00
 TIM2_ETR = 0x5253 ; TIM2 external trigger register 0x00
        .ifeq   (TARGET - STM8L_101)
        ; STM8L101 family devices have an offset shift here
 TIM2_IER = 0x5254 ; TIM2 interrupt enable register  0x00
 TIM2_SR1 = 0x5255 ; TIM2 status register 1 0x00
 TIM2_SR2 = 0x5256 ; TIM2 status register 2 0x00
 TIM2_EGR = 0x5257 ; TIM2 event generation register  0x00
 TIM2_CCMR1 = 0x5258 ; TIM2 capture/compare mode register 1 0x00
 TIM2_CCMR2 = 0x5259 ; TIM2 capture/compare mode register 2 0x00
 TIM2_CCER1 = 0x525A ; TIM2 capture/compare enable register 1 0x00
 TIM2_CNTRH = 0x525B ; TIM2 counter high 0x00
 TIM2_CNTRL = 0x525C ; TIM2 counter low 0x00
 TIM2_PSCR = 0x525D ; TIM2 prescaler register 0x00
 TIM2_ARRH = 0x525E ; TIM2 auto-reload register high 0xFF
 TIM2_ARRL = 0x525F ; TIM2 auto-reload register low 0xFF
 TIM2_CCR1H = 0x5260 ; TIM2 capture/compare register 1 high 0x00
 TIM2_CCR1L = 0x5261 ; TIM2 capture/compare register 1 low 0x00
 TIM2_CCR2H = 0x5262 ; TIM2 capture/compare register 2 high 0x00
 TIM2_CCR2L = 0x5263 ; TIM2 capture/compare register 2 low 0x00
 TIM2_BKR = 0x5264 ; TIM2 break register 0x00
 TIM2_OISR = 0x5265 ; TIM2 output idle state register 0x00
        .else
 TIM2_DER = 0x5254 ; TIM2 DMA1 request enable register 0x00
 TIM2_IER = 0x5255 ; TIM2 interrupt enable register  0x00
 TIM2_SR1 = 0x5256 ; TIM2 status register 1 0x00
 TIM2_SR2 = 0x5257 ; TIM2 status register 2 0x00
 TIM2_EGR = 0x5258 ; TIM2 event generation register  0x00
 TIM2_CCMR1 = 0x5259 ; TIM2 capture/compare mode register 1 0x00
 TIM2_CCMR2 = 0x525A ; TIM2 capture/compare mode register 2 0x00
 TIM2_CCER1 = 0x525B ; TIM2 capture/compare enable register 1 0x00
 TIM2_CNTRH = 0x525C ; TIM2 counter high 0x00
 TIM2_CNTRL = 0x525D ; TIM2 counter low 0x00
 TIM2_PSCR = 0x525E ; TIM2 prescaler register 0x00
 TIM2_ARRH = 0x525F ; TIM2 auto-reload register high 0xFF
 TIM2_ARRL = 0x5260 ; TIM2 auto-reload register low 0xFF
 TIM2_CCR1H = 0x5261 ; TIM2 capture/compare register 1 high 0x00
 TIM2_CCR1L = 0x5262 ; TIM2 capture/compare register 1 low 0x00
 TIM2_CCR2H = 0x5263 ; TIM2 capture/compare register 2 high 0x00
 TIM2_CCR2L = 0x5264 ; TIM2 capture/compare register 2 low 0x00
 TIM2_BKR = 0x5265 ; TIM2 break register 0x00
 TIM2_OISR = 0x5266 ; TIM2 output idle state register 0x00
        .endif

; 0x00 5267 to 0x00 527F Reserved area (25 bytes)

; TIM3
 TIM3_CR1 = 0x5280 ; TIM3 control register 1 0x00
 TIM3_CR2 = 0x5281 ; TIM3 control register 2 0x00
 TIM3_SMCR = 0x5282 ; TIM3 Slave mode control register  0x00
 TIM3_ETR = 0x5283 ; TIM3 external trigger register 0x00
        .ifeq   (TARGET - STM8L_101)
        ; STM8L101 family devices have an offset shift here
 TIM3_IER = 0x5284 ; TIM3 interrupt enable register  0x00
 TIM3_SR1 = 0x5285 ; TIM3 status register 1 0x00
 TIM3_SR2 = 0x5286 ; TIM3 status register 2 0x00
 TIM3_EGR = 0x5287 ; TIM3 event generation register  0x00
 TIM3_CCMR1 = 0x5288 ; TIM3 Capture/Compare mode register 1 0x00
 TIM3_CCMR2 = 0x5289 ; TIM3 Capture/Compare mode register 2 0x00
 TIM3_CCER1 = 0x528A ; TIM3 Capture/Compare enable register 1 0x00
 TIM3_CNTRH = 0x528B ; TIM3 counter high 0x00
 TIM3_CNTRL = 0x528C ; TIM3 counter low 0x00
 TIM3_PSCR = 0x528D ; TIM3 prescaler register 0x00
 TIM3_ARRH = 0x528E ; TIM3 Auto-reload register high 0xFF
 TIM3_ARRL = 0x528F ; TIM3 Auto-reload register low 0xFF
 TIM3_CCR1H = 0x5290 ; TIM3 Capture/Compare register 1 high 0x00
 TIM3_CCR1L = 0x5291 ; TIM3 Capture/Compare register 1 low 0x00
 TIM3_CCR2H = 0x5292 ; TIM3 Capture/Compare register 2 high 0x00
 TIM3_CCR2L = 0x5293 ; TIM3 Capture/Compare register 2 low 0x00
 TIM3_BKR = 0x5294 ; TIM3 break register 0x00
 TIM3_OISR = 0x5295 ; TIM3 output idle state register 0x00
        .else
 TIM3_DER = 0x5284 ; TIM3 DMA1 request enable register 0x00
 TIM3_IER = 0x5285 ; TIM3 interrupt enable register  0x00
 TIM3_SR1 = 0x5286 ; TIM3 status register 1 0x00
 TIM3_SR2 = 0x5287 ; TIM3 status register 2 0x00
 TIM3_EGR = 0x5288 ; TIM3 event generation register  0x00
 TIM3_CCMR1 = 0x5289 ; TIM3 Capture/Compare mode register 1 0x00
 TIM3_CCMR2 = 0x528A ; TIM3 Capture/Compare mode register 2 0x00
 TIM3_CCER1 = 0x528B ; TIM3 Capture/Compare enable register 1 0x00
 TIM3_CNTRH = 0x528C ; TIM3 counter high 0x00
 TIM3_CNTRL = 0x528D ; TIM3 counter low 0x00
 TIM3_PSCR = 0x528E ; TIM3 prescaler register 0x00
 TIM3_ARRH = 0x528F ; TIM3 Auto-reload register high 0xFF
 TIM3_ARRL = 0x5290 ; TIM3 Auto-reload register low 0xFF
 TIM3_CCR1H = 0x5291 ; TIM3 Capture/Compare register 1 high 0x00
 TIM3_CCR1L = 0x5292 ; TIM3 Capture/Compare register 1 low 0x00
 TIM3_CCR2H = 0x5293 ; TIM3 Capture/Compare register 2 high 0x00
 TIM3_CCR2L = 0x5294 ; TIM3 Capture/Compare register 2 low 0x00
 TIM3_BKR = 0x5295 ; TIM3 break register 0x00
 TIM3_OISR = 0x5296 ; TIM3 output idle state register 0x00
        .endif

        TIM1_CR1 = 0x52B0
        TIM1_IER = 0x52B5
        TIM1_SR1 = 0x52B6
        TIM1_PSCRL = 0x52C2
        TIM1_ARRH = 0x52C3
        TIM1_ARRL = 0x52C4

        .ifne   BG_USE_TIM1
        .ifne   (BG_USE_TIM3 + STM8L_LOD + STM8L_101)
        Error: either BG_USE_TIM1 or BG_USE_TIM3 can be selected but not both
        Error: STM8L Low density device doesn't have TIM1
        .else
        BG_TIM_CR1   = TIM1_CR1
        BG_TIM_IER   = TIM1_IER
        BG_TIM_SR1   = TIM1_SR1
        BG_TIM_ARRH  = TIM1_ARRH
        BG_TIM_ARRL  = TIM1_ARRL
        .endif
        .else
        .ifne   BG_USE_TIM3
        BG_TIM_CR1   = TIM3_CR1
        BG_TIM_IER   = TIM3_IER
        BG_TIM_SR1   = TIM3_SR1
        BG_TIM_ARRH  = TIM3_ARRH
        BG_TIM_ARRL  = TIM3_ARRL
        BG_TIM_PSCR  = TIM3_PSCR
        .else
        BG_TIM_CR1   = TIM2_CR1
        BG_TIM_IER   = TIM2_IER
        BG_TIM_SR1   = TIM2_SR1
        BG_TIM_ARRH  = TIM2_ARRH
        BG_TIM_ARRL  = TIM2_ARRL
        BG_TIM_PSCR  = TIM2_PSCR
        .endif
        .endif

; 0x00 5297 to 0x00 52DF Reserved area (72 bytes)

; TIM4
 TIM4_CR1 = 0x52E0 ; TIM4 control register 1 0x00
 TIM4_CR2 = 0x52E1 ; TIM4 control register 2 0x00
 TIM4_SMCR = 0x52E2 ; TIM4 Slave mode control register  0x00
        .ifeq   (TARGET - STM8L_101)
        ; STM8L101 family devices have an offset shift here
 TIM4_IER = 0x52E3 ; TIM4 Interrupt enable register  0x00
 TIM4_SR  = 0x52E4 ; TIM4 status register 1 0x00
 TIM4_SR1 = TIM4_SR ; alias
 TIM4_EGR = 0x52E5 ; TIM4 Event generation register  0x00
 TIM4_CNTR = 0x52E6 ; TIM4 counter 0x00
 TIM4_PSCR = 0x52E7 ; TIM4 prescaler register  0x00
 TIM4_ARR = 0x52E8 ; TIM4 Auto-reload register 0x00
        .else
  TIM4_DER = 0x52E3 ; TIM4 DMA1 request enable register 0x00
 TIM4_IER = 0x52E4 ; TIM4 Interrupt enable register  0x00
 TIM4_SR  = 0x52E5 ; TIM4 status register 1 0x00
 TIM4_SR1 = TIM4_SR ; STM8L051F3 data sheet error
 TIM4_EGR = 0x52E6 ; TIM4 Event generation register  0x00
 TIM4_CNTR = 0x52E7 ; TIM4 counter 0x00
 TIM4_PSCR = 0x52E8 ; TIM4 prescaler register  0x00
 TIM4_ARR = 0x52E9 ; TIM4 Auto-reload register 0x00
        .endif


; 0x00 52EA to 0x00 52FE Reserved area (21 bytes)
; IRTIM
 IR_CR = 0x52FF ; Infrared control register 0x00
; 0x00 5317 to 0x00 533F Reserved area (41 bytes)
; ADC1
 ADC1_CR1 = 0x5340 ; ADC1 configuration register 1 0x00
 ADC1_CR2 = 0x5341 ; ADC1 configuration register 2 0x00
 ADC1_CR3 = 0x5342 ; ADC1 configuration register 3 0x1F
 ADC1_SR = 0x5343 ; ADC1 status register 0x00
 ADC1_DRH = 0x5344 ; ADC1 data register high 0x00
 ADC1_DRL = 0x5345 ; ADC1 data register low 0x00
 ADC1_HTRH = 0x5346 ; ADC1 high threshold register high 0x0F
 ADC1_HTRL = 0x5347 ; ADC1 high threshold register low 0xFF
 ADC1_LTRH = 0x5348 ; ADC1 low threshold register high 0x00
 ADC1_LTRL = 0x5349 ; ADC1 low threshold register low 0x00
 ADC1_SQR1 = 0x534A ; ADC1 channel sequence 1 register 0x00
 ADC1_SQR2 = 0x534B ; ADC1 channel sequence 2 register 0x00
 ADC1_SQR3 = 0x534C ; ADC1 channel sequence 3 register 0x00
 ADC1_SQR4 = 0x534D ; ADC1 channel sequence 4 register 0x00
 ADC1_TRIGR1 = 0x534E ; ADC1 trigger disable 1 0x00
 ADC1_TRIGR2 = 0x534F ; ADC1 trigger disable 2 0x00
 ADC1_TRIGR3 = 0x5350 ; ADC1 trigger disable 3 0x00
 ADC1_TRIGR4 = 0x5351 ; ADC1 trigger disable 4 0x00
; 0x00 53C8 to 0x00 53FF Reserved area

; USART2
  USART2_SR   = 0x53E0      ; USART2 status register0xC0
  USART2_DR   = 0x53E1      ; USART2 data register0xXX
  USART2_BRR1 = 0x53E2      ; USART2 baud rate register 1
  USART2_CR2  = 0x53E5      ; USART2 control register 2
  USART2_CR5  = 0x53E8      ; USART2 control register 5

; USART3
  USART3_SR   = 0x53F0      ; USART3 status register0xC0
  USART3_DR   = 0x53F1      ; USART3 data register0xXX
  USART3_BRR1 = 0x53F2      ; USART3 baud rate register 1
  USART3_CR2  = 0x53F5      ; USART3 control register 2
  USART3_CR5  = 0x53F8      ; USART3 control register 5

      .ifeq   (TARGET - STM8L_MHD) + (USE_UART3 - 1)
        UART_SR   = USART3_SR
        UART_DR   = USART3_DR
        UART_BRR1 = USART3_BRR1
        UART_CR2  = USART3_CR2
        UART_CR5  = USART3_CR5
      .else
        .ifeq   (TARGET - STM8L_MHD) + (USE_UART2 - 1)
        UART_SR   = USART2_SR
        UART_DR   = USART2_DR
        UART_BRR1 = USART2_BRR1
        UART_CR2  = USART2_CR2
        UART_CR5  = USART2_CR5
        .else
        UART_SR   = USART1_SR
        UART_DR   = USART1_DR
        UART_BRR1 = USART1_BRR1
        UART_CR2  = USART1_CR2
        UART_CR5  = USART1_CR5
        .endif
      .endif
;; LCD
 LCD_CR1 = 0x5400 ; LCD control register 1 0x00
 LCD_CR2 = 0x5401 ; LCD control register 2 0x00
 LCD_CR3 = 0x5402 ; LCD control register 3 0x00
 LCD_FRQ = 0x5403 ; LCD frequency selection register 0x00
 LCD_PM0 = 0x5404 ; LCD Port mask register 0 0x00
 LCD_PM1 = 0x5405 ; LCD Port mask register 1 0x00
 LCD_PM2 = 0x5406 ; LCD Port mask register 2 0x00
 LCD_PM3 = 0x5407 ; LCD Port mask register 3 0x00
 LCD_PM4 = 0x5408 ; LCD Port mask register 4 0x00
 LCD_PM5 = 0x5409 ; LCD Port mask register 5 0x00
; 0x00 540A to 0x00 540B Reserved area (2 bytes)
 LCD_RAM0 = 0x540C ; LCD display memory 0 0x00
; ...
 LCD_RAM21 = 0x5421 ; LCD display memory 21 0x00
; 0x00 5422 to 0x00 542E Reserved area
 LCD_CR4 = 0x542F ; LCD control register 4 0x00
; RI
; 0x00 5430 Reserved area (1 byte)
 RI_ICR1 = 0x5431 ; RI Timer input capture routing register 1 0x00
 RI_ICR2 = 0x5432 ; RI Timer input capture routing register 2 0x00
 RI_IOIR1 = 0x5433 ; RI I/O input register 1 0xXX
 RI_IOIR2 = 0x5434 ; RI I/O input register 2 0xXX
 RI_IOIR3 = 0x5435 ; RI I/O input register 3 0xXX
 RI_IOCMR1 = 0x5436 ; RI I/O control mode register 1 0x00
 RI_IOCMR2 = 0x5437 ; RI I/O control mode register 2 0x00
 RI_IOCMR3 = 0x5438 ; RI I/O control mode register 3 0x00
 RI_IOSR1 = 0x5439 ; RI I/O switch register 1 0x00
 RI_IOSR2 = 0x543A ; RI I/O switch register 2 0x00
 RI_IOSR3 = 0x543B ; RI I/O switch register 3 0x00
 RI_IOGCR = 0x543C ; RI I/O group control register 0xFF
 RI_ASCR1 = 0x543D ; Analog switch register 1 0x00
 RI_ASCR2 = 0x543E ; RI Analog switch register 2 0x00
 RI_RCR = 0x543F ; RI Resistor control register  0x00
; 0x00 5440 to 0x00 544F Reserved area (16 bytes)
; RI
 RI_CR = 0x5450 ; RI I/O control register 0x00
 RI_MASKR1 = 0x5451 ; RI I/O mask register 1 0x00
 RI_MASKR2  = 0x5452 ; RI I/O mask register 2 0x00
 RI_MASKR3 = 0x5453 ; RI I/O mask register 3 0x00
 RI_MASKR4 = 0x5454 ; RI I/O mask register 4 0x00
 RI_IOIR4 = 0x5455 ; RI I/O input register 4 0xXX
 RI_IOCMR4 = 0x5456 ; RI I/O control mode register 4 0x00
 RI_IOSR4 = 0x5457 ; RI I/O switch register 4 0x00
; CPU(1)
 A = 0x7F00 ; Accumulator 0x00
 PCE = 0x7F01 ; Program counter extended  0x00
 PCH = 0x7F02 ; Program counter high 0x00
 PCL = 0x7F03 ; Program counter low 0x00
 XH = 0x7F04 ; X index register high 0x00
 XL = 0x7F05 ; X index register low 0x00
 YH = 0x7F06 ; Y index register high 0x00
 YL = 0x7F07 ; Y index register low 0x00
 SPH = 0x7F08 ; Stack pointer high 0x03
 SPL = 0x7F09 ; Stack pointer low 0xFF
 CCR = 0x7F0A ; Condition code register 0x28
; CPU
; 0x00 7F0B to 0x00 7F5F Reserved area (85 bytes)
 CFG_GCR = 0x7F60 ; Global configuration register 0x00
; ITC-SPR

        ITC_IX_TIM2  = 19       ; TIM2 update /overflow
        ITC_IX_TIM3  = 21       ; TIM3 update /overflow
        ITC_IX_TIM1  = 23       ; TIM1 update/overflow/underflow/ trigger/break

 ITC_SPR1 = 0x7F70 ; Interrupt Software priority register 1 0xFF
 ITC_SPR2 = 0x7F71 ; Interrupt Software priority register 2 0xFF
 ITC_SPR3 = 0x7F72 ; Interrupt Software priority register 3 0xFF
 ITC_SPR4 = 0x7F73 ; Interrupt Software priority register 4 0xFF
 ITC_SPR5 = 0x7F74 ; Interrupt Software priority register 5 0xFF
 ITC_SPR6 = 0x7F75 ; Interrupt Software priority register 6 0xFF
 ITC_SPR7 = 0x7F76 ; Interrupt Software priority register 7 0xFF
 ITC_SPR8 = 0x7F77 ; Interrupt Software priority register 8 0xFF
; 0x00 7F78 to 0x00 7F79 Reserved area (2 bytes)
; SWIM
 SWIM_CSR = 0x7F80 ; SWIM control status register 0x00
; 0x00 7F81 to 0x00 7F8F Reserved area (15 bytes)
; DM
 DM_BK1RE = 0x7F90 ; DM breakpoint 1 register extended byte 0xFF
 DM_BK1RH = 0x7F91 ; DM breakpoint 1 register high byte 0xFF
 DM_BK1RL = 0x7F92 ; DM breakpoint 1 register low byte 0xFF
 DM_BK2RE = 0x7F93 ; DM breakpoint 2 register extended byte 0xFF
 DM_BK2RH = 0x7F94 ; DM breakpoint 2 register high byte 0xFF
 DM_BK2RL = 0x7F95 ; DM breakpoint 2 register low byte 0xFF
 DM_CR1 = 0x7F96 ; DM Debug module control register 1 0x00
; DM
 DM_CR2 = 0x7F97 ; DM Debug module control register 2 0x00
 DM_CSR1 = 0x7F98 ; DM Debug module control/status register 1 0x10
 DM_CSR2 = 0x7F99 ; DM Debug module control/status register 2 0x00
 DM_ENFCTR = 0x7F9A ; DM enable function register 0xFF
; 0x00 7F9B to 0x00 7F9F Reserved area (5 bytes)
; 1.   Accessible by debug module only
