set term svg enh
set output "iter-50-50-5.svg"
set title "Iterations growth"
set ylabel "Iterations"
set xlabel "Number of edges"
set yrange [0:900]
#set xrange [0:900]
plot "experiment-50-50-5-iter" using 1:2:(0):($4-$2) with vec nohead lt -1 notit, "" using 1:3 w p lt 1 ps 0.6 pt 7 notit

set term svg enh
set output "iterlim-50-50-5.svg"
set title "Iterations growth"
set ylabel "Iterations"
set xlabel "Number of edges"
set yrange [0:8000]
plot "experiment-50-50-5-iter" using 1:2:(0):($4-$2) with vec nohead lt -1 notit, "" using 1:3 w p lt 1 ps 0.6 pt 7 notit, "" using ($1):(($1)*(log(($1)*($5))/log(2))) w linesp title "m logU"

set term svg enh
set output "lim-50-50-5.svg"
set title "Iterations growth"
set ylabel "Iterations"
set xlabel "Number of edges"
set yrange [0:200000]
plot "experiment-50-50-5-iter" using ($1):(($1)*(log(($1)*($5))/log(2))) w linesp title "m logU"

set term svg enh
set output "time-50-50-5.svg"
set title "Runing time growth"
set ylabel "Running time (ms)"
set xlabel "Number of edges"
set yrange [0:30000]
set xrange [0:8000]
plot "experiment-50-50-5-time" using 1:2:(0):($4-$2) with vec nohead lt -1 notit, "" using 1:3 w p lt 1 ps 0.6 pt 7 notit

