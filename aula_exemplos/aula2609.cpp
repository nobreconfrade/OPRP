#include<iostream>
#include<omp.h>
using namespace std;

int main(int argc, char const *argv[]) {
  int thread_id;
  int var1 = 10;
  #pragma omp parallel private(thread_id) firstprivate(var1)
  {
    thread_id = omp_get_thread_num(); // numero da thread
    cout << "Ola mundo! T:"<< thread_id << '\n';
    cout << "Olha esse rojão var1:"<< var1 << '\n';
    #pragma omp master
    {
      int nthreads = omp_get_num_threads(); //numero de threads no total
      cout << "Numero de threads rodando:"<< nthreads << '\n';
    }
  }
  return 0;
}
