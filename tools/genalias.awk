#! /usr/bin/env gawk -f
# usage: ./genalias.awk [-v dolog=1] [-v ITCindex=1] <path to forth.rst>
# source: tg9541/stm8ef

BEGIN {
  if (!target) {
    target = "target/"
  }
  if (!dolog) {
    dolog = 2                          # log warnings to STDOUT
  }

  windx = 0                            # word #
  line = 0                             # line # in rst file
  wline = 0                            # lines since word comment
  p = 0                                # state
  worddef = ""                         # word definition
  wordcomment = ""                     # word comment
}

{
  line++
  wline++
  # print p " " $0
  if (wline > 20 && p > 0) {
    warning("header too long " word " " label " " p)
    p = 0                              # too many lines since word comment
  }
  cOneIsAddress = ($1~/^00[8-9A-F][0-9A-F]{3}$/)
}


/^ +[0-9]+ ; +[^ ]+ +.+-- / && !/ core / {
  if (p) {
    p = 0
    warning("incomplete header " word)
  }

  worddef = $0
  sub(/[^;]+; +/, "", worddef)

  p = 1
  wline = 0
  label = 0
  immediate = 0
  word = $3

  info("header found " word)
  next
}

/(HEADER|HEADFLG)/ && !/\.macro/ {
  p = 2
  for (i=1; i<=NF; i++) {
    if (index($i,"HEAD")) {
      label = $(i+1)
      break
    }
  }

  if (/IMEDD/) {
    immediate = 1
  }

  info("header " word " for " label)
  next
}

$6 == "LINK" && cOneIsAddress {
  p = 0
  info("standard header " word " " p)
  next
}

p == 1 && (($2~/:$/) || ($3~/:$/))  {
  p = 0
  info("core assembly code: " label)
  next
}

p == 2 && index($3,label ":") {
  p = 3
  info("label found: " label)
  next
}

p > 0 && index($2,label ":") {
  p = 0
  info("no code: " word)
  next
}

p == 3 && cOneIsAddress {
  p = 0
  addrstr = substr($1,3)
  ALIASADDR[word] = addrstr
  ALIASFLAG[word] = immediate
  WORD[addrstr] = word
  INDEX[windx++] = addrstr
  result("alias " word)
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
  filename = word

  if (ALIASFLAG[word] == 1) {
    isImmediate = " IMMEDIATE"
  }
  else {
    isImmediate = ""
  }

  gsub("/", "_", filename)    # replace "/" - it's forbidden in Linux filenames
  print ": " word " [ $CC C, $" ALIASADDR[word] " , OVERT" isImmediate > target filename
}

function result (text) {
  logger("Result", text, 0)
}

function info (text) {
  logger("Info", text, 1)
}

function warning (text) {
  logger("WARNING", text, 2)
}

function logger (type, text, level) {
  if (level >= dolog) {
    print type " " line ":" text
  }
}
