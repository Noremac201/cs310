#!/bin/bash

for n in `seq 100`
do
   echo $n
   tail -$n points.dat | ./main 2>>data.dat
done

