#STM8L051F3P6 Base Image

By default, the USART interface for the STM8L051F3 is configured to support the LSE clock feature (which requires a 32768Hz crystal to be connected to PC5/PC6).

![stm8l051f3p6_](https://user-images.githubusercontent.com/5466977/40583511-8462f470-6190-11e8-8674-84338a991f58.png)

Should a different USART setting be required the configuration can be changed in `boardcore.inc`, or in start-up Forth code, e.g.:

```
\res MCU: STM8L051
\res export SYSCFG_RMPCR1 PA_DDR PA_CR1 PC_DDR PC_CR1
#require ]B!
#require ]C!

: init ( -- )  \  assign STM8L051 USART to PC5:TX, PC6:RX
   [ 0 PA_DDR 2 ]B!
   [ 0 PA_CR1 2 ]B!
   [ 1 PC_DDR 5 ]B!
   [ 1 PC_CR1 5 ]B!
   [ $0C SYSCFG_RMPCR1 ]C!
   ;
```
