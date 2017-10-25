#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>

void selection_sort(int *, unsigned long, unsigned int);
void imprimir_vetor(int *, unsigned long);
void verify(int *, unsigned long);

int main(int argc, char *argv[])
{
	struct timeval timevalA;
        struct timeval timevalB;

	int *vetor = NULL;
	unsigned long tam, i = 0;
	unsigned int numThread;
	int count;

	if (argc != 3) {
		printf("%s elementos e numero de threads\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	tam = atoi(argv[1]);
	numThread = atoi(argv[2]);

	if (!(vetor = (int *) malloc(sizeof(int) * tam))) {
		printf("Erro ao alocar memória\n");
		exit(EXIT_FAILURE);
	}

	double sum = 0.0;

	srand(time(NULL));
	for (count = 0; count < 10; count++) {
		for (i = 0; i < tam; i++) {
			*(vetor + i) = random() % 10000;
		}
		gettimeofday(&timevalA, NULL);
		selection_sort(vetor, tam, numThread);
		gettimeofday(&timevalB, NULL);
		verify(vetor,tam);

		double t = timevalB.tv_sec - timevalA.tv_sec + (timevalB.tv_usec - timevalA.tv_usec) / (double) 1000000;
		sum += t;
		printf("%lf\n", t);
	}
	printf("#\t%lf\t%u\t%lu\n", sum/10.0, numThread, tam);

	free(vetor);
	return EXIT_SUCCESS;
}


void selection_sort(int *vetor, unsigned long tam, unsigned int numThread)
{
	unsigned long i, j, min, c;
	int aux, *vetmin;

	vetmin = (int *)malloc(sizeof(int) * numThread);

	for (i = 0; i < tam - 1; i++) {
		for (c = 0; c < numThread; ++c)
			vetmin[c] = i;

		#pragma omp parallel for schedule(static) num_threads(numThread) shared(i, min, vetmin,vetor) private(j)
		for (j = i + 1; j < tam; j++) {
			if (vetor[j] < vetor[vetmin[omp_get_thread_num()]]) {
        vetmin[omp_get_thread_num()] = j;
			}
    }

    int k = 0;
    min = vetmin[k];
    for (k = 1; k < numThread; ++k){
    	if (vetor[min] > vetor[vetmin[k]])
    		min = vetmin[k];
    }

		if (vetor[i] != vetor[min]) {
			aux = vetor[i];
			vetor[i] = vetor[min];
			vetor[min] = aux;
		}
	}
}

void imprimir_vetor(int *vetor, unsigned long tam)
{
	unsigned long i;
	for (i = 0; i < tam; i++) {
		printf("%d\t", vetor[i]);
	}
	printf("\n");
}

void verify(int *vetor, unsigned long tam){
	for (int i = 0; i < tam - 1; i++) {
		if (vetor[i] > vetor[i+1]) {
			printf("TA ERRADO MANO\n");
			break;
		}
	}
}