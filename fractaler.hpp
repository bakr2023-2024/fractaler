#pragma once
#include "utils.hpp"
#define BAILOUT 4.0
using Plotter = int (*)(const Complex &);
struct Params
{
    double P, Q, cx, cy, λ = 0;
    Polynomial poly, polyd;
};
// params
extern Params params;
extern int maxItrs;
extern double tol;
extern Plotter plot;
extern Plotter plotters[];
int getColor(int itrs);
int multibrot(const Complex &c);
int julia(const Complex &c);
int burningShip(const Complex &c);
int newton(const Complex &z);
int nova(const Complex &z);
int sin(const Complex &z);
int sinh(const Complex &z);
int newtonCosh(const Complex &z);
int collatz(const Complex &z);
int septagon(const Complex &z);
int magnet1(const Complex &c);
int magnet2(const Complex &c);
int cactus(const Complex &z);
int lambda(const Complex &z);
int barnsleyTree(const Complex &z);
void setPlotter(int choice);
