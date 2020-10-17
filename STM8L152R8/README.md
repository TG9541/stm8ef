# STM8L152R8 Base Image

This folder contains the configuration for STM8L "High density" devices as described in [RM0031](https://www.st.com/resource/en/reference_manual/cd00218714-stm8l050j3-stm8l051f3-stm8l052c6-stm8l052r8-mcus-and-stm8l151l152-stm8l162-stm8al31-stm8al3l-lines-stmicroelectronics.pdf) with 64K Flash ROM, 4K RAM and 2K bytes EEPROM (plus 128 option bytes). Compared to STM8S "High density" devices they provide a richer set of peripherals (e.g. 12bit ADC, 2x 12bit DAC, 2nd SPI, DMA and RTC) but no CAN bus. STM8L152 "High density" devices can drive passive LCDs with up to 8*40 segments (the LCD peripheral is likely inaccessible in STM8L151 devices).

The following datasheets apply:

* [STM8L151C8/M8/R8 and STM8L152C8/K8/M8/R8](https://www.st.com/resource/en/datasheet/stm8l152r8.pdf)
* [STM8L052R8](https://www.st.com/resource/en/datasheet/stm8l052r8.pdf)

All variants should work with the STM8L152R8 binary in the Releases section (likely it's also usable for automotive grade STM8L "High density" devices).

Note that the "Medium+ density" device STM8L151R6 appears to be a "marketing name" for a lower-specs "High density" device (at least that's what Chinese vendors [say](https://www.aliexpress.com/item/32881789448.html)). Best you try it. If it doesn't work, please fall back to the STM8L151K4 image and provide [feedback](https://github.com/TG9541/stm8ef/issues).

LCD support for the [STM8L-DISCOVERY](https://github.com/TG9541/stm8ef/tree/master/STM8L-DISCOVERY) by @plumbum is provided as-is (it's untested and disabled in `globconf.inc`).

## STM8 eForth Programming

Peripheral register addresses are expected to be the same throughout the STM8L "Medium density" and "High density" devies and constants imported from `\res MCU: STM8L` should work.  If you spot a problem please file an issue.

Using e4thcom as a terminal program is recommended. With the help of e4thcom (or codeload.py) `mcu/STM8L101.efr` can be used for loading STM8L051 peripheral register address constants:

```Forth
\res MCU: STM8L
\res SYSCFG_RMPCR1 CLK_PCKENR1
```

## USART Console Settings

The STM8L152R8T6 (LQFP64 package) offers 6 possibilities for mapping a USART to pins.

![image](https://user-images.githubusercontent.com/5466977/95511446-c7c25900-09b7-11eb-8bc4-69e407a58602.png)

Pin|GPIO|Function
-|-|-
1|PA0|SWIM
2|PA1|NRST
3|PA2|[USART1_TX]
4|PA3|[USART1_RX]
14|PG0|USART3_RX
15|PG1|USART3_TX
22|PE3|USART2_RX
23|PE4|USART2_TX
39|PF0|[USART3_TX]
40|PF1|[USART3_RX]
57|PC2|USART1_RX (default)
58|PC3|USART1_TX (default)
60|PC5|[USART1_TX]
61|PC6|[USART1_RX]

The default USART for the Forth console is USART1. That can be changed by setting `USE_UART2 = 1` or `USE_UART3 = 1` in `globconf.inc`.

The following options in `globconf.inc` controll alternative port assignments of the selected USART:

If the default USART is used:
* `ALT_USART_STM8L = 0`: USART1_TX on PC3 and USART1_RX on PC2 (default)
* `ALT_USART_STM8L = 1`: USART1_TX on PA2 and USART1_RX on PA3
* `ALT_USART_STM8L = 2`: USART1_TX on PC5 and USART1_RX on PC6

If USART2 is used (`USE_UART2 = 1`):
* `ALT_USART_STM8L` has no effect

If USART3 is used (`USE_UART3 = 1`):

* `ALT_USART_STM8L = 0`: USART3_TX on PG1 and USART3_RX on PG0
* `ALT_USART_STM8L = 1`: USART3_TX on PF0 and USART3_RX on PF1

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
