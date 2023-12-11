// MODUL TIMER

#include "scrabble_timer.h"
#include "scrabble_menu.h"
#include "tercontrol.h"

bool _Stop_Thread;
int _Timer;
int _Max_Time;

struct args {
    int xPos;
    int yPos;
};

void initTimer(){
  _Timer = _Max_Time;
  _Stop_Thread = false;
}

/*
void* countdown_thread(void *param) {
  int col, row;
  tc_set_cursor(((struct args*) param)->xPos, ((struct args*) param)->yPos);
  printf("xxSisa waktu: %d detik\n", _Timer);
  while(_Timer > 0) {
    tc_set_cursor(10, 10);
    sleep(1);
    _Timer--;
    if (_Stop_Thread){
    	break;
	  }
    
    tc_get_cols_rows(&col, &row);
    tc_clear_partial(((struct args*) param)->xPos, ((struct args*) param)->yPos, (col / 2) - 5, ((struct args*) param)->yPos);
    tc_set_cursor(((struct args*) param)->xPos, ((struct args*) param)->yPos);
    printf("Sisa waktu: %d detik\n", _Timer);
  }
  pthread_exit(NULL); 
}

void startCountdown(int xPos, int yPos){
  struct args *Param = (struct args*) malloc(sizeof(struct args));
  Param->xPos = xPos;
  Param->yPos = yPos;
  pthread_t timer_thread;
  pthread_create(&timer_thread, NULL, countdown_thread, (void *)Param);
}*/

void* countdown_thread(void* arg) {
  int col, row;
  tc_get_cols_rows(&col, &row);
  printf("Sisa waktu: %d detik\n", _Timer);
  printf("\033[s");
  while(_Timer > 0) {
  	printf("\033[u"); 
    sleep(1);
    _Timer--;
    printf("\033[s");
    if (_Stop_Thread){
    	break;
	}
    printf("\033[%d;%dH", row-1, 70);
    printf("Sisa waktu: %d detik\n", _Timer);
  }
  pthread_exit(NULL); 
}

void startCountdown(){
    pthread_t timer_thread;
    pthread_create(&timer_thread, NULL, &countdown_thread, NULL);
}

void endCountdown(){
	_Stop_Thread = true;
	sleep(1);
}

void chooseTime(){
  int time_mode;
  centerPos("Pilih mode waktu:\n");
  centerPos("1. 60 detik\n");
  centerPos("2. 90 detik\n");
  centerPos("3. 120 detik\n");
  scanf(" %c", &time_mode);
  if (time_mode <= 3 && time_mode >= 1){
    _Max_Time = 30 + 30*time_mode;
  } else {
    _Max_Time = 60;
  }

}
