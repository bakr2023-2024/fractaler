#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../utils.hpp"
#include <format>
#include <iostream>
TEST_CASE("Testing Complex class")
{
    SUBCASE("Testing addition")
    {
        Complex res = Complex{1, 2} + Complex{3, 4};
        CHECK_EQ(res.x, 4);
        CHECK_EQ(res.y, 6);
    }
    SUBCASE("Testing subtraction")
    {
        Complex res = Complex{3, 4} - Complex{2, 1};
        CHECK_EQ(res.x, 1);
        CHECK_EQ(res.y, 3);
    }
    SUBCASE("Testing multiplication")
    {
        Complex res = Complex{3, 4} * Complex{2, 3};
        CHECK_EQ(res.x, -6);
        CHECK_EQ(res.y, 17);
    }
    SUBCASE("Testing division")
    {
        Complex res = Complex{6, 4} / Complex{2, 4};
        CHECK_EQ(res.x, 1.4);
        CHECK_EQ(res.y, -0.8);
    }
    SUBCASE("Testing magnitude")
    {
        double mag = Complex{3, 5}.mag();
        CHECK_GT(mag, 5.83);
        CHECK_LT(mag, 5.84);
    }
}
void checkComplex(const Complex &complex, double cx, double cy)
{
    CHECK_EQ(complex.x, cx);
    CHECK_EQ(complex.y, cy);
}
TEST_CASE("Testing PolynomialTerm class")
{
    PolynomialTerm term{-2, 3, 2};
    SUBCASE("Testing substitution")
    {
        checkComplex(term.substitute({4, 2}), -72, 4);
    }
    SUBCASE("Testing differentiation")
    {

        PolynomialTerm diff = term.differentiate(2);
        checkComplex(diff.coeff, -4, 6);
        CHECK_EQ(diff.pow, 0);
    }
}
TEST_CASE("Testing Polynomial class")
{
    Polynomial poly{"(2 - 3i)z^2 - (-4 + 2i)z + (13 + 5i)"};
    SUBCASE("Testing parsing")
    {
        checkComplex(poly.terms[0].coeff, 2, -3);
        CHECK_EQ(poly.terms[0].pow, 2);
        checkComplex(poly.terms[1].coeff, 4, -2);
        CHECK_EQ(poly.terms[1].pow, 1);
        checkComplex(poly.terms[2].coeff, 13, 5);
        CHECK_EQ(poly.terms[2].pow, 0);
    }
    SUBCASE("Testing differentiation")
    {
        Polynomial diff = poly.differentiate(1);
        checkComplex(diff.terms[0].coeff, 4, -6);
        CHECK_EQ(diff.terms[0].pow, 1);
        checkComplex(diff.terms[1].coeff, 4, -2);
        CHECK_EQ(diff.terms[1].pow, 0);
        checkComplex(diff.terms[2].coeff, 0, 0);
        CHECK_EQ(diff.terms[2].pow, 0);
    }
}