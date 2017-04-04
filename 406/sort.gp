f(x)=x * log(x) * 2.5
g(x)=x* log(x) * 2
set key off
set xlabel 'Input Size'
set ylabel 'Operation Count'
set title 'Empirical Analysis of Heap Sort Algorithm'
set label 1 '$\frac{5}{2} \log(n)$' at 1500,30500 rotate by 35 font 'Source Code Pro, 11'
set label 2 '$2 \log(n)$' at 2000,27500 rotate by 27 font 'Source Code Pro, 11'
plot f(x) lw 2 lt rgb '#696969', g(x) lw 2 lt rgb '#696969', 'update.dat' using 1:3 pt 7 ps .4 lc black
