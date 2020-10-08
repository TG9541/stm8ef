# STM8L101F3P6 Base Image

This "board folder" provides support for the [STM8L101F3P6](https://www.st.com/resource/en/datasheet/stm8l101f1.pdf) and [STM8L001J3M3](https://www.st.com/resource/en/datasheet/stm8l001j3.pdf) Low Density devices of the [RM0013](https://www.st.com/content/ccc/resource/technical/document/reference_manual/73/41/6f/b1/fd/45/4e/18/CD00184503.pdf/files/CD00184503.pdf/jcr:content/translations/en.CD00184503.pdf) STM8L sub-family.

Differences between the STM8L101 and other STM8L devices (e.g. option bytes), resulting in problems with programming tools, delayed support by STM8 eForth for a long time. [Using OpenOCD](https://hackaday.io/project/16097-eforth-for-cheap-stm8s-gadgets/log/184032-openocd-config-files-for-stm8l-low-density-devices) changed that. Core features now including NVM, the TIM2 based BG task and the simulated serial interface.

## The STM8L101 family

STM8L101 devices provide 1.5K RAM, which means that there is more headroom than in the other STM8 Low Density devices.

On the other side the feature set is much reduced

* Data Flash instead of dedicated EEPROM cells
* Option bytes and the STM8L OPT EEPROM block MASS can only be unlock through ICP (SWIM), not through the CPU
* no ADC (two comparators are the only analog peripherals)
* only few clock options (e.g. no HSE, no LSE, no LSI (38kHz) as CPU clock and no clock fail-over)
* advanced features from other STM8L devices (e.g. DMA, RTC, RI) are absent

STM8L051F3 or STM8L050J3 chips from the RM0031 sub-family certainly offer more features.

The STM8L101 family basically consists of one chip with 20pin, 28pin and 32pin package options. The STM8L101F3P6 (TSSOP20 package) is widely available:

![stm8l101f3p6_](https://user-images.githubusercontent.com/5466977/93720666-d7a20680-fb8a-11ea-88c0-6cb7e09e1f20.png)


The STM8L001J3M3 is the same chip in an SOP-8 package where up to 3 GPIOs share one pin:

![stm8l001j3m3_](https://user-images.githubusercontent.com/5466977/95388369-79975200-08f2-11eb-9638-21cc8b1a247d.png)


There's been some testing but using this image may brick your chip since PA0/SWIM shares pin1 with PC3/UART_TX and with PC4. The PC3/USART_TX doesn't have a half-duplex feature like the STM8S UART1 and there is no PA1/NRST pin to back you up!
!

It's maybe a good idea to test your software with an STM8L101F3P6 first (connect PA0, PC3 and PC4 and it will behave like an STM8L001J3M3)!

**Warning**: support for the STM8L001J3M3 is experimental!

## STM8 eForth Programming

Using e4thcom as a terminal program is recommended. With the help of e4thcom (or codeload.py) `mcu/STM8L101.efr` can be used for loading STM8L101 peripheral register address constants:

```Forth
\res MCU: STM8L101
\res AWU_CSR AWU_APR AWU_TBR
```

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
