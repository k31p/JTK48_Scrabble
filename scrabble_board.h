#ifndef SCRABBLE_BOARD_H
#define SCRABBLE_BOARD_H

#include <stdio.h>
#include <string.h>
#include "tercontrol.h"

extern char _Board[15][15];
void initBoard();
void printBoard();
void getInput(char *word, int *row, int *column, char *direction);
void placeTiles(char *word, int row, int col, char direction);
void extractLetter(char *letterOnBoard, int row, int col, int direction, char *word);

#endif