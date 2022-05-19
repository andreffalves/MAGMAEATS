#include <signal.h>
#include <main.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>



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

void timerHandler(int sig){
}

void setTimer(int secs){
    struct sigaction sa;
    sa.sa_handler = timerHandler;
    sa.sa_flags = 0;
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


