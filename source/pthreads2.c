#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

typedef struct{
    unsigned char *buffer;
    const Config *cfg;
    int *prox;
    pthread_mutex_t *mutex;
} TaskThread2;

static void *calculo2(void *arg){
    TaskThread2 *tarefa = (TaskThread2 *)arg;
    const Config *cfg = tarefa->cfg;

    while (1) {
        pthread_mutex_lock(tarefa->mutex);
        int lin = *(tarefa->prox);
        if (lin < cfg->altura) {
            (*(tarefa->prox))++;
        }
        pthread_mutex_unlock(tarefa->mutex);

        if (lin >= cfg->altura) {
            break;
        }

        double ci = IMAG_MIN + lin * (IMAG_MAX - (IMAG_MIN)) / cfg->altura;

        for (int col = 0; col < cfg->largura; col++) {
            double cr = REAL_MIN + col * (REAL_MAX - (REAL_MIN)) / cfg->largura;

            int iter = mandelbrot(cr, ci, cfg->max_iter);

            unsigned char intensidade = (unsigned char)((double)iter / cfg->max_iter * 255.0);

            size_t indice = (size_t)lin * cfg->largura + col;
            tarefa->buffer[indice] = intensidade;
        }
    }
    return NULL;
}

void mandelbrot_pthreads2(unsigned char *buffer, const Config *cfg){
    int n = cfg->q_threads;

    if (n > cfg->altura) {
        n = cfg->altura;
    }

    pthread_t *threads = malloc((size_t)n * sizeof(pthread_t));
    TaskThread2 *tarefas = malloc((size_t)n * sizeof(TaskThread2));
    if (threads == NULL || tarefas == NULL) {
        fprintf(stderr, "Falha ao alocar threads [ERROR]\n");
        free(threads);
        free(tarefas);
    }

    int prox_lin = 0;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    for (int i = 0; i < n; i++) {

        tarefas[i].buffer = buffer;
        tarefas[i].cfg = cfg;
        tarefas[i].prox = &prox_lin;
        tarefas[i].mutex = &mutex;

        pthread_create(&threads[i], NULL, calculo2, &tarefas[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    free(threads);
    free(tarefas);
}
