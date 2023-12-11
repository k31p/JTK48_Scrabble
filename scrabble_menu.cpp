#include "scrabble_menu.h"
#include "scrabble_game.h"
#include "scrabble_saveload.h"

int _Y_Pos = 1;
int globalMenuChoice = 1;

void centerPos(const char *text){
    int rows, cols, midCol;
    int xPos;
    tc_get_cols_rows(&cols, &rows);

    midCol = cols / 2;

    xPos = midCol - (strlen(text) / 2);
    tc_set_cursor(xPos, _Y_Pos);
    puts(text);
    tc_set_cursor(1, ++_Y_Pos);
}

void createMenus(char menus[5][50], int startPos){
    tc_set_cursor(1, startPos);
    tc_clear_from_cursor_to_bottom();
    _Y_Pos = startPos;

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

void HowToPlay(){  
    tc_clear_screen();  
    printf("How To Play\n"); 
    printf("1. Pemain menentukan banyak pemain, kemudian set pemain\n");  
    printf("2. Saat permainan dimulai, pemain pertama harus meletakkan huruf tepat di tengah papan\n");  
    printf("3. Pemain memasukkan kata, kemudian tentukan koordinat sesuai dengan tempat meletakkannya\n");  
    printf("4. Pemain akan mendapat skor sesuai dengan kata yang dimasukkan\n");  
    printf("5. Setelah pemain meletakkan kata atau kehabisan waktu untuk meletakkan kata , maka giliran pemain habis dan beralih ke giliran selanjutnya\n");
    printf("6. Permainan berlanjut sampai giliran pemain telah mencapai 25 atau huruf yang dimiliki dan yang dikantung player telah habis maka permainan dianggap selesai\n");
    printf("7. Peringkat pemain akan terlihat mengurut dari tertinggi ke terendah, pemain yang memiliki skor paling tinggi adalah pemenangnya ^-^\n");
}

void Credit(){
    tc_clear_screen();
    //printf("%s", TC_B_MAG);
    centerPos("Made by JTK48");
    centerPos("Member's Group");
    centerPos("1. Yobel El'Roy Doloksaribu - 231524029");
    centerPos("2. Amr Fadhilah Abiyyu Alif Basysyar - 231524002");
    centerPos("3. Micho Dhani Firmansyah - 231524013");
    //printf("\033[0m");
}

void selectMenu(){
    switch(globalMenuChoice){
        case 1:
            initNewGame();
            break;
        case 2:
            LoadMenus();
            startGame(1);
            break;
        case 3:
            HowToPlay();
            tc_getch();
            break;
        case 4:
            Credit();
            tc_getch();
            break;
        case 5:
            tc_clear_screen();
            printf("Selamat tinggal...");
            sleep(2);
            exit(0);
    }
}

void switchMenu(char menus[5][50], int menuPos, bool &toggle){
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
    } else if(input == 'a' || input == 'A'){
        globalMenuChoice--;
        if(globalMenuChoice < 1){
            globalMenuChoice = 5;
        }
        createMenus(menus, menuPos);
    } else if(input == 'd' || input == 'D'){
        globalMenuChoice++;
        if(globalMenuChoice > 5){
            globalMenuChoice = 1;
        }
        createMenus(menus, menuPos);
    } else if(input == '\n' || input == '\r'){
        toggle = false;
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
    menuPos = _Y_Pos;
    createMenus(menus, menuPos);

    tc_echo_off();
    bool toggle = true;
    while(toggle){
        switchMenu(menus, menuPos, toggle);
    }

    selectMenu();
}