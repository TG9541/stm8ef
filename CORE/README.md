## About STM8 eForth `CORE`

`CORE` is a minimal self-contained Forth system for STM8S Low Density devices (e.g. STM8S003F3P6 or STM8S103K3T6C). It's close to the original eForth feature set but it still contains the most important STM8 eForth features like `NVM`, `CONSTANT`, `'IDLE`.  and `SAVEC .. IRET` for interrupt handlers, and `WIPE` for removing temporary words.

Compared to full-featured STM8 eForth binaries the following limitations apply to `CORE`:

* case sensitive command line (the original eForth behavior)
* no Background Task (`BG` and `TIM`)
* no I/O words (`ADC!`, `ADC@`, `OUT` and `OUT!`)
* just eForth counted loops (no `DO .. LEAVE .. LOOP/+LOOP`)
* no `CREATE .. DOES>`

`CORE` requires about 4000 bytes Flash, about 800 bytes less than `MINDEV`.`CORE` has the following vocabulary:

```Forth
WORDS 
  WIPE IRET SAVEC RESET RAM NVM WORDS .S DUMP IMMEDIATE ALLOT VARIABLE CONSTANT CREATE ] : ; OVERT ." AFT 
REPEAT WHILE ELSE THEN IF AGAIN UNTIL BEGIN NEXT FOR LITERAL C, , ' CR [ \ ( .( ? . U. TYPE SPACE KEY 
DECIMAL HEX FILL CMOVE HERE +! PICK 0= ABS NEGATE NOT 1+ 1- 2+ 2- 2* 2/ */ */MOD M* * UM* / MOD /MOD M/MOD 
UM/MOD WITHIN MIN MAX < U< = 2DUP ROT ?DUP BASE - 0< OR AND XOR + UM+ I OVER SWAP DUP 2DROP DROP NIP >R R@ 
R> C! C@ ! @ 2@ 2! EXIT EXECUTE EMIT ?KEY COLD 'BOOT ok
```

## Adding STM8 eForth Features to `CORE`

Adding more STM8 eForth features is possible by copying the `CORE` folder to a new target folder, adding configuration items, e.g. from [MINDEV/globconf.inc](https://github.com/TG9541/stm8ef/blob/master/MINDEV/globconf.inc), and executing `make BOARD=<target folder>`.

Adding the following lines to `globconf.inc` will result in a binary with about 4144 bytes size:

```
        HAS_DOLOOP       = 1    ; DO .. LOOP extension: DO LEAVE LOOP +LOOP
        CASEINSENSITIVE  = 1    ; Case insensitive dictionary search
```

This results in the following vocabulary:

```Forth
words
  WIPE IRET SAVEC RESET RAM NVM WORDS .S DUMP IMMEDIATE ALLOT VARIABLE CONSTANT CREATE ] : ; OVERT ." AFT 
REPEAT WHILE ELSE THEN IF AGAIN UNTIL BEGIN +LOOP LOOP DO NEXT FOR LITERAL C, , ' CR [ \ ( .( ? . U. TYPE 
SPACE KEY DECIMAL HEX FILL CMOVE HERE +! PICK 0= ABS NEGATE NOT 1+ 1- 2+ 2- 2* 2/ */ */MOD M* * UM* / MOD 
/MOD M/MOD UM/MOD WITHIN MIN MAX < U< = 2DUP ROT ?DUP BASE - 0< OR AND XOR + UM+ I OVER SWAP DUP 2DROP DROP 
NIP >R R@ R> C! C@ ! @ 2@ 2! EXIT EXECUTE LEAVE EMIT ?KEY COLD 'BOOT ok
```

`CORE` can also be used creating binaries for very space constraint systems (even for STM8S devices with 4K Flash like the STM8S103F2P6) by moving a part of the dictionary to the EEPROM.
