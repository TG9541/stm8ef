( Work-in-progress library for the ezradio pro )
FILE

VARIABLE cmdbuf 14 ALLOT

: cs_delay ( -- )
  $80 0 DO LOOP ;

: cmdsend ( cmdlen -- )
  cs_delay  SPIS  cs_delay
  cmdbuf OVER 0
  DO
    DUP C@ SPI
    OVER C!
    1+
    LOOP/
  DROP SPIE ;

: cmdprint ( cmdlen -- )
  cmdbuf OVER 0 DO
    DUP C@ .
    1+
    LOOP
  DROP ;

: cmdbufwipe ( cmdlen -- )
  cmdbuf OVER 0 DO
    $FF OVER C! 1+
    LOOP
  DROP ;

: ezrinit ( -- )
  EZD EZE SPIS ;

\ : spicmd ( a n -- ) \ transfer n bytes from a to SPI
\ : spicmd DUP ROT cmdbuf ROT CMOVE cmdsend DROP ;
\ : seq ( a -- a )  \ transfer a 0-terminated sequence of commands to SPI
\  begin count ?dup while
\    2dup spicmd +
\  repeat ;
\ : seq begin count ?dup while 2dup mycmd @execute + repeat ;


