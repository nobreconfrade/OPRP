#include <iostream>

__global__ void matrixMulKernel (float* M, float* N, float* P, int Width){
  int Row = blockIdx.y*blockDim.y+threadIdx.y;
  int Col = blockIdx.x*blockDim.x+threadIdx.x;
  if ((Row < Width) && (Col < Width)) {
    float Pvalue = 0;
    for (int k = 0; k < Width; ++k) {
      Pvalue += M[Ŕow*Width+k]*N[k*Width+Col];
    }
    P[Row*Width+Col] = Pvalue;
  }
}

void dados(float *M, int size)
{
	int i, j;
	srand(time(NULL));
	for (int i = 0; i < size * size; ++i) {
		M[i] = rand();
	}
}

int main(int argc, char const *argv[]) {
  int size;
  size = atoi(argv[1]);

  float MCPU[size][size], NCPU[size][size], PCPU[size][size];
  dados(MCPU,size);
  dados(NCPU,size);

  float *M, *N, *P;
  cudaMalloc((void**)&M, size * size * sizeof(float));
  cudaMalloc((void**)&N, size * size * sizeof(float));
  cudaMalloc((void**)&P, size * size * sizeof(float));

  cudaMemcpy(M, MCPU, size * size * sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(N, NCPU, size * size * sizeof(float), cudaMemcpyHostToDevice);

  dim3 Grade(1,1);
  dim3 Bloco(size,size);

  matrixMulKernel<<Grade,Bloco>>>(M,N,P,size);


  cudaMemcpy(PCPU, P, size * size * sizeof(float), cudaMemcpyDeviceToHost);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      std::cout << PCPU[i][j]<< '\t';
    }
    std::cout << "" << '\n';
  }

  return 0;
}
