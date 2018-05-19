\ STM8S103 PD8544 "Nokia 3110 LCD"
\ requires configuration-words with port DDR address and bit numbers
\ see Example section below
\ refer to github.com/TG9541/stm8ef/blob/master/LICENSE.md

\ send c through SPI, discard input
: LCDout ( c -- )
  [ 0 LCDsce ]B!
  SPI
  [ 1 LCDsce ]B!
  DROP
;

\ set horizontal cursor to c ( 0..83 )
: LCDx ( c -- )
  [ 0 LCDdc ]B!
  $80 + LCDout
  [ 1 LCDdc ]B!
;

\ set vertical cursor to c ( 0..5 )
: LCDy ( c -- )
  [ 0 LCDdc ]B!
  $40 + LCDout
  [ 1 LCDdc ]B!
;

\ set cursor to (0,0)
: LCDhome ( -- )
  0 LCDx 0 LCDy
;

\ fill LCD with pattern c (use y auto increment)
: LCDfill ( c -- )
  LCDhome
  503 FOR
    DUP LCDout
  NEXT DROP
;

\ init ports, SPI, PD8544 with Vop c (0..127)
: LCDinit ( c -- )
  [ 0 LCDdc ]B!
  $21 LCDout \ instructions extended
  $14 LCDout \ bias 4
  $80 + LCDout \ Vop, e.g. 60
  $20 LCDout \ instructions normal
  $0C LCDout \ display conf ($08:blank,$09:on,$0C:normal,$0D:inv)
  [ 1 LCDdc ]B!
  0 LCDfill
;

\ copy n chars starting at a to PD8544
: LCDcpy ( a n -- )
  FOR DUP C@ LCDout 1+ NEXT DROP
;


\\ Example:

#require ]C!
#require ]B!

\res MCU: STM8S103

\res export PC_ODR
\res export PC_DDR
\res export PC_CR1

: LCDsce ( -- n n )
  \ configure port and bit# for chip enable (/SCE)
  PC_ODR 3   \ PC3
;

: LCDdc ( -- n n )
  \ configure port and bit# for data/command (D/C)
  PC_ODR 4   \ PC4
;

\ peripheral register constants for spi.fs
\res export SPI_CR1
\res export SPI_CR2
\res export SPI_SR
\res export SPI_DR

NVM

#include hw/spi.fs
#include hw/pd8544.fs

: init
  [ $18 PC_DDR ]C!
  [ $18 PC_CR1 ]C!
  1 SPIon
  65 LCDinit  \ init, set contrast value
;

RAM

\ test
init
$AA LCDfill \ fill the LCD with horizontal lines
