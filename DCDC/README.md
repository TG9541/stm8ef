## STM8 eForth "DCDC" configuration

This folder contains the STM8 eForth configuration files for the first mod of a "cheap DC/DC converter with voltmeter".

Documenation for this first board is in the [Wiki](https://github.com/TG9541/stm8ef/wiki/Board-CN2596).

In the meantime [other boards](https://hackaday.io/project/19647-low-cost-programmable-power-supply/log/172244-the-dcdc-mh-works-a-hack-while-waiting-for-santa) became more readily [available](https://www.aliexpress.com/item/32900897070.html):

![DCDC-MH](https://cdn.hackaday.io/images/931381577209891351.png)

For the DCDC-MH board there is additional information on [Hack-a-Day](https://hackaday.io/project/19647-low-cost-programmable-power-supply/log/172404-dcdc-mh-circuit-diagram), and a GitHub Gist with an initial [DCDC-MH STM8 eForth configuration](https://gist.github.com/TG9541/666e421f80dfbc6cca5957238175bf08).

The DCDC-MH board is powered by a pin-to-pin replacement Nuvoton chip, and converting the board for STM8 eForth requires some soldering skills. The conversion is still worth it since the design is well suited for implementing a serial console.

![DCDC-MH STM8S103F3P6 Mod](https://cdn.hackaday.io/images/7220691577209814290.png)

Some reverse-engineering of the DCDC-MH board was performed:

[DCDC-MH Circuit Diagram](https://cdn.hackaday.io/images/4607931577535865964.c7bee2247edabff2e773cde3ee5bba23)

An analysis of the [linear power supply](https://hackaday.io/project/19647-low-cost-programmable-power-supply/log/172270-this-linear-regulator-circuit-doesnt-look-quite-right) for the µC circuit shows that the board has a wider supply range than earlier DCDC-with-voltmeter modules.
