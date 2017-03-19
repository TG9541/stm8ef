
ifeq ($(BOARD),)

all: zip

zip: build
	find out/ -name "*.ihx" -print | zip out/stm8ef-bin docs/words.md -@

build: words
	make BOARD=CORE
	make BOARD=W1209
	make BOARD=W1401
	make BOARD=C0135
	make BOARD=DCDC
	make BOARD=MINDEV
	make BOARD=SWIMCOM

clean:
	rm -rf out/*

words:
	awk 'BEGIN { print "# STM8EF Words"} /^; +[^ ]+ +.+--/&&!p {p=1;print "```"} !/^;/&&p {p=0; print "```\n"} p' forth.asm > docs/words.md

defaults:
	stm8flash -c stlinkv2 -p stm8s103f3 -s opt -w tools/stm8s103FactoryDefaults.bin

else

MDEPS = forth.rel forth.h
FDEPS = hwregs8s003.inc
MKDIR_P = mkdir -p out

all: directories main.ihx

main.ihx: main.c $(MDEPS)
	sdcc -mstm8 -oout/$(BOARD)/$(BOARD).ihx main.c out/$(BOARD)/forth.rel

forth.rel: forth.asm $(FDEPS)
	mkdir -p out/$(BOARD)
	sdasstm8 -I. -I./$(BOARD) -plosgffw out/$(BOARD)/forth.rel forth.asm

flash: main.ihx
	stm8flash -c stlinkv2 -p stm8s103f3 -w out/$(BOARD)/$(BOARD).ihx

directories: out

out:
	${MKDIR_P}

.PHONY: directories
endif


#directories: out

#out:
#	${MKDIR_P}

.PHONY: all zip build defaults

