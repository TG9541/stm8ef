# STM8 eForth (stm8ef)

[![Travis-CI](https://travis-ci.org/TG9541/stm8ef.svg)](https://travis-ci.org/TG9541/stm8ef)

STM8 eForth is an interactive Forth system for very low-cost STM8 µCs. The Forth console has the look and feel of an operating system shell: the interpreter-compiler and multi-tasking features allow interactive control of peripherals, parameter tuning or even changing running code - which is rather unusual for a $0.20 "computer".

STM8 eForth is a much extended version of [Dr. C.H. Ting's eForth for the *STM8S Discovery*](http://www.forth.org/svfig/kk/07-2010.html). With the kind permission of the original author this version has a permissive [FOSS license](https://github.com/TG9541/stm8ef/blob/master/LICENSE.md). Core features include compiling Forth code to Flash memory, autostart operation and interrupt handling.

The [release](https://github.com/TG9541/stm8ef/releases) provides binaries, a library, STM8 register definitions and [modular board support](https://github.com/TG9541/stm8ef-modular-build). Travis-CI takes care of [automated testing in the uCsim STM8S simulator](https://travis-ci.org/TG9541/stm8ef) (this is also possible in "downstream projects" for creating ready-to-run binaries).

[![STM8EF Wiki](https://user-images.githubusercontent.com/5466977/28994765-3267d78c-79d6-11e7-927f-91751cd402db.jpg)](https://github.com/TG9541/stm8ef/wiki)

The programming language Forth works by defining new words out of existing words. "Hello World" in Forth is as simple as this:

```Forth
: hello ."  Hello World!" ;
```

Forth is very well suited for embedded programming. Find out more in the [STM8 eForth Walk-Through](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Programming).

STM8 eForth is configurable: a full core binary needs between short of 4K and 5.5K Flash memory, a minimal system fits in just 3.5K. Using headerless Forth words is possible with the unique `ALIAS` feature. Running it on the smallest STM8 device is possible (STM8S103F2 with 4K ROM) while a $0.50 32K Flash device (e.g. STM8S005C6T6) provides much room for applications.

The Forth console uses the STM8 U(S)ART or a simulated serial interface: 3-wire or 2-wire communication with a UART or a simulated serial interface are supported. [e4thcom](https://wiki.forth-ev.de/doku.php/en:projects:e4thcom) is recommended but any common serial terminal will work. The console can be configured at runtime to use other types of [character I/O](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Board-Character-IO), e.g. keyboard and display.

The [Wiki on GitHub](https://github.com/TG9541/stm8ef/wiki) covers various topics, e.g. using [Breakout Boards](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards) or the conversion of low-cost Chinese thermostats, voltmeters, or DC/DC-converters into Forth powered embedded control boards.

## Generic targets

Generic target binaries are provided as for use or for evaluation:

* STM8S Low Density devices (e.g. STM8S003x3, STM8S103x3, STM8S903x3 or STM8S001J3)
  *  [CORE](https://github.com/TG9541/stm8ef/tree/master/CORE), a basic configuration for STM8S Low Density devices, some features are disabled (no background task, `DO .. LOOP` or `CREATE .. DOES>`). Also, the dictionary search is case-sensitive.
  * [SWIMCOM](https://github.com/TG9541/stm8ef/tree/master/SWIMCOM) procides 2-wire communication through PD1/SWIM (i.e. the ICP pin) and a full feature set (the similar [DOUBLECOM](https://github.com/TG9541/stm8ef/tree/master/DOUBLECOM) also provides UART I/O words for applications)
  * [STM8S001J3](https://github.com/TG9541/stm8ef/tree/master/STM8S001J3) like SWIMCOM but with the 2-wire console through UART_TX (PA3 or PD5) - the binary supports STM8S001J3 / STM8S903K3 UART remapping and is compatible with all STM8S Low Density devices
* [STM8S105K4](https://github.com/TG9541/stm8ef/tree/master/STM8S105K4) for STM8S Medium Density devices (Value or Access Line) with 2K RAM and up to 32K Flash
* [STM8S207RB](https://github.com/TG9541/stm8ef/tree/master/STM8S207RB) for STM8S High Density devices (Value or Performance Line) with 6K RAM and up to 32K + 96K Flash
* [STM8L051F3](https://github.com/TG9541/stm8ef/tree/master/STM8L051F3) for STM8L Low Density devices (see [issue](https://github.com/TG9541/stm8ef/issues/137#issuecomment-354542670))
* [STM8L-DISCOVERY](https://github.com/TG9541/stm8ef/tree/master/STM8L-DISCOVERY) for STM8L Medium Density devices like STM8L152C6

Various STM8 Discovery boards and [breakout boards](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards) for Low-, Medium-, and High-Density devices can be used. STM8L devices are supported but there is currently no support for STM8L101F3 or STM8L001J3.

## Board support:

TG9541/STM8EF provides board support, e.g. LED display code, for several common "Chinese gadgets" like the following:

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

From STM8 eForth 2.2.24 on, the binary release contains all files necessary for building STM8 eForth, e.g. for a custom target board. The [modular build](https://github.com/TG9541/stm8ef-modular-build) repository provides instructions and all required files. Examples are [W1209](https://github.com/TG9541/W1209), [STM8 eForth MODBUS](https://github.com/TG9541/stm8ef-modbus), [STM8L051LED](https://github.com/TG9541/stm8l051led) or [XY-LPWM](https://github.com/TG9541/XY-LPWM).

# STM8 eForth Feature Overview

In addition to the original "stm8ef" this STM8 eForth offers many features:

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
  * `'IDLE` task code can run the interpreter with `EVALUATE`
* configuration options for serial console or dual serial interface
  * UART: `?RX` and `TX!` full-duplex w/ half-duplex option on STM8 Low Density devices
  * GPIO w/ Port edge & Timer4 interrupts: `?RXP .. TXP!`
  * half-duplex "bus style" communication using simulated COM port or UART
  * any GPIO or pair of GPIOs from ports PA through PD can be used as a simulated COM port
  * option for `TX! .. ?RX` on simulated COM port, and `?RXP .. TXP!` on UART
* configurable vocabulary subsets for binary size optimization
  * board dependent configuration possible down to the level of single words
  * `ALIAS` definitions for any unlinked words, also in the [EEPROM](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Alias-Words#alias-words-in-the-eeprom)
* Extended vocabulary:
  * `CONSTANT` (missing in the original code)
  * `'KEY?` and `'EMIT` for I/O redirection (originally hard-coded)
  * `CREATE .. DOES>` for *defining words* (few eForth variants have it)
  * `DO .. LEAVE .. LOOP`, `+LOOP` (for better compatibility with generic Forth)
  * STM8S ADC control: `ADC!`, `ADC@`
  * board keys, outputs, LEDs: `BKEY`, `KEYB?`, `EMIT7S`, `OUT`, `OUT!`
  * EEPROM, FLASH lock/unlock: `LOCK`, `ULOCK`, `LOCKF`, `ULOCKF`
  * bit access and native bit set/reset: `B!` (b a u -- ), `[ .. ]B!` (and more)
  * bitfield for little- and big-endian: `BF!`, `BF@`, `LEBF!`, `LEBF@`
  * native 16bit STM8 timer register access: `2C@`, `2C!`
  * far memory access: `FC!`, `FC@`
  * native memory set: `[ .. ]C!`
  * compile to Flash memory: `NVR`, `RAM`, `WIPE`, `RESET` and `PERSIST`
  * autostart applications: `'BOOT`
  * `EVALUATE` can run the Forth interpreter on text strings (even compilation is possible!)
  * many words from Forth systems that were popular in the 1980s are provided in the library

## Other changes to the original STM8EF code:

The code has little ressemblance with the original code. Porting back features should be possible anyway.

* "ASxxxx V2.0" syntax (the free [SDCC tool chain](http://sdcc.sourceforge.net/) allows mixing Forth, assembly, and C)
* hard STM8S105C6 dependencies were removed (e.g. initialization, clock, RAM layout, UART2)
* flexible RAM layout, basic RAM memory management, meaningful symbols for RAM locations
* conditional code for different target boards with a subdirectory based configuration framework
* original code bugs fixed (e.g. `COMPILE`, `DEPTH`, `R!`, `PICK`)
* significant binary size reduction

# Disclaimer, copyright

This is a hobby project! Don't use the code if support or correctness are required.

The license is MIT. Please refer to LICENSE.md for details.

[WG1]: https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets
