#!/usr/bin/env python2.7
# STM8EF uCsim telnet uploader
# - supports e4thcom style "#include" and "#require" pseudo words.
# - The include path is:
#   1. `cwd` of uploader
#   2. path of the including file
#   3. `cwd`/lib
# Limitations:
# - #require does the same as #include (no conditional uploading)
# - the telnet port is fixed (localhost 10000)

import sys
import os
import re
import telnetlib

HOST = "localhost"
PORT = 10000
CWDPATH = os.getcwd()

if len(sys.argv) < 2:
    print('Usage %s <file1> ... [fileN]' % (sys.argv[0]))
    sys.exit(2)

tn = telnetlib.Telnet(HOST,PORT)
tn.read_until("menu\r\n")

def error(message,line, path, lineNr):
    print 'Error file %s line %d: %s' % (path, lineNr, message)
    print '>>>  %s' % (line)
    sys.exit(1)

def upload(path):
    with open(path) as source:
        lineNr = 0
        print 'Uploading %s' % path
        try:
            CPATH = os.path.dirname(path)
            for line in source.readlines():
                lineNr += 1

                line = line.partition('\\')[0].strip()
                if not line: continue
                reInclude = re.search('^#(include|require) +(.+?)$', line)
                if reInclude:
                    includeFile = CWDPATH + '/' + reInclude.group(2)
                    if not os.path.isfile(includeFile):
                         includeFile = CPATH + '/' + reInclude.group(2)
                    if not os.path.isfile(includeFile):
                         includeFile = CWDPATH + '/lib/' + reInclude.group(2)
                    if not os.path.isfile(includeFile):
                        error('file not found', line, path, lineNr)
                    try:
                        upload(includeFile)
                    except:
                        error('could not upload file', line, path, lineNr)
                    continue
                if len(line) > 64:
                    raise ValueError('Line is too long: %s' % (line))
                print('TX: ' + line)
                tn.write(line + '\r')
                result = tn.expect(['\?\a\r\n', 'k\r\n', 'K\r\n'],60)
                if result[0]<0:
                    raise ValueError('timeout %s' % (line))
                elif result[0] == 0:
                    raise ValueError('error %s' % (result[2]))
        except ValueError as err:
            print(err.args[0])
            exit(1)

for path in sys.argv[1:]:
    upload(path)
