// MODUL TIMER
// Penanggung Jawab: Amr Fadhilah Abiyyu Alif Basysyar (231524002)

#include "scrabble_timer.h"

void countdown(){
	// Mengambil waktu saat prosedur ini dimulai
	clock_t startTime = clock();
	
	char *userinput = (char*) malloc(50*sizeof(char));
	char input;
	int total_rows = 1;
	int second = 60;
	while (clock() - startTime < 60 * CLOCKS_PER_SEC){
		// Mengubah warna teks menjadi warna merah
		printf("\033[u");
		printf("\033[s");
		printf("Timer: ");
		printf("\033[31m");
		printf("%ld\n", second-(clock() - startTime)/1000);
		// Mengubah warna teks menjadi warna default
		printf("\033[0m");
		usleep(10000);
		// Menggeser kursor di terminal satu baris ke atas
		printf("\033[u");
		// Meghapus teks di terminal dari posisi kursor hingga akhir baris
		printf("\033[K");
		printf("\033[2;1H", total_rows);
		printf("Masukkan input sebelum waktu habis: \n");
		printf("\033[3;%dH", total_rows);
		if (kbhit()) {
            input = getch();
            if (input=='#'){
            	break;
			}
			userinput[total_rows-1] = input;
			if(input=='\b'){
				printf("\033[3;%dH", total_rows-1);
				printf("\033[K");
				total_rows--;
				continue;
			}
			printf("%c", input);
            total_rows++;
        }
	}
	 
	printf("\n%s", userinput);
}

int maasdin(){
	countdown();
	return 0;
}

/*int main() {
    clock_t player1Time = 60 * CLOCKS_PER_SEC; // Waktu dalam detik
    clock_t player2Time = 60 * CLOCKS_PER_SEC;
    clock_t startTime;

    while (player1Time > 0 && player2Time > 0) {
        // Tampilkan waktu pemain saat ini
        printf("Player 1 Time: %.2f seconds\n", (double)player1Time / CLOCKS_PER_SEC);
		
        // Mulai menghitung mundur waktu input pemain
        startTime = clock();

		int second = 0;
        // Tunggu input pemain selama 60 detik atau sampai ada input
        while (clock() - startTime < 60 * CLOCKS_PER_SEC) {
            printf("\033[31m");
			printf("Timer: %d\n", 60 - second++);
            sleep(1);
            printf("\033[A\033[K");
			if (kbhit()) {
                char input = getch();
                scanf("%c", &input);
            }
        }

        // Kurangi waktu pemain 1
        player1Time -= 60 * CLOCKS_PER_SEC;

        // Ganti giliran pemain jika waktu habis
        if (player1Time == 0) {
            printf("Player 1 out of time. Player 2's turn.\n");
            // Gantilah giliran pemain di sini
        }
    }

    return 0;
}
*/
