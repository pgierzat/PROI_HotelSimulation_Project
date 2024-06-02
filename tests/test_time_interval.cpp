#include "catch_amalgamated.hpp"
#include "../src/types/time_interval.hpp"


TEST_CASE("Test TimeInterval")
{
    using namespace std::chrono_literals;

    auto start = jed_utils::datetime{2024, 6, 2, 6};
    auto end = jed_utils::datetime{2024, 6, 3, 8};
    auto interval = TimeInterval{start, end};

    SECTION("Test init")
    {
        REQUIRE(interval.get_start() == start);
        REQUIRE(interval.get_end() == end);
        REQUIRE(interval.get_duration() == end - start);
    }

    SECTION("Test month_to_interval")
    {
        using namespace std::chrono;
        auto exp_start = jed_utils::datetime{2024, 4, 1};
        auto exp_end = jed_utils::datetime{2024, 5, 1};
        auto exp = TimeInterval{exp_start, exp_end};
        REQUIRE( TimeInterval::month_to_interval(2024y / April) == exp );
    }
}
