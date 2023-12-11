#ifndef SCRABBLE_SCORING_H
#define SCRABBLE_SCORING_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*  
    Deskripsi       : 
        Fungsi ini berfungsi untuk menghitung skor dari kata yang diinput pemain berdasarkan nilai perhuruf
        sesuai aturan permainan scrabble

    Parameter       :
        1. kata : array of char (string) : parameter input

    F.S             :
        Mereturn nilai akumulatif per huruf dari kata yang dimasukkan

    Dibuat oleh     : Micho DF
*/
int hitungSkorKata(char *kata);

void sortingScore();

void showWinner();

void showHighscore();

void updateHighscore();

#endif
