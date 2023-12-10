// MODUL MEMVALIDASI INPUT DARI PEMAIN
// Penanggung Jawab: Amr Fadhilah Abiyyu Alif Basysyar (231524002)

#include "scrabble_utilities.h"
#include <string.h>

void removeNewlines(char *string){
    string[strcspn(string, "\n")] = '\0';
}
 
 /* Prosedur untuk mengubah seluruh huruf kata menjadi uppercase.  
	Parameter:
    - word (char*): kata yang akan diubah menjadi uppercase, parameter input/output.
 */
void toUpperCase(char *word){
	int wordLength = strlen(word);
	int i = 0;
	while (i<wordLength){
		// Mengubah setiap elemen (huruf) kata menjadi uppercase.
		if ((int)word[i] >= 97 && (int)word[i] <= 122){
			word[i] = (char)((int)word[i] - 32);
		}
		i++;
	}
}


/* Fungsi untuk memvalidasi apakah kata yang dimasukkan pemain ada dalam kamus bahasa Inggris.
   Parameter:
   - word (char*): kata masukkan pemain yang akan divalidasi apakah ada dalam kamus.
   Return:
   - boolean: true jika kata valid, false jika kata tidak valid.
*/
bool checkDictionary(char *word){
	char wordInDictionary[30];
	char filename[40];
	sprintf(filename, "english-dictionary/letter-%c.txt", toupper(word[0]));
	FILE *file = fopen(filename, "r");
	toUpperCase(word);
	while (fscanf(file, "%s\n", wordInDictionary)==1){
		toUpperCase(wordInDictionary);
		if (strcmp(word, wordInDictionary)==0){
			fclose(file);
			return true;
		}
	}
	fclose(file);
	return false;
}


/* Fungsi untuk memvalidasi apakah posisi yang dimasukkan melewati batas papan.
   Parameter:
   - row (int): nomor baris papan yang dipilih oleh pemain.
   - column (int): nomor kolom papan yang dipilih oleh pemain.
   Return:
   - boolean: true jika posisi valid (tidak keluar batas), false jika keluar batas.
*/
bool checkBound(int row, int col){
	return (row >= 0 && row <= 14 && col >= 0 && col <= 14);
}


/* Fungsi untuk memvalidasi apakah sekumpulan kotak/tile masih kosong.
   Parameter:
   - wordLength (int): panjang kata yang dimasukkan pemain.
   - board (array 2D of char): papan permainan berupa array character dua dimensi.
   - row (int): nomor baris papan yang dipilih oleh pemain.
   - col (int): nomor kolom papan yang dipilih oleh pemain 
   - direction (char): arah kata yang akan dipasang di papan (V: Vertikal, H: Horizontal).
   - depth (int): sebagai penghitung kedalaman rekursi.
   Return:
   - boolean: true jika sekumpulan kotak/tile masih kosong, false jika tidak.
*/
bool isTilesEmpty(int wordLength, char board[15][15], int row, int col, int direction, int depth){
	if (depth < wordLength){
		if (!checkBound(row, col)){
			return false;
		} else {
			if (direction == 'H'){
				return board[row][col]==' ' && isTilesEmpty(wordLength, board, row, col+1, direction, depth+1);
			} else  if (direction == 'V'){
				return board[row][col]==' ' && isTilesEmpty(wordLength, board, row+1, col, direction, depth+1);
			}
		}
	} else {
		return true;
	}
}


/* Fungsi untuk memeriksa apakah kata yang dimasukkan pemain sesuai 
   dengan ketersediaan huruf dalam tas.
   Parameter:
   - bag (array of char): tas berisi huruf yang dimiliki pemain.
   - word (char*): kata masukan pemain yang akan divalidasi
   Return:
   - boolean: true jika valid, false jika tidak. 
*/
bool validateWordWithBag(char bag[7], char *word, int row, int col, char direction){
	char letterInBag[26], letterInWord[26];
	int wordLength = strlen(word);
	char *letterOnBoard = (char *) malloc(wordLength*sizeof(char));
	extractLetter(letterOnBoard, row, col, direction, word);
	int letterLength = strlen(letterOnBoard);
	int i;
	
	// Inisialisasi array dengan nilai 0
	i = 0;
	while (i < 26){
		letterInBag[i] = 0;
		i++;
	}
	i = 0;
	while (i < 26){
		letterInWord[i] = 0;		
		i++;
	}
	
	// Menghitung setiap huruf di tas
	i = 0;
	while (i < 7){
		letterInBag[(int)bag[i] - (int)'A']++;
		i++;
	}
	
	// Menghitung setiap huruf di papan
	i = 0;
	while (i < letterLength){
		letterInBag[(int)letterOnBoard[i] - (int)'A']++;
		i++;
	}
	
	// Menghitung setiap huruf di kata masukan pemain
	i = 0;
	while (i < wordLength){
		letterInWord[(int)word[i] - (int)'A']++;
		i++;
	}
	
	// Memeriksa apakah huruf tersedia untuk membentuk kata yang dipilih
	i = 0;
	while (i < 26){
		if (letterInWord[i] > letterInBag[i]){
			return false;
		}
		i++;
	}
	return true;
}


