#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

typedef struct{
    unsigned char *buffer;
    const Config *cfg;
    int linha_ini;
    int linha_fim;
} TaskThread;

static void *calculo(void *arg){
    TaskThread *tarefa = (TaskThread *)arg;
    const Config *cfg = tarefa->cfg;

    for (int lin = tarefa->linha_ini; lin < tarefa->linha_fim; lin++){
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

void mandelbrot_pthreads1(unsigned char *buffer, const Config *cfg){
    int n = cfg->q_threads;

    if (n > cfg->altura) {
        n = cfg->altura;
    }

    pthread_t *threads = malloc((size_t)n * sizeof(pthread_t));
    TaskThread *tarefas = malloc((size_t)n * sizeof(TaskThread));
    if (threads == NULL || tarefas == NULL) {
        fprintf(stderr, "Falha ao alocar threads [ERROR]\n");
        free(threads);
        free(tarefas);
    }

    int linhas_thread = cfg->altura / n;
    int resto = cfg->altura % n;
    int linha_atual = 0;

    for (int i = 0; i < n; i++) {
        int quantidade = linhas_thread + (i < resto ? 1 : 0);

        tarefas[i].buffer = buffer;
        tarefas[i].cfg = cfg;
        tarefas[i].linha_ini = linha_atual;
        tarefas[i].linha_fim = linha_atual + quantidade;

        pthread_create(&threads[i], NULL, calculo, &tarefas[i]);

        linha_atual += quantidade;
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    free(tarefas);
}
