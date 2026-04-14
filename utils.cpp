#include "utils.hpp"

Complex Complex::power(double a, double b) const
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

PolynomialTerm PolynomialTerm::differentiate(int degree) const
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

void Polynomial::parse()
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
Polynomial Polynomial::differentiate(int degree)
{
    vector<PolynomialTerm> poly;
    poly.reserve(terms.size());
    for (const PolynomialTerm &term : terms)
        poly.push_back(term.differentiate(degree));
    return {poly};
}
Complex Polynomial::substitute(const Complex &z)
{
    Complex res = {0, 0};
    for (auto &term : terms)
        res = res + z.power(term.pow) * term.coeff;
    return res;
}