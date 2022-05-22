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
 * Retorna a quantidade maxima de operações como definidas no ficheiro de configurações.
 * O ficheiro tem de existir.
 * */
int getMaxOps(char* configFileName);

/*
 * Retorna o tamanho dos buffers como definidos no ficheiro de configurações.
 * O ficheiro tem de existir.
 * */
int getBufferSize(char* configFileName);

/*
 * Retorna o numero de restaurantes como definidos no ficheiro de configurações.
 * O ficheiro tem de existir.
 * */
int getNumRests(char* configFileName);

/*
 * Retorna o numero de restaurantes como definidos no ficheiro de configurações.
 * O ficheiro tem de existir
 * */
int getNumDrivers(char* configFileName);

/*
 * Retorna o numero de clientes como definidos no ficheiro de configurações.
 * O ficheiro tem de existir.
 * */
int getNumClients(char* configFileName);

/*
 * Devolve o apontador para o ficheiro de log, a partir do ficheiro definido no ficheiro de configurações.
 * Se o ficheiro de log não existir é criado um novo se existir os seus conteudos são apagados.
 *  O ficheiro de configurações tem de existir.
 * */
FILE * getLogFile(char* configFileName);

/*
 * Devolve o nome do ficheiro de Estatísticas como definido no ficheiro de configurações.
 * O ficheiro de configurações tem de existir.
 */
char* getStatsFileName(char* configFileName);

/*
 * Devolve o tamanho do intervalo de tempo como definido no ficheiro de configurações.
 * O ficheiro de configurações tem de existir.
 */
int getAlarmTime(char* configFileName);

#endif