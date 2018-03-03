;--------------------------------------------------------
;       STM8 eForth Board I/O
;       key input, and LED 7-segment LED display output
;--------------------------------------------------------

        .ifne   HAS_KEYS

;       ?KEYB   ( -- c T | F )  ( TOS STM8: -- Y,Z,N )
;       Return keyboard char and true, or false if no key pressed.

        HEADER  QKEYB "?KEYB"
QKEYB:
        CALL    BKEYCHAR        ; Read char from keyboard (option: vectored code)
        CALL    AFLAGS

        JRNE    KEYBPRESS
        ; Bit7: flag press + 100*5ms hold before repetition
        MOV     KEYREPET,#(0x80 + 100)
        JRA     NOKEYB
KEYBPRESS:
        BTJF    KEYREPET,#7,KEYBHOLD
        BRES    KEYREPET,#7
        JRA     ATOKEYB
KEYBHOLD:
        DEC     KEYREPET
        JRNE    NOKEYB
        MOV     KEYREPET,#30    ; repetition time: n*5ms
ATOKEYB:
        JP      ATOKEY          ; push char and flag true
NOKEYB:
        JP      ZERO            ; push flag false

        .endif

        .ifne   HAS_LED7SEG

;       7-seg LED patterns, "70s chique"
PAT7SM9:
        .db     0x00, 0x40, 0x80, 0x52 ; , - . / (',' as blank)
        .db     0x3F, 0x06, 0x5B, 0x4F ; 0,1,2,3
        .db     0x66, 0x6D, 0x7D, 0x07 ; 4,5,6,7
        .db     0x7F, 0x6F             ; 8,9
PAT7SAZ:
        .db           0x77, 0x7C, 0x39 ;   A,B,C
        .db     0x5E, 0x79, 0x71, 0x3D ; D,E,F,G
        .db     0x74, 0x30, 0x1E, 0x7A ; H,I,J,K
        .db     0x38, 0x55, 0x54, 0x5C ; L,M,N,O
        .db     0x73, 0x67, 0x50, 0x6D ; P,Q,R,S
        .db     0x78, 0x3E, 0x1C, 0x1D ; T,U,V,W
        .db     0x76, 0x6E, 0x5B       ; X,Y,Z

;       E7S  ( c -- )
;       Convert char to 7-seg LED pattern, and insert it in display buffer

        HEADER  EMIT7S "E7S"
EMIT7S:
        LD      A,(1,X)         ; c to A

        CP      A,#' '
        JRNE    E7SNOBLK

        .if     gt,(HAS_LED7SEG-1)
        LD      A,LED7GROUP
        JRMI    2$              ; test LED7GROUP.7 "no-tab flag"
        INC     A
        CP      A,#HAS_LED7SEG
        JRULT   1$
        CLR     A
1$:     OR      A,#0x80         ; only one tab action, set "no-tab flag"
        LD      LED7GROUP,A

2$:     CALLR   XLEDGROUP
        EXGW    X,Y             ; restore X/Y after XLEDGROUP
        .else
        LDW     Y,#LED7FIRST    ; DROP DOLIT LED7FIRST
        .endif
        LDW     (X),Y
        DoLitC  LEN_7SGROUP
        JP      ERASE

E7SNOBLK:

        .if     gt,(HAS_LED7SEG-1)
        CP      A,#LF           ; test for c ~ /[<CR><LF>]/
        JRNE    E7SNOLF
        MOV     LED7GROUP,#0x80 ; go to first LED group, set "no-tab flag"
        JRA     E7END
        .endif

E7SNOLF:
        .if     gt,(HAS_LED7SEG-1)
        BRES    LED7GROUP,#7    ; on char output: clear "no-tab flag"
        .endif

        CP      A,#'.'
        JREQ    E7DOT
        CP      A,#','
        JRMI    E7END
        CP      A,#'z'
        JRPL    E7END
        CP      A,#'A'
        JRUGE   E7ALPH

        ; '-'--'9' (and '@')
        SUB     A,#','
        LD      (1,X),A
        DoLitW  PAT7SM9
        JRA     E7LOOKA
E7ALPH:
        ; 'A'--'z'
        AND     A,#0x5F         ; convert to uppercase
        SUB     A,#'A'
        LD      (1,X),A
        DoLitW  PAT7SAZ
E7LOOKA:
        CALL    PLUS
        CALL    CAT
        JP      PUT7S

E7DOT:
        .if     gt,(HAS_LED7SEG-1)
        CALL    XLEDGROUP
        LD      A,((LEN_7SGROUP-1),X)
        OR      A,#0x80
        LD      ((LEN_7SGROUP-1),X),A
        EXGW    X,Y             ; restore X/Y after XLEDGROUP
        ; fall trough

        .else
        LD      A,#0x80         ; 7-seg P (dot)
        OR      A,LED7LAST
        LD      LED7LAST,A
        .endif
        ; fall trough

E7END:
        JP      DROP

        .if     gt,(HAS_LED7SEG-1)
;       Helper routine for calculating LED group start adress
;       return: X: LED group addr, Y: DSP, A: LEN_7SGROUP
;       caution: caller must restore X/Y!
XLEDGROUP:
        EXGW    X,Y             ; use X to save memory
        LD      A,LED7GROUP
        AND     A,#0x7F         ; ignore "no-tab flag"
        LD      XL,A
        LD      A,#LEN_7SGROUP
        MUL     X,A
        ADDW    X,#LED7FIRST
        RET
        .endif

;       P7S  ( c -- )
;       Right aligned 7S-LED pattern output, rotates LED group buffer

        HEADER  PUT7S "P7S"
PUT7S:
        .if     gt,(HAS_LED7SEG-1)
        CALLR   XLEDGROUP
        DEC     A
        PUSH    A
1$:     LD      A,(1,X)
        LD      (X),A
        INCW    X
        DEC     (1,SP)
        JRNE    1$
        POP     A

        EXGW    X,Y             ; restore X/Y after XLEDGROUP
        CALL    AFLAGS
        LD      (Y),A
        .else
        DoLitC  LED7FIRST+1
        DoLitC  LED7FIRST
        DoLitC  (LEN_7SGROUP-1)
        CALL    CMOVE
        CALL    AFLAGS
        LD      LED7LAST,A
        .endif

        RET
        .endif
