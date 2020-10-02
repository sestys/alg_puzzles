#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//global variables
int r;
int c;
int *matrix;
int numRobots;

void printMatrix(int* matrix, int c, int r){
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			printf("%i ", matrix[c *i +j]);
		}
		printf("\n");
	}
	printf("\n");
}

void returnMove(int *robotMoves, int *move, int *coor){
	if(move[0] == 0){
		for(int i = coor[1]; i < move[1]; i++){
			robotMoves[coor[0]*c + i] = 0;
		}
	}else if(move[0] == 1){
		for(int i = coor[1]; i > move[1]; i--){
			robotMoves[coor[0]*c + i] = 0;
		}
	}else if(move[0] == 2){
		for(int i = coor[0]; i < move[1]; i++){
			robotMoves[i*c + coor[1]] = 0;
		}
	}else{
		for(int i = coor[0]; i > move[1]; i--){
			robotMoves[i*c + coor[1]] = 0;
		}
	}
}


int moveRobot(int *move, int *robotMoves, int* coor, int subsum){
	int x1 = coor[0];
	int y1 = coor[1];
	int x2 = coor[2];
	int y2 = coor[3];
	int i;
	if(x1 == x2){ //going horizontaly
		if(y1 < y2){ //left to right
			move[0] = 0;
			for(i = y1; i <= y2; i++){
				if(robotMoves[x1*c + i] != -1){
					subsum += matrix[x1*c + i];
					robotMoves[x1*c + i] = -1;
					if(i == y2){
						move[1] = i+1;
					}
				} else {
					move[1] = i;
					break;
				}
			}
		} else { //right to left
			move[0] = 1;
			for(i = y1; i >= y2; i--){
				if(robotMoves[x1*c + i] != -1){
					subsum += matrix[x1*c + i];
					robotMoves[x1*c + i] = -1;
					if(i == y2){
						move[1] = i-1;
					}
				} else {
					move[1] = i;
					break;
				}
			}
		}
	}else{ //going verticaly
		if(x1 < x2){ //top to bottom
			move[0] = 2;
			for(i = x1; i <= x2; i++){
				if(robotMoves[i*c + y1] != -1){
					subsum += matrix[i*c + y1];
					robotMoves[i*c + y1] = -1;
					if(i == x2){
						move[1] = i+1;
					}
				} else {
					move[1] = i;
					break;
				}
			}
		} else { //bottom to top
			move[0] = 3;
			for(i = x1; i >= x2; i--){
				if(robotMoves[i*c + y1] != -1){
					subsum += matrix[i*c + y1];
					robotMoves[i*c + y1] = -1;
					if(i == x2){
						move[1] = i - 1;
					}
				} else {
					move[1] = i;
					break;
				}
			}
		}
	}
	return subsum;
}

void robotRecursion(int *robotMoves, int robots[][4], int robotID[], int *maxSum, int *subSum, int level){
	if(level == 0){
		if(*subSum > *maxSum){
			*maxSum = *subSum;
		}
	} else {
		int move[2];
		int nextSum;
		for(int i = 0; i < numRobots; i++){
			int run = 0;
			for(int j = 0; j < numRobots - level; j++){
				if(robotID[j] == i){
					run = 1;
					break;
				}
			}
			if(run){
				continue;
			}
			nextSum = moveRobot(move, robotMoves, robots[i], *subSum);
			//printf("Level: %i\n", level);
			//printMatrix(robotMoves, c, r);
			robotID[numRobots - level] = i;
			robotRecursion(robotMoves, robots, robotID, maxSum, &nextSum, level - 1);
			returnMove(robotMoves, move, robots[i]);
		}
	}
}

int main(void){
	scanf("%i %i", &r, &c);
	matrix = (int*)malloc(sizeof(int) * r * c);
	int *robotMoves;
	robotMoves = (int*)malloc(sizeof(int) * r * c);
	memset(robotMoves, 0, sizeof(int) * r * c);
	for(int i = 0; i < r*c; i++){
		scanf("%i", &matrix[i]);
	}
	scanf("%i", &numRobots);
	int robots[numRobots][4];
	for(int i = 0; i < numRobots; i++){
		scanf("%i %i %i %i", &robots[i][0], &robots[i][1], &robots[i][2], &robots[i][3]);
	}
	int maxSum = 0; 
	int robotID[numRobots];
	int subSum = 0;
	robotRecursion(robotMoves, robots, robotID, &maxSum, &subSum, numRobots);
	printf("%i\n", maxSum);
	/*
	printMatrix(matrix, c, r);
	printMatrix(robotMoves, c, r);
	for(int i = 0; i < numRobots; i++){
		for(int j = 0; j < 4; j++){
			printf("%i ", robots[i][j]);
		}
		printf("\n");
	}*/
	free(matrix);
	free(robotMoves);
	return 0;
}
