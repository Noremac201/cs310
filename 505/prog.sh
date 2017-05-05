#!/bin/bash
gen_rand () {
   echo gen_rands
   rm input.dat
   echo 4 >> input.dat
      for n in `seq 4`
      do
         echo $(( ( RANDOM % 4 )  + 1 )) $(( ( RANDOM % 4 )  + 1 )) $(( ( RANDOM % 4) + 1 )) $(( ( RANDOM % 4) + 1)) >> input.dat
   done
}
rm data.dat
rm beck.dat
for i in `seq 5000`
do
gen_rand
./main < input.dat 1>>/dev/null 2>>data.dat
./beck < input.dat 1>>/dev/null 2>>beck.dat
done
