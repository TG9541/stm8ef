;--------------------------------------------------------
;       STM8 eForth           STM8S/L Family ADC code 
;--------------------------------------------------------
        
        .ifne   HAS_ADC
;       ADC!  ( c -- )
;       Init ADC, select channel for conversion

	.ifeq   (TARGET - STM8L051F3)
;		ADC for L051F3
	HEADER  ADCSTOR "ADC!"
ADCSTOR:
		BSET	CLK_PCKENR2,#0	; enable clock for ADC
		BSET    ADC1_CR1,#0     ; enable ADC
		LD		A,#4
		LDW		Y,#ADC1_LTRL
0$:		INCW	Y				; clear DAC1_SQRx
		CLR		(Y)
		DEC		A
		JRUGT	0$
		CALL	AFLAGS	; A = adc channel#
		INC		A
		LDW		Y,#4
1$:		DECW	Y		; select appropriate ADC1-SQR#
		SUB		A,#8
		JRUGT	1$
		ADD		A,#7
		CALL	YSTOR	; offset to DAC_SQR1 -> tos
		CLRW	Y
		LD		YL,A
		LD		A,#1
		JP		3$
2$:		SLL		A
3$:		DECW	Y
		JRSGE	2$
		CALL	YFLAGS
		LD		(ADC1_SQR1,Y),A	; set channel bit
		BSET    ADC1_SQR1,#7    ; DMA disabled for single conversion
		BRES    ADC1_CR1,#0		; disable ADC
		RET

;       ADC@  ( -- w )
;       start ADC conversion, read result

	HEADER  ADCAT "ADC@"
ADCAT:
	BRES    ADC1_SR,#0      ; reset EOC
	BSET    ADC1_CR1,#0     ; enable ADC
	BSET    ADC1_CR1,#1     ; start ADC
1$:	BTJF    ADC1_SR,#0,1$   ; wait until EOC
	LDW		Y,ADC1_DRH      ; read ADC
	JP      YSTOR
	BRES    ADC1_CR1,#0     ; disable ADC

	.else

	HEADER  ADCSTOR "ADC!"
ADCSTOR:
        INCW    X
        LD      A,(X)			
        INCW    X
		AND     A,#0x0F
        LD      ADC_CSR,A       ; select channel
        BSET    ADC_CR2,#3      ; align ADC to LSB
        BSET    ADC_CR1,#0      ; enable ADC
        RET

;       ADC@  ( -- w )
;       start ADC conversion, read result

        HEADER  ADCAT "ADC@"
ADCAT:
	BRES    ADC_CSR,#7      ; reset EOC
	BSET    ADC_CR1,#0      ; start ADC
1$:	BTJF    ADC_CSR,#7,1$   ; wait until EOC
	LDW     Y,ADC_DRH       ; read ADC
	JP      YSTOR
	.endif
	.endif
