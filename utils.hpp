#include <math.h>
class Complex
{
public:
    double x, y;
    Complex(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    Complex operator+(const Complex &oth) const { return {x + oth.x, y + oth.y}; }
    Complex operator-(const Complex &oth) const { return {x - oth.x, y - oth.y}; }
    Complex operator*(const Complex &oth) const { return {x * oth.x - y * oth.y, x * oth.y + y * oth.x}; }
    Complex operator/(const Complex &oth) const
    {
        double denom = oth.x * oth.x + oth.y * oth.y;
        Complex num = Complex{x, y} * Complex{oth.x, -oth.y};
        return {num.x / denom, num.y / denom};
    }
    double mag() const { return sqrt(x * x + y * y); }
};