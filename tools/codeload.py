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
#   5. <base>/target

import sys
import os
import serial
import telnetlib
import re
import argparse

# hash for "\res MCU:" key-value pairs
resources = {}

# a modicum of OOP for target line transfer
class Connection:
    def dotrans(self, line):
        return "ok"
    def transfer(self, line):
        return self.dotrans(line)
    def testtrans(self, line):
        return self.dotrans(line)
    def tracef(self, line):
        if tracefile:
            try:
                tracefile.write(line + '\n')
            except:
                print('Error writing tracefile %s' % args.tracefile)
                exit(1)

# dummy line transfer
class ConnectDryRun(Connection):
    def transfer(self, line):
        print(line)
        return "ok"
    def testtrans(self, line):
        return ""

# uCsim telnet line transfer
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
        vprint('TX: ' + line)
        return self.dotrans(line)

    def dotrans(self, line):
        self.tracef(line)

        try:
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
            print('Error: timeout %s' % line)
            sys.exit(1)
        elif tnResult[0]==0:
            return tnResult[2]
        else:
            return "ok"

# serial line transfer
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
        vprint('TX: ' + line)
        return self.dotrans(line)

    def dotrans(self, line):
        self.tracef(line)

        try:
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

# simple show-error-and-exit
def error(message, line, path, lineNr):
    print 'Error file %s line %d: %s' % (path, lineNr, message)
    print '>>>  %s' % (line)
    sys.exit(1)

# simple stdout log printer
def vprint(text):
    if args.verbose:
        print text

# search an item (a source file) in the extended e4thcom search path
def searchItem(item, CPATH):
    # Windows' DOS days quirks: hack for STM8EF subfolders in lib/
    if os.name == 'nt' and re.search('^(hw|utils|math)',item):
        item = item.replace('/','\\',1)
    CWDPATH = os.getcwd()
    searchRes = os.path.join(CWDPATH, item)
    if not os.path.isfile(searchRes):
        searchRes = os.path.join(CPATH, item)
    if not os.path.isfile(searchRes):
        searchRes = os.path.join(CWDPATH, 'mcu', item)
    if not os.path.isfile(searchRes):
        searchRes = os.path.join(CWDPATH, args.base,'target', item)
        print(searchRes)
    if not os.path.isfile(searchRes):
        searchRes = os.path.join(CWDPATH, 'lib', item)
    if not os.path.isfile(searchRes):
        searchRes = ''
    return searchRes

# Forth "\" comment stripper
def removeComment(line):
    if re.search('^\\\\ +', line):
        return ''
    else:
        return line.partition(' \\ ')[0].strip()

# test if a word already exists in the dictionary
def required(word):
    return CN.testtrans("' %s DROP" % word) != 'ok'

# reader for e4thcom style .efr files (symbol-address value pairs)
def readEfr(path):
    with open(path) as source:
        vprint('Reading efr file %s' % path)
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

# uploader with resolution of #include, #require, and \res
def upload(path):
    reExampleStart = re.compile("^\\\\\\\\")

    with open(path) as source:
        vprint('Uploading %s' % path)
        lineNr = 0
        isExample = False

        try:
            CPATH = os.path.dirname(path)
            for line in source.readlines():
                lineNr += 1
                line = line.replace('\n', ' ').replace('\r', '').strip()

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
                        if required(symbol):
                            CN.transfer("$%s CONSTANT %s" % (resources[symbol], symbol))
                        else:
                            vprint("\\res export %s: skipped" % symbol)
                    continue

                reInclude = re.search('^#(include|require) +(.+?)$', line)
                if reInclude:
                    includeMode = reInclude.group(1).strip()
                    includeItem = reInclude.group(2).strip()

                    if includeMode == 'require' and not required(includeItem):
                        vprint("#require %s: skipped" % includeItem)
                        continue

                    includeFile = searchItem(includeItem,CPATH)
                    if includeFile == '':
                        error('file not found', line, path, lineNr)
                    try:
                        upload(includeFile)
                        if includeMode == 'require' and required(includeItem):
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

# Python has a decent command line argument parser - use it
parser = argparse.ArgumentParser()
parser.add_argument("method", choices=['serial','telnet','dryrun'],
        help="transfer method")
parser.add_argument("files", nargs='*',
        help="name of one or more files to transfer")
parser.add_argument("-b", "--target-base", dest="base", default="",
        help="target base folder, default: ./", metavar="base")
parser.add_argument("-p", "--port", dest="port",
        help="PORT for transfer, default: /dev/ttyUSB0, localhost:10000", metavar="port")
parser.add_argument("-q", "--quiet", action="store_false", dest="verbose", default=True,
        help="don't print status messages to stdout")
parser.add_argument("-t", "--trace", dest="tracefile",
        help="write source code (with includes) to tracefile", metavar="tracefile")
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

# Initalize transfer method with default destionation port
if args.method == "telnet":
    CN = ConnectUcsim(args.port or 'localhost:10000')
elif args.method == "serial":
    CN = ConnectSerial(args.port or '/dev/ttyUSB0')
else:
    CN = ConnectDryRun()

# Ze main
for path in args.files:
    upload(path)
