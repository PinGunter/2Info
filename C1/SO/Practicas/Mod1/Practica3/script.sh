#! /bin/bash

cont=1

while [ $cont -lt $1 ];
do
	sleep 1
	cont=$((cont+1))
done

echo $cont
