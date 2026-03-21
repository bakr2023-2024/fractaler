#include "fractaler.hpp"
Params params = {2, 2};
double maxItrs = 100;
Plotter plot = nullptr;
int getColor(int itrs)
{
    if (itrs == maxItrs)
        return 0xFF000000;
    int c = (itrs * 255) / maxItrs;
    return (255 << 24) | (c << 16) | (c << 8) | c;
}
void setPlotter(Algs alg)
{
    plot = alg == MANDELBROT ? mandelbrot : nullptr;
}
int mandelbrot(Complex c)
{
    Complex z{0, 0};
    int itrs = 0;
    while (z.x * z.x + z.y * z.y <= BAILOUT && itrs < maxItrs)
    {
        z = z.power(params.P) + c;
        itrs++;
    }
    return getColor(itrs);
}
