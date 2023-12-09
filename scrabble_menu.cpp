#include "scrabble_menu.h"
#include "tercontrol/tercontrol.h"
#include <cstdio>
#include <cstdlib>

int globalYPos = 1;
int globalMenuChoice = 1;

void centerPos(const char *text){
    int rows, cols, midCol;
    int xPos;
    tc_get_cols_rows(&cols, &rows);

    midCol = cols / 2;

    xPos = midCol - (strlen(text) / 2);
    tc_set_cursor(xPos, globalYPos);
    puts(text);
    tc_set_cursor(1, ++globalYPos);
}

void createMenus(char menus[5][50], int startPos){
    tc_set_cursor(1, startPos);
    tc_clear_from_cursor_to_bottom();
    globalYPos = startPos;

    for(int i = 0; i < 5; i++){
        char *text;
        if(i +1 == globalMenuChoice){
            text = (char*) malloc(sizeof(char) * 50);
            sprintf(text, "--> %s", menus[i]);
            centerPos(text);
            free(text);
        } else {
            centerPos(menus[i]);
        }
    }
}

void selectMenu(){
    switch(globalMenuChoice){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            tc_clear_screen();
            printf("Selamat tinggal...");
            exit(0);
            break;
    }
}

void switchMenu(char menus[5][50], int menuPos){
    char input = tc_getch();
    if(input == 'w' || input == 'W'){
        globalMenuChoice--;
        if(globalMenuChoice < 1){
            globalMenuChoice = 5;
        }
        createMenus(menus, menuPos);
    } else if(input == 's' || input == 'S'){
        globalMenuChoice++;
        if(globalMenuChoice > 5){
            globalMenuChoice = 1;
        }
        createMenus(menus, menuPos);
    } else if(input == '\n' || input == '\r'){
        selectMenu();
    }
}

void displayMainMenu() {
    char menus[5][50] = {
        "New Game",
        "Load Game",
        "How To Play",
        "Credits",
        "Quit Game"
    };
    int menuPos;

    tc_clear_screen();
    centerPos("==============================");
    centerPos("SCRABBLE BY JTK48");
    centerPos("==============================");
    menuPos = globalYPos;
    createMenus(menus, menuPos);

    tc_echo_off();
    for(;;){
        switchMenu(menus, menuPos);
    }
}