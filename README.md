# STM8 eForth (stm8ef)

[![Travis-CI](https://travis-ci.org/TG9541/stm8ef.svg)](https://travis-ci.org/TG9541/stm8ef)

STM8 eForth is an interactive Forth system for very low-cost STM8 µCs. The Forth console has the look and feel of an operating system shell. The interpreter-compiler and multi-tasking features allow interactive control of peripherals, parameter tuning or even changing running code, which is rather unusual for a $0.20 "computer".

STM8 eForth is based on [Dr. C.H. Ting's eForth](http://www.forth.org/svfig/kk/07-2010.html) for the STM8S Discovery. With the kind permission of the original author this code is under an [MIT-like license](https://github.com/TG9541/stm8ef/blob/master/LICENSE.md). Most of the code was re-written and new features include compiling Forth code to Flash memory, autostart operation, interrupt handling and many more.

The [binary release](https://github.com/TG9541/stm8ef/releases) provides a full working environment, including the library, target folders, STM8 register definitions and [modular board support](https://github.com/TG9541/stm8ef-modular-build). Travis-CI takes care of automated testing in the [uCsim STM8 simulator](https://travis-ci.org/TG9541/stm8ef) which also makes building ready-to-run binaries in "downstream projects" possible.

[![STM8EF Wiki](https://user-images.githubusercontent.com/5466977/28994765-3267d78c-79d6-11e7-927f-91751cd402db.jpg)](https://github.com/TG9541/stm8ef/wiki)

The programming language Forth is very well suited for embedded control. Forth works by defining new words out of existing words where data simply flows through the stack.

"Hello World" in Forth is as simple as this:

```Forth
: hello ."  Hello World!" ;
```

Find out more in the [STM8 eForth Walk-Through](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Programming).

STM8 eForth is configurable: a minimal system fits in 3.5K which is small enough for µCs with 4K ROM. A full featured core binary requires 4 to 5.5K Flash memory which leaves sufficent space for applications in the cheap 8K device [STM8S003F3P6](https://www.st.com/resource/en/datasheet/stm8s003f3.pdf). For larger applications 32K devices like the [STM8S005C6T6](https://www.st.com/resource/en/datasheet/stm8s005c6.pdf) can be used (a chip with 38 GPIOs for less than $1).

The Forth console uses the STM8 U(S)ART or a simulated serial interface and 3-wire or 2-wire (half-duplex). For interacting and programming [e4thcom](https://wiki.forth-ev.de/doku.php/en:projects:e4thcom) is recommended but any common serial terminal will work. The console can be configured, even at runtime, to use other types of [character I/O](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Board-Character-IO), e.g. keyboard and display.

The [Wiki on GitHub](https://github.com/TG9541/stm8ef/wiki) covers various topics, e.g. converting low-cost Chinese thermostats, voltmeters, or DC/DC-converters into Forth powered embedded control boards.

## Generic targets

The Releases section provides several generic binaries:

Support for STM8S devices [RM0016](https://www.st.com/resource/en/reference_manual/cd00190271-stm8s-series-and-stm8af-series-8-bit-microcontrollers-stmicroelectronics.pdf) is stable. Various STM8 Discovery boards and [breakout boards](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards) for "Low", "Medium", and "High density" devices can be used.

* STM8S "Low density" devices (e.g. STM8S003x3, STM8S103x3, STM8S903x3 or STM8S001J3)
  * [STM8S103F3](https://github.com/TG9541/stm8ef/tree/master/STM8S103F3) this binary is compatible with all STM8S "Low density" devices with 1K RAM, 8K Flash and up to 640 bytes EEPROM like STM8S003F3/K3, STM8S103F3/K3 and STM8S903F3/K3
  * [STM8S001J3](https://github.com/TG9541/stm8ef/tree/master/STM8S001J3) like SWIMCOM but with the 2-wire console through UART_TX (PA3 or PD5) - the binary supports STM8S001J3 / STM8S903K3 UART remapping and is compatible with all STM8S "Low density" devices
  *  [CORE](https://github.com/TG9541/stm8ef/tree/master/CORE), a basic configuration for STM8S "Low density" devices, some features are disabled (no background task, `DO .. LOOP` or `CREATE .. DOES>`). Also, the dictionary search is case-sensitive.
  * [SWIMCOM](https://github.com/TG9541/stm8ef/tree/master/SWIMCOM) procides 2-wire communication through PD1/SWIM (i.e. the ICP pin) and a full feature set (the similar [DOUBLECOM](https://github.com/TG9541/stm8ef/tree/master/DOUBLECOM) also provides UART I/O words for applications)
* STM8S "Medium" and "High density" devices
  * [STM8S105K4](https://github.com/TG9541/stm8ef/tree/master/STM8S105K4) for STM8S "Medium density" devices ("Value" or "Access Line") with 2K RAM and up to 32K Flash
  * [STM8S207RB](https://github.com/TG9541/stm8ef/tree/master/STM8S207RB) for STM8S "High density" devices ("Value" or "Performance Line") with 6K RAM and up to 32K + 96K Flash

Support for STM8L devices is work-in-progress: especially the latest additions STM8L101F3 and STM8L001J3 are experimental, and there have been few tests with STM8L "Medium+" or "High density" devices like STM8L152R8 (although the code can be expected to work).

Please refer to the `README.md` in the board folders below:

* STM8L [RM0013](https://www.st.com/resource/en/reference_manual/CD00184503-.pdf) "Low density" devices
  * [STM8L101F3](https://github.com/TG9541/stm8ef/tree/master/STM8L101F3) for STM8L101F1, STM8L101F2/G2, STM8L101F3/G3/K3 and STM8L001J3M3
* STM8L [RM0031](https://www.st.com/resource/en/reference_manual/cd00218714-stm8l050j3-stm8l051f3-stm8l052c6-stm8l052r8-mcus-and-stm8l151l152-stm8l162-stm8al31-stm8al3l-lines-stmicroelectronics.pdf) "Low density" devices
  * [STM8L051F3](https://github.com/TG9541/stm8ef/tree/master/STM8L051F3) for STM8L151C3/K3/G3/F3, STM8L151C2/K2/G2/F2, STM8L051F3 and STM8L050J3M3
* STM8L "Medium density" devices
  * [STM8L151K4](https://github.com/TG9541/stm8ef/tree/master/STM8L151K4) for STM8L151C4/K4/G4, STM8L151C6/K6/G6, STM8L152C4/K4/G4, STM8L152C6/K6/G6 and STM8L052C6
* STM8L "High" and "Medium+ density" devices
  * [STM8L152R8](https://github.com/TG9541/stm8ef/tree/master/STM8L152R8) for STM8L151C8/M8/R8, STM8L152C8/K8/M8/R8 and STM8L052R8

## Board support:

STM8 eForth provides board support like LED display code for several common boards and "Chinese gadgets":

* [MINDEV](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards) for the STM8S103F3P6 $0.80 "minimum development board"
* [STM8L-DISCOVERY](https://github.com/TG9541/stm8ef/tree/master/STM8L-DISCOVERY) for the STM8L-Discovery Board (STM8L152C6 "Medium density" with LCD)

* [C0135](https://github.com/TG9541/stm8ef/wiki/Board-C0135) the "Relay-4 Board" can be used as a *Nano PLC* (Forth MODBUS support is available)
* [W1209](https://github.com/TG9541/stm8ef/wiki/Board-W1209) $1.50 thermostat board w/ 3 digit 7S-LED display, full- or half-duplex RS232 (some board variants, e.g. with CA LED displays, are supported)
* [W1219](https://github.com/TG9541/stm8ef/wiki/Board-W1219) low cost thermostat with 2x3 digit 7S-LED display with half-duplex RS232 through PD1/SWIM
* [W1401](https://github.com/TG9541/stm8ef/wiki/Board-W1401) (also XH-W1401) thermostat with 3x2 digit 7S-LED display with half-duplex RS232 through shared PD1/SWIM
* [DCDC](https://github.com/TG9541/stm8ef/wiki/Board-CN2596) hacked DCDC converter with voltmeter
* [XH-M194](https://github.com/TG9541/stm8ef/wiki/Board-XH-M194) Timer board with STM8S105K4T6C, 6 relays, RTC with clock display, 6 keys with half-duplex RS232 through PD1/SWIM
* [XY-PWM](https://github.com/TG9541/stm8ef/wiki/XY-PWM) PWM board w/ 3 digit 7S-LED display, 3 keys, dual PWM and full-duplex RS232
* [XY-LPWM](https://github.com/TG9541/stm8ef/wiki/Board-XY-LPWM) PWM board w/ 2x4 digit 7S-LCD display, 4 keys, PWM and full-duplex RS232

The Wiki lists other supported "[Value Line Gadgets][WG1]", e.g. [voltmeters & power supplies](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#voltmeters-and-power-supplies), [breakout boards](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards), and [thermostats](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#thermostats).

## Targeting other boards

The binary release contains all files required for building a configured STM8 eForth, e.g. for a custom target board. The [modular build](https://github.com/TG9541/stm8ef-modular-build) repository provides instructions, a `Makefile` and an example "board folder". Other examples are in the GitHub repositories [W1209](https://github.com/TG9541/W1209), [STM8 eForth MODBUS](https://github.com/TG9541/stm8ef-modbus), [STM8L051LED](https://github.com/TG9541/stm8l051led) or [XY-LPWM](https://github.com/TG9541/XY-LPWM).


# STM8 eForth Feature Overview

Compared to the original "stm8ef" STM8 eForth offers many features:

* a versatile framework for development based on Manfred Mahlow's e4thcom
  * board folder and include file structure for simple configuration
  * `#include` and `#require` for loading code into the STM8 eForth dictionary
  * `mcu`, `target` and `lib` folders provide a high degree of abstraction
  * [ALIAS words](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Alias-Words) for indirect dictionary entries ([even in EEPROM!](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Alias-Words#dictionary-with-alias-words-in-the-eeprom))
* compile Forth to Flash ROM with IAP (In Application Programming)
  * Words `NVM` and `RAM` switch between volatile (RAM) and non volatile (NVM) modes (*execute `RAM` after `NVM` if you want your new words to be available after power-cycle or `COLD`*)
  * autostart feature for embedded applications
  * RAM allocation for `VARIABLE` and `ALLOT` in NVM mode (basic RAM management)
* Subroutine Threaded Code (STC) with improved code density that rivals DTC
  * native `BRANCH` (JP), and `EXIT` (RET)
  * relative CALL when possible (2 instead of 3 bytes)
  * TRAP as a pseudo-opcode for literals (3 instead of 5 bytes)
  * Forth - machine-code interface using STM8 registers
* preemptive background tasks `BG`
  * `INPUT-PROCESS-OUTPUT` task indepent of the Forth console
  * fixed cycle time (configurable, default: 5ms)
  * [on supported boards](https://github.com/TG9541/stm8ef/wiki/eForth-Background-Task) `?KEY` reads board keys, `EMIT` uses board display
  * robust context switch with "clean stack" approach
* cooperative multitasking with `'IDLE`
  * [idle task](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Idle-Task) execution while there is no console input with < 10µs cycle time
  * `'IDLE` task code can run the interpreter with `EVALUATE`
* Low-level interrupts in Forth
  * lightweight context switch with `SAVEC` and `IRET`
  * example code for HALT is in the [Wiki](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Interrupts)
* configuration options for serial console or dual serial interface
  * UART: `?RX` and `TX!` full-duplex w/ half-duplex option for STM8 "Low density" and STM8L RM0031 devices
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
  * `ADC!` and `ADC@` for STM8 ADC control
  * `BKEY`, `KEYB?`, `EMIT7S`, `OUT`, `OUT!` for board keys, outputs or LEDs
  * `LOCK`, `ULOCK`, `LOCKF`, `ULOCKF` to lock and unlock EEPROM and Flash ROM
  * `B!` (b a u -- ), `[ .. ]B!` (and more) bit access and native bit set/reset words
  * `BF!`, `BF@`, `LEBF!`, `LEBF@` bitfields for little- and big-endian
  * `2C@`, `2C!` for STM8 timer 16bit register access
  * `FC!`, `FC@` for far memory access
  * `[ .. ]C!` native memory
  * `NVR`, `RAM`, `WIPE`, `RESET` and `PERSIST` for compiling to Flash memory
  * `'BOOT` for autostart applications
  * `EVALUATE` interprets Forth code in text strings (even compilation is possible!)
  * many words from Forth systems that were popular in the 1980s are provided in the [library](https://github.com/TG9541/stm8ef/tree/master/lib)

## Other changes to the original STM8EF code:

The code has changed a lot compared to the original code. Porting back some features or bug fixes should be possible anyway.

* original code bugs fixed (e.g. `COMPILE`, `DEPTH`, `R!`, `PICK`)
* "ASxxxx V2.0" syntax (the free [SDCC tool chain](http://sdcc.sourceforge.net/) allows mixing Forth, assembly, and C)
* hard STM8S105C6 dependencies were removed (e.g. initialization, clock, RAM layout, UART2)
* flexible RAM layout, basic RAM memory management, meaningful symbols for RAM locations
* conditional code for different target boards with a subdirectory based configuration framework
* significant binary size reduction

# Disclaimer, copyright

This is a hobby project! Don't use the code if you need dependable support or if correctness is required.

The license is MIT. Please refer to LICENSE.md for details.

[WG1]: https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets
