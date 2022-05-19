#ifndef MESIGNAL_H_GUARD
#define MESIGNAL_H_GUARD

#include "main.h"


/*Função que define o comportamento de um processo a um sinal para apenas ignorar esse sinal
 *
 */
void ignoreSignal();

/*
 * Handler chamado pela função ignoreSignal
 */

void ignoreHandler(int sig);

/*
 *Função que define o comportamento de um processo a um sinal para chamar a função stop implementada
 *
 */
void stopMain();

/*
 * Handler chamado pela função stopMain
 */
void stopMainHandler(int sig);

/*
 *Função que define qual deve ser o intervalo de tempo para o alarme
 */
void setTimer(int secs);


/*
 * Handler do timer que faz que o timer dispare de de secs em secs como definido em setTimer
 */
void timerHandler(int sig);



#endif