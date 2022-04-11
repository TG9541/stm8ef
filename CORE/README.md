## STM8 eForth "CORE" configuration

`CORE` is a minimal STM8 eForth configuration for [STM8S "Low Density" devices](https://github.com/TG9541/stm8ef/wiki/STM8-Low-Density-Devices#stm8s-low-density-devices) (e.g., STM8S003F3P6, STM8S103K3T6C or STM8S903K3T6C). It's close to the original eForth feature set but many words were unlinked from the dictionary (using the `BAREBONES` configuration). It still contains the most important STM8 eForth additions like `CONSTANT` (true literals), `NVM` (compile to Flash memory), `'IDLE` (console idle tasks), `SAVEC .. IRET` (for interrupt handlers)and `WIPE` (for removing temporary words).

Compared to a full STM8 eForth configuration `CORE` it contains the following feature/memory trade-off:

* case sensitive (the original eForth behavior)
* no Background Task (`BG` and `TIM`)
* no I/O words (`ADC!`, `ADC@`, `OUT` and `OUT!`)
* no `DO .. LEAVE .. LOOP/+LOOP` (only eForth [`FOR ... NEXT`](https://github.com/TG9541/stm8ef/wiki/eForth-FOR-..-NEXT) counted loops)
* no `CREATE .. DOES>`

`CORE` requires less than 3900 bytes Flash memory, that's about 730 bytes less than [MINDEV](https://github.com/TG9541/stm8ef/tree/master/MINDEV).

The following is the visible vocabulary:

```Forth
WORDS
  WIPE IRET SAVEC RESET RAM NVM WORDS .S DUMP IMMEDIATE ALLOT VARIABLE CONSTANT CREATE ] : ; OVERT ." AFT
REPEAT WHILE ELSE THEN IF AGAIN UNTIL BEGIN NEXT FOR LITERAL C, , ' CR [ \ ( .( ? . U. TYPE SPACE KEY
DECIMAL HEX FILL CMOVE HERE +! PICK 0= ABS NEGATE NOT 1+ 1- 2+ 2- 2* 2/ */ */MOD M* * UM* / MOD /MOD M/MOD
UM/MOD WITHIN MIN MAX < U< = 2DUP ROT ?DUP BASE - 0< OR AND XOR + UM+ I OVER SWAP DUP 2DROP DROP NIP >R R@
R> C! C@ ! @ 2@ 2! EXIT EXECUTE EMIT ?KEY COLD 'BOOT ok
```

Hidden Forth words, which can be made visible with [`ALIAS`](https://github.com/TG9541/stm8ef/wiki/STM8-eForth-Alias-Words), are listed in the `CORE/target` folder.

## Adding STM8 eForth Features to `CORE`

Adding more STM8 eForth features is possible by copying the `CORE` folder to a new target folder, adding configuration items, e.g. from [MINDEV/globconf.inc](https://github.com/TG9541/stm8ef/blob/master/MINDEV/globconf.inc), and executing `make BOARD=<target folder>`.

Adding the following lines to `globconf.inc` will result in a binary with about 4040 bytes size:

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

# Creating even leaner STM8 eForth binaries

`CORE` can be used for creating binaries for very space constraint systems (even for STM8S devices with a nominal Flash size of 4K Flash like the STM8S103F2P6) by moving a part of the dictionary to the EEPROM:

In order to achieve this, it's recommended to first "unlink" a group of dictionary entries, e.g.:

```
        UNLINK_DDUP      = 1    ; "2DUP"
        UNLINK_DNEGA     = 1    ; "DNEGATE"
        UNLINK_EQUAL     = 0    ; "="
        UNLINK_ULESS     = 0    ; "U<"
        UNLINK_LESS      = 0    ; "<"
        UNLINK_MAX       = 1    ; "MAX"
        UNLINK_MIN       = 1    ; "MIN"
        UNLINK_WITHI     = 1    ; "WITHIN"
        UNLINK_UMMOD     = 0    ; "UM/MOD"
        UNLINK_MSMOD     = 0    ; "M/MOD"
        UNLINK_SLMOD     = 0    ; "/MOD"
        UNLINK_MMOD      = 1    ; "MOD"

```

After building the kernel, files with `ALIAS` statements for temporary dictionary entries are in `target`. The file `target/aliaslist.fs` contains a list of `#require` statements from which a selection for temporay dictionary entries in the EEPROM can be made.
