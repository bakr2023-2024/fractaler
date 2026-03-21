#pragma once
#include "utils.hpp"
#define BAILOUT 4.0
enum Algs
{
    MULTIBROT,
};
using Plotter = int (*)(Complex);
struct Params
{
    double P, Q, cx, cy = 0;
};
// params
extern Params params;
extern double maxItrs;
extern Plotter plot;
int getColor(int itrs);
int multibrot(Complex c);
void setPlotter(Algs alg);
