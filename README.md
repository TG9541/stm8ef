# STM8 eForth (stm8ef)

[![Travis-CI](https://travis-ci.org/TG9541/stm8ef.svg)](https://travis-ci.org/TG9541/stm8ef)

STM8 eForth is a Forth system for very low-cost STM8 µCs. Interacting with the Forth interpreter-compiler (the REPL) feels like using an operating system on a much larger machine, e.g. simple multi-tasking features allow running embedded control code in the background while tuning parameters (or change the code!) in the foreground.

STM8 eForth is based on [Dr. C.H. Ting's eForth for the *STM8S Discovery*](http://www.forth.org/svfig/kk/07-2010.html). With the kind permission of the original author it has a permissive [FOSS license](https://github.com/TG9541/stm8ef/blob/master/LICENSE.md).

The [release](https://github.com/TG9541/stm8ef/releases) provides binaries, a library, STM8 register definitions and [modular board support](https://github.com/TG9541/stm8ef-modular-build). Core features include compiling Forth to Flash memory, autostart-operation and everything needed for creating a custom Forth core. The STM8 eForth release automatically runs a [self-test in the uCsim STM8S simulator](https://travis-ci.org/TG9541/stm8ef) with Travis-CI, and it's easy to use this feature for creating ready-to-run binaries (including Forth code) through a simple `git push`.

[![STM8EF Wiki](https://user-images.githubusercontent.com/5466977/28994765-3267d78c-79d6-11e7-927f-91751cd402db.jpg)](https://github.com/TG9541/stm8ef/wiki)

Forth is a simple but highly extensible [programming language](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Programming). "Hello World" is as simple as this:

```Forth
: hello ."  Hello World!" ;
```

STM8 eForth is configurable: a full featured binary needs between 4.0K and 5.5K and a minimal interactive system fits in just 3.5K. The unique `ALIAS` feature provides convenient access to headerless Forth words which improves code economy. Working with the tiniest STM8 device with 4K Flash (STM8S103F2) is possible and a 32K Flash device (e.g. STM8S105C6T6C) provides ample room for applications!

The Forth console works with an STM8 UART, or with a simulated serial interface: 3-wire or 2-wire communication with up to two UARTs and a simulated serial interface are supported. It works best with [e4thcom](https://wiki.forth-ev.de/doku.php/en:projects:e4thcom) but any serial terminal can be used. The console can be configured at runtime to use any type of [character I/O](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Board-Character-IO), e.g. keyboard and display!

The [Wiki on GitHub](https://github.com/TG9541/stm8ef/wiki) covers various topics, e.g. using [Breakout Boards](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards), or the conversion of low-cost Chinese thermostats, voltmeters, or DC/DC-converters into Forth powered embedded control boards.

## Generic targets

Generic target binaries are provided as examples and for evaluation:

* STM8S Low Density devices (e.g. STM8S003x3, STM8S103x3, STM8S903x3 or STM8S001J3)
  *  [CORE](https://github.com/TG9541/stm8ef/tree/master/CORE), a basic configuration for STM8S Low Density devices, some features are disabled (e.g. no background task)
  * [SWIMCOM](https://github.com/TG9541/stm8ef/tree/master/SWIMCOM), a full feature set, and 2-wire communication through PD1/SWIM (i.e. the ICP pin)
  * [DOUBLECOM](https://github.com/TG9541/stm8ef/tree/master/DOUBLECOM) console through the SWIM interface, UART I/O words are provided for applications
  * [STM8S001J3](https://github.com/TG9541/stm8ef/tree/master/STM8S001J3) like SWIMCOM but with console through UART_TX (PA3 or PD5) in half-duplex mode (this binary supports STM8S001J3 / STM8S903K3 UART remapping but it's compatible with all STM8S Low Density devices)
* [STM8S105K4](https://github.com/TG9541/stm8ef/tree/master/STM8S105K4) for STM8S Medium Density devices (Value Line / Access Line) with 2K RAM and up to 32K Flash
* [STM8S207RB](https://github.com/TG9541/stm8ef/tree/master/STM8S207RB) support for STM8S High Density devices (Performance Line) with 6K RAM and up to 32K + 96K Flash
* [STM8L051J3](https://github.com/TG9541/stm8ef/tree/master/STM8L051J3) support for STM8L Low Density devices (see [issue](https://github.com/TG9541/stm8ef/issues/137#issuecomment-354542670))
* [STM8L-DISCOVERY](https://github.com/TG9541/stm8ef/tree/master/STM8L-DISCOVERY) support for STM8L Medium Density devices

Various STM8 Discovery boards and [breakout boards](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards) for Low-, Medium-, and High-Density devices can be used. Initial support for STM8L Medium Density devices is available.

## Board support:

TG9541/STM8EF provides board support for several common "Chinese gadgets" like the following:

* [MINDEV](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards) for the STM8S103F3P6 $0.80 "minimum development board"
* [C0135](https://github.com/TG9541/stm8ef/wiki/Board-C0135) the "Relay-4 Board" can be used as a *Nano PLC* (Forth MODBUS support is available)
* [W1209](https://github.com/TG9541/stm8ef/wiki/Board-W1209) $1.50 thermostat board w/ 3 digit 7S-LED display, full- or half-duplex RS232 (some board variants, e.g. with CA LED displays, are supported)
* [W1219](https://github.com/TG9541/stm8ef/wiki/Board-W1219) low cost thermostat with 2x3 digit 7S-LED display with half-duplex RS232 through PD1/SWIM
* [W1401](https://github.com/TG9541/stm8ef/wiki/Board-W1401) (also XH-W1401) thermostat with 3x2 digit 7S-LED display with half-duplex RS232 through shared PD1/SWIM
* [DCDC](https://github.com/TG9541/stm8ef/wiki/Board-CN2596) hacked DCDC converter with voltmeter
* [XH-M194](https://github.com/TG9541/stm8ef/wiki/Board-XH-M194) Timer board with STM8S105K4T6C, 6 relays, RTC with clock display, 6 keys with half-duplex RS232 through PD1/SWIM
* [XY-PWM](https://github.com/TG9541/stm8ef/wiki/XY-PWM) PWM board w/ 3 digit 7S-LED display, 3 keys, dual PWM and full-duplex RS232
* [XY-LPWM](https://github.com/TG9541/stm8ef/wiki/Board-XY-LPWM) PWM board w/ 2x4 digit 7S-LCD display, 4 keys, PWM and full-duplex RS232

The Wiki lists other supported "[Value Line Gadgets][WG1]", e.g. [voltmeters & power supplies](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#voltmeters-and-power-supplies), [breakout boards](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards), and [thermostats](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#thermostats).

## Other target boards

From STM8 eForth 2.2.24 on, the binary release contains all the files that are necessary for supporting a custom target board. For example, [STM8 eForth MODBUS](https://github.com/TG9541/stm8ef-modbus) uses the release files to combine target support with the application.

# Feature Overview

In addition to the initial code STM8 eForth offers many features:

* Subroutine Threaded Code (STC) with improved code density that rivals DTC
  * native `BRANCH` (JP), and `EXIT` (RET)
  * relative CALL when possible (2 instead of 3 bytes)
  * TRAP as pseudo-opcode for literals (3 instead of 5 bytes)
  * [ALIAS words](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Alias-Words) for indirect dictionary entries ([even in EEPROM!](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Alias-Words#dictionary-with-alias-words-in-the-eeprom))
  * Forth - machine-code interface using STM8 registers
* compile Forth to NVM (Non Volatile Memory) with IAP (In Application Programming)
  * Words `NVM` and `RAM` switch between volatile (RAM) and non volatile (NVM) modes (*execute `RAM` after `NVM` if you want your new words to be available after power-cycle or `COLD`*)
  * autostart feature for embedded applications
  * RAM allocation for `VARIABLE` and `ALLOT` in NVM mode (basic RAM management)
* Low-level interrupts in Forth
  * lightweight context switch with `SAVEC` and `IRET`
  * example code for HALT is in the [Wiki](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Interrupts)
* preemptive background tasks `BG`
  * `INPUT-PROCESS-OUTPUT` task indepent of the Forth console
  * fixed cycle time (configurable, default: 5ms)
  * [on supported boards](https://github.com/TG9541/stm8ef/wiki/eForth-Background-Task) `?KEY` reads board keys, `EMIT` uses board display
  * robust context switch with "clean stack" approach
* cooperative multitasking with `'IDLE`
  * [idle task](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Idle-Task) execution while there is no console input with < 10µs cycle time
  * code in the `'IDLE` task can use the interpreter with `EVALUATE`
* configuration options for serial console or dual serial interface
  * UART: `?RX` and `TX!` full-duplex w/ half-duplex option on STM8 Low Density devices
  * GPIO w/ Port edge & Timer4 interrupts: `?RXP .. TXP!`
  * half-duplex "bus style" communication using simulated COM port or UART
  * any GPIO or pair of GPIOs from ports PA through PD can be used as a simulated COM port
  * option for `TX! .. ?RX` on simulated COM port, and `?RXP .. TXP!` on UART
* configurable vocabulary subsets for binary size optimization
  * board dependent configuration possible down to the level of single words
  * export of `ALIAS` definitions for any unlinked words
* Extended vocabulary:
  * `CONSTANT` (yes, that was missing in the original code)
  * `'KEY?` and `'EMIT` for I/O redirection (that was missing, too)
  * `CREATE ... DOES>` for *defining words* (few eForth variants have it)
  * `DO .. LEAVE .. LOOP`, `+LOOP` for better compatibility with generic Forth
  * STM8S ADC control: `ADC!`, `ADC@`
  * board keys, outputs, LEDs: `BKEY`, `KEYB?`, `EMIT7S`, `OUT`, `OUT!`
  * EEPROM, FLASH lock/unlock: `LOCK`, `ULOCK`, `LOCKF`, `ULOCKF`
  * native bit set/reset: `B!` (b a u -- ), `[ .. ]B!` (and more)
  * native 16bit STM8 timer register access: `2C@`, `2C!`
  * compile to Flash memory: `NVR`, `RAM`, `WIPE`, `RESET` and `PERSIST`
  * autostart applications: `'BOOT`
  * `EVALUATE` can run the Forth interpreter on text strings (even compilation is possible!)
  * many words from Forth systems that were popular in the 1980s are provided in the library

## Other changes to the original STM8EF code:

* "ASxxxx V2.0" syntax (the free [SDCC tool chain](http://sdcc.sourceforge.net/) allows mixing Forth, assembly, and C)
* hard STM8S105C6 dependencies were removed (e.g. initialization, clock, RAM layout, UART2)
* flexible RAM layout, basic RAM memory management, meaningful symbols for RAM locations
* conditional code for different target boards with a subdirectory based configuration framework
* original code bugs fixed (e.g. `COMPILE`, `DEPTH`, `R!`, `PICK`)
* significant binary size reduction
* many more

# Disclaimer, copyright

This is a hobby project! Don't use the code if support or correctness are required.

The license is MIT. Please refer to LICENSE.md for details.

[WG1]: https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets
