#include <stdio.h>
#include "memory.h"
#include "main.h"
#include "client.h"

int execute_client(int client_id, struct communication_buffers* buffers, struct main_data* data){
    int ops = 0;
    int terminate_flag = *(data->terminate);
    while (1){
        terminate_flag = *(data->terminate);
        if(terminate_flag == 1)
            return ops;
        else{
            struct operation* op = create_dynamic_memory(sizeof (struct operation));
            client_get_operation(op, client_id, buffers, data);
            if(op->id != 1){
                client_process_operation(op, client_id, data, &ops);
            }
        }
    }
}


void client_get_operation(struct operation* op, int client_id, struct communication_buffers* buffers, struct main_data* data){
    int terminate_flag = *(data->terminate);
    if(terminate_flag == 1)
        return;
    else{
        read_driver_client_buffer(buffers->driv_cli, client_id, data->max_ops, op);
        printf("O cliente recebeu o pedido!");
    }
}

void client_process_operation(struct operation* op, int client_id, struct main_data* data, int* counter){
    op->receiving_client = client_id;
    op->status = 'C';
    (*counter)++;
    data->results[op->id] = *op;
}