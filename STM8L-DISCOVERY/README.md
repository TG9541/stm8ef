# STM8L-DISCOVERY

This is a board support folder for the STM8L-Discovery demo board with an STM8L152C6 device and an LCD.

The code in this folder is the work of @plumbum!

## STM8 eForth Programming

Peripheral register addresses are assumed to be the same throughout the STM8L Medium density and High density devies. Addresses imported from `\res MCU: STM8L` will work (but obviously "High density only" peripherals can't be used). If you spot a problem please file an issue.

Using e4thcom as a terminal program is recommended. With the help of e4thcom (or codeload.py) `mcu/STM8L101.efr` can be used for loading STM8L051 peripheral register address constants:

```Forth
\res MCU: STM8L
\res SYSCFG_RMPCR1 CLK_PCKENR1
```

## USART Console Settings

The following options in `globconf.inc` controlls port assignments options of the USART:

* `ALT_USART_STM8L = 0`: USART_TX on PC3 and USART_RX on PC2 (default)
* `ALT_USART_STM8L = 1`: USART_TX on PA2 and USART_RX on PA3
* `ALT_USART_STM8L = 2`: USART_TX on PC6 and USART_RX on PC5

The USART can be configured as `HAS_HALFDUPLEX`: by setting `HAS_HALFDUPLEX = 1` in `globconf.inc` the selected USART_TX switches betweens TX and RX:

```
               .
STM8L device   .      .----o serial TxD "TTL"
               .      |      (e.g. "CH340" USB serial converter)
               .     ---
               .     / \  1N4148
               .     ---
               .      |
USART_TX     -->>-----*----o serial RxD "TTL
               .
GND------------>>----------o serial GND
               .
               .
```

This feature can free up one more GPIO for other uses, or it can be used for creating a simple bus.

Of course, it's also possible to use a simulate

## I2C

If you want to use I2C the jumper SB17 needs to be opened since I2C is in conflict with the User Button.

Connect I2C bus to:

* PC0 [I2C_SDA]
* PC1 [I2C_SCL]

## LCD

Basic functions integrated into `boardcore.inc`.

* LCDF ( b -- ) \ Fill LCD display with value.
* LCD! ( w a -- ) \ Write code `w` to LCD position `a[0:5]`.

You can enable or disable it with `HAS_LCD` constant in `globconf.inc`.

* HAS_LCD=0 - disable.
* HAS_LCD>0 - enable. Value use by LCDF.

```
\ Display 'STM8EF'
0 lcdf
$00ed 0 lcd! \ S
$1201 1 lcd! \ T
$0536 2 lcd! \ M
$00ff 3 lcd! \ 8
$0079 4 lcd! \ E
$0071 5 lcd! \ F
```
