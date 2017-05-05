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
rm beck.dat
rm both.dat
rm baseline.dat
rm brek.dat
for i in `seq 5000`
do
gen_rand
./beck < input.dat 1>>/dev/null 2>>beck.dat
./both < input.dat 1>>/dev/null 2>>both.dat
./baseline < input.dat 1>>/dev/null 2>>baseline.dat
./brek < input.dat 1>>/dev/null 2>>brek.dat
./clb < input.dat 1>>/dev/null 2>>clb.dat
done
