
ifeq ($(BOARD),)

all: zip tgz

zip: build
	find out/ -name "*.ihx" -print | zip -r out/stm8ef-bin docs/words.md mcu/* lib/* -@
	find out/ -name "forth.rst" -print | zip -r out/stm8ef-bin tools/* -@
	find out/ -name "target" -print | zip -r out/stm8ef-bin -@

tgz: build
	( find out/ -path "*target/*" -print0 ; find out/ -name "*.ihx" -type f -print0 ; find out/ -name "forth.rst" -type f -print0 ) | tar -czvf out/stm8ef-bin.tgz docs/words.md mcu lib tools --null -T -

build: words
	make BOARD=CORE
	make BOARD=XH-M188
	make BOARD=W1209
	make BOARD=W1209-FD
	make BOARD=W1209-CA
	make BOARD=W1219
	make BOARD=W1401
	make BOARD=C0135
	make BOARD=DCDC
	make BOARD=MINDEV
	make BOARD=SWIMCOM
	make BOARD=STM8S105K4
	make BOARD=STM8S001J3

clean:
	rm -rf out/*

words:
	awk 'BEGIN { print "# STM8EF Words"} /^; +[^ ]+ +.+--/&&!p {p=1;print "```"} !/^;/&&p {p=0; print "```\n"} p' forth.asm > docs/words.md

defaults:
	stm8flash -c stlinkv2 -p stm8s103f3 -s opt -w tools/stm8s103FactoryDefaults.bin

defaults105:
	stm8flash -c stlinkv2 -p stm8s105k4 -s opt -w tools/stm8s105FactoryDefaults.bin

else

MDEPS = forth.rel forth.h
MKDIR_P = mkdir -p out
TARGET = `[ -f $(BOARD)/target.inc ] && awk '/TARGET/ {print tolower($$3)}' $(BOARD)/target.inc || echo "stm8s103f3"`

all: directories main.ihx

main.ihx: main.c $(MDEPS)
	sdcc -mstm8 -I./$(BOARD) -I./inc -oout/$(BOARD)/$(BOARD).ihx main.c out/$(BOARD)/forth.rel
	mkdir -p out/$(BOARD)/target
	rm -f out/$(BOARD)/target/*
	tools/genalias.awk -v target="out/$(BOARD)/target/" out/$(BOARD)/forth.rst
	tools/genconst.awk -v target="out/$(BOARD)/target/" out/$(BOARD)/forth.rst

forth.rel: forth.asm
	mkdir -p out/$(BOARD)
	sdasstm8 -I. -I./$(BOARD) -I./inc -plosgffw out/$(BOARD)/forth.rel forth.asm

flash: main.ihx
	stm8flash -c stlinkv2 -p $(TARGET) -w out/$(BOARD)/$(BOARD).ihx

forth: main.ihx
	tools/simload.sh $(BOARD)

forthflash: forth
	stm8flash -c stlinkv2 -p $(TARGET) -w out/$(BOARD)/$(BOARD)-forth.ihx

directories: out

out:
	${MKDIR_P}

.PHONY: directories
endif


#directories: out

#out:
#	${MKDIR_P}

.PHONY: all zip build defaults

