# STM8L152R8 Base Image

This folder contains (experimental) support for STM8L High Density devices like [STM8L151x8/152x8](https://www.st.com/resource/en/datasheet/stm8l152r8.pdf) or the identical (but lower specs "Value Line") [STM8L052R8](https://www.st.com/resource/en/datasheet/stm8l052r8.pdf). Medium+ Density devices (e.g. STM8L15xR6) look suspiciously similar to High Density devices since the set of peripherals is the same (but the specified amount of RAM and EEPROM might indeed be like that of Medium density devices - best you try it and make adjustments in `target.inc` as needed - [feedback]() is always welcome!).

STM8L152R8 stands for "High Density" devices with 4K RAM, 2K EEPROM and up to 64K Flash ROM as described in [RM0031](https://www.st.com/resource/en/reference_manual/cd00218714-stm8l050j3-stm8l051f3-stm8l052c6-stm8l052r8-mcus-and-stm8l151l152-stm8l162-stm8al31-stm8al3l-lines-stmicroelectronics.pdf). All variants should work with the STM8L152R8 binary in the Releases section (likely it's also usable for Automotive Grade STM8L High Density devices).

LCD support is from @plumbum 's work for the [STM8L-DISCOVERY](https://github.com/TG9541/stm8ef/tree/master/STM8L-DISCOVERY) - it's provided as-is and it's currently disabled in `globconf.inc` and untested.

Peripheral register addresses are the same throughout the STM8L Medium Density and High Density devies and constants imported from `\res MCU: STM8L` should work.  If you spot a problem please file an issue.

## USART Console Settings

The default USART for the Forth console is USART1. That can be changed by setting `USE_UART2 = 1` or `USE_UART3 = 1` in `globconf.inc`.

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

Of course, it's also possible to use a simulated serial interface (also in addition to a USART) which results in even more options for a Forth console.
