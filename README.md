# STM8S eForth (stm8ef)

TG9541/STM8EF is an extends [Dr. C.H. Ting's eForth for the *STM8S Discovery*](http://www.forth.org/svfig/kk/07-2010.html). It aims to be a very lightweight embedded "untethered" (self-hosted) Forth system for low-end STM8 µCs with a maximum "feature-to-binary-size" ratio. It provides a plug-in system for board support, base dictionary configuration, a Forth include file infrastructure, and uCsim based binary level simulation. With the kind permission of the original author, TG9541/STM8EF has a perimissive [FOSS license](https://github.com/TG9541/stm8ef/blob/master/LICENSE.md).

The [Wiki on GitHub](https://github.com/TG9541/stm8ef/wiki) provides information on various topics, e.g. how to use Chinese thermostats, voltmeters, or DC/DC-converters, as Forth powered embedded control boards!

[![STM8EF Wiki](https://user-images.githubusercontent.com/5466977/28994765-3267d78c-79d6-11e7-927f-91751cd402db.jpg)](https://github.com/TG9541/stm8ef/wiki)

This project has the following goals:

1. provide an easy to use [Forth kit](https://github.com/TG9541/stm8ef/wiki/STM8S-eForth-Programming) for STM8 µCs
2. offer board support for [common low-cost Chinese control boards](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets)
3. maximize the product *features* * *free space* for low-end STM8 *Value Line* µCs (see below)
4. learn to know the Forth community, and work on the development environment, libraries, and applications

TG9541/STM8EF can be configured for a range of Forth features and different STM8S devices: a full featured binary requires 4.7KiB, a basic interactive Forth fits in 3.5KiB, and building small non-interactive binaries is possible. 

The interactive Forth console can use any GPIO, a pair of GPIOs, or the STM8 UART, for 2-wire or 3-wire communication. Up to two serial interfaces can be configured.

## Generic targets

For a quick start, binaries for generic targets (e.g. breadboards) are provided:

* `CORE` a starting point for new boards - some advanced features were disabled (e.g. no background task)
* `SWIMCOM` communication through the SWIM interface for board exploration - full feature set
* [STM8S105K4](https://github.com/TG9541/stm8ef/tree/master/STM8S105K4), a starting point for STM8S Medium Density devices (Value Line / Access Line)
* `STM8S001J3M3` is a Low-Densisty STM8S in a SO8N package - the Forth console uses the STM8 UART half-duplex mode

Various STM8S Discovery boards and [breakout boards](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards) for Value- and Access-Line devices can be used. Support for STM8S High Density, and STM8L Medium Density devices is under consideration.

## Board support:

TG9541/STM8EF provides board support for several common "Chinese gadgets", like the following:

* [MINDEV](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards) for the STM8S103F3P6 $0.60 "minimum development board"
* [W1209](https://github.com/TG9541/stm8ef/wiki/Board-W1209) $1.50 thermostat board w/ 3 digit 7S-LED display, full- or half-duplex RS232
* [W1219](https://github.com/TG9541/stm8ef/wiki/Board-W1219) low cost thermostat with 2x3 digit 7S-LED display, half-duplex RS232 through PD1/SWIM
* [W1401](https://github.com/TG9541/stm8ef/wiki/Board-W1401) (also XH-W1401) thermostat with 3x2 digit 7S-LED display, half-duplex RS232 through SWIM
* [C0135](https://github.com/TG9541/stm8ef/wiki/Board-C0135) "Relay-4 Board" (can be used as a *Nano PLC*)
* [DCDC](https://github.com/TG9541/stm8ef/wiki/Board-CN2596) hacked DCDC converter with voltmeter

The Wiki lists other supported "[Value Line Gadgets](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets)", e.g. [voltmeters & power supplies](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#voltmeters-and-power-supplies), [breakout boards](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards), and [thermostats](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#thermostats).

## 2-Wire Communication

The Forth console can be configured to use 3-wire interfaces in full-duplex, or 2-wire interface in half-duplex mode. For boards without access to STM8S UART pins, a generic STM8EF binary is provided, that performs 2-wire communication through PD1 on the SWIM ICP header. 

The following simple wired-or interface can be used:

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
Please note that some PC serial interfaces require matching logic levels (e.g. a low drop diode, or buffers).

## Steps for creating a new board variant

For creating a variant, copy and rename a base variant folder (e.g. CORE). Running `make BOARD=<folderName> flash` builds the code, and transfers it to the target. 

When working with 3rd party boards, it's recommended to have at least two boards for reverse engineering: one in original state, and one for testing new code. If you believe to have identified a target board of general interest, please [open a ticket here](https://github.com/TG9541/stm8ef/issues), or contact the STM8EF [Hackaday.io project](https://hackaday.io/project/16097-eforth-for-cheap-stm8s-value-line-gadgets)!

In any case, please keep the following in mind:

* when working with unknown boards make sure to have at least a basic understanding of the schematics and workings of the board! The author(s) of this software can't help you reverse-engineering an unsupported board. Working knowledge of electronics engineering is required!
* the original ROM contents of most boards is read-protected and can't be read, and once erased the original function can't be restored (your board will be useless unless you write your own code)!
* if your target board is designed to supply or control connected devices (e.g. a power supply unit) it's recommended not to assume fail-safe properties of the board (e.g. the output voltage of a power supply board might rise to the maximum without the proper software). Disconnect any connected equipment, and if possible only supply the µC with a current limiting power supply!

Other than that, have fun, and consider sharing your results!

# Feature Overview

* Subroutine Threaded Code (STC) with improved code density
  * native BRANCH (JP), and EXIT (RET)
  * relative CALL with two bytes where possible
  * pseudo-opcode for DOLIT using TRAP: compiled literals 3 instead of 5 bytes
  * [ALIAS words](https://github.com/TG9541/stm8ef/wiki/STM8S-eForth-Alias-Words) for indirect dictionary entries
* compile Forth to NVM (Non Volatile Memory with Flash IAP)
  * Words `NVM` and `RAM` switch between volatile (RAM) and non volatile (NVM) modes
  * RAM allocation for `VARIABLE` and `ALLOT` fully transparent in NVM mode
  * autostart feature for embedded applications
* Low-level interrupts in Forth
  * lightweight context switch with `SAVEC` and `IRET`
  * example code for HALT is in the [Wiki](https://github.com/TG9541/stm8ef/wiki/STM8S-eForth-Programming#low-level-interrupts-in-forth)
* preemptive background tasks with fixed cycle time
  * configurable cycle (default: 5ms)
  * `INPUT-PROCESS-OUTPUT` processing indepent from the Forth console
  * robust and fast context switch with a "clean stack" approach
  * concurrent interactive console, e.g. for setting control process parameters
  * in background tasks `?KEY` can read board keys, and [boards with 7Seg-LED UI](https://github.com/TG9541/stm8ef/wiki/eForth-Background-Task) can simply output to the LED display
* configuration options for serial console or dual serial interface
  * UART: ?RX TX!
  * any GPIO or pair of GPIOs from ports PA through PD can be used as a simulated COM port
  * GPIO w/ Port edge & Timer4 interrupts: ?RXP TXP!
  * half-duplex "bus style" communication using a single GPIO (e.g. PD1/SWIM), or UART half-duplex mode
* board support for Chinese made [STM8S based very low cost boards][WG1]:
  * STM8S103F3 "$0.60" breakout board
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
  * 16bit STM8 timer register access: 2C@ 2C!
  * compile to Flash memory: NVR RAM RESET
  * autostart applications: 'BOOT
  * ASCII file transfer: FILE HAND
* configurable vocabulary subsets for binary size optimization

# Other changes compared to the original STM8EF code:

* "ASxxxx V2.0" syntax (the free [SDCC tool chain](http://sdcc.sourceforge.net/) allows mixing Forth, assembly, and C)
* hard STM8S105C6 dependencies removed (e.g. RAM layout, UART2)
* flexible RAM layout, basic RAM memory management, meaningful symbols for RAM locations
* conditional code for different target boards with a subdirectory based configuration framework
* bugs fixed (e.g. COMPILE, DEPTH, R!)
* rather significant binary size reduction

# Disclaimer, copyright

TL;DR: This is a hobby project! Don't use the code if support, correctness, or dependability are required. Also note that additional licenses might apply to the code which might require derived work to be made public!

Please refer to LICENSE.md for details.

[WG1]: https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets
