# STM8L101F3P6 Base Image

This folder contains expertimental support for the STM8L Low Density devices [STM8L101F3P6](https://www.st.com/resource/en/datasheet/stm8l101f1.pdf) and [STM8L001J3M3](https://www.st.com/resource/en/datasheet/stm8l001j3.pdf) (described in [RM0013](https://www.st.com/content/ccc/resource/technical/document/reference_manual/73/41/6f/b1/fd/45/4e/18/CD00184503.pdf/files/CD00184503.pdf/jcr:content/translations/en.CD00184503.pdf)). This sub-family of STM8L devices has 1.5K RAM, which means that there is a bit more headroom than the 1K that other Low Density devices but there is no dedicated EEPROM. There is a comparator but there is no ADC. Clock options are much reduced, e.g. there is no HSE, no 38kHz CPU clock and no clock fail-over. Advanced features from other STM8L devices (e.g. DMA, RTC, RI) are absent.

**Warning**: The usage of this image on an STM8L001J3M3 is even more experimental! There's been some testing but using this image may brick your chip since PA0/SWIM shares pin1 with PC3/UART_TX and with PC4, and there is no PA1/NRST pin!

It's recommended to test the this code with an STM8L101F3P6 configured to behave like an STM8L001J3M3 first!

Otherwise, most things, including NVM, the TIM2 based BG task and the simulated serial interface have been tested.

![stm8l101f3p6_](https://user-images.githubusercontent.com/5466977/93720666-d7a20680-fb8a-11ea-88c0-6cb7e09e1f20.png)

In order to make the binary compatible with the STM8L001J3M3 the TX pin uses default GPIO settings (i.e. it requires a pull-up).

By uncommenting the BSET lines in `boardcore.inc` the need for a pull-up can be removed, but this may mean that need to re-enable PA0/SWIM through the Forth console:

```

BOARDINIT:
        ; Clock init: enable TIM2 and USART clock
        MOV     CLK_PCKENR1,#0x21
        ; Board I/O for UART: enable USART push/pull (careful with STM8L001J3!)
        BSET    PC_DDR,#3        ; TX->PC3, RX->PC2
        BSET    PC_CR1,#3
        RET
```

Using e4thcom as a terminal program is recommended. With the help of e4thcom (or codeload.py) `mcu/STM8L101.efr` can be used for loading STM8L101 peripheral register address constants:

```Forth
\res MCU: STM8L101
\res AWU_CSR AWU_APR AWU_TBR
```
