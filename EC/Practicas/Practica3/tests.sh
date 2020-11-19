# !/bin/bash
debug="-D CALC=1"
for i in 0 g 1 2; do
    for k in `seq 1 1 10`; do
        archivo="resultados/popcountO$i"
        gcc popcount.c -o popcount -O$i -g -D TEST=0 $debug 
        echo "Iteracion $k" >> $archivo
        ./popcount >> $archivo
        rm popcount
    done
done