/*
Grupo: SO-010
Membros:
Francisco Teixeira | FC56305
Andre Alves        | FC56349
Rodrigo Antunes    | FC56321
*/
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <time.h>
#include "synchronization.h"
char* statsFileName;
extern struct main_data* data;
extern struct semaphores* sems;


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
    int mili =0;
    struct timespec created;
    struct tm *createdTime;

    struct timespec rest;
    struct tm *restTime;

    struct timespec driver;
    struct tm *driverTime;

    struct timespec client;
    struct tm *clientTime;

    time_t secDiff = 0;
    long nanoDiff;

    fputs("\nRequest Statistics:\n",fp);
    semaphore_mutex_lock(sems->results_mutex);
    for (int i = 0; i < data->max_ops; ++i) {
        struct operation temp= (data->results)[i];
        switch (temp.status) {
            case 'I':
                fprintf(fp,"Request: %d\n",i);
                fputs("Status: I\n",fp);
                fprintf(fp,"Restaurant id: %d\n",temp.requested_rest);
                fprintf(fp,"Driver id: N/A \n");
                fprintf(fp,"Request: %d\n",temp.requesting_client);

                created= temp.start_time;
                createdTime = localtime(&created.tv_sec);

                mili = created.tv_nsec/1000000;
                fprintf(fp,"Created Time: %d-%d-%d %d:%d:%d.%03d\n",createdTime->tm_year+1900,createdTime->tm_mon+1,createdTime->tm_mday,
                        createdTime->tm_hour,createdTime->tm_min,createdTime->tm_sec,mili);

                fputs("Restaurant time: N/A\n",fp);
                fputs("Driver time: N/A\n",fp);
                fputs("Client time (end): N/A\n",fp);
                fputs("Total time: N/A\n\n",fp);

                break;
            case 'R':
                fprintf(fp,"Request: %d\n",i);
                fputs("Status: R\n",fp);
                fprintf(fp,"Restaurant id: %d\n",temp.requested_rest);
                fprintf(fp,"Driver id: N/A \n");
                fprintf(fp,"Client id: %d\n",temp.requesting_client);

                created= temp.start_time;
                createdTime = localtime(&created.tv_sec);

                mili = created.tv_nsec/1000000;
                fprintf(fp,"Created Time: %d-%d-%d %d:%d:%d.%03d\n",createdTime->tm_year+1900,createdTime->tm_mon+1,createdTime->tm_mday,
                        createdTime->tm_hour,createdTime->tm_min,createdTime->tm_sec,mili);

                rest = temp.rest_time;
                restTime = localtime(&rest.tv_sec);

                mili = rest.tv_nsec/1000000;

                fprintf(fp,"Restaurant Time: %d-%d-%d %d:%d:%d.%03d\n",restTime->tm_year+1900,restTime->tm_mon+1,restTime->tm_mday,
                        restTime->tm_hour,restTime->tm_min,restTime->tm_sec,mili);

                fputs("Driver time: N/A\n",fp);
                fputs("Client time (end): N/A\n",fp);
                fputs("Total time: N/A\n\n",fp);

                break;
            case 'D':
                fprintf(fp,"Request: %d\n",i);
                fputs("Status: D\n",fp);
                fprintf(fp,"Restaurant id: %d\n",temp.requested_rest);
                fprintf(fp,"Driver id: %d \n",temp.receiving_driver);
                fprintf(fp,"Client id: %d\n",temp.requesting_client);

                created= temp.start_time;
                createdTime = localtime(&created.tv_sec);

                mili = created.tv_nsec/1000000;
                fprintf(fp,"Created Time: %d-%d-%d %d:%d:%d.%03d\n",createdTime->tm_year+1900,createdTime->tm_mon+1,createdTime->tm_mday,
                        createdTime->tm_hour,createdTime->tm_min,createdTime->tm_sec,mili);


                rest = temp.rest_time;
                restTime = localtime(&rest.tv_sec);

                mili = rest.tv_nsec/1000000;

                fprintf(fp,"Restaurant Time: %d-%d-%d %d:%d:%d.%03d\n",restTime->tm_year+1900,restTime->tm_mon+1,restTime->tm_mday,
                        restTime->tm_hour,restTime->tm_min,restTime->tm_sec,mili);

                driver = temp.driver_time;
                driverTime = localtime(&rest.tv_sec);

                mili = driver.tv_nsec/1000000;

                fprintf(fp,"Driver Time: %d-%d-%d %d:%d:%d.%03d\n",driverTime->tm_year+1900,driverTime->tm_mon+1,driverTime->tm_mday,
                        driverTime->tm_hour,driverTime->tm_min,driverTime->tm_sec,mili);

                fputs("Client time (end): N/A\n",fp);
                fputs("Total time: N/A\n\n",fp);

                break;
            case 'C':
                fprintf(fp,"Request: %d\n",i);
                fputs("Status: C\n",fp);
                fprintf(fp,"Restaurant id: %d\n",temp.requested_rest);
                fprintf(fp,"Driver id: %d \n",temp.receiving_driver);
                fprintf(fp,"Client id: %d\n",temp.requesting_client);

                created = temp.start_time;
                createdTime = localtime(&created.tv_sec);

                mili = created.tv_nsec/1000000;
                fprintf(fp,"Created Time: %d-%d-%d %d:%d:%d.%03d\n",createdTime->tm_year+1900,createdTime->tm_mon+1,createdTime->tm_mday,
                        createdTime->tm_hour,createdTime->tm_min,createdTime->tm_sec,mili);


                rest = temp.rest_time;
                restTime = localtime(&rest.tv_sec);

                mili = rest.tv_nsec/1000000;

                fprintf(fp,"Restaurant Time: %d-%d-%d %d:%d:%d.%03d\n",restTime->tm_year+1900,restTime->tm_mon+1,restTime->tm_mday,
                        restTime->tm_hour,restTime->tm_min,restTime->tm_sec,mili);


                driver = temp.driver_time;
                driverTime = localtime(&rest.tv_sec);

                mili = driver.tv_nsec/1000000;

                fprintf(fp,"Driver Time: %d-%d-%d %d:%d:%d.%03d\n",driverTime->tm_year+1900,driverTime->tm_mon+1,driverTime->tm_mday,
                        driverTime->tm_hour,driverTime->tm_min,driverTime->tm_sec,mili);


                client = temp.driver_time;
                clientTime = localtime(&rest.tv_sec);

                mili = client.tv_nsec/1000000;

                fprintf(fp,"Client Time (end): %d-%d-%d %d:%d:%d.%03d\n",clientTime->tm_year+1900,clientTime->tm_mon+1,clientTime->tm_mday,
                        clientTime->tm_hour,driverTime->tm_min,clientTime->tm_sec,mili);



                nanoDiff = client.tv_nsec-created.tv_nsec;
                secDiff = client.tv_sec-created.tv_sec;
                if(nanoDiff<0){
                    nanoDiff += 1000000000;
                    secDiff -=1;
                }
                mili = nanoDiff/1000000;
                fprintf(fp,"Total time: %ld.%03d\n\n",secDiff,mili);

                break;
            default:
                break;

        }
        semaphore_mutex_unlock(sems->results_mutex);
    }
    fclose(fp);
}

