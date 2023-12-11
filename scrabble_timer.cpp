// MODUL TIMER

#include "scrabble_timer.h"
#include "tercontrol.h"

bool _Stop_Thread;
int _Timer;

struct args {
    int xPos;
    int yPos;
};

void initTimer(){
  _Timer = 60;
  _Stop_Thread = false;
}

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
}

void endCountdown(){
	_Stop_Thread = true;
	sleep(1);
}
