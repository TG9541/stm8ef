#!/bin/sh
# TODO Create a Makefile
rm -rf build
mkdir -p build

# SDCC version of Alan R. Baldwin's ASxxxx cross assembler for the STM8
sdasstm8 -plosgffw forth.asm

# SDCC compile init code, link
sdcc -mstm8 main.c forth.rel 

mv *map *sym *lst *rel *rst main.lk main.cdb main.asm main.ihx build

# Flash device through STM8S SWIM 
sudo ./stm8flash -c stlinkv2 -p stm8s103f3 -w build/main.ihx

