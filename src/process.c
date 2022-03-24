#include <stdio.h>
#include <stdlib.h>
int launch_restaurant(int restaurant_id, struct communication_buffers* buffers, struct main_data* data){
    int pid = fork();
    if(pid<0){
        perror("launch_restaurant");
        exit(1)
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
        exit(1)
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
        exit(1)
    }
    else if(pid==0){
        int ret = execute_client(restaurant_id, buffers, data);
        exit(ret);
    }
    return pid;
}