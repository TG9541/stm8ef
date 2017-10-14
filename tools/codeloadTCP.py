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
reExampleStart = re.compile("^\\\\\\\\ Example:")

def error(message,line, path, lineNr):
    print 'Error file %s line %d: %s' % (path, lineNr, message)
    print '>>>  %s' % (line)
    sys.exit(1)

def transfer(line):
    tn.write(line + '\r')
    tnResult=tn.expect(['\?\a\r\n', 'k\r\n', 'K\r\n'],60)
    if tnResult[0]<0:
        raise ValueError('timeout %s' % line)
    elif tnResult[0]==0:
        return tnResult[2]
    else:
        return "ok"

def notRequired(word):
    return transfer("' %s DROP" % word) == 'ok'

def upload(path):
    with open(path) as source:
        print 'Uploading %s' % path
        lineNr = 0
        isExample = False

        try:
            CPATH = os.path.dirname(path)
            for line in source.readlines():
                lineNr += 1
                # all lines from "\\ Example:" on are comments
                if reExampleStart.match(line):
                    isExample = True

                if isExample:
                    print('\\ ' + line)
                    continue

                reRes = re.search('^\\\\res +(.+?)$', line)
                if reRes:
                    reRes = reRes.group(1)
                    print('res: ' + reRes)
                    continue

                line = line.partition('\\')[0].strip()
                if not line: continue

                reInclude = re.search('^#(include|require) +(.+?)$', line)
                if reInclude:
                    includeMode = reInclude.group(1)
                    includeItem = reInclude.group(2)

                    if includeMode == 'require' and notRequired(includeItem):
                        continue

                    includeFile = CWDPATH + '/' + includeItem
                    if not os.path.isfile(includeFile):
                        includeFile = CPATH + '/' + includeItem
                    if not os.path.isfile(includeFile):
                        includeFile = CWDPATH + '/lib/' + includeItem
                    if not os.path.isfile(includeFile):
                        includeFile = CWDPATH + '/mcu/' + includeItem
                    if not os.path.isfile(includeFile):
                        includeFile = CWDPATH + '/target/' + includeItem
                    if not os.path.isfile(includeFile):
                        error('file not found', line, path, lineNr)
                    try:
                        upload(includeFile)
                    except:
                        error('could not upload file', line, path, lineNr)
                    continue
                if len(line) > 80:
                    raise ValueError('Line is too long: %s' % (line))
                print('TX: ' + line)
                result = transfer(line)
                if result != 'ok':
                    raise ValueError('error %s' % result)
        except ValueError as err:
            print(err.args[0])
            exit(1)

for path in sys.argv[1:]:
    upload(path)
