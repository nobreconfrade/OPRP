#include <iostream>
#include <random>
#define SIZEF 500

struct Position{
  int x;
  int y;
};

using namespace std;

void walk(Position *p,int &board,int size){
  //https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
  random_device rd;
  mt19937 gen(rd());
  //http://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
  uniform_int_distribution<int> uni(0,100);
  auto random = uni(gen);
  cout << random+"\n";
}

int main(int argc, char const *argv[]) {
  int board [SIZEF][SIZEF];
  int size,count;
  Position *p;
  p = (Position *) malloc(sizeof(Position));
  cin >> size;
  p->x = 0;
  p->y = 0;
  board[0][0] = 1;
  count = 2;
  for (int i = 0; i < size; i++) {
    for (int j = 0;j < size; j++){
      walk(p,**board,size);
    }
  }
  return 0;
}
