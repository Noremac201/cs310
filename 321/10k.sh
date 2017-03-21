#!/bin/bash
for n in `seq 5000`
do
   echo $n
   head -$n input.dat | ./main 2>>data.dat
done
