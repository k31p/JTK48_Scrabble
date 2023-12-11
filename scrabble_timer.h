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

// _Max_Time: Digunakan untuk menentukan lama dari waktu timer.
extern int _Max_Time;

/*  
    Deskripsi       : Inisialisasi timer dengan nilai awal dan stop flag.

    F.S             : Timer diatur ke nilai maksimum, dan stop flag diatur ke false.

    Dibuat oleh     : Amr Fadhilah AAB
*/
void initTimer();

/*  
    Deskripsi       : Fungsi thread countdown untuk melakukan penghitungan mundur.

    Parameter       :
        1. arg         -> void* (tidak digunakan dalam implementasi ini)

    F.S             : Timer berkurang setiap detik, dan nilai sisa waktu ditampilkan di konsol.

    Dibuat oleh     : Amr Fadhilah AAB
*/
void* countdown_thread(void* arg);

/*  
    Deskripsi       : Memulai thread countdown.

    F.S             : Thread countdown dimulai.

    Dibuat oleh     : Amr Fadhilah AAB
*/
void startCountdown();

/*  
    Deskripsi       : Menghentikan thread countdown.

    F.S             : Stop flag diatur ke true untuk menghentikan thread countdown.

    Dibuat oleh     : Amr Fadhilah AAB
*/
void endCountdown();

/*  
    Deskripsi       : Meminta pengguna memilih mode waktu countdown.

    F.S             : Nilai _Max_Time diatur sesuai pilihan pengguna.

    Dibuat oleh     : Amr Fadhilah AAB
*/
void chooseTime();

#endif