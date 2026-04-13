#include "fractaler.hpp"
Params params = {};
int maxItrs = 100;
double tol = 0.00001;
Plotter plot = nullptr;
Plotter plotters[] = {multibrot, julia, burningShip, newton, nova, sin, sinh, newtonCosh, collatz, septagon, magnet1, magnet2, cactus, lambda, barnsleyTree, rings};
void setPlotter(int choice)
{
    if (choice == 3 || choice == 4)
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
int nova(const Complex &c)
{
    Complex z = params.λ == 0 ? c : Complex{params.cx, params.cy};
    Complex zp = z;
    Complex a{params.P, params.Q};
    int itrs = 0;
    while (itrs < maxItrs)
    {
        z = zp - (a * (params.poly.substitute(zp) / params.polyd.substitute(zp))) + c;
        if (abs(z.x - zp.x) < tol && abs(z.y - zp.y) < tol)
            break;
        zp = z;
        itrs++;
    }
    return getColor(itrs);
}
int sin(const Complex &z)
{
    Complex c{params.cx, params.cy};
    Complex zn = z;
    int itrs = 0;
    if (params.λ != 0)
    {
        double b = params.λ * BAILOUT;
        while (abs(zn.y) < b && itrs < maxItrs)
        {
            zn = zn.sine().power(params.P) + c;
            itrs++;
        }
    }
    else
    {
        while (zn.mag2() <= BAILOUT && itrs < maxItrs)
        {
            zn = zn.sine().power(params.P) * c;
            itrs++;
        }
    }
    return getColor(itrs);
}
int sinh(const Complex &z)
{
    Complex zn = z;
    Complex c{params.cx, params.cy};
    int itrs = 0;
    if (params.λ != 0)
    {
        double b = params.λ * BAILOUT;
        while (abs(zn.y) < b && itrs < maxItrs)
        {
            zn = zn.sineh().power(params.P) + c;
            itrs++;
        }
    }
    else
    {
        while (zn.mag2() <= BAILOUT && itrs < maxItrs)
        {
            zn = zn.sineh().power(params.P) + c;
            itrs++;
        }
    }
    return getColor(itrs);
}
int newtonCosh(const Complex &z)
{
    Complex z0 = z;
    Complex zn = z;
    int itrs = 0;
    double t = tol / BAILOUT;
    while (itrs < maxItrs)
    {
        zn = zn - ((zn.cosineh().minus(1, 0)) / zn.sineh());
        if (max(abs(zn.x - z0.x), abs(zn.y - z0.y)) < t)
            break;
        z0 = zn;
        itrs++;
    }
    return getColor(itrs);
}
int collatz(const Complex &z)
{
    Complex zn = z;
    int itrs = 0;
    while (abs(zn.y) < BAILOUT && itrs < maxItrs)
    {
        zn = (zn.multiply(4).plus(1, 0) - (zn.multiply(2).plus(1, 0) * (zn.multiply(M_PI, 0).cosine()))).divide(4);
        itrs++;
    }
    return getColor(itrs);
}
int septagon(const Complex &z)
{
    double phi = -0.7 / 5;
    Complex zn = z;
    int itrs = 0;
    while (zn.mag2() <= BAILOUT && itrs < maxItrs)
    {
        zn = zn.power(7).plus(phi) / zn;
        itrs++;
    }
    return getColor(itrs);
}
int magnet1(const Complex &c)
{
    Complex z = params.λ == 0 ? Complex{0, 0} : c;
    Complex cp = params.λ == 0 ? c : Complex{params.cx, params.cy};
    int itrs = 0;
    while (z.mag2() <= BAILOUT && itrs < maxItrs)
    {
        Complex numer = z.power(2) + (c).minus(1);
        Complex denom = z.multiply(2) + (c).minus(2);
        z = (numer / denom).power(2);
        itrs++;
    }
    return getColor(itrs);
}
int magnet2(const Complex &c)
{
    Complex z = params.λ == 0 ? Complex{0, 0} : c;
    Complex cp = params.λ == 0 ? c : Complex{params.cx, params.cy};
    int itrs = 0;
    while (z.mag2() <= BAILOUT && itrs < maxItrs)
    {
        Complex c1 = c.minus(1);
        Complex c2 = c.minus(2);
        Complex z2 = z.power(2);
        Complex z3 = z2 * z;
        Complex c1c2 = c1 * c2;
        Complex zzz = z.multiply(3);
        Complex numer = z3 + zzz * (c1) + c1c2;
        Complex denom = z2.multiply(3) + (zzz * c2) + c1c2.plus(1);
        z = (numer / denom).power(2);
        itrs++;
    }
    return getColor(itrs);
}
int cactus(const Complex &z)
{
    Complex zn = z;
    int itrs = 0;
    while (zn.mag2() <= BAILOUT && itrs < maxItrs)
    {
        zn = zn.power(3) + zn * (z.minus(1)) - z;
        itrs++;
    }
    return getColor(itrs);
}
int lambda(const Complex &z)
{
    Complex zn = z;
    int itrs = 0;
    Complex c = {1, 0};
    Complex a = {params.cx, params.cy};
    while (zn.mag() <= BAILOUT && itrs < maxItrs)
    {
        zn = a * zn * (c - zn);
        itrs++;
    }
    return getColor(itrs);
}
int barnsleyTree(const Complex &z)
{
    Complex zn = z;
    int itrs = 0;
    Complex a{params.cx, params.cy};
    while (zn.mag2() <= BAILOUT && itrs < maxItrs)
    {
        int sign = (zn.x > 0) - (zn.x < 0);
        zn = a * (zn.minus(sign));
        itrs++;
    }
    return getColor(itrs);
}
int rings(const Complex &z)
{
    Complex zn = z;
    int itrs = 0;
    double phi = 1 + sqrt(5) / 2;
    double sigma = sqrt(params.P);
    double theta = 2 * M_PI * phi;
    Complex e{cos(theta), sin(theta)};
    while (zn.mag2() <= BAILOUT && itrs < maxItrs)
    {
        Complex z2 = zn * zn;
        zn = (z2 * (z2.plus(sigma)) * e) / (z2.multiply(sigma).plus(1));
        itrs++;
    }
    return getColor(itrs);
}
