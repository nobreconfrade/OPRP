#include <mpi.h>
// #include <iostream>
#include <stdio.h>

// using namespace std;
int main(int argc, char *argv[]) {
  int rank,size, tag = 0;
  int token;
  MPI_Status status;

  MPI_Init(&argc, &argv);


  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  token = 589456451 ;
  if (rank == 0) {
    MPI_Send(&token, 1, MPI_INT, rank+1, tag, MPI_COMM_WORLD);
    printf("Eu sou %d estou enviando %d para %d\n",rank, token, rank+ 1);
  	MPI_Recv(&token, 1,MPI_INT, size-1, tag, MPI_COMM_WORLD, &status);
    printf("Eu sou %d estou recebendo %d de %d\n",rank, token, size-1);
  } else {
    if (rank == size-1){
      MPI_Recv(&token, 1,MPI_INT,rank-1, tag, MPI_COMM_WORLD, &status);
      printf("Eu sou %d estou enviando %d para %d\n",rank,token, rank+1);
      MPI_Send(&token, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
      printf("Eu sou %d estou recebendo %d de %d\n",rank, token, rank-1);
    }else{
      MPI_Recv(&token, 1,MPI_INT,rank-1, tag, MPI_COMM_WORLD, &status);
      printf("Eu sou %d estou enviando %d para %d\n",rank,token, rank+1);
      MPI_Send(&token, 1, MPI_INT, rank+1, tag, MPI_COMM_WORLD);
      printf("Eu sou %d estou recebendo %d de %d\n",rank, token, rank-1);
    }
  }

  MPI_Finalize();
  return 0;
}
