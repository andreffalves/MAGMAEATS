/*
Grupo: SO-010
Membros:
Francisco Teixeira | FC56305
Andre Alves        | FC56349
Rodrigo Antunes    | FC56321
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "process.h"

int main(int argc, char *argv[]) {
//init data structures
    struct main_data* data = create_dynamic_memory(sizeof(struct
            main_data));
    struct communication_buffers* buffers =
            create_dynamic_memory(sizeof(struct communication_buffers));
    buffers->main_rest = create_dynamic_memory(sizeof(struct
            rnd_access_buffer));
    buffers->rest_driv = create_dynamic_memory(sizeof(struct
            circular_buffer));
    buffers->driv_cli = create_dynamic_memory(sizeof(struct
            rnd_access_buffer));
//execute main code
    main_args(argc, argv, data);
    create_dynamic_memory_buffers(data);
    create_shared_memory_buffers(data, buffers);
    launch_processes(buffers, data);
    user_interaction(buffers, data);
//release memory before terminating
    destroy_dynamic_memory(data);
    destroy_dynamic_memory(buffers->main_rest);
    destroy_dynamic_memory(buffers->rest_driv);
    destroy_dynamic_memory(buffers->driv_cli);
    destroy_dynamic_memory(buffers);
}


void main_args(int argc, char* argv[], struct main_data* data){
    if(argc!=6){
        perror("Uso: magnaeats max_ops buffers_size n_restaurants n_drivers n_clients\n"
               "Exemplo: ./bin/magnaeats 10 10 1 1 1\n");
        exit(1);
    }
    int max_ops = atoi(argv[1]);			//número máximo de operações
    int buffers_size = atoi(argv[2]);		//tamanho máximo dos buffers de mem. partilhada

    int n_restaurants = atoi(argv[3]);		//número de restaurantes
    int n_drivers = atoi(argv[4]);			//número de motoristas
    int n_clients = atoi(argv[5]);
    if(max_ops==0||buffers_size==0||n_restaurants==0||n_drivers==0||n_clients==0){
        perror("Parâmetros incorretos! Exemplo de uso: ./bin/magnaeats 10 10 1 1 1");
        exit(2);
    }
    data->max_ops = max_ops;
    data->buffers_size = buffers_size;

    data->n_restaurants = n_restaurants;
    data->n_drivers = n_drivers;
    data->n_clients =n_clients;
}


void create_dynamic_memory_buffers(struct main_data* data){
    data->restaurant_pids = create_dynamic_memory(sizeof(int) * data->n_restaurants);
    data->driver_pids = create_dynamic_memory(sizeof(int) * data->n_drivers);
    data->client_pids = create_dynamic_memory(sizeof(int) * data->n_clients);

    data->restaurant_stats = malloc(sizeof(int) * data->n_restaurants);
    data->driver_stats = create_dynamic_memory(sizeof(int) * data->n_drivers);
    data->client_stats = create_dynamic_memory(sizeof(int) * data->n_clients);
}


void launch_processes(struct communication_buffers* buffers, struct main_data* data){
    int num_rest = data->n_restaurants;
    for (int i = 0; i < num_rest; ++i) {
        int pid = launch_restaurant(i,buffers,data);
        (data->restaurant_pids)[i] = pid;
    }

    int num_drivers = data->n_drivers;
    int pid;
    for (int i = 0; i < num_drivers; ++i) {
        pid = launch_driver(i,buffers,data);
        (data->driver_pids)[i] = pid;
    }

    int num_clients = data->n_clients;
    for (int i = 0; i < num_clients; ++i) {
        pid = launch_client(i,buffers,data);
        (data->client_pids)[i] = pid;
    }

}


void user_interaction(struct communication_buffers* buffers, struct main_data* data){
    char buffer[50];
    int op_counter = 0;
    printf("Ações disponíveis:\n"
           "        request client restaurant dish - criar um novo pedido\n"
           "        status id - consultar o estado de um pedido\n"
           "        stop - termina a execução do magnaeats.\n"
           "        help - imprime informação sobre as ações disponíveis.\n");
    while (1){
        printf("Introduzir ação:\n");
        scanf("%s",buffer);
        if(strcmp(buffer,"help")==0){
            printf("Ações disponíveis:\n"
                   "        request client restaurant dish - criar um novo pedido\n"
                   "        status id - consultar o estado de um pedido\n"
                   "        stop - termina a execução do magnaeats.\n"
                   "        help - imprime informação sobre as ações disponíveis.\n");
        }
        else if(strcmp(buffer,"status")==0){
            read_status(data);
        }
        else if(strcmp(buffer,"request")==0){
            create_request(&op_counter,buffers,data);
            op_counter++;
        }
        else if (strcmp(buffer,"stop")==0){
            stop_execution(data,buffers);
            return;
        }
        else{
            printf("Ação não reconhecida, insira 'help' para assistência.\n");
        }

    }
}


void create_shared_memory_buffers(struct main_data* data, struct communication_buffers* buffers){
    data->results = create_shared_memory(STR_SHM_RESULTS,sizeof(struct operation)*data->max_ops);
    data->terminate = create_shared_memory(STR_SHM_TERMINATE,sizeof(int));
    int bufs = data->buffers_size;


    buffers->main_rest->ptrs = create_shared_memory(STR_SHM_MAIN_REST_PTR,sizeof(int)*bufs);
    buffers->main_rest->buffer =create_shared_memory(STR_SHM_MAIN_REST_BUFFER,sizeof(struct operation)*bufs);

    buffers->rest_driv->ptrs = create_shared_memory(STR_SHM_REST_DRIVER_PTR,sizeof(struct pointers));
    buffers->rest_driv->buffer = create_shared_memory(STR_SHM_REST_DRIVER_BUFFER,sizeof(struct operation)*bufs);

    buffers->driv_cli->ptrs = create_shared_memory(STR_SHM_DRIVER_CLIENT_PTR,sizeof(int)*bufs);
    buffers->driv_cli->buffer = create_shared_memory(STR_SHM_DRIVER_CLIENT_BUFFER,sizeof(struct operation)*bufs);


}


void read_status(struct main_data* data){
    int temp = -1;
    scanf("%d",&temp);
    if((temp==-1)|(temp>data->max_ops)){
        printf("id de pedido fornecido é inválido!\n");
        return;
    }
    struct operation temp_op = data->results[temp];
    switch (temp_op.status) {
        case 'I':
            printf("Pedido %d com estado %c requisitado pelo cliente %d ao restaurante %d com o prato %s, ainda não foi recebido no restaurante!\n",
                   temp_op.id,temp_op.status,temp_op.requesting_client,temp_op.requested_rest,temp_op.requested_dish);
            break;
        case 'R':
            printf("Pedido %d com estado %c requisitado pelo cliente %d ao restaurante %d com o prato %s,foi recebido pelo restaurant %d ainda não foi levantado por um motorista!\n",
                   temp_op.id,temp_op.status,temp_op.requesting_client,temp_op.requested_rest,temp_op.requested_dish,temp_op.receiving_rest);
            break;
        case 'D':
            printf("Pedido %d com estado %c requisitado pelo cliente %d ao restaurante %d com o prato %s, foi levantado por o motorista %d e ainda não foi entrege ao cliente%d!\n",
                   temp_op.id,temp_op.status,temp_op.requesting_client,temp_op.requested_rest,temp_op.requested_dish,temp_op.receiving_driver,temp_op.requesting_client);
            break;
        case 'C':
            //
            printf("Pedido %d com estado %c requisitado pelo cliente %d ao restaurante %d com o prato %s, foi tratado pelo restaurante %d, encaminhado pelo motorista %d, e enviado ao cliente %d!\n",
                   temp_op.id,temp_op.status,temp_op.requesting_client,temp_op.requested_rest,temp_op.requested_dish,temp_op.receiving_rest,temp_op.receiving_driver,temp_op.receiving_client);
            break;
        default:
            printf("Pedido %d ainda não é váldio!\n",temp);
            break;

    }
}


void wait_processes(struct main_data* data){
    for (int i = 0; i < data->n_restaurants; ++i) {
        data->restaurant_stats[i] = wait_process(data->restaurant_pids[i]);
    }
    for (int i = 0; i < data->n_drivers; ++i) {
        data->driver_stats[i] = wait_process(data->driver_pids[i]);
    }
    for (int i = 0; i < data->n_clients; ++i) {
        data->client_stats[i] = wait_process(data->client_pids[i]);
    }
}


void stop_execution(struct main_data* data, struct communication_buffers* buffers){
    *(data->terminate)=1;
    wait_processes(data);
    write_statistics(data);
    destroy_memory_buffers(data,buffers);
}


void destroy_memory_buffers(struct main_data* data, struct communication_buffers* buffers){
    int bufs = data->buffers_size;
    destroy_dynamic_memory(data->restaurant_pids);
    destroy_dynamic_memory(data->driver_pids);
    destroy_dynamic_memory(data->client_pids);

    destroy_dynamic_memory(data->restaurant_stats);
    destroy_dynamic_memory(data->driver_stats);
    destroy_dynamic_memory(data->client_stats);

    int i = 0;
    while(data->results[i].requested_dish !=NULL){
        destroy_dynamic_memory(data->results[i].requested_dish);
        i++;
    }


    destroy_shared_memory(STR_SHM_RESULTS,data->results,sizeof(struct operation)*data->max_ops);
    destroy_shared_memory(STR_SHM_TERMINATE,data->terminate,sizeof(int));

    destroy_shared_memory(STR_SHM_MAIN_REST_PTR,buffers->main_rest->ptrs,sizeof(int)*bufs);
    destroy_shared_memory(STR_SHM_MAIN_REST_BUFFER,buffers->main_rest->buffer,sizeof(struct operation)*bufs);

    destroy_shared_memory(STR_SHM_REST_DRIVER_PTR,buffers->rest_driv->ptrs,sizeof(struct pointers));
    destroy_shared_memory(STR_SHM_REST_DRIVER_BUFFER,buffers->rest_driv->buffer,sizeof(struct operation)*bufs);

    destroy_shared_memory(STR_SHM_DRIVER_CLIENT_PTR,buffers->driv_cli->ptrs,sizeof(int)*bufs);
    destroy_shared_memory(STR_SHM_DRIVER_CLIENT_BUFFER,buffers->driv_cli->buffer,sizeof(struct operation)*bufs);

}


void write_statistics(struct main_data* data){
    int num_rest = data->n_restaurants;
    for (int i = 0; i < num_rest; ++i) {
        printf("Restaurante %d preparou %d pedidos\n",i,data->restaurant_stats[i]);
    }

    int num_driv = data->n_drivers;
    for (int i = 0; i < num_driv; ++i) {
        printf("Motorista %d entregou %d pedidos\n",i,data->driver_stats[i]);
    }

    int num_cli = data->n_clients;
    for (int i = 0; i < num_cli; ++i) {
        printf("Cliente %d recebeu %d pedidos\n",i,data->client_stats[i]);
    }
}


void create_request(int* op_counter, struct communication_buffers* buffers, struct main_data* data){
    int client = -1;
    int rest = -1;
    char* dish = create_dynamic_memory(sizeof(char )*100);
    scanf("%d",&client);
    scanf("%d",&rest);
    scanf("%s",dish);
    if((*op_counter)>(data->max_ops)){
        printf("O número máximo de pedidos foi alcançado!\n");
    }
    else{
        //unit by heap
        struct operation* dummy = malloc(sizeof (struct operation));
        dummy->id=*op_counter;
        dummy->requested_rest=rest;
        dummy->requesting_client=client;
        dummy->requested_dish = dish;

        dummy->status = 'I';
        write_main_rest_buffer(buffers->main_rest,data->buffers_size,dummy);
        printf("Pedido #%d foi criado!\n",dummy->id);
        data->results[dummy->id] = *dummy;
        //free(dummy->requested_dish);
        free(dummy);
    }
}
