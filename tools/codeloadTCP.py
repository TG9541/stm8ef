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
resources = {}

def searchItem(item, CPATH):
    searchRes = CWDPATH + '/' + item
    if not os.path.isfile(searchRes):
        searchRes = CPATH + '/' + item
    if not os.path.isfile(searchRes):
        searchRes = CWDPATH + '/lib/' + item
    if not os.path.isfile(searchRes):
        searchRes = CWDPATH + '/mcu/' + item
    if not os.path.isfile(searchRes):
        searchRes = CWDPATH + '/target/' + item
    if not os.path.isfile(searchRes):
        searchRes = ''
    return searchRes


def removeComment(line):
    if re.search('^\\\\ +', line):
        return ''
    else:
        return line.partition(' \\ ')[0].strip()

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

def readEfr(path):
    with open(path) as source:
        print 'Reading efr file %s' % path
        lineNr = 0
        try:
            CPATH = os.path.dirname(path)
            for line in source.readlines():
                lineNr += 1
                line = removeComment(line)
                if not line:
                    continue
                resItem = line.rsplit()
                if resItem[1] == 'equ':
                    resources[resItem[2]] = resItem[0]

        except ValueError as err:
            print(err.args[0])
            exit(1)

def upload(path):
    with open(path) as source:
        print 'Uploading %s' % path
        lineNr = 0
        isExample = False

        try:
            CPATH = os.path.dirname(path)
            for line in source.readlines():
                lineNr += 1
                line = removeComment(line)
                if not line:
                    continue

                # all lines from "\\ Example:" on are comments
                if reExampleStart.match(line):
                    isExample = True

                if isExample:
                    print('\\ ' + line)
                    continue

                if re.search('^\\\\index ', line):
                    continue

                if re.search('^\\\\res ', line):
                    resSplit = line.rsplit()
                    if resSplit[1] == 'MCU:':
                        mcuFile = resSplit[2]
                        if not re.search('\\.efr', mcuFile):
                            mcuFile = mcuFile + '.efr'
                        mcuFile = searchItem(mcuFile,CPATH)
                        if not mcuFile:
                            error('file not found', line, path, lineNr)
                        else:
                            readEfr(mcuFile)
                    elif resSplit[1] == 'export':
                        symbol = resSplit[2]
                        if not symbol in resources:
                            error('symbol not found: %s' % symbol, line, path, lineNr)
                        transfer("$%s CONSTANT %s" % (resources[symbol], symbol))
                    continue

                reInclude = re.search('^#(include|require) +(.+?)$', line)
                if reInclude:
                    includeMode = reInclude.group(1)
                    includeItem = reInclude.group(2)

                    if includeMode == 'require' and notRequired(includeItem):
                        print "#require %s: skipped" % includeItem
                        continue

                    includeFile = searchItem(includeItem,CPATH)
                    if includeFile == '':
                        error('file not found', line, path, lineNr)
                    try:
                        upload(includeFile)
                        if includeMode == 'require' and not notRequired(includeItem):
                            result = transfer(": %s ;" % includeItem)
                            if result != 'ok':
                                raise ValueError('error closing #require %s' % result)
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
