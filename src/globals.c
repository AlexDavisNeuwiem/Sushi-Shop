#include <stdlib.h>

#include "globals.h"

/*
    VOCÊ DEVE CRIAR VARIÁVEIS GLOBAIS PARA ARMAZENAR DADOS SOBRE A SIMULAÇÃO.
    NOTAS:
    1.  OS SEGUINTES DADOS DEVEM SER ARMAZENADOS E PRINTADOS AO FIM DA SIMULAÇÃO:
        a. Quantidade de clientes que sentaram-se no conveyor e consumiram todos os itens desejados
        b. Quantidades produzidas de cada alimento
        c. Quantidades consumidas de cada alimento
    2.  SIGA OS EXEMPLOS DE VARIÁVEIS GLOBAIS JÁ EXISTENTES NESSE ARQUIVO PARA CRIAR AS NOVAS.
*/

/*Fechamento do Restaurante*/
int global_sushi_shop_fechado = 0;

void globals_set_sushi_shop_fechado(int sushi_shop_fechado) {
    global_sushi_shop_fechado = sushi_shop_fechado;
}

int globals_get_sushi_shop_fechado() {
    return global_sushi_shop_fechado;
}

/*Total Clientes Satisfeitos*/
int global_clientes_satisfeitos = 0;
pthread_mutex_t global_clientes_satisfeitos_mutex;

pthread_mutex_t* globals_get_clientes_satisfeitos_mutex() {
    return &global_clientes_satisfeitos_mutex;
}

void globals_set_clientes_satisfeitos(int clientes_satisfeitos) {
    global_clientes_satisfeitos = clientes_satisfeitos;
}

int globals_get_clientes_satisfeitos() {
    return global_clientes_satisfeitos;
}

void globals_add_clientes_satisfeitos() {
    global_clientes_satisfeitos++;
}

/*Globais Sushi*/
int global_sushi_cons = 0;
pthread_mutex_t global_sushi_cons_mutex;
int global_sushi_prod = 0;

pthread_mutex_t* globals_get_sushi_cons_mutex() {
    return &global_sushi_cons_mutex;
}

void globals_set_sushi_cons(int sushi) {
    global_sushi_cons = sushi;
}

int globals_get_sushi_cons() {
    return global_sushi_cons;
}

void globals_add_sushi_cons() {
    global_sushi_cons++;
}

void globals_set_sushi_prod(int sushi) {
    global_sushi_prod = sushi;
}

int globals_get_sushi_prod() {
    return global_sushi_prod;
}

void globals_add_sushi_prod() {
    global_sushi_prod++;
}

/*Globais Dango*/
int global_dango_cons = 0;
pthread_mutex_t global_dango_cons_mutex;
int global_dango_prod = 0;

pthread_mutex_t* globals_get_dango_cons_mutex() {
    return &global_dango_cons_mutex;
}

void globals_set_dango_cons(int dango) {
    global_dango_cons = dango;
}

int globals_get_dango_cons() {
    return global_dango_cons;
}

void globals_add_dango_cons() {
    global_dango_cons++;
}

void globals_set_dango_prod(int dango) {
    global_dango_prod = dango;
}

int globals_get_dango_prod() {
    return global_dango_prod;
}

void globals_add_dango_prod() {
    global_dango_prod++;
}

/*Globais Ramen*/
int global_ramen_cons = 0;
pthread_mutex_t global_ramen_cons_mutex;
int global_ramen_prod = 0;

pthread_mutex_t* globals_get_ramen_cons_mutex() {
    return &global_ramen_cons_mutex;
}

void globals_set_ramen_cons(int ramen) {
    global_ramen_cons = ramen;
}

int globals_get_ramen_cons() {
    return global_ramen_cons;
}

void globals_add_ramen_cons() {
    global_ramen_cons++;
}

void globals_set_ramen_prod(int ramen) {
    global_ramen_prod = ramen;
}

int globals_get_ramen_prod() {
    return global_ramen_prod;
}

void globals_add_ramen_prod() {
    global_ramen_prod++;
}

/*Globais Onigiri*/
int global_onigiri_cons = 0;
pthread_mutex_t global_onigiri_cons_mutex;
int global_onigiri_prod = 0;

pthread_mutex_t* globals_get_onigiri_cons_mutex() {
    return &global_onigiri_cons_mutex;
}

void globals_set_onigiri_cons(int onigiri) {
    global_onigiri_cons = onigiri;
}

int globals_get_onigiri_cons() {
    return global_onigiri_cons;
}

void globals_add_onigiri_cons() {
    global_onigiri_cons++;
}

void globals_set_onigiri_prod(int onigiri) {
    global_onigiri_prod = onigiri;
}

int globals_get_onigiri_prod() {
    return global_onigiri_prod;
}

void globals_add_onigiri_prod() {
    global_onigiri_prod++;
}

/*Globais Tofu*/
int global_tofu_cons = 0;
pthread_mutex_t global_tofu_cons_mutex;
int global_tofu_prod = 0;

pthread_mutex_t* globals_get_tofu_cons_mutex() {
    return &global_tofu_cons_mutex;
}

void globals_set_tofu_cons(int tofu) {
    global_tofu_cons = tofu;
}

int globals_get_tofu_cons() {
    return global_tofu_cons;
}

void globals_add_tofu_cons() {
    global_tofu_cons++;
}

void globals_set_tofu_prod(int tofu) {
    global_tofu_prod = tofu;
}

int globals_get_tofu_prod() {
    return global_tofu_prod;
}

void globals_add_tofu_prod() {
    global_tofu_prod++;
}

virtual_clock_t* global_virtual_clock = NULL;
conveyor_belt_t* global_conveyor_belt = NULL;
queue_t* global_queue = NULL;

void globals_set_virtual_clock(virtual_clock_t* virtual_clock) {
    global_virtual_clock = virtual_clock;
}

virtual_clock_t* globals_get_virtual_clock() {
    return global_virtual_clock;
}

void globals_set_conveyor_belt(conveyor_belt_t* conveyor_belt) {
    global_conveyor_belt = conveyor_belt;
}

conveyor_belt_t* globals_get_conveyor_belt() {
    return global_conveyor_belt;
}

void globals_set_queue(queue_t* queue) {
    global_queue = queue;
}

queue_t* globals_get_queue() {
    return global_queue;
}

/**
 * @brief Finaliza todas as variáveis globais.
 * Se criar alguma variável global que faça uso de mallocs, lembre-se sempre 
 * de usar o free dentro dessa função.
 */
void globals_finalize() {
    conveyor_belt_finalize(global_conveyor_belt);
    virtual_clock_finalize(global_virtual_clock);
}
