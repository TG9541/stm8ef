# Notes on XY-LPWM

The board support code in this folder was contributed by @plumbum. It uses the serial interface pin header for console communication and provides code for writing text to the LCD.

The GitHub project [STM8S eForth XY-LPWM](https://github.com/TG9541/XY-LPWM) is based on the code here. It provides full background task LCD and key support and it enables the original use case by freeing up the UART for a bus protocol, e.g. MODBUS or even for supporting the original (rather minimalistic) XY-LPWM protocol. TIM1 is used for the background task so that TIM2 can be used for PWM.

When you order a XY-LPWM board today expect it to have a N76E003AT20 chip. It's still a good hacking target since the Nuvoton chip is easy to replace with an STM8S003F3P6.

## Hardware

![XY-LPWM](https://raw.githubusercontent.com/wiki/plumbum/stm8ef/helo_forth.jpg)

J3 ICP Pin|Signal
-|-
1|+3.3V (supply)
2|NRST
3|PD1/SWIM
4|STM8S003F3P6 Vcap (do not connect)
5|GND
