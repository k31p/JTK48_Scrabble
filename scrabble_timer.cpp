// MODUL TIMER

#include "scrabble_timer.h"

bool _Stop_Thread;
int _Timer;

void initTimer(){
  _Timer = 60;
  _Stop_Thread = false;
}

void* countdown_thread(void* arg) {
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
    printf("\033[1A\r\033[K");
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
