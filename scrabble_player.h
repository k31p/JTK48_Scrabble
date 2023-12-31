#ifndef SCRABBLE_PLAYER_H
#define SCRABBLE_PLAYER_H

#include "scrabble_utilities.h"

#define MAX_PLAYERNAME_LENGTH 50

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char namaPlayer[MAX_PLAYERNAME_LENGTH];
    char bag[7];
    unsigned int skor;
    bool is_computer;
} Player;

extern unsigned int _Total_Player;
extern int _Current_Player_Turn; 
extern Player _Players[4];

/*  
    Deskripsi       : 
        Prosedur ini berfungsi untuk mengisi setiap elemen dalam Array of Player dengan input pengguna

    Parameter       :
        1. numPlayers   -> Unsigned Int 

    F.S             :
        Parameter players terisi oleh user

    Dibuat oleh     : Yobel El'Roy D 
*/
void initPlayers(unsigned int numPlayers); 

/*  
    Deskripsi       : 
        Prosedur ini berfungsi untuk menampilkan list player ke layar

    Parameter       :
        1. players      -> Player*
        2. numPlayers   -> Unsigned Int 

    F.S             :
        Isi dari parameter players tertampil pada layar

    Dibuat oleh     : Yobel El'Roy D
*/
void printPlayers(unsigned int numPlayers);

/*  
    Deskripsi       : Mengganti giliran pemain menjadi pemain berikutnya.

    F.S             :
        Mengganti giliran pemain saat ini menjadi pemain berikutnya.

    Dibuat oleh     : Yobel El'Roy D
*/
void nextTurn();

#endif 