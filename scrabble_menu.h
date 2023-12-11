#ifndef SCRABBLE_MENU_H
#define SCRABBLE_MENU_H

#include <unistd.h>
#include "tercontrol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <cstdlib>

extern int _Y_Pos;

/*  
    Deskripsi       : Menengahkan teks di tengah layar pada posisi vertikal _Y_Pos.

    Parameter       :
        - text         -> const char* (teks yang akan ditampilkan).

    Dibuat oleh     : Yobel El'Roy D
*/
void centerPos(const char *text);

/*  
    Deskripsi       : Menampilkan layar menu utama dan memproses input pemain.

    Variabel Global:
        - globalMenuChoice -> int (pilihan menu global).

    Dibuat oleh     : Yobel El'Roy D
*/
void displayMainMenu();

#endif