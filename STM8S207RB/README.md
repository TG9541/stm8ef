# STM8S207RB Base Image

This folder contains the configuration for STM8S "High density" devices as described in [RM0016](https://www.st.com/resource/en/reference_manual/cd00190271-stm8s-series-and-stm8af-series-8-bit-microcontrollers-stmicroelectronics.pdf) with up to 32K normal Flash ROM + [96K far Flash ROM](https://hackaday.io/project/16097-eforth-for-cheap-stm8s-gadgets/log/181451-accessing-stm8-far-memory), 6K RAM and 2K EEPROM. These robust devices can run at 24MHz and offer a good feature set (e.g. 10bit ADC, 4 timers, 2 UARTs, I2C, SPI, TLI, AWU) and configuration is trivially easy compared to STM8L devices (e.g. simple ADC, clock tree "normally on"). STM8S208 devices provide a CAN controller.

The following datasheets apply:
* [STM8S207C6/K6/R6/S6, STM8S207C8/K8/M8/R8/S8, STM8S207CB/MB/RB/SB, STM8S208C6/R6/S6, STM8S208C8/R8/S8 and STM8S208CB/MB/RB/SB](https://www.st.com/resource/en/datasheet/stm8s208r8.pdf) for 32 to 80 pin packages 
* [STM8S007C8](https://www.st.com/resource/en/datasheet/stm8s007c8.pdf) "Value Line" with reduced specs

The specified memory for the different devices varies (which doesn't rule out that the memory is there).

## STM8 eForth Programming

Most of the STM8S (RM0016) peripheral registers addresses are the same across "Low density" and "Medium" or "High density" devices and device independent code can be written by using `\res MCU: STM8S`.

Using e4thcom as a terminal program is recommended. With the help of e4thcom (or codeload.py) `mcu/STM8S.efr` can be used to load peripheral register address constants:

```Forth
\res MCU: STM8S
\res export SPI_CR1 SPI_CR2 SPI_DR SPI_SR
```

UART constants are a special case: writing device independent code works best if a sub-set of registers with a `UART_` prefix is used. This can be achieved by using `\res MCU: STM8S207`. The "device independent" `\res MCU: STM8S` can also be used by reassigning constants (e.g. `UART1_DR CONSTANT UART_DR`). More on this in [Some STM8S peripherals are equal, some are the same](https://hackaday.io/project/16097-eforth-for-cheap-stm8s-gadgets/log/178072-some-stm8s-peripherals-are-equal-some-are-the-same) on HaD.

## UART Console Settings

STM8S "High density" devices have two UARTs with the exception of the 32pin STM8S207K8 that has no pins for UART1 signals.

The binary release contains the image STM8S207RB which can be used for any High Density device since it communicates through the 2nd UART (i.e. it's also compatible with STM8S207Kx devices in a LQFP-32 package). The first UART can be selected as a build option by setting `USE_UART2 = 0` in `globconf.inc`.

Device|Package|pin RX-1 ‡|pin Tx-1 ‡|pin RX-2|pin TX-2
-|-|-|-|-|-
STM8S207Kx|LQFP-32|-|-|**31**|**30**
STM8S207Sx|LQFP-44|9|10|**43**|**42**
STM8S207Cx|LQFP-48|10|11|**47**|**46**
STM8S207Rx|LQFP-64|10|11|**63**|**62**
STM8S207Mx|LQFP-80|10|11|**79**|**78**

**‡**: Note: to configure the Forth console to use the first UART (UART1) apply the following settings in `globconf.inc`:

Buffered high speed console communication can be added by following the instructions in [`INTRX`](https://github.com/TG9541/stm8ef/blob/master/lib/INTRX) (refer to the `\\ Example` part of the library word).

The STM8S "High density" `UART1` can be configured as `HAS_HALFDUPLEX`: by setting `HAS_HALFDUPLEX = 1` in `globconf.inc` the selected UART_TX switches betweens TX and RX:

```
               .
STM8S device   .      .----o serial TxD "TTL"
               .      |      (e.g. "CH340" USB serial converter)
               .     ---
               .     / \  1N4148
               .     ---
               .      |
USRT_TX - ----->>-----*----o serial RxD "TTL
               .
GND ----------->>----------o serial GND
               .
               .
```

This feature can free up one more GPIO for other uses, or it can be used for creating a simple bus.

It's possible to use a simulated serial interface (also in addition to the UART) - please refer to the [SWIMCOM](https://github.com/TG9541/stm8ef/tree/master/SWIMCOM) or the [DOUBLECOM](https://github.com/TG9541/stm8ef/tree/master/DOUBLECOM) configurations for guidance on settings in `globconf.inc`.

## Breakout boards

STM8S207RB breakout boards like the one below for around $4 offer 6K RAM, 2K EEPROM and 32K "Forth Flash" (which is quite a lot for STM8 eForth). It also provides additionally 96K "far flash memory", 2 UARTs and many GPIOs.

![STM8S207RB](https://camo.githubusercontent.com/7e004d7f26e26268c70e227df98aa8e561f4da5b/68747470733a2f2f696d672e73746174696362672e636f6d2f7468756d622f766965772f6f6175706c6f61642f62616e67676f6f642f696d616765732f45302f31392f65643166663938372d613834322d346634382d383464362d3639363234303564656633332e6a706567)

Documentation for this board is in the [Wiki](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards#stm8s207rbt6-breakout-board).
