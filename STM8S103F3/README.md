# STM8S103F3 Base Image

This folder contains the configuration for STM8S "Low density" devices as described in [RM0016](https://www.st.com/resource/en/reference_manual/cd00190271-stm8s-series-and-stm8af-series-8-bit-microcontrollers-stmicroelectronics.pdf) with 8K Flash ROM, 1K RAM and 640 bytes EEPROM. These very low cost devices offer a good feature set (e.g. 10bit ADC, 3 timers, I2C, SPI, TLI, AWU) while the clock tree is active by default and configuration is trivial compared with STM8L devices (e.g. ADC). This makes STM8S devices a good choice for getting started with STM8 eForth.

The following datasheets apply:

* [STM8S003F3/K3](https://www.st.com/resource/en/datasheet/stm8s003f3.pdf)
* [STM8S103F2 STM8S103F3/K3](https://www.st.com/resource/en/datasheet/stm8s103f3.pdf)
* [STM8S903F3/K3](https://www.st.com/resource/en/datasheet/stm8s903f3.pdf)

Note that using this configuration for the [STM8S001J3](https://www.st.com/resource/en/datasheet/stm8s001j3.pdf) is possible but not recommended: `PD1/SWIM` and `PD5/UART_TX` share pin8 and recovering from a software problem may not be possible. Please use the [STM8S001J3 configuration](https://github.com/TG9541/stm8ef/tree/master/STM8S001J3) instead.

## STM8 eForth Programming

Most of the STM8S (RM0016) peripheral registers addresses are the same across "Low density" and "Medium" or "High density" devices and device independent code can be written by using [`\res MCU: STM8S`](https://github.com/TG9541/stm8ef/blob/master/mcu/STM8S.efr).

Using e4thcom as a terminal program is recommended. With the help of e4thcom (or codeload.py) `mcu/STM8S.efr` can be used to load peripheral register address constants:

```Forth
\res MCU: STM8S
\res export SPI_CR1 SPI_CR2 SPI_DR SPI_SR
```

Register addresses of TIM2 and TIM4 are different in STM8S "Low Density" devices. Address constants for these peripherals should then be imported with [`\res MCU: STM8S103`](https://github.com/TG9541/stm8ef/blob/master/mcu/STM8S103.efr).

UART constants are again a special case: writing device independent code works best if a sub-set of registers with a `UART_` prefix is used. This can be achieved by using `\res MCU: STM8S103`. The "device independent" `\res MCU: STM8S` can also be used by reassigning constants (e.g. `UART1_DR CONSTANT UART_DR`). More on this in "[Some STM8S peripherals are equal, some are the same](https://hackaday.io/project/16097-eforth-for-cheap-stm8s-gadgets/log/178072-some-stm8s-peripherals-are-equal-some-are-the-same)" on HaD.

## USART Console Settings

STM8S "Low density" devices have just one UART, and only STM8S903 devices can remap the UART from the ordinary `PD5/UART_TX` to `PA3/UART_TX` and `PD6/UART_RX` to `PF4/UART_RX` (the STM8S001J3 technically is a STM8S903 chip but it lacks access to `PF4`).

The STM8S103F3 pin description can also be used for the slightly upgraded STM8S903F3 and for STM8S003F3 "Value Line" devices. There are automotive [STM8AF "Low density" devices](https://github.com/TG9541/stm8ef/wiki/STM8-Low-Density-Devices) with mathing or different pin assignments):

![STM8S103F3](https://user-images.githubusercontent.com/5466977/96366390-b6abe180-1147-11eb-9333-cf47f83759ba.png)

The STM8S903K3 pin functions are a superset of STM8S103K3 (e.g. optional UART pin remapping):
![STM8S903K3](https://user-images.githubusercontent.com/5466977/96366224-7730c580-1146-11eb-90da-1230533a9505.png)

Buffered high speed console communication can be added by following the instructions in [`INTRX`](https://github.com/TG9541/stm8ef/blob/master/lib/INTRX) (refer to the `\\ Example` part of the library word).

### 3-wire serial interface

The default console configuration uses a standard 3-wire serial interface:

```
               .
STM8S device   .
               .
USRT_TX - ----->>----------o serial TxD "TTL"
               .             (e.g. "CH340" USB serial converter)
USRT_RX - ----->>----------o serial RxD "TTL
               .
GND ----------->>----------o serial GND
               .
```
Note that console communiaction is actually half-duplex (i.e., the device either processes a command while sending characters on the serial interface, or it listens for the next command).  

### 2-wire serial interface

The STM8S "Low density" UART (`UART1`) supports a 2-wire mode which can be configured by by setting `HAS_HALFDUPLEX = 1` in `globconf.inc` the selected USART_TX switches betweens TX and RX:

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
```

This feature frees up a GPIO for other uses, or it can be used for creating a simple bus.

It's also possible to use a simulated serial interface (also in addition to the UART) - please refer to the [SWIMCOM](https://github.com/TG9541/stm8ef/tree/master/SWIMCOM) or the [DOUBLECOM](https://github.com/TG9541/stm8ef/tree/master/DOUBLECOM) configurations.
