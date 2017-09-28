#include<iostream>
#include <omp.h>
using namespace std;


int main(int argc, char const *argv[]) {
  int i, n=100;
  float a[100], b[100], sum = 0;
  #pragma omp parallel for
  for (i = 0; i < n; i++) {
    a[i]=b[i]=i*1.0;
  }
  // #pragma omp parallel for
  for (i = 0; i < n; i++) {
    sum = sum + (a[i] * b[i]);
  }
  cout << "resultado:\t"<< sum << '\n';
  return 0;
}
