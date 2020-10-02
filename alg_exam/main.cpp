#include <bits/stdc++.h>

using namespace std;
void printMatrix(int *matrix[], int rows, int colums){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < colums; j++){
			printf("%i ", matrix[i][j]);
		}
		printf("\n");
	}
}
int fastscan()
{
	char c;
    	int number = 0;
    	c = getchar();
	while(c>=58 || c<=47) c=getchar();
    	// Keep on extracting characters if they are integers
    	// i.e ASCII Value lies from '0'(48) to '9' (57)
    	for (; (c>47 && c<58); c=getchar())
        	number = number *10 + c - 48;
	return number;
}

int calcMove(int i1, int i2, int ee, int dmov, int denv){
	int e = ee;
	if (i1 < i2){
		e += dmov;
	} else if (i1 > i2){
		if (e < dmov){
			e = 0;
		} else {
			e -= dmov;
		}
	}
	if (e >= denv + i2){
		e -= denv;
	} else if ((denv + i2 > e ) && (e > i2)){
		e = i2;
	}
	return e;
}

class Entry {
public:
	int moves;
	int iont;
	int x;
	int y;
	Entry(int m, int i,int _x, int _y){
		moves = m;
		iont = i;
		x = _x;
		y = _y;
	}
	
};

struct comparator{
	bool operator()(Entry &a, Entry &b) const{
		return a.moves > b.moves;
	}
};

int runDron(int *matrix[], int r, int c, int e, int dmov, int denv){
	vector<vector<int>> moves(r, vector<int>(c,numeric_limits<int>::max()));
	vector<vector<int>> iont(r, vector<int>(c, 0));
	vector<Entry> queue;
	int ee;
	iont[0][0] = e;
	moves[0][0] = 0;
	queue.push_back(Entry(0, e, 0, 0));
	while (!queue.empty()){
		Entry u = queue.front();
		pop_heap(queue.begin(), queue.end(), comparator()); queue.pop_back();
		
//		printf("[%i, %i, %i, %i]\n", u.moves, 0-u.iont, u.x, u.y);
		if (u.y - 1 >= 0){
	//		printf("1");
			ee = calcMove(matrix[u.y][u.x], matrix[u.y-1][u.x], u.iont, dmov, denv);
			if (ee > 0){
				if (moves[u.y-1][u.x] > u.moves+1){
					moves[u.y-1][u.x] = u.moves + 1;
					queue.push_back(Entry(u.moves+1, ee, u.x, u.y-1));
					push_heap(queue.begin(), queue.end(), comparator());
				} else if (iont[u.y-1][u.x] < ee){
					iont[u.y-1][u.x] = ee;
					queue.push_back(Entry(u.moves+1, ee, u.x, u.y-1));
					push_heap(queue.begin(), queue.end(), comparator());
				}
			}
		}
		if (u.y +1 < r){
	//		printf("2");
			if ((u.y+1 == r-1) && (u.x == c-1)){
				return u.moves + 1;
			}
			ee = calcMove(matrix[u.y][u.x], matrix[u.y+1][u.x], u.iont, dmov, denv);
			if (ee > 0){
				if (moves[u.y+1][u.x] > u.moves+1){
					moves[u.y+1][u.x] = u.moves + 1;
					queue.push_back(Entry(u.moves+1, ee, u.x, u.y+1));
					push_heap(queue.begin(), queue.end(), comparator());
				} else if (iont[u.y+1][u.x] < ee){
					iont[u.y+1][u.x] = ee;
					queue.push_back(Entry(u.moves+1, ee, u.x, u.y+1));
					push_heap(queue.begin(), queue.end(), comparator());
				}
			}
		}
		if (u.x - 1 >= 0){
			//printf("3");
			ee = calcMove(matrix[u.y][u.x], matrix[u.y][u.x-1], u.iont, dmov, denv);
			if (ee > 0){
				if (moves[u.y][u.x-1] > u.moves +1){
					moves[u.y][u.x-1] = u.moves+1;
					queue.push_back(Entry(u.moves+1, ee, u.x-1, u.y));
					push_heap(queue.begin(), queue.end(), comparator());
				} else if (iont[u.y][u.x-1] < ee){
					iont[u.y][u.x-1] = ee;
					queue.push_back(Entry(u.moves+1, ee, u.x-1, u.y));
					push_heap(queue.begin(), queue.end(), comparator());
				}
			}
		}
		if (u.x + 1 < c){
			//printf("4");
			if ((u.y == r-1) && (u.x+1 == c-1)){
				return u.moves+1;
			}
			ee = calcMove(matrix[u.y][u.x], matrix[u.y][u.x+1], u.iont, dmov, denv);
			if (ee > 0){
				if (moves[u.y][u.x+1] > u.moves +1){
					moves[u.y][u.x+1] = u.moves+1;
					queue.push_back(Entry(u.moves+1, ee, u.x+1, u.y));
					push_heap(queue.begin(), queue.end(), comparator());
				} else if (iont[u.y][u.x+1] < ee){
					iont[u.y][u.x+1] = ee;
					queue.push_back(Entry(u.moves+1, ee, u.x+1, u.y));
					push_heap(queue.begin(), queue.end(), comparator());
				}
			}
		}
	}
}


int main(){
	int m, n, e, dmov, denv;
	m = fastscan();
	n = fastscan();
	e = fastscan();
	dmov = fastscan();
	denv = fastscan();
	int *matrix[m];
	for(int i = 0; i < m; i++){
		matrix[i] = new int[n];
		for(int j = 0; j < n; j++){
			matrix[i][j] = fastscan();
		}
	}
	printf("%i\n", runDron(matrix, m, n, e, dmov, denv));
}
	
