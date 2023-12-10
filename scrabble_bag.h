#ifndef SCRABBLE_BAG_H
#define SCRABBLE_BAG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "scrabble_board.h"

extern int _Main_Bag_Size;
extern char _Main_Bag[98];
void initPlayerBag(char playerBag[7]);
void printBag(char bag[7]);
void setBag(int index);
void setPlayerBag(char bag[7], int index, int *bagSize);
void removePlayerLetter(char *word, char bag[7], char *letterOnBoard);
void fillPlayerBag(char playerBag[7]);
void swapLetter(char bag[7]);

#endif