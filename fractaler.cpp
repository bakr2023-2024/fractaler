#include "fractaler.hpp"
int Fractaler::getColor(int itrs)
{
    if (itrs == maxItrs)
        return 0xFF000000;
    int c = (itrs * 255) / maxItrs;
    return (255 << 24) | (c << 16) | (c << 8) | c;
}
int Fractaler::mandelbrot(Complex c)
{
    Complex z{0, 0};
    int itrs = 0;
    while (z.x * z.x + z.y * z.y <= BAILOUT && itrs < maxItrs)
    {
        z = z * z + c;
        itrs++;
    }
    return getColor(itrs);
}