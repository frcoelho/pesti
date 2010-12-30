#!/bin/sh
# This script builds executable file "pesti"

rm -f build/*
gcc -I /usr/include/libxml2/ -I include/ -L /usr/lib/ -o build/pesti src/simul-engine.c src/control-flow-graph.c src/random-number.c src/monte-carlo.c src/main.c -lxml2


