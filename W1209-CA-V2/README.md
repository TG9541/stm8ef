25/10/2019

W1209-CA another variation
=====================
This is  another variation of the Common Anode W1209 boards
 which has totally different pin mappings, and a different layout 
 e.g the swim connections are at the side next to the thermistor connection

The mappings are as Follows:

Pin#	Pin Name	Connection
11	PB5	Seg a
13	PC3	Seg b
15	PC5	Seg c
17	PC7	Seg d
19	PD2	Seg e
12	PB4	Seg f
14	PC4	Seg g
16	PC6	DP
5	PA1	Digit 3
6	PA2	Digit 2
10	PA3	Digit 1
2	PD5	'+'
1	PD4	'-'
3	PD6	Set
18	PD1	Relay
20	PD3	Sensor

For changes required in boardcore.inc and globconf.inc see attached files!

Images show the ICSP connections on the Top and Serial port on '-' and '+'

