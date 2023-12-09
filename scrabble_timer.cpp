// MODUL TIMER
//

#include "scrabble_timer.h"

bool stop_thread;
int timer;

void initTimer(){
    timer = 60;
    stop_thread = false;
}

void* countdown_thread(void* arg) {
  printf("Sisa waktu: %d detik\n", timer);
  printf("\033[s");
  while(timer > 0) {
  	printf("\033[u"); 
    sleep(1);
    timer--;
    printf("\033[s");
    if (stop_thread){
    	break;
	}
    printf("\033[1A\r\033[K");
    printf("Sisa waktu: %d detik\n", timer);
  }
  pthread_exit(NULL); 
}

void startCountdown(){
    pthread_t timer_thread;
    pthread_create(&timer_thread, NULL, &countdown_thread, NULL);
}
