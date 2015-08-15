#!/bin/sh

#  compileAndRun.sh
#  
#
#  Created by Stefan Dierauf on 1/15/15.
#


gcc -Wall -g -std=c11 -o GetPrime.o -c GetPrime.c
gcc -Wall -g -std=c11 -o ex4.o -c ex4.c
gcc -Wall -g -std=c11 -o ex4 ex4.o GetPrime.o
./ex4
