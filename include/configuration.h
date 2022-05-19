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