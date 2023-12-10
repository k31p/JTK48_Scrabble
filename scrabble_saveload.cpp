#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scrabble_player.h"
#include "scrabble_board.h"
#include "scrabble_menu.h"

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

   fread(_Players,sizeof(_Players),(LoadNumber*3)-2,file);
   fread(_Board, sizeof(_Board),(LoadNumber*3)-1,file);
   fread(&_Current_Player_Turn,sizeof(_Current_Player_Turn),LoadNumber*3,file);
   printPlayers(4);
   printBoard();
   fclose(file);
}

void saveGame(unsigned int saveNumber){
   FILE *file;
   // SaveData savedata;
   file = fopen("savedata.dat", "wb");

   initPlayers(4);
   // savedata.players = _Players;
   // savedata.board = _Board;

   fwrite(_Players,sizeof(_Players),(saveNumber*3)-2,file);
   fwrite(_Board, sizeof(_Board),(saveNumber*3)-1,file);
   fwrite(&_Current_Player_Turn,sizeof(_Current_Player_Turn),saveNumber*3,file);
   fclose(file);
}

void LoadMenu(){
   char loadgames;
   printf("=======================\n");
   printf("      Load Game\n");
   printf("      1. Game 1 \n");
   printf("      2. Game 2 \n");
   printf("      3. Game 3 \n");
   printf("      4. Game 4 \n");
   printf("      5. Game 5 \n");
   printf("=======================\n");
   scanf("%c",&loadgames);
   switch(loadgames){
      case '1':
         loadgame(1);
      case '2':
         loadgame(2);
      case '3':
         loadgame(3);
      case '4':
         loadgame(4);
      case '5':
         loadgame(5);
   };
}

// int main (){
//    LoadMenu();
//    return 0; 
// }
