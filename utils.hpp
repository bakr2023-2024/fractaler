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
    Complex operator+(const Complex &oth) const { return {x + oth.x, y + oth.y}; }
    Complex operator-(const Complex &oth) const { return {x - oth.x, y - oth.y}; }
    Complex operator*(const Complex &oth) const { return {x * oth.x - y * oth.y, x * oth.y + y * oth.x}; }
    Complex operator/(const Complex &oth) const
    {
        double denom = oth.mag2();
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
        double logR = log(r);
        double mul = exp(a * logR - b * theta);
        double imag = a * theta + b * logR;
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
    Complex substitute(const Complex &z) { return coeff * (z.power(pow)); }
};
class Polynomial
{
public:
    vector<PolynomialTerm> terms;
    Polynomial(const string &s)
    {
        bool inParen = false;
        vector<string> tokens{};
        string token = "";
        string str = s;
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
};