#!/usr/bin/awk -f
BEGIN {
  print ";       DOLITEXIT   ( -- w )    ( TOS STM8: -- Y,Z,N )"
  print ";       Push an inline literal and exit"
  print ""
  print "DOLITEXIT:"
  print "        DECW    X"
  print "        DECW    X"
  print "        EXGW    X,Y ; Y is discarded"
  print "        POPW    X"
  print "        LDW     X,(X)"
  print "        EXGW    X,Y"
  print "        LDW     (X),Y"
  print "        RET"
  print ""


}

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
  print "         CALL    DOLITEXIT"
  print "         .dw " a
  print ""

}

