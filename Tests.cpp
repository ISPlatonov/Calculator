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
}