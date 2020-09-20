;       STM8L101F3 device and memory layout configuration

        TARGET = STM8L101F3     ; Not quite the same as STM8L051F3

        RAMEND =        0x05FF  ; "RAMEND" system (return) stack, growing down
        EEPROMBASE =    0x1000  ; "EESTART" EEPROM start address (not really)
        EEPROMEND =     0x10FF  ; "EEEND" 256 bytes EEPROM (see datasheet...)
        FLASHEND =      0x9FFF  ; "FLASHEND" 8K devices

        FORTHRAM =      0x0030  ; Start of RAM controlled by Forth
        UPPLOC  =       0x0060  ; UPP (user/system area) location for 1K RAM
        CTOPLOC =       0x0080  ; CTOP (user dictionary) location for 1K RAM
        SPPLOC  =       0x0550  ; SPP (data stack top), TIB start (rather 0x0550)
        RPPLOC  =       RAMEND  ; RPP (return stack top)
