/*
Grupo: SO-010
Membros:
Francisco Teixeira | FC56305
Andre Alves        | FC56349
Rodrigo Antunes    | FC56321
*/
#ifndef MAGMAEATS_LOG_H
#define MAGMAEATS_LOG_H


/*
 * escreve no ficheiro de log definido com o formato
 * tempo help
 * onde o tempo é o tempo quando a função é chamada
 */
void logHelp();



/*
 * escreve no ficheiro de log definido com o formato
 * tempo status rest cli dishName
 * onde o tempo é o tempo quando a função é chamada
 * e rest e cli são os numeros introduzidos pelo o utilizador em caso de um formato de input valido de um numero
 * tal numero aparece como -1
 * dishName é o nome do prato introduzido
 */
void logRequest(int rest,  int cli, char* dishName);


/*
 * escreve no ficheiro de log definido com o formato
 * tempo stop
 * onde o tempo é o tempo quando a função é chamada
 */
void logStop();


/*
 * escreve no ficheiro de log definido com o formato
 * tempo status requestNum
 * onde o tempo é o tempo quando a função é chamada
 * e requestNum é o numero introduzido pelo o utilizador em caso de um formato de input valido de numero
 * o numero aparece como -1
 */
void logStatus(int resquestNum);

/*
 * Fecha o ficheiro de log.
 */
void closeLog();


#endif