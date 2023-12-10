#include "scrabble_scoring.h"

// Fungsi untuk menghitung skor kata tanpa mempertimbangkan multiplier
int hitungSkorKata(char *kata) {
    int skor = 0;
    int panjang = strlen(kata);

    const char *hurufHuruf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int skorHuruf[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    for (int i = 0; i < panjang; i++) {
        char huruf = toupper(kata[i]); 

        for (int j = 0; j < 26; j++) {
            if (huruf == hurufHuruf[j]) {
                skor += skorHuruf[j];
                break;
            }
        }
    }

    return skor;
}