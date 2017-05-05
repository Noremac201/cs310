#!/bin/bash

for X in {0..9}
do
   for Y in {0..9}
   do
      for Z in {0..9}
      do
         for I in {0..9}
         do
            for J in {0..9}
            do
               for K in {0..9}
               do
                  for N in {0..9}
                  do
                     for M in {0..9}
                     do
                        for O in {0..9}
                        do
                           NBS=$(printf 3\n$X $Y $Z\n$I $J $K\n$N $M $O | ./beck) 
                           if [[ $NBS -gt 1 ]]
                           then
                              echo 3 >> answers.dat
                              echo $X $Y $Z >> answers.dat;
                              echo $I $J $K >> answers.dat;
                              echo $N $M $O >> answers.dat;
                              printf \n >> answers.dat;
                           fi
                        done
                     done
                  done
               done
            done
            echo out of 5th loop
         done
      done
   done
done

