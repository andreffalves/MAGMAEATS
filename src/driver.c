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

int execute_driver(int driver_id, struct communication_buffers* buffers, struct main_data* data){
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
            driver_receive_operation(&op, buffers, data);
            if(op.id != -1){
                driver_process_operation(&op, driver_id, data, ptr);
                driver_send_answer(&op, buffers, data);
            }

        }
    }
}

void driver_receive_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data){
    int terminate_flag = *(data->terminate);
    if(terminate_flag == 1)
        return;
    else{
        read_rest_driver_buffer(buffers->rest_driv, data->buffers_size, op);

    }
}

void driver_process_operation(struct operation* op, int driver_id, struct main_data* data, int* counter){
    printf("O condutor recebeu o pedido!\n");
    op->receiving_driver = driver_id;
    op->status = 'D';
    (*counter)++;
    data->results[op->id] = *op;
}

void driver_send_answer(struct operation* op, struct communication_buffers* buffers, struct main_data* data){
    write_driver_client_buffer(buffers->driv_cli, data->buffers_size, op);
}