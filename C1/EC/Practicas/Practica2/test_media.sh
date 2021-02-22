#!/bin/bash
for i in `seq 1 1 19`; do
    rm media32b
    gcc -x assembler-with-cpp -D TEST=$i -no-pie media32b.s -o media32b
    printf "__TEST%02d__%35s\n" $i "" | tr " " "-" ; ./media32b
done