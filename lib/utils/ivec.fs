\ Patch STM8 interrupt vector n to handler a
\ refer to github.com/TG9541/stm8ef/blob/master/LICENSE.md

\ Interrupt handler a should use SAVEC, IRET, and little stack
\ github.com/TG9541/stm8ef/wiki/STM8S-eForth-Interrupts
: IVEC  ( a n -- )
  2* 2* $800A + !
;

