#ifndef __UTILS_C__
#define __UTILS_C__

//print current state of board
void printBoard(void);
// set board to start the game
void initBoard(void);
// move all pieces in given direction
void move();

// add 2 or 4 to empty position
void addNumber(void);
// move left or right
void moveLR(int x, int y, int* last, int* combine, int c);
// move up or down
void moveUD(int x, int y, int* last, int* combine, int c);

#endif