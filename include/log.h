#ifndef MAGMAEATS_LOG_H
#define MAGMAEATS_LOG_H

void logHelp();

void logRequest(int rest,  int cli, char* dishName);

void logStop();

void logStatus(int resquestNum);

void closeLog();


#endif