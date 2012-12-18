set term svg enh
set output "iter-40-40-10000.svg"
set title "Crescimento das iterações"
set ylabel "Iterações"
set xlabel "Número de arestas"
set yrange [0:500]
#set xrange [0:900]
plot "experiment-40-40-10000-iter" using 1:2:(0):($4-$2) with vec nohead lt -1 notit, "" using 1:3 w p lt 1 ps 0.6 pt 7 notit

set term svg enh
set output "iterlim-40-40-10000.svg"
set title "Crescimento das iterações"
set ylabel "Iterações"
set xlabel "Número de arestas"
set yrange [0:4000]
plot "experiment-40-40-10000-iter" using 1:2:(0):($4-$2) with vec nohead lt -1 notit, "" using 1:3 w p lt 1 ps 0.6 pt 7 notit, "" using ($1):(($1)*(log($5)/log($1))) w linesp title "m logm U"

set term svg enh
set output "time-40-40-10000.svg"
set title "Tempo de execução"
set ylabel "Tempo de execução (ms) / Complexidade esperada"
set xlabel "Número de arestas"
set autoscale
plot "experiment-40-40-10000-time" using ($1):($3)/((($6)*(log($6)/log(2))+($1))*(($1)*(log($5)/log($1)))) w linesp notit

