;       STM8S207RB device and memory layout configuration

        TARGET  =       STM8S207RB

        RAMEND =        0x17FF  ; "RAMEND" system (return) stack, growing down
        EEPROMBASE =    0x4000  ; "EESTART" EEPROM start address
        EEPROMEND =     0x47FF  ; "EEEND" 640 bytes EEPROM
        FLASHEND =      0xFFFF  ; "FLASHEND" 8K devices

        FORTHRAM =      0x0030  ; Start of RAM controlled by Forth
        UPPLOC  =       0x0060  ; UPP (user/system area) location for 6KiB RAM
        CTOPLOC =       0x0080  ; CTOP (user dictionary) location for 6KiB RAM
        SPPLOC  =       0x1680  ; SPP (data stack top), TIB start
        RPPLOC  =       RAMEND  ; RPP (return stack top)

