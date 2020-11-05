#!/bin/bash
free | awk '/total/{ print "\t" $2 "\t" $3} /Mem:|Swap:/{ print $1 "\t" $3 "\t"$4}' > ~/log/free-`date +%Y-%j-%T`
