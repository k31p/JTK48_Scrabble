#ifndef SCRABBLE_UTILITIES_H
#define SCRABBLE_UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "scrabble_board.h"

/*  
    Deskripsi       : 
        Prosedur ini berfungsi untuk menghilangkan newline dari suatu string

    Parameter       :
        1. string       -> char*

    F.S             :
        String tidak mengandung newline

    Dibuat oleh     : Yobel El'Roy Doloksaribu 
*/
void removeNewlines(char *string);

void toUpperCase(char *word);
 /* Prosedur untuk mengubah seluruh huruf kata menjadi uppercase.  
	Parameter:
    - word (char*): kata yang akan diubah menjadi uppercase, parameter input/output.
 */


bool checkDictionary(char *word);
/* Fungsi untuk memvalidasi apakah kata yang dimasukkan pemain ada dalam kamus bahasa Inggris.
   Parameter:
   - word (char*): kata masukkan pemain yang akan divalidasi apakah ada dalam kamus.
   Return:
   - boolean: true jika kata valid, false jika kata tidak valid.
*/


bool checkBound(int row, int col);
/* Fungsi untuk memvalidasi apakah posisi yang dimasukkan melewati batas papan.
   Parameter:
   - row (int): nomor baris papan yang dipilih oleh pemain.
   - column (int): nomor kolom papan yang dipilih oleh pemain.
   Return:
   - boolean: true jika posisi valid (tidak keluar batas), false jika keluar batas.
*/


bool isTilesEmpty(int wordLength, char board[15][15], int row, int col, int direction, int depth);
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


bool validateWordWithBag(char bag[7], char *word, int row, int col, char direction);
/* Fungsi untuk memeriksa apakah kata yang dimasukkan pemain sesuai 
   dengan ketersediaan huruf dalam tas.
   Parameter:
   - bag (array of char): tas berisi huruf yang dimiliki pemain.
   - word (char*): kata masukan pemain yang akan divalidasi
   Return:
   - boolean: true jika valid, false jika tidak. 
*/


bool isPositionValid(char *word, int row, int col, char direction);
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


bool isOverlappingWordValid(char board[15][15], char *word, int row, int col, int direction);
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


bool isIntersect(char board[15][15], int row, int col, char direction);
/* Fungsi untuk memeriksa apakah suatu tile/kotak berpotongan dengan kata lain.
   Parameter:
   - board (array 2D of char): papan permainan berupa array character dua dimensi.
   - row (int): nomor baris papan yang dipilih oleh pemain.
   - col (int): nomor kolom papan yang dipilih oleh pemain 
   - direction (char): arah kata yang akan dipasang di papan (V: Vertikal, H: Horizontal).
   Return:
   - boolean: true jika berpotongan, false jika tidak.
*/


bool checkIntersectingWord(char *word, char board[15][15], int row, int col, char direction);
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

bool isValid(char bag[7], char *word, char board[15][15], int row, int col, char direction);
/*

*/

void invalidMessage(char bag[7], char *word, char board[15][15], int row, int col, char direction);
/*

*/

#endif 