int mandelbrot(double cr,double ci, int max_inter){
    double zr = 0.0, zi = 0.0;
    int inter = 0;

    while (zr * zr + zi * zi <= 4 && inter < max_inter) {
        double zr_novo = zr * zr - zi * zi + cr;
        double zi_novo = 2 * zr * zi + ci;

        zr = zr_novo;
        zi = zi_novo;
        inter++;
    }

    return inter;
}
