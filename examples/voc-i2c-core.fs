\ stm8ef : voc-i2c-core.fs                                             MM-170928
\ ------------------------------------------------------------------------------
\             I2C Bus Master, Core Word Set, Bit-Bang Implementation
\
\               Copyright (C) 2017,2018 manfred.mahlow@forth-ev.de
\
\           License see github.com/TG9541/stm8ef/blob/master/LICENSE.md
\
\ Requires: * STM8S eForth on an STM8S MCU (tested with STM8S103xy  STM8S105xy)
\           * e4thcom Terminal (e4thcom-x.y.z -t stm8ef) or codeload.py
\
\ Uses: PB5 as serial data pin (SDA)
\       PB4 as serial clock pin (SCL)

\ I2C clock frequency : ~ 50 kHz with 8 MHz MCU clock
\
\ External pull-up resistors of ~ 10 kOhm are required on the SDA and SCL pins.
\

#require VOC
#require :NVM
#require ALIAS
#require ]B!
#require ]B?
#require WIPE

\res MCU: STM8S103

RAM

\res export PB_IDR  PB_ODR  PB_DDR   PB_CR1  PB_CR2

:NVM ( -- ) dup drop ;RAM ALIAS WAIT

:NVM ( -- ) [ 0 PB_DDR 4 ]B! WAIT ;RAM  ALIAS SCL1
:NVM ( -- ) WAIT [ 1 PB_DDR 4 ]B! ;RAM  ALIAS SCL0

:NVM ( -- ) [ 0 PB_DDR 5 ]B! WAIT ;RAM  ALIAS SDA1
:NVM ( -- ) WAIT [ 1 PB_DDR 5 ]B! ;RAM  ALIAS SDA0

:NVM ( -- f ) WAIT [ PB_IDR 5 ]B? ;RAM  ALIAS SDA?

NVM

VOC i2c  i2c DEFINITIONS

: start ( -- ) \ in: SDA=? SCL=? out: SDA=SCL=0
\ Start an I2C Bus transmission.
  SDA1 SCL1 SDA0 SCL0 ;

: stop ( -- ) \ in: SDA=1 SCL=0  out: SDA=SCL=1
\ Stop an I2C Bus transmission.
  SDA0 SCL1 SDA1 ;

: tx ( byte -- )
\ Send a byte to the I2C Bus.
  DUP 7 FOR $80 AND IF SDA1 ELSE SDA0 THEN SCL1 2* DUP SCL0 NEXT 2DROP ;

: nak? ( -- f ) \ in: SDA=? SCL=0  out: SDA=1 SCL=0
\ Return a true/false flag if an NAK/ACK was received from the I2C Bus.
  SDA1 SCL1 SDA? SCL0 ;

: rx ( -- byte ) \ in: SDA=1 SCL=0   out: SDA=?  SCL=0
\ Receive a byte from the I2C Bus.
  0 7 FOR 2* SCL1 SDA? SCL0 ABS OR NEXT ;

: nak ( -- ) \ in: SDA=? SCL=0  out: SDA=1 SCL=0
\ Send an NAK to the I2C Bus.
  SDA1 SCL1 SCL0 ;

: ack ( -- ) \ in: SDA=? SCL=0  out: SDA=1 SCL=0
\ Send an ACK to the I2C Bus.
  SDA0 SCL1 SCL0 SDA1 ;

: rdy ( sid -- f )
\ Send a start/stop sequence with the slave address sid and return true if an
\ ACK is returned. Otherwise return a false flag.
  2*  i2c start  i2c tx  i2c nak? 0=  i2c stop ;

: init ( -- )
\ Initialize the I2C Bus interface
  SDA1 SCL1                        \ enable I2C pins as input
  [ 0 PB_ODR 5 ]B! [ 0 PB_ODR 4 ]B!  \ set output registers low
  \ Send a start/stop sequence. Otherwise the first bus access fails with an
  \ ACK error
  i2c start i2c stop
;

FORTH DEFINITIONS

RAM WIPE

i2c init

\ ------------------------------------------------------------------------------
\ Last Revision: TG951 ]B? parameter order changed
\                MM-181221 V1.1 , ]B? and WAIT added
\                MM-171206 start/stop sequence added to i2c init
\                MM-171121 B! --> ]B!
\                MM-170928 ported from MSP430 Version
