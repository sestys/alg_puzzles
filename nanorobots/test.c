#include <stdlib.h>
#include <stdio.h>

void printMat(int *p){
	printf("%i %i\n", p[0], p[1]);
}

int main(void){
	int r[2][2];
	r[0][0] = 0;
	r[0][1] = 1;
	r[1][0] = 2;
	r[1][1] = 3;
	printMat(r[1]);
}
