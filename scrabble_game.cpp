#include "scrabble_game.h"
#include "scrabble_bag.h"
#include "scrabble_menu.h"
#include "scrabble_player.h"
#include "scrabble_board.h"
#include "scrabble_scoring.h"
#include "scrabble_timer.h"
#include "scrabble_utilities.h"
#include <unistd.h>

int globalChoice = 1;
bool globalToggle = true;

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
    startGame();
    // initPlayers(globalChoice + 1);
}

void startGame(){
    _Current_Player_Turn = 1;
    int round = 1;
    initBoard();
    while (round <= 25) {
        Player currentPlayer = _Players[_Current_Player_Turn - 1];
        int choice;
        char direction;
        int col, row;
        char *word = (char*) malloc(sizeof(char) * 20);
        char *letterOnBoard = (char*) malloc(sizeof(char) * 20);

        printBoard();
        initTimer();
        startCountdown();
        printf("BAG\n");
        printBag(currentPlayer.bag);
        printf("SCORE: %d\n", currentPlayer.skor);
        if(currentPlayer.is_computer){

        } else {
            printf("1. Swap\n");
            printf("2. Place Word\n");
            printf("3. Skip\n");
            printf("4. Exit\n");
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
                    } while (!isValid(currentPlayer.bag, word, _Board, row, col, direction));
                    
                    extractLetter(letterOnBoard, row, col, direction, word);
                    placeTiles(word, row, col, direction);
                    removePlayerLetter(word, currentPlayer.bag, letterOnBoard);
                    fillPlayerBag(currentPlayer.bag);
                    currentPlayer.skor += hitungSkorKata(word);
                    break;
                case 3:
                    break;
                case 4:
                    break;
            }
        }
        _Players[_Current_Player_Turn - 1] = currentPlayer;
        free(word);
        free(letterOnBoard);

        endCountdown();
        round++;
        nextTurn();
    }
}