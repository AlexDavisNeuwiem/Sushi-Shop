#include <stdio.h>
#include <stdlib.h>

#include "virtual_clock.h"
#include "customer.h"
#include "globals.h"


void* customer_run(void* arg) {
    /* 
        MODIFIQUE ESSA FUNÇÃO PARA GARANTIR O COMPORTAMENTO CORRETO E EFICAZ DO CLIENTE.
        NOTAS:
        1.  A PRIMEIRA AÇÃO REALIZADA SERÁ ESPERAR NA FILA GLOBAL DE CLIENTES, ATÉ QUE O HOSTESS
            GUIE O CLIENTE PARA UM ASSENTO LIVRE.
        2.  APÓS SENTAR-SE, O CLIENTE COMEÇARÁ PEGAR E COMER OS PRATOS DA ESTEIRA.
        3.  O CLIENTE SÓ PODERÁ PEGAR UM PRATO QUANDO A ESTEIRA ESTIVER PARADA.
        4.  O CLIENTE SÓ PEGARÁ PRATOS CASO ELE DESEJE-OS, INFORMAÇÃO CONTIDA NO ARRAY self->_wishes[...].
        5.  APÓS CONSUMIR TODOS OS PRATOS DESEJADOS, O CLIENTE DEVERÁ SAIR IMEDIATAMENTE DA ESTEIRA.
        6.  QUANDO O RESTAURANTE FECHAR, O CLIENTE DEVERÁ SAIR IMEDIATAMENTE DA ESTEIRA. 
        7.  CASO O CLIENTE ESTEJA COMENDO QUANDO O SUSHI SHOP FECHAR, ELE DEVE TERMINAR DE COMER E EM SEGUIDA
            SAIR IMEDIATAMENTE DA ESTEIRA.
        8.  LEMBRE-SE DE TOMAR CUIDADO COM ERROS DE CONCORRÊNCIA!
    */ 
    
    customer_t* self = (customer_t*) arg;

    /* O semáforo abaixo é inicializado com 0 e apenas o hostess e a Queue podem fazer o "post" */
    /* Assim, o cliente só continuará sua execução quando estiver sentado ou quando o restaurante fechar */

    /* Semáforo para evitar espera ocupada do cliente */
    sem_wait(&self->espera);

    conveyor_belt_t* conveyor_belt = globals_get_conveyor_belt();

    int wishes_size = sizeof(self->_wishes)/sizeof(self->_wishes[0]);

    /* A variável "desejos" determina se o cliente sairá do loop ou não */
    int desejos = 0;
    for (int i = 0; i < wishes_size; i++) {
        desejos += self->_wishes[i];
    }

    while(globals_get_sushi_shop_fechado() == 0) {
        if (desejos > 0) {
            for (int i = 0; i < wishes_size && globals_get_sushi_shop_fechado() == 0; i++) {
                if (self->_wishes[i] > 0) {

                    /* A variável "found_food" informa se o cliente já pegou a comida ou não */
                    /* A variável "food" nos permite separar as funções "customer_pick_food" e "customer_eat" */

                    int food_found = 0;
                    enum menu_item food;

                    /* Como há um mutex em cada posição da esteira, os clientes podem pegar a comida paralelamente */
                    /* Esses mutexes também são disputados pelo sushi_chef e pela conveyor_belt */

                    pthread_mutex_lock(&conveyor_belt->_pratos_mutex[self->_seat_position]);
                    if (conveyor_belt->_food_slots[self->_seat_position] == i) {
                        food = customer_pick_food(self->_seat_position);
                        food_found = 1;
                    }
                    pthread_mutex_unlock(&conveyor_belt->_pratos_mutex[self->_seat_position]);

                    if (food_found == 0) {
                        pthread_mutex_lock(&conveyor_belt->_pratos_mutex[self->_seat_position - 1]);
                        if (conveyor_belt->_food_slots[self->_seat_position - 1] == i) {
                            food = customer_pick_food(self->_seat_position - 1);
                            food_found = 1;
                        }
                        pthread_mutex_unlock(&conveyor_belt->_pratos_mutex[self->_seat_position - 1]);
                    }

                    if (food_found == 0 && (self->_seat_position + 1) != conveyor_belt->_size) {
                        pthread_mutex_lock(&conveyor_belt->_pratos_mutex[self->_seat_position + 1]);
                        if (conveyor_belt->_food_slots[self->_seat_position + 1] == i) {
                            food = customer_pick_food(self->_seat_position + 1);
                            food_found = 1;
                        }
                        pthread_mutex_unlock(&conveyor_belt->_pratos_mutex[self->_seat_position + 1]);
                    }

                    if (food_found == 1 && globals_get_sushi_shop_fechado() == 0) {
                        customer_eat(self, food);
                        if (food == 0) {
                            pthread_mutex_lock(globals_get_sushi_cons_mutex());
                            globals_add_sushi_cons();
                            pthread_mutex_unlock(globals_get_sushi_cons_mutex());
                        } else if (food == 1) {
                            pthread_mutex_lock(globals_get_dango_cons_mutex());
                            globals_add_dango_cons();
                            pthread_mutex_unlock(globals_get_dango_cons_mutex());
                        } else if (food == 2) {
                            pthread_mutex_lock(globals_get_ramen_cons_mutex());
                            globals_add_ramen_cons();
                            pthread_mutex_unlock(globals_get_ramen_cons_mutex());
                        } else if (food == 3) {
                            pthread_mutex_lock(globals_get_onigiri_cons_mutex());
                            globals_add_onigiri_cons();
                            pthread_mutex_unlock(globals_get_onigiri_cons_mutex());
                        } else {
                            pthread_mutex_lock(globals_get_tofu_cons_mutex());
                            globals_add_tofu_cons();
                            pthread_mutex_unlock(globals_get_tofu_cons_mutex());
                        }
                        food_found = 0;
                        desejos--;
                    }
                }
            }

        }
        if (desejos == 0) {
            pthread_mutex_lock(globals_get_clientes_satisfeitos_mutex());
            globals_add_clientes_satisfeitos();
            pthread_mutex_unlock(globals_get_clientes_satisfeitos_mutex());
            break;
        }
    }

    customer_leave(self);
}

