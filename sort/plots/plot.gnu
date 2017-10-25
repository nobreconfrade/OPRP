#gnuplot -e "set xrange [0:10]; set term png; set output 'print.png'; stats \$data using ;plot 'resultados/$script.txt'"

# BUBBLE 

set title 'Bubble Sort'
set xlabel 'Número de Threads' 
set ylabel 'Tempo'
set xtics 1
# set yrange[0:0.000012] 
# set xrange [0:10]

set term png
set output "Bubble.png"
plot 'resultadosBubble.csv' u 2:1 with line linewidth 4 title 'Bubble' 
reset 

# SELECTION
set title 'Selection Sort'
set xlabel 'Número de Threads' 
set ylabel 'Tempo'
#set xtics [10:110]
# set yrange[0:0.000012] 
# set xrange [0:10]

set term png
set output "Selection.png"
plot 'resultadosSelection.csv' u 2:1 with line linewidth 4 title 'Selection' 
reset 

# COMB
set title 'Comb Sort'
set xlabel 'Número de Threads' 
set ylabel 'Tempo'
#set xtics [10:110]
# set yrange[0:0.000012] 
# set xrange [0:10]

set term png
set output "Comb.png"
plot 'resultadosComb.csv' u 2:1 with line linewidth 4 title 'Comb' 
reset 
