#!/bin/sh

## This script generates a .s file with line of code information
cd examples/
rm -f $1.s
#arm-none-eabi-gcc -S -g $1.c
arm-linux-gcc -S -g $1.c
#../../arm-2007q3/bin/arm-none-eabi-gcc -S -g $1.c

cd ..


