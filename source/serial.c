//serial.c
#include "config.h"

void mandelbrot_serial(unsigned char *buffer, const Config *cfg){
    for (long lin = 0; lin < cfg->altura; lin++){
        double cy = -1.5 + lin * (1.5 - (-1.5)) / cfg->altura;
        for (long col = 0; col < cfg->largura; col++) {
            double cx = -2.0 + col * (1.0 - (-2.0)) / cfg->largura;

            int iter = mandelbrot(cx, cy, cfg->max_iter);

            unsigned char intensidade = (unsigned char)((double)iter / cfg->max_iter * 255.0);

            size_t indice = (size_t)lin * cfg-> largura + col;
            buffer[indice] = intensidade;
        }
    }
}
