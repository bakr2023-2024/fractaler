#pragma once
#include "utils.hpp"
#define BAILOUT 4.0
using Plotter = int (*)(const Complex &);
struct Params
{
    int algChoice = 0, themeChoice = 0, maxItrs = 0;
    double P = 0, Q = 0, cx = 0, cy = 0, λ = 0;
    std::string polyStr;

};
int getColor(int itrs);
Plotter getPlotter();
void setParams(Params params);
void buildPalettes();

int multibrot(const Complex &c);
int julia(const Complex &c);
int burningShip(const Complex &c);
int newton(const Complex &z);
int nova(const Complex &z);
int sine(const Complex &z);
int sineh(const Complex &z);
int newtonCosh(const Complex &z);
int collatz(const Complex &z);
int septagon(const Complex &z);
int magnet1(const Complex &c);
int magnet2(const Complex &c);
int cactus(const Complex &z);
int lambda(const Complex &z);
int barnsleyTree(const Complex &z);
int rings(const Complex &z);
int rogerRational(const Complex &z);
int spiralJulia(const Complex &z);
int tetration(const Complex &z);
int tripleDragon(const Complex &z);