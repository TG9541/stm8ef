;       STM8S105K4 device and memory layout configuration

        TARGET  =       STM8S105K4

        RAMEND =        0x07FF  ; "RAMEND" system (return) stack, growing down
        EEPROMBASE =    0x4000  ; "EESTART" EEPROM start address
        EEPROMEND =     0x43FF  ; "EEEND" 640 bytes EEPROM
        FLASHEND =      0xFFFF  ; "FLASHEND" 32K devices

        FORTHRAM =      0x0030  ; Start of RAM controlled by Forth
        UPPLOC  =       0x0060  ; UPP (user/system area) location for 2KiB RAM
        CTOPLOC =       0x0080  ; CTOP (user dictionary) location for 2KiB RAM
        SPPLOC  =       0x0750  ; SPP (data stack top), TIB start
        RPPLOC  =       RAMEND  ; RPP (return stack top)