enum menu_item customer_pick_food(int food_slot) {
    /* 
        MODIFIQUE ESSA FUNÇÃO PARA GARANTIR O COMPORTAMENTO CORRETO E EFICAZ DO CLIENTE.
        NOTAS:
        1.  O CLIENTE SÓ PODE COMEÇAR A PEGAR COMIDA APÓS ESTAR SENTADO EM UMA VAGA DA ESTEIRA.
        2.  O CLIENTE SÓ SENTARÁ QUANDO O HOSTESS ATUALIZAR O VALOR customer_t->_seat_position.
        3.  SE VOCÊ AINDA NÃO IMPLEMENTOU O HOSTESS, COMECE POR ELE (VEJA O ARQUIVO `hostess.c`)!
        4.  O CLIENTE PODERÁ PEGAR COMIDA DE TRÊS POSSÍVEIS SLOTS: {i-1, i, i+1}, ONDE i É O ÍNDICE 
            POSICIONAL DO CLIENTE NA ESTEIRA (O ASSENTO ONDE ELE ESTÁ SENTADO).
        5.  NOTE QUE CLIENTES ADJACENTES DISPUTARÃO OS MESMOS PRATOS. CUIDADO COM PROBLEMAS DE SINCRONIZAÇÃO!
    */

   conveyor_belt_t* conveyor_belt = globals_get_conveyor_belt();
   enum menu_item food = conveyor_belt->_food_slots[food_slot];
   conveyor_belt->_food_slots[food_slot] = -1;

   /* Semáforo que diminui a espera ocupada do sushi_chef */
   sem_post(&conveyor_belt->pratos_sem);
   return food;

}

