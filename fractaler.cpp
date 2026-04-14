#include "fractaler.hpp"
static Params params;
static Plotter plotter;
static Polynomial poly, polyd;
static double tol = 0.00001;
static Plotter plotters[] = {multibrot, julia, burningShip, newton, nova, sine, sineh, newtonCosh,
                             collatz, septagon, magnet1, magnet2, cactus, lambda, barnsleyTree,
                             rings, rogerRational, spiralJulia, tetration, tripleDragon, phoenix};
enum class Fractals
{

};
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
    if (params.λ == 0)
    {
        while (z.mag2() <= BAILOUT && itrs < params.maxItrs)
        {
            z = z.power(params.P) + c;
            itrs++;
        }
    }
    else
    {
        while (z.mag2() <= BAILOUT && itrs < params.maxItrs)
        {
            z = z.power(params.P).conj() + c;
            itrs++;
        }
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
        z = Complex{abs(z.x), fabs(z.y)}.power(params.P) - c;
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
int phoenix(const Complex &z)
{
    Complex z_1 = {0, 0}, zn = {z.y, z.x};
    Complex c{params.cx, params.cy}, P{params.P, params.Q};
    int itrs = 0;
    while (zn.mag2() <= BAILOUT && itrs < params.maxItrs)
    {
        Complex zp = zn;
        zn = zn * zn + c + P * z_1;
        z_1 = zp;
        itrs++;
    }
    return getColor(itrs);
}
struct Theme
{
    float a[3], b[3], c[3], d[3];
};
static const Theme themes[] = {
    {{0.1f, 0.1f, 0.1f}, {0.8f, 0.8f, 0.8f}, {1.0f, 2.0f, 3.0f}, {0.0f, 0.0f, 0.5f}}, // Groovy
    {{0.9f, 0.7f, 0.9f}, {0.7f, 0.9f, 0.7f}, {0.9f, 0.9f, 1.0f}, {0.3f, 0.5f, 0.7f}}, // Pastel
    {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {2.0f, 2.0f, 2.0f}, {0.1f, 0.2f, 0.4f}}, // Bright
    {{0.1f, 0.2f, 0.4f}, {0.2f, 0.3f, 0.6f}, {1.0f, 2.0f, 3.0f}, {0.1f, 0.1f, 0.5f}}, // Deep Blues
    {{0.9f, 0.7f, 0.2f}, {1.0f, 0.8f, 0.3f}, {1.5f, 1.8f, 2.0f}, {0.0f, 0.0f, 0.3f}}, // Warm Golden
    {{0.3f, 0.1f, 0.6f}, {1.0f, 0.4f, 0.0f}, {0.9f, 2.0f, 3.0f}, {0.5f, 0.2f, 0.3f}}, // Vibrant
    {{0.1f, 0.1f, 0.3f}, {0.5f, 0.1f, 0.8f}, {1.0f, 1.5f, 2.0f}, {0.2f, 0.3f, 0.5f}}, // Cosmic
    {{0.0f, 1.0f, 0.0f}, {0.9f, 0.0f, 0.9f}, {2.0f, 1.5f, 1.0f}, {0.0f, 0.5f, 0.2f}}, // Neon
    {{0.8f, 0.5f, 0.3f}, {0.7f, 0.6f, 0.4f}, {1.0f, 1.2f, 1.5f}, {0.2f, 0.3f, 0.5f}}, // Mellow
    {{0.4f, 0.2f, 0.1f}, {0.6f, 0.3f, 0.2f}, {1.2f, 1.5f, 2.0f}, {0.1f, 0.1f, 0.3f}}, // Earthy
};
static const int themesCount = sizeof(themes) / sizeof(themes[0]);
static int palettes[themesCount][256] = {};
void buildPalettes()
{
    for (int tc = 0; tc < themesCount; tc++)
    {
        for (int i = 0; i <= 255; i++)
        {
            float t = i / 255.0f;
            int r = (int)(255 * (themes[tc].a[0] + themes[tc].b[0] * cosf(2 * M_PI * (themes[tc].c[0] * t + themes[tc].d[0]))));
            int g = (int)(255 * (themes[tc].a[1] + themes[tc].b[1] * cosf(2 * M_PI * (themes[tc].c[1] * t + themes[tc].d[1]))));
            int b = (int)(255 * (themes[tc].a[2] + themes[tc].b[2] * cosf(2 * M_PI * (themes[tc].c[2] * t + themes[tc].d[2]))));
            r = max(0, min(255, r));
            g = max(0, min(255, g));
            b = max(0, min(255, b));
            palettes[tc][i] = (255 << 24) | (r << 16) | (g << 8) | b;
        }
    }
}
int getColor(int itrs)
{
    return (itrs == params.maxItrs) ? 0 : palettes[params.themeChoice][(itrs * 255) / params.maxItrs];
}
