#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int largura;
    int altura;
    int max_iter;
    int q_threads;
} Config;

int parser(const char *texto, int *saida){
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
        fprintf(stderr, "4 Argumentos esperados");
        return 0;
    }

    if (!parser(argv[1], &cfg->largura)) {
        fprintf(stderr, "Largura invalida [ERROR]");
        return 0;
    }
    if (!parser(argv[2], &cfg->altura)) {
        fprintf(stderr, "Altura invalida [ERROR]");
        return 0;
    }
    if (!parser(argv[3], &cfg->max_iter)) {
        fprintf(stderr, "Numero max de iterações invalido [ERROR]");
        return 0;
    }
    if (!parser(argv[4], &cfg->q_threads)) {
        fprintf(stderr, "Quantidade de threads invalida [ERROR]");
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[]){
    Config cfg;

    if (!erros(argc, argv, &cfg)) {
        return 1;
    }

    printf("Teste:\n");
    printf("  largura = %d, altura = %d, max inter = %d, num threads = %d\n", cfg.largura,cfg.altura,cfg.max_iter,cfg.q_threads);
}
