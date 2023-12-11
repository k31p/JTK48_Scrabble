#ifndef SCRABBLE_SAVELOAD_H
#define SCRABBLE_SAVELOAD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scrabble_player.h"
#include "scrabble_board.h"
#include "scrabble_menu.h"

void loadgame(unsigned int LoadNumber);

void saveGame(unsigned int saveNumber);

void saveSlot();

void LoadMenus();

#endif