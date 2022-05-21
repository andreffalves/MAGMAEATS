/*
Grupo: SO-010
Membros:
Francisco Teixeira | FC56305
Andre Alves        | FC56349
Rodrigo Antunes    | FC56321
*/
#ifndef METIME_H_GUARD
#define METIME_H_GUARD

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * Função que usa o clock_gettime para devolver o tempo atual
 */
struct timespec getCurrentTime();


#endif