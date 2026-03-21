#include "fractaler.hpp"
Params params = {};
int maxItrs = 100;
Plotter plot = nullptr;
Plotter plotters[] = {multibrot, julia};
void setPlotter(Algs alg) { plot = plotters[(int)alg]; }
int getColor(int itrs)
{
    if (itrs == maxItrs)
        return 0xFF000000;
    int c = (itrs * 255) / maxItrs;
    return (255 << 24) | (c << 16) | (c << 8) | c;
}
int multibrot(Complex c)
{
    int itrs = 0;
    Complex z{0, 0};
    while (z.mag2() <= BAILOUT && itrs < maxItrs)
    {
        z = z.power(params.P) + c;
        itrs++;
    }
    return getColor(itrs);
}
int julia(Complex z)
{
    int itrs = 0;
    Complex c{params.cx, params.cy};
    while (z.mag2() <= BAILOUT && itrs < maxItrs)
    {
        z = z.power(params.P) + c;
        itrs++;
    }
    return getColor(itrs);
}