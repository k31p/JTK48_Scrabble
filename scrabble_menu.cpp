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

void HowToPlay(){  
    tc_clear_screen();  
    printf("%s How To Play\n%s",TC_YEL,TC_NRM); 
    printf("%s1. Pemain menentukan banyak pemain, kemudian set pemain\n%s",TC_YEL,TC_NRM);  
    printf("%s2. Saat permainan dimulai, pemain pertama harus meletakkan huruf tepat di tengah papan\n%s",TC_YEL,TC_NRM);  
    printf("%s3. Pemain memasukkan kata, kemudian tentukan koordinat sesuai dengan tempat meletakkannya\n%s",TC_YEL,TC_NRM);  
    printf("%s4. Pemain akan mendapat skor sesuai dengan kata yang dimasukkan\n%s",TC_YEL,TC_NRM);  
    printf("%s5. Setelah pemain meletakkan kata atau kehabisan waktu untuk meletakkan kata , maka giliran pemain habis dan beralih ke giliran selanjutnya\n%s",TC_YEL,TC_NRM);
    printf("%s6. Permainan berlanjut sampai giliran pemain telah mencapai 25 atau huruf yang dimiliki dan yang dikantung player telah habis maka permainan dianggap selesai\n%s",TC_YEL,TC_NRM);
    printf("%s7. Peringkat pemain akan terlihat mengurut dari tertinggi ke terendah, pemain yang memiliki skor paling tinggi adalah pemenangnya ^-^\n%s",TC_YEL,TC_WHT);
}

void Credit(){
    tc_clear_screen();
    printf("%s",TC_RED);
    centerPos("Made by JTK48");
    centerPos("Member's Group");
    centerPos("1. Yobel El'Roy Doloksaribu - 231524029");
    centerPos("2. Amr Fadhilah Abiyyu Alif Basysyar - 231524002");
    centerPos("3. Micho Dhani Firmansyah - 231524013");
    printf("%s",TC_WHT);
}

void selectMenu(){
    switch(globalMenuChoice){
        case 1:
            break;
        case 2:
            break;
        case 3:
            HowToPlay();
            break;
        case 4:
            Credit();
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