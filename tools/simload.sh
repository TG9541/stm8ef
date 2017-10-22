#!/bin/bash
# requires SSTM8 >= https://svn.code.sf.net/p/sdcc/code/trunk/?p=9933

# parameter e.g. W1209
export object="$1"

# create sstm8-start.txt
export ucsimstart=`mktemp`
echo "load \"out/$object/$object.ihx\""  > "$ucsimstart"

# gawk: set breakpoint at binary code address of HI
read -d '' setbreak << 'EOF'
/^ +([0-9A-F]){6}.* HI:/ {
  print "break 0x" $1
}
EOF
gawk "$setbreak" out/$object/forth.rst >> "$ucsimstart"

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
run
EOF

# wait some more before Forth code transfer
sleep 0.5

echo "simload.sh: transfer $object/board.fs"

tools/codeload.py telnet "$object/board.fs" || exit

echo "simload.sh: prepare uCsim memory dump to .ihx script"

# gawk: uCsim "dch" dump to Intel HEX conversion
read -d '' makeHex << 'EOF'
/^0x/ {
  cs=0; a=":"; g=$0; n=gsub(/ 0x/,"",g)
  App(Xpr(n),1); App($1,4); App($1,6); App("00",1)
  for (i=2; i<=(n+1); i++) { App($i,3) }
  print a Xpr(and(-cs,0xFF))
}
END { print ":00000001FF" }
function Xpr(x) { return sprintf("%02x",x) }
function App(x,n) { s=substr(x,n,2); a=a s; cs+=strtonum("0x" s) }
EOF

echo "simload.sh: load $object binary before exiting uCsim"

# dump flash data, convert to Intel Hex, hard exit uCsim
nc -w 1 localhost 10001 <<EOF | gawk "$makeHex" > "out/$object/$object-forth.ihx"
dch 0x8000 0x9FFF 16
kill
EOF

echo "simload.sh: complete - bye!"
