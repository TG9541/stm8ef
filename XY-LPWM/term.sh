#!/bin/sh

# https://wiki.forth-ev.de/doku.php/en:projects:e4thcom

if [ "$1" eq "" ]; then
    COM=ttyUSB0
else
    COM=$1
fi

e4thcom-0.6.3 -t stm8ef -p .:../lib -d ttyUSB0

