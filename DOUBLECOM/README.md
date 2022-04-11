## STM8 eForth "DOUBLECOM" configuration

This folder contains a full-featured STM8 eForth configuration for an STM8S "Low density" device like the STM8S103F3P6 that communicates through a half-duplex simulated serial interface but that also provides the words `?RX` and `TX!` for the STM8 UART hardware that are independent of the Forth console. The binary release contains the image DOUBLECOM simulates a 2-wire half-duplex communications interface on PD1/SWIM.

The condiguration is a good starting point for developing simple RS232 protocols in Forth, especially with boards like the [C0135](https://github.com/TG9541/stm8ef/tree/master/C0135), and it's an example for "advanced" serial interface configuration in STM8 eForth.

Please refer to the local [globconf.inc]( https://github.com/TG9541/stm8ef/blob/master/DOUBLECOM/globconf.inc) for details.

The recommended circuit for connection to a USB RS232 "TTL" adapter is this:

```
STM8 device    .      .----o serial TxD "TTL"
               .      |      (e.g. "PL2303" USB serial converter)
               .     ---
               .     / \  1N4148
               .     ---
ICP header     .      |
               .      *----o serial RxD "TTL
               .      |
STM8 PD1/SWIM-->>-----*----o ST-LINK SWIM
               .
NRST----------->>----------o ST-LINK NRST
               .
GND------------>>-----*----o ST-LINK GND
               .      |
................      .----o serial GND
```

[e4thcom](https://github.com/TG9541/stm8ef/wiki/STM8S-eForth-Programming#using-e4thcom) fully supports STM8EF 2 wire connections, and an example `picocom` configuration for half-duplex communication is described [here](https://github.com/TG9541/stm8ef/wiki/STM8S-eForth-Programming#using-file--hand).
