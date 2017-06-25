#!/usr/bin/env python2

import sys
import telnetlib

HOST = "localhost"
PORT = 10000
tn = telnetlib.Telnet(HOST,PORT)
tn.read_until("menu\r\n")

if len(sys.argv) < 2:
    print('Usage %s <file1> ... [fileN]' % (sys.argv[0]))
    sys.exit()

def upload(path): 
    with open(path) as source:
        for line in source.readlines():
            line = line.strip()
            if not line: continue
            if len(line) > 64:
                raise 'Line is too long: %s' % (line)
            print('sending: ' + line)
            line = line.strip()
            if not line: continue
            tn.write(line + '\r')
            print tn.expect(['(\v|\n)'])[2]

for path in sys.argv[1:]:
    print('Uploading %s' % path)
    upload(path)
               
