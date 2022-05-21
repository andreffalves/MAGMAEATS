/*
Grupo: SO-010
Membros:
Francisco Teixeira | FC56305
Andre Alves        | FC56349
Rodrigo Antunes    | FC56321
*/
#include "metime.h"

struct timespec getCurrentTime(){
    struct timespec currentTime;
    if( clock_gettime( CLOCK_REALTIME, &currentTime) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }
    return currentTime;
}