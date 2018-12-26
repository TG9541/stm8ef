\ stm8ef : voc-i2c.fs                                                  MM-170928
\ ------------------------------------------------------------------------------
\           I2C Library, Extended Word Set ( extends voc-i2c-core.fs )
\
\               Copyright (C) 2017 manfred.mahlow@forth-ev.de
\
\ Requires: * STM8S eForth on STM8S103xy
\           * e4thcom -t stm8ef
\           * voc-i2c-core-fs
\

\ #require LSHIFT
\ #require RSHIFT

#require WIPE
#require ABORT"

NVM i2c DEFINITIONS

BASE @ HEX

: ?ack ( -- )
  \ Throw an error if no ACK was received.
  i2c nak? DUP IF i2c stop THEN ABORT"  I2C: ACK missing"
;

: out ( cn .. c1 +n sid -- )
\ Send sid and +n bytes without start and stop condition to an I2C slave. sid
\ is the slaves 7 bit id or addr. An ambiguous condition exists for n = 0.
  2* ( r/w bit = 0 ) SWAP FOR i2c tx i2c ?ack NEXT
;

: write ( cn .. c1 +n sid -- )
\ Send sid and +n bytes with start and stop condition to an I2C slave. sid is
\ the slaves 7 bit id or addr. An ambiguous condition exists for n = 0.
  i2c start i2c out i2c stop ;

: in ( +n sid -- c1 .. cn )
\ Read +n bytes from I2C slave sid. Do not send a start or stop condition. An
\ ambiguous condition exists for n = 0.
  2* 1 OR i2c tx i2c ?ack 1 - FOR i2c rx R@ IF i2c ack ELSE i2c nak THEN NEXT ;

: read ( +n c|a sid -- c1 .. cn )
\ Send the command or address byte c|a to the I2C slave sid and read +n bytes
\ back. sid is the slaves 7 bit identifier or address. An ambiguous condition
\ exists for n = 0.
  >R 1 R@ i2c start i2c out         \ send c|a
  R> i2c start i2c in i2c stop ;    \ read data bytes

\ A dummy for compatibility with the hardware based I2C version.
: ?busy ( -- ) ;

BASE !

FORTH DEFINITIONS

RAM WIPE

\ ------------------------------------------------------------------------------
\ Last Revision: MM-171129 Comment updated
\                MM-170928 ported from noForth V

