#!/usr/bin/gawk -f
BEGIN {
  if (!target) {
    target = "target/"
  }
}

$3!~/(LINK|RAMPOOL)/ && $4=="=" && $5~/(SPP|UPP|RAMPOOL)/ && $1~/^00/ {
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
}
