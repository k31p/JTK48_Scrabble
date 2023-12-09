#include "scrabble_bag.h"

char mainBag[98] = {'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', // 12 A
                    'B', 'B', 'B', // 3 B
                    'C', 'C', // 2 C
                    'D', 'D', 'D', // 3 D
                    'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 8 E
                    'F', 'F', // 2 F
                    'G', 'G', 'G', 'G', // 4 G
                    'H', 'H', // 2 H
                    'I', 'I', 'I', 'I', 'I', 'I', 'I', 'I', // 8 I
                    'J', 'J', // 2 J
                    'K', 'K', 'K', 'K', // 4 K
                    'L', 'L', 'L', 'L', // 4 L
                    'M', 'M', 'M', // 3 M
                    'N', 'N', 'N', 'N', 'N', // 5 N
                    'O', 'O', 'O', 'O', 'O', 'O', // 6 O
                    'P', 'P', // 2 P
                    'Q', // 1 Q
                    'R', 'R', 'R', 'R', 'R', // 5 R
                    'S', 'S', 'S', 'S', 'S', // 5 S
                    'T', 'T', 'T', 'T', 'T', // 5 T
                    'U', 'U', 'U', 'U', // 4 U
                    'V', 'V', // 2 V
                    'W', 'W', // 2 W
                    'X', // 1 X
                    'Y', 'Y', // 2 Y
                    'Z', // 1 Z
                    };

int mainBagSize = 98;

/*

*/
void initPlayerBag(char playerBag[7]){
	int index, i = 0;
	while (i < 7){
		srand(time(NULL));
		index = rand() % mainBagSize;
		playerBag[i] = mainBag[index];
		setBag(index);
		i++;
	}
}

/*

*/
void printBag(char bag[7]){
	int i = 0;
	printf("[");
	while (i < 6){
		printf(" %c,",bag[i]);
		i++;
	}
	printf(" %c ", bag[i]);
	printf("]\n");
}

/*

*/
void setBag(int index){
	mainBag[index] = mainBag[mainBagSize-1];
	mainBag[mainBagSize-1] = '\0';
	mainBagSize--;
}

/*

*/
void setPlayerBag(char bag[7], int index, int *bagSize){
	bag[index] = bag[*bagSize-1];
	bag[*bagSize-1] = '\0';
	(*bagSize)--;
}

/*

*/
void removePlayerLetter(char *word, char bag[7], char *letterOnBoard){
	int wordLength = strlen(word);
	int letterLength = strlen(letterOnBoard);
	int i, j, k, bagSize;
	i = 0;
	bagSize = 7;
	while (i < wordLength){
		k = 0;
		j = 0;
		while (j < 7){
			if (k < letterLength && word[i]==letterOnBoard[j]){
				k++;
				break;
			}
			if (word[i] == bag[j]){
				setPlayerBag(bag, j, &bagSize);
				break;
			}
			j++;
		}
		i++;
	}
}

/*

*/
void fillPlayerBag(char playerBag[7]){
	int index, bagSize = 0;
	while (playerBag[bagSize]!='\0'){
		bagSize++;
	}
	
	while (bagSize < 7){
		srand(time(NULL));
		index = rand() % mainBagSize;
		playerBag[bagSize] = mainBag[index];
		setBag(index);
		bagSize++;
	}
}

/*

*/
void swapLetter(char bag[7]){
	int N, i, ind;
	char temp;
	printf("Masukkan banyak huruf yang ingin diganti: ");
	scanf(" %d", &N);
	int index[N];

	printf("Masukkan urutan huruf yang ingin diganti (contoh: 1 4 6 ...): ");
	i = 0;
	while (i < N){
		scanf(" %d", &index[i]);
		i++;
	}

	i = 0;
	while (i < N){
		index[i]--;
		temp = bag[index[i]];
		srand(time(NULL)*i*399397132);
		ind = rand() % mainBagSize;
		bag[index[i]] = mainBag[ind];
		mainBag[ind] = temp;
		i++;
	}
}