#include <stdio.h>
#include <stdlib.h>

#include "utils.h"


int main(int argc, char const *argv[])
{
	printf("WELCOME to 2048 game\n\nControls:\n");
	printf("UP - w;  DOWN - s;  LEFT - a;  RIGHT - d\n\n");
	initBoard();
	printBoard();
	while (1) {
		fflush(stdin);
		move();
	}
	return 0;
}