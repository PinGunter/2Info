#!/bin/bash

for i in `ls /tmp/varios/core*`; do
	rm -v $i >> /tmp/listacores
done
