#include <bits/stdc++.h>

using namespace std;

class Entry {
public:
	unsigned value;
	int x;
	int y;
	Entry(){
		value = numeric_limits<int>::max();
		x = -1;
		y = -1;
	}
	Entry(int r, int _x, int _y){
		value = r;
		x = _x;
		y = _y;
	}
	
};

struct comparator{
	bool operator()(Entry &a, Entry &b) const{
		return a.value> b.value;
	}
};

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

vector<pair<int, int>> subSum(int *matrix[], int *sumMatrix[], int x1, int y1, int rows, int colums, int &sum){
	sumMatrix[x1][y1] = -1;
	vector<pair<int, int>> ret;
	vector<pair<int, int>> queue;

	int xx, yy, x, y;
	int dir[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
	queue.push_back(make_pair(x1, y1));
	while(!queue.empty()){
		pair<int, int> u = queue.back();
		x = u.first;
		y = u.second;

		ret.push_back(make_pair(x, y));
		queue.pop_back();
		sum++;
		for(int i = 0; i < 4; i++){
			xx = x + dir[i][0];
			yy = y + dir[i][1];
			
			if((xx >= 0) && (xx < rows) && (yy >= 0) && (yy < colums)){
				if((sumMatrix[xx][yy] == 0) && (matrix[x][y] == matrix[xx][yy])){
					sumMatrix[xx][yy] = -1;
					queue.push_back(make_pair(xx, yy));
				}
			}
		}
	}
	return ret;
}

void getSubSum(int *matrix[], int *sumMatrix[], int rows, int colums){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < colums; j++){
			if (sumMatrix[i][j] == 0){
				int sum = 0;
				vector<pair<int, int>> v = subSum(matrix, sumMatrix, i, j, rows, colums, sum);
				while(!v.empty()){
					sumMatrix[v.back().first][v.back().second] = sum;
					v.pop_back();
				}
			}
		}
	}

}
bool reconfigure(int x, int y){
	return abs(x - y) > min(x, y);
}

int reconfigure2(int x, int y){
	if(reconfigure(x, y)){
		return 1;
	} else {
		return 0;
	}
}


vector<vector<unsigned>> bfs_reconfiguration(int *matrix[], int rows, int colums, int x1, int y1, int x2, int y2){
	vector<Entry> queue;

	unsigned best_r = numeric_limits<unsigned>::max();

	vector<vector<unsigned>> reconfiguration(rows, vector<unsigned>(colums,numeric_limits<unsigned>::max()));
	vector<vector<bool>> visited(rows, vector<bool>(colums, false));

	visited[x1][y1] = true;
	reconfiguration[x1][y1] = 0;

	int xx, yy;
	int dir[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

	queue.push_back(Entry(reconfiguration[x1][y1], x1, y1));
	while(!queue.empty()){
		Entry e = queue.front();
		pop_heap(queue.begin(), queue.end(), comparator()); queue.pop_back();

		if(best_r < e.value){
			continue;
		}

		for(int i = 0; i < 4; i++){
			xx = e.x + dir[i][0];
			yy = e.y + dir[i][1];
			if((xx >= 0) && (xx < rows) && (yy >= 0) && (yy < colums)){
				if(!visited[xx][yy]){
					visited[xx][yy] = true;
					if(reconfigure(matrix[xx][yy], matrix[e.x][e.y])){
						reconfiguration[xx][yy] = e.value + 1;
					} else {
						reconfiguration[xx][yy] = e.value;
					}
					queue.push_back(Entry(reconfiguration[xx][yy], xx, yy));
					push_heap(queue.begin(), queue.end(), comparator());
				} else {
					int r = reconfigure2(matrix[xx][yy], matrix[e.x][e.y]);
					if(reconfiguration[xx][yy] > e.value + r){
						reconfiguration[xx][yy] = e.value + r;
						queue.push_back(Entry(reconfiguration[xx][yy], xx, yy));
						push_heap(queue.begin(), queue.end(), comparator());
					}
				}
				if((xx == x2) && (yy == y2)){
					best_r = reconfiguration[xx][yy];
				}
			}
		}
	}
	return reconfiguration;
}

int bfs_distance(int *matrix[], vector<vector<unsigned>> reconfiguration, int rows, int colums, int x1, int y1, int x2, int y2){
	vector<vector<unsigned>> distance(rows, vector<unsigned>(colums, numeric_limits<unsigned>::max()));
	vector<vector<bool>> visited(rows, vector<bool>(colums, false));

	distance[x1][y1] = 0;
	visited[x1][y1] = true;
	unsigned best_r = reconfiguration[x2][y2];
	int xx, yy;
	int dir[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
	vector<Entry> queue;
	queue.push_back(Entry(distance[x1][y1], x1, y1));
	while(!queue.empty()){
		Entry e = queue.front();
		
		pop_heap(queue.begin(), queue.end(), comparator()); queue.pop_back();
	       	if(best_r < reconfiguration[e.x][e.y]){
			continue;
		}
		for(int i = 0; i < 4; i++){
			xx = e.x + dir[i][0];
			yy = e.y + dir[i][1];
			if((xx >= 0) && (xx < rows) && (yy >= 0) && (yy < colums) && (reconfiguration[xx][yy] == reconfiguration[e.x][e.y] + reconfigure2(matrix[xx][yy], matrix[e.x][e.y]))){
				if(!visited[xx][yy]){
					visited[xx][yy] = true;
					distance[xx][yy] = distance[e.x][e.y] + 1;
					if((xx==x2) && (yy==y2)){
						return distance[xx][yy];
					}
					queue.push_back(Entry(distance[xx][yy], xx, yy));
					push_heap(queue.begin(), queue.end(), comparator());
				} else if(distance[xx][yy] > distance[e.x][e.y] + 1){
					distance[xx][yy] = distance[e.x][e.y] + 1;
					queue.push_back(Entry(distance[xx][yy], xx, yy));
					push_heap(queue.begin(), queue.end(), comparator());
				}
			}
		}
	}
	return -1;
}

int main(){
	int rows = fastscan();
	int colums = fastscan();
	int x1 = fastscan() - 1;
	int y1 = fastscan() - 1;
	int x2 = fastscan() - 1;
	int y2 = fastscan() - 1;
	int *matrix[rows];
	int *subSum[rows];
	for(int i = 0; i < rows; i++){
		matrix[i] = new int[colums];
		subSum[i] = new int[colums]();
		for(int j = 0; j < colums; j++){
			matrix[i][j] = fastscan();
		}
	}
	getSubSum(matrix, subSum, rows, colums);
//	printMatrix(subSum, rows, colums);
//	cout << "after getSubSum"<< endl;
	vector<vector<unsigned>> r = bfs_reconfiguration(subSum, rows, colums, x1, y1, x2, y2);
	/*for(int i = 0; i < rows; i++){
		for(int j = 0; j < colums; j++){
			cout << r[i][j];
		}
		cout << endl;
	}*/
	int d = bfs_distance(subSum, r, rows, colums, x1, y1, x2, y2);
	printf("%u %i\n", r[x2][y2], d);
}

