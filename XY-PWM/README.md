# XY-PWM board

The board support code in this folder was contributed by @plumbum. It uses the serial interface pin header for console communication .

The hardware is also know as HW-0515.

PWM outputs are notsupported by the STM8 eForth core but you can write your own code in Forth.

## STM8S003F3 pins

```
                         ____________
                        |            |
[PD4] A               --| 1       20 | -- [PD3/TIM2_CH2] PWM1
[PD5] UART1_TX        --| 2       19 | -- [PD2] Seg B
[PD6] UART1_RX        --| 3       18 | -- [PD1] Seg F
NRST                  --| 4       17 | -- [PC7] Seg D
[PA1] Cathode 3       --| 5       16 | -- [PC6] Seg H / Key Down
[PA2] Seg E / Key Set --| 6       15 | -- [PC5] Seg C
[Vss]                 --| 7       14 | -- [PC4] Seg G / Key UP
[Vcap]                --| 8       13 | -- [PC3/TIM1_CH3] PWM2
[Vdd]                 --| 9       12 | -- [PB4] Cathode 2
[PA3] not connected   --| 10      11 | -- [PB5] Cathode 1
                        |____________|
```

## LED pinout


```
                         ____________
                        |    _ _     |
                        |   |_|_|    |
             Seg E    --|   '        |-- Cathode 3
             Seg D    --|    _ _     |-- Seg A
             Seg H    --|   |_|_|    |-- Seg F
             Seg C    --|   '        |-- Cathode 2
             Seg G    --|    _ _     |-- Cathode 1
                        |   |_|_|    |-- Seg B
                        |   '        |
                        |____________|
```

## SWIM pins

* 1 NRST [Square pad]
* 2 GND
* 3 SWIM
* 4 +5V
