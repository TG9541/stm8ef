( Work-in-progress library for the ezradio pro )
FILE
VARIABLE cmdbuf 128 ALLOT
HEX
: cs_delay ( -- )
80 0 DO LOOP ;
: cmdsend ( cmdlen -- ) 
cs_delay
SPIS
cs_delay
cmdbuf OVER 0
DO
  DUP C@ SPI 
  OVER C!
  1+
LOOP
DROP SPIE ; 
: cmdprint ( cmdlen -- )
cmdbuf OVER 0 DO
  DUP C@ .
  1+ 
LOOP
DROP ;
: cmdbufwipe ( cmdlen -- )
cmdbuf OVER 0 DO
  FF OVER C! 1+
LOOP
DROP ;
: ezrinit ( -- ) EZD EZE SPIS ;
HAND
