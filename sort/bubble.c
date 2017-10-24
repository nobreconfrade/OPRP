#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

void bubble_sort(int *, unsigned long,int);
void imprimir_vetor(int *, unsigned long);
void verify(int *, unsigned long );

int main(int argc, char *argv[])
{
	struct timeval timevalA;
        struct timeval timevalB;

	int *vetor = NULL;
	unsigned long tam, i = 0;
	unsigned int numThread;

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

	srand(time(NULL));
	for (int j = 0; j < 10; j++) {
		for (i = 0; i < tam; i++) {
			*(vetor + i) = random() % 10000;
		}


		gettimeofday(&timevalA, NULL);
		bubble_sort(vetor, tam,numThread);
		gettimeofday(&timevalB, NULL);
		// imprimir_vetor(vetor,tam);
		printf("%lf\n", timevalB.tv_sec - timevalA.tv_sec + (timevalB.tv_usec - timevalA.tv_usec) / (double) 1000000);
		verify(vetor,tam);
	}

	// vetor[59999] = ;
	// imprimir_vetor(vetor, tam);
	free(vetor);
	return EXIT_SUCCESS;
}

void verify(int *vetor, unsigned long tam){
	int x;
	x = vetor[0];
	for (int i = 0; i < tam; i++) {
		if (x > vetor[i]) {
			printf("TA ERRADO MANO\n");
			break;
		}
		x = vetor[i];
	}
}


void bubble_sort(int *vetor, unsigned long tam, int numThread)
{
	unsigned long i, j;
	int aux,start;
	for (i = tam; i > 0; i--) {
		start = i % 2;
		#pragma omp parallel for schedule(static) num_threads(numThread) shared(i,vetor,start,tam) private(aux,j)
		for (j = start; j < tam - 1; j+=2){
			if (vetor[j] > vetor[j + 1]) {
				aux = vetor[j];
				vetor[j] = vetor[j + 1];
				vetor[j + 1] = aux;
			}
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
