#include "main.h"
/* Função principal de um Restaurante. Deve executar um ciclo infinito onde em
* cada iteração lê uma operação da main e se e data->terminate ainda for igual a 0, processa-a e
* escreve-a para os motoristas. Operações com id igual a -1 são ignoradas
* (op inválida) e se data->terminate for igual a 1 é porque foi dada ordem
* de terminação do programa, portanto deve-se fazer return do número de
* operações processadas. Para efetuar estes passos, pode usar os outros
* métodos auxiliares definidos em restaurant.h.
*/


int execute_restaurant(int rest_id, struct communication_buffers* buffers, struct main_data* data){
    int ops = 0;
    int terminate_flag = *(data->terminate);
    while (1){
        terminate_flag = *(data->terminate);
        if(terminate_flag == 1)
            return ops;
    }
}