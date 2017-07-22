\ STM8S option setting words
\ (c) TG9541, refer to licence at github.com/TG9541/stm8ef

\ store char to (a), and inverted value to (a+1)
: CN! ( c a -- )
  2DUP C! SWAP NOT SWAP 1+ C!
;

\ unlock write protection, store option byte
: OPT! ( c a -- )
  FLASH_CR2 DUP C@ $80 OR SWAP CN!
  ULOCK CN! LOCK
;
