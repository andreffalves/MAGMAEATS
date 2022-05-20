#include <stdio.h>
#include <stdlib.h>
#include "main.h"
char* statsFileName;
extern struct main_data* data;


void writeStatsToFile(){
    FILE *fp;
    fp = fopen(statsFileName,"w");
    if(ferror(fp)){
        perror("stats file");
        exit(1);
    }
    fputs("Process Statistics:\n",fp);
    int num_rest = data->n_restaurants;
    for (int i = 0; i < num_rest; ++i) {
        fprintf(fp,"\tRestaurant %d prepared %d requests\n",i,data->restaurant_stats[i]);
    }

    int num_driv = data->n_drivers;
    for (int i = 0; i < num_driv; ++i) {
        fprintf(fp,"\tDriver %d delivered %d requests\n",i,data->driver_stats[i]);
    }

    int num_cli = data->n_clients;
    for (int i = 0; i < num_cli; ++i) {
        fprintf(fp,"\tDriver %d received %d requests\n",i,data->client_stats[i]);
    }
    fputs("\nRequest Statistics:\n",fp);
    fclose(fp);
}

