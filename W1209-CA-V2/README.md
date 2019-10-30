# W1209-CA another variation

This is another variation of the Common Anode W1209 boards which has totally different pin mappings, and a different layout e.g the swim connections are at the side next to the thermistor connection.

The board was introduced in [Issue #275](https://github.com/TG9541/stm8ef/issues/275). Code examples and docs in [W1209](https://github.com/TG9541/stm8ef/wiki/Board-W1209) also apply to this board.

## Pin Mapping

The STM8S003F3 pins are mapped as follows:

Pin#|Pin Name|Connection
-|-|-
11|PB5|Seg a
13|PC3|Seg b
15|PC5|Seg c
17|PC7|Seg d
19|PD2|Seg e
12|PB4|Seg f
14|PC4|Seg g
16|PC6|DP
5|PA1|Digit 3
6|PA2|Digit 2
10|PA3|Digit 1
2|PD5|Key '+'
1|PD4|Key '-'
3|PD6|Key 'Set'
18|PD1|Relay
20|PD3|Sensor

The files `boardcore.inc` and `globconf.inc` implement the required changes.

## Board pictures and serial interface connection

Images show the ICSP connections on the Top and Serial port on '-' and '+':

![W1209-CAV2-Bottom](https://user-images.githubusercontent.com/5466977/67842489-8d3f1380-fafa-11e9-89b3-8720eaefb583.png)

![W1209-CAV2-Top](https://user-images.githubusercontent.com/5466977/67842502-929c5e00-fafa-11e9-958e-6657c999da2d.png)
