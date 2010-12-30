#!/bin/sh
# This script generates control flow graph file in xml format from .s .c files
# tab_S.txt is a file that contains cycles and energy information about hardware platform instructions

cd examples

python ../utils/c2cfg.py $1.s $1.c $1.xml ../utils/powerAsm.mod ../utils/powerC.mod $2 ../utils/powerInterInst.pow

cd ..
