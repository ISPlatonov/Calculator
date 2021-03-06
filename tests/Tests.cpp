#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Calculator.hpp"


TEST_CASE("Проверка результата")
{
    REQUIRE(Calculator("1 + 2 + 3 * 4 + 5 * 6").GetResult() == 45);
    REQUIRE(Calculator("(5 + 232,32) * 333 +     8").GetResult() == 79035.56f);
    REQUIRE(Calculator("2*2*3    -1").GetResult() == 11);
    REQUIRE(Calculator("2*2*(3    -1)").GetResult() == 8);
    REQUIRE(Calculator("(-1)").GetResult() == -1);
    REQUIRE(Calculator("10 + (8 * 2.5) - (3 / 1,5)").GetResult() == 28);
    REQUIRE(Calculator("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)").GetResult() == 11);
    REQUIRE(Calculator("2-(-2)").GetResult() == 4);
    REQUIRE(Calculator("2*(2)").GetResult() == 4);
    REQUIRE(Calculator("2*(-2)").GetResult() == -4);
    REQUIRE(Calculator("2*(2-2)").GetResult() == 0);
    REQUIRE(Calculator("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)").GetResult() == 11);
    //REQUIRE(Calculator("1.1 + 2.1 + abc").GetResult() == -1);
    REQUIRE(Calculator("2 * (2-3)").GetResult() == -2);
    REQUIRE(Calculator("2 * (-3 + 2)").GetResult() == -2);
    REQUIRE(Calculator("2 - (-3 + 2)").GetResult() == 3);
    //REQUIRE(Calculator("2*(-(-(-3)))").GetResult() == -6);
}


TEST_CASE("Выброс исключений")
{
    CHECK_THROWS(Calculator("1.1 + 2.1 + abc").GetResult());
    CHECK_THROWS(Calculator("1.1 + 2.1 +").GetResult());
    CHECK_THROWS(Calculator("1.1 + 2.1 )").GetResult());
    CHECK_THROWS(Calculator(")1.1 + 2.1(").GetResult());
    CHECK_THROWS(Calculator("1.1 (+) 2.1").GetResult());
    CHECK_THROWS(Calculator("1.1 2.1").GetResult());
    CHECK_THROWS(Calculator("1.1 .1").GetResult());
    CHECK_THROWS(Calculator("1. 2.1").GetResult());
    CHECK_THROWS(Calculator("2/(2-2)").GetResult() == 0);
}