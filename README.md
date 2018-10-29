# STM8 eForth (stm8ef)

[![Travis-CI](https://travis-ci.org/TG9541/stm8ef.svg)](https://travis-ci.org/TG9541/stm8ef)

STM8 eForth is an interactive Forth programming system for STM8 µCs with a good feature to binary size ratio. It provides a [binary release](https://github.com/TG9541/stm8ef/releases), a plug-in system for custom board support, a library, and automated testing with uCsim instruction level simulation.

STM8 eForth is based on [Dr. C.H. Ting's eForth for the *STM8S Discovery*](http://www.forth.org/svfig/kk/07-2010.html). With the kind permission of the original author it has a permissive [FOSS license](https://github.com/TG9541/stm8ef/blob/master/LICENSE.md).

[![STM8EF Wiki](https://user-images.githubusercontent.com/5466977/28994765-3267d78c-79d6-11e7-927f-91751cd402db.jpg)](https://github.com/TG9541/stm8ef/wiki)

Forth is a very simple but highly extensible [programming language](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Programming). "Hello World" is as simple as this:

```Forth
: hello ."  Hello World!" ;
```
STM8 eForth is a compiler-interpreter on a µC that interacts through a character interface (e.g. with a serial terminal). With the help of [e4thcom](https://wiki.forth-ev.de/doku.php/en:projects:e4thcom) it can be used as a semi-tethered Forth (an interactive system on the µC with source dependencies resolution on the PC).

The Forth console works with an STM8 UART, a pair of GPIOs, or even any single GPIO and 3-wire or 2-wire communication. Up to two serial interfaces can be used at the same time. Console configuration is possible for any type of [character I/O](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Board-Character-IO) (e.g. keyboard and display), even at runtime!

STM8 eForth is highly configurable: depending on the board a full featured binary requires between 4.7K and 5.5K, a basic interactive Forth fits in about 3.5K. The unique `ALIAS` feature that provides access to headerless Forth words which enables interactive programming even on the smallest available STM8 device (e.g. STM8S003F2 with just 4K Flash memory).

The [Wiki on GitHub](https://github.com/TG9541/stm8ef/wiki) covers various topics, e.g. using [Breakout Boards](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards), or the conversion of low-cost Chinese thermostats, voltmeters, or DC/DC-converters into Forth powered embedded control boards.

## Generic targets

Generic target binaries are provided as examples and for evaluation:

* STM8S Low Density devices (e.g. STM8S003x3, STM8S103x3, STM8S903x3 or STM8S001J3)
  *  [CORE](https://github.com/TG9541/stm8ef/tree/master/CORE), a basic configuration for STM8S Low Density devices, some features are disabled (e.g. no background task)
  * [SWIMCOM](https://github.com/TG9541/stm8ef/tree/master/SWIMCOM), a full feature set, and 2-wire communication through PD1/SWIM (i.e. the ICP pin)
  * [DOUBLECOM](https://github.com/TG9541/stm8ef/tree/master/DOUBLECOM) console through the SWIM interface, the UART can be used, e.g. for background tasks
  * [STM8S001J3](https://github.com/TG9541/stm8ef/tree/master/STM8S001J3) like SWIMCOM but with console through PD5/UART_TX in half-duplex mode (this binary also works on other STM8S Low Density devices)
* [STM8S105K4](https://github.com/TG9541/stm8ef/tree/master/STM8S105K4) for STM8S Medium Density devices (Value Line / Access Line)
* [STM8S207RB](https://github.com/TG9541/stm8ef/tree/master/STM8S207RB) initial support for STM8S High Density devices (Performance Line)
* [STM8L051J3](https://github.com/TG9541/stm8ef/tree/master/STM8L051J3) support for STM8L Low Density devices (see [issue](https://github.com/TG9541/stm8ef/issues/137#issuecomment-354542670))
* [STM8L-DISCOVERY](https://github.com/TG9541/stm8ef/tree/master/STM8L-DISCOVERY) support for STM8L Medium Density devices

Various STM8 Discovery boards and [breakout boards](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards) for Low-, Medium-, and High-Density devices can be used. Initial support for STM8L Medium Density devices is available.

## Board support:

TG9541/STM8EF provides board support for several common "Chinese gadgets" like the following:

* [MINDEV](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards) for the STM8S103F3P6 $0.65 "minimum development board"
* [C0135](https://github.com/TG9541/stm8ef/wiki/Board-C0135) "Relay-4 Board" - it can be used as a *Nano PLC*
* [W1209](https://github.com/TG9541/stm8ef/wiki/Board-W1209) $1.50 thermostat board w/ 3 digit 7S-LED display, full- or half-duplex RS232
* [W1219](https://github.com/TG9541/stm8ef/wiki/Board-W1219) low cost thermostat with 2x3 digit 7S-LED display, half-duplex RS232 through PD1/SWIM
* [W1401](https://github.com/TG9541/stm8ef/wiki/Board-W1401) (also XH-W1401) thermostat with 3x2 digit 7S-LED display, half-duplex RS232 through SWIM
* [DCDC](https://github.com/TG9541/stm8ef/wiki/Board-CN2596) hacked DCDC converter with voltmeter
* [XH-M194](https://github.com/TG9541/stm8ef/wiki/Board-XH-M194) Timer board with 6 relays, RTC with clock display, and 6 keys
* [XY-PWM](https://github.com/TG9541/stm8ef/wiki/XY-PWM) PWM board w/ 3 digit 7S-LED display, 3 keys, dual PWM and full-duplex RS232
* [XY-LPWM](https://github.com/TG9541/stm8ef/wiki/Board-XY-LPWM) PWM board w/ 2x4 digit 7S-LCD display, 4 keys, PWM and full-duplex RS232

The Wiki lists other supported "[Value Line Gadgets][WG1]", e.g. [voltmeters & power supplies](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#voltmeters-and-power-supplies), [breakout boards](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards), and [thermostats](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#thermostats).

# Feature Overview

Even though the binaries are very small, STM8 eForth offers many features:

* Subroutine Threaded Code (STC) with improved code density
  * native `BRANCH` (JP), and `EXIT` (RET)
  * relative CALL with two bytes for the latest Forth words
  * pseudo-opcode for DOLIT with TRAP implements literals in 3 instead of 5 bytes
  * [ALIAS words](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Alias-Words) for indirect dictionary entries ([even in EEPROM!](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Alias-Words#dictionary-with-alias-words-in-the-eeprom))
* compile Forth to NVM (Non Volatile Memory) with IAP
  * Words `NVM` and `RAM` switch between volatile (RAM) and non volatile (NVM) modes (*REMEMBER execute `RAM` before a power recycle or executing `COLD` if you want the words added to NVM to be available in future terminal sessions*)
  * RAM allocation for `VARIABLE` and `ALLOT` is transparent in NVM mode (basic RAM management)
  * autostart feature for embedded applications
* Low-level interrupts in Forth
  * lightweight context switch with `SAVEC` and `IRET`
  * example code for HALT is in the [Wiki](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Interrupts)
* preemptive background tasks with a fixed cycle time
  * configurable cycle (default: 5ms)
  * `INPUT-PROCESS-OUTPUT` task indepent of the Forth console
  * robust and fast context switch with a "clean stack" approach
  * concurrent interactive Forth console, e.g. for setting control process parameters
  * in background tasks `?KEY` reads board keys, and [boards with 7Seg-LED UI](https://github.com/TG9541/stm8ef/wiki/eForth-Background-Task) can simply `EMIT` to the LED display
* cooperative multitasking with `'IDLE`
  * code can be executed in an idle task while the console waits for user input
* configuration options for serial console or dual serial interface
  * UART: `?RX` and `TX!`
  * any GPIO or pair of GPIOs from ports PA through PD can be used as a simulated COM port
  * GPIO w/ Port edge & Timer4 interrupts: `?RXP .. TXP!`
  * half-duplex "bus style" communication using simulated COM port or UART
  * option for `TX! .. ?RX` on simulated COM port, and `?RXP .. TXP!` on UART
* configurable vocabulary subsets for binary size optimization
  * configuration possible down to the level of single words
  * export of `ALIAS` definitions for unlinked words
* Extended vocabulary:
  * `CREATE ... DOES>` for defining *defining words*
  * Vectored I/O: `'KEY?` and `'EMIT`
  * Loop structure words: `DO .. LEAVE .. LOOP`, `+LOOP`
  * STM8S ADC control: `ADC!`, `ADC@`
  * board keys, outputs, LEDs: `BKEY`, `KEYB?`, `EMIT7S`, `OUT`, `OUT!`
  * EEPROM, FLASH lock/unlock: `LOCK`, `ULOCK`, `LOCKF`, `ULOCKF`
  * native bit set/reset: `B!` (b a u -- ), `[ .. ]B!`
  * native 16bit STM8 timer register access: `2C@`, `2C!`
  * compile to Flash memory: `NVR`, `RAM`, `WIPE`, `RESET`
  * autostart applications: `'BOOT`
  * `EVALUATE` for interpreting text strings (even in the idle task!)
  * many words that were missing in eForth compared to Forth systems popular in the 1980s
* board support for [STM8S based very-low-cost boards][WG1]:
  * STM8S103F3P6 "$0.80" breakout board
  * Termostats, e.g. W1209, W1219, or W1401
  * Low cost power supply boards, e.g. XH-M188, DCDC w/ voltmeter
  * C0135 Relay Board
  * configuration folders for easy application to new boards

## Other changes to the original STM8EF code:

* "ASxxxx V2.0" syntax (the free [SDCC tool chain](http://sdcc.sourceforge.net/) allows mixing Forth, assembly, and C)
* hard STM8S105C6 dependencies removed (e.g. RAM layout, UART2)
* flexible RAM layout, basic RAM memory management, meaningful symbols for RAM locations
* conditional code for different target boards with a subdirectory based configuration framework
* serious bugs fixed (e.g. `COMPILE`, `DEPTH`, `R!`)
* significant binary size reduction

# Disclaimer, copyright

TL;DR: This is a hobby project! Don't use the code if support, correctness, or dependability are required. Additional licenses might apply to the code which may require derived work to be made public!

Please refer to LICENSE.md for details.

[WG1]: https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets
