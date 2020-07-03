## STM8 eForth "SWIMCOM" configuration

This folder contains the STM8 eForth configuration files for a full-featured system that communicates through a half-duplex simulated serial interface.

The binary release contains the image SWIMCOM, which simulates a 2-wire half-duplex communications interface on PD1/SWIM.

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


