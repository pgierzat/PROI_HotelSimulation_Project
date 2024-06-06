#include "catch_amalgamated.hpp"
#include "../src/systems/clock.hpp"


TEST_CASE("Test Clock, default init")
{
    Clock clock{};
    REQUIRE( clock.get_time() == jed_utils::datetime{1970, 1, 1} );
    REQUIRE( clock.get_unit_delta() == jed_utils::timespan{1} );
}

TEST_CASE("Test Clock, init")
{
    Clock clock{};
    auto unit_delta = jed_utils::timespan{0, 1};
    clock.set_unit_delta(unit_delta);
    REQUIRE( clock.get_time() == jed_utils::datetime{1970, 1, 1} );
    REQUIRE( clock.get_unit_delta() == unit_delta );
}

TEST_CASE("Test Clock, simple use")
{
    Clock clock{};
    auto delta = jed_utils::timespan{0, 1};
    clock.set_unit_delta(delta);
    jed_utils::datetime time{2024, 5, 11, 13};
    clock.set_time(time);

    SECTION("setters")
    {
        jed_utils::timespan ndelta{0, 0, 30};
        clock.set_unit_delta(ndelta);
        REQUIRE( clock.get_time() == time );
        REQUIRE( clock.get_unit_delta() == ndelta );
    }

    SECTION("+=")
    {
        jed_utils::timespan day{1};
        clock += day;
        REQUIRE( clock.get_time() == time + day );
    }

    SECTION("preincrement")
    {
        auto result = ++clock;
        REQUIRE( result == clock );
        REQUIRE( clock.get_time() == time + delta );
    }
}