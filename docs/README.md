# Docs for STM8 eForth

STM8 eForth maintains most of the docs in the [Wiki](https://github.com/TG9541/stm8ef/wiki) while this folder contains the current [core vocabulary](https://github.com/TG9541/stm8ef/blob/master/docs/words.md). Many [library words](https://github.com/TG9541/stm8ef/tree/master/lib) contain example code, and there is a directory of [example code](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Example-Code) that also contains GitHub Gists that explain things or demonstrate features. Also the [release notes](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Releases-Overview) contain docs, code examples and references to [GitHub Issues](https://github.com/TG9541/stm8ef/issues) where features are often introduced or discussed. Note that there is also a [GitHub Discussions](https://github.com/TG9541/stm8ef/discussions) forum - questions are always welcome.

## STM8 eForth Feature Overview

Compared to the original "stm8ef" STM8 eForth offers many new features:

* a versatile framework for development based on Manfred Mahlow's e4thcom
  * board folder and include file structure for simple configuration
  * `#include` and `#require` for loading code into the STM8 eForth dictionary
  * `mcu`, `target` and `lib` folders provide a high degree of abstraction
  * [ALIAS words](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Alias-Words) for indirect dictionary entries ([even in EEPROM!](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Alias-Words#dictionary-with-alias-words-in-the-eeprom))
* compile Forth to Flash ROM with IAP (In Application Programming)
  * switch between volatile (`RAM`) and non volatile (`NVM`) modes (remember to run `RAM` after `NVM` or else new definition will be lost after a reset)
  * autostart feature for embedded applications
  * RAM allocation for `VARIABLE` and `ALLOT` in NVM mode (basic RAM management)
* Subroutine Threaded Code (STC) with improved code density that rivals DTC
  * native `BRANCH` (JP), and `EXIT` (RET)
  * relative CALL when possible (2 instead of 3 bytes)
  * TRAP as a pseudo-opcode for literals (3 instead of 5 bytes)
  * Forth - machine-code interface using STM8 registers
* preemptive background tasks `BG`
  * `INPUT-PROCESS-OUTPUT` task independent of the Forth console
  * fixed cycle time (configurable, default: 5ms)
  * [on supported boards](https://github.com/TG9541/stm8ef/wiki/eForth-Background-Task) `?KEY` reads board keys, `EMIT` uses board display
  * robust context switching with "clean stack" approach
* cooperative multitasking with `'IDLE`
  * [idle task](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Idle-Task) execution while there is no console input with < 10µs cycle time
  * `'IDLE` task code can run the interpreter with `EVALUATE`
  * STM8 Active-Halt can be [implemented](https://gist.github.com/TG9541/61db6e1bdef35d10a7aa02e321d99aa6) as an `'IDLE` task
* Low-level interrupts in Forth
  * lightweight context switch with `SAVEC` and `IRET`
  * example code for HALT is in the [Wiki](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Interrupts)
* configuration options for serial console or dual serial interface
  * UART: `?RX` and `TX!` full-duplex w/ half-duplex option for STM8 "Low density" and STM8L RM0031 devices
  * GPIO w/ Port edge & Timer4 interrupts: `?RXP .. TXP!`
  * half-duplex "bus style" communication using simulated COM port or UART
  * any GPIO or pair of GPIOs from ports PA to PE can be used to simulate a COM port
  * option for `TX! .. ?RX` on simulated COM port, and `?RXP .. TXP!` on UART
* configurable vocabulary subsets for binary size optimization
  * board dependent configuration possible down to the level of single words
  * `ALIAS` definitions for any unlinked words, also in the [EEPROM](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Alias-Words#alias-words-in-the-eeprom)
* Extended vocabulary:
  * `CONSTANT` (missing in the original code)
  * `'KEY?` and `'EMIT` for I/O redirection (originally hard-coded)
  * `CREATE .. DOES>` for *defining words* (few eForth variants have it)
  * `DO .. LEAVE .. LOOP`, `+LOOP` (for better compatibility with generic Forth)
  * `POSTPONE` replaces `COMPILE` and `[COMPILE]` (the legacy words are available as build options)
  * `ADC!` and `ADC@` for STM8 ADC control
  * `BKEY`, `KEYB?`, `EMIT7S`, `OUT`, `OUT!` for board keys, outputs or LEDs
  * `LOCK`, `ULOCK`, `LOCKF`, `ULOCKF` to lock and unlock EEPROM and Flash ROM
  * `B!` bit access and `BF!`, `BF@`, `LEBF!`, `LEBF@` bitfields for little- and big-endian
  *  `[..]B!`, `[..]B?`, `[..]SPIN` (and more) bit access words using STM8 code
  * `[..]C!` memory byte set using STM8 code
  * `2C@`, `2C!` for STM8 timer 16bit register access
  * `FC!`, `FC@` for far memory access
  * `>A`, `A@`,  `A>`, `>Y`, `Y@`, `Y>`, `[..]BC`, `[..]CB` for assembler interfacing
  * `NVR`, `RAM`, `WIPE`, `RESET` and `PERSIST` for compiling to Flash memory
  * `'BOOT` for autostart applications
  * `EVALUATE` interprets Forth code in text strings (even compilation is possible!)
  * `OUTER` and `BYE` a simple debug console for foreground code
  * many words from Forth systems that were popular in the 1980s are provided in the [library](https://github.com/TG9541/stm8ef/tree/master/lib)

## Other changes to the original STM8EF code:

The code has changed a lot compared to the original code but porting back some bug fixes or features should be possible.

* original code bugs fixed (e.g. `COMPILE`, `DEPTH`, `R!`, `PICK`, `UM/MOD`)
* "ASxxxx V2.0" syntax (the free [SDCC tool chain](http://sdcc.sourceforge.net/) allows mixing Forth, assembly, and C)
* hard STM8S105C6 dependencies were removed (e.g. initialization, clock, RAM layout, UART2)
* flexible RAM layout, basic RAM memory management, meaningful symbols for RAM locations
* a simple configuration system for new targets that gives files and settings in "target configuration folders" precedence over defaults
* significant binary size reduction

## Additional target and board documenation

Additional documentation is located in the following target folders:

* [C0135](https://github.com/TG9541/stm8ef/tree/master/C0135)
* [CORE](https://github.com/TG9541/stm8ef/tree/master/CORE)
* [DCDC](https://github.com/TG9541/stm8ef/tree/master/DCDC)
* [DOUBLECOM](https://github.com/TG9541/stm8ef/tree/master/DOUBLECOM)
* [MINDEV](https://github.com/TG9541/stm8ef/tree/master/MINDEV)
* [STM8L001J3](https://github.com/TG9541/stm8ef/tree/master/STM8L001J3)
* [STM8L051F3](https://github.com/TG9541/stm8ef/tree/master/STM8L051F3)
* [STM8L101F3](https://github.com/TG9541/stm8ef/tree/master/STM8L101F3)
* [STM8L151K4](https://github.com/TG9541/stm8ef/tree/master/STM8L151K4)
* [STM8L152R8](https://github.com/TG9541/stm8ef/tree/master/STM8L152R8)
* [STM8L-DISCOVERY](https://github.com/TG9541/stm8ef/tree/master/STM8L-DISCOVERY)
* [STM8S001J3](https://github.com/TG9541/stm8ef/tree/master/STM8S001J3)
* [STM8S103F3](https://github.com/TG9541/stm8ef/tree/master/STM8S103F3)
* [STM8S105K4](https://github.com/TG9541/stm8ef/tree/master/STM8S105K4)
* [STM8S207RB](https://github.com/TG9541/stm8ef/tree/master/STM8S207RB)
* [SWIMCOM](https://github.com/TG9541/stm8ef/tree/master/SWIMCOM)
* [W1209-CA](https://github.com/TG9541/stm8ef/tree/master/W1209-CA)
* [W1209-CA-V2](https://github.com/TG9541/stm8ef/tree/master/W1209-CA-V2)
* [W1209-FD](https://github.com/TG9541/stm8ef/tree/master/W1209-FD)
* [W1209](https://github.com/TG9541/stm8ef/tree/master/W1209)
* [W1219](https://github.com/TG9541/stm8ef/tree/master/W1219)
* [W1401](https://github.com/TG9541/stm8ef/tree/master/W1401)
* [XH-M188](https://github.com/TG9541/stm8ef/tree/master/XH-M188)
* [XH-M194](https://github.com/TG9541/stm8ef/tree/master/XH-M194)
* [XY-LPWM](https://github.com/TG9541/stm8ef/tree/master/XY-LPWM)
* [XY-PWM](https://github.com/TG9541/stm8ef/tree/master/XY-PWM)
