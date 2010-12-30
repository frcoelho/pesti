#!/bin/sh
# This script generates control flow graph file in xml format from .s .c files
# tab_S.txt is a file that contains cycles and energy information about hardware platform instructions

# Usage: ./c2cfg.sh <program> <pipelines> <start> <end> <step>
# Note: the last 3 parameter are optional

# Example: ./c2cfg.sh bolha 6 0.45 0.55 0.3

cd examples

filename=$1
pipelines=$2
shift; shift

python ../utils/c2cfg.py $filename.s $filename.c $filename.xml ../utils/powerAsm.mod ../utils/powerC.mod $pipelines ../utils/powerInterInst.pow "$@"

cd ..
