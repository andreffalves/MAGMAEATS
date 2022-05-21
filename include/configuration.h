/*
Grupo: SO-010
Membros:
Francisco Teixeira | FC56305
Andre Alves        | FC56349
Rodrigo Antunes    | FC56321
*/
#ifndef CONFIGURATION_H_GUARD
#define CONFIGURATION_H_GUARD


int getMaxOps(char* configFileName);


int getBufferSize(char* configFileName);


int getNumRests(char* configFileName);


int getNumDrivers(char* configFileName);


int getNumClients(char* configFileName);


FILE * getLogFile(char* configFileName);


char* getStatsFileName(char* configFileName);


int getAlarmTime(char* configFileName);

#endif