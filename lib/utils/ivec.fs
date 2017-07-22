\ Patch STM8 interrupt vector n to handler a
\ (c) TG9541, refer to licence at github.com/TG9541/stm8ef/
 
\ Interrupt handler a should use SAVEC, IRET, and little stack
\ github.com/TG9541/stm8ef/wiki/STM8S-eForth-Interrupts
: IVEC  ( a n -- )  
  2* 2* $800A + !
;

