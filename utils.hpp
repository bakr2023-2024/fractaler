#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

class Complex
{
public:
    double x, y;
    Complex() : x(0), y(0) {};
    Complex(double x, double y) : x(x), y(y) {};
    Complex inline operator+(const Complex &oth) const { return {x + oth.x, y + oth.y}; }
    Complex inline operator-(const Complex &oth) const { return {x - oth.x, y - oth.y}; }
    Complex inline operator*(const Complex &oth) const { return {x * oth.x - y * oth.y, x * oth.y + y * oth.x}; }
    Complex inline operator/(const Complex &oth) const
    {
        double denom = oth.mag2();
        Complex num = Complex{x, y} * Complex{oth.x, -oth.y};
        return {num.x / denom, num.y / denom};
    }
    Complex inline operator^(const Complex &oth) const { return power(oth.x, oth.y); }
    Complex inline plus(double real, double imag = 0) const { return Complex{x + real, y + imag}; };
    Complex inline minus(double real, double imag = 0) const { return Complex{x - real, y - imag}; };
    Complex inline multiply(double real, double imag = 0) const { return {x * real - y * imag, x * imag + y * real}; };
    Complex inline divide(double real, double imag = 0) const
    {
        double denom = real * real + imag * imag;
        Complex num = this->multiply(real, -imag);
        return {num.x / denom, num.y / denom};
    };
    double inline mag() const { return sqrt(x * x + y * y); }
    double inline mag2() const { return x * x + y * y; }
    Complex inline absolute() const { return Complex{abs(x), abs(y)}; };
    Complex power(double a, double b = 0) const;
    Complex inline sine() const
    {
        return Complex{sin(x) * cosh(y), cos(x) * sinh(y)};
    }
    Complex inline cosine() const
    {
        return Complex{cos(x) * cosh(y), -sin(x) * sinh(y)};
    }
    Complex inline tangent() const { return sine() / cosine(); }
    Complex inline sineh() const
    {
        return Complex{sinh(x) * cos(y), cosh(x) * sin(y)};
    }
    Complex inline cosineh() const
    {
        return Complex{cosh(x) * cos(y), sinh(x) * sin(y)};
    }
    Complex inline logarithm() const { return Complex{log(mag()), atan2(y, x)}; };
};
class PolynomialTerm
{
public:
    Complex coeff;
    double pow = 0;
    PolynomialTerm(double coeffx, double coeffy, double pow) : coeff(coeffx, coeffy), pow(pow) {}
    PolynomialTerm differentiate(int degree = 1) const;
    Complex inline substitute(const Complex &z) const { return coeff * (z.power(pow)); }
};
class Polynomial
{
public:
    vector<PolynomialTerm> terms;

    Polynomial(){}
    Polynomial(const vector<PolynomialTerm> &terms) : terms(terms) {}
    void parse(std::string str);
    Polynomial differentiate(int degree = 1);
    Complex substitute(const Complex &z);
};