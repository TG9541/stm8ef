; STM8S105K4 generic SWIM single pin communication


;       BOARDINIT  ( -- )
;       Init board GPIO (except COM ports)

BOARDINIT:
        ; Board I/O initialization
        BSET    PE_DDR,#5
        BSET    PE_CR1,#5

        .ifne   HAS_OUTPUTS
        CLR     A
        JRA     AOUTSTOR
        .else
        RET
        .endif

;===============================================================

        .ifne   HAS_LED7SEG
;       LED_MPX driver ( -- )
;       Code called from ISR for LED MPX

LED_MPX:        
        RET
        .endif

        
;===============================================================

        .ifne   HAS_OUTPUTS
        RamWord OUTPUTS         ; "OUT", e.g. relays, LEDs, etc. (16 bit)

;       OUT!  ( c -- )
;       Put c to board outputs, storing a copy in OUTPUTS  
        .dw     LINK

        LINK =  .
        .db     (4)
        .ascii  "OUT!"
OUTSTOR:
        INCW    X
        LD      A,(X)
        INCW    X
AOUTSTOR:
        LD      OUTPUTS+1,A
        RRC     A
        CCF
        BCCM    PE_ODR,#5       ; STM8105K4 dev board: PE5 LED
        RET       
        .endif

;===============================================================

        .ifne   HAS_KEYS
;       BKEY  ( -- f )     ( TOS STM8: -- A,Z,N )
;       Read board key state as a bitfield
        .dw     LINK
        
        LINK =  .
        .db     (4)
        .ascii  "BKEY"
BKEY:   
        CLR     A
        JP      ASTOR


;       BKEYC  (  -- c )   ( TOS STM8: -- A,Z,N )
;       Read and translate board dependent key bitmap into char 

BKEYCHAR:
        JRA     BKEY            ; Dummy: get "no key" and leave it as it is 
       .endif
