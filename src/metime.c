#include "metime.h"

struct timespec getCurrentTime(){
    struct timespec currentTime;
    if( clock_gettime( CLOCK_REALTIME, &currentTime) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }
    return currentTime;
}