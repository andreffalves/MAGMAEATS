#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "memory.h"
 FILE *logFile;

void logHelp(){
    struct timespec currentTime;
    if( clock_gettime( CLOCK_REALTIME, &currentTime) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }
    int mili = currentTime.tv_nsec/1000000;
    time_t secs= currentTime.tv_sec;
    struct tm* time;
    time = localtime(&secs);
    char* buffer = create_dynamic_memory(50*sizeof(char));
    int result = sprintf(buffer,"%d-%d-%d %d:%d:%d.%d help\n",time->tm_year+1900,time->tm_mon+1,time->tm_mday,
                         time->tm_hour,time->tm_min,time->tm_sec,mili);
    if(result==-1){
        perror("log help");
        exit(1);
    }
    fputs(buffer, logFile);
    destroy_dynamic_memory(buffer);
}



void logStop(){
    struct timespec currentTime;
    if( clock_gettime( CLOCK_REALTIME, &currentTime) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }
    int mili = currentTime.tv_nsec/1000000;
    time_t secs= currentTime.tv_sec;
    struct tm* time;
    time = localtime(&secs);
    char* buffer = create_dynamic_memory(50*sizeof(char));
    int result = sprintf(buffer,"%d-%d-%d %d:%d:%d.%d stop\n",time->tm_year+1900,time->tm_mon+1,time->tm_mday,
                         time->tm_hour,time->tm_min,time->tm_sec,mili);
    if(result==-1){
        perror("log stop");
        exit(1);
    }
    fputs(buffer, logFile);
    destroy_dynamic_memory(buffer);
}



void logRequest(int rest, int cli, char* dishName){
    struct timespec currentTime;
    if( clock_gettime( CLOCK_REALTIME, &currentTime) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }
    int mili = currentTime.tv_nsec/1000000;
    time_t secs= currentTime.tv_sec;
    struct tm* time;
    time = localtime(&secs);
    char* buffer = create_dynamic_memory(50*sizeof(char));
    int result = sprintf(buffer,"%d-%d-%d %d:%d:%d.%d request %d %d %s\n",time->tm_year+1900,time->tm_mon+1,time->tm_mday,
                         time->tm_hour,time->tm_min,time->tm_sec,mili,
                         cli, rest, dishName);
    if(result==-1){
        perror("log request");
        exit(1);
    }
    fputs(buffer, logFile);
    destroy_dynamic_memory(buffer);
}






void logStatus(int requestNum){
    struct timespec currentTime;
    if( clock_gettime( CLOCK_REALTIME, &currentTime) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }
    int mili = currentTime.tv_nsec/1000000;
    time_t secs= currentTime.tv_sec;
    struct tm* time;
    time = localtime(&secs);
    char* buffer = create_dynamic_memory(50*sizeof(char));
    int result = sprintf(buffer,"%d-%d-%d %d:%d:%d.%d status %d\n",time->tm_year+1900,time->tm_mon+1,time->tm_mday,
                         time->tm_hour,time->tm_min,time->tm_sec,mili,
                         requestNum);
    if(result==-1){
        perror("log request");
        exit(1);
    }
    fputs(buffer, logFile);
    destroy_dynamic_memory(buffer);
}


void closeLog(){
    fclose(logFile);
}