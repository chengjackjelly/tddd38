#include "../tool/catch.hpp"
#include "../include/Timex.h"

TEST_CASE("Test case IS VALID")
{
    // Your test code here
    Time x{1, 2, 4};
    CHECK(x.is_valid());
    Time y{100, 2, 4};
    CHECK_FALSE(y.is_valid());
}
TEST_CASE("Test case override")
{
    // Your test code here
    Time x{1, 2, 4};
    Time y{2, 2, 5};
    Time z = x + 3601;
    bool result = (z == y);
    CHECK(result);
}

TEST_CASE("Test case cout")
{
    // Your test code here
    Time x{1, 2, 4};
    std::cout << x << std::endl;
}