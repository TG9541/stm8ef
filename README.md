# STM8S eForth (stm8ef)

TG9541/STM8EF is an extends [Dr. C.H. Ting's eForth for the *STM8S Discovery*](http://www.forth.org/svfig/kk/07-2010.html). It aims to be a very lightweight embedded "untethered" Forth system for low-end STM8 µCs with a maximum "feature-to-binary-size" ratio. TG9541/STM8EF is published as Free Open Source Software ([license](https://github.com/TG9541/stm8ef/blob/master/LICENSE.md)) with the kind permission of the original author.

![4th_640](https://user-images.githubusercontent.com/5466977/28994765-3267d78c-79d6-11e7-927f-91751cd402db.jpg)

The project has the following goals:

1. provide an easy to use [Forth kit](https://github.com/TG9541/stm8ef/wiki/STM8S-eForth-Programming) for STM8 µCs
2. board support for [common low-cost Chinese control boards](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets)
3. maximize the product *features* * *free space* for low-end STM8 *Value Line* µCs (see below)
4. create a development environment, libraries, and encourage community support

Please refer to the [Wiki on GitHub](https://github.com/TG9541/stm8ef/wiki) for more information!

# Board support:

TG9541/STM8EF provides board support for several common "Chinese gadgets", and for generic targets:

* [W1209](https://github.com/TG9541/stm8ef/wiki/Board-W1209) low-cost thermostat w/ 3 digit 7S-LED display, full- or half-duplex RS232
* [W1219](https://github.com/TG9541/stm8ef/wiki/Board-W1219) low cost thermostat with 2x3 digit 7S-LED display, half-duplex RS232 through PD1/SWIM
* [W1401](https://github.com/TG9541/stm8ef/wiki/Board-W1401) (also XH-W1401) thermostat with 3x2 digit 7S-LED display, half-duplex RS232 through SWIM
* [C0135](https://github.com/TG9541/stm8ef/wiki/Board-C0135) "Relay-4 Board" (can be used as a *Nano PLC*)
* [DCDC](https://github.com/TG9541/stm8ef/wiki/Board-CN2596) hacked DCDC converter with voltmeter
* [MINDEV](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards)` STM8S103F3 low cost "minimum development board"
* `CORE` starting point for new boards, most extra feature words disabled
* `SWIMCOM` communication through the SWIM interface for board exploration

Please refer to [STM8S-Value-Line-Gadgets][WG1] in the Wiki. Binaries for the listed targets are in the [Releases](https://github.com/TG9541/stm8ef/releases) section.

There is limited support for the STM8S Discovery, and for Access Line devices with 2KiB RAM (tested on a STM8S105K4T6 breakout board).

## W1209 Thermostat Module

STM8S003F3P6-based thermostat board with a 3 digit 7S-LED display, a relay, and a 10k NTC sensor.
This very cheap board can be used for single input/single output control applications with a basic UI (e.g. timer, counter, dosing, monitoring).

Please refer to the [wiki](https://github.com/TG9541/stm8ef/wiki/Board-W1209) for more informatiom.

* Binary size below 5500 bytes
* Selected feature set:
  * Full-duplex serial interface through key pins (variant W1209-FD)
  * Half-duplex serial interface through the sensor header (variant W1209)
  * 7S-LED display and board keys (P7S E7S BKEY KEYB?)
  * EEPROM access
  * background task
  * eForth extensions *CREATE-DOES>*, *DO-LEAVE-LOOP/+LOOP*
  * I/O words
  * bit addressing
  * case-insensitive vocabulary

Run `make BOARD=W1209-FD flash` or `make BOARD=W1209 flash` for building and flashing.

## 1401 Thermostat Module

STM8S003F3P6-based thermostat board with 3x2 digit 7S-LED display, relay, LED, buzzer, 4 keys, and a 10k NTC sensor.
A cheap board that, like the W1209, can be used for single input/single output control applications with a basic UI (e.g. timer, counter, dosing, monitoring).

Please refer to the [wiki](https://github.com/TG9541/stm8ef/wiki/Board-W1401) for more informatiom.

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

## STM8S103F3 "minimum development board"

Cheap STM8S103F3P6-based breakout board with LED on port B5 (there are plenty of vendors on EBay or AliExpress, the price starts below $0.70 incl. shipping).

Please refer to the [wiki](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards) for more informatiom.

* Selected features (superset of CORE):
  * EEPROM access
  * background task
  * eForth extensions *CREATE-DOES>*, *DO-LEAVE-LOOP/+LOOP*
  * I/O words, bit access
  * bit addressing
  * case-insensitive vocabulary
* Binary size below 5000 bytes

Run `make BOARD=MINDEV flash` for building and flashing.

## Other Supported Gadgets

The Wiki lists other supported "[Value Line Gadgets](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets)", e.g. [voltmeters & power supplies](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#voltmeters-and-power-supplies), [breakout boards](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards), and [thermostats](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#thermostats).

## STM8S003F3 Core

A plain STM8S003F3P6 eForth core with a lean scripting oriented vocabulary (words like AHEAD or [COMPILE] not linked), and a minimal memory footprint (less than 4KiB Flash). CORE can be used as-is or as a starting point for new configurations.

* Selected features:
  * 16MHz HSI
  * compile to Flash
  * lightweight low-level interrupt handlers in Forth code
  * serial console with UART
* Binary size below 4096 bytes

More features can be selected from the list of options in `globalconf.inc`.

Run `make BOARD=CORE flash` for building and flashing.

## STM8S003F3 "Communication through PD1/SWIM"

This is a generic STM8EF target for exploring boards where no UART pins are broken out but where PD1 is available on a SWIM ICP header. Access to PD5/TX and PD6/RX is not required, bus-style half-duplex console communciation with a software UART simulation is used instead.

* Selected features (superset of CORE):
  * any port pin can be configured for half-duplex RS232 (standard: PD1/SWIM)
  * EEPROM access
  * background task
  * eForth extensions *CREATE-DOES>*, *DO-LEAVE-LOOP/+LOOP*
  * bit addressing
  * case-insensitive vocabulary
* Binary size below 5100 bytes

For serial communication the following simple wired-or interface can be used:

```

STM8 device    .      .----o serial TxD "TTL"
               .      |      (e.g. "CH340 USB serial converter")
               .     ---
               .     / \  1N4148
               .     ---
               .      |
STM8 PD1/SWIM-->>-----*----o serial RxD "TTL
               .
GND------------>>----------o serial GND
               .
................
```

Run `make BOARD=SWIMCOM flash` for building and flashing.

## Steps for creating a new board variant

For creating a variant, copy and rename a base variant folder (e.g. CORE). By running `make BOARD=<folderName> flash` will be compiled and programmed to the target. Other STM8 variants can be supported by a putting a matching `stm8device.inc` file into the board folder.

It's advisable to have at least two boards for reverse engineering: one in original state, and one for testing new code. Please [open a ticket here](https://github.com/TG9541/stm8ef/issues), or contact the STM8EF [Hackaday.io project](https://hackaday.io/project/16097-eforth-for-cheap-stm8s-value-line-gadgets) before you start working on a new board!

**Warning**:  the original ROM contents of most boards is read-protected and can't be read, and once erased the original function can't be restored (your board will be useless unless you write your own code).

**Warning**: if your target board is designed to supply or control connected devices (e.g. a power supply unit) it's recommended not to assume fail-safe properties of the board (e.g. the output voltage of a power supply board might rise to the maximum without the proper software). Disconnect any connected equipment, and if possible only supply the µC with a current limiting power supply!

**Warning**: when working with unknown boards make sure to have at least a basic understanding of the schematics and workings of the board! The author(s) of this software can't help you reverse-engineering an unsupported board. Working knowledge of electronics engineering is assumed.

# Feature Overview

* Subroutine Threaded Code (STC) with improved code density
  * native BRANCH (JP), and EXIT (RET)
  * relative CALL with two bytes where possible
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
  * STM8S103F3 "$0.65" breakout board
  * Termostats, e.g. W1209, W1219, or W1401
  * Low cost power supply boards, e.g. XH-M188, DCDC w/ voltmeter
  * C0135 Relay Board
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

# Support for STM8S Value Line and Access Line

The availability of low-cost boards (e.g. thermostats, power supplies, WIFI modules) makes the *STM8S003F3P6* the main target.

Differences between STM8S003F3P6 and STM8S105C6T6 (*STM8S Discovery*) are:

* 8 KiB Flash instead of 32 KiB
* 1 KiB RAM instead of 2 KiB
* 128 bytes EEPROM instead of 1 KiB (the STM8S103F3 has 640 bytes)
* reduced set of GPIO and other peripherals
* UART1 instead of UART2

Other changes to the original code:

* use of the free SDCC tool chain ("ASxxxx V2.0" syntax, SDCC linker with declaration of ISR routines in `main.c`)
* the [SDCC toolchain](http://sdcc.sourceforge.net/) allows mixing Forth, assembly, and C
* removal of hard STM8S105C6 dependencies (e.g. RAM layout, UART2)
* flexible RAM layout, meaningful symbols for RAM locations
* conditional code for different target boards with a subdirectory based configuration framework
* bug fixes (e.g. COMPILE, DEPTH, R!)
* significant binary size reduction

# Disclaimer, copyright

TL;DR: This is a hobby project! Don't use the code for any application that requires support, correctness, or dependability. Please note that different licenses may apply to the code, some of which might require that derived work is to be made public!

Please refer to LICENSE.md for details.

[WG1]: https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets
