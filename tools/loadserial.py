#!/usr/bin/env python2

import serial
import sys
import time

port = serial.Serial(
    port='/dev/ttyUSB0',
    # port='/dev/ttyACM0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,	
    bytesize=serial.EIGHTBITS,
    timeout=5)

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
            print('\n\rsending: ' + line)
            #print('\r')
            port.write(line)        
            port.write('\n\r')
            chin = ''
            response_buffer = []
            while (chin <> '\v') and (chin <> '\n'):
	      response_buffer.append(chin)
#	      while port.inWaiting() > 0:
	      chin = port.read(1)
            response = ''.join(response_buffer)
            sys.stdout.write(response)

for path in sys.argv[1:]:
    print('Uploading %s' % path)
    upload(path)
               
