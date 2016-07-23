# stm8ef
Port of Dr. C.H. Ting's eForth for the `STM8S Discovery` to STM8S *Value Line* devices like STM8S003F3, and to the SDCC toolchain.

The code was refactored to make initialization more modular, some useful low level words were added, and some bugs were fixed (e.g. the SEE "decompiler"). 
Most of the changes are related to providing "board support" for STM8S based low-cost Chinese made "gadgets".

Please check [Wiki on GitHub](https://github.com/TG9541/stm8ef/wiki) for documentation! 

## STM8S003F3/STM8S103F3 devices

The STM8S003F3 is the main target due to the easy availability of low-cost modules (e.g. thermostats, power supplies, WIFI modules).

The main differences of the STM8S003F3 to the STM8S105C6T6 in the *STM8S Discovery* are:

* the only RS232 is on UART1 (instead of UART2)
* 8 KiB Flash (instead of 32 KiB)
* 1 KiB RAM (instead of 2 KiB)
* 128 bytes EEPROM (640 on STM8S103F3)
* reduced set of GPIO and other peripherals 

### STM8S103F3 Breakout

Cheap STM8S103F3-based breakout board with LED on port B5 (there are plenty of vendors on ebay or aliexpress, the price span is from about $0.75)

* clock source internal 16 MHz RC oscillator `HSI` (instead of 16 MHz crystal) 

Set option `MODULE_MINIMAL = 1` in `forth.asm`

### W1209 Thermostat Module

Cheap STM8S003F3-based thermostat module with 3 dig. 7S-LED display, relay, and 10k NTC sensor. 

Port D6 (RxD) is on the NTC header, communication is possible with a half-duplex "multiple access bus". 
TxD works through SW simulation using the same pin with the help of TIM4.

Instructions for using eForth on a W1209:

* clock source internal 16 MHz RC oscillator `HSI` (instead of 16 MHz crystal) 
* remove the capacitor next to header: 0.47µF is way too much for the UART, I'll experiment with lower values (e.g. a few nF)
* on the terminal side, use wired-or *RXD || TxD*  /w open drain (e.g. USB CH340 with 1N4148 in series with TxD) 

Set option `MODULE_W1209 = 1` in `forth.asm`

### Relay Board-4

Low cost STM8S103F3 based PLC I/O expander board with the following features:

* 4 relays NC/NO rated 250VAC-10A (with red monitoring LEDs) on PB4, PC3, PC4, and PC5 
* 4 unprotected inputs (PC6, PC7, PD2, PD3, 2 usable as 3.3V analog-in), 
* 1 LED on PD4, 
* 1 key on PA3, 
* RS485 (PB5 enable - PD5 TX, PD6 RX on headers)
* 8MHz crystal (16 MHz HSI can be used instead) 

Set option `MODULE_RELAY = 1` in `forth.asm`

## STM8S Discovery

The code is assumed broken (I don't have any device for testing it).
