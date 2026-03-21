#pragma once
#include "utils.hpp"
#define BAILOUT 4.0
enum Algs
{
    MANDELBROT,
};
using Plotter = int (*)(Complex);
struct Params
{
    double P, Q;
};
// params
extern Params params;
extern double maxItrs;
extern Plotter plot;
int getColor(int itrs);
int mandelbrot(Complex c);
void setPlotter(Algs alg);
