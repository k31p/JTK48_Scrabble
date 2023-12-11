#include "scrabble_scoring.h"
#include "scrabble_player.h"
#include "scrabble_menu.h"

// Fungsi untuk menghitung skor kata tanpa mempertimbangkan multiplier
// PJ: Micho
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

void sortingScore(){
    int len = 4;
	int i, j;
    Player temp;
	i = 1;
	while (i < len){
		j = 0;
		while (j < i){
			if (_Players[i].skor > _Players[j].skor){
				temp = _Players[i];
				_Players[i] = _Players[j];
				_Players[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void showWinner(){
    tc_clear_screen();
    int i = 0;
    centerPos("Rank:\n");
    while (i < 4){
        printf("\t\t\t\t\t\t%d. %s's Score: %d\n", i+1, _Players[i].namaPlayer, _Players[i].skor);
        i++;
    }
    tc_getch();
    printf("\n\t\t\t\t\t\tWinner: %s\n", _Players[0].namaPlayer);
    tc_getch();
}

void showHighscore(){
    int highscore;
    FILE* file = fopen("highscore.txt", "r");
    fscanf(file, " %d", &highscore);
    printf("\t\t\t\t\t\tHighscore: %d\n", highscore);
    fclose(file);
    tc_getch();
}

void updateHighscore(){
    int highscore;
    FILE* file = fopen("highscore.txt", "r");
    fscanf(file, " %d", &highscore);
    if (_Players[0].skor > highscore){
        highscore = _Players[0].skor;
    }
    fclose(file);
    file = fopen("highscore.txt", "w");
    fprintf(file, "%d", highscore);
    fclose(file);
}