#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <string.h>

extern char board[15][15];
void initBoard();
void printBoard();
void getInput(char *word, int *row, int *column, char *direction);
void placeTiles(char *word, int row, int col, char direction);
void extractLetter(char *letterOnBoard, int row, int col, int direction, char *word);

#endif