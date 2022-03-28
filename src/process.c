#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "client.h"
#include "driver.h"
#include "restaurant.h"

int launch_restaurant(int restaurant_id, struct communication_buffers* buffers, struct main_data* data){
    int pid = fork();
    if(pid<0){
        perror("launch_restaurant");
        exit(1);
    }
    else if(pid==0){
        int ret = execute_restaurant(restaurant_id, buffers, data);
        exit(ret);
    }
    return pid;
}

int launch_driver(int restaurant_id, struct communication_buffers* buffers, struct main_data* data){
    int pid = fork();
    if(pid<0){
        perror("launch_restaurant");
        exit(1);
    }
    else if(pid==0){
        int ret = execute_driver(restaurant_id, buffers, data);
        exit(ret);
    }
    return pid;
}

int launch_client(int restaurant_id, struct communication_buffers* buffers, struct main_data* data){
    int pid = fork();
    if(pid<0){
        perror("launch_restaurant");
        exit(1);
    }
    else if(pid==0){
        int ret = execute_client(restaurant_id, buffers, data);
        exit(ret);
    }
    return pid;
}

int wait_process(int process_id){
    int stat, ret;
    //dava-me erro por isso coloquei 0 nas options
    waitpid(process_id,&stat,0);
    if(WIFEXITED(stat)){
        ret = WEXITSTATUS(stat);
    }
    else{
        ret = -1;
    }
    return ret;
}