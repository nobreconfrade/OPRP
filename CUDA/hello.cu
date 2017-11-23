#include <stdio.h>
__device__ const char *STR = "HELLO WORLD!";
const char STR_LENGTH = 12;

__global__ void hello()
{
  printf("%c\n",STR[threadIdx.x % STR_LENGTH]);
}

int main(void)
{
  int num_threads = STR_LENGTH;
  int num_blocks = 2;
  dim3 dimBlock(num_threads);
  dim3 dimGrid(1,1);
  hello<<<dimGrid,dimBlock>>>();
  cudaDeviceSynchronize();
  return 0;
}
