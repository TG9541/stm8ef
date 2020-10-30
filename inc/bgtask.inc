;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------

        .globl _TRAP_Handler
        .globl _TIM1_IRQHandler
        .globl _TIM2_IRQHandler
        .globl _TIM3_IRQHandler
        .globl _forth

        ;******  Board variables  ******

        .ifne   HAS_BACKGROUND
        RamWord BGADDR          ; address of background routine (0: off)
        RamWord TICKCNT         ; "TICKCNT" 16 bit ticker (counts up)

        BSPPSIZE = BG_STACKSIZE ; Size of data stack for background tasks
       .endif

       ;******  timer macro  ******

        ; init BG timer interrupt
        .macro BGTASK_Init
        .ifne   HAS_BACKGROUND

        .ifne   BG_USE_TIM1
        BG_INT = ITC_IX_TIM1
        MOV     TIM1_PSCRL,#7   ; prescaler 1/(7+1) = 1/8
        .else
        .ifne   BG_USE_TIM3
        BG_INT = ITC_IX_TIM3
        .else
        BG_INT = ITC_IX_TIM2
        .endif
        MOV     BG_TIM_PSCR,#3  ; prescaler 1/(2^3) = 1/8
        .endif
        BRES    ITC_SPR1+(BG_INT/4),#((BG_INT%4)*2+1)  ; Interrupt prio. low

        MOV     BG_TIM_ARRH,#(BG_TIM_REL/256)  ; reload H
        MOV     BG_TIM_ARRL,#(BG_TIM_REL%256)  ;        L
        MOV     BG_TIM_CR1,#0x01 ; enable background timer
        MOV     BG_TIM_IER,#0x01 ; enable background timer interrupt
        .endif
        .endm

       ;******  ISR handler  ******

;       TIM1 or TIM2 interrupt handler for background task
_TIM1_IRQHandler:
_TIM2_IRQHandler:
_TIM3_IRQHandler:
        .ifne   (HAS_LED7SEG + HAS_BACKGROUND)
        BRES    BG_TIM_SR1,#0   ; clear TIMx UIF

        .ifne   HAS_LED7SEG
        CALL    LED_MPX         ; "PC_LEDMPX" board dependent code for 7Seg-LED-Displays
        .endif

;       Background operation saves & restores the context of the interactive task
;       Cyclic context reset of Forth background task (stack, BASE, HLD, I/O vector)
        .ifne   HAS_BACKGROUND
        LDW     X,TICKCNT
        INCW    X
        LDW     TICKCNT,X
        ; fall through

        .ifne   BG_RUNMASK
        LD      A,XL            ; Background task runs if "(BG_RUNMASK AND TICKCNT) equals 0"
        AND     A,#BG_RUNMASK
        JRNE    TIM2IRET
        .endif

        LDW     Y,BGADDR        ; address of background task
        TNZW    Y               ; 0: background operation off
        JREQ    TIM2IRET

        LDW     X,YTEMP         ; Save context
        PUSHW   X

        PUSH    USRBASE+1       ; 8bit since BASE should be < 36
        MOV     USRBASE+1,#10

        LDW     X,USREMIT       ; save EMIT exection vector
        PUSHW   X
        LDW     X,#EMIT_BG      ; "'BGEMIT" xt of EMIT for BG task
        LDW     USREMIT,X

        LDW     X,USRQKEY       ; save QKEY exection vector
        PUSHW   X
        LDW     X,#QKEY_BG      ; "'?BGKEY" xt of ?KEY for BG task
        LDW     USRQKEY,X

        LDW     X,USRHLD
        PUSHW   X
        LDW     X,#PADBG        ; "BGPAD" empty PAD for BG task
        LDW     USRHLD,X

        LDW     X,#BSPP         ; "BGSPP" data stack for BG task
        CALL    (Y)

        POPW    X
        LDW     USRHLD,X

        POPW    X
        LDW     USRQKEY,X

        POPW    X
        LDW     USREMIT,X

        POP     USRBASE+1

        POPW    X
        LDW     YTEMP,X
TIM2IRET:
        .endif

        IRET
        .endif

       ;******  BG User Words  ******

        .ifne   HAS_BACKGROUND
;       TIM     ( -- T)     ( TOS STM8: -- Y,Z,N )
;       Return TICKCNT as timer

        HEADER  TIMM "TIM"
TIMM:
        LDW     Y,TICKCNT
        JP      AYSTOR


;       BG      ( -- a)     ( TOS STM8: -- Y,Z,N )
;       Return address of BGADDR vector

        HEADER  BGG "BG"
BGG:
        LD      A,#(BGADDR)
        JP      ASTOR
        .endif
