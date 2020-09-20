# STM8L101F3P6 Base Image

Expertimental image for STM8L101F3P6. Most things, including NVM and the BG task should work.

The STM8L101F3P6 has 1.5K RAM, which means that it has a bit more headroom than in other Low Density devices. On the other side there is no ADC and no dedicated EEPROM, and other peripherals are missing, too.  

![stm8l101f3p6_](https://user-images.githubusercontent.com/5466977/93720666-d7a20680-fb8a-11ea-88c0-6cb7e09e1f20.png)

The STM8L001J3M3 is even more experimental - it may brick your chip!.

In order to make the binary compatible with the STM8L001J3M3 the TX pin uses low-side GPIO settings (i.e. it requires a pull-up).
