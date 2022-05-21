/*
Grupo: SO-010
Membros:
Francisco Teixeira | FC56305
Andre Alves        | FC56349
Rodrigo Antunes    | FC56321
*/
#ifndef MAGMAEATS_LOG_H
#define MAGMAEATS_LOG_H

void logHelp();

void logRequest(int rest,  int cli, char* dishName);

void logStop();

void logStatus(int resquestNum);

void closeLog();


#endif