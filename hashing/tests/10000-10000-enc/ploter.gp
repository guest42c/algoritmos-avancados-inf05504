set term svg enh
set output "insert-10000-10000.svg"
set title "Crescimento das iterações"
set ylabel "Iterações"
set xlabel "Número de arestas"
#set yrange [0:900]
set xrange [0:1.2]
#set autoscale
plot "experiment-10000-10000-inserts" using 1:2:(0):($4-$2) with vec nohead lt -1 notit, "" using 1:3 w p lt 1 ps 0.6 pt 7 notit

set term svg enh
set output "lookup-10000-10000.svg"
set title "Crescimento das iterações"
set ylabel "Iterações"
set xlabel "Número de arestas"
#set yrange [0:900]
set xrange [0:1.2]
#set autoscale
plot "experiment-10000-10000-lookups" using 1:2:(0):($4-$2) with vec nohead lt -1 notit, "" using 1:3 w p lt 1 ps 0.6 pt 7 notit

#set term svg enh
#set output "iterlim-50-50-100.svg"
#set title "Crescimento das iterações"
#set ylabel "Iterações"
#set xlabel "Número de arestas"
#set yrange [0:8000]
#plot "experiment-50-50-100-iter" using 1:2:(0):($4-$2) with vec nohead lt -1 notit, "" using 1:3 w p lt 1 ps 0.6 pt 7 notit, "" using ($1):(($1)*(log($5)/log($1))) w linesp title "m logm U"

#set term svg enh
#set output "time-50-50-100.svg"
#set title "Tempo de execução"
#set ylabel "Tempo de execução (ms) / Complexidade esperada"
#set xlabel "Número de arestas"
#set autoscale
#plot "experiment-50-50-100-time" using ($1):($3)/((($6)*(log($6)/log(2))+($1))*(($1)*(log($5)/log($1)))) w linesp notit

