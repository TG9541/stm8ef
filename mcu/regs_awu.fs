\ STM8S103 AWU register words - immediate
\ (c) TG9541, refer to license at github.com/TG9541/stm8ef/

: AWU_CSR1 $50F0 ; IMMEDIATE \ AWU control/status1 (0x00)
: AWU_APR  $50F1 ; IMMEDIATE \ AWU asynch. prescaler buf. (0x3F)
: AWU_TBR  $50F2 ; IMMEDIATE \ AWU timebase selection (0x00)
