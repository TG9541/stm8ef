# STM8L151K4 Base Image

This folder contains the configuration for STM8L "Medium density" devices as described in [RM0031](https://www.st.com/resource/en/reference_manual/cd00218714-stm8l050j3-stm8l051f3-stm8l052c6-stm8l052r8-mcus-and-stm8l151l152-stm8l162-stm8al31-stm8al3l-lines-stmicroelectronics.pdf) (or "32 Kbyte die" as described in [UM0470](https://www.st.com/content/ccc/resource/technical/document/user_manual/ca/89/41/4e/72/31/49/f4/CD00173911.pdf/files/CD00173911.pdf/jcr:content/translations/en.CD00173911.pdf)) with 32K Flash ROM, 2K RAM and 1K bytes EEPROM (plus 128 option bytes). Compared to STM8S "Medium density" devices they provide a richer set of peripherals (e.g. 12bit ADC and DAC, DMA and RTC). STM8L152 "Medium density" devices can drive passive LCDs with up to 4*28 segments (the LCD peripheral isn't accessible in STM8L151 devices).

The following datasheets apply:

* [STM8L151C4/K4/G4, STM8L151C6/K6/G6, STM8L152C4/K4/G4, STM8L152C6/K6/G6](https://www.st.com/resource/en/datasheet/stm8l151K4.pdf)
* [STM8L052C6](https://www.st.com/resource/en/datasheet/stm8l052c6.pdf)

The pin and GPIO function overview for the LQFP-32 "K" package is courtesy of @Eelkhorn (author of [STM8-Peripherals Forth](https://github.com/Eelkhoorn/stm8-peripherals-forth):

![image](https://user-images.githubusercontent.com/5466977/95673419-98bf0980-0ba8-11eb-9b5c-be89e0702ab8.png)
:
All STM8L "Medium density" devices (also automotive grade STM8AL devices) should work with the STM8L151K4 binary in the Releases section.

STM8L "High density" devices (e.g. STM8L152R8) provide more memory and a richer set of peripherals. Using the [STM8L152R8](https://github.com/TG9541/stm8ef/tree/master/STM8L152R8) binary is recommended although the `target.inc` provided here will work. Note that "Medium+ density" (e.g. STM8L151R6 and some STM8AL devices) appears to be a "marketing name" for lower-specs "High density" devices (at least that's what Chinese vendors [say](https://www.aliexpress.com/item/32881789448.html)).

For STM8L "Low density" devices described in RM0031 (e.g. STM8L051) a different binary is required (different memory layout/peripheral register addresses).

The code in this folder also contains [STM8L-Discovery_LCD and board support code](https://github.com/TG9541/stm8ef/tree/master/STM8L-DISCOVERY) by @plumbum but it has to be enabled manually in `globconf.inc`.

## STM8 eForth Programming

Peripheral register addresses are assumed to be the same throughout the STM8L Medium density and High density devies. Addresses imported from `\res MCU: STM8L` will work (but obviously "High density only" peripherals can't be used). If you spot a problem please file an issue.

Using e4thcom as a terminal program is recommended. With the help of e4thcom (or codeload.py) `mcu/STM8L101.efr` can be used for loading STM8L051 peripheral register address constants:

```Forth
\res MCU: STM8L
\res SYSCFG_RMPCR1 CLK_PCKENR1
```

## USART Console Settings

The following options in `globconf.inc` controlls port assignments options of the USART:

* `ALT_USART_STM8L = 0`: USART_TX on PC3 and USART_RX on PC2 (default)
* `ALT_USART_STM8L = 1`: USART_TX on PA2 and USART_RX on PA3
* `ALT_USART_STM8L = 2`: USART_TX on PC6 and USART_RX on PC5

The USART can be configured as `HAS_HALFDUPLEX`: by setting `HAS_HALFDUPLEX = 1` in `globconf.inc` the selected USART_TX switches betweens TX and RX:

```
               .
STM8L device   .      .----o serial TxD "TTL"
               .      |      (e.g. "CH340" USB serial converter)
               .     ---
               .     / \  1N4148
               .     ---
               .      |
USART_TX     -->>-----*----o serial RxD "TTL
               .
GND------------>>----------o serial GND
               .
               .
```

This feature can free up one more GPIO for other uses, or it can be used for creating a simple bus.

Of course, it's also possible to use a simulated serial interface (also in addition to a USART) which results in even more options for a Forth console.
