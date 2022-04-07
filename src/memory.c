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
    char* zone = create_dynamic_memory(strlen(name)+1+10);
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
    destroy_dynamic_memory(zone);
    return ptr;
}


void destroy_shared_memory(char* name, void* ptr, int size){
    int id = getuid();
    int ret;
    char* zone = create_dynamic_memory(strlen(name)+1+10);
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
    destroy_dynamic_memory(zone);
}


void write_main_rest_buffer(struct rnd_access_buffer* buffer, int buffer_size, struct operation* op){
    struct operation next_produced = *op;
    int n;
    while (1){
        for(n=0;n<buffer_size;n++){
            if(((buffer->ptrs)[n])==0){
                ((buffer->ptrs)[n])=1;
                ((buffer->buffer)[n])=next_produced;
                return;
            }
        }
    }
}


void read_main_rest_buffer(struct rnd_access_buffer* buffer, int rest_id, int buffer_size, struct operation* op){
    int n;
    for (n = 0; n < buffer_size; n++) {
        if(((buffer->ptrs)[n])==1){
            if((((buffer->buffer)[n]).requested_rest)==rest_id) {
                (buffer->ptrs)[n] = 0;
                *op = (buffer->buffer)[n];
                return;
            }
        }
    }
    op->id=-1;
}

void write_rest_driver_buffer(struct circular_buffer* buffer, int buffer_size, struct operation* op){
    struct operation next_produced = *op;
    struct pointers *ptr = buffer->ptrs;
    struct operation* arr_ops = buffer->buffer;
    while(((ptr->in)+1)%buffer_size==(ptr->out)){
    }
    arr_ops[ptr->in] = next_produced;
    ptr->in = (ptr->in+1)%buffer_size;
}


void read_rest_driver_buffer(struct circular_buffer* buffer, int buffer_size, struct operation* op){
    struct pointers *ptr = buffer->ptrs;
    struct operation* ops = buffer->buffer;
    if((ptr->in)==(ptr->out)){
        op->id=-1;
    } else{
        *op = ops[(ptr->out)];
        (ptr->out)= ((ptr->out)+1)%buffer_size;
    }
}

void write_driver_client_buffer(struct rnd_access_buffer* buffer, int buffer_size, struct operation* op){
    struct operation next_produced = *op;
    int n;
    while (1){
        for (n = 0; n < buffer_size; n++) {
            for(n=0;n<buffer_size;n++) {
                if (((buffer->ptrs)[n]) == 0) {
                    ((buffer->ptrs)[n]) = 1;
                    ((buffer->buffer)[n]) = next_produced;
                    return;
                }
            }
        }
    }
}



/*
  void read_main_rest_buffer(struct rnd_access_buffer* buffer, int rest_id, int buffer_size, struct operation* op){
    int n;
    for (n = 0; n < buffer_size; n++) {
        if(((buffer->ptrs)[n])==1){
            if((((buffer->buffer)[n]).requested_rest)==rest_id) {
                (buffer->ptrs)[n] = 0;
                *op = (buffer->buffer)[n];
                return;
            }
        }
    }
    op->id=-1;
}*/

void read_driver_client_buffer(struct rnd_access_buffer* buffer, int client_id, int buffer_size, struct operation* op){
    int n;
    for (n = 0; n < buffer_size; n++) {
        if(((buffer->ptrs)[n])==1){
            if((((buffer->buffer)[n]).requesting_client)==client_id){
                (buffer->ptrs)[n] = 0;
                *op = (buffer->buffer)[n];
                return;
            }
        }
    }
    op->id=-1;
}