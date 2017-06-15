#! /usr/bin/gawk -f
# usage: ./genalias.awk [-v dolog=1] [-v ITCindex=1] <path to forth.rst>
# source: tg9541/stm8ef

BEGIN {
  windx = 0                            # word #
  line = 0                             # line # in rst file
  wline = 0                            # lines since word comment
  p = 0                                # state
}

{
  line++
  wline++
  if (wline > 15 && p) {
    p = 0                              # too many lines since word comment
    warning("header too long " word)
  }
}

/^ +[0-9]+ ; +[^ ]+ +.+--/ && !/core/ {
  if (p) {
    info("no code " word)
  }

  p = 1
  wline = 0
  word = $3
  info("header found " word)
  next
}

/\.dw +(LINK|0)/ && p==1 {
  p=2
  if ($2~/\.dw/ && $3~/(LINK|0)/) {
    p++
  }
  next
}


$1 ~ /[0-9A-F]{6}/ && $3 ~ /[A-Z_]{2,12}:/ {
  addrstr = substr($1,3)

  if (p==3) {
    ALIASADDR[word] = addrstr
    WORD[addrstr] = word
    INDEX[windx++] = addrstr
    result("alias " word)
  }
  else if (p==2) {
    INDEX[windx++] = addrstr
    WORD[addrstr] = word
    result("standard header " word)
  }
  else {
    info("rejected " word)
  }
  word = "..."
  p = 0
  next
}

END {
  if (ALIASADDR["OVERT"]) {
    print ": OVERT [ $CC C, $" ALIASADDR["OVERT"] " , ] ;"
  }

  if (ALIASADDR["\\"]) {
    makeAlias("\\")
  }

  for (word in ALIASADDR) {
    if (word !~/(OVERT|\\)/) {
      makeAlias(word)
    }
  }

  if (ITCindex) {
    a = 0x8000
    for (ii=0; ii<windx; ii++) {
      addr = INDEX[ii]
      aa = strtonum("0x" addr)
      print "INDEX " ii , addr , aa-a , WORD[addr]
      a = aa
    }
  }

}

function makeAlias(word,addr) {
  print ": " word " [ OVERT $CC C, $" ALIASADDR[word] " ,"
}

function result (text) {
  logger("Result", text)
}

function info (text) {
  logger("Info", text)
}

function warning (text) {
  logger("WARNING", text)
}

function logger (type, text) {
  if (dolog) {
    print type " " line ":" text
  }
}