/* Fungsi untuk memvalidasi apakah panjang kata yang dimasukkan ke posisi
   tersebut valid atau melewati batas papan.
   Parameter:
   - word (char *): kata yang dimasukkan pemain.
   - row (int): nomor baris papan yang dipilih oleh pemain.
   - col (int): nomor kolom papan yang dipilih oleh pemain.
   - direction (char): arah kata yang akan dipasang di papan (V: Vertikal, H: Horizontal).
   Return:
   - boolean: true jika valid, false jika tidak.
*/
bool isPositionValid(char *word, int row, int col, char direction){
	int wordLength = strlen(word);
	if (direction == 'H'){
		return checkBound(row, col+wordLength-1);
	} else if (direction == 'V') {
		return checkBound(row+wordLength-1, col);
	}
}


/* Fungsi untuk memastikan kata masukkan tidak menimpa kata yang sudah ada sebelumnya
   Parameter:
   - board (array 2D of char): papan permainan berupa array character dua dimensi.
   - word (char *): kata masukan pemain.
   - row (int): nomor baris papan yang dipilih oleh pemain.
   - col (int): nomor kolom papan yang dipilih oleh pemain 
   - direction (char): arah kata yang akan dipasang di papan (V: Vertikal, H: Horizontal).
   Return:
   - boolean: true jika kata masukan pemain sesuai dengan kata yang sudah ada sebelumnya,
   			  false jika tidak.
*/
bool isOverlappingWordValid(char board[15][15], char *word, int row, int col, int direction){
	int wordLength = strlen(word);
	int i = 0;
	if (direction == 'H'){
		while (i < wordLength){
			if (board[row][col+i]!=' ' && board[row][col+i]!=word[i] && board[row][col+i]!='*'){
				return false;
			}
			i++;
		}
	} else if (direction == 'V'){
		while (i < wordLength){
			if (board[row+i][col]!=' ' && board[row+i][col]!=word[i] && board[row+i][col]!='*'){
				return false;
			}
			i++;
		}
	}
	return true;
}


/* Fungsi untuk memeriksa apakah suatu tile/kotak berpotongan dengan kata lain.
   Parameter:
   - board (array 2D of char): papan permainan berupa array character dua dimensi.
   - row (int): nomor baris papan yang dipilih oleh pemain.
   - col (int): nomor kolom papan yang dipilih oleh pemain 
   - direction (char): arah kata yang akan dipasang di papan (V: Vertikal, H: Horizontal).
   Return:
   - boolean: true jika berpotongan, false jika tidak.
*/
bool isIntersect(char board[15][15], int row, int col, char direction){
	if (direction == 'H'){
		if (!checkBound(row+1, col)){
			return board[row-1][col]!=' ';
		} else if (!checkBound(row-1, col)){
			return board[row+1][col]!=' ';
		} else {
			return (board[row+1][col]!=' ' || board[row-1][col]!=' ');
		}
	} else if (direction == 'V'){
		if (!checkBound(row, col+1)){
			return board[row][col-1]!=' ';
		} else if (!checkBound(row, col-1)){
			return board[row][col+1]!=' ';
		} else {
			return (board[row][col+1]!=' ' || board[row][col-1]!=' ');
		}
	}
}


