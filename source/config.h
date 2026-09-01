//config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <stddef.h>

typedef struct{
    int largura;
    int altura;
    int max_iter;
    int q_threads;
} Config;

int mandelbrot(double cr,double ci, int max_iter);
void mandelbrot_serial(unsigned char *buffer, const Config *cfg);

unsigned char*aloca_buffer(int largura, int altura);
int make_pgm(const char *nome, const unsigned char *buffer, int largura, int altura);

#endif
