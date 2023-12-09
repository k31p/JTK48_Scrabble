#include "scrabble_board.h"
#include "scrabble_utilities.h"
#include <ctype.h>

char board[15][15];

/* Mereset papan Scrabble (mengosongkan seluruh isinya)

*/
void initBoard(){
	int i, j;
	
	i = 0;
	while (i<15){
		j = 0;
		while (j<15){
			board[i][j] = ' ';
			j++;
		}
		i++;
	}
	board[7][7]='*';
}

/* Mencetak papan Scrabble sesuai dengan kondisi saat ini

*/
void printBoard(){
	int i, j, k;
	
	k = 0;
	printf("   ");
	while(k<15){
		printf(" %c  ", (char)65+k);
		k++;
	}
	printf("\n");

	k = 0;
	while (k<15){
		
		printf("  ");
		i = 0;
		while (i<15){
			printf("+---");
			i++;
		}
		printf("+\n%2d", (1+k));
		
		j = 0;
		while (j<15){
			printf("| %c ", board[k][j]);
			j++;
		}
		printf("|\n");
		
		k++;
	}
	
		printf("  ");
		i = 0;
		while (i<15){
			printf("+---");
			i++;
		}
		printf("+\n");
}

/*

*/
void getInput(char *word, int *row, int *col, char *direction){
	char tempCol;
	printf("Masukkan kata yang akan dipasang: ");
	scanf(" %s", word);
	toUpperCase(word);
	printf("Masukkan posisi kolom dan baris (contoh: 11 F): ");
	scanf(" %d %c", row, &tempCol);
	*row = *row-1;
	*col = toupper(tempCol) - 65;
	printf("Masukkan arah pemasangan (H/V): ");
	scanf(" %c", direction);
	*direction = toupper(*direction);
	printf("%s %d %d %c\n", word, *row, *col, *direction);
}

void placeTiles(char *word, int row, int col, char direction){
	int i;
	if (direction=='H'){
		i = 0;
		while (i<strlen(word)){
			board[row][col+i] = word[i];
			i++;
		}
	} else if (direction=='V'){
		i = 0;
		while (i<strlen(word)){
			board[row+i][col] = word[i];
			i++;
		}
	}
}

/*

*/
void extractLetter(char *letterOnBoard, int row, int col, int direction, char *word){
	// Mengekstrak huruf pada board/papan yang berpotongan dengan kata masukkan pemain.
	int wordLength = strlen(word);
	int j = 0;
	if (direction == 'H'){
		while (checkBound(row, col) && j < wordLength){
			if (board[row][col]!=' ' && board[row][col]!='*'){
				letterOnBoard[j] = board[row][col];
				j++;
			}
			col++;	
		}
		letterOnBoard[j] = '\0';
	} else if (direction == 'V'){
		while (checkBound(row, col) && j < wordLength){
			if (board[row][col]!=' ' && board[row][col]!='*'){
				letterOnBoard[j] = board[row][col];
				j++;
			}
			row++;
		}
		letterOnBoard[j] = '\0';
	}
}
