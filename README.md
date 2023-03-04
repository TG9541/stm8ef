# STM8 eForth (stm8ef)

![Build](https://github.com/TG9541/stm8ef/actions/workflows/build-test.yml/badge.svg)

STM8 eForth is an interactive Forth system for the [STM8 family of highly reliable 8-bit MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm8-8-bit-mcus.html). The STM8 core is a 8bit µC with 16bit extensions. Peripherals are modern but easier to master than those in the STM32 family of 32bit µCs. The Forth console, an interpreter and native-code compiler, turns this simple device into a "computer" that provides operating-system-like features such as background code execution. It enables interactive exploration of peripherals or tuning of control parameters, and it's even possible to change code in the Flash ROM while an application is running. [Code examples](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Example-Code) for STM8 peripherals (like I2C, ADC, PWM, RTC, etc.) can be used as a starting point for creating reliable embedded control applications.

[![STM8EF Wiki](https://user-images.githubusercontent.com/5466977/28994765-3267d78c-79d6-11e7-927f-91751cd402db.jpg)](https://github.com/TG9541/stm8ef/wiki)

The [binary release](https://github.com/TG9541/stm8ef/releases) provides a ready-to-run Forth for a range of devices and target boards (including STM8 register definitions and library). Build- and test-automation uses the uCsim STM8 simulator in a [GitHub Action](https://github.com/TG9541/stm8ef/actions). In the order of "stability" releases are organized as "release", "pre-release" and (unstable) "[volatile](https://github.com/TG9541/stm8ef/releases/tag/volatile)".

For downstream projects the binary release contains all necessary sources, tools and libraries to build a custom STM8 eForth core (e.g., using the [modular build support](https://github.com/TG9541/stm8ef-modular-build). Typical modular build use cases are, e.g., adding a new target with specific hardware support, custom memory layout, a tailored vocabulary or making a mixed C/Forth project.

## About Forth

Forth works by defining new words with "phrases" consisting of existing words - "Hello World" in Forth is this:

```Forth
: hello ." Hello World!" ;
```

Forth is a "low level" language that offers a high level of abstraction:

Forth has no real syntax but good phrases look like Yoda-speak (e.g. `15 deg left servo turn-by` or `center right servo turn-to`).

Data flows on the stack from one word to the next and in most cases there is no need for temporary variables. This leads to very good code density and it also simplifies testing. Even control structures in the compiler are just Forth words.

The best feature of Forth is that it allows interactive testing of words and phrases. This turns the embedded system into an application oriented test environment!

Forth is so simple that you can learn the basics in a snap, e.g. in the [STM8 eForth Walk-Through](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Programming).

## About STM8 eForth

The STM8 eForth core is written in STM8 assembly using the SDCC tool chain's sdasstm8 assembler. Combining Forth with C is supported.

The original STM8 eForth was written by [Dr. C.H. Ting's eForth](http://www.forth.org/svfig/kk/07-2010.html) for the STM8S Discovery. With the kind permission of Dr. Ting the code presented here is under [MIT license](https://github.com/TG9541/stm8ef/blob/master/LICENSE.md). Bugs were fixed, the code size reduced, standards compatibility improved and many features added (e.g. compilation to Flash memory, autostart code, interrupt handling - see [overview](https://github.com/TG9541/stm8ef/tree/master/docs) and [words list](https://github.com/TG9541/stm8ef/blob/master/docs/words.md) in the docs folder.

STM8 eForth is highly configurable: a Forth binary that allows compiling new words to Flash ROM or RAM requires less than 4K. A binary with an extended vocabulary needs no more than about 5.5K. Due to the extraordinary code density very-low-cost 8K devices, e.g. [STM8S003F3P6](https://www.st.com/resource/en/datasheet/stm8s003f3.pdf) or [STM8L051F3P6](https://www.st.com/resource/en/datasheet/stm8l051F3.pdf), are sufficient for non-trivial applications. If more space is needed a low-cost 32K device can be used, e.g. [STM8S005C6](https://www.st.com/resource/en/datasheet/stm8s005c6.pdf) or [STM8L052C6](https://www.st.com/resource/en/datasheet/stm8l052c6.pdf).

The Forth console uses the STM8 U(S)ART or a simulated serial interface for communicating with the console (3-wire full-duplex or 2-wire half-duplex are supported). For console access and programming [e4thcom](https://wiki.forth-ev.de/doku.php/en:projects:e4thcom) is recommended but any serial terminal will work. The console can be configured, even at runtime, to use other [character I/O channels](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Board-Character-IO), e.g. keyboard and display.

The [Wiki on GitHub](https://github.com/TG9541/stm8ef/wiki) covers various topics, e.g. converting low-cost Chinese thermostats, voltmeters or DC/DC-converters into Forth powered embedded control boards.

## Release and development cycle

The Github Releases section contains binary releases. As STM8 eForth is based on eForth V2 (an embedded STC Forth), and it improves on STM8EF V2.1, releases follow the naming scheme "STM8 eForth 2.2.x".

Using a target binary requires setting a symlink `target` to the desired board target folder, e.g. `ln -s out/STM8S105K4/target target` (a `make BOARD=<target>` will do that for you).

The git master branch contains the current development version (releases are tagged). After cloning the repository `make` will build all targets.

Running `make BOARD=STM8S105K4` will set a symlink. The Forth console prompt will show the release version (e.g. `STM8eForth 2.2.27`) or the next pre-release (e.g. `STM8EF2.2.28.pre1`).

## Generic targets

STM8 eForth provides configurations and binaries for typical STM8S and STM8L devices. The binaries for selected "Low", "Medium" or "High density" can be expected to work for all of the listed packaging and memory "specs variants". For details please refer to the `README.md` in the configuration folders referenced below.

### Generic STMS targets

Support for STM8S devices in the [RM0016](https://www.st.com/resource/en/reference_manual/cd00190271-stm8s-series-and-stm8af-series-8-bit-microcontrollers-stmicroelectronics.pdf) family is stable. Peripherals aren't as advanced as those of e.g. STM8L devices but that makes them easy to master. Automotive grade STM8AF devices in the same family can be expected to work. Various STM8 Discovery boards and breakout boards for "Low", "Medium", and "High density" devices can be used.

* STM8S "Low density" devices (up to 1K RAM, 8K Flash and 640 bytes EEPROM)
  * [STM8S103F3](https://github.com/TG9541/stm8ef/tree/master/STM8S103F3) for STM8S003F3/K3, STM8S103F2/F3/K3 and STM8S903F3/K3 (not recommended for STM8S001J3)
  * [STM8S001J3](https://github.com/TG9541/stm8ef/tree/master/STM8S001J3) for STM8S001J3 (and STM8Sx03x3) with half-duplex `UART_TX-RX`
* STM8S "Medium density" devices (up to 2K RAM, 32K Flash and 1K EEPROM)
  * [STM8S105K4](https://github.com/TG9541/stm8ef/tree/master/STM8S105K4) for STM8S005C6/K6, STM8S105C4/K4/S4 and STM8S105C6/K6/S6
* STM8S "High density" devices (up to 6K RAM, 32K + 96K Flash and 2K EEPROM)
  * [STM8S207RB](https://github.com/TG9541/stm8ef/tree/master/STM8S207RB) for STM8S007C8, STM8S207C6/K6/R6/S6, STM8S207C8/K8/M8/R8/S8, STM8S207CB/MB/RB/SB, STM8S208C6/R6/S6, STM8S208C8/R8/S8 and STM8S208CB/MB/RB/SB

### Generic STML targets

Compared to STM8S most STM8L devices provide a much richer feature set and studying the reference manual may take more time. Although support for STM8L peripherals is relatively recent the STM8 eForth core is mostly the same as for STM8S devices and thus well tested. The latest addition is support for STM8L101F3 and STM8L001J3, the only members of the [RM0013](https://www.st.com/resource/en/reference_manual/CD00184503-.pdf) family.

For more details please refer to the `README.md` in the board folders below.

* STM8L [RM0013](https://www.st.com/resource/en/reference_manual/CD00184503-.pdf) family "Low density" devices (1.5K RAM, 8K Flash, basic peripherals)
  * [STM8L101F3](https://github.com/TG9541/stm8ef/tree/master/STM8L101F3) for STM8L101F1, STM8L101F2/G2, STM8L101F3/G3/K3 and STM8L001J3M3
* [RM0031](https://www.st.com/resource/en/reference_manual/cd00218714-stm8l050j3-stm8l051f3-stm8l052c6-stm8l052r8-mcus-and-stm8l151l152-stm8l162-stm8al31-stm8al3l-lines-stmicroelectronics.pdf) family STM8L "Low density" devices (1K RAM, 8K Flash, 256 bytes EEPROM, advanced peripherals)
  * [STM8L051F3](https://github.com/TG9541/stm8ef/tree/master/STM8L051F3) for STM8L151C3/K3/G3/F3, STM8L151C2/K2/G2/F2, STM8L051F3 and STM8L050J3M3
* STM8L "Medium density" devices (2K RAM, 32K Flash, 1K EEPROM)
  * [STM8L151K4](https://github.com/TG9541/stm8ef/tree/master/STM8L151K4) for STM8L151C4/K4/G4, STM8L151C6/K6/G6, STM8L152C4/K4/G4, STM8L152C6/K6/G6 and STM8L052C6
* STM8L "High" and "Medium+ density" devices (4K RAM, 32K + 32K Flash, 2K EEPROM)
  * [STM8L152R8](https://github.com/TG9541/stm8ef/tree/master/STM8L152R8) for STM8L151C8/M8/R8, STM8L152C8/K8/M8/R8 and STM8L052R8

## Board support:

STM8 eForth provides board support, e.g. words for relay outputs or I/O with keys and LED displays, for several common development boards and "Chinese gadgets" like thermostats, voltmeters or relay boards. There is more [information in the Wiki](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets).

*  [CORE](https://github.com/TG9541/stm8ef/tree/master/CORE) "svelte" 4K configuration for STM8S "Low density" devices, some features are disabled (no background task, `DO .. LOOP` or `CREATE .. DOES>`). Also, the dictionary search is case-sensitive.
* [SWIMCOM](https://github.com/TG9541/stm8ef/tree/master/SWIMCOM) 2-wire communication through PD1/SWIM (i.e. the ICP pin) and a full feature set (the similar [DOUBLECOM](https://github.com/TG9541/stm8ef/tree/master/DOUBLECOM) also provides UART I/O words for applications)
* [MINDEV](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards) for the STM8S103F3P6 $0.80 "minimum development board" (just like the STM8S103F3 configuration but with a word `OUT!` for controlling the LED)
* [STM8L-DISCOVERY](https://github.com/TG9541/stm8ef/tree/master/STM8L-DISCOVERY) for the STM8L-Discovery Board (STM8L152C6 "Medium density" with LCD)
* [C0135](https://github.com/TG9541/stm8ef/wiki/Board-C0135) the "Relay-4 Board" can be used as a *Nano PLC* (Forth [MODBUS support](https://github.com/TG9541/stm8ef-modbus) is available)
* [W1209](https://github.com/TG9541/stm8ef/wiki/Board-W1209) $1.50 thermostat board w/ 3 digit 7S-LED display, full- or half-duplex RS232 (some board variants, e.g. with CA LED displays, are supported). A [W1209 demo application](https://github.com/TG9541/W1209) is available.
* [W1219](https://github.com/TG9541/stm8ef/wiki/Board-W1219) low cost thermostat with 2x3 digit 7S-LED display with half-duplex RS232 through PD1/SWIM
* [W1401](https://github.com/TG9541/stm8ef/wiki/Board-W1401) (also XH-W1401) thermostat with 3x2 digit 7S-LED display with half-duplex RS232 through shared PD1/SWIM
* [DCDC](https://github.com/TG9541/stm8ef/wiki/Board-CN2596) hacked DCDC converter with voltmeter
* [XH-M194](https://github.com/TG9541/stm8ef/wiki/Board-XH-M194) Timer board with STM8S105K4T6C, 6 relays, RTC with clock display, 6 keys with half-duplex RS232 through PD1/SWIM
* [XY-PWM](https://github.com/TG9541/stm8ef/wiki/XY-PWM) PWM board w/ 3 digit 7S-LED display, 3 keys, dual PWM and full-duplex RS232
* [XY-LPWM](https://github.com/TG9541/stm8ef/wiki/Board-XY-LPWM) PWM board w/ 2x4 digit 7S-LCD display, 4 keys, PWM and full-duplex RS232

The Wiki lists other supported "[Value Line Gadgets][WG1]", e.g. [voltmeters & power supplies](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#voltmeters-and-power-supplies), [breakout boards](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards), and [thermostats](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#thermostats).

## Targeting other boards

The binary release contains all files required for building a configured STM8 eForth, e.g. for a custom target board. The [modular build](https://github.com/TG9541/stm8ef-modular-build) repository provides instructions, a `Makefile` and an example "board folder". Other examples are in the GitHub repositories [W1209](https://github.com/TG9541/W1209), [STM8 eForth MODBUS](https://github.com/TG9541/stm8ef-modbus), [STM8L051LED](https://github.com/TG9541/stm8l051led) or [XY-LPWM](https://github.com/TG9541/XY-LPWM).

# Disclaimer, copyright

This is a hobby project! Don't use the code if you need dependable support or if correctness is required.

The license is MIT. Please refer to LICENSE.md for details.

[WG1]: https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets
