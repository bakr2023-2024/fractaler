#include "fractaler.hpp"
static Params params;
static Plotter plotter;
static Polynomial poly, polyd;
static double tol = 0.00001;
static Plotter plotters[] = {multibrot, julia, burningShip, newton, nova, sine, sineh, newtonCosh,
                             collatz, septagon, magnet1, magnet2, cactus, lambda, barnsleyTree,
                             rings, rogerRational, spiralJulia, tetration, tripleDragon, iabs};

void setParams(Params parameters)
{
    params = parameters;
    if (params.algChoice == 3 || params.algChoice == 4)
    {
        poly.parse(params.polyStr);
        polyd = poly.differentiate();
    }
    plotter = plotters[params.algChoice];
}
Plotter getPlotter() { return plotter; };

int multibrot(const Complex &c)
{
    int itrs = 0;
    Complex z{0, 0};
    while (z.mag2() <= BAILOUT && itrs < params.maxItrs)
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
    while (z.mag2() <= BAILOUT && itrs < params.maxItrs)
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
    while (z.mag2() <= BAILOUT && itrs < params.maxItrs)
    {
        z = Complex{abs(z.x), -fabs(z.y)}.power(params.P) + c;
        itrs++;
    }
    return getColor(itrs);
}
int newton(const Complex &zn)
{
    Complex z = zn;
    Complex zp{z.x, z.y};

    int itrs = 0;
    while (itrs < params.maxItrs)
    {
        z = zp - (poly.substitute(zp) / polyd.substitute(zp));
        if (fabs(z.x - zp.x) < tol && fabs(z.y - zp.y) < tol)
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
    while (itrs < params.maxItrs)
    {
        z = zp - (a * (poly.substitute(zp) / polyd.substitute(zp))) + c;
        if (abs(z.x - zp.x) < tol && abs(z.y - zp.y) < tol)
            break;
        zp = z;
        itrs++;
    }
    return getColor(itrs);
}
int sine(const Complex &z)
{
    Complex c{params.cx, params.cy};
    Complex zn = z;
    int itrs = 0;
    if (params.λ != 0)
    {
        double b = params.λ * BAILOUT;
        while (fabs(zn.y) < b && itrs < params.maxItrs)
        {
            zn = zn.sine().power(params.P) + c;
            itrs++;
        }
    }
    else
    {
        while (zn.mag2() <= BAILOUT && itrs < params.maxItrs)
        {
            zn = zn.sine().power(params.P) * c;
            itrs++;
        }
    }
    return getColor(itrs);
}
int sineh(const Complex &z)
{
    Complex zn = z;
    Complex c{params.cx, params.cy};
    int itrs = 0;
    if (params.λ != 0)
    {
        double b = params.λ * BAILOUT;
        while (fabs(zn.y) < b && itrs < params.maxItrs)
        {
            zn = zn.sineh().power(params.P) + c;
            itrs++;
        }
    }
    else
    {
        while (zn.mag2() <= BAILOUT && itrs < params.maxItrs)
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
    while (itrs < params.maxItrs)
    {
        zn = zn - ((zn.cosineh().minus(1, 0)) / zn.sineh());
        if (max(fabs(zn.x - z0.x), fabs(zn.y - z0.y)) < t)
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
    while (fabs(zn.y) < BAILOUT && itrs < params.maxItrs)
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
    while (zn.mag2() <= BAILOUT && itrs < params.maxItrs)
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
    while (z.mag2() <= BAILOUT && itrs < params.maxItrs)
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
    while (z.mag2() <= BAILOUT && itrs < params.maxItrs)
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
    while (zn.mag2() <= BAILOUT && itrs < params.maxItrs)
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
    while (zn.mag() <= BAILOUT && itrs < params.maxItrs)
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
    while (zn.mag2() <= BAILOUT && itrs < params.maxItrs)
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
    while (zn.mag2() <= BAILOUT && itrs < params.maxItrs)
    {
        Complex z2 = zn * zn;
        zn = (z2 * (z2.plus(sigma)) * e) / (z2.multiply(sigma).plus(1));
        itrs++;
    }
    return getColor(itrs);
}
int rogerRational(const Complex &z)
{
    Complex zn = z;
    double mag = zn.mag();
    int itrs = 0;
    Complex a{1, 0};
    while (mag * mag <= BAILOUT && itrs < params.maxItrs)
    {
        Complex gz = a / (zn.multiply(params.P));
        Complex g3z = gz * gz * gz;
        Complex g5z = g3z * gz * gz;
        Complex g7z = g5z * gz * gz;
        zn = (zn * zn) * (gz + a) * (g3z + a) * (g5z + a) * (g7z + a) + (Complex{mag, 1} / Complex{1 + mag, 0});
        mag = zn.mag();
        itrs++;
    }
    return getColor(itrs);
}
int spiralJulia(const Complex &z)
{
    Complex zn = z;
    Complex c{params.cx, params.cy};
    int itrs = 0;
    while (zn.mag2() <= BAILOUT && itrs < params.maxItrs)
    {
        zn = (zn * zn + c).tangent();
        itrs++;
    }
    return getColor(itrs);
}
int tetration(const Complex &z)
{
    Complex zn = z;
    int itrs = 0;
    while (zn.x <= BAILOUT && z.y <= BAILOUT && itrs < params.maxItrs)
    {
        zn = z ^ zn;
        itrs++;
    }
    return getColor(itrs);
}
int tripleDragon(const Complex &z)
{
    Complex zn = z;
    Complex c{params.cx, params.cy};
    int itrs = 0;
    while (zn.mag2() <= BAILOUT && itrs < params.maxItrs)
    {
        Complex z3 = zn.power(3);
        zn = (z3 / (z3.plus(1))) + c;
        itrs++;
    }
    return getColor(itrs);
}
int iabs(const Complex &z)
{
    Complex zn = z;
    Complex c{params.cx, params.cy};
    int itrs = 0;
    Complex xn = zn;
    while (zn.mag2() <= BAILOUT && itrs < params.maxItrs)
    {
        Complex zp = zn.power(params.P);
        zn = zp + c;
        zn.y = fabs(zn.y);
        xn = zp - c;
        xn.y = fabs(xn.y);
        zn = zn * xn;
        itrs++;
    }
    return getColor(itrs);
}

int getColor(int itrs)
{
    if (itrs == params.maxItrs)
        return 0xFF000000;
    int c = (itrs * 255) / params.maxItrs;
    return (255 << 24) | (c << 16) | (c << 8) | c;
}