#!/usr/bin/awk -f
# extract dictionary docs from STM8 eForth assembler source files
BEGIN {
  print "# STM8EF Words"
  print "This is an auto-generated summary from STM8 eForth core code - do not edit!\n"
}

# markdown start quote block 
/^; +[^ ]+ +.+--/ && !p {
  p=1;

  # print header or section header
  if (fname != FILENAME) {
    fname = FILENAME
    print "## Words in " FILENAME "\n"
  }

  print "```"
}

# markdown close quote block 
!/^;/&&p {
  p=0;
  print "```\n"
} 

# if p print line (in quote block)
p
