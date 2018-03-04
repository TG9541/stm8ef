;       STM8S207RB device and memory layout configuration

        TARGET  =       STM8S207RB

        RAMEND =        0x17FF  ; system (return) stack, growing down
        EEPROMEND =     0x47FF  ; STM8S207RB: 2048 bytes EEPROM
        FLASHEND =      0xFFFF  ; 32 KiB devices (+96 KiB > 0xFFFF )

        FORTHRAM =      0x0040  ; Start of RAM controlled by Forth
        UPPLOC  =       0x0060  ; UPP (user/system area) location for 6KiB RAM
        CTOPLOC =       0x0080  ; CTOP (user dictionary) location for 6KiB RAM
        SPPLOC  =       0x1680  ; SPP (data stack top), TIB start
        RPPLOC  =       RAMEND  ; RPP (return stack top)

