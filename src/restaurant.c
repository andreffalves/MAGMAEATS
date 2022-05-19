/*
Grupo: SO-010
Membros:
Francisco Teixeira | FC56305
Andre Alves        | FC56349
Rodrigo Antunes    | FC56321
*/
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "memory.h"
#include "restaurant.h"
#include "metime.h"


#include <semaphore.h>


int execute_restaurant(int rest_id, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){
    int ops = 0;
    int* ptr = &ops;
    int terminate_flag = *(data->terminate);
    while (1){
        terminate_flag = *(data->terminate);
        if(terminate_flag == 1) {
            return *ptr;
        }
        else {
            struct operation op;
            restaurant_receive_operation(&op, rest_id, buffers, data,sems);

            if((op.id) != (-1)){
                restaurant_process_operation(&op, rest_id, data, ptr,sems);
                restaurant_forward_operation(&op, buffers, data,sems);
            }
        }  
    }
}

void restaurant_receive_operation(struct operation* op, int rest_id, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){
    int terminate_flag = *(data->terminate);
        if(terminate_flag == 1){
            return;
        } else{
            consume_begin(sems->main_rest);
            read_main_rest_buffer(buffers->main_rest, rest_id, data->max_ops, op);
            if((op->id)!=-1) {
                consume_end(sems->main_rest);
                op->rest_time=getCurrentTime();
            }
            else{
                produce_end(sems->main_rest);
                /*codigo equivalente
                sem_post(sems->main_rest->mutex);
                sem_post(sems->main_rest->full);
                 */
            }

        }
}

void restaurant_process_operation(struct operation* op, int rest_id, struct main_data* data, int* counter, struct semaphores* sems){
    printf("O restaurante recebeu o pedido!\n");
    semaphore_mutex_lock(sems->results_mutex);
    data->results[op->id].receiving_rest = rest_id;
    data->results[op->id].status = 'R';
    semaphore_mutex_unlock(sems->results_mutex);
    (*counter)++;
}

void restaurant_forward_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){
    produce_begin(sems->rest_driv);
    write_rest_driver_buffer(buffers->rest_driv, data->buffers_size, op);
    produce_end(sems->rest_driv);
}