# STM8L151K4 Base Image

This folder contains support for STM8L Medium Density devices like [STM8L151K4](https://www.st.com/resource/en/datasheet/stm8l151r6.pdf).

STM8L151K4 stands for "Medium density" devices with 2K RAM, 1K EEPROM and up to 32K Flash ROM as described in [RM0031](https://www.st.com/resource/en/reference_manual/cd00218714-stm8l050j3-stm8l051f3-stm8l052c6-stm8l052r8-mcus-and-stm8l151l152-stm8l162-stm8al31-stm8al3l-lines-stmicroelectronics.pdf) (or "32 Kbyte die" as described in [UM0470](https://www.st.com/content/ccc/resource/technical/document/user_manual/ca/89/41/4e/72/31/49/f4/CD00173911.pdf/files/CD00173911.pdf/jcr:content/translations/en.CD00173911.pdf)), all of which should work with the STM8L151K4 binary in the Releases section (likely it's also usable for Automotive Grade STM8L Medium Density devices).

![image](https://user-images.githubusercontent.com/5466977/95546354-ab96da00-0a00-11eb-9907-5e89812284ff.png)

Pin|GPIO|Function
-|-|-
32|PA0|SWIM
1|PA1|NRST
2|PA2|[USART1_TX]
3|PA3|[USART1_RX]
27|PC2|USART1_RX
28|PC3|USART1_TX

High Density devices as described in RM0031 (e.g. STM8L152R8) have more memory and a richer set of peripherals. Using the [STM8L152R8](https://github.com/TG9541/stm8ef/tree/master/STM8L152R8) binary is recommended.

Low Density devices described in RM0031 (e.g. STM8L051), RM0013 (e.g. STM8L101) or RM0312 (STM8TL5xxx) use different peripheral register addresses and have a different memory layout. These require a different binary.

The code in this folder also contains [STM8L-Discovery_board support code](https://github.com/TG9541/stm8ef/tree/master/STM8L-DISCOVERY) by @plumbum but it has to be enabled manually in `globconf.inc`.
