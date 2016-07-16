# stm8ef
Port of Dr. C.H. Ting's eForth for the `STM8S Discovery` to STM8S *Value Line* devices like STM8S003F3, and to the SDCC toolchain.

I refactored the code to make initialization more modular, added some useful low level words, and fixed some bugs (e.g. the SEE "decompiler"). 
Most of the changes are related to providing "board support" for STM8S based low-cost "gadgets".

Please check [Wiki on GitHub](https://github.com/TG9541/stm8ef/wiki) for documentation! 

## STM8S003/STM8S103 devices

The STM8S003iF3 is the main target due to the easy availability of low-cost modules (e.g. thermostats, power supplies, WIFI modules). 

The main differences of the STM8S103F3 to the STM8S105C6T6 in the *STM8S Discovery* are:

* clock source internal 16 MHz RC oscillator `HSI` (instead of 16 MHz crystal) 
* the only RS232 is on UART1 (instead of UART2)
* 1 KiB RAM (instead of 2 KiB)
* 8 KiB Flash (instead of 32 KiB)
* different set of available GPIO


### STM8S103F3 Breakout

Cheap STM8S103F3-based breakout board with LED on port B5 (you'll find plenty of vendors on ebay or aliexpress)

### W1209 Thermostat Module

Cheap STM8S003F3-based thermostat module with 3 dig. 7S-LED display, relay, and 10k NTC sensor. 

Port D6 (RxD) is on the NTC header, communication is possible with a half-duplex "multiple access bus". 
TxD works through SW simulation using the same pin with the help of TIM4.

Instructions for using eForth on a W1209:

* remove the capacitor next to header: 0.47µF is way too much for the UART, I'll experiment with lower values (e.g. a few nF)
* on the terminal side, use wired-or *RXD || TxD*  /w open drain (e.g. USB CH340 with 1N4148 in series with TxD) 
* Set options `HALF_DUPLEX = 1`, and `GADGET_W1209 = 1` in `forth.asm`

## STM8S Discovery

Assumed broken (I don't have any device for testing it).
