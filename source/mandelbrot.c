//mandelbrot.c
#include "config.h"

int mandelbrot(double cr,double ci, int max_iter){
    double zr = 0.0, zi = 0.0;
    int iter = 0;

    while (zr * zr + zi * zi <= 4 && iter < max_iter) {
        double zr_novo = zr * zr - zi * zi + cr;
        double zi_novo = 2 * zr * zi + ci;

        zr = zr_novo;
        zi = zi_novo;
        iter++;
    }

    return iter;
}
