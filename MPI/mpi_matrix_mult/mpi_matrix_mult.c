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


// Envia matriz 'm' para processo 'dest'.
void mpi_send_matrix(matrix_t *m)
{

// Mestre e escravos sabem o tamanho da matriz via MPI_Init
//   MPI_Send(&m->rows, 1, MPI_INT, dest, MSG_TAG, MPI_COMM_WORLD);
//   MPI_Send(&m->cols, 1, MPI_INT, dest, MSG_TAG, MPI_COMM_WORLD);
//   MPI_Send(&m->data[0][0], m->rows * m->cols, MPI_DOUBLE, dest, MSG_TAG,
//            MPI_COMM_WORLD);

}

// Envia um bloco da matriz 'm' para processo 'dest'.
// Atencao: so funciona para blocos contendo linha completas.
void mpi_send_submatrix(matrix_t *m, block_t part, int dest)
{
   int rows = part.row_end - part.row_start;
   int cols = part.col_end - part.col_start;
   assert(cols == m->cols);

   MPI_Send(&rows, 1, MPI_INT, dest, MSG_TAG, MPI_COMM_WORLD);
   MPI_Send(&cols, 1, MPI_INT, dest, MSG_TAG, MPI_COMM_WORLD);
   MPI_Send(&m->data[part.row_start][0], rows * cols, MPI_DOUBLE, dest,
            MSG_TAG, MPI_COMM_WORLD);
}

// Recebe matriz do processo 'source'.
matrix_t *mpi_recv_matrix(int source)
{
   MPI_Status status;
   matrix_t *m;
   int rows, cols;
   MPI_Recv(&rows, 1, MPI_INT, source, MSG_TAG, MPI_COMM_WORLD,
            &status);
   MPI_Recv(&cols, 1, MPI_INT, source, MSG_TAG, MPI_COMM_WORLD,
            &status);
   m = matrix_create(rows, cols);
   MPI_Recv(&m->data[0][0], rows * cols, MPI_DOUBLE, source, MSG_TAG,
            MPI_COMM_WORLD, &status);
   return m;
}


// Recebe um bloco da matriz 'm' calculado pelo processo 'source'.
void mpi_recv_submatrix(matrix_t *m, block_t part, int source)
{
   MPI_Status status;
   int rows, cols;
   MPI_Recv(&rows, 1, MPI_INT, source, MSG_TAG, MPI_COMM_WORLD,
            &status);
   MPI_Recv(&cols, 1, MPI_INT, source, MSG_TAG, MPI_COMM_WORLD,
            &status);
   assert(cols == m->cols);
   MPI_Recv(&m->data[part.row_start][0], rows * cols, MPI_DOUBLE, source, MSG_TAG,
            MPI_COMM_WORLD, &status);
}

// Funcao executada pelos processos trabalhadores
void matrix_mult_slave(matrix_t * A, matrix_t * B, matrix_t * C, int n, int linha)
{
   C = matrix_multiply(A, B);
// PARAMOS AQUIIIIIIIIIIIII
   matrix_t *m;
   int i, j, k, count;
   double sum;

   assert(A->cols == B->rows);
   m = matrix_create(A->rows, B->cols);
   count = A->cols;

   for (i = 0; i < m->rows; i++) {
      for (j = 0; j < m->cols; j++) {
         sum = 0.0;
         for (k = 0; k < count; k++) {
            sum += A->data[i][k] * B->data[k][j];
         }
         m->data[i][j] = sum;
      }
   }
   return m;




   }
}



// Funcao de multiplicacao executada pelo processo mestre
void matrix_mult_master(matrix_t *A, matrix_t *B, matrix_t *C, int linha, int n, int start)
{
  for (i = start; i < n; i++) {
     for (j = 0; j < n; j++) {
        double sum = 0.0;
        for (k = 0; k < n; k++) {
           sum += A->data[i][k] * B->data[k][j];
        }
        C->data[i][j] = sum;
     }
  }
  // return C;
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

  if (taskid == MASTER) {  // Codigo executado pelo processo mestre
    A_mestre = matrix_create(n, n);
    C_mestre = matrix_create(n, n);
    matrix_randfill(B);
    matrix_randfill(A_mestre);
  }
  A_escravo = matrix_create(linha, n);
  C_escravo = matrix_create(linha, n);

  MPI_Bcast(&m->data[0][0], m->rows * m->cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  MPI_Scatter(A_mestre, n  *n, MPI_DOUBLE, A_escravo, linha*n, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);

  if (taskid == MASTER) {  // Codigo executado pelo processo mestre
    if (resto != 0) {
      start_time = MPI_Wtime();
      matrix_mult_master(A_mestre, B, C_mestre, linha, n, n - resto);
      end_time = MPI_Wtime();
    }
    // Calcula C = A * B, medindo o tempo

    // Mostra estatisticas da execucao
    printf("%d %f\n", ntasks, end_time - start_time);
    fflush(stdout);


  } else { // Codigo executado pelos processos trabalhadores
    matrix_mult_slave(B,n);
  }

  MPI_Gather(C_mestre, n*n, MPI_INT,void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);

  matrix_print(C_mestre);

  matrix_destroy(B);
  matrix_destroy(A_escravo);
  matrix_destroy(A_mestre);
  matrix_destroy(C_escravo);
  matrix_destroy(C_mestre);

  MPI_Finalize();
  return 0;
}
