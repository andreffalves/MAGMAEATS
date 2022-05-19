#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "memory.h"
#define MAXLINE 1024

int getMaxOps(char* configFileName){
    char line[MAXLINE];
    FILE *fp;
    fp = fopen(configFileName,"r");
    if(fp==NULL){
        perror("ficheiro não existe\n");
        exit(1);
    }
    if(ferror(fp)){
        perror("config file");
        exit(1);
    }

    fgets(line,MAXLINE,fp);
    int ops = atoi(line);
    fclose(fp);
    return ops;
}

int getBufferSize(char* configFileName){
    char line[MAXLINE];
    FILE *fp;
    fp = fopen(configFileName,"r");
    if(fp==NULL){
        perror("ficheiro não existe\n");
        exit(1);
    }
    if(ferror(fp)){
        perror("config file");
        exit(1);
    }
    for (int i = 0; i <2; i++) {
        fgets(line,MAXLINE,fp);
    }
    int bufs = atoi(line);
    fclose(fp);
    return bufs;
}


int getNumRests(char* configFileName){
    char line[MAXLINE];
    FILE *fp;
    fp = fopen(configFileName,"r");
    if(fp==NULL){
        perror("ficheiro não existe\n");
        exit(1);
    }
    if(ferror(fp)){
        perror("config file");
        exit(1);
    }
    for (int i = 0; i <3 ; i++) {
        fgets(line,MAXLINE,fp);
    }
    int rests = atoi(line);
    fclose(fp);
    return rests;
}


int getNumDrivers(char* configFileName){
    char line[MAXLINE];
    FILE *fp;
    fp = fopen(configFileName,"r");
    if(fp==NULL){
        perror("ficheiro não existe\n");
        exit(1);
    }
    if(ferror(fp)){
        perror("config file");
        exit(1);
    }
    for (int i = 0; i <4 ; i++) {
        fgets(line,MAXLINE,fp);
    }
    int drivers = atoi(line);
    fclose(fp);
    return drivers;
}

int getNumClients(char* configFileName){
    char line[MAXLINE];
    FILE *fp;
    fp = fopen(configFileName,"r");
    if(fp==NULL){
        perror("ficheiro não existe\n");
        exit(1);
    }
    if(ferror(fp)){
        perror("config file");
        exit(1);
    }
    for (int i = 0; i <5 ; i++) {
        fgets(line,MAXLINE,fp);
    }
    int clients = atoi(line);
    fclose(fp);
    return clients;
}


FILE * getLogFile(char* configFileName){
    char line[MAXLINE];
    FILE *fp;
    fp = fopen(configFileName,"r");
    if(fp==NULL){
        perror("ficheiro não existe\n");
        exit(1);
    }
    if(ferror(fp)){
        perror("config file");
        exit(1);
    }
    for (int i = 0; i <7 ; i++) {
        fgets(line,MAXLINE,fp);
    }
    fclose(fp);
    FILE *log;
    log = fopen(line,"w");
    if(ferror(fp)){
        perror("log file");
        exit(1);
    }
    return log;
}


char* getStatsFileName(char* configFileName){
    char* line = create_dynamic_memory(MAXLINE*sizeof(char));//destroy when stop
    FILE *fp;
    fp = fopen(configFileName,"r");
    if(fp==NULL){
        perror("ficheiro não existe\n");
        exit(1);
    }
    if(ferror(fp)){
        perror("config file");
        exit(1);
    }
    for (int i = 0; i <7 ; i++) {
        fgets(line,MAXLINE,fp);
    }
    fclose(fp);
    return line;
}



int getAlarmTime(char* configFileName){
    char line[MAXLINE];
    FILE *fp;
    fp = fopen(configFileName,"r");
    if(fp==NULL){
        perror("ficheiro não existe\n");
        exit(1);
    }
    if(ferror(fp)){
        perror("config file");
        exit(1);
    }
    for (int i = 0; i <8 ; i++) {
        fgets(line,MAXLINE,fp);
    }
    int alarmTime = atoi(line);
    fclose(fp);
    return alarmTime;
}
