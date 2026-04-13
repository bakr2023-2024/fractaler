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
        double logR = log(r);
        double mul = exp(a * logR - b * theta);
        double imag = a * theta + b * logR;
        return {mul * cos(imag), mul * sin(imag)};
    }
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
    PolynomialTerm differentiate(int degree = 1) const
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
    Complex substitute(const Complex &z) const { return coeff * (z.power(pow)); }
};
class Polynomial
{
public:
    string str;
    vector<PolynomialTerm> terms;

    Polynomial(){}
    Polynomial(const vector<PolynomialTerm> &terms) : terms(terms)
    {
    }
    void parse()
    {
        if (str.empty())
            return;
        bool inParen = false;
        vector<string> tokens{};
        string token = "";
        str.erase(remove(str.begin(), str.end(), ' '), str.end());
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == '(')
                inParen = true;
            else if (str[i] == ')')
                inParen = false;
            if ((str[i] == '+' || str[i] == '-') && !inParen)
            {
                if (!token.empty())
                    tokens.push_back(token);
                token = str[i];
            }
            else
                token += str[i];
        }
        if (!token.empty())
            tokens.push_back(token);
        double cx = 0, cy = 0, pow = 0;
        for (string &term : tokens)
        {
            token = "";
            int i = 0;
            i = term.find('(') + 1;
            token += term[i];
            i++;
            while (i < term.size() && term[i] != '+' && term[i] != '-')
                token += term[i++];
            cx = stod(token);
            token = "";
            while (i < term.size() && term[i] != 'i')
                token += term[i++];
            cy = stod(token);
            i += 2;
            pow = i >= term.size() ? 0 : i == (term.size() - 1) ? 1
                                                                : pow = stod(term.substr(i + 2));
            if ((term[0] == '-'))
                terms.push_back({-cx, -cy, pow});
            else
                terms.push_back({cx, cy, pow});
        }
    }
    Polynomial differentiate(int degree = 1)
    {
        vector<PolynomialTerm> poly;
        poly.reserve(terms.size());
        for (const PolynomialTerm &term : terms)
            poly.push_back(term.differentiate(degree));
        return {poly};
    }
    Complex substitute(const Complex &z)
    {
        Complex res = {0, 0};
        for (auto &term : terms)
            res = res + z.power(term.pow) * term.coeff;
        return res;
    }
};