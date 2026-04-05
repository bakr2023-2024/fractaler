#include "fractaler.hpp"
Params params = {};
int maxItrs = 100;
double tol = 0.00001;
Plotter plot = nullptr;
Plotter plotters[] = {multibrot, julia, burningShip, newton};
void setPlotter(int choice)
{
    if (choice == 3)
    {
        params.poly.parse();
        params.polyd = params.poly.differentiate();
    }
    plot = plotters[choice];
}
int getColor(int itrs)
{
    if (itrs == maxItrs)
        return 0xFF000000;
    int c = (itrs * 255) / maxItrs;
    return (255 << 24) | (c << 16) | (c << 8) | c;
}
int multibrot(const Complex &c)
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
int julia(const Complex &zn)
{
    int itrs = 0;
    Complex c{params.cx, params.cy};
    Complex z = zn;
    while (z.mag2() <= BAILOUT && itrs < maxItrs)
    {
        z = z.power(params.P) + c;
        itrs++;
    }
    return getColor(itrs);
}
int burningShip(const Complex &zn)
{
    int itrs = 0;
    Complex z = zn;
    Complex c = (params.cx == 0 && params.cy == 0) ? z : Complex{params.cx, params.cy};
    while (z.mag2() <= BAILOUT && itrs < maxItrs)
    {
        z = Complex{abs(z.x), -abs(z.y)}.power(params.P) + c;
        itrs++;
    }
    return getColor(itrs);
}
int newton(const Complex &zn)
{
    Complex z = zn;
    Complex zp{z.x, z.y};

    int itrs = 0;
    while (itrs < maxItrs)
    {
        z = zp - (params.poly.substitute(zp) / params.polyd.substitute(zp));
        if (abs(z.x - zp.x) < tol && abs(z.y - zp.y) < tol)
            break;
        zp = z;
        itrs++;
    }
    return getColor(itrs);
}