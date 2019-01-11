E4THCOM=e4thcom-0.6.3
TERM_PORT=ttyUSB0
TERM_BAUD=9600
TERM_FLAGS=

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
	make BOARD=XH-M194
	make BOARD=W1209
	make BOARD=W1209-FD
	make BOARD=W1209-CA
	make BOARD=W1219
	make BOARD=W1401
	make BOARD=C0135
	make BOARD=DCDC
	make BOARD=XY-PWM
	make BOARD=XY-LPWM
	make BOARD=MINDEV
	make BOARD=SWIMCOM
	make BOARD=STM8L051F3
	make BOARD=STM8L-DISCOVERY
	make BOARD=STM8S105K4
	make BOARD=STM8S001J3

clean:
	rm -rf out/*
	rm target

words:
	awk 'BEGIN { print "# STM8EF Words"} /^; +[^ ]+ +.+--/&&!p {p=1;print "```"} !/^;/&&p {p=0; print "```\n"} p' forth.asm > docs/words.md

defaults:
	stm8flash -c stlinkv2 -p stm8s103f3 -s opt -w tools/stm8s103FactoryDefaults.bin

defaults105:
	stm8flash -c stlinkv2 -p stm8s105k4 -s opt -w tools/stm8s105FactoryDefaults.bin

else

MDEPS   = forth.rel forth.h
MKDIR_P = mkdir -p out
BTARGET = $(BOARD)/target.inc
OUT     = out/$(BOARD)

TARGET := $(shell echo `[ -f $(BTARGET) ] && awk '/TARGET/ {print tolower($$3)}' $(BTARGET) || echo "stm8s103f3"`)
OPTFILE := $(shell echo $(TARGET) | awk '{print "tools/" substr($$0,1,8) "FactoryDefaults.bin"}')

all: directories main.ihx

main.ihx: main.c $(MDEPS)
	sdcc -mstm8 -I./$(BOARD) -I./inc -o$(OUT)/$(BOARD).ihx main.c $(OUT)/forth.rel
	mkdir -p $(OUT)/target
	rm -f $(OUT)/target/*
	rm -f target
	ln -s $(OUT)/target/ target
	awk -f tools/genalias.awk -v target="$(OUT)/target/" $(OUT)/forth.rst
	awk -f tools/genconst.awk -v target="$(OUT)/target/" $(OUT)/forth.rst

forth.rel: forth.asm
	mkdir -p $(OUT)
	sdasstm8 -I. -I./$(BOARD) -I./inc -plosgffw $(OUT)/forth.rel forth.asm

flash: main.ihx
	stm8flash -c stlinkv2 -p $(TARGET) -w $(OUT)/$(BOARD).ihx

forth: main.ihx
	tools/simload.sh $(BOARD)

forthflash: forth
	stm8flash -c stlinkv2 -p $(TARGET) -w $(OUT)/$(BOARD)-forth.ihx

readflash:
	stm8flash -c stlinkv2 -p $(TARGET) -s flash -r $(OUT)/$(BOARD)-readflash.ihx

readeeprom:
	stm8flash -c stlinkv2 -p $(TARGET) -s eeprom -r $(OUT)/$(BOARD)-readeeprom.ihx

readopt:
	stm8flash -c stlinkv2 -p $(TARGET) -s opt -r $(OUT)/$(BOARD)-readopt.ihx

defaults:
	stm8flash -c stlinkv2 -p $(TARGET) -s opt -w $(OPTFILE)


# Usage:
# 	make term BOARD=<board dir> [TERM_PORT=ttyXXXX] [TERM_BAUD=nnnn] [TERM_FLAGS="--half-duplex --idm"]
term:
	cd $(BOARD) && $(E4THCOM) -t stm8ef -p .:../lib $(TERM_FLAGS) -d $(TERM_PORT) -b B$(TERM_BAUD)

directories: out

out:
	${MKDIR_P}

.PHONY: directories
endif


#directories: out

#out:
#	${MKDIR_P}

.PHONY: all zip build defaults term

