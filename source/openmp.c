//openmp.c
#include "config.h"

void mandelbrot_openmp(unsigned char *buffer, const Config *cfg){

    #pragma omp parallel for num_threads(cfg->q_threads) schedule(static)

    for (int lin = 0; lin < cfg->altura; lin++){
        double ci = IMAG_MIN + lin * (IMAG_MAX - (IMAG_MIN)) / cfg->altura;
        for (int col = 0; col < cfg->largura; col++) {
            double cr = REAL_MIN + col * (REAL_MAX - (REAL_MIN)) / cfg->largura;

            int iter = mandelbrot(cr, ci, cfg->max_iter);

            unsigned char intensidade = (unsigned char)((double)iter / cfg->max_iter * 255.0);

            size_t indice = (size_t)lin * cfg-> largura + col;
            buffer[indice] = intensidade;
        }
    }
}
