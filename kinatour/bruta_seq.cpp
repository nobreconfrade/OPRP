#include <iostream>
#include <random>
#define SIZEF 500

struct Position{
  int x;
  int y;
};

using namespace std;

int walk(Position *p,int &board,int size){
  //https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
  random_device rd;
  mt19937_64 gen(rd());
  //http://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
  uniform_real_distribution<> uni(0,99);
  cout << uni(gen)<<"\n";
  float random = uni(gen);

  while(1){
    if (0 <= random%100 < 12.5) { // move 1
      if((p->x-2>=0)&&(p->y+1<size)){
        if (board[p->x-2][p->y+1] == 0) {
          p->x-=2;
          p->y+=1;
        }
      }
    }else if (12.5 <= random%100 < 25){ // move 2
      if((p->x-1>=0)&&(p->y+2<size)){
        if (board[p->x-1][p->y+2] == 0) {
          p->x-=1;
          p->y+=2;
        }
      }
    }else if (25 <= random%100 < 37.5){ // move 3
      if((p->x+1<size)&&(p->y+2<size)){
        if (board[p->x+1][p->y+2] == 0) {
          p->x+=1;
          p->y+=2;
        }
      }
    }else if (37.5 <= random%100 < 50){ // move 4
      if((p->x+2<size)&&(p->y+1<size)){
        if (board[p->x+2][p->y+1] == 0) {
          p->x+=2;
          p->y+=1;
        }
      }
    }else if (50 <= random%100 < 62.5){ // move 5
      if((p->x+2<size)&&(p->y-1>=0)){
        if (board[p->x+2][p->y+1] == 0) {
          p->x+=2;
          p->y-=1;
        }
      }
    }else if (62.5 <= random%100 < 75){ // move 6
      if((p->x+1<size)&&(p->y-2>=0)){
        if (board[p->x+1][p->y+2] == 0) {
          p->x+=1;
          p->y-=2;
        }
      }
    }else if (75 <= random%100 < 87.5){ // move 7
      if((p->x-1>=0)&&(p->y-2>=0)){
        if (board[p->x-1][p->y-2] == 0) {
          p->x-=1;
          p->y-=2;
        }
      }
    }else if (87.5 <= random%100 < 100){ // move 8
      if((p->x-2>=0)&&(p->y-1>=0)){
        if (board[p->x-2][p->y-1] == 0) {
          p->x-=2;
          p->y-=1;
        }
      }
    }
    
  }

}

int main(int argc, char const *argv[]) {
  int board [SIZEF][SIZEF] = {0};
  int size,count,end;
  int i, j;
  Position *p;
  p = (Position *) malloc(sizeof(Position));
  cin >> size;
  while (1) {
    p->x = 0;
    p->y = 0;
    board[0][0] = 1;
    count = 2;
    for (i = 0; i < size; i++) {
      for (j = 0;j < size; j++){
        end = walk(p,**board,size);
        if (end == 1) {

        }
      }
    }
  }
  return 0;
}
