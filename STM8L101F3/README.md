# STM8L101F3P6 Base Image

This is the base configuration for STM8L [RM0013](https://www.st.com/content/ccc/resource/technical/document/reference_manual/73/41/6f/b1/fd/45/4e/18/CD00184503.pdf/files/CD00184503.pdf/jcr:content/translations/en.CD00184503.pdf) "Low density" devices family with 8K Flash ROM, 1.5K RAM and 64 option bytes (no IAP).

The following datasheets apply:

* [STM8L101F1, STM8L101F2/G2 and STM8L101F3/G3/K3](https://www.st.com/resource/en/datasheet/stm8l101f1.pdf)
* [STM8L001J3M3](https://www.st.com/resource/en/datasheet/stm8l001j3.pdf)

Compared to RM0031 STM8L or RM0016 STM8S "Low density" devices the RM0013 chip provides more RAM. Otherwise the feature set is considerably reduced (no ADC, RTC, DMA or EEPROM ...). Unless you need more RAM or a comparator (or simple configuration is a plus) the STM8L051F3 may be a better choice.

Differences between the STM8L101 and other STM8L devices have long delayed STM8 eForth support. Using [OpenOCD](https://hackaday.io/project/16097-eforth-for-cheap-stm8s-gadgets/log/184032-openocd-config-files-for-stm8l-low-density-devices) changed that. Main features are supported, e.g., NVM programming, TIM2 based BG task or the simulated serial interface. The normal STM8 eForth workflow can be used.

## The STM8L101 STM8L family

The STM8L101 family consists of one chip with package options from 8 to 32 pin. The STM8L101F3P6 (TSSOP20) is widely available and relatively cheap. STM8L101 devices provide 1.5K RAM, considerably more than the 1K in other STM8 "Low density" devices.

Compared to RM0031 STM8L "Low density" devices (e.g. STM8L051F3) the feature set is much smaller:

* no ADC (analog peripherals limited to two comparators)
* no advanced features like DMA, RTC, RI)
* no USART half-duplex mode
* no dedicated EEPROM (replaced with Data Flash)
* no IAP for "option bytes" (unlocking requires ICP through PA0/SWIM)
* few clock options (e.g. no HSE, no LSE, no LSI CPU clock)
* no clock safety features and only one watchdog

On the plus side, configuration is easier (because there is less to be configured). There is an AWU (Auto Wakeup Unit) resembling that in the STM8S family.


## STM8 eForth Programming

Using e4thcom as a terminal program is recommended. With the help of e4thcom (or codeload.py) `mcu/STM8L101.efr` can be used for loading STM8L101 peripheral register address constants:

```Forth
\res MCU: STM8L101
\res AWU_CSR AWU_APR AWU_TBR
```

### Using the STM8L101F3M3

In order to make the binary work with the STM8L001J3M3 the TX pin uses default GPIO settings which may mean that it requires a small external pull-up.

![stm8l101f3](https://user-images.githubusercontent.com/5466977/216818185-c99d6860-7e7e-4bf7-b640-86faa5106ca2.png)

By uncommenting the BSET lines in `boardcore.inc` PC3/USART_TX will work without the pull-up:

```
BOARDINIT:
        ; Clock init: enable TIM2 and USART clock
        MOV     CLK_PCKENR1,#0x21
        ; Board I/O for UART: enable USART push/pull (careful with STM8L001J3!)
        BSET    PC_DDR,#3        ; TX->PC3, RX->PC2
        BSET    PC_CR1,#3
        RET
```

### Using the STM8L001J3M3

**Warning**: support for the STM8L001J3M3 is experimental!

**Warning**: when using an image with active USART GPIO pull-up in an STM8L001J3M3 ICP through PA0/SWIM needs to be re-enabled with the Forth console. This won't work when a bug disables the console and your chip may be lost.

The STM8L001J3M3 is the same chip in an SOP-8 package where up to 3 GPIOs share a pin:

![stm8l001j3m3](https://user-images.githubusercontent.com/5466977/95388369-79975200-08f2-11eb-9638-21cc8b1a247d.png)

Some testing with the STM8L101F3 image has been done but since PA0/SWIM shares pin1 with PC4 and PC3/UART_TX the risk remains that it renders your chip unusable. Unlink the other 8pin chips STM8L050J3M3 or STM8S001J3M3 the USART doesn't have a half-duplex feature and there is no PA1/NRST pin to back you up!

If possible test your software with an STM8L101F3P6 first. If PA0, PC3 and PC4 are connected it will behave like an STM8L001J3M3.
