
ifeq ($(BOARD),)

all: zip 

zip: build
	find out/ -name "*.ihx" -print | zip out/stm8ef -@

build:
	make BOARD=CORE
	make BOARD=W1209
	make BOARD=C0135
	make BOARD=MINDEV

clean:
	rm -rf out/*

else

MDEPS = forth.rel forth.h
FDEPS = hwregs8s003.inc
MKDIR_P = mkdir -p out

all: directories main.ihx 

main.ihx: main.c $(MDEPS)
	sdcc -mstm8 -oout/$(BOARD)/$(BOARD).ihx main.c out/$(BOARD)/forth.rel 

forth.rel: forth.asm $(FDEPS) 
	mkdir -p out/$(BOARD)
	sdasstm8 -I./$(BOARD) -plosgffw out/$(BOARD)/forth.rel forth.asm 

flash: main.ihx  
	./stm8flash -c stlinkv2 -p stm8s103f3 -w out/$(BOARD)/$(BOARD).ihx

directories: out

out:
	${MKDIR_P} 

.PHONY: directories
endif


#directories: out

#out:
#	${MKDIR_P} 

.PHONY: all zip build 

