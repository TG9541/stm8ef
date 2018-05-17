\ STM8L SPI

\ Init SPI and enable in master mode.
: SPIon ( baud -- )
    [ 1 PB_CR1 5 ]B! \ SPI1_CLK Push-pull/Pull-up
    [ 1 PB_CR1 6 ]B! \ SPI1_MOSI Push-pull/Pull-up
    [ 1 PB_CR1 7 ]B! \ SPI1_MISO Push-pull/Pull-up
    [ 1 CLK_PCKENR1 4 ]B! \ Enable SPI clock
    $07 AND
    2* 2* 2* \ 3 left shift
    SPI1_CR1 C! \ Write baud rate
    [ %00000011 SPI1_CR2 ]C! \ SSM, SSI. Internal slave nSS as master. 
    [ 1 SPI1_CR1 2 ]B! \ Master mode
    [ 1 SPI1_CR1 6 ]B! \ SPI enable
;

\ Disable SPI.
: SPIoff ( -- )
    [ 0 SPI1_CR1 ]C!    \ disable SPI
;

\ Perform SPI byte cycle with result c
: SPI ( c -- c)
  [ $E601 ,                  \ LD A,(1,X)
    $C7  C, SPI1_DR ,        \ LD SPI_DR,A
    $7203 , SPI1_SR , $FB C, \ BTJF SPI_SR,#SPITXE_WAIT (1)
    $7201 , SPI1_SR , $FB C, \ BTJF SPI_SR,#SPIRXNE_WAIT (0)
    $C6  C, SPI1_DR ,        \ LD A,SPI_DR
    $E701 , ]                \ LD (1,X),A
;

\\ Example:

\res MCU: STM8L051

\res export CLK_PCKENR1

\res export SPI1_CR1
\res export SPI1_CR2
\res export SPI1_ICR
\res export SPI1_SR
\res export SPI1_DR

\res export PB_ODR
\res export PB_DDR
\res export PB_CR1

#require ]C!
#require ]B!

#include hw/spi8l.fs

%111 SPIon \ Fsysclk/256

165 SPI . CR

SPIoff


