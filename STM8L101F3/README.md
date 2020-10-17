# STM8L101F3P6 Base Image

This folder contains the configuration for the sub-family of STM8L "Low density" devices described in [RM0013](https://www.st.com/content/ccc/resource/technical/document/reference_manual/73/41/6f/b1/fd/45/4e/18/CD00184503.pdf/files/CD00184503.pdf/jcr:content/translations/en.CD00184503.pdf) with 8K Flash ROM and 1.5K RAM (plus 64 option bytes). Compared to other STM8L devices they have more RAM but a much reduced feature set (no ADC, no RTC, no DMA, no EEPROM ... see below).

The following datasheets apply:

* [STM8L101F1, STM8L101F2/G2 and STM8L101F3/G3/K3](https://www.st.com/resource/en/datasheet/stm8l101f1.pdf)
* [STM8L001J3M3](https://www.st.com/resource/en/datasheet/stm8l001j3.pdf)

The STM8L101 family basically consists of one chip with 20pin, 28pin and 32pin package options. The STM8L101F3P6 (TSSOP20 package) is widely available.

Several differences between the STM8L101 and other STM8L devices (e.g. option bytes) delayed support by STM8 eForth for a long time. [Using OpenOCD](https://hackaday.io/project/16097-eforth-for-cheap-stm8s-gadgets/log/184032-openocd-config-files-for-stm8l-low-density-devices) changed that and STM8 eForth now supports NVM, the TIM2 based BG task and the simulated serial interface. The ordinary workflows can be used.

## The STM8L101 STM8L sub-family

STM8L101 devices provide 1.5K RAM which means that there is more headroom than in the other STM8 Low Density devices. On the other side the feature set is much reduced compared to RM0031 devices (e.g. STM8L051F3):

* no ADC (two comparators are the only analog peripherals)
* advanced features from other STM8L devices (e.g. DMA, RTC, RI) are absent
* Data Flash area instead of a dedicated EEPROM blocks
* Option bytes and the STM8L Option bytes block MASS can only be unlock through ICP (SWIM), not through the CPU
* only few clock options (e.g. no HSE, no LSE, no LSI (38kHz) as CPU clock and no clock fail-over)


## STM8 eForth Programming

Using e4thcom as a terminal program is recommended. With the help of e4thcom (or codeload.py) `mcu/STM8L101.efr` can be used for loading STM8L101 peripheral register address constants:

```Forth
\res MCU: STM8L101
\res AWU_CSR AWU_APR AWU_TBR
```

### Using the STM8L001J3M3

**Warning**: support for the STM8L001J3M3 is experimental!

The STM8L001J3M3 is the same chip in an SOP-8 package where up to 3 GPIOs share one pin:

![stm8l001j3m3_](https://user-images.githubusercontent.com/5466977/95388369-79975200-08f2-11eb-9638-21cc8b1a247d.png)

There's been some testing but using this image may brick your chip since PA0/SWIM shares pin1 with PC3/UART_TX and with PC4. The PC3/USART_TX doesn't have a half-duplex feature like the STM8S UART1 and there is no PA1/NRST pin to back you up!
!

It's maybe a good idea to test your software with an STM8L101F3P6 first (connect PA0, PC3 and PC4 and it will behave like an STM8L001J3M3)!

### Using the STM8L101F3M6

The TX pin uses default GPIO settings (i.e. it requires a pull-up) in order to make the binary work with the STM8L001J3M3.

By uncommenting the BSET lines in `boardcore.inc` PC3/USART_TX will work without an external pull-up:

```
BOARDINIT:
        ; Clock init: enable TIM2 and USART clock
        MOV     CLK_PCKENR1,#0x21
        ; Board I/O for UART: enable USART push/pull (careful with STM8L001J3!)
        BSET    PC_DDR,#3        ; TX->PC3, RX->PC2
        BSET    PC_CR1,#3
        RET
```

When using the above code in an STM8L001J3M3 you will have to re-enable PA0/SWIM through the Forth console. This is, of course, no longer an option when using start-up code that makes the Forth console inaccessible.
