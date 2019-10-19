
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
	awk '/^ +([0-9A-F]){6}.* HI:/ {print "break 0x" $$1}' $(OUT)/forth.rst > $(OUT)/simbreak.txt
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


#directories: out

#out:
#	${MKDIR_P}

.PHONY: all zip build defaults term

