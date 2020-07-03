# STM8 eForth "W1219" configuration

This folder contains the STM8 eForth configuration files for the W1219 thermostat board.

The binary release contains the image W1219, which simulates a 2-wire half-duplex communications interface on PD1/SWIM.

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

Documenation for the W1219 board is in the [Wiki](https://github.com/TG9541/stm8ef/wiki/Board-W1219).
