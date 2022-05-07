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
#include "driver.h"


int execute_driver(int driver_id, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){
    int ops = 0;
    int* ptr = &ops;
    int terminate_flag = *(data->terminate);
    while (1){
        struct operation op;
        terminate_flag = *(data->terminate);
        if(terminate_flag == 1) {
            return *ptr;
        }
        else{
            driver_receive_operation(&op, buffers, data,sems);
            if(op.id != -1){
                driver_process_operation(&op, driver_id, data, ptr,sems);
                driver_send_answer(&op, buffers, data,sems);
            }

        }
    }
}

void driver_receive_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){
    int terminate_flag = *(data->terminate);
    if(terminate_flag == 1)
        return;
    else{
        consume_begin(sems->rest_driv);
        read_rest_driver_buffer(buffers->rest_driv, data->buffers_size, op);
        if(op->id!=-1){
            consume_end(sems->rest_driv);
        }
        else{
            produce_end(sems->rest_driv);
        }
    }
}

void driver_process_operation(struct operation* op, int driver_id, struct main_data* data, int* counter, struct semaphores* sems){
    printf("O condutor recebeu o pedido!\n");
    semaphore_mutex_lock(sems->results_mutex);
    data->results[op->id].receiving_driver = driver_id;
    data->results[op->id].status = 'D';
    semaphore_mutex_unlock(sems->results_mutex);
    (*counter)++;
}

void driver_send_answer(struct operation* op, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){
    produce_begin(sems->driv_cli);
    write_driver_client_buffer(buffers->driv_cli, data->buffers_size, op);
    produce_end(sems->driv_cli);
}