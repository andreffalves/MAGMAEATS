#include <stdio.h>
 FILE *logFile;

void logHelp(){
    fputs("help", logFile);
}

void closeLog(){
    fclose(logFile);
}