# STM8 eForth (stm8ef)

![Build](https://github.com/TG9541/stm8ef/actions/workflows/build-test.yml/badge.svg)

STM8 eForth is a ready to use interactive Forth system for [STM8 MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm8-8-bit-mcus.html). The STM8 family of highly reliable 8bit microcontrollers has 16bit extensions and modern peripherals. STM8 devices are widely available and easy to master. The [embedded Forth](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Programming) turns STM8 devices into a "computer" with a serial console. STM8 eForth has been used for learning, creating one-off appliances, and for small-scale commercial projects.

The Forth console provides a command interpreter, a native code compiler, and features like background execution of application code. This enables use cases like interactive testing of peripherals, control parameter tuning, and adding or changing code in the Flash ROM while application code is running. [Code examples](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Example-Code) for STM8 peripherals, e.g., timers, RTC, ADC, I2C, can be used as a starting point for creating reliable embedded systems.

[![STM8EF Wiki](https://user-images.githubusercontent.com/5466977/28994765-3267d78c-79d6-11e7-927f-91751cd402db.jpg)](https://github.com/TG9541/stm8ef/wiki)

The [binary release](https://github.com/TG9541/stm8ef/releases) provides ready-to-run Forth binaries with STM8 register definitions and a library for a range of STM8 chips and target boards. Build- and test-automation uses the uCsim STM8 simulator in a [GitHub Action](https://github.com/TG9541/stm8ef/actions). Releases are presented as "release" (stable), "pre-release" (unstable) and "[volatile](https://github.com/TG9541/stm8ef/releases/tag/volatile)" (latest).

The binary release contains all necessary sources, tools and libraries needed by downstream projects for building a custom STM8 eForth core. The SDCC tool chain is used, and the [modular build](https://github.com/TG9541/stm8ef-modular-build) concept simplifies use cases like "adding board support", "custom memory layout", "tailored vocabulary" or a "mixed C/Forth project".

## About Forth

Forth works by defining new words with "phrases" consisting of existing words, numbers or strings. A simple "Hello World" in Forth looks like this:

```Forth
: hello ." Hello World!" ;
```

The Forth language is so simple that you can learn the basics in a snap, e.g., with the [STM8 eForth Walk-Through](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Programming). Forth has no real syntax but good design results in readable phrases (e.g. `15 deg left servo turn-by` or `center right servo turn-to`).

Forth is a stack based language: data flows on the data stack from one word to the next and in most cases there is no need for temporary variables.

The Forth programming style encourages "factoring" functionality. This leads to very good code density but it also simplifies testing. Forth is a "low level" language that offers a high level of abstraction: even words for control structures like `IF ... THEN` are just Forth words that compile code.

The best feature of Forth is that it allows interactive testing of words and phrases. An embedded system can be used as its own application oriented test environment!

## About STM8 eForth

The STM8 eForth core is written in STM8 assembly using the SDCC tool chain. Combining Forth with C is supported.

The original STM8 eForth was written by [Dr. C.H. Ting's eForth](http://www.forth.org/svfig/kk/07-2010.html) for the STM8S Discovery. With the kind permission of Dr. Ting the code presented here is under [MIT license](https://github.com/TG9541/stm8ef/blob/master/LICENSE.md). Bugs were fixed, the code size reduced, standards compatibility improved and many features were added (e.g. compilation to Flash memory, autostart code, interrupt handling - see [overview](https://github.com/TG9541/stm8ef/tree/master/docs) and [words list](https://github.com/TG9541/stm8ef/blob/master/docs/words.md) in the docs folder.

STM8 eForth is highly configurable: a Forth binary that allows compiling new words to Flash ROM or RAM fits in less than 4K, amd a binary with extended vocabulary requires about 5.5K. Due to the high code density a low cost devices with 8K Flash ROM, like the [STM8S003F3P6](https://www.st.com/resource/en/datasheet/stm8s003f3.pdf), is sufficient for non-trivial applications. If more space is needed a low-cost 32K device can be used, e.g. [STM8S005C6](https://www.st.com/resource/en/datasheet/stm8s005c6.pdf) or [STM8L052C6](https://www.st.com/resource/en/datasheet/stm8l052c6.pdf).

The Forth console uses the STM8 UART or a simulated serial interface for communication with a serial terminal (3-wire full-duplex and 2-wire half-duplex are supported). For console access and programming [e4thcom](https://wiki.forth-ev.de/doku.php/en:projects:e4thcom) is recommended but any serial terminal will work. The console can be configured, even at runtime, to use other [character I/O channels](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Board-Character-IO), e.g., a keyboard and a character display.

The [Wiki on GitHub](https://github.com/TG9541/stm8ef/wiki) covers various topics, e.g. converting low-cost Chinese thermostats, voltmeters or DC/DC-converters into Forth powered embedded control boards.

## Board support:

STM8 eForth provides board support for selected mass-produced Chinese low-cost control boards, e.g. words for relay outputs, or I/O with keys and LED displays. Since the appearance of MCUs with the same pin-out as the popular STM8S003F3P6 common "Chinese gadgets" like thermostats, voltmeters or relay boards can no longer be expected to use an STM8 chip, and soldering skills are required to replace it. There is more [information in the Wiki](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets).

Note that break-out boards and the [C0135](https://github.com/TG9541/stm8ef/wiki/Board-C0135) control board can be expected to work without any change.

![C0135](https://user-images.githubusercontent.com/5466977/64919487-9f176200-d7ab-11e9-9a4f-00d0d6d24ceb.png)

* [STM8L-DISCOVERY](https://github.com/TG9541/stm8ef/tree/master/STM8L-DISCOVERY) for the STM8L-Discovery Board (STM8L152C6 "Medium density" with LCD)
* [MINDEV](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards) for the STM8S103F3P6 $0.80 "minimum development board" (just like the STM8S103F3 configuration but with a word `OUT!` for controlling the LED)
* [C0135](https://github.com/TG9541/stm8ef/wiki/Board-C0135) the "Relay-4 Board" can be used as a *Nano PLC* (Forth [MODBUS support](https://github.com/TG9541/stm8ef-modbus) is available)
* [W1209](https://github.com/TG9541/stm8ef/wiki/Board-W1209) $1.50 thermostat board w/ 3 digit 7S-LED display, full- or half-duplex RS232 (some board variants, e.g. with CA LED displays, are supported). A [W1209 demo application](https://github.com/TG9541/W1209) is available.
* [W1219](https://github.com/TG9541/stm8ef/wiki/Board-W1219) low cost thermostat with 2x3 digit 7S-LED display with half-duplex RS232 through PD1/SWIM
* [W1401](https://github.com/TG9541/stm8ef/wiki/Board-W1401) (also XH-W1401) thermostat with 3x2 digit 7S-LED display with half-duplex RS232 through shared PD1/SWIM
* [DCDC](https://github.com/TG9541/stm8ef/wiki/Board-CN2596) hacked DCDC converter with voltmeter
* [XH-M194](https://github.com/TG9541/stm8ef/wiki/Board-XH-M194) Timer board with STM8S105K4T6C, 6 relays, RTC with clock display, 6 keys with half-duplex RS232 through PD1/SWIM
* [XY-PWM](https://github.com/TG9541/stm8ef/wiki/XY-PWM) PWM board w/ 3 digit 7S-LED display, 3 keys, dual PWM and full-duplex RS232
* [XY-LPWM](https://github.com/TG9541/stm8ef/wiki/Board-XY-LPWM) PWM board w/ 2x4 digit 7S-LCD display, 4 keys, PWM and full-duplex RS232

The Wiki lists other supported "[Value Line Gadgets][WG1]", e.g. [voltmeters & power supplies](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#voltmeters-and-power-supplies), [breakout boards](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards), and [thermostats](https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets#thermostats).

### Targeting other boards

The binary release contains all files required for building a configured STM8 eForth, e.g. for a custom target board. The [modular build](https://github.com/TG9541/stm8ef-modular-build) repository provides instructions, a `Makefile` and an example "board folder". Other examples are in the GitHub repositories [W1209](https://github.com/TG9541/W1209), [STM8 eForth MODBUS](https://github.com/TG9541/stm8ef-modbus), [STM8L051LED](https://github.com/TG9541/stm8l051led) or [XY-LPWM](https://github.com/TG9541/XY-LPWM).

## Generic targets

STM8 eForth provides configurations and binaries for typical STM8S and STM8L devices. The binaries for selected "Low", "Medium" or "High density" can be expected to work for all of the listed packaging and memory "specs variants" (i.e., a device with 32K Flash specified as 16K). For details please refer to the `README.md` in the configuration folders referenced below. The automotive grade and the special purpose families should also work. Please open an [Issue](https://github.com/TG9541/stm8ef/issues) or use [Discussions](https://github.com/TG9541/stm8ef/discussions) if you have questions about support for a device!

### STM8S targets

Support for STM8S devices in the [RM0016](https://www.st.com/resource/en/reference_manual/cd00190271-stm8s-series-and-stm8af-series-8-bit-microcontrollers-stmicroelectronics.pdf) family is stable. Peripherals aren't as advanced as those of e.g. STM8L devices but that makes them easy to master. Automotive grade STM8AF devices in the same family can be expected to work. Various STM8 Discovery boards and breakout boards for "Low", "Medium", and "High density" devices can be used.

* STM8S "Low density" devices (up to 1K RAM, 8K Flash and 640 bytes EEPROM)
  * [STM8S103F3](https://github.com/TG9541/stm8ef/tree/master/STM8S103F3) for STM8S003F3/K3, STM8S103F2/F3/K3 and STM8S903F3/K3 (not recommended for STM8S001J3)
  * [STM8S001J3](https://github.com/TG9541/stm8ef/tree/master/STM8S001J3) for STM8S001J3 (and STM8Sx03x3) with half-duplex `UART_TX-RX`
* STM8S "Medium density" devices (up to 2K RAM, 32K Flash and 1K EEPROM)
  * [STM8S105K4](https://github.com/TG9541/stm8ef/tree/master/STM8S105K4) for STM8S005C6/K6, STM8S105C4/K4/S4 and STM8S105C6/K6/S6
* STM8S "High density" devices (up to 6K RAM, 32K + 96K Flash and 2K EEPROM)
  * [STM8S207RB](https://github.com/TG9541/stm8ef/tree/master/STM8S207RB) for STM8S007C8, STM8S207C6/K6/R6/S6, STM8S207C8/K8/M8/R8/S8, STM8S207CB/MB/RB/SB, STM8S208C6/R6/S6, STM8S208C8/R8/S8 and STM8S208CB/MB/RB/SB

### STM8L targets

STM8L support for [RM0031](https://www.st.com/resource/en/reference_manual/cd00218714-stm8l050j3-stm8l051f3-stm8l052c6-stm8l052r8-mcus-and-stm8l151l152-stm8l162-stm8al31-stm8al3l-lines-stmicroelectronics.pdf) family devices in STM8 eForth is stable. Compared to STM8S most STM8L devices provide a much richer feature set, and studying the reference manual may take more time. The STM8 eForth core is mostly the same as for STM8S devices. The latest addition was support for STM8L101F3 and STM8L001J3, the only members of the frugal [RM0013](https://www.st.com/resource/en/reference_manual/CD00184503-.pdf) family.

For more details please refer to the `README.md` in the board folders below.

* RM0013 family STM8L "Low density" devices (1.5K RAM, 8K Flash, basic peripherals)
  * [STM8L101F3](https://github.com/TG9541/stm8ef/tree/master/STM8L101F3) for STM8L101F1, STM8L101F2/G2, STM8L101F3/G3/K3 and STM8L001J3M3
* RM0031 family STM8L "Low density" devices (1K RAM, 8K Flash, 256 bytes EEPROM, advanced peripherals)
  * [STM8L051F3](https://github.com/TG9541/stm8ef/tree/master/STM8L051F3) for STM8L151C3/K3/G3/F3, STM8L151C2/K2/G2/F2, STM8L051F3 and STM8L050J3M3
* RM0031 family STM8L "Medium density" devices (2K RAM, 32K Flash, 1K EEPROM)
  * [STM8L151K4](https://github.com/TG9541/stm8ef/tree/master/STM8L151K4) for STM8L151C4/K4/G4, STM8L151C6/K6/G6, STM8L152C4/K4/G4, STM8L152C6/K6/G6 and STM8L052C6
* RM0031 family STM8L "High" and "Medium+ density" devices (4K RAM, 32K + 32K Flash, 2K EEPROM)
  * [STM8L152R8](https://github.com/TG9541/stm8ef/tree/master/STM8L152R8) for STM8L151C8/M8/R8, STM8L152C8/K8/M8/R8 and STM8L052R8

## Other configuration examples

The STM8 eForth core is highly configurable. The following configuration examples showcase minimal configurations or communication settings.

*  [CORE](https://github.com/TG9541/stm8ef/tree/master/CORE) "svelte" 4K configuration for STM8S "Low density" devices, some features were disabled (no background task, `DO .. LOOP` or `CREATE .. DOES>`) and dictionary search is case-sensitive like in the original STM8EF (to conserve a few more bytes)
* [SWIMCOM](https://github.com/TG9541/stm8ef/tree/master/SWIMCOM) 2-wire console interface through PD1/SWIM (i.e. the ICP pin) with full feature set
* [DOUBLECOM](https://github.com/TG9541/stm8ef/tree/master/DOUBLECOM) 3-wire console interface with extra UART I/O words for the application

# Release and development cycle

The Github Releases section contains binary releases. As STM8 eForth is based on eForth V2 (embedded STC Forth) and, since it improves on STM8EF V2.1, releases follow the naming scheme "STM8 eForth 2.2.x".

Using a target binary requires setting a symlink `target` to the desired board target folder, e.g. `ln -s out/STM8S105K4/target target` (use `make BOARD=<target>` or `BOARD=<target> make`).

The git master branch contains the current development version (releases are tagged). After cloning the repository `make` will build all targets.

Running `make BOARD=STM8S105K4` will set a symlink. The Forth console prompt will show the release version (e.g. `STM8eForth 2.2.27`) or the next pre-release (e.g. `STM8EF2.2.28.pre1`).

# Disclaimer, copyright

This is a hobby project! Don't use the code if you need dependable support or if correctness is required.

The license is MIT. Please refer to LICENSE.md for details.

[WG1]: https://github.com/TG9541/stm8ef/wiki/STM8S-Value-Line-Gadgets
