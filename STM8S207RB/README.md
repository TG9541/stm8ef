## STM8 eForth "STM8S207RB" configuration

This folder contains the STM8 eForth configuration for STM8S207 and STM8S208 High Density devices, e.g. generic breakout boards (also STM8AF High Density devices).

The binary release contains the image STM8S207RB which can be used for any High Density device since it communicates through the 2nd UART (i.e. it's also compatible with STM8S207Kx devices in a LQFP-32 package). The first UART can be selected as a build option.

Device|Package|pin RX-1 ‡|pin Tx-1 ‡|pin RX-2|pin TX-2
-|-|-|-|-|-
STM8S207Kx|LQFP-32|-|-|**31**|**30**
STM8S207Sx|LQFP-44|9|10|**43**|**42**
STM8S207Cx|LQFP-48|10|11|**47**|**46**
STM8S207Rx|LQFP-64|10|11|**63**|**62**
STM8S207Mx|LQFP-80|10|11|**79**|**78**

**‡**: Note: to configure the Forth console to use the first UART (UART1) apply the following settings in `globconf.inc`:

```Forth
        HALF_DUPLEX      = 0    ; Use UART in half duplex mode
        USE_UART2        = 0    ; Use the 2nd UART for the console (STM8S207: optional)
        HAS_TXUART       = 1    ; Use UART TXD, word TX!
        HAS_RXUART       = 1    ; Use UART RXD, word ?RX
```

![STM8S207RB](https://camo.githubusercontent.com/7e004d7f26e26268c70e227df98aa8e561f4da5b/68747470733a2f2f696d672e73746174696362672e636f6d2f7468756d622f766965772f6f6175706c6f61642f62616e67676f6f642f696d616765732f45302f31392f65643166663938372d613834322d346634382d383464362d3639363234303564656633332e6a706567)

STM8S207RB breakout boards, like the one above for around $4, offer 6K RAM, 2K EEPROM and 32K "Forth Flash" (which is quite a lot for STM8 eForth). It also provides additionally 96K "far flash memory", 2 UARTs and many GPIOs.

Documenation for this board is in the [Wiki](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards#stm8s207rbt6-breakout-board).
