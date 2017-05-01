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
./main < input.dat 1>>/dev/null 2>data.dat

while [ true ]
do

NBS="$(tail -1 data.dat)"
if [ $NBS -gt 1 ]
then
   cat input.dat >> answers.txt
   printf "\n" >> answers.txt 
break
fi
echo loping
done
