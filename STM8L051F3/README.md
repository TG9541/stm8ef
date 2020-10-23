# STM8L051F3 Base Image

This folder contains the configuration for STM8L "Low density" devices as described in [RM0031](https://www.st.com/resource/en/reference_manual/cd00218714-stm8l050j3-stm8l051f3-stm8l052c6-stm8l052r8-mcus-and-stm8l151l152-stm8l162-stm8al31-stm8al3l-lines-stmicroelectronics.pdf) with 8K Flash ROM, 1K RAM and 256 bytes EEPROM (plus 64 option bytes). Compared to other STM8 "Low density" devices they provide a richer set of peripherals (e.g. 12bit ADC, DMA and RTC).

The following datasheets apply:

* [STM8L151C3/K3/G3/F3 and STM8L151C2/K2/G2/F2](https://www.st.com/resource/en/datasheet/stm8l151f3.pdf)
* [STM8L051F3P6](https://www.st.com/resource/en/datasheet/stm8l051F3.pdf)
* [STM8L050J3M3](https://www.st.com/resource/en/datasheet/stm8l050j3.pdf)

![stm8l051f3p6](https://user-images.githubusercontent.com/5466977/40583511-8462f470-6190-11e8-8674-84338a991f58.png)

STM8L "Low density" devices in the sub-families RM0013 (STM8L101) or RM0312 (STM8TL5xxx) are [substantially different](https://github.com/TG9541/stm8ef/tree/master/STM8L101F3).

## STM8 eForth Programming

Peripheral register addresses of RM0031 "Low density" devices differ from STM8L "Medium density" and "High density" devices. Constants should be imported with `\res MCU: STM8L051`.  If you spot a problem please file an issue.

Using e4thcom as a terminal program is recommended. With the help of e4thcom (or codeload.py) `mcu/STM8L101.efr` can be used for loading STM8L051 peripheral register address constants:

```Forth
\res MCU: STM8L051
\res SYSCFG_RMPCR1 CLK_PCKENR1
```

## USART Console Settings

By default `globconf.inc` configures the USART interface for the STM8L051F3 to `PA2/USART_TX` and `PA3/2/USART_RX` in order to support the LSE clock feature (which needs `PC5` and `PC6` for the 32.768kHz crystal).

Pin|GPIO|Function
-|-|-
1|PC5|USART_TX
2|PC6|USART_RX
3|PA0|SWIM
4|PA1|NRST
5|PA2|[USART_TX]
6|PA3|[USART_RX]

The following options in `globconf.inc` control alternative port assignments of USART:

* `ALT_USART_STM8L = 0`: USART_TX on PC5 and USART_RX on PC6
* `ALT_USART_STM8L = 1`: USART_TX on PA2 and USART_RX on PA3 (default)
* `ALT_USART_STM8L = 2`: USART_TX on PC3 (NC) and USART_RX on PC2 (NC)

Note that Table 4 in the [STM8L151C3 datasheet](https://www.st.com/resource/en/datasheet/stm8l151c3.pdf) lists different options for remapping the UART pin functions, some of which don't match the description in SYSCFG_RMPCR2 bits 5:4 in RM0031. The options `0` and `1` above were tested with STM8L051F3 - it's possible that other chips have the order of `0` and `2` swapped.

The USART can be configured as `HAS_HALFDUPLEX`: by setting `HAS_HALFDUPLEX = 1` in `globconf.inc` the selected USART_TX switches betweens TX and RX:

```
               .
STM8L device   .      .----o serial TxD "TTL"
               .      |      (e.g. "CH340" USB serial converter)
               .     ---
               .     / \  1N4148
               .     ---
               .      |
USART_TX ------>>-----*----o serial RxD "TTL
               .
GND ----------->>----------o serial GND
               .
               .
```

This feature can free up one more GPIO for other uses, or it can be used for creating a simple bus.

Of course, it's also possible to use a simulated serial interface (also in addition to a USART) which results in even more options for a Forth console.

## STM8L050J3M3 considerations

The STM8L050J3 has many more configuration options than the other STM8 devices in a SOIC-8 package (STM8L001J3 and STM8S001J2).

![stm8l050j3m3](https://user-images.githubusercontent.com/5466977/95416097-3bba1e00-0932-11eb-9df1-aa5dfba2b688.png)

The STM8L050J3 doesn't provide access to `PA0/NRST` and there is always the risk of blocking access to `PA1/SWIM` by configuring a GPIO bonded-out to pin1 to output, and that includes `PA2/USART_TX`. A safe half-duplex option can be selected by setting `HAS_HALFDUPLEX = 1` in `globconf.inc`. Alternatively `PC5/USART_TX` can be used (which is on pin8 and that's "safe" anyway).

**Warning**: support for the STM8L050J3M3 is experimental!
