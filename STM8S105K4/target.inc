; STM8S105K4 device and memory layout configuration  
        TARGET  =       STM8S105K4

        RAMEND =        0x07FF  ; system (return) stack, growing down
        EEPROMEND =     0x43FF  ; STM8S105K4: 1024 bytes EEPROM
        FLASHEND =      0xBFFF  ; 16 KiB devices

        FORTHRAM =      0x0040  ; Start of RAM controlled by Forth
        UPPLOC  =       0x0060  ; UPP (user/system area) location for 2KiB RAM
        CTOPLOC =       0x0080  ; CTOP (user dictionary) location for 2KiB RAM
        SPPLOC  =       0x0750  ; SPP (data stack top), TIB start
        RPPLOC  =       RAMEND  ; RPP (return stack top)


