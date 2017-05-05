#!/bin/bash

count=0;
total=0; 

for i in $( awk '{ print $2; }' data.dat )
   do 
     total=$(echo $total+$i | bc )
     ((count++))
   done
echo "scale=2; $total / $count" | bc

for i in $( awk '{ print $2; }' beck.dat )
   do 
     total=$(echo $total+$i | bc )
     ((count++))
   done
echo "scale=2; $total / $count" | bc