/* Fungsi untuk memeriksa apabila posisi kata yang disimpan bersebelahan dengan huruf yang sebelumnya 
   sudah ada, sehingga huruf yang bersebelahan tersebut membentuk kata baru, lalu kata baru tersebut 
   diperiksa apakah ada dalam kamus.
   Parameter:
   - word (char *): kata yang dimasukkan oleh pemain.
   - board (array 2D of char): papan permainan berupa array character dua dimensi.
   - row (int): nomor baris papan yang dipilih oleh pemain.
   - col (int): nomor kolom papan yang dipilih oleh pemain 
   - direction (char): arah kata yang akan dipasang di papan (V: Vertikal, H: Horizontal).
   Return:
   - boolean: true jika kata yang berpotongan valid, false jika tidak.
*/
bool checkIntersectingWord(char *word, char board[15][15], int row, int col, char direction){
	char *wordOnBoard;
	int i, j, firstTile;
	int wordLength = strlen(word);
	i = 0;
	while (i < wordLength){
		wordOnBoard = (char*) malloc(15*sizeof(char));
		if (direction=='H' && isIntersect(board, row, col+i, direction)){ // Jika arah pemasangan kata horizontal.
			firstTile = row;
			j = 1;
			// Mencari posisi awal dari kata yang berpotongan dengan kata masukkan pemain.
			while (board[row-j][col+i]!=' ' && checkBound(row-j, col+i)){
				firstTile = row-j;
				j++;
			}
			
			j = 0;
			// Mengekstrak kata pada board/papan yang berpotongan dengan kata masukkan pemain.
			while ((board[firstTile][col+i]!=' ' || firstTile==row) && checkBound(firstTile, col+i)){
				wordOnBoard[j] = board[firstTile][col+i];
				if (firstTile==row){
					wordOnBoard[j] = word[i];
				}
				j++;
				firstTile++;
			}
			wordOnBoard[j] = '\0';
			
			// Memeriksa apakah kombinasi huruf dari kata masukkan user dan huruf pada papan valid.
			if (!checkDictionary(wordOnBoard)){
				free(wordOnBoard);
				return false;
			}	
		} else if (direction=='V' && isIntersect(board, row+i, col, direction)){ // Jika arah pemasangan kata vertikal.
	
			firstTile = col;
			j = 1;
			// Mencari posisi awal dari kata yang berpotongan dengan kata masukkan pemain.
			while (board[row+i][col-j]!=' ' && checkBound(row+i, col-j)){
				firstTile = col-j;
				j++;
			}
			
			j = 0;
			// Mengekstrak kata pada board/papan yang berpotongan dengan kata masukkan pemain.
			while ((board[row+i][firstTile]!=' ' || firstTile==col) && checkBound(row+i, firstTile)){
				wordOnBoard[j] = board[row+i][firstTile];
				if (firstTile==col){
					wordOnBoard[j] = word[i];
				}
				j++;
				firstTile++;
			}
			wordOnBoard[j] = '\0';
			
			// Memeriksa apakah kombinasi huruf dari kata masukkan user dan huruf pada papan valid.
			if (!checkDictionary(wordOnBoard)){
				free(wordOnBoard);
				return false;
			}
		}	
		free(wordOnBoard);
		i++;
	}
	return true;
}

/*

*/
bool isValid(char bag[7], char *word, char board[15][15], int row, int col, char direction){
	bool wordValid = checkDictionary(word);
	bool tilesNotEmpty = !isTilesEmpty(strlen(word), board, row, col, direction, 0);
	bool notOutOfBound = checkBound(row, col);
	bool positionValid = isPositionValid(word, row, col, direction);
	bool overlappingWordValid = isOverlappingWordValid(board, word, row, col, direction);
	bool intersectingWordValid = checkIntersectingWord(word, board, row, col, direction);
	bool wordValidWithBag = validateWordWithBag(bag, word, row, col, direction);
	
	return wordValid && tilesNotEmpty && notOutOfBound && positionValid 
		   && overlappingWordValid && intersectingWordValid && wordValidWithBag;
}

/*

*/
void invalidMessage(char bag[7], char *word, char board[15][15], int row, int col, char direction){
	if (!validateWordWithBag(bag, word, row, col, direction)){
		printf("Huruf yang dimiliki kurang untuk membentuk kata tersebut.\n");
	}
	if (!checkDictionary(word)){
		printf("Kata tidak ada di kamus.\n");
	}
	if (isTilesEmpty(strlen(word), board, row, col, direction, 0)){
		printf("Posisi yang dimasukkan tidak berpotongan dengan kata yang sudah ada sebelumnya.\n");
	}
	if (!checkBound(row, col)){
		printf("Posisi yang dimasukkan keluar batas (1).\n");
	}
	if (!isPositionValid(word, row, col, direction)){
		printf("Posisi yang dimasukkan keluar batas (2).\n");
	}
	if (!isOverlappingWordValid(board, word, row, col, direction)){
		printf("Kata yang bertumpang tindah tidak valid.\n");
	}
	if (!checkIntersectingWord(word, board, row, col, direction)){
		printf("Kata yang berpotongan tidak valid.\n");
	}
}
