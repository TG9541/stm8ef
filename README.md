# stm8ef
Port of Dr. C.H. Ting's eForth for the STM8S Discovery to STM8S *Value Line* devices (and to the SDCC toolchain).

Please check [Wiki on GitHub](https://github.com/TG9541/stm8ef/wiki) for documentation! 

## STM8S003/STM8S103 devices


Main differences to *STM8S Discovery*:

* Clock source internal 16 MHz RC oscillator `HSI` (instead of 16 MHz crystal) 
* RS232 is on UART1 (instead of UART2)
* 1 KiB RAM (instead of 2 KiB)


### STM8S103F3 Breakout

Cheap STM8S103F3-based breakout board with LED on port B5 

### W1209 Thermostat Module

Cheap STM8S003F3-based thermostat module with 3 dig. 7S-LED display, relay, and 10k NTC sensor. 

Port D6 (RxD) is on the NTC header, communication is possible with a half-duplex "multiple access bus". 
TxD works through SW simulation using the same pin with the help of TIM4.

Instructions for using eForth on a W1209:

* remove the capacitor next to header
* on the terminal side, use wired-or *RXD || TxD*  /w open drain (e.g. USB CH340 with 1N4148 in series with TxD) 
* Set options `HALF_DUPLEX = 1`, and `GADGET_W1209 = 1` in `forth.asm`

## STM8S Discovery

Currently broken (I have no way to test it).
