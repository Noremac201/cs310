f(x)=2.25*(log(x)/log(2))
set key off
set yrange [0:30]
set xrange [10:5000]
set xlabel 'Input Size'
set ylabel 'Operation Count'
set title 'Empirical Analysis of Percolate Down Algorithm'
set label 2 '$\frac{3}{2} \log(n)$' at 2000,24.5 rotate by 9 font 'Source Code Pro, 11'
plot f(x) lw 2 lt rgb '#696969', 'perc.dat' using 1:2 pt 7 ps .4 lc black
