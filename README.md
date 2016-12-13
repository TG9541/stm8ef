# STM8S eForth (stm8ef)

This is an extended and refactored version of [Dr. C.H. Ting's eForth for the *STM8S Discovery*](http://www.forth.org/svfig/kk/07-2010.html) that turns STM8S *Value Line* µCs boards into an interactive Forth development environment. The [SDCC toolchain](http://sdcc.sourceforge.net/) is used for building the eForth core, which makes mixing Forth, assembly, and C possible.

The binary of an interactive eForth system uses below 4400 bytes, including the overhead from SDCC (C startup code and interrupt table). With a rich feature feature set (*Compile to Flash*, *Background Task*, and *CREATE-DOES>*) the binary size is below 5000 bytes.

Please refer to the [Wiki on GitHub](https://github.com/TG9541/stm8ef/wiki) for more information! 

## Overview

Features:

* compile Forth to NVM (Non Volatile Memory with Flash IAP)
* autostart feature for embedded applications
* preemptive background tasks, e.g. for `INPUT-PROCESS-OUTPUT` proces with fixed cycle time (default 5ms)
* configurable vocabulary subsets for binary size reduction
* Subroutine Threaded Code (STC) with native BRANCH and EXIT
* Extended vocabulary:
  * *CREATE-DOES>* for defining words
  * Loop structure words: DO LEAVE LOOP +LOOP
  * STM8 ADC control: ADC! ADC@
  * board keys, outputs, LEDs: OUT OUT!
  * EEPROM, FLASH lock/unlock: LOCK ULOCK LOCKF ULOCKF
  * native bit set/reset: BSR
  * inverted byte order 16bit register access: 2C@ 2C!
  * compile to Flash memory: NVR RAM RESET
  * autostart applications: 'BOOT
  * ASCII file transfer: FILE HAND
* board support for Chinese made [STM8S based very low cost boards][WG1]:
  * W1209 LED display & half-duplex with SW TX
  * C0135 Relay-4 Board
  * STM8S103F3 "$0.70" breakout board
  * support for [boards with 7Seg-LED UI](https://github.com/TG9541/stm8ef/wiki/eForth-Background-Task): in a background task, `123 .` goes to the 7Seg-LED display, and `?KEY` reads board keys


Canges that required refactoring the original code:

* use of the free SDCC tool chain ("ASxxxx V2.0" syntax, SDCC linker with declaration of ISR routines in `main.c`)
* removal of hard STM8S105C6 dependencies (e.g. RAM layout, UART2)
* flexible RAM layout, meaningful symbols for RAM locations
* conditional code for different target boards with a subdirectory based configuration framework 
* bugfixes (e.g. COMPILE)
* major binary size optimization


## Support for STM8S Value Line µC 

The availability of low-cost boards (e.g. thermostats, power supplies, WIFI modules) makes the *STM8S003F3P6* the main target.

The main differences between STM8S003F3P6 and STM8S105C6T6 (*STM8S Discovery*) are:

* 8 KiB Flash instead of 32 KiB
* 1 KiB RAM instead of 2 KiB
* 128 bytes EEPROM instead of 1 KiB (the STM8S103F3 has 640 bytes) 
* reduced set of GPIO and other peripherals
* UART1 instead of UART2

## Board support:

There is board suport for some easily available "Chinese gadgets". For details, refer to [STM8S-Value-Line-Gadgets][WG1] in the Wiki.

* `BOARD_CORE` STM8S003F3 core, most extra feature words disabled 
* `BOARD_MINDEV` STM8S103F3 low cost "minimum development board"
* `BOARD_W1209` W1209 low cost thermostat with LED display and half-duplex RS232 through sensor header (9600 baud) 
* `BOARD_C0135` C0135 "Relay-4 Board" (can be used as a *Nano PLC*)

Currently, there is no support for the STM8S Discovery, since I don't have any STM8S105C6T6 based boards for testing.

### STM8S003F3 Core

The plain STM8S003F3P6 eForth core as a starting point for configurations

* 16MHz HSI, serial console
* Reduced feature set for minimal memory footprint (less than 4400 bytes)
* Configured for the interactive use case, e.g. hardware testing, or as a debugging console

More features can be selected from the list of options in `globalconf.inc`.

Run `make BOARD=CORE flash` for building and flashing.

### STM8S103F3 "minimum development board"

Cheap STM8S103F3P6-based breakout board with LED on port B5 (there are plenty of vendors on EBay or AliExpress, the price starts below $0.70 incl. shipping)

* Binary size below 5300 bytes 
* Selected feature set:
  * compile to Flash 
  * background task 
  * CREATE-DOES>
  * I/O words
  * special STM8 memory access words (bit addressing, reversed access order) 
  * EEPROM access
  * Case insensitive vocabulary
* Clock source internal 16 MHz RC oscillator `HSI`

Run `make BOARD=MINDEV flash` for building and flashing.

### W1209 Thermostat Module

STM8S003F3P6-based thermostat board with a 3 digit 7S-LED display, relay, and a 10k NTC sensor. 
This very cheap board can be used easily for single input/single output control applications with a basic UI (e.g. timer, counter, dosing, monitoring).

* Binary size about 5600 bytes
* Selected feature set:
  * 7S-LED display and board keys
  * Half-duplex serial interface through sensor header
  * compile to Flash 
  * background task 
  * CREATE-DOES>
  * I/O words
  * EEPROM access
  * Case insensitive vocabulary
* Clock source internal 16 MHz RC oscillator `HSI`

Run `make BOARD=W1209 flash` for building and flashing.

#### Serial console on W1209

Interactive development is possible using half-duplex RS232 communication through the sensor header:

Port D6 (RxD) is on the NTC header. I implemented a half-duplex "multiple access bus" communication interface with an interrupt based
software simulation for TX that causes very little CPU overhead (9600 baud with TIM4).

Prerequists for using eForth on a W1209 interactively:

* remove the capacitor next to header (0.47µF would limit the UART to about 5 character/s) 
* on the terminal side, use wired-or *RXD || TxD* (with open drain, e.g. USB CH340 with 1N4148 in series with TxD) 


Refer to the [wiki](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#w1209).

### Relay Board-4

The board, sometimes labelled C0135 or "Relay Board-4" is a low cost PLC I/O expander with the following features:

* STM8S103F3P6 (640 bytes EEPROM) 
* 4 relays NC/NO rated 250VAC-10A (with red monitoring LEDs) on PB4, PC3, PC4, and PC5 
* 4 unprotected inputs (PC6, PC7, PD2, PD3, 2 usable as 3.3V analog-in), 
* 1 LED on PD4, 
* 1 key on PA3, 
* RS485 (PB5 enable - PD5 TX, PD6 RX on headers)
* 8MHz crystal (or 16 MHz HSI) 

* Binary size below 5300 bytes 
* Selected feature set:
  * compile to Flash 
  * background task 
  * CREATE-DOES>
  * I/O words
  * EEPROM access
  * Case insensitive vocabulary
* Clock source internal 16 MHz RC oscillator `HSI`

Run `make BOARD=C0135 flash` for building and flashing.

## Steps for creating a new board variant

For creating a variant, simply create a copy of the base variant's folder (e.g. CORE). By running `make BOARD=<folderName> flash` it can be compiled, and programmed to the target.

## Disclaimer, copyright

Tl;dr: this is a hobby project! Don't use this code for anything that requires any kind of correctness, support, dependability. Different licenses may apply to the code in this GitHub repository, some of which may require you to make derived work publically available!

Please refer to LICENSE.md for details.

[WG1]: https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets
