\ STM8S option setting words
\ refer to github.com/TG9541/stm8ef/blob/master/LICENSE.md

\ store char to (a), and inverted value to (a+1)
: CN! ( c a -- )
  2DUP C! SWAP NOT SWAP 1+ C!
;

\ unlock write protection, store option byte
: OPT! ( c a -- )
  [ FLASH_CR2 ] LITERAL DUP C@ $80 OR SWAP CN!
  ULOCK CN! LOCK
;
