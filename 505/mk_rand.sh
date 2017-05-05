#!/bin/bash
gen_rand () {
   echo gen_rands
   rm input.dat
   echo 4 >> input.dat
      for n in `seq 4`
      do
         echo $(( ( RANDOM % 4 )  + 1 )) $(( ( RANDOM % 4 )  + 1 )) $(( ( RANDOM % 4 )  + 1 )) $(( ( RANDOM % 4 )  + 1 ))>> input.dat
   done
}

gen_rand
echo me
./main < input.dat 2>>/dev/null
echo beck
./beck < input.dat 2>>/dev/null

