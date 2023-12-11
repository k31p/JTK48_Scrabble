#ifndef SCRABBLE_SAVELOAD_H
#define SCRABBLE_SAVELOAD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scrabble_player.h"
#include "scrabble_board.h"
#include "scrabble_menu.h"

/*  
    Deskripsi       : Memuat permainan dari file yang disimpan.

    Parameter       :
        - LoadNumber   -> unsigned int (nomor slot permainan yang akan di-load).

    F.S             :
        Memuat data permainan dari file savedata.dat dan menampilkan pemain serta papan permainan.

    Dibuat oleh     : Micho DF & Yobel El'Roy D
*/
void loadgame(unsigned int LoadNumber);

/*  
    Deskripsi       : Menyimpan permainan ke file savedata.dat.

    Parameter       :
        - saveNumber   -> unsigned int (nomor slot permainan yang akan di-save).

    F.S             :
        Menyimpan data permainan, pemain, dan papan permainan ke dalam file savedata.dat.

    Dibuat oleh     : Micho DF & Yobel El'Roy D
*/
void saveGame(unsigned int saveNumber);

/*  
    Deskripsi       : Menampilkan opsi slot penyimpanan dan menyimpan permainan ke slot yang dipilih.

    F.S             :
        Menyimpan permainan ke slot yang dipilih oleh pengguna.

    Dibuat oleh     : Amr Fadhilah AAB
*/
void saveSlot();

/*  
    Deskripsi       : Menampilkan opsi permainan yang tersimpan dan memuat permainan dari slot yang dipilih.

    F.S             :
        Memuat permainan dari slot yang dipilih oleh pengguna.

    Dibuat oleh     : Micho DF & Yobel El'Roy D
*/
void LoadMenus();

#endif