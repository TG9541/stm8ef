#STM8L051F3P6 Base Image

This folder contains the configuration fo STML Low Density devices as described in [RM0031](https://www.st.com/resource/en/reference_manual/cd00218714-stm8l050j3-stm8l051f3-stm8l052c6-stm8l052r8-mcus-and-stm8l151l152-stm8l162-stm8al31-stm8al3l-lines-stmicroelectronics.pdf) (e.g. [STM8L051F3P6](https://www.st.com/resource/en/datasheet/stm8l051F3.pdf) or [STM8L050J3M3](https://www.st.com/resource/en/datasheet/stm8l050j3.pdf)). STM8L Low Density devices from the families RM0013 (STM8L101) or RM0312 (STM8TL5xxx) use different peripheral register addresses and have a different memory layout. These require a different binary.

![stm8l051f3p6](https://user-images.githubusercontent.com/5466977/40583511-8462f470-6190-11e8-8674-84338a991f58.png)

Peripheral register addresses of RM0031 Low Density devices differ from STM8L Medium Density and High Density devies. Constants should therefor be imported from `\res MCU: STM8L051`.  If you spot a problem please file an issue.

## USART Console Settings

By default, the USART interface for the STM8L051F3 is configured to support the LSE clock feature (which requires a 32768Hz crystal to be connected to PC5/PC6).

Pin|GPIO|Function
-|-|-
1|PC5|USART_TX
2|PC6|USART_RX
3|PA0|SWIM
4|PA1|NRST
5|PA2|[USART_TX]
6|PA3|[USART_RX]

The following options in `globconf.inc` controll alternative port assignments of USART:

* `ALT_USART_STM8L = 0`: USART_TX on PC5 and USART_RX on PC6
* `ALT_USART_STM8L = 1`: USART_TX on PA2 and USART_RX on PA3
* `ALT_USART_STM8L = 2`: USART_TX on PC3 (NC) and USART_RX on PC2 (NC)

Note that Table 4 in the [STM8L151C3 datasheet](https://www.st.com/resource/en/datasheet/stm8l151c3.pdf) lists different options for remapping the UART pin functions, some of which don't match the description in SYSCFG_RMPCR2 bits 5:4 in RM0031. The options `0` and `1` above were tested with STM8L051F3 - it's possible that other chips have the order of `0` and `2` swapped.

The USART can be configured as `HAS_HALFDUPLEX`: this means that the selected USART_TX works alternatively as TX or RX. This feature can free up one more GPIO for other uses.

## STM8L050J3M3 considerations

The STM8L050J3 has many more configuration options than the STM8L001J3 or the STM8S001J2. Setting `HAS_HALFDUPLEX = 1` in `globconf.inc` is a safe half-duplex option for using `PA2/USART_TX` (which is on pin1 like PA0/SWIM). Alternatively `PC5/USART_TX` can be used (which is on pin8 and that's "safe" anyway).

![stm8l050j3m3](https://user-images.githubusercontent.com/5466977/95416097-3bba1e00-0932-11eb-9df1-aa5dfba2b688.png)
