#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

void bubble_sort(int *, unsigned long);
void imprimir_vetor(int *, unsigned long);
int validador(int *, unsigned long);

int main(int argc, char *argv[])
{
	struct timeval timevalA;
        struct timeval timevalB;

	int *vetor = NULL;
	unsigned long tam, i = 0;

	if (argc != 2) {
		printf("%s elementos\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	tam = atoi(argv[1]);

	if (!(vetor = (int *) malloc(sizeof(int) * tam))) {
		printf("Erro ao alocar memória\n");
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));
	int j;
	double sum = 0;
	for (j = 0; j < 10; ++j){
		for (i = 0; i < tam; i++) {
			*(vetor + i) = random() % 10000;
		}

		gettimeofday(&timevalA, NULL);
		bubble_sort(vetor, tam);
		gettimeofday(&timevalB, NULL);

		double t = timevalB.tv_sec - timevalA.tv_sec + (timevalB.tv_usec - timevalA.tv_usec) / (double) 1000000;
		sum += t;
		// printf("%lf\n", t);
	}

	printf("bubble %lf\n", sum/10.0);
	//imprimir_vetor(vetor, tam);

	free(vetor);
	return EXIT_SUCCESS;
}

void bubble_sort(int *vetor, unsigned long tam)
{
	unsigned long i, j;
	int aux;

	for (i = tam - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (vetor[j] > vetor[j + 1]) {
				aux = vetor[j];
				vetor[j] = vetor[j + 1];
				vetor[j + 1] = aux;
			}
		}
	}
}

int validador(int *vetor, unsigned long tam)
{
	unsigned long i;
	for (i = 0; i < tam - 1; i++) {
		if (vetor[i] > vetor[i + 1]) {
			return 0;
		}
	}
	return 1;
}

void imprimir_vetor(int *vetor, unsigned long tam)
{
	unsigned long i;
	for (i = 0; i < tam; i++) {
		printf("%d\t", vetor[i]);
	}
	printf("\n");
}
