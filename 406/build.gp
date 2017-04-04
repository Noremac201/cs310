f(x)=2*x
g(x)=1.75*x
set key off
set xlabel 'Input Size'
set ylabel 'Operation Count'
set title 'Empirical Analysis of Build Heap Algorithm'
set label 1 '$2n$' at 1500,3333 rotate by 37 font 'Source Code Pro, 11'
set label 2 '$\frac{7}{8} n$' at 2000,3200 rotate by 33 font 'Source Code Pro, 11'
plot f(x) lw 2 lt rgb '#696969', g(x) lw 2 lt rgb '#696969', 'update.dat' using 1:2 pt 7 ps .4 lc black
