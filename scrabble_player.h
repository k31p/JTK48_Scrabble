#ifndef scrabble_player_H
#define scrabble_player_H

#include "scrabble_utilities.h"

#define MAX_PLAYERNAME_LENGTH 50

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char namaPlayer[MAX_PLAYERNAME_LENGTH];
    unsigned int skor;
    bool is_computer;
} Player;

extern unsigned int _Total_Player;
extern int _Current_Turn; 
extern Player _Players[4];

/*  
    Deskripsi       : 
        Prosedur ini berfungsi untuk mengisi setiap elemen dalam Array of Player dengan input pengguna

    Parameter       :
        1. players      -> Player*
        2. numPlayers   -> Unsigned Int 

    F.S             :
        Parameter players terisi oleh user

    Dibuat oleh     : Yobel El'Roy Doloksaribu 
*/
void initPlayers(Player *players, unsigned int numPlayers); 

/*  
    Deskripsi       : 
        Prosedur ini berfungsi untuk menampilkan list player ke layar

    Parameter       :
        1. players      -> Player*
        2. numPlayers   -> Unsigned Int 

    F.S             :
        Isi dari parameter players tertampil pada layar

    Dibuat oleh     : Yobel El'Roy Doloksaribu 
*/
void printPlayers(Player *players, unsigned int numPlayers);

#endif 