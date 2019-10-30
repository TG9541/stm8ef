E4THCOM=e4thcom-0.6.3
TERM_PORT=ttyUSB0
TERM_BAUD=9600
TERM_FLAGS=

ifeq ($(BOARD),)

all: zip tgz

zip: build
	find out/ -name "*.ihx" -print | zip -r out/stm8ef-bin forth.asm forth.h forth.mk main.c LICENSE.md docs/words.md inc/* mcu/* lib/* -@
	find out/ -name "simbreak.txt" -print | zip -r out/stm8ef-bin tools/* -@
	find out/ -name "target" -print | zip -r out/stm8ef-bin -@

tgz: build
	( find out/ -path "*target/*" -print0 ; find out/ -name "*.ihx" -type f -print0 ; find out/ -name "simbreak.txt" -type f -print0 ) | tar -czvf out/stm8ef-bin.tgz forth.asm forth.h forth.mk main.c LICENSE.md docs/words.md mcu lib tools --null -T -
	( find out/ -name "forth.rst" -type f -print0 ) | tar -czvf out/stm8ef-rst.tgz --null -T -

build: words
	make BOARD=CORE
	make BOARD=XH-M188
	make BOARD=XH-M194
	make BOARD=W1209
	make BOARD=W1209-FD
	make BOARD=W1209-CA
	make BOARD=W1209-CA-V2
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
include forth.mk
endif


#directories: out

#out:
#	${MKDIR_P}

.PHONY: all zip build defaults term

