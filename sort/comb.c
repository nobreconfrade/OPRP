#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>

void comb_sort(int *, unsigned long, unsigned int);
void imprimir_vetor(int *, unsigned long);
void verify(int *, unsigned long);

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

	double sum = 0.0;

	srand(time(NULL));
	for (int j = 0; j < 10; j++) {
		for (i = 0; i < tam; i++) {
			*(vetor + i) = random() % 10000;
		}

		gettimeofday(&timevalA, NULL);
		comb_sort(vetor, tam,numThread);
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

void comb_sort(int *vetor, unsigned long tam,unsigned int numThread)
{
	unsigned int i;
	int intervalo, trocado = 1;
	int aux;

	intervalo = tam;

	while (intervalo > 1 || trocado == 1)
	{
		intervalo = intervalo * 10 / 13;
		if (intervalo == 9 || intervalo == 10) {
			intervalo = 11;
		}
		if (intervalo < 1) {
			intervalo = 1;
		}

		trocado = 0;
		#pragma omp parallel for schedule(static) num_threads(numThread) shared(vetor,tam,intervalo,trocado) private(aux,i)
		for (i = 0; i < tam - intervalo; i++)
		{
			if (vetor[i] > vetor[i+intervalo])
			{
				aux = vetor[i];
				vetor[i] = vetor[i+intervalo];
				vetor[i+intervalo] = aux;
				trocado = 1;
			}
		}
	}

}

void verify(int *vetor, unsigned long tam){
	for (int i = 0; i < tam - 1; i++) {
		if (vetor[i] > vetor[i+1]) {
			printf("TA ERRADO MANO\n");
			break;
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
