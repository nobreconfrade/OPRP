#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void bubble_sort(int *, unsigned long,int);
void imprimir_vetor(int *, unsigned long);
void verify(int *, unsigned long );

int main(int argc, char *argv[])
{
	struct timeval timevalA;
        struct timeval timevalB;

	int *vetor = NULL;
	unsigned long tam, i = 0;
	unsigned int num_thread;

	if (argc != 3) {
		printf("%s elementos\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	tam = atoi(argv[1]);
	num_thread = atoi(argv[2]);

	if (!(vetor = (int *) malloc(sizeof(int) * tam))) {
		printf("Erro ao alocar memória\n");
		exit(EXIT_FAILURE);
	}

	for (int j = 0; j < 10; j++) {
		srand(time(NULL));
		for (i = 0; i < tam; i++) {
			*(vetor + i) = random() % 10000;
		}


		gettimeofday(&timevalA, NULL);
		bubble_sort(vetor, tam,num_thread);
		gettimeofday(&timevalB, NULL);
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


void bubble_sort(int *vetor, unsigned long tam, int num_thread)
{
	unsigned long i, j;
	int aux,start;
	for (i = tam; i > 0; i--) {
		start = i % 2;
		#pragma omp parallel for schedule(static) num_threads(num_thread) shared(i,vetor,start) private(aux,j)
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
