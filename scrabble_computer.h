//
//

#ifndef SCRABBLE_COM_OPPONENT_H
#define SCRABBLE_COM_OPPONENT_H

#include <string.h>
#include <stdbool.h>
#include "scrabble_utilities.h"
#include "scrabble_board.h"

int setDifficulty(int input);
void choosePosition(char *enemyWord, int enemyRow, int enemyCol, char enemyDirection, int *row, int *col, char *direction);
void generateWord(char *bags, char bag[7], char *word, char *letterOnBoard, int row, int col, char direction, int difficulty, bool *isFound, int depth);
void reposition(char *word, int *row, int *col, char direction);
void goThinkComputer(char bag[7], char *word, int row, int col, char direction, int difficulty);

#endif