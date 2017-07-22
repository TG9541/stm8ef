\ STM8S103 AWU register words
\ (c) TG9541, refer to licence at github.com/TG9541/stm8ef/

\ AWU control/status register 1         (0x00)
: AWU_CSR1   $50F0 [COMPILE] LITERAL ; IMMEDIATE

\ AWU asynchronous prescaler buffer register (0x3F)
: AWU_APR    $50F1 [COMPILE] LITERAL ; IMMEDIATE

\ AWU timebase selection register       (0x00)
: AWU_TBR    $50F2 [COMPILE] LITERAL ; IMMEDIATE

