#!/usr/bin/env python3
# Converts uCsim dumps to ihx format https://en.wikipedia.org/wiki/Intel_HEX
# 'dch 0xXX 0xXX 16' dumps ROM to multiple rows formated like {adress} {byte 1} ... {byte 16} {ASCI_representation}

import argparse
import sys

NUMBER_OF_BYTES = 16

def parse_arguments():
    parser = argparse.ArgumentParser(description="ucsim 'dch 0xXX 0xXX 16' to ihc converter")
    parser.add_argument('-i', nargs='?', dest="infile", type=argparse.FileType('r'), default=sys.stdin, 
        help="ucsim 'dch 0xXX 0xXX 16' output")
    parser.add_argument('-o', nargs='?', dest="outfile", type=argparse.FileType('w'), default=sys.stdout)
    return parser.parse_args()

def twos_complement(input_value):
    return (~input_value +1) & 0xFF

def read_dump(infile, colnum_to_read):
    lines = filter(lambda l: l.startswith('0x'), infile.readlines())
    return map(lambda l: l.split(' ')[:colnum_to_read + 1], lines)

def output_ihx(outfile, lines):
    lines.append('00000001FF')
    outfile.write('\n'.join([':%s' % l for l in lines]))

def parse_row(row):
    data_size = "%02x" % ( len(row) - 1)
    adress = row[0][-4:] # eg. 0x08100
    data = row[1:]
    record = bytearray.fromhex(''.join([data_size, adress, '00'] + data))
    record.append(twos_complement(sum(record)))
    return ''.join("%02x" % b for b in record)

#--- main
args = parse_arguments()
rows = read_dump(args.infile, NUMBER_OF_BYTES)
result = list(map(parse_row, rows))
output_ihx(args.outfile, result)
