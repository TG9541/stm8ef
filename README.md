# STM8S eForth (stm8ef)

Port of Dr. C.H. Ting's eForth for the *STM8S Discovery* to STM8S *Value Line* devices like *STM8S003F3*, and to the SDCC toolchain.

Most of the changes are related to providing "board support" for STM8S based low-cost Chinese made "gadgets", but there is also some basic support for background operations

Changes and code refactoring:

* SDCC tool chain "ASxxxx V2.0" syntax
* conditional code for different target devices
* 1K RAM layout, symbols for RAM loc. ROM size opt.
* STM8S105C6 dependencies removed (e.g. UART2)
* some bugfixes (e.g. SEE)

New features:

* simple *concurrent* background operation with 5 ms timebase (using TIM2)
* words for device keys, outputs, leds
* words for EEPROM, bit operations, inv. order 16bit acc.

Board/module support:

* W1209 LED display & half-duplex with software TX (9600 baud using TIM4) 
* C0125 Relay-4 Board (as a *Nano PLC*)
* "75ct" cheap STM8S103F3 breakout board

Please refer to the [Wiki on GitHub](https://github.com/TG9541/stm8ef/wiki) for more information! 

## STM8S003F3/STM8S103F3 µC devices

The availability of low-cost modules (e.g. thermostats, power supplies, WIFI modules) makes *STM8S003F3* the main target.

Some of the differences between STM8S003F3, and the STM8S105C6T6 (*STM8S Discovery*) are:

* UART1 instead of UART2
* 8 KiB Flash instead of 32 KiB
* 1 KiB RAM instead of 2 KiB
* 128 bytes EEPROM (STM8S103F3 bytes) instead of 1 KiB
* reduced set of GPIO and other peripherals 

## Value Line modules 

There is board suport for some easily available modules. For details, refer to [STM8S-Value-Line-Gadgets](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets) in the Wiki.

### STM8S103F3 Breakout

Cheap STM8S103F3-based breakout board with LED on port B5 (there are plenty of vendors on EBay or AliExpress, the price starts at about $0.75 incl. shipping)

* clock source internal 16 MHz RC oscillator `HSI` (instead of 16 MHz crystal)
* LED on GPIO PB5
* reset key

Set option `MODULE_MINIMAL = 1` in `forth.asm`

### W1209 Thermostat Module

Low-cost STM8S003F3-based thermostat module with a 3 digit 7S-LED display, relay, and a 10k NTC sensor. 

Set option `MODULE_W1209 = 1` in `forth.asm`.

#### Note:

Port D6 (RxD) is on the NTC header, and communication is possible with a half-duplex "multiple access bus". 
The board support code implements SW simulation for TX using the same pin (9600 baud with TIM4).

Prerequists for using eForth on a W1209 interactively:

* remove the capacitor next to header (0.47µF is way too much for the UART) 
* on the terminal side, use wired-or *RXD || TxD*  /w open drain (e.g. USB CH340 with 1N4148 in series with TxD) 

Please refer to the [wiki](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#w1209).

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

The code is currently assumed broken (I don't have any device for testing it).

