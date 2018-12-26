\ stm8ef : voc-i2c-core.fs                                             MM-170928
\ ------------------------------------------------------------------------------
\             I2C Library, Core Word Set, Bit-Bang Implementation
\
\               Copyright (C) 2017 manfred.mahlow@forth-ev.de
\
\ Requires: * STM8S eForth on STM8S103xy
\           * e4thcom -t stm8ef
\
\ Uses: PB5 as serial data pin (SDA)
\       PB4 as serial clock pin (SCL)

\ I2C clock frequency : ?
\
\ External pull-up resistors of 10 kOhm are required on the SDA and SCL pins.
\

#require VOC \ requires the persistent patch for context switching, see CURRENT

#require CONSTANT
#require :NVM
#require ALIAS
#require ]B!

\res MCU: STM8S103

RAM

\res export PB_IDR  PB_ODR  PB_DDR
\res export BIT5

:NVM ( -- ) [ 0 PB_DDR 5 ]B! ;RAM      ALIAS SDA1
:NVM ( -- ) [ 1 PB_DDR 5 ]B! ;RAM      ALIAS SDA0
:NVM ( -- f ) PB_IDR C@ BIT5 AND ;RAM  ALIAS SDA?
:NVM ( -- ) [ 0 PB_DDR 4 ]B! ;RAM      ALIAS SCL1
:NVM ( -- ) [ 1 PB_DDR 4 ]B! ;RAM      ALIAS SCL0

NVM

VOC i2c  i2c DEFINITIONS

: init ( -- )
\ Initialize the I2C Bus interface
  SDA1 SCL1                          \ enable I2C pins as input
  [ 0 PB_ODR 5 ]B! [ 0 PB_ODR 4 ]B!  \ set output registers low
;

\ : wait ( -- ) ;

: start ( -- ) \ in: SDA=? SCL=? out: SDA=SCL=0
\ Start an I2C Bus transmission.
  SDA1 SCL1 ( wait ) SDA0 ( wait ) SCL0 ;

: stop ( -- )
\ Stop an I2C Bus transmission.
  SDA0 ( wait ) SCL1 ( wait ) SDA1 ;

: tx ( byte -- )
\ Send a byte to the I2C Bus.
  7 FOR DUP $80 AND IF SDA1 ELSE SDA0 THEN ( wait ) SCL1 ( wait ) SCL0 2* NEXT
  DROP ;

: nak? ( -- f ) \ in: SDA=? SCL=0  out: SDA=1 SCL=0
\ Return a true/false flag if an NAK/ACK was received from the I2C Bus.
  SDA1 ( wait ) SCL1 ( wait ) SDA? SCL0 ;

: rx ( -- byte ) \ in: SDA=1 SCL=0   out: SDA=?  SCL=0
\ Receive a byte from the I2C Bus.
  0 7 FOR ( wait ) SCL1 ( wait ) SDA? SCL0 IF 1 ELSE 0 THEN SWAP 2* OR NEXT ;

: nak ( -- ) \ in: SDA=? SCL=0  out: SDA=1 SCL=0
\ Send an NAK to the I2C Bus.
 SDA1 ( wait ) SCL1 ( wait ) SCL0 ;

: ack ( -- ) \ in: SDA=? SCL=0  out: SDA=1 SCL=0
\ Send an ACK to the I2C Bus.
  SDA0 ( wait ) SCL1 ( wait ) SCL0 SDA1 ;

: rdy ( sid -- f )
\ Send a start/stop sequence with the slave address sid and return true if an
\ ACK is returned. Otherwise return a false flag.
  2*  i2c start  i2c tx  i2c nak? 0=  i2c stop ;

FORTH DEFINITIONS

RAM WIPE

i2c init

\index  i2c rdy .  i2c init  i2c WORDS

\ ------------------------------------------------------------------------------
\ Last Revision: MM-171121  B! --> ]B!




