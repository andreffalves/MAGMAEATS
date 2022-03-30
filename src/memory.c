#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>


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

}