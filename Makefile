MDEPS = forth.rel forth.h
FDEPS = hwregs8s003.inc

all: flash 

main.ihx: main.c $(MDEPS)
	sdcc -mstm8 main.c forth.rel

forth.rel: forth.asm $(FDEPS) 
	sdasstm8 -plosgffw forth.asm

flash: main.ihx  
	sudo ./stm8flash -c stlinkv2 -p stm8s103f3 -w main.ihx

clean:
	rm -f *\.rel *\.ihx *\.sym *\.lst *\.map *\.lk *\.rst *\.cdb main.asm
