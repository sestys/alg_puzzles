#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

#define LEFT 'a'
#define RIGHT 'd'
#define UP 'w'
#define DOWN 's'
#define SIZE 4

#define TRUE 1
#define FALSE 0

const int numbers[] = {
	0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048
};

int board[SIZE * SIZE];

void initBoard(void) {
	int i;
	for (i = 0; i < SIZE * SIZE; i++) {
		board[i] = 0;
	}
	// set rand()
	srand(time(NULL));
	for (int i = 0; i < 3; i++) {
		addNumber();
	}
}


void printBoard(void) {
	for (int i = 0; i < SIZE * SIZE; i++) {
		printf("[%4i]", numbers[board[i]]);
		if (i % SIZE == SIZE - 1) {
			printf("\n");
		}
	}
}

void move() {
	int x, y;
	int last; // index to move to
	int combine; // index to combine piece with
	char direction;

	direction = getchar();
	getchar(); // get the newline

	switch (direction) {
	case UP:
		for (x = 0; x < SIZE; x++) {
			last = 0;
			combine = 0;
			for (y = 0; y < SIZE; y++) {
				moveUD(x, y, &last, &combine, 1);
			}
		}
		break;
	case DOWN:
		for (x = 0; x < SIZE; x++) {
			last = SIZE - 1;
			combine = SIZE - 1;
			for (y = SIZE - 1; y >= 0; y--) {
				moveUD(x, y, &last, &combine, -1);
			}
		}
		break;

	case RIGHT:
		for (y = 0; y < SIZE; y++) {
			last = SIZE - 1;
			combine = SIZE - 1;
			for (x = SIZE - 1; x >= 0; x--) {
				moveLR(x, y, &last, &combine, -1);
			}
		}
		break;

	case LEFT:
		for (y = 0; y < SIZE; y++) {
			last = 0;
			combine = 0;
			for (x = 0; x < SIZE; x++) {
				moveLR(x, y, &last, &combine, 1);
			}
		}
		break;
	default:
		printf("Wrong move entered\n");
		return;
	}
	addNumber();
	printBoard();

}
void moveUD(int x, int y, int* last, int* combine, int c) {
	if (board[y * SIZE + x] != 0) {
		if (*combine != y) {
			if (board[y * SIZE + x] == board[(*combine)*SIZE + x]) {
				board[(*combine)*SIZE + x] += 1;
				board[y * SIZE + x] = 0;
				*combine += c;
			} else if (*last != y) {
				board[(*last)*SIZE + x] = board[y * SIZE + x];
				board[y * SIZE + x] = 0;
				*combine = *last;
				*last += c;
			} else {
				*combine = *last;
				*last += c;
			}
		} else {
			*last += c;
		}
	}
}
void moveLR(int x, int y, int* last, int* combine, int c) {
	if (board[y * SIZE + x] != 0) {
		if (*combine != x) { // possible to combine numbers
			if (board[y * SIZE + x] == board[y * SIZE + (*combine)]) { //numbers are same, combine
				board[y * SIZE + (*combine)] += 1;
				board[y * SIZE + x] = 0;
				*combine += c;
			} else if (*last != x) {
				board[y * SIZE + (*last)] = board[y * SIZE + x];
				board[y * SIZE + x] = 0;
				*combine = *last;
				*last += c;
			} else {
				*combine = *last;
				*last += c;
			}
		} else {
			*last += c;
		}

	}

}
void addNumber(void) {
	int x, y, check;
	check = FALSE;
	for (int i = 0; i < SIZE * SIZE; i++) {
		if (board[i] == 0) {
			check = TRUE;
			break;
		}
	}
	if (check) {
		while (1) {
			x = rand() % SIZE;
			y = rand() % SIZE;
			if (board[y * SIZE + x] == 0) {
				board[y * SIZE + x] = (rand() % 2) + 1;
				break;
			}
		}
	} else {
		printf("GAME OVER\n");
		exit(-1);
	}
}
