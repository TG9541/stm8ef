;--------------------------------------------------------
;       STM8 eForth           STM8S Family ADC code 
;--------------------------------------------------------
        
        .ifne   HAS_ADC
;       ADC!  ( c -- )
;       Init ADC, select channel for conversion

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
1$:     BTJF    ADC_CSR,#7,1$   ; wait until EOC
        LDW     Y,ADC_DRH       ; read ADC
        JP      YSTOR
        .endif
