#!/bin/bash

for n in `seq 10000`
do
   rm input.dat
   for j in `seq $n`
   do
      echo $RANDOM $RANDOM >> input.dat
   done
   #main is the name of your executable, output is output
   ./main < input.dat 2>>data.dat
done

