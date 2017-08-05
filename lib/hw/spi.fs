\ STM8S103 SPI
\ derived from al177/stm8ef/HC12/boardcore.inc
\ refer to github.com/TG9541/stm8ef/blob/master/LICENSE.md

\ Example:
\   SPIon
\   $AA SPI .
\   SPIoff

#require RAMmark
RAMmark
#include regs_spi.fs

NVM

\ Init and enable SPI 
: SPIon ( -- )
  $14 SPI_CR1 C!  \ master, CLK/8, CPOL=CPHA=0, MSB first
  $01 SPI_CR2 C!  \ no NSS, FD, no CRC
  $54 SPI_CR1 C!  \ enable SPI 
;

\ disable SPI 
: SPIoff ( -- )
  0 SPI_CR1 C!    \ disable SPI
;

\ Perform SPI byte cycle with result c
: SPI ( c -- c)
  [ $E601 , $C752 ,          \ LD A,(1,X)  LD SPI_DR,A
    $0472 , $0352 , $03FB ,  \ BTJF SPI_SR,#1,SPITXE_WAIT
    $7201 , $5203 , $FBC6 ,  \ BTJF SPI_SR,#0,SPIRXNE_WAIT
    $5204 , $E701 , ]        \ LD A,SPI_DR  LD (1,X),A
;

RAMdrop
