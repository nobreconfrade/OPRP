#!/bin/sh

if [ "$#" -ne 2 ]; then
    echo "Falta parametro: <quantidade maxima de threads> <elementos>"
    return
fi

gcc -Wall bubble.c    -fopenmp -o bubble
gcc -Wall selection.c -fopenmp -o selection
gcc -Wall comb.c      -fopenmp -o comb 

mkdir -p resultados

# LINE="media   numThread    tam"
# echo $LINE >> resultados/"bubble.txt" 

maxThreads=$1
tam=$2
# for tam in 10000; do
	for numThreads in $(seq 1 $maxThreads); do
		echo "$numThreads"
		echo "bubble rodando"
		./bubble $tam $numThreads >> resultados/"bubble.txt"
		echo "selection rodando"
		./selection $tam $numThreads >> resultados/"selection.txt"
		echo "comb rodando"
		./comb $tam $numThreads >> resultados/"comb.txt"
	# done
done

rm bubble selection comb

# depois pegar as medias e jogar no arquivo resultados.txt
touch plots/"mediasBubble_$tam".csv 
touch plots/"mediasSelection_$tam".csv 
touch plots/"mediasComb_$tam".csv