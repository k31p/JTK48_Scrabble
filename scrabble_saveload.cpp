#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scrabble_player.h"
#include "scrabble_board.h"

void loadgame(int LoadNumber){
   FILE *file;
   file = fopen("savedata.txt", "rb");
   if (file == NULL){
      printf("Load gagal\n");
   }

   fread(_Players,sizeof(_Players),LoadNumber,file);
   fread(board, sizeof(board),LoadNumber,file);
   fclose(file);
}

int main (){
   
   // loadgame(1);
   return 0; 
}