#ifndef TIMER_H
#define TIMER_H

#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

extern bool _Stop_Thread;
extern int _Timer;
void initTimer();
void* countdown_thread(void* arg);
void startCountdown();
void endCountdown();

#endif
