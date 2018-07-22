#!/usr/bin/awk -f
BEGIN {
  if (!target) {
    target = "target/"
  }
}

# extract lines like:
# USRNTIB =    UPP+26     ; "#TIB" count in terminal input buffer
$3!~/(LINK|RAMPOOL)/ && $4~/[=;]/ && $5~/(SPP|UPP|CFG)/ && $1~/^00/ {
  if (split($0,b,"\"") == 3) {
    symbol = b[2]
  }
  else {
    symbol = $3
  }
  split($0,a,";");
  addr = "$" substr($1,3)
  comment = " \\ " a[2]
  print  addr " CONSTANT " symbol comment > target symbol
  next
}

# extract lines like:
# RamWord USREVAL         ; "'EVAL" execution vector of EVAL
preLine~/RamWord/ && $3!~/RAMPOOL/ && $4=="=" && $5~/RAMPOOL/ {
  if (split(preLine,b,"\"") == 3) {
    symbol = b[2]
  }
  else {
    symbol = $3
  }
  split(preLine,a,";");
  addr = "$" substr($1,3)
  comment = " \\ " a[2]
  print  addr " CONSTANT " symbol comment > target symbol
  next
}

# keep the current (unprocessesed) line as the next "previous line"
{
  preLine = $0
}
