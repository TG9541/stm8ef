#!/bin/bash
# requires SSTM8 >= https://svn.code.sf.net/p/sdcc/code/trunk/?p=9933

# parameter e.g. W1209
export object="$1"

# create sstm8-start.txt
export ucsimstart=`mktemp`
echo "load \"out/$object/$object.ihx\""  > "$ucsimstart"

cat out/$object/simbreak.txt >> "$ucsimstart"

echo "simload.sh: run STM8EF in uCsim with breakpoint at HI"

# start simulator, it's set to break at HI
sstm8 -w -C$ucsimstart -g -Z10001 -tS103 -Suart=1,port=10000 &
sleep 1.0

# wait, inject uart code patch, and start over
echo "simload.sh: inject UART code into RAM and continue execution"

nc -w 1 localhost 10001 <<EOF
download
:04006000100010205C
:1010000090AE680390CF5232350C523535100061e6
:0C1010005CF65C720F5230FBC75231815d
:101020004F720B523003C652314D2704AD024F436d
:08103000905F90975A5AFF816e
:00000001FF
uart1_flowctrl=1
run
EOF

export boardihx="out/$object/$object-forth.ihx"
export boardcode="$object/board.fs"
if [ ! -f "$boardcode" ]; then
  echo "local $boardcode not found ..."
  export boardcode="main.fs"
  export boardihx="$object-forth.ihx"
  echo "... trying $boardcode"
fi

# wait some more before Forth code transfer
sleep 0.5

echo "simload.sh: transfer $boardcode"

tools/codeload.py -b "out/$object" telnet "$boardcode" || exit

echo "simload.sh: extract $boardihx binary and exit uCsim"

# dump flash data, convert to Intel Hex, hard exit uCsim
nc -w 1 localhost 10001 <<EOF | python3 tools/dch2ihx.py > "$boardihx"
dch 0x8000 0x9FFF 16
kill
EOF
echo "simload.sh: complete - bye!"
