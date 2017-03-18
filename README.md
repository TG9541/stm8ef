# STM8S eForth (stm8ef)

TG9541/STM8EF is an extended version of [Dr. C.H. Ting's eForth for the *STM8S Discovery*](http://www.forth.org/svfig/kk/07-2010.html). It aims to be a very lightweight embedded "untethered" Forth system for low-end STM8 µCs with a maximum "feature-to-binary-size" ratio. TG9541/STM8EF is published as Free Open Source Software ([license](https://github.com/TG9541/stm8ef/blob/master/LICENSE.md)) with the kind permission of the original author.

The project has the following goals:

1. provide an easy to use [Forth kit](https://github.com/TG9541/stm8ef/wiki/STM8S-eForth-Programming) for STM8 µCs
2. provide board support for a variety of [common low-cost Chinese control boards](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets)
3. maximize the product *features* * *free space* for low-end STM8 *Value Line* µCs (see below)


The binary size of a basic interactive Forth is below 3700 bytes, and a self-contained programming kit with a rich feature set (e.g. *Compile to Flash*, *Background Task*, *DO-LEAVE-LOOP/+LOOP*, *CREATE-DOES>*, native bit set) uses less than 5000 bytes.

Please refer to the [Wiki on GitHub](https://github.com/TG9541/stm8ef/wiki) for more information!

## Overview

Features:

* Subroutine Threaded Code (STC) with improved code density
  * native BRANCH (JP), and EXIT (RET)
  * relative CALL with two bytes where possiblet
  * pseudo-opcode for DOLIT using TRAP: compiled literals 3 instead of 5 bytes
* compile Forth to NVM (Non Volatile Memory with Flash IAP)
  * Words `NVM` and `RAM` switch between volatile (RAM) and non volatile (NVM) modes
  * RAM allocation for `VARIABLE` and `ALLOT` fully transparent in NVM mode
  * autostart feature for embedded applications
* Low-level interrupts in Forth
  * lightweight context switch with `SAVEC` and `IRET`
  * example code for HALT is in the [Wiki](https://github.com/TG9541/stm8ef/wiki/STM8S-eForth-Programming#low-level-interrupts-in-forth)
* preemptive background tasks with fixed cycle time (default 5ms)
  * robust and fast context switch with "clean stack" approach
  * allows `INPUT-PROCESS-OUTPUT` processing indepent from the Forth console
  * allows setting process parameters through interactive console
  * in background tasks `?KEY` can read board keys, and [boards with 7Seg-LED UI](https://github.com/TG9541/stm8ef/wiki/eForth-Background-Task) can simply output to the LED display
* configuration options for serial console or dual serial interface
  * UART: ?RX TX!
  * any GPIO or pair of GPIOs from ports PA through PD can be used as a simulated COM port
  * GPIO w/ Port edge & Timer4 interrupts: ?RXP TXP!
  * half-duplex "bus style" communication with a single GPIO (e.g. PD1/SWIM)
* board support for Chinese made [STM8S based very low cost boards][WG1]:
  * STM8S103F3 "$0.70" breakout board
  * Termostats, e.g. W1209, W1401
  * Low cost power supply boards, e.g. XH-M188, DCDC w/ voltmeter
  * C0135 Relay-4 Board
  * configuration folders for easy application to other boards
* Extended vocabulary:
  * `CREATE ... DOES>` for defining *defining words*
  * Vectored I/O: 'KEY? 'EMIT
  * Loop structure words: DO LEAVE LOOP +LOOP
  * STM8 ADC control: ADC! ADC@
  * board keys, outputs, LEDs: BKEY KEYB? EMIT7S OUT OUT!
  * EEPROM, FLASH lock/unlock: LOCK ULOCK LOCKF ULOCKF
  * native bit set/reset: B! (b a u -- )
  * 16bit register access with reversed byte order (e.g. timer registers): 2C@ 2C!
  * compile to Flash memory: NVR RAM RESET
  * autostart applications: 'BOOT
  * ASCII file transfer: FILE HAND
* configurable vocabulary subsets for binary size optimization

Other changes to the original code:

* use of the free SDCC tool chain ("ASxxxx V2.0" syntax, SDCC linker with declaration of ISR routines in `main.c`)
* the [SDCC toolchain](http://sdcc.sourceforge.net/) allows mixing Forth, assembly, and C
* removal of hard STM8S105C6 dependencies (e.g. RAM layout, UART2)
* flexible RAM layout, meaningful symbols for RAM locations
* conditional code for different target boards with a subdirectory based configuration framework
* bug fixes (e.g. COMPILE, DEPTH, R!)
* significant binary size reduction

## Support for STM8S Value Line µC

The availability of low-cost boards (e.g. thermostats, power supplies, WIFI modules) makes the *STM8S003F3P6* the main target.

Differences between STM8S003F3P6 and STM8S105C6T6 (*STM8S Discovery*) are:

* 8 KiB Flash instead of 32 KiB
* 1 KiB RAM instead of 2 KiB
* 128 bytes EEPROM instead of 1 KiB (the STM8S103F3 has 640 bytes)
* reduced set of GPIO and other peripherals
* UART1 instead of UART2

## Board support:

TG9541/STM8EF provides board support for several common "Chinese gadgets":

* `CORE` starting point for new boards, most extra feature words disabled
* `SWIMCOM` communication through the SWIM interface for board exploration
* `MINDEV` STM8S103F3 low cost "minimum development board"
* `W1209` (also XH-W1209) low cost thermostat with 3 digit 7S-LED display and half-duplex RS232 through sensor header
* `W1401` (also XH-W1401) thermostat with 3x2 digit 7S-LED display
* `C0135` C0135 "Relay-4 Board" (can be used as a *Nano PLC*)

Refer to [STM8S-Value-Line-Gadgets][WG1] in the Wiki. Binaries for the listed targets are in the *Releases* section.

Currently, there is no support for the STM8S Discovery, since I don't have STM8S105C6T6 based boards for testing.

### STM8S003F3 Core

A plain STM8S003F3P6 eForth core with a lean scripting oriented vocabulary (words like AHEAD or [COMPILE] not linked), and a minimal memory footprint (less than 4KiB Flash). CORE can be used as-is or as a starting point for new configurations.

* Selected features:
  * 16MHz HSI
  * compile to Flash
  * lightweight low-level interrupt handlers in Forth code
  * serial console with UART
* Binary size below 4096 bytes

More features can be selected from the list of options in `globalconf.inc`.

Run `make BOARD=CORE flash` for building and flashing.

### STM8S003F3 "Communication through PD1/SWIM"

This is a generic STM8EF target for exploring boards where no UART pins are broken out but where PD1 is available on a SWIM ICP header. Access to PD5/TX and PD6/RX is not required, bus-style half-duplex console communciation with a software UART simulation is used instead.

* Selected features (superset of CORE):
  * rich set of words for register addresses (e.g. Px_CR2 Px_CR1 Px_DDR Px_IDR Px_ODR)
  * EEPROM access
  * background task
  * eForth extensions *CREATE-DOES>*, *DO-LEAVE-LOOP/+LOOP*
  * bit addressing
  * case-insensitive vocabulary
* Binary size below 6600 bytes

For serial communication the following simple wired-or interface can be used:

```

STM8 device    .      .----o serial TxD "TTL"
               .      |      (e.g. "CH340 USB serial converter")
               .     ---
               .     / \  1N4148
               .     ---
ICP header     .      |
               .      *----o serial RxD "TTL
               .      |
STM8 PD1/SWIM-->>-----*----o ST-LINK SWIM
               .
NRST----------->>----------o ST-LINK NRST
               .
GND------------>>-----*----o ST-LINK GND
               .      |
................      .----o serial GND
```

It's advisable to have at least two boards for reverse engineering: one in original state, and one for testing new code. Please [open a ticket here](https://github.com/TG9541/stm8ef/issues), or contact the STM8EF [Hackaday.io project](https://hackaday.io/project/16097-eforth-for-cheap-stm8s-value-line-gadgets) before you start working on a new board!

**Warning**:  the original ROM contents of most boards is read-protected and can't be read, and once erased the original function can't be restored (your board will be useless unless you write your own code).

**Warning**: if your target board is designed to supply or control connected devices (e.g. a power supply unit) it's recommended not to assume fail-safe properties of the board (e.g. the output voltage of a power supply board might rise to the maximum without the proper software). Disconnect any connected equipment, and if possible only supply the µC with a current limiting power supply!

**Warning**: when working with unknown boards make sure to have at least a basic understanding of the schematics and workings of the board! The author(s) of this software can't help you reverse-engineering an unsupported board. Working knowledge of electronics engineering is assumed.

Run `make BOARD=SWIMCOM flash` for building and flashing.

### STM8S103F3 "minimum development board"

Cheap STM8S103F3P6-based breakout board with LED on port B5 (there are plenty of vendors on EBay or AliExpress, the price starts below $0.70 incl. shipping).

* Selected features (superset of CORE):
  * EEPROM access
  * background task
  * eForth extensions *CREATE-DOES>*, *DO-LEAVE-LOOP/+LOOP*
  * I/O words, bit access
  * bit addressing
  * case-insensitive vocabulary
* Binary size below 5000 bytes

Run `make BOARD=MINDEV flash` for building and flashing.

### W1209 Thermostat Module

STM8S003F3P6-based thermostat board with a 3 digit 7S-LED display, a relay, and a 10k NTC sensor.
This very cheap board can be used for single input/single output control applications with a basic UI (e.g. timer, counter, dosing, monitoring).

* Binary size below 5500 bytes
* Selected feature set:
  * Half-duplex serial interface through sensor header
  * 7S-LED display and board keys (P7S E7S BKEY KEYB?)
  * EEPROM access
  * background task
  * eForth extensions *CREATE-DOES>*, *DO-LEAVE-LOOP/+LOOP*
  * I/O words
  * bit addressing
  * case-insensitive vocabulary
* Binary size below 5500 bytes

Run `make BOARD=W1209 flash` for building and flashing.

#### Serial console on W1209

Interactive development is possible using the sensor header as a half-duplex "bus style" serial interface with an interrupt basedUART simulation that causes very little CPU overhead (9600 baud with TIM4).

Prerequists for using eForth on a W1209 interactively:

* remove the capacitor next to header (0.47µF would limit the UART to about 5 character/s)
* on the terminal side, use wired-or *RXD || TxD* (with open drain, e.g. USB CH340 with 1N4148 in series with TxD)

Alternative solution: reconfigure to use PD1/SWIM (shared with 7S-LED segment `A`)

Refer to the [wiki](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#w1209).

### 1401 Thermostat Module

STM8S003F3P6-based thermostat board with 3x2 digit 7S-LED display, relay, LED, buzzer, 4 keys, and a 10k NTC sensor.
A cheap board that, like the W1209, can be used for single input/single output control applications with a basic UI (e.g. timer, counter, dosing, monitoring).

* Binary size below 5600 bytes
* Selected feature set:
  * Half-duplex serial interface through ICP header
  * 7S-LED display and board keys (P7S E7S BKEY KEYB?)
  * EEPROM access
  * background task
  * eForth extensions *CREATE-DOES>*, *DO-LEAVE-LOOP/+LOOP*
  * I/O words
  * bit addressing
  * case-insensitive vocabulary
* Binary size below 5600 bytes

Run `make BOARD=W1401 flash` for building and flashing.

### Relay Board-4

The board, sometimes labelled C0135 or "Relay Board-4" is a low cost PLC I/O expander with the following features:

* Binary size below 5100 bytes
* STM8S103F3P6 (640 bytes EEPROM)
* 4 relays NC/NO rated 250VAC-10A (with red monitoring LEDs) on PB4, PC3, PC4, and PC5
* 4 unprotected inputs (PC6, PC7, PD2, PD3, 2 usable as 3.3V analog-in),
* 1 LED on PD4,
* 1 key on PA3,
* RS485 (PB5 enable - PD5 TX, PD6 RX on headers)
* 8MHz crystal (or 16 MHz HSI)
* Selected feature set like MINDEV, additionally:
  * I/O words for board keys, OUT! for relays and LED
* Clock source internal 16 MHz RC oscillator `HSI`

Run `make BOARD=C0135 flash` for building and flashing.

## Steps for creating a new board variant

For creating a variant, copy and rename a base variant folder (e.g. CORE). By running `make BOARD=<folderName> flash` will be compiled and programmed to the target. Other STM8 variants can be supported by a putting a matching `stm8device.inc` file into the board folder.

## Disclaimer, copyright

TL;DR: This is a hobby project! Don't use the code for any application that requires support, correctness, or dependability. Please note that different licenses may apply to the code, some of which might require that derived work is to be made public!

Please refer to LICENSE.md for details.

[WG1]: https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets
