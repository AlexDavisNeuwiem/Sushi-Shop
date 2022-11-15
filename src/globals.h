#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <pthread.h>

#include "conveyor_belt.h"
#include "virtual_clock.h"
#include "queue.h"

/**
 * @brief Inicia o estado do sushi shop (de modo global)
 * 
 * @param sushi_shop_fechado 
 */
extern void globals_set_sushi_shop_fechado(int sushi_shop_fechado);

/**
 * @brief Retorna o estado do sushi shop (de modo global)
 * 
 * @return int
 */
extern int globals_get_sushi_shop_fechado();

/**
 * @brief Retorna o mutex
 * 
 * @return pthread_mutex_t*
 */
extern pthread_mutex_t* globals_get_clientes_satisfeitos_mutex();

/**
 * @brief Inicia um contador de clientes satisfeiros (de modo global)
 * 
 * @param clientes_satisfeitos 
 */
extern void globals_set_clientes_satisfeitos(int clientes_satisfeitos);

/**
 * @brief Retorna um contador de clientes satisfeiros (de modo global)
 * 
 * @return int 
 */
extern int globals_get_clientes_satisfeitos();

/**
 * @brief Incrementa o contador de clientes satisfeiros (de modo global)
 * 
 *  
 */
extern void globals_add_clientes_satisfeitos();

/**
 * @brief Retorna o mutex
 * 
 * @return pthread_mutex_t*
 */
extern pthread_mutex_t* globals_get_sushi_cons_mutex();

/**
 * @brief Inicia um contador de alimentos (de modo global)
 * 
 * @param sushi
 */
extern void globals_set_sushi_cons(int sushi);

/**
 * @brief Retorna um contador de alimentos (de modo global)
 * 
 * @return int
 */
extern int globals_get_sushi_cons();

/**
 * @brief Incrementa o contador de alimentos (de modo global)
 * 
 * 
 */
extern void globals_add_sushi_cons();

/**
 * @brief Inicia um contador de alimentos (de modo global)
 * 
 * @param sushi
 */
extern void globals_set_sushi_prod(int sushi);

/**
 * @brief Retorna um contador de alimentos (de modo global)
 * 
 * @return int
 */
extern int globals_get_sushi_prod();

/**
 * @brief Incrementa o contador de alimentos (de modo global)
 * 
 * 
 */
extern void globals_add_sushi_prod();

/**
 * @brief Retorna o mutex
 * 
 * @return pthread_mutex_t*
 */
extern pthread_mutex_t* globals_get_dango_cons_mutex();

/**
 * @brief Inicia um contador de alimentos (de modo global)
 * 
 * @param dango
 */
extern void globals_set_dango_cons(int dango);

/**
 * @brief Retorna um contador de alimentos (de modo global)
 * 
 * @return int
 */
extern int globals_get_dango_cons();

/**
 * @brief Incrementa o contador de alimentos (de modo global)
 * 
 * 
 */
extern void globals_add_dango_cons();

/**
 * @brief Inicia um contador de alimentos (de modo global)
 * 
 * @param dango
 */
extern void globals_set_dango_prod(int dango);

/**
 * @brief Retorna um contador de alimentos (de modo global)
 * 
 * @return int
 */
extern int globals_get_dango_prod();

/**
 * @brief Incrementa o contador de alimentos (de modo global)
 * 
 * 
 */
extern void globals_add_dango_prod();

/**
 * @brief Retorna o mutex
 * 
 * @return pthread_mutex_t*
 */
extern pthread_mutex_t* globals_get_ramen_cons_mutex();

/**
 * @brief Inicia um contador de alimentos (de modo global)
 * 
 * @param ramen
 */
extern void globals_set_ramen_cons(int ramen);

/**
 * @brief Retorna um contador de alimentos (de modo global)
 * 
 * @return int
 */
extern int globals_get_ramen_cons();

