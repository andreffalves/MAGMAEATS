/*
Grupo: SO-010
Membros:
Francisco Teixeira | FC56305
Andre Alves        | FC56349
Rodrigo Antunes    | FC56321
*/
#include <semaphore.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "memory.h"
#include "synchronization.h"

sem_t * semaphore_create(char* name, int value){
    sem_t *sem;
    int id = getuid();
    char* zone = create_dynamic_memory(strlen(name)+1+10);
    int result = sprintf(zone,"/%s-%d",name,id);
    if(result==-1){
        perror(name);
        exit(1);
    }
    sem = sem_open(zone, O_CREAT, 0xFFFFFFFF, value);
    if (sem == SEM_FAILED){
        perror(name);
        exit(2);
    }
    destroy_dynamic_memory(zone);
    return sem;

}


void semaphore_destroy(char* name, sem_t* semaphore){
    int id = getuid();
    char* zone = create_dynamic_memory(strlen(name)+1+10);
    int result = sprintf(zone,"/%s-%d",name,id);
    if(result==-1){
        perror(name);
        exit(1);
    }
    if (sem_close(semaphore) == -1){
        perror(name);
        exit(1);
    }
    if (sem_unlink(zone) == -1){
        perror(name);
        exit(2);
    }
    destroy_dynamic_memory(zone);
}


void produce_begin(struct prodcons* pc){
    sem_wait(pc->empty);
    sem_wait(pc->mutex);
}


void produce_end(struct prodcons* pc)  {
    sem_post(pc->mutex);
    sem_post(pc->full);
}


void consume_begin(struct prodcons* pc){
    sem_wait(pc->full);
    sem_wait(pc->mutex);
}


void consume_end(struct prodcons* pc){
    sem_post(pc->mutex);
    sem_post(pc->empty);
}


void semaphore_mutex_lock(sem_t* sem){
    sem_wait(sem);
}


void semaphore_mutex_unlock(sem_t* sem){
    sem_post(sem);
}