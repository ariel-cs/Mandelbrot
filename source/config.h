//config.h
#ifndef CONFIG_H
#define CONFIG_H

#define REAL_MIN -2.0
#define REAL_MAX 1.0
#define IMAG_MIN -1.5
#define IMAG_MAX 1.5

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
