#!/usr/bin/env python2

import sys
import time
import socket

so = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
so.connect(("localhost",10000))
si = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
si.connect(("localhost",10001))

if len(sys.argv) < 2:
    print('Usage %s <file1> ... [fileN]' % (sys.argv[0]))
    sys.exit()

def upload(path): 
    with open(path) as source:
        for line in source.readlines():
            time.sleep(0.2)        
            line = line.strip()
            if not line: continue
            if len(line) > 64:
                raise 'Line is too long: %s' % (line)
            print('sending: ' + line)
            so.sendall(line)
            so.sendall('\n')
            chin = ''
            response_buffer = []
            while chin <> '\v':
	      response_buffer.append(chin)
	      chin = si.recv(1)
            response = ''.join(response_buffer)
            sys.stdout.write(response)

for path in sys.argv[1:]:
    print('Uploading %s' % path)
    upload(path)
               
