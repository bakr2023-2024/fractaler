#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../utils.hpp"
#include <format>
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