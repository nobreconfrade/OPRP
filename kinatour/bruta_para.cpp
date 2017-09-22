#include <iostream>
#include <random>
#include <stdlib.h>
#include <thread>

#define SIZEF 500

struct Position{
  int x;
  int y;
};


using namespace std;

int walk(Position *p,int board[SIZEF][SIZEF],int size){
  //https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
  random_device rd;
  mt19937_64 gen(rd());
  //http://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
  uniform_real_distribution<> uni(0,99.9);
  // cout << uni(gen)<<"\n";
  double random = uni(gen);
  int pass = 0;
  // printf("[%i],[%i]\n",p->x,p->y);
  while(1){
    random = fmod(random,100);
    // cout << board[1][2]<<" BOARD[1][2]\n";
    // cout << board[2][1]<<" BOARD[2][1]\n";
    // cout << p->x+1<<" p.x\n";
    // cout << p->y<<" p.y\n";
    // if ((random >= 25)&&(random < 37.5)) {
    //   cout << "rnd: "<<random<<"\n";
    // }
    if ((0 <= random)&&(random < 12.5)) { // move 1
      if((p->x-2>=0)&&(p->y+1<size)){
        if (board[p->x-2][p->y+1] == 0) {
          // cout << "oi!1" << '\n';
          p->x-=2;
          p->y+=1;
          return 0;
        }
      }
      pass++;
    }else if ((12.5 <= random)&&(random < 25)){ // move 2
      if((p->x-1>=0)&&(p->y+2<size)){
        if (board[p->x-1][p->y+2] == 0) {
          // cout << "oi!2" << '\n';
          p->x-=1;
          p->y+=2;
          return 0;
        }
      }
      pass++;
    }else if ((25 <= random)&&(random< 37.5)){ // move 3
      if((p->x+1<size)&&(p->y+2<size)){
        if (board[p->x+1][p->y+2] == 0) {
          // cout << "oi!3" << '\n';
          p->x+=1;
          p->y+=2;
          return 0;
        }
      }
      pass++;
    }else if ((37.5 <= random)&&(random < 50)){ // move 4
      if((p->x+2<size)&&(p->y+1<size)){
        if (board[p->x+2][p->y+1] == 0) {
          // cout << "oi!4" << '\n';
          p->x+=2;
          p->y+=1;
          return 0;
        }
      }
      pass++;
    }else if ((50 <= random)&&(random < 62.5)){ // move 5
      if((p->x+2<size)&&(p->y-1>=0)){
        if (board[p->x+2][p->y-1] == 0) {
          // cout << "oi!5" << '\n';
          p->x+=2;
          p->y-=1;
          return 0;
        }
      }
      pass++;
    }else if ((62.5 <= random)&&(random < 75)){ // move 6
      if((p->x+1<size)&&(p->y-2>=0)){
        if (board[p->x+1][p->y-2] == 0) {
          // cout << "oi!6" << '\n';
          p->x+=1;
          p->y-=2;
          return 0;
        }
      }
      pass++;
    }else if ((75 <= random)&&(random < 87.5)){ // move 7
      if((p->x-1>=0)&&(p->y-2>=0)){
        if (board[p->x-1][p->y-2] == 0) {
          // cout << "oi!7" << '\n';
          p->x-=1;
          p->y-=2;
          return 0;
        }
      }
      pass++;
    }else{ // move 8
      if((p->x-2>=0)&&(p->y-1>=0)){
        if (board[p->x-2][p->y-1] == 0) {
          // cout << "oi!8" << '\n';
          p->x-=2;
          p->y-=1;
          return 0;
        }
      }
      pass++;
    }

    random+=12.5;
    if (pass == 8) {
      return 1;
    }
  }

}

void printBoard(int board[SIZEF][SIZEF], int size){
  for (int i = 0; i < size; ++i){
    for (int j = 0; j < size; ++j)
      cout << board[i][j] << "\t";
    cout << "\n\n";
  }
}

void populate(vector<Position> &p, int threads, int size){
  random_device rd;
  mt19937_64 gen(rd());
  uniform_int_distribution<> duo(0,size-1);
  int count = 0;
  while (count != threads){
    int flag = 1;
    Position aux;
    aux.x = duo(gen);
    aux.y = duo(gen);
    // cout << "count "<<count << '\n';
    // cout << "threads "<<threads << '\n';
    for (int i = 0; i < p.size(); i++) {
      if ((p[i].x == aux.x) && (p[i].y == aux.y)) {
        // cout << "estoy aqui!" << '\n';
        flag = 0;
      }
    }
    if (flag) {
      p.push_back(aux);
      count ++;
      // cout << "p.size()"<<p.size() << '\n';
    }
  }
}

int main(int argc, char const *argv[]) {
  int size,count,end,threads;
  int flag = 0, iter = 0;
  int i;
  vector<Position> p;
  cin >> size;
  if (size > 500) {
    cout << "Mano, respeita o size < 500." << '\n';
    return 0;
  }
  if (size < 5) {
    cout << "Mano, respeita o size > 5." << '\n';
    return 0;
  }
  cin >> threads;
  if (threads > size*size) {
    cout << "Mano, respeita threads < size**2 = "<< size*size << '\n';
    return 0;
  }else if (threads < 1) {
    cout << "Pelo menos 1 thread" << '\n';
    return 0;
  }
  populate(p,threads,size);
  for (i = 0; i < p.size(); i++) {
    cout << i <<": x="<<p[i].x<<", y="<<p[i].y<< '\n';
  }
  // FIXME: LINK! For test purposes
  return 0;
  // while (1) {
  //   iter++;
  //   int board [SIZEF][SIZEF] = {0};
  //   board[0][0] = 1;
  //   count = 2;
  //   for (i = 0; i < size*size; i++){
  //       end = walk(p,board,size);
  //       if (end == 1) {
  //         flag = 0;
  //         for (int i2 = 0; i2 < size; i2++) {
  //           for (int j2 = 0; j2 < size; j2++) {
  //             if (board[i2][j2] == 0) {
  //               flag++;
  //             }
  //           }
  //         }
  //         if (flag == 0) {
  //           cout << "random is good! Iteration:"<< iter << '\n';
  //           printBoard(board, size);
  //           return 0;
  //         }
  //         // cout << "random is mean" << '\n';
  //         break;
  //       }
  //       board[p->x][p->y] = count;
  //       count++;
  //     }
  //     if(flag != 0){
  //       p->x=0;
  //       p->y=0;
  //     }
  // }
  // return 0;
}
