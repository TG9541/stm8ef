\ STM8EF dictionary management
\ Manage NVM reset 
\ (c) TG9541, refer to licence at github.com/TG9541/stm8ef/

\ Set RESET defaults to include newly defined NVM words  
: PERSIST ( -- )
  ULOCKF 
  'BOOT DUP $12 DUP ROT + SWAP CMOVE
  LOCKF
;
