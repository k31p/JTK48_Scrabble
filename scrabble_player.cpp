#include "scrabble_player.h" 
#include <cstdio>

void initPlayers(Player *players, unsigned int numPlayers){
    _Total_Player = numPlayers;
    int computerCount = 0;
    for(int i = 0; i < numPlayers; i++){
        char pilihan;
        printf("PLAYER %d\n", i + 1);
        printf("Apakah player adalah komputer (y/n)? ");
        scanf(" %c", &pilihan); fflush(stdin);

        players[i].skor = 0;
        if(pilihan == 'y' || pilihan == 'Y'){
            players[i].is_computer = true;
            computerCount++;
        } else if(pilihan == 'n' || pilihan == 'N'){
            players[i].is_computer = false;
        } else {
            fprintf(stderr, "Input invalid!");
            return;
        }

        if(players[i].is_computer){
            snprintf(players[i].namaPlayer, MAX_PLAYERNAME_LENGTH, "Computer %d", computerCount);
            printf("\n");
        } else {
            printf("Masukkan nama player: ");
            getchar();
            fgets(players[i].namaPlayer, MAX_PLAYERNAME_LENGTH, stdin); fflush(stdin);
            removeNewlines(players[i].namaPlayer);
            printf("\n");
        }

    }
}

void printPlayers(Player *players, unsigned int numPlayers){
    for(int i = 0; i < numPlayers; i++){
        printf("PLAYER %d\n", i + 1);
        printf("Nama    : %s\n", players[i].namaPlayer);
        printf("Skor    : %d\n", players[i].skor);
        printf("\n");
    }
}

void nextTurn(){
    _Current_Turn = _Current_Turn + 1;
    if(_Current_Turn > _Total_Player){
        _Current_Turn = 1;
    }
}

void setTurn(int nPlayer){
    if(nPlayer > 0 && nPlayer <= _Total_Player){
        _Current_Turn = nPlayer;
    }
}