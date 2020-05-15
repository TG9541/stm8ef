# Notes on XY-LPWM

The board support code in this folder is the work of @plumbum. It uses the serial interface pin header for console communication and provides code for writing text to the LCD. 

If you order a XY-LPWM board today expect it to have a N76E003AT20 chip. It's still worth it since the Nuvoton chip is easy to replace with an STM8S003F3P6.

There is now also a [STM8S eForth XY-LPWM](https://github.com/TG9541/XY-LPWM) project that enables the original use case (e.g. free up the UART for MODBUS or even for the original protocol, TIM1 for the background task, full background task LCD support). 

## Hardware

![XY-LPWM](https://raw.githubusercontent.com/wiki/plumbum/stm8ef/helo_forth.jpg)

J3 ICP Pin|Signal
-|-
1|+3.3V (supply)
2|NRST
3|PD1/SWIM
4|STM8S003F3P6 Vcap (do not connect)
5|GND
