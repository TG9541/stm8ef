# STM8S001J3M3 and STM8S Low Density Half-Duplex Base Image

This folder contains a special "half-duplex" UART configuration for the STM8S "Low density" device [STM8S001J3](https://www.st.com/resource/en/datasheet/stm8s001J3.pdf) but it can also be used with other STM8S "Low density" devices like STM8L003F3. As described [in the Wiki](https://github.com/TG9541/stm8ef/wiki/STM8-Low-Density-Devices#stm8s001j3) it behaves like an STM8S903x3 chip with 1 to 4 GPIOs bonded to the same pin. Out of 8 pins, 3 are used for the power supply (Vss, Vdd, and Vcap, and since NRST was sacrificed, 5 pins are connected to GPIOs. STM8S903 features like upgraded timers the reference voltage source can be expected to work.

ST provides a breakout board as a [reference design](https://community.st.com/docs/DOC-1565-my-project) (an alternative is [described in the Wiki](https://github.com/TG9541/stm8ef/wiki/Breakout-Boards#homemade-stm8s001j3m3-breakout-board)).

![stm8s001j3m3-breakout](https://user-images.githubusercontent.com/5466977/31315055-d1cd1eac-ac0f-11e7-89d4-184a421e783f.jpg)


## USART Console Settings

The UART uses `HAS_HALFDUPLEX` mode (through `HAS_HALFDUPLEX = 1` in `globconf.inc`). This means that `PD5/UART_TX` switches betweens TX and RX. Normal serial communication with the STM8 eForth console can be achieved using a simple diode (e.g. 1N4148 but any ordinary diode can be used):

```
               .
STM8S001J3M3   .      .----o serial TxD "TTL"
               .      |      (e.g. "CH340" USB serial converter)
               .     ---
               .     / \  1N4148
               .     ---
               .      |
pin8 UART_TX--->>-----*----o serial RxD "TTL
               .
GND ----------->>----------o serial GND
               .
               .
```

![image](https://user-images.githubusercontent.com/5466977/96503648-e0eac580-1253-11eb-9f5f-7f3724e99d13.png)

Half-duplex operation not only makes sharing pin8 between `PD1/SWIM` and `PD5/UART_TX` safe but it also frees up a pin for applications. Note that the UART_TX function can be remapped from `PD5` to `PA3` by setting an option byte OPT2[1:0] to "3" . This can be done  with the help of the `OPT!` word in the library:

```Forth
#require OPT!
\res MCU: STM8S103
\res export OPT2
3 OPT2 OPT!
\ a reset will be required!
```

STM8 eForth will automatically configure the GPIO pull-up for the selected pin.

Of course, it's also possible to use a simulated serial interface instead of the UART. This way the UART can be freed up, e.g. for [MODBUS RTU](https://github.com/TG9540/stm8ef-modbus).

Note: it's possible to use the STM8S001J3M3 with the `CORE` or the `MINDEV` binary, but that's not recommended: as soon as pin8 operates as `UART1_TX`, access to `PD1/SWIM` for ICP programming is blocked. It's possible to disable the UART through the STM8 eForth console and regain access to `PD1/SWIM` but, of course, only as long as access to the console works!
