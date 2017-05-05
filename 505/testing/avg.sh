#!/bin/bash
rm plot.dat
awk '{ total +=  } END { print total/NR }' beck.dat >> plot.dat
awk '{ total +=  } END { print total/NR }' both.dat >> plot.dat
awk '{ total +=  } END { print total/NR }' baseline.dat >> plot.dat
awk '{ total +=  } END { print total/NR }' brek.dat >> plot.dat
