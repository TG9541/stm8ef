( Work-in-progress library for the ezradio pro )
FILE
VARIABLE cmdbuf 128 ALLOT
HEX
: cmdsend ( cmdlen -- ) 
SPIS
cmdbuf OVER 0 DO
DUP C@ SPI 
OVER C!
2 +
LOOP
DROP SPIE ; 
: cmdprint ( cmdlen -- )
cmdbuf OVER 0 DO
DUP C@ . 2 + 
LOOP
DROP ;
: ezrinit ( -- ) EZD EZE SPIS ;
HAND
