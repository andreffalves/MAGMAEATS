/*
Grupo: SO-010
Membros:
Francisco Teixeira | FC56305
Andre Alves        | FC56349
Rodrigo Antunes    | FC56321
*/
#include <stdio.h>
#include <string.h>
#include "memory.h"
#include "main.h"
#include "client.h"

int execute_client(int client_id, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){
    int ops = 0;
    int* ptr = &ops;
    int terminate_flag = *(data->terminate);
    while (1){
        terminate_flag = *(data->terminate);
        if(terminate_flag == 1) {
            return *ptr;
        }
        else{
            struct operation op;
            client_get_operation(&op, client_id, buffers, data,sems);
            if(op.id != -1){
                client_process_operation(&op, client_id, data, ptr,sems);
            }
        }
    }
}


void client_get_operation(struct operation* op, int client_id, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){
    int terminate_flag = *(data->terminate);
    if(terminate_flag == 1)
        return;
    else{
        consume_begin(sems->driv_cli);
        read_driver_client_buffer(buffers->driv_cli, client_id, data->buffers_size, op);
        if(op->id!=-1){
            consume_end(sems->driv_cli);
        }
        else{
            produce_end(sems->driv_cli);
        }

    }
}

void client_process_operation(struct operation* op, int client_id, struct main_data* data, int* counter, struct semaphores* sems){
    printf("O cliente recebeu o pedido!\n");
    semaphore_mutex_lock(sems->results_mutex);
    data->results[op->id].receiving_client = client_id;
    data->results[op->id].status = 'C';
    semaphore_mutex_unlock(sems->results_mutex);
    (*counter)++;
}