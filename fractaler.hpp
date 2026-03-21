#pragma once
#include "utils.hpp"
#define BAILOUT 4.0
enum Algs
{
    MULTIBROT,
    JULIA
};
using Plotter = int (*)(Complex);
struct Params
{
    double P, Q, cx, cy = 0;
};
// params
extern Params params;
extern int maxItrs;
extern Plotter plot;
extern Plotter plotters[];
int getColor(int itrs);
int multibrot(Complex c);
int julia(Complex c);
void setPlotter(Algs alg);
