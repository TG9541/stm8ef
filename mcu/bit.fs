\ STM8S assembly words
\ (c) TG9541, refer to license at github.com/TG9541/stm8ef

: bit! ( b a c -- )
  rot 0= 1 and swap 2* $10 + + $72 c, c, , 
; immediate

: bres ( a c -- ) [ 0 ] [compile] bit! ; immediate

: bset ( a c -- ) [ 1 ] [compile] bit! ; immediate
