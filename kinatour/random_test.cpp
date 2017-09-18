#include<iostream>
#include<random>
using namespace std;
int main(int argc, char const *argv[]) {
  int v[100] = {0};
  random_device rd;
  mt19937_64 gen(rd());
  uniform_real_distribution<> uni(0,99.9);
  for (int i = 0; i < 100000; i++) {
    v[int(uni(gen))]++;
  }
  for (int i = 0; i < 100; i++) {
    cout << i<<"->"<<v[i]<< '\n';
  }
  return 0;
}
