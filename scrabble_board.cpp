#include "scrabble_board.h"
#include "scrabble_utilities.h"
#include <ctype.h>

char _Board[15][15];

/* Mereset papan Scrabble (mengosongkan seluruh isinya)

*/
void initBoard(){
	int i, j;
	
	i = 0;
	while (i<15){
		j = 0;
		while (j<15){
			_Board[i][j] = ' ';
			j++;
		}
		i++;
	}
	_Board[7][7]='*';
}

/* Mencetak papan Scrabble sesuai dengan kondisi saat ini

*/
void printBoard(){
	int i, j, k;
	int termCols, termRows;
	
	tc_get_cols_rows(&termCols, &termRows);
	int colPos = (termCols / 2) - 2;
	int rowPos = 1;

	tc_set_cursor(colPos, rowPos);
	
	k = 0;
	printf("   ");
	while(k<15){
		printf(" %c  ", (char)65+k);
		k++;
	}
	
	tc_set_cursor(colPos, ++rowPos);

	k = 0;
	while (k<15){
		tc_set_cursor(colPos, rowPos);
		printf("  ");
		i = 0;
		while (i<15){
			printf("+---");
			i++;
		}
		printf("+");
		printf("\n");
		tc_set_cursor(colPos, ++rowPos);
		
		printf("%2d", (1+k));		

		j = 0;
		while (j<15){
			printf("| %c ", _Board[k][j]);
			j++;
		}
		printf("|");

		rowPos++;
		printf("\n");
		k++;
	}
	
	tc_set_cursor(colPos, rowPos);
	
	printf("  ");
	i = 0;
	while (i<15){
		printf("+---");
		i++;
	}
	printf("+");
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
			_Board[row][col+i] = word[i];
			i++;
		}
	} else if (direction=='V'){
		i = 0;
		while (i<strlen(word)){
			_Board[row+i][col] = word[i];
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
			if (_Board[row][col]!=' ' && _Board[row][col]!='*'){
				letterOnBoard[j] = _Board[row][col];
				j++;
			}
			col++;	
		}
		letterOnBoard[j] = '\0';
	} else if (direction == 'V'){
		while (checkBound(row, col) && j < wordLength){
			if (_Board[row][col]!=' ' && _Board[row][col]!='*'){
				letterOnBoard[j] = _Board[row][col];
				j++;
			}
			row++;
		}
		letterOnBoard[j] = '\0';
	}
}
