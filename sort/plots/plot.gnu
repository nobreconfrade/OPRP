#gnuplot -e "set xrange [0:10]; set term png; set output 'print.png'; stats \$data using ;plot 'resultados/$script.txt'"

# BUBBLE

set title 'Bubble Sort'
set xlabel 'Número de Threads'
set ylabel 'Tempo'
set xtics 1
# set yrange[0:0.000012]
set xrange [0:11]

set term png
set output "Bubble_50000.png"
plot 'speedupBubble_50000.csv' u 2:1 with line linewidth 2 title 'Bubble 50000'
reset

# SELECTION
set title 'Selection Sort'
set xlabel 'Número de Threads'
set ylabel 'Tempo'
#set xtics [10:110]
# set yrange[0:0.000012]
set xrange [0:11]

set term png
set output "Selection_50000.png"
plot 'speedupSelection_50000.csv' u 2:1 with line linewidth 2 title 'Selection 50000'
reset

# COMB
set title 'Comb Sort'
set xlabel 'Número de Threads'
set ylabel 'Tempo'
#set xtics [10:110]
# set yrange[0:0.000012]
set xrange [0:11]

set term png
set output "Comb_50000.png"
plot 'speedupComb_50000.csv' u 2:1 with line linewidth 2 title 'Comb 50000'
reset
