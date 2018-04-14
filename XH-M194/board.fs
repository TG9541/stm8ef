\ STM8 eForth XH-M194 board.fs
\ refer to github.com/TG9541/stm8ef/blob/master/LICENSE.md
\
\ * DS1302 RTC routines

RAM

\res MCU: STM8S105
\res export PA_ODR
\res export PB_ODR
\res export PB_DDR
\res export PB_IDR
\res export PB_CR1

#require ]B!
#require ]BCCM
#require ]B?C
#require WIPE

  $6601 CONSTANT RRC(1,X)

  : RTCLK PA_ODR 6 ;
  : RTCE  PB_ODR 6 ;
  : RTOUT PB_ODR 7 ;
  : RTIN  PB_IDR 7 ;

NVM

  : RTC.RB ( -- c )
    0 7 FOR
      [ 0 RTCLK ]B!
      [ RTIN ]B?C [ RRC(1,X) , ]
      [ 1 RTCLK ]B!
    NEXT
  ;

  : RTC.WB ( c -- )
    [ 1 PB_DDR 7 ]B!  [ 1 PB_CR1 7 ]B!
    7 FOR
      [ 0 RTCLK ]B!
      [ RRC(1,X) , RTOUT ]BCCM
      [ 1 RTCLK ]B!
    NEXT DROP
    [ 0 PB_DDR 7 ]B!  [ 0 PB_CR1 7 ]B!
  ;

  : RTC.READ ( a -- c )
    [ 1 RTCE ]B!
    2* $81 OR RTC.WB RTC.RB
    [ 0 RTCE ]B!
  ;

  : RTC.WRITE ( c a -- )
    [ 1 RTCE ]B!
    2* $80 OR RTC.WB RTC.WB
    [ 0 RTCE ]B!
  ;

RAM WIPE

\\ Example: 

: decode ( c -- c )
  \ DS1302 uses BCD encoding
  16 /MOD 10 * +
;

: minsec ( -- )
  \ show minutes and seconds, e.g. on 7S-LED display
  0 RTC.READ decode
  1 RTC.READ decode
  100 * + .
;

\ set background task
' minsec BG !
