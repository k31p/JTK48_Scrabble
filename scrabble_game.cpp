#include "scrabble_game.h"

void printPlayerChoices(char option[3][20], int choice){
    for(int i = 0; i < 3; i++){
        char *text;
        text = (char*) malloc(sizeof(char) * 20);
        text = option[i];

        if(choice == i + 1){
            sprintf(text, "%s %s", "-->", text);
        }
        
        centerPos(text);
        free(text);
    }
}

void newGame(){
    char option[3][20] = {
        "2 Player",
        "3 Player",
        "4 Player"
    };
    tc_clear_screen();
    centerPos("Pilih jumlah player");
    

    int pilihan = 2;
    bool isSelected = false;
    while(!isSelected){
        printPlayerChoices(option, pilihan - 1);
        tc_echo_off();
        tc_getch();
    }


    tc_clear_screen();
    initPlayers(pilihan);
}