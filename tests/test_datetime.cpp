#include "../src/types/datetime.h"
#include "../src/types/timespan.h"
#include "catch_amalgamated.hpp"

TEST_CASE("Test datetime, year_month_day constructor")
{
    using namespace std::chrono;
    std::chrono::year_month_day ymd{2024y, May, 12d};
    jed_utils::datetime dt{ymd};
    REQUIRE( dt.get_year() == 2024 );
    REQUIRE( dt.get_month() == 5 );
    REQUIRE( dt.get_day() == 12 );
}

TEST_CASE("Test datetime operator-=, operator+=")
{
    jed_utils::datetime t{ 2024, 5, 11, 10, 10, 10};
    jed_utils::timespan dt{ 11, 10, 10, 11};
    jed_utils::datetime expected1{ 2024, 4, 29, 23, 59, 59 };
    jed_utils::datetime expected2 = t;
    t -= dt;
    REQUIRE( t == expected1 );
    t += dt;
    REQUIRE( t == expected2 );
}

TEST_CASE("Test datetime operator-(datetime, timespan), operator+")
{
    jed_utils::datetime t{ 2024, 5, 11, 10, 10, 10};
    jed_utils::timespan dt{ 11, 10, 10, 11};
    jed_utils::datetime expected{ 2024, 4, 29, 23, 59, 59 };
    REQUIRE( t - dt == expected );
    REQUIRE( expected + dt == t );
}
