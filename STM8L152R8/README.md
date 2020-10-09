# STM8L151K4 Base Image

This folder contains experimental support for STM8L High Density devices like [STM8L151x8/152x8](https://www.st.com/resource/en/datasheet/stm8l152r8.pdf) or the identical (but lower specs "Value Line") [STM8L052R8](https://www.st.com/resource/en/datasheet/stm8l052r8.pdf). Medium+ Density devices (e.g. STM8L15xR6) look suspiciously similar to High Density devices since the set of peripherals is identical (but the specified amount of RAM and EEPROM might indeed be like that of Medium density devices - best you try it and make adjustments in `target.inc` as needed - feedback is always welcome!).

STM8L152R8 stands for "High Density" devices with 4K RAM, 2K EEPROM and up to 64K Flash ROM as described in [RM0031](https://www.st.com/resource/en/reference_manual/cd00218714-stm8l050j3-stm8l051f3-stm8l052c6-stm8l052r8-mcus-and-stm8l151l152-stm8l162-stm8al31-stm8al3l-lines-stmicroelectronics.pdf). All variants should work with the STM8L151K4 binary in the Releases section (likely it's also usable for Automotive Grade STM8L High Density devices).
```
;       STM8L152R8 device and memory layout configuration

        TARGET = STM8L152R8

        RAMEND =        0x0FFF  ; "RAMEND" system (return) stack, growing down
        EEPROMBASE =    0x1000  ; "EESTART" EEPROM start address
        EEPROMEND =     0x17FF  ; "EEEND" 2K EEPROM
        FLASHEND =      0xFFFF  ; 32K Forth + 32K far memory

        FORTHRAM =      0x0030  ; Start of RAM controlled by Forth
        UPPLOC  =       0x0060  ; UPP (user/system area) location for 4K RAM
        CTOPLOC =       0x0080  ; CTOP (user dictionary) location for 4K RAM
        SPPLOC  =       0x0f50  ; SPP (data stack top), TIB start
        RPPLOC  =       RAMEND  ; RPP (return stack top)
```

The default USART for the Forth console is USART1. That can be changed by setting `USE_UART2 = 1` or `USE_UART3 = 1` in `globconf.inc`. Peripheral register addresses are likely the same and constants imported from `\res MCU: STM8L151` should work.  Of course, we'd be happy to hear from you if it works (or help fixing it if it doesn't).

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
57|PC2|USART1_RX
58|PC3|USART1_TX

LCD support is from @plumbum 's work for the [STM8L-DISCOVERY](https://github.com/TG9541/stm8ef/tree/master/STM8L-DISCOVERY) - it's provided as-is and it's currently disabled in `globconf.inc` and untested.
