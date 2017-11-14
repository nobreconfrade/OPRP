/*
 *  Exemplo de programa para multiplicacao de matrizes em paralelo.
 *  Para fins de simplificacao, as matrizes devem ser quadradas.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <mpi.h>
#include "matrix.h"

#define MASTER 0        // id do mestre
#define MSG_TAG 0       // tag das mensagens

matrix_t *matrix_mult(matrix_t *A, matrix_t *B, matrix_t *C, int start)
{
  int i, j, k;

  int count = C->cols;

  for (i = start; i < A->rows; i++) {
     for (j = 0; j < B->cols; j++) {
        double sum = 0.0;
        for (k = 0; k < count; k++) {
           sum += A->data[i][k] * B->data[k][j];
        }
        C->data[i][j] = sum;
     }
  }
}

int main(int argc, char **argv)
{
  int n;
  int rc;
  int taskid, ntasks;
  double start_time, end_time;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

  if ((argc != 2)) {
    printf("Uso: mpirun -np <nprocs> %s <ordem da matriz quadrada>\n",
           argv[0]);
    MPI_Abort(MPI_COMM_WORLD, rc);
    exit(1);
  }

  n = atoi(argv[1]); //mestre e escravos sabem o tamanho da matriz

  matrix_t *A_mestre = NULL;
  matrix_t *C_mestre = NULL;
  matrix_t *A_escravo  = NULL;
  matrix_t *C_escravo = NULL;

  matrix_t *B = matrix_create(n, n); //mestre e escravos alocam B

  int linha = n / ntasks;
  int resto = n % ntasks;
  A_mestre = matrix_create(n, n);
  C_mestre = matrix_create(n, n);
  A_escravo = matrix_create(linha, n);
  C_escravo = matrix_create(linha, n);

  if (taskid == MASTER) {  // Codigo executado pelo processo mestre
    matrix_randfill(B);
    matrix_randfill(A_mestre);
    start_time = MPI_Wtime();
  }

  MPI_Bcast(&B->data[0][0], B->rows * B->cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  MPI_Scatter(&A_mestre->data[0][0], linha*n, MPI_DOUBLE, &A_escravo->data[0][0], linha*n, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);

  if (taskid == MASTER) {
    if (resto != 0) {
      matrix_mult(A_mestre, B, C_mestre, n-resto);
    }
  }

  matrix_mult(A_escravo, B, C_escravo, 0);


  MPI_Gather(&C_escravo->data[0][0], linha*n, MPI_DOUBLE, &C_mestre->data[0][0], linha*n, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);

  if (taskid == MASTER) {
    end_time = MPI_Wtime();
    printf("%d %f\n", ntasks, end_time - start_time);
    // matrix_print(C_mestre);
  }

  matrix_destroy(B);
  matrix_destroy(A_escravo);
  matrix_destroy(A_mestre);
  matrix_destroy(C_escravo);
  matrix_destroy(C_mestre);

  MPI_Finalize();
  return 0;
}
