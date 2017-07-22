\ STM8S: Shift Right Logical
\ (c) TG9541, refer to licence at github.com/TG9541/stm8ef

\ SRL: shift right logical (unsigned divide by 2)
: SRL ( n -- n )
  \ LDW Y,X , LDW X,(X) , SRLW X , EXGW X,Y , LDW (X),Y
  [ $9093 , $FE C, $54 C, $51 C, $FF C, ] ;
