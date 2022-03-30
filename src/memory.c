#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "memory.h"
#include "main.h"


void* create_dynamic_memory(int size){
    void *ptr = malloc(size);
    memset(ptr,0, size);
    return ptr;
}


void destroy_dynamic_memory(void *ptr){
    free(ptr);
}


void* create_shared_memory(char* name, int size){
    int *ptr;
    int id = getuid();
    char* zone = calloc(strlen(name)+1+10,1);
    int result = sprintf(zone,"/%s-%d",name,id);
    if(result==-1){
        perror(name);
        exit(1);
    }
    int fd = shm_open(zone, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1){
        perror(name);
        exit(2);
    }
    result = ftruncate(fd,size);
    if(result==-1){
        perror(name);
        exit(3);
    }
    ptr = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr==MAP_FAILED){
        perror("mmap");
        exit(4);
    }
    free(zone);
    return ptr;
}


void destroy_shared_memory(char* name, void* ptr, int size){
    int id = getuid();
    int ret;
    char* zone = calloc(strlen(name)+1+10,1);
    int result = sprintf(zone,"/%s-%d",name,id);
    if(result==-1){
        perror(name);
        exit(6);
    }
    ret = munmap(ptr, size);
    if (ret == -1){
        perror(zone);
        exit(7);
    }
    ret = shm_unlink(zone);
    if (ret == -1){
        perror(zone);
        exit(8);
    }
}


void write_main_rest_buffer(struct rnd_access_buffer* buffer, int buffer_size, struct operation* op){
    int* arr_free = buffer->ptrs;
    struct operation* arr_ops = buffer->buffer;
    while (1){
        for (int i = 0; i < buffer_size; ++i) {
            if(arr_free[i]==0){
                //não sei se é correto a fazer
                arr_ops[i]= *op;
            }
        }
    }
}


void write_rest_driver_buffer(struct circular_buffer* buffer, int buffer_size, struct operation* op){
    struct pointers *ptr = buffer->ptrs;
    int in  = ptr->in;
    int out = ptr->out;
    struct operation* arr_ops = buffer->buffer;
    while((in+1)%buffer_size==out){
        __asm__("nop");
    }
    arr_ops[in] = *op;
    in = (in+1)%buffer_size;
}



void write_driver_client_buffer(struct rnd_access_buffer* buffer, int buffer_size, struct operation* op){
    int* arr_free = buffer->ptrs;
    struct operation* arr_ops = buffer->buffer;
    while (1){
        for (int i = 0; i < buffer_size; ++i) {
            if(arr_free[i]==0){
                //não sei se é correto a fazer
                arr_ops[i]= *op;
            }
        }
    }
}


void read_main_rest_buffer(struct rnd_access_buffer* buffer, int rest_id, int buffer_size, struct operation* op){
    int* ptrs = buffer->ptrs;
    struct operation* arr_ops = buffer->buffer;
    for (int i = 0; i < buffer_size; ++i) {
        if(ptrs[i]==1){
            int op_rest_id =  arr_ops[i].receiving_rest;
            if(op_rest_id==rest_id){
                op = &arr_ops[i];
                ptrs[i]=0;
                return;
            }
        }
    }
    op->id=-1;
}


void read_rest_driver_buffer(struct circular_buffer* buffer, int buffer_size, struct operation* op){
    struct pointers *ptr = buffer->ptrs;
    struct operation* ops = buffer->buffer;
    int in  = ptr->in;
    int out = ptr->out;
    if(in==out){
        op->id=-1;
    } else{
        op = &ops[out];
        buffer->ptrs->out= (out+1)%buffer_size;
    }
}

/* Função que lê uma operação do buffer de memória partilhada entre os motoristas e os clientes,
* se houver alguma disponível para ler dirijida ao cliente especificado. A leitura deve
* ser feita tendo em conta o tipo de buffer e as regras de leitura em buffers desse tipo. Se não houver
* nenhuma operação disponível, afeta op->id com o valor -1.
*/
void read_driver_client_buffer(struct rnd_access_buffer* buffer, int client_id, int buffer_size, struct operation* op){
    int* ptrs = buffer->ptrs;
    struct operation* arr_ops = buffer->buffer;
    for (int i = 0; i < buffer_size; ++i) {
        if(ptrs[i]==1){
            int op_rest_id =  arr_ops[i].receiving_rest;
            if(op_rest_id==client_id){
                op = &arr_ops[i];
                ptrs[i]=0;
                return;
            }
        }
    }
    op->id=-1;
}