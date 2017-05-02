#! /bin/bash

#
# File to compile and open the pdf version of the document.
#

make clean
make latexpdf
evince _build/latex/SystemCalls.pdf &

