# STM8 eForth (stm8ef)

[![Travis-CI](https://travis-ci.org/TG9541/stm8ef.svg)](https://travis-ci.org/TG9541/stm8ef)

STM8 eForth is a very compact interactive Forth system for STM8 µCs. It provides a [binary release](https://github.com/TG9541/stm8ef/releases), a library, a plug-in system for board support and automated tests with uCsim. Core features include simple multitasking with interactive parameter setting and autostart-operation.

It runs on an STM8 µC as a compiler-interpreter and interacts with the user through a console (e.g. using [e4thcom](https://wiki.forth-ev.de/doku.php/en:projects:e4thcom) or a serial terminal).

[![STM8EF Wiki](https://user-images.githubusercontent.com/5466977/28994765-3267d78c-79d6-11e7-927f-91751cd402db.jpg)](https://github.com/TG9541/stm8ef/wiki)

STM8 eForth is based on [Dr. C.H. Ting's eForth for the *STM8S Discovery*](http://www.forth.org/svfig/kk/07-2010.html). With the kind permission of the original author it has a permissive [FOSS license](https://github.com/TG9541/stm8ef/blob/master/LICENSE.md).

Forth is a simple but highly extensible [programming language](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Programming). "Hello World" is as simple as this:

```Forth
: hello ."  Hello World!" ;
```

STM8 eForth is configurable: a full featured binary needs between 4.7K and 5.5K, a basic interactive Forth fits in just 3.5K. The unique `ALIAS` feature provides access to headerless Forth words enables interactive programming even on the smallest available STM8 device (e.g. STM8S003F2 with 4K Flash memory).

The Forth console works with an STM8 UART, a pair of GPIOs, or even any single GPIO and 3-wire or 2-wire communication. Up to two UARTs and a simulated serial interface are supported. The console can be configured for any type of [character I/O](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Board-Character-IO)  (e.g. keyboard and display), even at runtime!


The [Wiki on GitHub](https://github.com/TG9541/stm8ef/wiki) covers various topics, e.g. using [Breakout Boards](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards), or the conversion of low-cost Chinese thermostats, voltmeters, or DC/DC-converters into Forth powered embedded control boards.

## Generic targets

Generic target binaries are provided as examples and for evaluation:

* STM8S Low Density devices (e.g. STM8S003x3, STM8S103x3, STM8S903x3 or STM8S001J3)
  *  [CORE](https://github.com/TG9541/stm8ef/tree/master/CORE), a basic configuration for STM8S Low Density devices, some features are disabled (e.g. no background task)
  * [SWIMCOM](https://github.com/TG9541/stm8ef/tree/master/SWIMCOM), a full feature set, and 2-wire communication through PD1/SWIM (i.e. the ICP pin)
  * [DOUBLECOM](https://github.com/TG9541/stm8ef/tree/master/DOUBLECOM) console through the SWIM interface, UART I/O words are provided for applications
  * [STM8S001J3](https://github.com/TG9541/stm8ef/tree/master/STM8S001J3) like SWIMCOM but with console through PD5/UART_TX in half-duplex mode (this binary is compatible with all STM8S Low Density devices)
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

In addition to basic eForth, STM8 eForth offers many features:

* Subroutine Threaded Code (STC) with improved code density
  * native `BRANCH` (JP), and `EXIT` (RET)
  * relative CALL where possible (2 instead of 3 bytes)
  * TRAP as pseudo-opcode for literals (3 instead of 5 bytes)
  * [ALIAS words](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Alias-Words) for indirect dictionary entries ([even in EEPROM!](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Alias-Words#dictionary-with-alias-words-in-the-eeprom))
* compile Forth to NVM (Non Volatile Memory) with IAP (In Application Programming)
  * Words `NVM` and `RAM` switch between volatile (RAM) and non volatile (NVM) modes (*REMEMBER execute `RAM` after `NVM` if you want your new words to be available after power-cycle or `COLD`*)
  * RAM allocation for `VARIABLE` and `ALLOT` is transparent in NVM mode (basic RAM management)
  * autostart feature for embedded applications
* Low-level interrupts in Forth
  * lightweight context switch with `SAVEC` and `IRET`
  * example code for HALT is in the [Wiki](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Interrupts)
* preemptive background tasks `BG`
  * `INPUT-PROCESS-OUTPUT` task indepent of the Forth console
  * fixed cycle time (configurable, default: 5ms)
  * [on supported boards](https://github.com/TG9541/stm8ef/wiki/eForth-Background-Task) `?KEY` reads board keys, `EMIT` uses board display
  * robust context switch with "clean stack" approach
* cooperative multitasking with `'IDLE`
  * [idle task](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Idle-Task) execution while there is no console input
  * very fast idle loop (< 10µs)
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
  * native bit set/reset: `B!` (b a u -- ), `[ .. ]B!` (and more)
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
* hard STM8S105C6 dependencies removed (e.g. initialization, clock, RAM layout, UART2)
* flexible RAM layout, basic RAM memory management, meaningful symbols for RAM locations
* conditional code for different target boards with a subdirectory based configuration framework
* original code bugs fixed (e.g. `COMPILE`, `DEPTH`, `R!`, `PICK`)
* significant binary size reduction

# Disclaimer, copyright

This is a hobby project! Don't use the code if support or correctness are required.

Additional licenses might apply to the code which might require derived work to be made public! Please refer to LICENSE.md for details.

[WG1]: https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets
