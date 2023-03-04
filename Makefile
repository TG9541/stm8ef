E4THCOM ?= e4thcom
TERM_PORT ?= ttyUSB0
TERM_BAUD ?= 9600
TERM_FLAGS ?= "-p mcu:target:lib"

ifeq ($(BOARD),)

all: zip tgz

zip: build
	find out/ -name "*.ihx" -print | zip -r out/stm8ef-bin forth.asm forth.mk main.c LICENSE.md docs/words.md inc/* mcu/* lib/* -@
	find out/ -name "simbreak.txt" -print | zip -r out/stm8ef-bin tools/* -@
	find out/ -name "target" -print | zip -r out/stm8ef-bin -@

tgz: build
	( find out/ -path "*target/*" -print0 ; find out/ -name "*.ihx" -type f -print0 ; find out/ -name "simbreak.txt" -type f -print0 ) | tar -czvf out/stm8ef-bin.tgz forth.asm forth.mk main.c LICENSE.md docs/words.md inc mcu lib tools --null -T -
	( find out/ -name "forth.rst" -type f -print0 ) | tar -czvf out/stm8ef-rst.tgz --null -T -

build: words
	make BOARD=STM8L101F3
	make BOARD=STM8L051F3
	make BOARD=STM8L151K4
	make BOARD=STM8L152R8
	make BOARD=STM8L-DISCOVERY
	make BOARD=STM8S001J3
	make BOARD=STM8S103F3
	make BOARD=STM8S105K4
	make BOARD=STM8S207RB
	make BOARD=MINDEV
	make BOARD=SWIMCOM
	make BOARD=CORE
	make BOARD=XY-PWM
	make BOARD=XH-M194
	make BOARD=XH-M188
	# make BOARD=DCDC
	# make BOARD=XY-LPWM
	# make BOARD=W1209-CA
	# make BOARD=W1209-CA-V2
	make BOARD=W1209
	make BOARD=W1209-FD
	make BOARD=W1219
	make BOARD=W1401
	make BOARD=C0135

clean:
	rm -rf out/*
	rm -f target

words:
	tools/genwords.awk `ls inc/*.inc` forth.asm	> docs/words.md

defaults:
	stm8flash -c stlinkv2 -p stm8s103f3 -s opt -w tools/stm8s103FactoryDefaults.bin

defaults105:
	stm8flash -c stlinkv2 -p stm8s105k4 -s opt -w tools/stm8s105FactoryDefaults.bin

term:
	$(E4THCOM) -t stm8ef -p .:lib $(TERM_FLAGS) -d $(TERM_PORT) -b B$(TERM_BAUD)

else
include forth.mk
endif


#directories: out

#out:
#	${MKDIR_P}

.PHONY: all zip build defaults term

