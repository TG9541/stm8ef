;       STM8L152R8 device and memory layout configuration

        TARGET = STM8L152C6

        RAMEND =        0x0FFF  ; "RAMEND" system (return) stack, growing down
        EEPROMBASE =    0x1000  ; "EESTART" EEPROM start address
        EEPROMEND =     0x17FF  ; "EEEND" 2K EEPROM
        FLASHEND =      0xFFFF  ; 32K Forth + 32K far memory

        FORTHRAM =      0x0030  ; Start of RAM controlled by Forth
        UPPLOC  =       0x0060  ; UPP (user/system area) location for 4K RAM
        CTOPLOC =       0x0080  ; CTOP (user dictionary) location for 4K RAM
        SPPLOC  =       0x0f50  ; SPP (data stack top), TIB start
        RPPLOC  =       RAMEND  ; RPP (return stack top)
