/*
Grupo: SO-010
Membros:
Francisco Teixeira | FC56305
Andre Alves        | FC56349
Rodrigo Antunes    | FC56321
*/
#include <signal.h>
#include <main.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "synchronization.h"


extern struct main_data* data;
extern struct communication_buffers* buffers;
extern struct semaphores* sems;



void ignoreHandler(int sig){
    //DO NOTHING
}


void stopMainHandler(int sig){
    stop_execution(data,buffers,sems);
    exit(0);
}

void ignoreSignal(){
    struct sigaction sa;
    sa.sa_handler = ignoreHandler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Ignore Signal:");
        exit(-1);
    }
}


void stopMain(){
    struct sigaction sa;
    sa.sa_handler = stopMainHandler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Stop Main:");
        exit(1);
    }
}

void timerHandler(int sig){
    struct sigaction sa;
    sa.sa_handler = timerHandler;
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("Alarm Signal:");
        exit(-1);
    }
    semaphore_mutex_lock(sems->results_mutex);
    for (int i = 0; i < data->max_ops; ++i) {
        char status = data->results[i].status;
        if(status=='C'){
            printf("request:%d status:%c start: %ld restaurant:%d rest_time:%ld\n"
                   "driver:%d driver_time:%ld client:%d client_end_time:%ld \n"
                   ,i,status,
                   data->results[i].start_time.tv_sec,
                   data->results[i].receiving_rest, data->results[i].rest_time.tv_sec,
                   data->results[i].receiving_driver,data->results[i].driver_time.tv_sec,
                   data->results[i].receiving_client, data->results[i].client_end_time.tv_sec );
        }
        else if(status=='I' || status=='R' || status =='D' ){
            printf("request:%d status:%c\n",i,status);
        }
    }
    semaphore_mutex_unlock(sems->results_mutex);
}

void setTimer(int secs){
    struct sigaction sa;
    sa.sa_handler = timerHandler;
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("Alarm Signal:");
        exit(-1);
    }
    struct itimerval val;
    val.it_interval.tv_sec = secs;
    val.it_interval.tv_usec = 0;
    val.it_value.tv_sec = secs;
    val.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &val, 0);
}


