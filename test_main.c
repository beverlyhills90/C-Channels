#include "channels.h"
#include "mpsc/cmpsc.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int thread_id;
    t_sender *sender;
    int rand_num;
} WorkerArgs;


void *worker(void *arg){
    WorkerArgs *worker = arg; 
    srand(time(NULL));
    usleep(worker->rand_num); 
    send_data(worker->sender, (void *)&worker->thread_id);
    return (NULL);
}


int main(void) {
    t_mpscRes *test;
    t_sender *sender_org;
    t_reciver *reciver;
    t_sender *tmp;

    test = MPSCNew(5);
    sender_org = test->sender;
    reciver = test->reciver;
    pthread_t threads[5];

    for (int i = 0; i < 5; i++){
        WorkerArgs* args = malloc(sizeof(WorkerArgs));
        int random_num = rand() % (100 - i + i) + i;
        printf("Random number: %d\n", random_num);
        tmp = clone_sender(sender_org);
        args->sender = tmp;
        args->thread_id = i;
        args->rand_num = random_num;
        pthread_create(&threads[i],NULL, worker,(void *)args);
    }

    while (1) {
        int *rcived = reciv(reciver);
        if (rcived == NULL){
            continue;
        }
        printf("HI from : %i \n",*rcived);
    }
} 