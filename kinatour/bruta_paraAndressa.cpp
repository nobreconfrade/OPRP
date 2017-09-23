#include <iostream>
#include <random>
#include <thread>

using std::cout; 
using std::cin; 
using std::random_device;
using std::mt19937_64;
using std::uniform_real_distribution;
using std::vector; 
using std::thread;

#define SIZEF 500

typedef struct Info{
	int board[SIZEF][SIZEF];
	int x;
	int y;
} Info;

int size;

int iPasso[8] = { -2, -1,  1,  2,  2,  1, -1, -2 };
int jPasso[8] = {  1,  2,  2,  1, -1, -2, -2, -1 };

double Random(int n){
	//https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
	random_device rd;
	mt19937_64 gen(rd());
	//http://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
	uniform_real_distribution<> uni(0,n);
	return uni(gen);
}

void InitMatrix(int matrix[SIZEF][SIZEF], int x, int y){
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			matrix[i][j] = 0; 
		}
	}
	matrix[x][y] = 1;
}

void PrintBoard(int board[SIZEF][SIZEF]){
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j)
			cout << board[i][j] << "\t";
		cout << "\n\n";
	}
}

void populate(vector<Info> &p, int threads){
	int count = 0;

	while (count != threads){
		int flag = 1;
		Info tmp;
		tmp.x = Random(size-1);
		tmp.y = Random(size-1);
		InitMatrix(tmp.board, tmp.x, tmp.y);

		for (unsigned int i = 0; i < p.size(); i++) {
			if (p[i].x == tmp.x && p[i].y == tmp.y) {
				flag = 0;
				break;
			}
		}

		if (flag) {
			p.push_back(tmp);
			count ++;
		}
	}
}	

bool Valid(Info *p, int i){
  int x = (p->x) + iPasso[i];
  int y = (p->y) + jPasso[i]; 

  if( x >= 0 && x < size && y >= 0 && y < size && p->board[x][y] == 0 )
    return true;
  return false;
}

void SaveMove(Info *p, int i){
  p->x+=iPasso[i];
  p->y+=jPasso[i];
}


int walk(Info *p){
	double random = Random(99.9);
	int pass = 0;

	while(1){
		random = fmod(random,100);
		if (0 <= random && random < 12.5) { // move 1
			if(Valid(p, 0)) {
				SaveMove(p, 0);
				return 0;
			}
			pass++;

		}else if (12.5 <= random && random < 25){ // move 2
			if(Valid(p, 1)) {
				SaveMove(p, 1);
				return 0;
			}
			pass++;

		}else if (25 <= random && random< 37.5){ // move 3
			if(Valid(p, 2)){
				SaveMove(p, 2);
					return 0;
			}
			pass++;

		}else if (37.5 <= random && random < 50){ // move 4
			if(Valid(p, 3)){
				SaveMove(p, 3);
				return 0;
			}
			pass++;

		}else if (50 <= random && random < 62.5){ // move 5
			if(Valid(p, 4)) {
				SaveMove(p, 4);
				return 0;
			}
			pass++;

		}else if (62.5 <= random && random < 75){ // move 6
			if(Valid(p, 5)) {
				SaveMove(p, 5);
				return 0;
			}
			pass++;

		}else if (75 <= random && random < 87.5){ // move 7
			if(Valid(p, 6)) {
				SaveMove(p, 6);
				return 0;
			}
			pass++;

		}else{
			if(Valid(p, 7)) {
				SaveMove(p, 7);
				return 0;
			}
			pass++;
		}

		random+=12.5;
		if (pass == 8) 
			return 1;
	}
}

int Tour(Info *p){
	int flag = 0, iter = 0;
	
	while (1) {
		InitMatrix(p->board, p->x, p->y);
		
		int count = 2;
		for (int k = 0; k < size*size; k++){
			int end = walk(p);
			
			if (end == 1) {
				flag = 0;
				
				for (int i = 0; i < size; i++) {
					for (int j = 0; j < size; j++) {
						if (p->board[i][j] == 0) 
							flag++;
					}
				}

				if (flag == 0) {
					cout << "random is good! Iteration:"<< iter << '\n';
					PrintBoard(p->board);
					return 0;
				}
				break;
			}
			
			p->board[p->x][p->y] = count;
			count++;
		}

		if(flag != 0){
			p->x=0;
			p->y=0;
		}
		iter++;
	}
}

int main(int argc, char const *argv[]){
	
	cin >> size;

	int nthreads;
	cin >> nthreads;

	vector<Info> p;
	populate(p,nthreads);

	// for (unsigned int i = 0; i < p->size(); i++) {
	//     cout << i << ": x=" << p[i].x << ", y=" << p[i].y << '\n';
 	//    	PrintBoard(p[i].board);
	// }

	thread threads[nthreads];
    for (int i = 0; i < nthreads; i++) 
        threads[i] = thread(Tour, p[i]);

    for (auto& th : threads) {
        th.join();
    }



	return 0;
}