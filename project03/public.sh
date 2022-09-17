#!/bin/bash

for i in {1..13};
do
    p=`printf %02d $i`
    echo ""
    echo "Running public$p"
    gcc public$p.c machine.c -o public$p.x
    ./public$p.x | diff -b - public$p.output
done