/**
 * @brief Incrementa o contador de alimentos (de modo global)
 * 
 * 
 */
extern void globals_add_ramen_cons();

/**
 * @brief Inicia um contador de alimentos (de modo global)
 * 
 * @param ramen
 */
extern void globals_set_ramen_prod(int ramen);

/**
 * @brief Retorna um contador de alimentos (de modo global)
 * 
 * @return int
 */
extern int globals_get_ramen_prod();

/**
 * @brief Incrementa o contador de alimentos (de modo global)
 * 
 * 
 */
extern void globals_add_ramen_prod();

/**
 * @brief Retorna o mutex
 * 
 * @return pthread_mutex_t*
 */
extern pthread_mutex_t* globals_get_onigiri_cons_mutex();

/**
 * @brief Inicia um contador de alimentos (de modo global)
 * 
 * @param onigiri
 */
extern void globals_set_onigiri_cons(int onigiri);

/**
 * @brief Retorna um contador de alimentos (de modo global)
 * 
 * @return int
 */
extern int globals_get_onigiri_cons();

/**
 * @brief Incrementa o contador de alimentos (de modo global)
 * 
 * 
 */
extern void globals_add_onigiri_cons();

/**
 * @brief Inicia um contador de alimentos (de modo global)
 * 
 * @param onigiri
 */
extern void globals_set_onigiri_prod(int onigiri);

/**
 * @brief Retorna um contador de alimentos (de modo global)
 * 
 * @return int
 */
extern int globals_get_onigiri_prod();

/**
 * @brief Incrementa o contador de alimentos (de modo global)
 * 
 * 
 */
extern void globals_add_onigiri_prod();

/**
 * @brief Retorna o mutex
 * 
 * @return pthread_mutex_t*
 */
extern pthread_mutex_t* globals_get_tofu_cons_mutex();

/**
 * @brief Inicia um contador de alimentos (de modo global)
 * 
 * @param tofu
 */
extern void globals_set_tofu_cons(int tofu);

/**
 * @brief Retorna um contador de alimentos (de modo global)
 * 
 * @return int
 */
extern int globals_get_tofu_cons();

/**
 * @brief Incrementa o contador de alimentos (de modo global)
 * 
 * 
 */
extern void globals_add_tofu_cons();

/**
 * @brief Inicia um contador de alimentos (de modo global)
 * 
 * @param tofu
 */
extern void globals_set_tofu_prod(int tofu);

/**
 * @brief Retorna um contador de alimentos (de modo global)
 * 
 * @return int
 */
extern int globals_get_tofu_prod();

/**
 * @brief Incrementa o contador de alimentos (de modo global)
 * 
 * 
 */
extern void globals_add_tofu_prod();

/**
 * @brief Inicia um relógio virtual (de modo global)
 * 
 * @param virtual_clock 
 */
extern void globals_set_virtual_clock(virtual_clock_t *virtual_clock);

/**
 * @brief Retorna um relógio virtual (de modo global)
 * 
 * @return virtual_clock_t* 
 */
extern virtual_clock_t *globals_get_virtual_clock();

/**
 * @brief Inicia uma esteira de sushi (de modo global).
 * 
 * @param conveyor_belt
 */
extern void globals_set_conveyor_belt(conveyor_belt_t *conveyor_belt);

/**
 * @brief Retorna uma esteira de sushi (de modo global)
 * 
 * @return conveyor_belt_t* 
 */
extern conveyor_belt_t *globals_get_conveyor_belt();

/**
 * @brief Inicia uma fila (de modo global)
 * 
 * @param queue 
 */
extern void globals_set_queue(queue_t *queue);

/**
 * @brief Retorna uma fila (de modo global)
 * 
 * @return queue_t* 
 */
extern queue_t *globals_get_queue();

/**
 * @brief Finaliza todas as variáveis globais.
 * 
 */
extern void globals_finalize();

#endif  // __GLOBALS_H__
