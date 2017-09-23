#include <iostream>
#include <random>
#include <stdlib.h>

using std::cout; 
using std::cin; 
using std::random_device;
using std::mt19937_64;
using std::uniform_real_distribution;

#define SIZEF 500

struct Position{
  int x = 0;
  int y = 0;
};

int iPasso[8] = { -2, -1,  1,  2,  2,  1, -1, -2 };
int jPasso[8] = {  1,  2,  2,  1, -1, -2, -2, -1 };


double Random(){
  //https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
  random_device rd;
  mt19937_64 gen(rd());
  //http://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
  uniform_real_distribution<> uni(0,99.9);
  return uni(gen);
}

void InitMatrix(int matrix[SIZEF][SIZEF], int n){
  for (int i = 0; i < n; ++i){
    for (int j = 0; j < n; ++j){
      matrix[i][j] = 0; 
    }
  }
  matrix[0][0] = 1;
}

void SaveMove(int i, Position *p){
  p->x+=iPasso[i];
  p->y+=jPasso[i];
}

bool Valid(Position *p, int i, int board[SIZEF][SIZEF], int size){
  int x = (p->x) + iPasso[i];
  int y = (p->y) + jPasso[i]; 

  if( x >= 0 && x < size && y >= 0 && y < size && board[x][y] == 0 )
    return true;
  return false;
}

int walk(Position *p,int board[SIZEF][SIZEF],int size){
  double random = Random();
  int pass = 0;
  while(1){
    random = fmod(random,100);
    
    if (0 <= random && random < 12.5){
      if (Valid(p, 0, board, size)){
        SaveMove(0, p);
        return 0;
      }
      pass++;
    } 

    else if (12.5 <= random && random < 25){
      if (Valid(p, 1, board, size)){
        SaveMove(1, p);
        return 0;
      }
      pass++;
    }

    else if (25 <= random && random < 37.5){
      if (Valid(p, 2, board, size)){
        SaveMove(2, p);
        return 0;
      }
      pass++;
    }

    else if (37.5 <= random && random < 50){
      if (Valid(p, 3, board, size)) {
        SaveMove(3, p);
        return 0;
      }
      pass++;
    }

    else if (50 <= random && random < 62.5){
      if (Valid(p, 4, board, size)) {
        SaveMove(4, p);
        return 0;
      }
      pass++;
    }

    else if (62.5 <= random && random < 75){
      if (Valid(p, 5, board, size)) {
        SaveMove(5, p);
        return 0;
      }
      pass++;
    }

    else if (75 <= random && random < 87.5){
      if (Valid(p, 6, board, size)) {
        SaveMove(6, p);
        return 0;
      }
      pass++;
    }

    else{ 
      if (Valid(p, 7, board, size)) {
        SaveMove(7, p);
        return 0;
      }
      pass++;
    }

    random+=12.5;
    if (pass == 8)
      return 1;
    
  }
}

void PrintBoard(int board[SIZEF][SIZEF], int size){
  for (int i = 0; i < size; ++i){
    for (int j = 0; j < size; ++j)
      cout << board[i][j] << "\t";
    cout << "\n\n";
  }
}

int main(int argc, char const *argv[]) {
  int size;
  
  cin >> size;
 
  int board [SIZEF][SIZEF];
  
  Position *p;
  p = (Position *) malloc(sizeof(Position));

  int flag = 0, iter = 0;
  while (1) {
    InitMatrix(board, size);

    int count = 2;
    for (int k = 0; k < size*size; k++){
      int end = walk(p,board,size);
      if (end == 1) {
        flag = 0;
        for (int i = 0; i < size; i++) {
          for (int j = 0; j < size; j++) {
            if (board[i][j] == 0)
              flag++;
          }
        }

        if (flag == 0) {
          cout << "random is good! Iteration:"<< iter << '\n';
          PrintBoard(board, size);
          return 0;
        }
        // cout << "random is mean" << '\n';
        break;
      }
      
      board[p->x][p->y] = count;
      count++;
    }

    if(flag != 0){
      p->x=0;
      p->y=0;
    }

    iter++;
  }
  return 0;
}
