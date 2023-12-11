#ifndef SCRABBLE_GAME_H
#define SCRABBLE_GAME_H

#include "scrabble_menu.h"
#include "scrabble_player.h"

#include "tercontrol.h"

#define MAX_PLAYER_SELECTION 3

void initNewGame();
void startGame(bool loading_game);
void loadGame();

#endif