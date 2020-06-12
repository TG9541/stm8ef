#!/usr/bin/awk -f
BEGIN {
  if (!target) {
    target = "target/"
  }
  split(target,t,/\//)
  board = t[2]
}

# extract lines like the following:
#   LDW     X,#(EMIT_BG)    ; "EMITBG" xt of EMIT for BG task
#   CALL    NAMEQ           ; "PC_?UNIQUE" name exists
($2=="AE" && $8=="LDW") ||  ($2=="CD" && $8=="CALL") {
  if (split($0,b,"\"") == 3) {
    symbol = b[2]
    split($0,a,";");
    addr = sprintf("$%04X",strtonum("0x" substr($1,3))+1)
    comment = " \\ NVM " board ":" b[3]
    print  addr " CONSTANT " symbol comment > target symbol
  }
  next
}

# extract lines like:
# USRNTIB =    UPP+26     ; "#TIB" count in terminal input buffer
$1~/^00/ && $3!~/(LINK|RAMPOOL)/ && $4~/[=;]/ && $7~/^"/ {
  if (split($0,b,"\"") == 3) {
    symbol = b[2]
  }
  else {
    symbol = $3
  }
  split($0,a,";");
  addr = "$" substr($1,3)
  comment = " \\ " board ":" a[2]
  print  addr " CONSTANT " symbol comment > target symbol
  next
}

# use case 1:
#         RamWord USREVAL         ; "'EVAL" execution vector of EVAL
# use case 2:
#         RamByte LED7GROUP       ; byte index of 7-SEG digit group
preLine~/Ram(Word|Byte|Blck)/ && $3!~/RAMPOOL/ && $4=="=" && $5~/RAMPOOL/ {
  if (split(preLine,b,"\"") == 3) {
    symbol = b[2]           # use case 1
    addr = "$" substr($1,3)
    comment = " \\ " board ":" b[3]
  }
  else {
    symbol = $3             # use case 2
    split(preLine,a,";");
    addr = "$" substr($1,3)
    comment = " \\ " board ":" a[2]
  }
  print  addr " CONSTANT " symbol comment > target symbol
  next
}

# keep the current (unprocessesed) line as the next "previous line"
{
  preLine = $0
}
