#!/bin/sh

if [ "$#" -ne 1 ]; then
    echo "Falta parametro: <quantidade maxima de threads>"
    return
fi

gcc -Wall bubble.c    -fopenmp -o bubble
gcc -Wall selection.c -fopenmp -o selection
gcc -Wall comb.c      -fopenmp -o comb 

mkdir -p resultados

LINE="media   numThread    tam"
echo $LINE >> resultados/"bubble.txt" 

maxThreads=$1
# for tam in 10000; do
tam=100000
	for numThreads in $(seq 1 $maxThreads); do
		./bubble $tam $numThreads >> resultados/"bubble.txt"
		./selection $tam $numThreads >> resultados/"selection.txt"
		./comb $tam $numThreads >> resultados/"comb.txt"
	done
done

rm bubble selection comb

# depois pegar as medias e jogar no arquivo resultados.txt