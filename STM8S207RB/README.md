## STM8 eForth "STM8S207RB" configuration

This folder contains the STM8 eForth configuration files for an STM8S207RB breakout board.

![STM8S207RB](https://camo.githubusercontent.com/7e004d7f26e26268c70e227df98aa8e561f4da5b/68747470733a2f2f696d672e73746174696362672e636f6d2f7468756d622f766965772f6f6175706c6f61642f62616e67676f6f642f696d616765732f45302f31392f65643166663938372d613834322d346634382d383464362d3639363234303564656633332e6a706567)

For around $4 this board offers 6K RAM, 2K EEPROM and up to 32 "NVM Forth Flash" (which is a lot for STM8 eForth). It also provides additional 96K Flash "far memory", 2 UARTs and many GPIOs.

The binary release contains the image STM8S207RB which can be used for any High Density device since it communicates through the 2nd UART (i.e. it's also compatible with STM8S207Kx devices in a QLFP32 package - the first UART can be selected as a build option).

Documenation for this board is in the [Wiki](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards#stm8s207rbt6-breakout-board).
