/*
Grupo: SO-010
Membros:
Francisco Teixeira | FC56305
Andre Alves        | FC56349
Rodrigo Antunes    | FC56321
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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
    fprintf(logFile,"%d-%d-%d %d:%d:%d.%03d help\n",time->tm_year+1900,time->tm_mon+1,time->tm_mday,
                         time->tm_hour,time->tm_min,time->tm_sec,mili);
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
    fprintf(logFile,"%d-%d-%d %d:%d:%d.%03d stop\n",time->tm_year+1900,time->tm_mon+1,time->tm_mday,
            time->tm_hour,time->tm_min,time->tm_sec,mili);


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
    fprintf(logFile,"%d-%d-%d %d:%d:%d.%03d request %d %d %s\n",time->tm_year+1900,time->tm_mon+1,time->tm_mday,
                         time->tm_hour,time->tm_min,time->tm_sec,mili,
                         cli, rest, dishName);
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
    fprintf(logFile,"%d-%d-%d %d:%d:%d.%03d status %d\n",time->tm_year+1900,time->tm_mon+1,time->tm_mday,
                         time->tm_hour,time->tm_min,time->tm_sec,mili,
                         requestNum);
}


void closeLog(){
    fclose(logFile);
}