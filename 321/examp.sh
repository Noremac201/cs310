#!/bin/bash

for n in `seq 100` #where 100 is the number of pairs of points
do
   head -$n points.dat | ./gauer_321 2>>data.dat
done
