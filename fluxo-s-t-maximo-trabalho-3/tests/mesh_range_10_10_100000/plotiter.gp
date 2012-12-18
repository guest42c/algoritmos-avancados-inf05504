set term svg enh
set output "iter-10-10-100000.svg"
set title "Crescimento das iterações"
set ylabel "Iterações"
set xlabel "Capacidade máxima para os arcos"
set yrange [0:200]
plot "experiment-range-10-10-100000-iter" using 1:2:(0):($4-$2) with vec nohead lt -1 notit, "" using 1:3 w p lt 1 ps 0.6 pt 7 notit

set term svg enh
set output "time-10-10-100000.svg"
set title "Tempo de execução x limite superior da capacidade dasarestas"
set ylabel "Running time (ms)"
set xlabel "Range"
set autoscale
plot "experiment-range-10-10-100000-time" using ($5):($3)/((($6)*(log($6)/log(2))+($1))*(($1)*(log($5)/log($1)))) w linesp notit

