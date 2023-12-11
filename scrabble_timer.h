#ifndef SCRABBLE_TIMER_H
#define SCRABBLE_TIMER_H

#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include "tercontrol.h"

// _Stop_Thread: Digunakan untuk mengontrol apakah thread countdown harus dihentikan atau tidak.
extern bool _Stop_Thread;

// _Timer: Digunakan untuk menyimpan nilai sisa waktu timer dalam detik.
extern int _Timer;

/*  
    Deskripsi       : 
        Prosedur ini berfungsi untuk menginisialisasi timer dengan nilai awal 60 detik dan menghentikan thread countdown.

    F.S             :
        Timer diinisialisasi dan thread countdown dihentikan.

    Dibuat oleh     : Amr Fadhilah Abiyyu Alif Basysyar
*/
void initTimer();

/*  
    Deskripsi       : 
        Fungsi ini merupakan thread untuk melakukan penghitungan mundur (countdown) timer. 
        Timer akan dikurangi setiap detik, dan pesan sisa waktu akan ditampilkan di layar.

    Parameter       :
        arg -> Pointer ke argumen fungsi thread (tidak digunakan).

    F.S             :
        Jika waktu habis atau fungsi endCountdown dipanggil, thread akan dihentikan.

    Dibuat oleh     : Amr Fadhilah Abiyyu Alif Basysyar
*/
// void* countdown_thread(void* arg);

/*  
    Deskripsi       : 
        Prosedur ini berfungsi untuk memulai thread countdown timer.

    F.S             :
        Thread countdown timer dimulai.

    Dibuat oleh     : Amr Fadhilah Abiyyu Alif Basysyar
*/
void startCountdown(int xPos, int yPos);

/*  
    Deskripsi       : 
        Prosedur ini berfungsi untuk menghentikan thread countdown timer.

    F.S             :
        Thread countdown timer dihentikan.

    Dibuat oleh     : Amr Fadhilah Abiyyu Alif Basysyar
*/
void endCountdown();

#endif