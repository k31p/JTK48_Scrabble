#include "scrabble_game.h"
#include "scrabble_bag.h"
#include "scrabble_menu.h"
#include "scrabble_player.h"
#include "scrabble_board.h"
#include "scrabble_scoring.h"
#include "scrabble_timer.h"
#include "scrabble_utilities.h"
#include "scrabble_computer.h"
#include "tercontrol.h"
#include "scrabble_saveload.h"
#include <unistd.h>

int globalChoice = 1;
bool globalToggle = true;
int _Round;

void printPlayerChoices(char option[3][20]){
    _Y_Pos = 2;
    for(int i = 0; i < 3; i++){
        char *text;
        text = (char*) malloc(sizeof(char) * 20);
        strcpy(text, option[i]);

        if(globalChoice == i + 1){
            sprintf(text, "%s %s", "-->", option[i]);
        }
        
        centerPos(text);
        free(text);
    }
}

void changeSelection(){
    char input = tc_getch();
    if(input == 'w' || input == 'W'){
        globalChoice--;
        if(globalChoice < 1){
            globalChoice = MAX_PLAYER_SELECTION;
        }
    } else if(input == 's' || input == 'S'){
        globalChoice++;
        if(globalChoice > MAX_PLAYER_SELECTION){
            globalChoice = 1;
        }
    } else if(input == 'a' || input == 'A'){
        globalChoice--;
        if(globalChoice < 1){
            globalChoice = MAX_PLAYER_SELECTION;
        }
    } else if(input == 'd' || input == 'D'){
        globalChoice++;
        if(globalChoice > MAX_PLAYER_SELECTION){
            globalChoice = 1;
        }
    } else if(input == '\n' || input == '\r'){
        globalToggle = false;
    }
}

void initNewGame(){
    char option[3][20] = {
        "2 Player",
        "3 Player",
        "4 Player"
    };
    tc_clear_screen();
    _Y_Pos = 1;
    centerPos("Pilih jumlah player");

    while(globalToggle){
        tc_set_cursor(1, 2);
        tc_clear_from_cursor_to_bottom();
        printPlayerChoices(option);
        changeSelection();
    }

    tc_echo_on();
    initPlayers(globalChoice + 1);
    startGame(0);
}

void startGame(bool loading_game){
    char direction = 'H';
    int col = 7, row = 7;
    char *word = (char*) malloc(sizeof(char) * 20);
    if (!loading_game){
        _Difficulty = chooseComputerDifficulty();
        chooseTime();
        _Current_Player_Turn = 1;
        _Round = 1;
        word[0] = '\0';
        word[0] = _Players[_Current_Player_Turn - 1].bag[0];
        tc_clear_screen();
        initBoard();
    }
    while (_Round <= 25) {
        Player currentPlayer = _Players[_Current_Player_Turn - 1];
        //int termRows, termCols;
        int choice;
        char *letterOnBoard = (char*) malloc(sizeof(char) * 20);

        //tc_get_cols_rows(&termCols, &termRows);

        printBoard();

        initTimer();
        startCountdown();
        sleep(1);
        //tc_set_cursor(1, 2);
        printf("Round: %d\n", _Round);
        printf("%s's Turn\n", currentPlayer.namaPlayer);
        printf("Available Letters: \n");
        printBag(currentPlayer.bag);
        printf("Score: %d\n", currentPlayer.skor);
        if(currentPlayer.is_computer){
            if (_Round != 1){
                choosePosition(word, row, col, direction, &row, &col, &direction);
            }
			goThinkComputer(currentPlayer.bag, word, &row, &col, direction, _Difficulty);
            if (_Round == 1){
                col = 7;
            }
			if (isValid(currentPlayer.bag, word, _Board, row, col, direction)){
				extractLetter(letterOnBoard, row, col, direction, word);
				placeTiles(word, row, col, direction);
				removePlayerLetter(word, currentPlayer.bag, letterOnBoard);
				fillPlayerBag(currentPlayer.bag);
				currentPlayer.skor += hitungSkorKata(word);
			} else {
				swapLetter_Com(currentPlayer.bag);
			}
        } else {
            printf("1. Swap\n");
            printf("2. Place Word\n");
            printf("3. Skip\n");
            printf("4. Exit\n");
            printf("Pilih: ");
            scanf("%d", &choice);
            switch(choice){
                case 1:
                    tc_clear_screen();
                    printBoard();
                    printBag(currentPlayer.bag);
                    swapLetter(currentPlayer.bag);
                    break;
                case 2:
                    do {
                        tc_clear_screen();
                        printBoard();
                        printBag(currentPlayer.bag);
                        printf("SCORE: %d\n", currentPlayer.skor);
                        printf("\n");
                        getInput(word, &row, &col, &direction);
                        invalidMessage(currentPlayer.bag, word, _Board, row, col, direction);
                    } while (!isValid(currentPlayer.bag, word, _Board, row, col, direction) && _Timer > 0);
                    if (_Timer > 0){
                        extractLetter(letterOnBoard, row, col, direction, word);
                        placeTiles(word, row, col, direction);
                        removePlayerLetter(word, currentPlayer.bag, letterOnBoard);
                        fillPlayerBag(currentPlayer.bag);
                        currentPlayer.skor += hitungSkorKata(word);
                    }
                    break;
                case 3:
                    break;
                case 4:
                    endCountdown();
                    tc_clear_screen();
                    saveSlot();
                    return;
            }
        }
        _Players[_Current_Player_Turn - 1] = currentPlayer;
        free(letterOnBoard);

        endCountdown();
        _Round++;
        nextTurn();
    }
    sortingScore();
    showWinner();
    updateHighscore();
    showHighscore();
}