#include "scrabble_computer.h"

/*

*/
int setDifficulty(){
	int input;
	printf("Select Difficulty of Computer:\n");
	printf("1. Easy\n");
	printf("2. Normal\n");
	printf("3. Hard\n");
	scanf(" %d", &input);
	if (input==1){
		return 3;
	} else if (input==2){
		return 4;
	} else if (input==3){
		return 5;
	}
}

/*

*/
void choosePosition(char *enemyWord, int enemyRow, int enemyCol, char enemyDirection, int *row, int *col, char *direction){
	int enemyWordLength = strlen(enemyWord);
	int intersectList[enemyWordLength][2];
	int i = 0;
	while(i < enemyWordLength){
		if (enemyDirection == 'H'){
			if (!isIntersect(_Board, enemyRow, enemyCol+i, enemyDirection)){
				intersectList[i][0] = enemyRow;
				intersectList[i][1] = enemyCol+i;
			}
		} else if (enemyDirection == 'V'){
			if (!isIntersect(_Board, enemyRow+i, enemyCol, enemyDirection)){
				intersectList[i][0] = enemyRow+i;
				intersectList[i][1] = enemyCol;
			}
		}
		i++;
	}
	*row = intersectList[0][0];
	*col = intersectList[0][1];
	if (enemyDirection == 'H'){
		*direction = 'V';
	} else if (enemyDirection == 'V'){
		*direction = 'H';
	}
}

/*

*/
void generateWord(char *bags, char bag[7], char *word, char *letterOnBoard, int row, int col, char direction, int difficulty, bool *isFound, int depth){
	if (depth == difficulty){
		word[difficulty] = '\0';
		if (checkDictionary(word) && validateWordWithBag(bag, word, row, col, direction) && strstr(word, letterOnBoard) != NULL){
			*isFound = true;
			printf("Word: %s", word);
		}
		return;
	}
	int i = 0;
	while (i < strlen(bags)){
		word[depth] = bags[i];
		generateWord(bags, bag, word, letterOnBoard, row, col, direction, 3, isFound, depth+1);
		if (*isFound){
			return;
		}
		i++;
	}
}

/*

*/
void reposition(char *word, int *row, int *col, char direction){
	int wordLength = strlen(word);
	int i = 0;
	while (i < wordLength){
		if (word[i] == _Board[*row][*col]){
			break;
		}
		i++;
	}
	if (direction == 'H'){
		*col -= i;
	} else if (direction == 'V') {
		*row -= i;
	}
}

void goThinkComputer(char bag[7], char *word, int *row, int *col, char direction, int difficulty){
	bool isFound = false;
	char *letterOnBoard = (char *) malloc(15*sizeof(char));
	char *bags = (char *) malloc(15*sizeof(char));
	extractLetter(letterOnBoard, *row, *col, direction, word);
	int wordOnBoardLength = strlen(letterOnBoard);
	letterOnBoard [ wordOnBoardLength ] = '\0';
	strcpy(bags, letterOnBoard);
	int i = 0;
	while (i < 7){
		bags[ wordOnBoardLength + i ] = bag[i];
		i++;
	}
	bags[wordOnBoardLength + i] = '\0';
	
	while (difficulty > 2 && !isFound){
		generateWord(bags, bag, word, letterOnBoard, *row, *col, direction, difficulty, &isFound, 0);
		difficulty--;
	}
	if (isFound){
		reposition(word, row, col, direction);
	}
    free(letterOnBoard);
    free(bags);
}

/*

*/
void swapLetter_Com(char bag[7]){
	int N, i, ind;
	char temp;

	srand(time(NULL)*345872923);
	N = rand()%7 + 1;
	int index[N];

	i = 0;
	while (i < N){
		srand(time(NULL)*345872923*i);
		index[i] = rand()%7 + 1;
		i++;
	}

	i = 0;
	while (i < N){
		index[i]--;
		temp = bag[index[i]];
		srand(time(NULL)*i*399397132);
		ind = rand() % _Main_Bag_Size;
		bag[index[i]] = _Main_Bag[ind];
		_Main_Bag[ind] = temp;
		i++;
	}
}