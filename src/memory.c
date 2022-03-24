#include <stdlib.h>
#include <strings.h>
void* create_dynamic_memory(int size){
    *ptr = malloc(size);
    bzero(ptr,size);
    return ptr;
}

void destroy_dynamic_memory(void *ptr){
    free(ptr)
}