void customer_eat(customer_t* self, enum menu_item food) {
    /*
        MODIFIQUE ESSA FUNÇÃO PARA GARANTIR O COMPORTAMENTO CORRETO E EFICAZ DO CLIENTE.
        NOTAS:
        1.  ESSA FUNÇÃO JÁ VEM COM PARTE DO CÓDIGO PRONTA (OS SLEEPS PARA CADA TIPO DE ALIMENTO).
        2.  LEMBRE-SE DE DECREMENTAR OS ITENS DA LISTA DE DESEJOS DO CLIENTE CONFORME ELE CONSUMIR OS PRATOS.
        3.  A LISTA DE DESEJOS DO CLIENTE É UM ARRAY COM AS QUANTIDADES DESEJADAS DE CADA PRATO.
        4.  CADA PRATO DO MENU (VER ENUM `menu_item` NO ARQUIVO `menu.h` É REPRESENTADO POR UM INTEIRO),
            ENTÃO UM self->_wishes = [0,0,1,2,0] CONDIZ COM O DESEJO DE COMER 1 RAMÉN E 2 ONIGUIRIS.
    */

    self->_wishes[food]--;
    
    /* NÃO EDITE O CONTEÚDO ABAIXO */
    virtual_clock_t* global_clock = globals_get_virtual_clock();
    switch (food) {
        case Sushi:
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d started eating Sushi!\n", self->_id);
            msleep(SUSHI_PREP_TIME/global_clock->clock_speed_multiplier);
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d finished eating Sushi!\n", self->_id);
            break;
        case Dango:
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d started eating Dango!\n", self->_id);
            msleep(DANGO_PREP_TIME/global_clock->clock_speed_multiplier);
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d finished eating Dango!\n", self->_id);
            break;
        case Ramen:
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d started eating Ramen!\n", self->_id);
            msleep(RAMEN_PREP_TIME/global_clock->clock_speed_multiplier);
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d finished eating Ramen!\n", self->_id);
            break;
        case Onigiri:
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d started eating Onigiri!\n", self->_id);
            msleep(ONIGIRI_PREP_TIME/global_clock->clock_speed_multiplier);
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d finished eating Onigiri!\n", self->_id);
            break;
        case Tofu:
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d started eating Tofu!\n", self->_id);
            msleep(TOFU_PREP_TIME/global_clock->clock_speed_multiplier);
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d finished eating Tofu!\n", self->_id);
            break; 
        default:
            fprintf(stdout, RED "[ERROR] Invalid menu_item variant passed to `customer_eat()`.\n" NO_COLOR);
            exit(EXIT_FAILURE);
    }
}

void customer_leave(customer_t* self) {
    /*
        MODIFIQUE ESSA FUNÇÃO PARA GARANTIR O COMPORTAMENTO CORRETO E EFICAZ DO CLIENTE.
        NOTAS:
        1.  ESSA FUNÇÃO DEVERÁ REMOVER O CLIENTE DO ASSENTO DO CONVEYOR_BELT GLOBAL QUANDO EXECUTADA.
    */
    if (self->_seat_position != -1) {
        conveyor_belt_t* conveyor_belt = globals_get_conveyor_belt();
        conveyor_belt->_seats[self->_seat_position] = -1;

        /* Semáforo que impede a espera ocupada do hostess */
        sem_post(&conveyor_belt->vagas_sem);
    }

    customer_finalize(self);
}

customer_t* customer_init() {
    /* NÃO PRECISA ALTERAR ESSA FUNÇÃO */
    customer_t* self = malloc(sizeof(customer_t));
    if (self == NULL) {
        fprintf(stdout, RED "[ERROR] Bad malloc() at `customer_t* customer_init()`.\n" NO_COLOR);
        exit(EXIT_FAILURE);
    }
    self->_id = rand() % 1000;
    for (int i=0; i<=4; i++) {
        self->_wishes[i] = (rand() % 4);
    }
    self->_seat_position = -1;
    sem_init(&self->espera, 0, 0);
    pthread_create(&self->thread, NULL, customer_run, (void *) self);
    return self;
}

void customer_finalize(customer_t* self) {
    /* NÃO PRECISA ALTERAR ESSA FUNÇÃO */
    pthread_join(self->thread, NULL);
    sem_destroy(&self->espera);
    free(self);
}

void print_customer(customer_t* self) {
    /* NÃO PRECISA ALTERAR ESSA FUNÇÃO */
    print_virtual_time(globals_get_virtual_clock());
    fprintf(stdout, BROWN "[DEBUG] Customer " NO_COLOR "{\n");
    fprintf(stdout, BROWN "    _id" NO_COLOR ": %d\n", self->_id);
    fprintf(stdout, BROWN "    _wishes" NO_COLOR ": [%d, %d, %d, %d, %d]\n", self->_wishes[0], self->_wishes[1], self->_wishes[2], self->_wishes[3], self->_wishes[4]);
    fprintf(stdout, BROWN "    _seat_position" NO_COLOR ": %d\n", self->_seat_position);
    fprintf(stdout, NO_COLOR "}\n" NO_COLOR);
}
