\ STM8S103 PORTC register words - immediate
\ (c) TG9541, refer to license at github.com/TG9541/stm8ef/

: PC_ODR  $500A ; IMMEDIATE \ Port C data output latch (0x00)
: PC_IDR  $500B ; IMMEDIATE \ Port C input pin value   (0xXX)
: PC_DDR  $500C ; IMMEDIATE \ Port C data direction    (0x00)
: PC_CR1  $500D ; IMMEDIATE \ Port C control  1        (0x00)
: PC_CR2  $500E ; IMMEDIATE \ Port C control  2        (0x00)
