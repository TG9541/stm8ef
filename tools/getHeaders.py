#!/usr/bin/env python2

import sys
import string

if len(sys.argv) < 2:
    print('Usage %s <file1> ... [fileN]' % (sys.argv[0]))
    sys.exit()

def scanning(path): 
    with open(path) as source:
        line = source.readline()
        #print(line)
        while line != '':
            # look for next LINK line
            while line != '' and line.find("LINK =  .") == -1:
                line = source.readline()
            if line == '':
                continue
            # if not compiled, candidate for header
            #print('1' + line)
            if not line.startswith('                                  '):
                line = source.readline()
                continue
            # find the next .ascii line
            #print('2' + line)
            while line != '' and line.find(".ascii") == -1:
                line = source.readline()
            if line == '':
                continue
            parts=line.split(line.__getslice__(56,57))
            # find the next line with a label (: teminated)
            while line != '' and line.find(":",41,48) == -1:
                line = source.readline()
            if line == '':
                continue
             # now, has it got an address in cols 7-12
            if line.__getslice__(6,12) != '      ':
                print(": " + parts[1] + " [ OVERT $CC C, $" + 
                    line.__getslice__(8,12) + " ,")
            line = source.readline()

for path in sys.argv[1:]:
    print('\ Scanning %s' % path)
    scanning(path)
               
