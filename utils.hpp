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
    Complex operator^(const Complex &oth) const { return pow(oth.x, oth.y); }
    double mag() const { return sqrt(x * x + y * y); }
    double mag2() const { return x * x + y * y; }
    Complex pow(double x, double y) const
    {
        double r = mag();
        double e = exp(x);
        return Complex{r * e * cos(y), r * e * sin(y)};
    }
};