#include <iostream>
#include <random>
#include <stdlib.h>

#define NOT_VISITED 0
#define VISITED 1
#define ERROR -1
#define SIZEF 500

using namespace std;

int xPasso[8] = { -2, 1, -1, 2, -2, -1,  1,  2 };
int yPasso[8] = {  1, 2,  2, 1, -1, -2, -2, -1 };

typedef struct Position{
	int x = 0;
	int y = 0;
} Position;

void InitMatrix(int matrix[SIZEF][SIZEF], int n);

double Random();

int walk(Position *p, int board[SIZEF][SIZEF], int size);

int main(int argc, char const *argv[]) {
	int size;

	cin >> size;
	
	int board[SIZEF][SIZEF];
	InitMatrix(board, size);
	
	Position *p;
	p = (Position *) malloc(sizeof(Position));
	p->x = 0; p->y = 0;

	int end,flag;

	int it = 0;
	while (1) {

		it++;
		walk(p, board, size);
	// 	int count = 2; //?????????

		// for (int i = 0; i < size; i++){
	// 		for (int j = 0; j < size; j++){
	// 			end = walk(p, board, size);

	// 			if (end == 1) {
	// 				flag = 0;
					
	// 				for (i = 0; i < count; i++) {
	// 					for (j = 0; j < count; j++) {
	// 						if (board[i][j] == 0) {
	// 							flag++;
	// 						}
	// 					}
	// 				}
					
	// 				if (flag == 0) {
	// 					cout << "random is good!" << '\n';
	// 					return 0;
	// 				}

	// 				cout << "random is mean" << '\n';
	// 				break;
	// 			}

	// 			board[p->x][p->y] = count;
	// 			count++;
	// 		}
			
	// 		if(flag != 0){
	// 			free(p);
	// 			break;
	// 		}

	// 	}
	// }
	return 0;
}

void InitMatrix(int matrix[SIZEF][SIZEF], int n){
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			matrix[i][j] = NOT_VISITED;	
		}
	}
	matrix[0][0] = VISITED;
}

double Random(){
	//https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
	random_device rd;
	mt19937_64 gen(rd());
	//http://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
	uniform_real_distribution<> uni(0,99.9);
	return uni(gen);
}

bool Valid(Position p, int i, int board[SIZEF][SIZEF]){
	int x = (p->x) + xPasso[i];
	int y = (p->y) + yPasso[i]; 

	if( x < 0 || x >= size || y < 0 || y >= size || board[x][y] != 0 ){
		return false;
	return true;
}

void SaveMove(int i, Position *p){
	p->x-=xPasso[i];
	p->y-=yPasso[i];
}

int Move(int random, Position *p, int board[SIZEF][SIZEF]){
	if (0 <= random && random < 12.5){
		if (!Valid(p, 1, move))
			return ERROR;
		return 1;
	}

	if (random < 25){
		if (!Valid(p, 2, move))
			return ERROR;
		return 2;
	}

	if (random < 37.5){
		if (!Valid(p, 3, move))
			return ERROR;
		return 3;
	}

	if (random < 50){
		if (!Valid(p, 4, move))
			return ERROR;
		return 4;
	}

	if (random < 62.5){
		if (!Valid(p, 5, move))
			return ERROR;
		return 5;
	}

	if (random < 75){
		if (!Valid(p, 6, move))
			return ERROR;
		return 6;
	}

	if (random < 87.5){
		if (!Valid(p, 7, move))
			return ERROR;
		return 7;
	}

	if (!Valid(p,8, move))
		return ERROR;
	return 8;
	
}

int walk(Position *p, int board[SIZEF][SIZEF], int size){
	int pass = 0;
	double random = Random();
	while(1){
		switch (Move(random, p)){
			case 1:
				SaveMove(1);
				pass++;
			case 2:
				SaveMove(2);
				pass++;
			case 3:
				SaveMove(3);
				pass++;
			case 4:
				SaveMove(4);
				pass++;
			case 5:
				SaveMove(5);
				pass++;
			case 6:
				SaveMove(6);
				pass++;			
			case 7:
				SaveMove(7);
				pass++;			
			case 8:
				SaveMove(8);
				pass++;			
			case ERROR:
				printf("Movimento invalido\n");
		}
		
		random+=12.5;
		random = fmod(random,100);
		if (pass == 8) {
			return 1;
		}
		}
}