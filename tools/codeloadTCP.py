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
        try:
            for line in source.readlines():
                line = line.strip()
                if not line: continue
                if len(line) > 64:
                    raise ValueError('Line is too long: %s' % (line))
                print('sending: ' + line)
                tn.write(line + '\r')
                result = tn.expect(['.*\?\r\n', '.*k\r\n', '\r\n'],3)[0]
                if result<0:
                    raise ValueError('timeout %s' % (line))
                elif result == 0:
                    raise ValueError('error %s' % (line))
        except ValueError as err:
            print(err.args)

for path in sys.argv[1:]:
    print('Uploading %s' % path)
    upload(path)
