//main.c
#include <bits/time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"


static int parser(const char *texto, int *saida){
    char *fim;
    long valor = strtol(texto, &fim, 10);

    if(fim == texto){
        return 0;
    }
    if (*fim != '\0'){
        return 0;
    }
    if (valor <= 0 || valor > INT_MAX) {
        return 0;
    }

    *saida = (int)valor;
    return 1;
}

int erros(int argc, char *argv[], Config *cfg) {
    if (argc != 5) {
        fprintf(stderr, "4 Argumentos esperados\n");
        return 0;
    }

    if (!parser(argv[1], &cfg->largura)) {
        fprintf(stderr, "Largura invalida [ERROR]\n");
        return 0;
    }
    if (!parser(argv[2], &cfg->altura)) {
        fprintf(stderr, "Altura invalida [ERROR]\n");
        return 0;
    }
    if (!parser(argv[3], &cfg->max_iter)) {
        fprintf(stderr, "Numero max de iterações invalido [ERROR]\n");
        return 0;
    }
    if (!parser(argv[4], &cfg->q_threads)) {
        fprintf(stderr, "Quantidade de threads invalida [ERROR]\n");
        return 0;
    }

    return 1;
}


static double roda_serial(const Config *cfg, unsigned char *buffer){
    struct timespec inicio, fim;

    clock_gettime(CLOCK_MONOTONIC, &inicio);
    mandelbrot_serial(buffer, cfg);
    clock_gettime(CLOCK_MONOTONIC, &fim);

    double segundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    return segundos;
}

int main(int argc, char *argv[]) {
    Config cfg;

    if (!erros(argc, argv, &cfg)) {
        return 1;
    }

    unsigned char *buffer = aloca_buffer(cfg.largura, cfg.altura);
    if (buffer == NULL) {
        return 1;
    }

    double tempo_serial = roda_serial(&cfg, buffer);

    if (!make_pgm("mandelbrot_aco4_serial.pgm", buffer, cfg.largura, cfg.altura)) {
        free(buffer);
        return 1;
    }

    FILE *tempos = fopen("times.txt", "w");
    if (tempos == NULL) {
        fprintf(stderr, "Falha em criar times.txt [ERROR]\n");
        free(buffer);
        return 1;
    }
    fprintf(tempos, "Serial: %.6f segundos\n", tempo_serial);
    fclose(tempos);

    free(buffer);
    return 0;
}
