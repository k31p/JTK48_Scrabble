#include "scrabble_saveload.h"

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

   fread(_Players,sizeof(_Players),(LoadNumber*5)-4,file);
   fread(_Board, sizeof(_Board),(LoadNumber*5)-3,file);
   fread(&_Current_Player_Turn,sizeof(_Current_Player_Turn),(LoadNumber*5)-2,file);
   fread(&_Max_Time, sizeof(_Max_Time), (LoadNumber*5)-1,file);
   fread(&_Difficulty, sizeof(_Difficulty), LoadNumber*5,file);
   fclose(file);
}

void saveGame(unsigned int saveNumber){
   FILE *file;
   // SaveData savedata;
   file = fopen("savedata.dat", "wb");

   // savedata.players = _Players;
   // savedata.board = _Board;

   fwrite(_Players,sizeof(_Players),(saveNumber*5)-4,file);
   fwrite(_Board, sizeof(_Board),(saveNumber*5)-3,file);
   fwrite(&_Current_Player_Turn,sizeof(_Current_Player_Turn),(saveNumber*5)-2,file);
   fwrite(&_Max_Time, sizeof(_Max_Time), (saveNumber*5)-1,file);
   fwrite(&_Difficulty, sizeof(_Difficulty), saveNumber*5,file);
   fclose(file);
}

void saveSlot(){
   char savegame;
   tc_clear_screen();
   centerPos("=======================\n");
   centerPos("Save Slot\n");
   centerPos("1. Slot 1 \n");
   centerPos("2. Slot 2 \n");
   centerPos("3. Slot 3 \n");
   centerPos("4. Slot 4 \n");
   centerPos("5. Slot 5 \n");
   centerPos("=======================\n");
   scanf(" %c", &savegame);
   switch(savegame){
      case '1':
         saveGame(1);
      case '2':
         saveGame(2);
      case '3':
         saveGame(3);
      case '4':
         saveGame(4);
      case '5':
         saveGame(5);
   };
}

void LoadMenus(){
   char loadgames;
   tc_clear_screen();
   centerPos("=======================\n");
   centerPos("Saved Game\n");
   centerPos("1. Game 1 \n");
   centerPos("2. Game 2 \n");
   centerPos("3. Game 3 \n");
   centerPos("4. Game 4 \n");
   centerPos("5. Game 5 \n");
   centerPos("=======================\n");
   scanf(" %c",&loadgames);
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
