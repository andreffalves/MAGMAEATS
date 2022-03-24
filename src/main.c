#include <stdlib.h>
#include <stdio.h>
void main_args(int argc, char* argv[], struct main_data* data){
    if(argc!=6){
        perror("Numero incorreto");
        exit(1);
    }
    int max_ops = atoi(argv[1]);			//número máximo de operações
    int buffers_size = atoi(argv[2]);		//tamanho máximo dos buffers de mem. partilhada

    int n_restaurants = atoi(argv[3]);		//número de restaurantes
    int n_drivers = atoi(argv[4]);			//número de motoristas
    int n_clients = atoi(argv[5]);
    if(max_ops==0||buffers_size==0||n_restaurants==0||n_drivers==0||n_clients==0){
        perror("input incorreto");
    }
    data->max_ops = max_ops;
    data->buffers_size = buffers_size;

    data->n_restaurants = n_restaurants;
    data->n_drivers = n_drivers;
    data->n_clients =n_clients;

}


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