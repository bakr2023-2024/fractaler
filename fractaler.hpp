#include <functional>
#include "utils.hpp"
enum Algs
{
    MANDELBROT,
};
using Plotter = std::function<int(Complex)>;
class Fractaler
{
private:
    int getColor(int itrs);

public:
    double width, height, maxItrs;
    double BAILOUT = 4.0;
    Plotter plot;
    Fractaler(double width, double height, int maxItrs)
    {
        this->width = width;
        this->height = height;
        this->maxItrs = maxItrs;
    }
    int mandelbrot(Complex c);
    void setPlotter(Algs alg)
    {
        switch (alg)
        {
        case MANDELBROT:
            plot = [this](Complex c)
            { return mandelbrot(c); };
            break;
        default:
            break;
        }
    }
};