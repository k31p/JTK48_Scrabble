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

    Dibuat oleh     : Yobel El'Roy D
*/
void removeNewlines(char *string);

/*  
    Deskripsi       : Mengubah seluruh huruf kata menjadi uppercase.

    Parameter       :
        1. word         -> char* (kata yang akan diubah menjadi uppercase, parameter input/output).

    F.S             :
        Kata diubah menjadi uppercase.

    Dibuat oleh     : Amr Fadhilah AAB
*/
void toUpperCase(char *word);

/*  
    Deskripsi       : Memvalidasi apakah kata ada dalam kamus bahasa Inggris.

    Parameter       :
        1. word         -> char* (kata yang akan divalidasi apakah ada dalam kamus).

    Return          :
        - boolean: true jika kata valid, false jika tidak valid.

    Dibuat oleh     : Amr Fadhilah AAB
*/
bool checkDictionary(char *word);

/*  
    Deskripsi       : Memvalidasi apakah posisi melewati batas papan.

    Parameter       :
        1. row          -> int (nomor baris papan yang dipilih oleh pemain).
        2. col          -> int (nomor kolom papan yang dipilih oleh pemain).

    Return          :
        - boolean: true jika posisi valid (tidak keluar batas), false jika keluar batas.

    Dibuat oleh     : Amr Fadhilah AAB
*/
bool checkBound(int row, int col);

/*  
    Deskripsi       : Memvalidasi apakah sekumpulan kotak/tile masih kosong.

    Parameter       :
        1. wordLength   -> int (panjang kata yang dimasukkan pemain).
        2. board        -> char[15][15] (papan permainan berupa array character dua dimensi).
        3. row          -> int (nomor baris papan yang dipilih oleh pemain).
        4. col          -> int (nomor kolom papan yang dipilih oleh pemain).
        5. direction    -> char (arah kata yang akan dipasang di papan: V - Vertikal, H - Horizontal).
        6. depth        -> int (sebagai penghitung kedalaman rekursi).

    Return          :
        - boolean: true jika sekumpulan kotak/tile masih kosong, false jika tidak.

    Dibuat oleh     : Amr Fadhilah AAB
*/
bool isTilesEmpty(int wordLength, char board[15][15], int row, int col, int direction, int depth);

/*  
    Deskripsi       : Memvalidasi apakah kata sesuai dengan huruf yang ada dalam tas.

    Parameter       :
        1. bag          -> char[7] (tas berisi huruf yang dimiliki pemain).
        2. word         -> char* (kata masukan pemain yang akan divalidasi).

    Return          :
        - boolean: true jika valid, false jika tidak valid.

    Dibuat oleh     : Amr Fadhilah AAB
*/
bool validateWordWithBag(char bag[7], char *word, int row, int col, char direction);

/*  
    Deskripsi       : Memvalidasi apakah panjang kata dan posisinya sesuai dengan batas papan.

    Parameter       :
        1. word         -> char* (kata yang dimasukkan pemain).
        2. row          -> int (nomor baris papan yang dipilih oleh pemain).
        3. col          -> int (nomor kolom papan yang dipilih oleh pemain).
        4. direction    -> char (arah kata yang akan dipasang di papan: V - Vertikal, H - Horizontal).

    Return          :
        - boolean: true jika valid, false jika tidak valid.

    Dibuat oleh     : Amr Fadhilah AAB
*/
bool isPositionValid(char *word, int row, int col, char direction);

/*  
    Deskripsi       : Memastikan kata masukkan tidak menimpa kata yang sudah ada sebelumnya.

    Parameter       :
        1. board        -> char[15][15] (papan permainan berupa array character dua dimensi).
        2. word         -> char* (kata masukan pemain).
        3. row          -> int (nomor baris papan yang dipilih oleh pemain).
        4. col          -> int (nomor kolom papan yang dipilih oleh pemain).
        5. direction    -> char (arah kata yang akan dipasang di papan: V - Vertikal, H - Horizontal).

    Return          :
        - boolean: true jika kata masukan pemain sesuai dengan kata yang sudah ada sebelumnya,
                   false jika tidak sesuai.

    Dibuat oleh     : Amr Fadhilah AAB
*/
bool isOverlappingWordValid(char board[15][15], char *word, int row, int col, int direction);

/*  
    Deskripsi       : Memeriksa apakah suatu tile/kotak berpotongan dengan kata lain.

    Parameter       :
        1. board        -> char[15][15] (papan permainan berupa array character dua dimensi).
        2. row          -> int (nomor baris papan yang dipilih oleh pemain).
        3. col          -> int (nomor kolom papan yang dipilih oleh pemain).
        4. direction    -> char (arah kata yang akan dipasang di papan: V - Vertikal, H - Horizontal).

    Return          :
        - boolean: true jika berpotongan, false jika tidak berpotongan.

    Dibuat oleh     : Amr Fadhilah AAB
*/
bool isIntersect(char board[15][15], int row, int col, char direction);

/*  
    Deskripsi       : Fungsi untuk memeriksa apabila posisi kata yang disimpan bersebelahan dengan huruf yang sebelumnya 
                      sudah ada, sehingga huruf yang bersebelahan tersebut membentuk kata baru, lalu kata baru tersebut 
                      diperiksa apakah ada dalam kamus.

    Parameter       :
        1. word         -> char* (kata yang dimasukkan oleh pemain).
        2. board        -> char[15][15] (papan permainan berupa array character dua dimensi).
        3. row          -> int (nomor baris papan yang dipilih oleh pemain).
        4. col          -> int (nomor kolom papan yang dipilih oleh pemain).
        5. direction    -> char (arah kata yang akan dipasang di papan: V - Vertikal, H - Horizontal).

    Return          :
        - boolean: true jika kata yang berpotongan valid, false jika tidak valid.

    Dibuat oleh     : Amr Fadhilah AAB
*/
bool checkIntersectingWord(char *word, char board[15][15], int row, int col, char direction);

/*  
    Deskripsi       : Memeriksa kevalidan sebuah kata untuk ditempatkan pada papan permainan.

    Parameter       :
        1. bag          -> char[7] (tas berisi huruf yang dimiliki pemain).
        2. word         -> char* (kata yang akan divalidasi).
        3. board        -> char[15][15] (papan permainan berupa array karakter dua dimensi).
        4. row          -> int (nomor baris tempat kata akan ditempatkan).
        5. col          -> int (nomor kolom tempat kata akan ditempatkan).
        6. direction    -> char (arah kata: V - Vertikal, H - Horizontal).

    Return          :
        - boolean: true jika kata valid, false jika tidak valid.

    Dibuat oleh     : Amr Fadhilah AAB
*/
bool isValid(char bag[7], char *word, char board[15][15], int row, int col, char direction);

/*  
    Deskripsi       : Menampilkan pesan kesalahan terkait kevalidan sebuah kata.

    Parameter       :
        1. bag          -> char[7] (tas berisi huruf yang dimiliki pemain).
        2. word         -> char* (kata yang akan divalidasi).
        3. board        -> char[15][15] (papan permainan berupa array karakter dua dimensi).
        4. row          -> int (nomor baris tempat kata akan ditempatkan).
        5. col          -> int (nomor kolom tempat kata akan ditempatkan).
        6. direction    -> char (arah kata: V - Vertikal, H - Horizontal).

    F.S             :
        Menampilkan pesan kesalahan terkait kevalidan kata.

    Dibuat oleh     : Amr Fadhilah AAB
*/
void invalidMessage(char bag[7], char *word, char board[15][15], int row, int col, char direction);

#endif 