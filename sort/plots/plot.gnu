#gnuplot -e "set xrange [0:10]; set term png; set output 'print.png'; stats \$data using ;plot 'resultados/$script.txt'"

# BUBBLE 

set title 'Bubble Sort'
set xlabel 'Número de Threads' 
set ylabel 'Tempo'
set xtics 1
# set yrange[0:0.000012] 
# set xrange [0:10]

set term png
set output "Bubble_50000.png"
plot 'mediasBubble_50000.csv' u 2:1 with line linewidth 2 title 'Bubble' 
reset 

# SELECTION
set title 'Selection Sort'
set xlabel 'Número de Threads' 
set ylabel 'Tempo'
#set xtics [10:110]
# set yrange[0:0.000012] 
# set xrange [0:10]

set term png
set output "Selection_50000.png"
plot 'mediasSelection_50000.csv' u 2:1 with line linewidth 2 title 'Selection' 
reset 

# COMB
set title 'Comb Sort'
set xlabel 'Número de Threads' 
set ylabel 'Tempo'
#set xtics [10:110]
# set yrange[0:0.000012] 
# set xrange [0:10]

set term png
set output "Comb_50000.png"
plot 'mediasComb_50000.csv' u 2:1 with line linewidth 2 title 'Comb' 
reset 
