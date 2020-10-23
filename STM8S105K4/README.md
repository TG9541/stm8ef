# STM8S105K4 Base Image

This folder contains the configuration for STM8S "Medium density" devices as described in [RM0016](https://www.st.com/resource/en/reference_manual/cd00190271-stm8s-series-and-stm8af-series-8-bit-microcontrollers-stmicroelectronics.pdf) with up to 32K Flash ROM, 2K RAM and 1K EEPROM. These robust devices offer a good feature set (e.g. 10bit ADC, 4 timers, I2C, SPI, TLI, AWU) and configuration is trivially easy compared to STM8L devices (e.g. simple ADC, clock tree "normally on"). Tests have shown that, like automotive grade STM8AF "Medium density" devices, using a 24MHz clock for the core [is possible](https://hackaday.io/project/16097-eforth-for-cheap-stm8s-gadgets/log/172752-stm8s-medium-density-devices-can-have-performance-too).

The following datasheets apply:
* [STM8S105C4/K4/S4 and STM8S105C6/K6/S6](https://www.st.com/resource/en/datasheet/stm8s105k4.pdf) "Access Line"
* [STM8S005C6/K6](https://www.st.com/resource/en/datasheet/stm8s005c6.pdf) "Value Line"

The specified memory for the different devices varies (which doesn't rule out that the memory is there).

## STM8 eForth Programming

Most of the STM8S (RM0016) peripheral registers addresses are the same across "Low density" and "Medium" or "High density" devices and device independent code can be written by using `\res MCU: STM8S`.

Using e4thcom as a terminal program is recommended. With the help of e4thcom (or codeload.py) `mcu/STM8S.efr` can be used to load peripheral register address constants:

```Forth
\res MCU: STM8S
\res export SPI_CR1 SPI_CR2 SPI_DR SPI_SR
```

UART constants are a special case: writing device independent code works best if a sub-set of registers with a `UART_` prefix is used. This can be achieved by using `\res MCU: STM8S105`. The "device independent" `\res MCU: STM8S` can also be used by reassigning constants (e.g. `UART1_DR CONSTANT UART_DR`). More on this in [Some STM8S peripherals are equal, some are the same](https://hackaday.io/project/16097-eforth-for-cheap-stm8s-gadgets/log/178072-some-stm8s-peripherals-are-equal-some-are-the-same) on HaD.

## UART Console Settings

STM8S "Mediym density" devices have a UART2 as described in RM0016 - its register addresses are at the same location as those of the secondary UART of STM8S "High denisty" devices. For UART2 no half-duplex mode is documented.

![STM8S105K4 pinout](https://user-images.githubusercontent.com/5466977/96959390-3945ef80-1500-11eb-8b82-3f9cfdfba66b.png)

Device|Package|pin RX|pin TX
-|-|-|-
STM8S105Kx|LQFP-32|31|30
STM8S105Sx|LQFP-44|43|42
STM8S105Cx|LQFP-48|47|46

Buffered high speed console communication can be added by following the instructions in [`INTRX`](https://github.com/TG9541/stm8ef/blob/master/lib/INTRX) (refer to the `\\ Example` part of the library word).

It's possible to use a simulated serial interface (also in addition to the UART) - please refer to the [SWIMCOM](https://github.com/TG9541/stm8ef/tree/master/SWIMCOM) or the [DOUBLECOM](https://github.com/TG9541/stm8ef/tree/master/DOUBLECOM) configurations for guidance on settings in `globconf.inc`.

## Breakout boards

STM8S105K4 breakout boards like the one below offer 2K RAM, 1K EEPROM and 32K Flash ROM (which is quite a lot for STM8 eForth).

![STM8S105K4](https://camo.githubusercontent.com/6f83aa69a3bdd8833792c67c084b9195a710f825/68747470733a2f2f616530312e616c6963646e2e636f6d2f6b662f485442314c694f625058585858585878585658587136785846585858592f467265652d317063732d53544d38532d73746d3873312d73746d38733130352d73746d38733130356b2d73746d38733130356b342d646576656c6f706d656e742d626f6172642d636f72652d626f6172642d73746d38733130356b3474362d73797374656d2d626f6172642d6d696e696d756d2d73797374656d2e6a70675f323230783232302e6a7067)

Documenation for this board is in the [Wiki](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards#stm8s105k4t6-breakout-board).

The binary release contains the image STM8S105K4 which can be used for any Medium Density device that communicates through the STM8 UART.
