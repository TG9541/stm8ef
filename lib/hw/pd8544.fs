\ STM8S103 PD8544 "Nokia 3110 LCD"
\ refer to github.com/TG9541/stm8ef/blob/master/LICENSE.md

#require hw/spi.fs
#include pd8544ctrl.fs

NVM
\ send c through SPI, discard input
: LCDout ( c -- )
  0 LCDdis
  SPI 
  1 LCDdis
  drop
;

\ set horizontal cursor to c ( 0..83 )
: LCDx ( c -- )
  0 LCDdat
  $80 + LCDout
  1 LCDdat
;

\ set vertical cursor to c ( 0..5 )
: LCDy ( c -- )
  0 LCDdat
  $40 + LCDout
  1 LCDdat
;
 
\ set cursor to (0,0)
: LCDhome ( -- )
  0 LCDx 0 LCDy
;

\ fill LCD with pattern c (use y auto increment)
: LCDfill ( c -- )
  LCDhome 
  503 for 
    dup LCDout 
  next drop 
;

\ init ports, SPI, PD8544 with Vop c (0..127) 
: LCDinit ( c -- )
  PD8544ctrl
  SPIon
  0 LCDdat
  $21 LCDout \ instructions extended
  $14 LCDout \ bias 4
  $80 + LCDout \ Vop, e.g. 60
  $20 LCDout \ instructions normal
  $0C LCDout \ display conf ($08:blank,$09:on,$0C:normal,$0D:inv)
  1 LCDdat
  0 LCDfill
;

\ copy n chars starting at a to PD8544
: LCDcpy ( a n -- )
  for dup C@ LCDout 1+ next drop 
;

RAM

