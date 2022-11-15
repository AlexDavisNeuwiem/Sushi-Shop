#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "args.h"
#include "customer.h"
#include "sushi_chef.h"
#include "hostess.h"
#include "globals.h"

int main (int argc, char** argv) {
    /* Read command line options */
    config_t config = parse(argc, argv);

    /* Setup random seed */
    srand(time(0));

    /* Inicializando os mutexes */
    pthread_mutex_init(globals_get_clientes_satisfeitos_mutex(), NULL);
    pthread_mutex_init(globals_get_sushi_cons_mutex(), NULL);
    pthread_mutex_init(globals_get_dango_cons_mutex(), NULL);
    pthread_mutex_init(globals_get_ramen_cons_mutex(), NULL);
    pthread_mutex_init(globals_get_onigiri_cons_mutex(), NULL);
    pthread_mutex_init(globals_get_tofu_cons_mutex(), NULL);

    /* Setup simulation virtual clock */
    globals_set_virtual_clock(virtual_clock_init(&config));

    /* Setup sushi conveyor belt */
    globals_set_conveyor_belt(conveyor_belt_init(&config));
    
    /* Init the Sushi Chef */
    sushi_chef_t* sushi_chef = sushi_chef_init();

    /* Setup customer queue */
    globals_set_queue(queue_init());

    /* Init the Hostess */
    hostess_t* hostess = hostess_init();

    /* Join threads and free used memory */
    hostess_finalize(hostess);
    sushi_chef_finalize(sushi_chef);
    
    virtual_clock_t* clock = globals_get_virtual_clock();
    msleep(5000/clock->clock_speed_multiplier);
    
    globals_finalize();

    /*Prints finais*/
    fprintf(stdout, GREEN "\n[INFO]" NO_COLOR " Quantidade de Clientes Satisfeitos: %d\n", globals_get_clientes_satisfeitos());
    fprintf(stdout, GREEN "[INFO]" NO_COLOR " SUSHI: %d produzidos e %d consumidos\n", globals_get_sushi_prod(), globals_get_sushi_cons());
    fprintf(stdout, GREEN "[INFO]" NO_COLOR " DANGO: %d produzidos e %d consumidos\n", globals_get_dango_prod(), globals_get_dango_cons());
    fprintf(stdout, GREEN "[INFO]" NO_COLOR " RAMEN: %d produzidos e %d consumidos\n", globals_get_ramen_prod(), globals_get_ramen_cons());
    fprintf(stdout, GREEN "[INFO]" NO_COLOR " ONIGIRI: %d produzidos e %d consumidos\n", globals_get_onigiri_prod(), globals_get_onigiri_cons());
    fprintf(stdout, GREEN "[INFO]" NO_COLOR " TOFU: %d produzidos e %d consumidos\n\n", globals_get_tofu_prod(), globals_get_tofu_cons());

    /*Destruindo os mutexes*/
    pthread_mutex_destroy(globals_get_clientes_satisfeitos_mutex());
    pthread_mutex_destroy(globals_get_sushi_cons_mutex());
    pthread_mutex_destroy(globals_get_dango_cons_mutex());
    pthread_mutex_destroy(globals_get_ramen_cons_mutex());
    pthread_mutex_destroy(globals_get_onigiri_cons_mutex());
    pthread_mutex_destroy(globals_get_tofu_cons_mutex());

    return EXIT_SUCCESS;
}
