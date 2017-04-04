#!/bin/bash
for n in `seq 5000`
do
   rm nums.dat

   for j in `seq $n`
   do
      echo $RANDOM >> nums.dat
   done
   cat nums.dat | ./main $RANDOM 2>>perc.dat 1>>/dev/null
done
