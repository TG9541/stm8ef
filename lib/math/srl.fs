\ STM8S: Shift Right Logical
\ refer to github.com/TG9541/stm8ef/blob/master/LICENSE.md

\ SRL: shift right logical (unsigned divide by 2)
: SRL ( n -- n )
  \ LDW Y,X , LDW X,(X) , SRLW X , EXGW X,Y , LDW (X),Y
  [ $9093 , $FE C, $54 C, $51 C, $FF C, ] ;
