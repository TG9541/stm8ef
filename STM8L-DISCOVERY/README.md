# STM8L-DISCOVERY

The code in this folder is the work of @plumbum!

Peripheral register addresses are the same throughout the STM8L Medium Density and High Density devies and constants imported from `\res MCU: STM8L` should work.  If you spot a problem please file an issue.

## USART Console Settings

The following options in `globconf.inc` controlls port assignments options of the USART (TTL, limited to 3.3V):

* `ALT_USART_STM8L = 0`: USART_TX on PC3 and USART_RX on PC2
* `ALT_USART_STM8L = 1`: USART_TX on PA2 and USART_RX on PA3 (default)
* `ALT_USART_STM8L = 2`: USART_TX on PC6 and USART_RX on PC5

The USART can be configured as `HAS_HALFDUPLEX`: this means that the selected USART_TX works alternatively as TX or RX. This feature can free up one more GPIO for other uses.

## I2C

If you want to use I2C, you must remove SB17. I2C is in conflict with the User Button.

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
