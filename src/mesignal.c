#include <signal.h>
#include <main.h>
#include <stdio.h>
#include <stdlib.h>

extern struct main_data* data;
extern struct communication_buffers* buffers;
extern struct semaphores* sems;

void ignoreHandler(int sig){
    //DO NOTHING
}


void stopMainHandler(int sig){
    stop_execution(data,buffers,sems);
}

void ignoreSignal(){
    struct sigaction sa;
    sa.sa_handler = ignoreHandler;
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Ignore Signal:");
        exit(-1);
    }
}


void stopMain(){
    struct sigaction sa;
    sa.sa_handler = stopMainHandler;
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Stop Main:");
        exit(-1);
    }
}