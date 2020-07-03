# STM8L-DISCOVERY

The code in this folder is the work of @plumbum.

## USART1

Connect Serial-TTL (3.3V limited) to:

* PA2 [USART1_TX]
* PA3 [USART1_RX]

## I2C

If you want to use I2C, you must remove SB17 fuse. I2C conflict with User Button.

Connect I2C bus to:

* PC0 [I2C_SDA]
* PC1 [I2C_SCL]

## LCD

Basic functions integrated to `boardcore.inc`.

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

