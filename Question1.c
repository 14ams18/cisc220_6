#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#undef NUM_THREADS
#define NUM_THREADS 6

int prog[5] = {0, 0, 0, 0, 0};

void *new_thread (void *threadid) {
        int lane = (int)threadid -1;
        do {
                if (lane == 0) {  //draw thread
                        system("clear");
                        printf("Welcome to the CISC220 Racing Arena! \nHit Enter to move.\n");
                        for (int i=0; i < 5; i++) {
                                if (prog[i] < 40) {
                                        for (int j=0; j<prog[i]; j++){
                                                putchar('~');
                                        }
                                        printf("|->");
                                        int invprog = 40 - prog[i];
                                        for (int k=0; k<invprog; k++){
                                                putchar(' ');
                                        }
                                        printf("# Lane %d #\n", i+1);
                                }
                                else {
                                        for (int j=0; j<40; j++){
                                                putchar('~');
                                        }
                                        printf("|-># Lane %d #\n", i+1);
                                }
                        }
                        sleep(20);
                }
                else if (lane == 1) { // Player thead
                        char move = getchar();
                        if (move == '\n') {
                                prog[0] += 1;
                        }
                }
                else { //start the AI threads lane == 2,3,4,5
                        int srand = rand() % 10;//decreased to 10 instead of 100 to make game harder
                        sleep(srand);
                        prog[lane-1] += 1;
                }
        } while (prog[0] < 40 && prog[1] < 40 && prog[2] < 40 && prog[3] < 40 && prog[4] < 40);
        if (lane == 0) { //draw thread
                 system("clear");
                        printf("Welcome to the CISC220 Racing Arena! \nHit Enter to move.\n");
                        for (int i=0; i < 5; i++) {
                                if (prog[i] < 40) {
                                        for (int j=0; j<prog[i]; j++){
                                                putchar('~');
                                        }
                                        printf("|->");
                                        int invprog = 40 - prog[i];
                                        for (int k=0; k<invprog; k++){
                                                putchar(' ');
                                        }
                                        printf("# Lane %d #\n", i+1);
                                }
                                else {
                                        for (int j=0; j<40; j++){
                                                putchar('~');
                                        }
                                        printf("|-># Lane %d #\n", i+1);
                                }
                        }
                for (int i=0; i < 5; i++) {
                        if (prog[i] == 40) {
                                printf("Player %d WINS\n", i+1);
                        }
                }
        }
        pthread_exit(NULL);
}

int main(){
        pthread_t threads[NUM_THREADS];
        int status;
        long t;
        for (t=1; t < NUM_THREADS+1; t++) {
                status = pthread_create(threads + t, NULL, new_thread, (void *)t);
                if (status != 0){
                        printf("Error; return code from pthread_create() is %d\n", status);
                        exit(-1);
                }
        }
        for (t = 0; t < NUM_THREADS; t++) {
                pthread_join(threads[t], NULL);
        }
        pthread_exit(NULL);
        return 0;
}
