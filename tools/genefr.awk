#!/usr/bin/gawk -f

$3!~/(LINK|RAMPOOL)/ && $4=="=" && $5~/(UPP|RAMPOOL)/ && $1~/^00/ {
  if (split($0,b,"\"") == 3) {
    symbol = b[2]
  }
  else {
    symbol = $3
  }
  split($0,a,";"); 
  print substr($1,3) " equ " symbol " \\ " a[2]
}
