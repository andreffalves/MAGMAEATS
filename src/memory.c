#include <stdlib.h>
#include <string.h>
void* create_dynamic_memory(int size){
    void *ptr = malloc(size);
    memset(ptr,0, size)
    return ptr;
}

void destroy_dynamic_memory(void *ptr){
    free(ptr);
}