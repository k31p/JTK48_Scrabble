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

void switchMenu(char menus[5][50], int menuPos){
    switch (tc_getch()) {
        case 'A':
            // printf("Panah atas");
            globalMenuChoice--;
            if(globalMenuChoice < 1){
                globalMenuChoice = 5;
            }
            createMenus(menus, menuPos);
            break;
        case 'B':
            // printf("Panah bawah");
            globalMenuChoice++;
            if(globalMenuChoice > 5){
                globalMenuChoice = 1;
            }
            createMenus(menus, menuPos);
            break;
        case 'C':
            // printf("Panah kanan");
            break;
        case 'D':
            // printf("Panah kiri");
            break;
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
        char input = tc_getch();
        if(input == '\033'){ // escape
            tc_getch(); // [
            switchMenu(menus, menuPos);
        } else if(input == '\r') { // enter
            selectMenu();
        }
    }
}