#!/usr/bin/awk -f

$1 ~ /^;\./ {
  sub(/;/,"") 
  print "        " $0
  print ""
  next
}

$1 ~ /^;/ {
  print
  next
}

$1 ~ /_/  {
  a = $1
  n = a
  sub(/_/,"",n) 
  
  c = $4

  for (i = 5; i<=NF; i++) {
    c = c " " $i
  }

  print ";       " a "    ( -- a )"
  print c
 
  print "         .dw     LINK"
  print "         LINK =  ."
  print "         .db     " length(a)
  print "         .ascii  \"" a "\""
  print n ":"
  print "         DoLitW " a
  print "         RET"
  print ""

}

