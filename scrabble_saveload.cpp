#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scrabble_player.h"
#include "scrabble_board.h"

// typedef struct {
//    Player *players;
//    char **board;
// } SaveData;


void loadgame(unsigned int LoadNumber){
   FILE *file;
   file = fopen("savedata.dat", "rb");
   if (file == NULL){
      printf("Load gagal\n");
   }

   fread(_Players,sizeof(_Players),LoadNumber,file);
   fread(_Board, sizeof(_Board),LoadNumber + 1,file);
   printPlayers(4);
   fclose(file);
}

void saveGame(unsigned int saveNumber){
   FILE *file;
   // SaveData savedata;
   file = fopen("savedata.dat", "wb");

   initPlayers(4);
   // savedata.players = _Players;
   // savedata.board = _Board;

   fwrite(_Players, sizeof(_Players), saveNumber, file);
   fwrite(_Board, sizeof(_Board), saveNumber + 1, file);
   fclose(file);
}