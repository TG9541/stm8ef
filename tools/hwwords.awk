#!/usr/bin/awk -f
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
  print "         LDW     Y,#(" a ")"
  print "         SUBW    X,#2"
  print "         LDW     (X),Y"
  print "         RET"
  print ""
}
