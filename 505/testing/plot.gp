set style line 2 lc rgb 'grey' lt 1 lw 1
set style data histogram
set style histogram cluster gap 1
set style fill pattern border -1

set ylabel "Basic Operations"
set xlabel "Type of Modification"
set style fill solid
set boxwidth 0.9
set yrange[0:250]
set key off
set xtics format ""
set grid ytics

set title "Average Basic Operations by Modification with 4x4 Input Size"
plot "plot.dat" using 2:xtic(1) ls 2
