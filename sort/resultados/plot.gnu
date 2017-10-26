#gnuplot -e "set xrange [0:10]; set term png; set output 'print.png'; stats \$data using ;plot 'resultados/$script.txt'"

# BUBBLE

set title 'Bubble Sort'
set xlabel 'Número de Threads'
set ylabel 'Tempo'
set xtics 1
# set ytics 0.1
# set yrange[0:0.9]
set xrange [0:11]

set term png
set output "../plots/Bubble_50000.png"
plot 'speedupBubble_50000.csv' u 2:1 with line linewidth 2 title 'Bubble 50000'
reset

set title 'Bubble Sort'
set xlabel 'Número de Threads'
set ylabel 'Tempo'
set xtics 1
# set ytics 0.1
# set yrange[0:0.9]
set xrange [0:11]

set term png
set output "../plots/Bubble_100000.png"
plot 'speedupBubble_100000.csv' u 2:1 with line linewidth 2 title 'Bubble 100000'
reset


# SELECTION
set title 'Selection Sort'
set xlabel 'Número de Threads'
set ylabel 'Tempo'
set xtics 1
set ytics 0.11
#set xtics [10:110]
set yrange[0:1.21]
set xrange [0:11]

set term png
set output "../plots/Selection_50000.png"
plot 'speedupSelection_50000.csv' u 2:1 with line linewidth 2 title 'Selection 50000'
reset

set title 'Selection Sort'
set xlabel 'Número de Threads'
set ylabel 'Tempo'
set xtics 1
set ytics 0.11
#set xtics [10:110]
set yrange[0:1.21]
set xrange [0:11]

set term png
set output "../plots/Selection_100000.png"
plot 'speedupSelection_100000.csv' u 2:1 with line linewidth 2 title 'Selection 100000'
reset

# COMB
set title 'Comb Sort'
set xlabel 'Número de Threads'
set ylabel 'Tempo'
set xtics 1
set ytics 0.066
#set xtics [10:110]
set yrange[0	:0.73]
set xrange [0:11]

set term png
set output "../plots/Comb_50000.png"
plot 'speedupComb_50000.csv' u 2:1 with line linewidth 2 title 'Comb 50000'
reset

set title 'Comb Sort'
set xlabel 'Número de Threads'
set ylabel 'Tempo'
set xtics 1
set ytics 0.09
#set xtics [10:110]
set yrange[0:1]
set xrange [0:11]

set term png
set output "../plots/Comb_100000.png"
plot 'speedupComb_100000.csv' u 2:1 with line linewidth 2 title 'Comb 100000'
reset