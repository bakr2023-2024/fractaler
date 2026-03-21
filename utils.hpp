#include <math.h>
class Complex
{
public:
    double x, y;
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