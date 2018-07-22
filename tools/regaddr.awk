#!/usr/bin/awk -f

# Print formatted STM8 register addresses from an edited datasheet table
# 
# After copying plain from datasheet follow these steps:
# 1. remove all page numbers, page titles/footers, and table headers
# 2. find all register group identifiers, delete them, or turn into comments
# 3. combine all "Reserved area" addresses and lines into comments
# 4. fix all split lines (also register identifiers)
# 5. remove all leading blanks
# 6. combine, or fix all reset status values, and remarks
# 7. run script without parameters, apply 1..6 to fix errors, re-run
# 8. run script with -v INC=1 to create include file contents
# 9  run script with -v EFR=1 to create e4thcom style EFR file contents
#
# The result of the editing should look like this:
#   0x00 5013
#   PD_CR2
#   Port D control register 2
#   0x00
#   ; 0x00 5014 to 0x00 501D Reserved area (0 bytes)
#   ; 0x00 502E to 0x00 5049 Reserved area (44 bytes)
#   0x00 5050
#   ; Flash
#   FLASH_CR1
#   Flash control register 1
#   0x00

BEGIN {
  rnum = 0
}


{ 
  lnum++
}

# handle comment lines
/^; / {
  printCom($0) 
  next
}

# collect table lines
{
  rnum++
 
  if (rnum == 1) {
    if ($1 != "0x00") {
      print "*** Error line " lnum " address " $0 
    }
    addr = $2 
  } 
  else if (rnum == 2) {
    if (NF != 1) {
      print "*** Error line " lnum " identifier " $0
    }
    ident = $0
  }
  else if (rnum == 3) {
    comment = $0
  }
  else {
    reset = $0
    printReg(addr, ident, comment, reset)
    rnum = 0
  }
}  

function printReg(addr, ident, comment, reset) {
  if (EFR) {
    print addr , "equ" , ident , "\\ " comment , "(" reset ")"
  }
  else if (INC) {
    print "" , ident , "=", "0x" addr , "; " comment , reset 
  }
}

function printCom(t) {
  if (EFR) {
    sub(/;/, "\\",t)
    print t
  }
  else if (INC) {
    print t
  }
}


