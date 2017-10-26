#include <mpi.h>
// #include <iostream>
#include <stdio.h>
#include <stdlib.h>

// using namespace std;
int main(int argc, char *argv[]) {
  int rank,size,tag = 0;
  int tam,valor;
  MPI_Status status;

  tam = atoi(argv[1]);


  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);


  if (rank == 0) {
    MPI_Send(&tam, 1, MPI_INT, rank+1, tag, MPI_COMM_WORLD);
    printf("%d - enviando o tamanho %d para %d\n",rank, tam, rank + 1);

    int *vetor = NULL;
    vetor = (int *) malloc(sizeof(int)*tam);

    for (int i = 0; i < tam; i++) {
      vetor[i] = i;
    }

    MPI_Send(vetor, tam, MPI_INT, rank+1, tag, MPI_COMM_WORLD);
    printf("%d - enviando o tamanho %d para %d\n",rank, tam, rank + 1);

    MPI_Recv(&tam, 1,MPI_INT, size-1, tag, MPI_COMM_WORLD, &status);
    printf("%d - recebendo o tamanho %d de %d\n",rank, tam, size-1);
    MPI_Recv(vetor, tam,MPI_INT,rank-1, tag, MPI_COMM_WORLD, &status);
    for (int i = 0; i < tam; i++) {
      printf("%d\t",vetor[i]);
    }
    printf("\n");

  } else {
    if (rank == size-1){
      MPI_Recv(&tam, 1,MPI_INT,rank-1, tag, MPI_COMM_WORLD, &status);
      printf("%d - recebendo o tamanho %d de %d\n",rank,tam, rank-1);

      int *vetor = NULL;
      vetor = (int *) malloc(sizeof(int)*tam);

      MPI_Recv(vetor, tam,MPI_INT,rank-1, tag, MPI_COMM_WORLD, &status);

      for (int i = 0; i < tam; i++) {
        printf("%d\t",vetor[i]);
      }
      printf("\n");

      MPI_Send(&tam, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
      printf("%d - enviando o tamanho %d para %d\n",rank, tam, 0);

      MPI_Send(vetor, tam, MPI_INT, 0, tag, MPI_COMM_WORLD);
      printf("%d - enviando o tamanho %d para %d\n",rank, tam, 0);


    }else{
      MPI_Recv(&tam, 1,MPI_INT,rank-1, tag, MPI_COMM_WORLD, &status);
      printf("%d - recebendo o tamanho %d de %d\n",rank,tam, rank-1);

      int *vetor = NULL;
      vetor = (int *) malloc(sizeof(int)*tam);

      MPI_Recv(vetor, tam,MPI_INT,rank-1, tag, MPI_COMM_WORLD, &status);

      for (int i = 0; i < tam; i++) {
        printf("%d\t",vetor[i]);
      }
      printf("\n");

      MPI_Send(&tam, 1, MPI_INT, rank+1, tag, MPI_COMM_WORLD);
      printf("%d - enviando o tamanho %d para %d\n",rank, tam, rank + 1);

      MPI_Send(vetor, tam, MPI_INT, rank+1, tag, MPI_COMM_WORLD);
      printf("%d - enviando o tamanho %d para %d\n",rank, tam, rank + 1);
    }
  }

  MPI_Finalize();
  return 0;
}
