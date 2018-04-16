\ STM8 eForth XH-M194 board.fs
\ refer to github.com/TG9541/stm8ef/blob/master/LICENSE.md
\
\ * DS1302 RTC routines using in-line assembly

RAM

\res MCU: STM8S105
\res export PA_ODR
\res export PB_ODR
\res export PB_DDR
\res export PB_IDR
\res export PB_CR1

#require ]B!
#require ]CB
#require ]BC
#require WIPE
#require :NVM
#require ALIAS

  \ opcode: rotate c at TOS through carry flag
  $6601 CONSTANT RRC(1,X)

  : RTCLK PA_ODR 6 ; \ DS1302 SCLK
  : RTCE  PB_ODR 6 ; \ DS1302 CE
  : RTOUT PB_ODR 7 ; \ DS1302 I/O (out)
  : RTIN  PB_IDR 7 ; \ DS1302 I/O (in)

  :NVM ( -- c )
    \ DS1302 8 bit read
    0 7 FOR
      [ 0 RTCLK ]B!
      [ RTIN ]BC [ RRC(1,X) , ]
      [ 1 RTCLK ]B!
    NEXT
  ;RAM ALIAS RB

  :NVM ( c -- )
    \ DS1302 8 bit write
    [ 1 PB_DDR 7 ]B!  [ 1 PB_CR1 7 ]B!
    7 FOR
      [ 0 RTCLK ]B!
      [ RRC(1,X) , RTOUT ]CB
      [ 1 RTCLK ]B!
    NEXT DROP
    [ 0 PB_DDR 7 ]B!  [ 0 PB_CR1 7 ]B!
  ;RAM ALIAS WB

  :NVM ( c a -- )
    2* $80 OR
  ;RAM ALIAS ADDR

NVM

  : RTC@ ( a -- c )
    \ read byte from DS1302 at a=0..8:clock, or a=32..62:RAM
    [ 1 RTCE ]B! ADDR 1+ WB RB [ 0 RTCE ]B!
  ;

  : RTC! ( c a -- )
    \ write byte to DS1302 at a=0..8:clock, or a=32..62:RAM
    [ 1 RTCE ]B! ADDR    WB WB [ 0 RTCE ]B!
  ;

  : BURST@ ( a -- )
    \ Burst-read 7 RTC time/date registers to variable RTC
    [ 1 RTCE ]B! $BF WB
    6 FOR
      RB OVER C! 1+
    NEXT DROP
    [ 0 RTCE ]B!
  ;

  : BURST! ( a -- )
    \ Burst-write variable RTC to 7 RTC time/date registers
    [ 1 RTCE ]B! $BE WB
    6 FOR
      DUP C@ WB 1+
    NEXT DROP
    [ 0 RTCE ]B!
  ;

RAM WIPE

\\ Example:

: decode ( c -- c )
  \ DS1302 uses BCD encoding
  16 /MOD 10 * +
;

: minsec ( -- )
  \ show minutes and seconds, e.g. on the 7S-LED display
  0 RTC@ decode
  1 RTC@ decode
  100 * + .
;

\ set background task
' minsec BG !

VARIABLE MRTC 5 ALLOT  \ memory for RTC Burst

\ read and dump the RTC clock register
MRTC BURST@   MRTC 7 DUMP
