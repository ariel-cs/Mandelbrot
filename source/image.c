//image.c
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

unsigned char *aloca_buffer(int largura, int altura){
    size_t total = (size_t)largura * (size_t)altura;
    unsigned char *buffer = malloc(total);
    if (buffer == NULL) {
        fprintf(stderr, "Falha em alocar imagem\n");
    }
    return buffer;
}

int make_pgm(const char *nome, const unsigned char *buffer, int largura, int altura){
    FILE *f = fopen(nome, "w");
    if (f == NULL) {
        fprintf(stderr, "Falha em criar arquivo [ERROR]\n");
        return 0;
    }

    for (int linha = 0; linha < altura; linha++) {
        for (int col = 0; col < largura; col++) {
            size_t indice = (size_t)linha * largura + col;
            fprintf(f, "%d", buffer[indice]);
            if (col < largura - 1) {
                fprintf(f, " ");
            }
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 1;

}
