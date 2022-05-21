/*
Grupo: SO-010
Membros:
Francisco Teixeira | FC56305
Andre Alves        | FC56349
Rodrigo Antunes    | FC56321
*/
#ifndef CONFIGURATION_H_GUARD
#define CONFIGURATION_H_GUARD

/*
 * Retorna a quantidade maxima de operações como definidas no ficheiro.
 * O ficheiro tem de existir
 * */
int getMaxOps(char* configFileName);

/*
 * Retorna o tamanho dos buffers como definidos no ficheiro.
 * O ficheiro tem de existir
 * */
int getBufferSize(char* configFileName);

/*
 * Retorna o numero de restaurantes como definidos no ficheiro.
 * O ficheiro tem de existir
 * */
int getNumRests(char* configFileName);

/*
 * Retorna o numero de restaurantes como definidos no ficheiro.
 * O ficheiro tem de existir
 * */
int getNumDrivers(char* configFileName);


int getNumClients(char* configFileName);


FILE * getLogFile(char* configFileName);


char* getStatsFileName(char* configFileName);


int getAlarmTime(char* configFileName);

#endif