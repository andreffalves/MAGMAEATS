#include <stdio.h>
#include <string.h>
#include "main.h"
#include "memory.h"
#include "restaurant.h"
/* Função principal de um Restaurante. Deve executar um ciclo infinito onde em
* cada iteração lê uma operação da main e se e data->terminate ainda for igual a 0, processa-a e
* escreve-a para os motoristas. Operações com id igual a -1 são ignoradas
* (op inválida) e se data->terminate for igual a 1 é porque foi dada ordem
* de terminação do programa, portanto deve-se fazer return do número de
* operações processadas. Para efetuar estes passos, pode usar os outros
* métodos auxiliares definidos em restaurant.h.
*/


int execute_restaurant(int rest_id, struct communication_buffers* buffers, struct main_data* data){
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
            restaurant_receive_operation(&op, rest_id, buffers, data);

            if((op.id) != (-1)){
                restaurant_process_operation(&op, rest_id, data, ptr);
                restaurant_forward_operation(&op, buffers, data);
            }
        }  
    }
}

void restaurant_receive_operation(struct operation* op, int rest_id, struct communication_buffers* buffers, struct main_data* data){
    int terminate_flag = *(data->terminate);
        if(terminate_flag == 1){
            return;
        } else {
           read_main_rest_buffer(buffers->main_rest, rest_id, data->max_ops, op);

        }
}

void restaurant_process_operation(struct operation* op, int rest_id, struct main_data* data, int* counter){
    printf("O restaurante recebeu o pedido!\n");
    op->receiving_rest = rest_id;
    op->status = 'R';
    (*counter)++;
    data->results[op->id] = *op;
}

void restaurant_forward_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data){
    write_rest_driver_buffer(buffers->rest_driv, data->buffers_size, op);
}