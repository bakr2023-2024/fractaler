#include <math.h>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
class Complex
{
public:
    double x, y;
    Complex() : x(0), y(0) {};
    Complex(double x, double y) : x(x), y(y) {};
    Complex operator+(const Complex &oth) const { return {x + oth.x, y + oth.y}; }
    Complex operator-(const Complex &oth) const { return {x - oth.x, y - oth.y}; }
    Complex operator*(const Complex &oth) const { return {x * oth.x - y * oth.y, x * oth.y + y * oth.x}; }
    Complex operator/(const Complex &oth) const
    {
        double denom = oth.x * oth.x + oth.y * oth.y;
        Complex num = Complex{x, y} * Complex{oth.x, -oth.y};
        return {num.x / denom, num.y / denom};
    }
    Complex operator^(const Complex &oth) const { return power(oth.x, oth.y); }
    double mag() const { return sqrt(x * x + y * y); }
    double mag2() const { return x * x + y * y; }
    Complex power(double a, double b = 0) const
    {
        if (b == 0)
        {
            if (floor(a) == a)
            {
                int n = a;
                Complex res = {1, 0};
                Complex base = {x, y};
                while (n > 0)
                {
                    if (n % 2 == 1)
                        res = res * base;
                    base = base * base;
                    n /= 2;
                }
                return res;
            }
            double rn = pow(mag(), a);
            double theta = atan2(y, x);
            return {rn * cos(a * theta), rn * sin(a * theta)};
        }
        double r = mag();
        double theta = atan2(y, x);
        double mul = pow(r, a) * exp(-b * theta);
        double imag = a * theta + b * log(r);
        return {mul * cos(imag), mul * sin(imag)};
    }
};
class PolynomialTerm
{
public:
    Complex coeff;
    double pow = 0;
    PolynomialTerm(double coeffx, double coeffy, double pow)
    {
        this->coeff = {coeffx, coeffy};
        this->pow = pow;
    };
    PolynomialTerm differentiate(int degree)
    {
        if (pow == 0)
            return PolynomialTerm{0, 0, 0};
        double cx = coeff.x, cy = coeff.y, p = pow;
        for (int i = 0; i < degree; i++)
        {
            cx *= p;
            cy *= p;
            p--;
        }
        return PolynomialTerm{cx, cy, p};
    }
    Complex substitute(const Complex &z) { return (z * coeff).power(pow); }
};
