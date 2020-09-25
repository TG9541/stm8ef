;       STM8L152K4 device and memory layout configuration

        TARGET = STM8L152C6

        RAMEND =        0x07FF  ; "RAMEND" system (return) stack, growing down
        EEPROMBASE =    0x1000  ; "EESTART" EEPROM start address
        EEPROMEND =     0x13FF  ; "EEEND" 1024 bytes EEPROM
        FLASHEND =      0xFFFF  ; 32K devices

        FORTHRAM =      0x0030  ; Start of RAM controlled by Forth
        UPPLOC  =       0x0060  ; UPP (user/system area) location for 2K RAM
        CTOPLOC =       0x0080  ; CTOP (user dictionary) location for 2K RAM
        SPPLOC  =       0x0750  ; SPP (data stack top), TIB start
        RPPLOC  =       RAMEND  ; RPP (return stack top)
