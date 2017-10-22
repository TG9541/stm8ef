#!/usr/bin/env python2.7
# STM8EF code loader
# targets uCsim (telnet), serial interface, and text file
# supports e4thcom pseudo words, e.g. #include, #require, and \res .
#
# The include path is:
#   1. ./
#   2. path of the includedfile
#   3. ./lib
#   4. ./mcu
#   5. ./target

import sys
import os
import serial
import telnetlib
import re
import argparse

class Connection:
    def transfer(self, line):
        return "ok"
    def tracef(self, line):
        if tracefile:
            try:
                tracefile.write(line + '\n')
            except:
                print('Error writing tracefile %s' % args.tracefile)
                exit(1)

class ConnectDryRun(Connection):
    def transfer(self, line):
        print(line)
        return "ok"

class ConnectUcsim(Connection):
    tn = { }
    def __init__(self, comspec):
        try:
            HOST = comspec.split(':')[0]
            PORT = comspec.split(':')[1]
            self.tn = telnetlib.Telnet(HOST,PORT)
        except:
            print("Error: couldn't open telnet port")
            sys.exit(1)

        self.tn.read_until("\n",1)

    def transfer(self, line):
        self.tracef(line)

        try:
            vprint('TX: ' + line)
            line = removeComment(line)
            if line:
                self.tn.write(line+ '\r')
                tnResult = self.tn.expect(['\?\a\r\n', 'k\r\n', 'K\r\n'],60)
            else:
                return "ok"
        except:
            print('Error: telnet transfer failure')
            sys.exit(1)

        if tnResult[0]<0:
            print('timeout %s' % line)
            sys.exit(1)
        elif tnResult[0]==0:
            return tnResult[2]
        else:
            return "ok"

class ConnectSerial(Connection):
    port = { }
    def __init__(self, ttydev):
        try:
            self.port = serial.Serial(
                port     = ttydev,
                baudrate = 9600,
                parity   = serial.PARITY_NONE,
                stopbits = serial.STOPBITS_ONE,
                bytesize = serial.EIGHTBITS,
                timeout  = 5 )
        except:
            print('Error: TTY device %s invalid' % ttydev)
            sys.exit(1)

    def transfer(self, line):
        self.tracef(line)

        try:
            vprint('TX: ' + line)
            line = removeComment(line)
            if line:
                self.port.write(line + '\r')
                sioResult = self.port.readline()
            else:
                return "ok"
        except:
            print('Error: TTY transmission failed')
            sys.exit(1)

        if re.search(' (OK|ok)$', sioResult):
            return "ok"
        else:
            return sioResult

#argparse https://docs.python.org/2/howto/argparse.html
parser = argparse.ArgumentParser()

parser.add_argument("method", choices=['serial','telnet','dryrun'],
        help="transfer method")
parser.add_argument("files", nargs='*',
        help="name of one or more files to transfer")
parser.add_argument("-p", "--port", dest="port",
        help="PORT for transfer, default: /dev/ttyUSB0, localhost:10000", metavar="port")
parser.add_argument("-t", "--trace", dest="tracefile",
        help="write source code (with includes) to tracefile", metavar="tracefile")
parser.add_argument("-q", "--quiet", action="store_false", dest="verbose", default=True,
        help="don't print status messages to stdout")
args = parser.parse_args()

# create tracefile if needed
if args.tracefile:
    try:
        tracefile = open(args.tracefile,'w')
    except:
        print('Error writing tracefile %s' % args.tracefile)
        exit(1)
else:
    tracefile = False


# Initualize transfer method with default destionation port
if args.method == "telnet":
    CN = ConnectUcsim(args.port or 'localhost:10000')
elif args.method == "serial":
    CN = ConnectSerial(args.port or '/dev/ttyUSB0')
else:
    CN = ConnectDryRun()

def vprint(text):
    if args.verbose:
        print text

CWDPATH = os.getcwd()
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

def error(message, line, path, lineNr):
    print 'Error file %s line %d: %s' % (path, lineNr, message)
    print '>>>  %s' % (line)
    sys.exit(1)

def notRequired(word):
    return CN.transfer("' %s DROP" % word) == 'ok'

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
        vprint('Uploading %s' % path)
        lineNr = 0
        isExample = False

        try:
            CPATH = os.path.dirname(path)
            for line in source.readlines():
                lineNr += 1
                line = line.replace('\n', ' ').replace('\r', '')

                # all lines from "\\ Example:" on are comments
                if reExampleStart.match(line):
                    isExample = True

                if isExample:
                    vprint('\\ ' + line)
                    continue

                if re.search('^\\\\index ', line):
                    continue

                if re.search('^\\\\res ', line):
                    resSplit = line.rsplit()
                    if resSplit[1] == 'MCU:':
                        mcuFile = resSplit[2].strip()
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
                        CN.transfer("$%s CONSTANT %s" % (resources[symbol], symbol))
                    continue

                reInclude = re.search('^#(include|require) +(.+?)$', line)
                if reInclude:
                    includeMode = reInclude.group(1).strip()
                    includeItem = reInclude.group(2).strip()

                    if includeMode == 'require' and notRequired(includeItem):
                        print "#require %s: skipped" % includeItem
                        continue

                    includeFile = searchItem(includeItem,CPATH)
                    if includeFile == '':
                        error('file not found', line, path, lineNr)
                    try:
                        upload(includeFile)
                        if includeMode == 'require' and not notRequired(includeItem):
                            result = CN.transfer(": %s ;" % includeItem)
                            if result != 'ok':
                                raise ValueError('error closing #require %s' % result)
                    except:
                        error('could not upload file', line, path, lineNr)
                    continue
                if len(line) > 80:
                    raise ValueError('Line is too long: %s' % (line))

                result = CN.transfer(line)
                if result != 'ok':
                    raise ValueError('error %s' % result)

        except ValueError as err:
            print(err.args[0])
            exit(1)

for path in args.files:
    upload(path)
