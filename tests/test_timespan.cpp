#include "../src/types/timespan.h"
#include "catch_amalgamated.hpp"

TEST_CASE("Test timespan operator-=, +=")
{
    jed_utils::timespan dt1{ 12, 14, 21, 14};
    jed_utils::timespan dt2{ 12, 14, 21, 15};
    jed_utils::timespan expected1{0, 0, 0, -1};
    jed_utils::timespan expected2 = dt1;
    dt1 -= dt2;
    REQUIRE( dt1 == expected1 );
    dt1 += dt2;
    REQUIRE( dt1 == expected2 );
}

TEST_CASE("Test timespan operator-, +")
{
    jed_utils::timespan dt1{ 12, 14, 21, 14};
    jed_utils::timespan dt2{ 12, 14, 21, 15};
    jed_utils::timespan expected{0, 0, 0, -1};
    REQUIRE( dt1 - dt2 == expected );
    REQUIRE( dt2 + expected == dt1 );
}

TEST_CASE("Test timespan operator*=, *")
{
    jed_utils::timespan dt{ 1, 12};
    dt *= 4;
    REQUIRE( dt == jed_utils::timespan{6} );
    REQUIRE( dt * 4 == jed_utils::timespan{24} );
}
