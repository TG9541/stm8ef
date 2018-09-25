## STM8S001J3M3

The STM8S001J3M3 is a member of the STM8S *low density* family. As described [here](https://github.com/TG9541/stm8ef/wiki/STM8-Low-Density-Devices#stm8s001j3) it behaves very much like an STM8S903x3 chip with 1 to 4 GPIOs bonded to the same pin. Out of 8 pins, 3 are used for the power supply (Vss, Vdd, and Vcap, and since NRST was sacrificed, 5 pins are connected to GPIOs. 

ST provides a breakout board as a [reference design](https://community.st.com/docs/DOC-1565-my-project) (an alternative is [described in the Wiki](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards#homemade-stm8s001j3m3-breakout-board).

![stm8s001j3m3-breakout](https://user-images.githubusercontent.com/5466977/31315055-d1cd1eac-ac0f-11e7-89d4-184a421e783f.jpg)


### Serial Interface

It's possible to use the STM8S001J3M3 with the `CORE` or the `MINDEV` binary, but that's not recommended: as soon as pin8 operates as `UART1_TX` it's no longer possible to access `PD1/SWIM` for ICP programming. Although it's possible to disable the UART, and thus regain access to `PD1/SWIM`, it's much safer to use the `STM8S001J3.ihx` binary. It uses UART1_TX in bi-directional half-duplex mode (2-wire mode communication). With the recommended [2-wire communication circuit](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Programming-Tools#using-a-serial-interface-with-2-wire-communication), and a good serial interface adapter (e.g. PL2303, not CH340/CH341), this provides full console operation, e.g. with picocom, or e4thcom.

Pin STM8S001J3M3|Port|Connect to
-|-|-
2|GND|serial interface "GND"
8|PD1,PD5|SWIM, serial interface "TTL" RxD/TxD

It's also possible to remap `UART1_TX` to pad5 `PA3` with the help of the `OPT!` word in the library.
